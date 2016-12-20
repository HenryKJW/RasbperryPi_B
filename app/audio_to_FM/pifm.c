// To run:
//  wget -O - http://beta.etherpad.org/p/pihackfm/export/txt 2>/dev/null | gcc -lm -std=c99 -g -xc - && ./a.out beatles.wav
// Access from ARM Running Linux


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
char *gpio_mem, *gpio_map;
char *spi0_mem, *spi0_map;

// I/O access
volatile unsigned *gpio;
volatile unsigned *allof7e;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
#define GPIO_GET *(gpio+13)  // sets   bits which are 1 ignores bits which are 0

#define ACCESS(base)		*(volatile int*)((int)allof7e+base-0x7e000000)
#define SETBIT(base, bit)	ACCESS(base) |= 1<<bit
#define CLRBIT(base, bit)	ACCESS(base) &= ~(1<<bit)

#define CM_GP0CTL	(0x7e101070)
#define GPFSEL0		(0x7E200000)
#define CM_GP0DIV	(0x7e101074)
#define CLKBASE		(0x7E101000)
#define DMABASE		(0x7E007000)
#define PWMBASE		(0x7e20C000) /* PWM controller */
#define PADS_GPIO_0_27	(0x7e10002c)

struct GPCTL {
    char SRC		: 4;
    char ENAB		: 1;
    char KILL		: 1;
    char			: 1;
    char BUSY		: 1;
    char FLIP		: 1;
    char MASH		: 2;
    unsigned int	: 13;
    char PASSWD	: 8;
};

void getRealMemPage(void** vAddr, void** pAddr) {
    void* a = valloc(4096);
    
    ((int*)a)[0] = 1;  // use page to force allocation.
    
    mlock(a, 4096);  // lock into ram.

    *vAddr = a;  // yay - we know the virtual address

    unsigned long long frameinfo;

    int fp = open("/proc/self/pagemap", 'r');
    lseek(fp, ((int)a)/4096*8, SEEK_SET);
    read(fp, &frameinfo, sizeof(frameinfo));

    *pAddr = (void*)((int)(frameinfo*4096));
}

void freeRealMemPage(void* vAddr) {
    
    munlock(vAddr, 4096);  // unlock ram.
    
    free(vAddr);
}


void setup_fm()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
        printf("can't open /dev/mem \n");
        exit (-1);
    }
    
    allof7e = (unsigned *)mmap(
                  NULL,
                  0x01000000,  //len
                  PROT_READ|PROT_WRITE,
                  MAP_SHARED,
                  mem_fd,
                  0x20000000  //base
              );

    if ((int)allof7e==-1) exit(-1);

    SETBIT(GPFSEL0 , 14);//GPIO - GPCLK0
    CLRBIT(GPFSEL0 , 13);
    CLRBIT(GPFSEL0 , 12);

    // Set GPIO drive strength, more info: http://www.scribd.com/doc/101830961/GPIO-Pads-Control2 
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 0;  //2mA -3.4dBm
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 1;  //4mA +2.1dBm
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 2;  //6mA +4.9dBm
    ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 3;  //8mA +6.6dBm(default)
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 4;  //10mA +8.2dBm
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 5;  //12mA +9.2dBm
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 6;  //14mA +10.0dBm
    //ACCESS(PADS_GPIO_0_27) = 0x5a000018 + 7;  //16mA +10.6dBm

    struct GPCTL setupword = {6/*SRC*/, 1, 0, 0, 0, 1,0x5a};// 1-stage MASH, PLLD = 500MHz

    ACCESS(CM_GP0CTL) = *((int*)&setupword);
}


void modulate(int m)
{
    ACCESS(CM_GP0DIV) = (0x5a << 24) + 0x4d72 + m;
}

struct CB {
    volatile unsigned int TI;
    volatile unsigned int SOURCE_AD;
    volatile unsigned int DEST_AD;
    volatile unsigned int TXFR_LEN;
    volatile unsigned int STRIDE;
    volatile unsigned int NEXTCONBK;
    volatile unsigned int RES1;
    volatile unsigned int RES2;
    
};

struct DMAregs {
    volatile unsigned int CS;
    volatile unsigned int CONBLK_AD;
    volatile unsigned int TI;
    volatile unsigned int SOURCE_AD;
    volatile unsigned int DEST_AD;
    volatile unsigned int TXFR_LEN;
    volatile unsigned int STRIDE;
    volatile unsigned int NEXTCONBK;
    volatile unsigned int DEBUG;
};

struct PageInfo {
    void* p;  // physical address
    void* v;   // virtual address
};

struct PageInfo constPage;
struct PageInfo instrPage;
struct PageInfo instrs[1024];

void playWav(char* filename, float samplerate)
{
    int fp= STDIN_FILENO;
    if(filename[0]!='-') fp = open(filename, 'r');
    //int sz = lseek(fp, 0L, SEEK_END);
    //lseek(fp, 0L, SEEK_SET);
    //short* data = (short*)malloc(sz);
    //read(fp, data, sz);
    
    int bufPtr=0;
    float datanew, dataold = 0;
    short data;
    
    for (int i=0; i<22; i++)
       read(fp, &data, 2);  // read past header
    
    while (read(fp, &data, 2)) {
	float fmconstant = samplerate * 50.0e-6;  // for pre-emphisis filter.  50us time constant (20KHz)
	int clocksPerSample = 22500.0/samplerate*1400.0;  // for timing

	datanew = (float)(data)/32767;
            
        float sample = datanew;// + (dataold-datanew) / (1-fmconstant);  // fir of 1 + s tau
        float dval = sample*15.0;  // actual transmitted sample.  15 is bandwidth (about 75 kHz)
        
        int intval = (int)(round(dval));  // integer component
        float frac = (dval - (float)intval)/2 + 0.5;
        unsigned int fracval = frac*clocksPerSample;

#if 0
if(intval!=0)
{
	printf("playWav: sample=%f, dval=%f  \n",sample, dval);//Henry Test
	printf("playWav: intval=%d, frac=%f ,fracval=%x \n", intval, frac, fracval);//Henry Test
}
#endif

#if 1
        bufPtr++;
        while( ACCESS(DMABASE + 0x04 /* CurBlock*/) ==  (int)(instrs[bufPtr].p)) usleep(1000);
        ((struct CB*)(instrs[bufPtr].v))->SOURCE_AD = (int)constPage.p + 2048 + intval*4 - 4 ;

//if(intval!=0)
//	printf("playWav1: bufPtr=%d, intval=%d, SOURCE_AD=%x  \n",bufPtr, intval, *(int *)((int) constPage.v+2048+intval*4-4));//Henry Test
        
        bufPtr++;
        while( ACCESS(DMABASE + 0x04 /* CurBlock*/) ==  (int)(instrs[bufPtr].p)) usleep(1000);
        ((struct CB*)(instrs[bufPtr].v))->TXFR_LEN = clocksPerSample-fracval;

//if(intval!=0)
//	printf("playWav2: bufPtr=%d, TXFR_LEN=%x  \n",bufPtr, (clocksPerSample-fracval));//Henry Test
        
        bufPtr++;
        while( ACCESS(DMABASE + 0x04 /* CurBlock*/) ==  (int)(instrs[bufPtr].p)) usleep(1000);
        ((struct CB*)(instrs[bufPtr].v))->SOURCE_AD = (int)constPage.p + 2048 + intval*4 + 4;

//if(intval!=0)
//	printf("playWav3: bufPtr=%d, intval=%d, SOURCE_AD=%x  \n",bufPtr, intval, *(int *)((int)constPage.v+2048+intval*4+4));//Henry Test
        
        bufPtr=(bufPtr+1) % (1024);
        while( ACCESS(DMABASE + 0x04 /* CurBlock*/) ==  (int)(instrs[bufPtr].p)) usleep(1000);
        ((struct CB*)(instrs[bufPtr].v))->TXFR_LEN = fracval;

//if(intval!=0)
//	printf("playWav4: bufPtr=%d, TXFR_LEN=%x  \n",bufPtr, fracval);//Henry Test
#endif
        dataold = datanew;
    }
    close(fp);
}

void unSetupDMA(){
    printf("exiting\n");
    struct DMAregs* DMA0 = (struct DMAregs*)&(ACCESS(DMABASE));
    DMA0->CS =1<<31;  // reset dma controller
}

void handSig() {
    exit(0);
}

//PWM via DMA (up to 1us resolution)
void setupDMA( float centerFreq ){

  atexit(unSetupDMA);
  signal (SIGINT, handSig);
  signal (SIGTERM, handSig);
  signal (SIGHUP, handSig);
  signal (SIGQUIT, handSig);

   // allocate a few pages of ram
   getRealMemPage(&constPage.v, &constPage.p);
   
   int centerFreqDivider = (int)((500.0 / centerFreq) * (float)(1<<12) + 0.5); // DIVI value(23~12 bit)

//   printf("setupDMA: constPage.v=%x - constPage.p=%x \n",constPage.v,constPage.p);//Henry Test
   
   // make data page contents - it's essientially 1024 different commands for the
   // DMA controller to send to the clock module at the correct time.
   for (int i=0; i<1024; i++)
{
     ((int*)(constPage.v))[i] = (0x5a << 24) + centerFreqDivider - 512 + i;
//     printf("setupDMA: centerFreqDivider[%d]=%x \n",i,*((int*)constPage.v+i));//Henry Test
}
   
  int instrCnt = 0;
 
  while (instrCnt<1024) {
 
    getRealMemPage(&instrPage.v, &instrPage.p);

    // make copy instructions
 
    struct CB* instr0= (struct CB*)instrPage.v;
 
    for (int i=0; i<4096/sizeof(struct CB); i++) {
 
      instrs[instrCnt].v = (void*)((int)instrPage.v + sizeof(struct CB)*i);
 
      instrs[instrCnt].p = (void*)((int)instrPage.p + sizeof(struct CB)*i);
 
      instr0->SOURCE_AD = (unsigned int)constPage.p+2048;  //select ¤¤¤ßÂIFM Frequency
 
      instr0->DEST_AD = PWMBASE+0x18 /* FIF1 */;
 
      instr0->TXFR_LEN = 4;
 
      instr0->STRIDE = 0;
 
      //instr0->NEXTCONBK = (int)instrPage.p + sizeof(struct CB)*(i+1);
 
      instr0->TI = (1/* DREQ  */<<6) | (5 /* PWM */<<16) |  (1<<26/* no wide*/) ;
 
      instr0->RES1 = 0;
 
      instr0->RES2 = 0;
 
      if (i%2) {
 
        instr0->DEST_AD = CM_GP0DIV;
 
        instr0->STRIDE = 4;
 
        instr0->TI = (1<<26/* no wide*/);
 
      }
 
      if (instrCnt!=0) ((struct CB*)(instrs[instrCnt-1].v))->NEXTCONBK = (int)instrs[instrCnt].p;
 
      instr0++;
 
      instrCnt++;
 
    }
 
  }
 
  ((struct CB*)(instrs[1023].v))->NEXTCONBK = (int)instrs[0].p;
 
  // set up a clock for the PWM

  ACCESS(CLKBASE + 40*4 /*PWMCLK_CNTL*/) = 0x5A000026;// Source=PLLD and disable
 
  usleep(1000);

  ACCESS(CLKBASE + 41*4 /*PWMCLK_DIV*/)  = 0x5A002000; // set  PWM div to 2, for 250MHZ      
//  ACCESS(CLKBASE + 41*4 /*PWMCLK_DIV*/)  = 0x5A002800;// 500/2.5 (MHz)= 200 (MHz)
 
  ACCESS(CLKBASE + 40*4 /*PWMCLK_CNTL*/) = 0x5A000016;	// Source=PLLD and enable
 
  usleep(1000); 
 
  // set up pwm
 
  ACCESS(PWMBASE + 0x0 /* CTRL*/) = 0;
 
  usleep(1000);
 
  ACCESS(PWMBASE + 0x4 /* status*/) = -1;  // clear errors
 
  usleep(1000);
 
  ACCESS(PWMBASE + 0x0 /* CTRL*/) = -1; //(1<<13 /* Use fifo */) | (1<<10 /* repeat */) | (1<<9 /* serializer */) | (1<<8 /* enable ch */) ;
 
  usleep(1000);
 
  ACCESS(PWMBASE + 0x8 /* DMAC*/) = (1<<31 /* DMA enable */) | 0x0707;
 
  //activate dma
 
  struct DMAregs* DMA0 = (struct DMAregs*)&(ACCESS(DMABASE));
 
  DMA0->CS =1<<31;  // reset
 
  DMA0->CONBLK_AD=0; 
 
  DMA0->TI=0; 
 
  DMA0->CONBLK_AD = (unsigned int)(instrPage.p);
 
  DMA0->CS =(1<<0)|(255 <<16);  // enable bit = 0, clear end flag = 1, prio=19-16
}

int main(int argc, char **argv)
{

   if (argc>1) {
 
     setup_fm();
 
     setupDMA(argc>2?atof(argv[2]):103.3);
 
     playWav(argv[1], argc>3?atof(argv[3]):22500);
 
   } else
 
     fprintf(stderr, "Usage:   program wavfile.wav [freq] [sample rate]\n\nWhere wavfile is 16 bit 22.5kHz Mono.  Set wavfile to '-' to use stdin.\nfreq is in Mhz (default 103.3)\nsample rate of wav file in Hz\n\nPlay an empty file to transmit silence\n");
 
   return 0;

}
 // main
