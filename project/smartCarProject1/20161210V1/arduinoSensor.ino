//**********************************************************
// Include
//**********************************************************
#include <Wire.h>
//Leonardo：2 (SDA), 3 (SCL)
//Uno, Ethernet：A4 (SDA), A5 (SCL)
//**********************************************************
// Define
//**********************************************************
//I2C define
#define I2CSlaveAddress 0x14
#define I2CBuzzerRegister '0'
#define I2CSMDLedRegister '1'
#define I2CLeaserRegister '2'

#define I2CBuffer         5
//Buzzer --------------------------------
#define BuzzerPin               4     //設置控制蜂鳴器的數字IO腳

#define I2CBuzzerFunPassiveOn  '0'  //無源buzzer控制-['0', '0', frq, time]
#define I2CBuzzerFunOn         '1'  //有源buzzer控制-['0', '1', 100ms]

void PassiveBuzeerOn(long frq,long onTime);//frq Hz, onTime sec
void BuzzerOn(char onTime);//OnTime - sec
//SMD LED ---------------------------------
#define RedPin        9
#define GreenPin      11
#define BluePin       10

#define I2CSMDLedFunPWMOn     '0' //-['1', '0', (R=0,G=1,B=2),PWM]
#define I2CSMDLedFunOff       '1' //-['1', '1']
#define I2CSMDLedFunOnTime    '2' //-['1', '2', (R=0,G=1,B=2), 100ms]

void SMDLedPWMOn(char RGBlight,char Pwm);
void SMDLedOff(void);
void SMDLedOnTime(char RGBlight,char OnTime);
//Leaser-------------------------------------------
#define LeaserPin   5

#define I2CLeaserFunOn     '0' //-['2', '0', [0-Off, 1-On]]

void LeaserOn(char Status);
//Common-------------------------------------------
#define Debug            Serial
#define dugStatus        false  //true,false
//**********************************************************
// variable
//**********************************************************
//I2C define
char getI2CIndex,putI2CIndex;
char I2CSlaveRegisterData[I2CBuffer],I2CSlaveFun[I2CBuffer],I2CSlaveData1[I2CBuffer],I2CSlaveData2[I2CBuffer];
//**********************************************************
// Func Code
//**********************************************************
//buzzer ----------------------------------
void PassiveBuzeerOn(long frq,long onTime)//frq Hz, onTime sec
{
  long i,j;
  j = 1000000/frq;  //1(sec)/frq(Hz) =xx(us)時間
  i = onTime*1000000/frq/2; //for次數*xx(us)時間=onTime時間
  for(i= frq; i>=0; i--)//播放2 sec
  {
    digitalWrite(BuzzerPin,HIGH);//發聲音
    delayMicroseconds(j);//延時us
    digitalWrite(BuzzerPin,LOW);//不發聲音
    delayMicroseconds(j);//延時us
  }
}

void BuzzerOn(char onTime)//OnTime - sec
{
  if(dugStatus==true)
  {
    Debug.print("BuzzerOn-onTime:(DEC)");
    Debug.println(onTime,DEC);
  }
  digitalWrite(BuzzerPin,HIGH);//發聲音
  delay(onTime*100);
  digitalWrite(BuzzerPin,LOW);//不發聲音
}
//Led --------------------------------------
void SMDLedPWMOn(char RGBlight,char Pwm)
//RGBlight(R=0,G=1,B=2), PWM(0~255)
{
  if(dugStatus==true)
  {
    Debug.print("SMDLedPWMOn RGBlight:(DEC)");
    Debug.println(RGBlight,DEC);
    Debug.print("SMDLedPWMOn Pwm:(DEC)");
    Debug.println(Pwm,DEC);
  }
  if(RGBlight==0)
    analogWrite(RedPin, Pwm);
  if(RGBlight==1)
    analogWrite(GreenPin, Pwm);
  if(RGBlight==2)
    analogWrite(BluePin, Pwm);
}

void SMDLedOff(void)
{
  analogWrite(RedPin, 255);
  analogWrite(GreenPin, 255);
  analogWrite(BluePin, 255);
}

void SMDLedOnTime(char RGBlight,char OnTime)
//RGBlight(R=0,G=1,B=2), OnTime-100ms
{
  if(RGBlight==0)
  {  
    analogWrite(RedPin, 255);
    delay(OnTime*100);
    analogWrite(RedPin, 0);
  }
  if(RGBlight==1)
  {
    analogWrite(GreenPin, 255);
    delay(OnTime*100);
    analogWrite(GreenPin, 0);
  }
  if(RGBlight==2)
  {
    analogWrite(BluePin, 255);
    delay(OnTime*100);
    analogWrite(BluePin, 0);
  }
}
//Leaser-------------------------------------------
void LeaserOn(char Status)
{
  if(dugStatus==true)
  {
    Debug.print("LeaserOn Status:(DEC)");
    Debug.println(Status,DEC);
  }
  if(Status==1)
    digitalWrite(LeaserPin, HIGH);
  else
    digitalWrite(LeaserPin, LOW);   
}
//Common-------------------------------------------
void cleanI2CDate(void)
{
  int i;
  
  for(i=0;i<I2CBuffer;i++)
  {
    I2CSlaveRegisterData[i] = 0;
    I2CSlaveFun[i] = 0;
    I2CSlaveData1[i] = 0;
    I2CSlaveData2[i] = 0;
  }
  getI2CIndex=0;
  putI2CIndex=0;
}

char checkI2CQueueFull(void)//確認Queue是否為Full.(Full為1,not Full為0)
{
  char temp;

  temp=putI2CIndex+1;
  temp%=3;
  if(dugStatus==true)
  {  
    Debug.print("checkI2CQueueFull-temp:");// UART debug module
    Debug.println(temp,DEC);  
    Debug.print("checkI2CQueueFull-getI2CIndex:");// UART debug module
    Debug.println(getI2CIndex,DEC);
  }
  if(temp!=getI2CIndex)
    return false;
  return true;
}

void putDatatoQueue(void)
{
  putI2CIndex++;
  putI2CIndex%=3;
  if(dugStatus==true)
  {
    Debug.print("putDatatoQueue:");// UART debug module
    Debug.println(putI2CIndex);
  }  
}

char checkI2CQueueEmpty(void)//當Queue為Empty為1,否則為0
{
  //Debug.print("loop-getI2CIndex:");// UART debug module
  //Debug.println(getI2CIndex,DEC);  
  //Debug.print("loop-putI2CIndex:");// UART debug module
  //Debug.println(putI2CIndex,DEC);
  if(getI2CIndex!=putI2CIndex)
     return false;
  return true;
}

void getDatafromQueue(void)
{
  getI2CIndex++;
  getI2CIndex%=3;
  if(dugStatus==true)
  {
    Debug.print("getDatafromQueue:");// UART debug module
    Debug.println(getI2CIndex);
  }
}
//**********************************************************
// Main
//**********************************************************
void setup()
{
//UART
  if(dugStatus==true)
  {
    Debug.begin(115200);// UART debug module
    Debug.println("arduino Sensor by I2C Slaver");
  }
//I2C
  Wire.begin(I2CSlaveAddress);// join i2c bus with address 0x08
  Wire.onReceive(receiveEvent);// register event
//buzzer
  pinMode(BuzzerPin,OUTPUT);//設置數字IO腳模擬,OUTPUT
//LED
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  digitalWrite(RedPin, HIGH);
  digitalWrite(GreenPin, HIGH);  
  digitalWrite(BluePin, HIGH);  
//Leaser
  pinMode(LeaserPin, OUTPUT);
  cleanI2CDate();
}

void loop()
{
  //delay(500);
  if(!checkI2CQueueEmpty())
  {
    switch(I2CSlaveRegisterData[getI2CIndex])
    {
      case I2CBuzzerRegister:
        switch(I2CSlaveFun[getI2CIndex])
        {
          case I2CBuzzerFunPassiveOn:
            //PassiveBuzeerOn(long frq,long onTime)//frq Hz, onTime sec
          break;
          case I2CBuzzerFunOn:
            BuzzerOn(I2CSlaveData1[getI2CIndex]);
          break;
        }
      break;

      case I2CSMDLedRegister:
        switch(I2CSlaveFun[getI2CIndex])
        {
          case I2CSMDLedFunPWMOn:
            SMDLedPWMOn(I2CSlaveData1[getI2CIndex],I2CSlaveData2[getI2CIndex]);
          break;
          case I2CSMDLedFunOff:
            SMDLedOff();
          break;
          case I2CSMDLedFunOnTime:
            SMDLedOnTime(I2CSlaveData1[getI2CIndex],I2CSlaveData2[getI2CIndex]);
          break;
        }
      break;

      case I2CLeaserRegister:
        switch(I2CSlaveFun[getI2CIndex])
        {
          case I2CLeaserFunOn:
            LeaserOn(I2CSlaveData1[getI2CIndex]);
          break;
        }
      break;
    }
    getDatafromQueue();
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  char string[5],i;

  i=0;
  while(0 < Wire.available() || i < howMany) // loop through all but the last
  {
    string[i] = Wire.read();   // receive byte as a character    
    i++;
  }
  if(dugStatus==true)
  {  
    Debug.print("howMany:");
    Debug.println(howMany);
    Debug.print("string:");
    Debug.println(string);
  }
//save data
  if(checkI2CQueueFull())
      return;
  if(i>=1)
  {
    I2CSlaveRegisterData[putI2CIndex] = string[0];
    if(dugStatus==true)
    {
      Debug.print("I2CSlaveRegisterData:");
      Debug.println(I2CSlaveRegisterData[putI2CIndex]);
    }
  }  
  if(i>=2)
  {
    I2CSlaveFun[putI2CIndex] = string[1];
    if(dugStatus==true)
    {
      Debug.print("I2CSlaveFun:");
      Debug.println(I2CSlaveFun[putI2CIndex]);
    }
  }     
  if(i>=3)
  {
    I2CSlaveData1[putI2CIndex] = string[2];
    if(dugStatus==true)
    {    
      Debug.print("I2CSlaveData1:(HEX)");
      Debug.println(I2CSlaveData1[putI2CIndex],HEX);
    }
  }
  if(i>=4)
  {
    I2CSlaveData2[putI2CIndex] = string[3];
    if(dugStatus==true)
    {
      Debug.print("I2CSlaveData2:(HEX)");
      Debug.println(I2CSlaveData2[putI2CIndex],HEX);
    }
  }
  putDatatoQueue();
}
