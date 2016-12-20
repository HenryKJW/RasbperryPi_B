#include <bcm2835.h>
#include <stddef.h>
#include <stdio.h>

#define BCM8235_PWM_Serialiser_TestData	1
#define BCM8235_PWM_Serialiser_TestFIFO	2
#define BCM8235_PWM_Serialiser_DMA			3

#define RunCode								3

#define PWM_CHANNEL						0

#define DMASize								1024//Max 1024
PageInfo constDMAPage;
PageInfo CBTableDMAPage;
PageInfo RecordDMAAddress[DMASize];

//return TRUE=keep run ,FALSE=quit programming.
int ControlScreen(uint32_t data)
{
	char string;

	string=getchar();
	if(string!=0)
	{
		printf("Input PWM DMA Control : \n");
		printf("1:GPCLK_Osc \n");
		printf("2:GPCLK_PLLD \n");
		printf("3:Reset PWM FIFO&DMA \n");
		printf("q:Exit PWM \n\n");
		switch(string)
		{
			case '1':
				bcm2835_gpio_fsel(RPI_GPIO_P1_07, BCM2835_GPIO_FSEL_ALT0);
				//Source=PLLD (500 MHz), 1-stage MASH.
				bcm2835_cm_set_clock(BCM2835_CM_MashControl_1_Stage_Mash, BCM2835_CM_ClockSource_Oscillator, 2, 0);
				break;

			case '2':
				bcm2835_gpio_fsel(RPI_GPIO_P1_07, BCM2835_GPIO_FSEL_ALT0);
				//  Source=PLLD (500 MHz), 1-stage MASH.
				bcm2835_cm_set_clock(BCM2835_CM_MashControl_1_Stage_Mash, BCM2835_CM_ClockSource_PLLD_per, 2, 0);
				break;

			case '3':
				bcm2835_DMA_unSetupDMA();
				bcm2835_pwm_reset_fifo(TRUE);
				bcm2835_pwm_reset_pwm_enable(PWM_CHANNEL);
				break;
				
			case 'q':
				return FALSE;
		}
		string = 0;
		return TRUE;
	}
	return TRUE;
}

void Setup_DMA_CB(void)
{
	int	i;

	uint32_t DMA_Value=0xFFFFFFFF, DMA_Count=1;

	getRealMemPage(&constDMAPage.v, &constDMAPage.p);

#if 0//debug
	printf("Setup_DMA_CB-->constDMAPage.p: %x---------------------\n", constDMAPage.p);
#endif

	for(i=0;i < DMASize ; i++)
	{
		((uint32_t*)(constDMAPage.v))[i] = DMA_Value;
		DMA_Value &= ~(DMA_Count);
		DMA_Count <<= 1;
#if 0//debug
		printf("[%d], DMA_Value=%x, DMA_Count=%x \n",i, DMA_Value, DMA_Count);
#endif
	}

	getRealMemPage(&CBTableDMAPage.v, &CBTableDMAPage.p);
       BCM2835_DMA_CB* instr0 = (BCM2835_DMA_CB*) CBTableDMAPage.v;

#if 0//debug
	printf("Setup_DMA_CB-->CBTableDMAPage.p:%x---------------------\n", CBTableDMAPage.p);
#endif

	for (i=0; i < DMASize; i++) //4096/sizeof(BCM2835_DMA_CB)
	{
		RecordDMAAddress[i].v = (void*)((int)CBTableDMAPage.v + sizeof(BCM2835_DMA_CB)*i);
		RecordDMAAddress[i].p = (void*)((int)CBTableDMAPage.p + sizeof(BCM2835_DMA_CB)*i);

		instr0->SOURCE_AD = (unsigned int) constDMAPage.p +(4*i);
//		instr0->DEST_AD = (unsigned int) (bcm2835_pwm+BCM2835_PWM_FIF1);
		instr0->DEST_AD = (unsigned int) 0x7e20C000 + 0x18;
		instr0->TXFR_LEN = 4;
		instr0->STRIDE = 0;
	      //instr0->NEXTCONBK = (int)instrPage.p + sizeof(struct CB)*(i+1);
		instr0->TI = BCM2835_DMA_TI_DEST_WRITE_DREQ | (BCM2835_DMA_DREQ_PWM<<16) | BCM2835_DMA_TI_NO_WIDE_BURSTS ;//BCM2835_DMA_WAIT_RESP | 
 		instr0->RES1 = 0;
		instr0->RES2 = 0;

#if 0//debug
		printf("constDMAPage.p +(4*%x):  %x, bcm2835_pwm=%x, bcm2835_pwm+BCM2835_PWM_FIF1=%x \n",i, (unsigned int)constDMAPage.p +(4*i), bcm2835_pwm, bcm2835_pwm+BCM2835_PWM_FIF1);
#endif

		if (i!=0)
			((BCM2835_DMA_CB*)(RecordDMAAddress[i-1].v))->NEXTCONBK = (int)RecordDMAAddress[i].p;
 		instr0++;
 	}
	((BCM2835_DMA_CB*)(RecordDMAAddress[DMASize-1].v))->NEXTCONBK = (int)RecordDMAAddress[0].p;

#if 0//debug
	for (i=0; i < 32; i++) //4096/sizeof(BCM2835_DMA_CB)
	{
		printf("Setup_DMA_CB[%d]: %x,     NEXTCONBK:%x---------------------\n",i, RecordDMAAddress[i].p,((BCM2835_DMA_CB*)(RecordDMAAddress[i].v))->NEXTCONBK);
	}
#endif
}


int main(int argc, char **argv)
{
   if(!bcm2835_init())
    return 1;

#if (RunCode==BCM8235_PWM_Serialiser_TestData)
  int direction = 1;
  uint32_t data = 0xFFFFFFFF;
  uint32_t RANGE=32;

  bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_ALT5);
  bcm2835_all_set_clock(BCM2835_CM_PWMCLK, BCM2835_CM_MashControl_Integer_Division, BCM2835_CM_ClockSource_Oscillator, BCM2835_PWM_CLOCK_DIVIDER_2, 0);

  bcm2835_pwm_set_channel_out(PWM_CHANNEL, BCM2835_PWM_OUTPUTMODE_SERIALISER, BCM2835_DATA_REGEISTER);
  bcm2835_pwm_reset_pwm_enable(PWM_CHANNEL);

  bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
  bcm2835_pwm_set_data(PWM_CHANNEL, data);
  while (1)
  {
/*
	if (data == 1)
		direction = 1;
	else if (data == RANGE-1)
		direction = -1;
	data += direction;
	bcm2835_pwm_set_data(PWM_CHANNEL, data);
*/
	bcm2835_delay(50);
	if(FALSE==ControlScreen(data))
		break;
  }
#endif

#if (RunCode==BCM8235_PWM_Serialiser_TestFIFO)
  uint32_t data = 0xFFFF0000;
  uint32_t RANGE=32;

  bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_ALT5);
  bcm2835_all_set_clock(BCM2835_CM_PWMCLK, BCM2835_CM_MashControl_Integer_Division,BCM2835_CM_ClockSource_Oscillator , BCM2835_PWM_CLOCK_DIVIDER_2, 0);//BCM2835_CM_ClockSource_PLLD_per

  bcm2835_pwm_set_channel_out(PWM_CHANNEL, BCM2835_PWM_OUTPUTMODE_SERIALISER, BCM2835_FIFO);
  bcm2835_pwm_reset_pwm_enable(PWM_CHANNEL);
  
  bcm2835_pwm_set_fifo_ctl(PWM_CHANNEL, 1);
  bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
  bcm2835_pwm_reset_fifo(TRUE);
  bcm2835_pwm_set_fifo_data(data);
  while (1)
  {
#if 0
	bcm2835_delayMicroseconds(3);
	bcm2835_pwm_set_fifo_data(0xFFFF0000);
	bcm2835_delayMicroseconds(4);
	bcm2835_pwm_set_fifo_data(0x0000FFFF);
#else
//	bcm2835_delay(50);
	if(FALSE==ControlScreen(data))
		break;
#endif
  }
#endif

#if (RunCode==BCM8235_PWM_Serialiser_DMA)
  uint32_t control;
  int j=0;

//PWM
  bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_ALT5);
  bcm2835_all_set_clock(BCM2835_CM_PWMCLK, BCM2835_CM_MashControl_Integer_Division, BCM2835_CM_ClockSource_PLLD_per, BCM2835_PWM_CLOCK_DIVIDER_1, 0x03);//BCM2835_CM_ClockSource_Oscillator

  bcm2835_pwm_set_channel_out(PWM_CHANNEL, BCM2835_PWM_OUTPUTMODE_SERIALISER, BCM2835_FIFO);
  bcm2835_pwm_reset_pwm_enable(PWM_CHANNEL);

  bcm2835_pwm_set_fifo_ctl(PWM_CHANNEL, 1);
  bcm2835_pwm_set_range(PWM_CHANNEL, 32);
  bcm2835_pwm_reset_fifo(TRUE);
  bcm2835_pwm_set_DMA(TRUE);
//DMA
#if 1
  Setup_DMA_CB();
  bcm2835_DMA_SetupDMA(&CBTableDMAPage.p);
#endif

  while (1)
  {
#if 0
	int j=0;

	for(j=0;j<32; j++)
	{
		*(volatile uint32_t*)(bcm2835_pwm+BCM2835_PWM_FIF1) = ((volatile uint32_t*)(constDMAPage.v))[j];
		bcm2835_delay(100);
		printf("DMA [%x]: %x ----------------------\n", j, ((uint32_t*)(constDMAPage.v))[j]);
	}
	break;
#endif
#if 0
	if(FALSE==ControlScreen(0))
		break;
#endif
  }
#if 1
	bcm2835_delayMicroseconds(1);
#endif
  bcm2835_DMA_unSetupDMA();
  freeRealMemPage(constDMAPage.v);
  freeRealMemPage(CBTableDMAPage.v);
#endif

  bcm2835_close();
  return 0;
}
