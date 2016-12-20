/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <bcm2835.h>
#include <stdio.h>

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define	SPITransfer  /**< select SPI mode */
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
/**
*	\brief	main
*
*		Shows how to use SPI interface to transfer a byte to and from an SPI device.
*
*		Shows how to use SPI interface to transfer a number of bytes to and from an SPI device
*	\param	NONE
*	\return	bool paramter: Ture-> Initial fail, False-> Programming was ok.
*	\note	gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
**/
int main(int argc, char **argv)
{
  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);

  if (!bcm2835_init())
    return 1;

  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);	// The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);			// The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);	// The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// The default
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// the default

#ifdef SPITransfer
  // Send a byte to the slave and simultaneously read a byte back from the slave
  // If you tie MISO to MOSI, you should read back what was sent
  uint8_t data = bcm2835_spi_transfer(0x23);
  printf("Read from SPI: %02X\n", data);
#endif

#ifdef SPITransfern
  // Send a some bytes to the slave and simultaneously read
  // some bytes back from the slave
  // Most SPI devices expect one or 2 bytes of command, after which they will send back
  // some data. In such a case you will have the command bytes first in the buffer,
  // followed by as many 0 bytes as you expect returned data bytes. After the transfer, you
  // Can the read the reply bytes from the buffer.
  // If you tie MISO to MOSI, you should read back what was sent.
  char buf[] = { 0x01, 0x02, 0x11, 0x33 }; // Data to send
  bcm2835_spi_transfern(buf, sizeof(buf));

  // buf will now be filled with the data that was read from the slave
  printf("Read from SPI: %02X  %02X  %02X  %02X \n", buf[0], buf[1], buf[2], buf[3]);
#endif

  bcm2835_spi_end();
  bcm2835_close();
  return 0;
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/