/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <bcm2835.h>
#include <stdio.h>

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#define	I2C_Slave_Address 0x04
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
//#define	I2CWriter	/**< select I2C Write Mode */
#define	I2CWriterRead	/**< select I2C Write Mode */

#define	I2C_Length		8
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
#ifdef	I2CWriter
static char eeprom[I2C_Length] = {'1','2','3','4','5','6','7','8'};
#else      
static char eeprom[I2C_Length];
#endif
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
/**
*	\brief	main
*			Shows how to use I2C interface to transfer a byte to and from an SPI device.
*
*	\param	NONE
*	\return	bool paramter: Ture-> Initial fail, False-> Programming was ok.
*	\note	gcc -o i2c -I ../../src ../../src/bcm2835.c i2c.c
**/
int main(int argc, char **argv)
{
  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);
  int i=0,ret;

  if (!bcm2835_init())
    return 1;

#ifdef	I2CWriter  //Arduino - slave reciver
  bcm2835_i2c_begin();
  bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500);
  bcm2835_i2c_setSlaveAddress(I2C_Slave_Address);//Set I2C register Address
  while(i<=10)
  {
	printf("ret: %d \n",i); 
	bcm2835_i2c_write(eeprom, I2C_Length);//Write I2C Data
	sleep(1);
	i++;
  }
#endif
#ifdef	I2CWriterRead  //Arduino - slave sender
  bcm2835_i2c_begin();
  bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500);
  bcm2835_i2c_setSlaveAddress(I2C_Slave_Address);//Set I2C register Address
  bcm2835_i2c_read(eeprom, I2C_Length);//Write I2C Data
  for(i=0;i<I2C_Length;i++)
  	printf("%c \n",eeprom[i]);
#endif
  bcm2835_i2c_end();
  bcm2835_close();
  return 0;
}
/****************************************************************************/
/***							 END OF FILE                                                       ***/
/****************************************************************************/
