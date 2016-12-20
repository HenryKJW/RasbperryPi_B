#!/usr/bin/python
#I2CSlaveAddress 0x14
#I2CBuzzerRegister '0'
#		I2CBuzzerFunPassiveOn	'0'  //['0', '0', frq, time]
#		I2CBuzzerFunOn				'1'  //['0', '1', 100ms]
#I2CSMDLedRegister '1'
#		I2CSMDLedFunPWMOn     '0' //-['1', '0', (R=0,G=1,B=2),PWM]
#		I2CSMDLedFunOff       '1' //-['1', '1']
#		I2CSMDLedFunOnTime    '2' //-['1', '2', (R=0,G=1,B=2),100ms]
#I2CLeaserRegister '2'
#		I2CLeaserFunOn		'0' //-['2', '0', [0-Off, 1-On]]
import smbus,time

bus = smbus.SMBus(1)    #0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

DEVICE_ADDRESS = 0x14   #7 bit address (will be left shifted to add the read write bit)

#Write a single register
#bus.write_byte_data(DEVICE_ADDRESS, DEVICE_REG_MODE1, 0x80)


def BuzzerOn(onTime):			#onTime - 100ms
    DEVICE_REG = 0x30
    BuzzerFunOn_values = [0x31, onTime]
    bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG, BuzzerFunOn_values)
    time.sleep(1);
		
def LedOn(LedRGB,LedPWM):	#LedRGB-(R=0,G=1,B=2)  ,LedPWM-0~255
    DEVICE_REG = 0x31
    LedFunOn_values = [0x30,LedRGB,LedPWM]
    bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG, LedFunOn_values)
    time.sleep(0.1);

def LedOff():
    DEVICE_REG = 0x31
    LedFunOn_values = [0x31]
    bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG, LedFunOn_values)
    time.sleep(0.1);

def LeaserOn(status):	#status- 1=On, 2=Off
    DEVICE_REG = 0x32
    LeaserOn_values = [0x30, status]
    bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG, LeaserOn_values)
    time.sleep(0.1);

if __name__ == "__main__":
    try:
        while True :
            print "BuzzerOn"
            BuzzerOn(2)
            time.sleep(2)
            print "LEDOn"
            LedOn(0,55)
            time.sleep(2)
            LedOff()
            time.sleep(0.1)
            LedOn(1,55)
            time.sleep(2)
            LedOff()
            time.sleep(0.1)
            LedOn(2,55)
            time.sleep(2)
            LedOff()
            time.sleep(0.1)
            print "LeaserOn"
            LeaserOn(1)
            time.sleep(4)
            LeaserOn(0)
        
    except KeyboardInterrupt:
        print "Exception: KeyboardInterrupt"
        LedOff()
        LeaserOn(0)

