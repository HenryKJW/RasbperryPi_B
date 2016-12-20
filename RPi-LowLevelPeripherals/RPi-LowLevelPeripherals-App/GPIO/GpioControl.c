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
#define GPIO_OUTPUT		/**< Select GPIO Function. */

#ifdef GPIO_OUTPUT
#define PIN RPI_GPIO_P1_11 	/**< Run GPIO Pin. */
#endif

#ifdef GPIO_INPUT_EDGE
#define PIN RPI_GPIO_P1_15 	/**< Run GPIO Pin. */
#endif

#ifdef GPIO_INPUT_GETLEVEL
#define PIN RPI_GPIO_P1_15 	/**< Run GPIO Pin. */
#endif
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
*	        GPIO.c a pin on an off every 0.5 secs
*	\param	NONE
*	\return	bool paramter: Ture-> Initial fail, False-> Programming was ok.
*	\note	gcc -o GpioControl.exe -I ../../src ../../src/bcm2835.c GpioControl.c
**/
int main(int argc, char **argv)
{
// If you call this, it will not actually access the GPIO
// Use for testing
// bcm2835_set_debug(1);

  if(!bcm2835_init())
    return 1;

#ifdef GPIO_OUTPUT
  // Set the pin to be an output
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

  // Blink
  while (1)
  {
    // Turn it on
    bcm2835_gpio_write(PIN, HIGH);
     
    // wait a bit
    bcm2835_delay(500);

    // turn it off
    bcm2835_gpio_write(PIN, LOW);

    // wait a bit
    bcm2835_delay(500);
  }
#endif

#ifdef GPIO_INPUT_EDGE
  // Set RPI pin P1-15 to be an input
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
  //  with a pullup
  bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
  // And a low detect enable
  bcm2835_gpio_len(PIN);

  while (1)
  {
    if (bcm2835_gpio_eds(PIN))
    {
      // Now clear the eds flag by setting it to 1
      bcm2835_gpio_set_eds(PIN);
      printf("low event detect for pin 15\n");
    }
    // wait a bit
    delay(500);
  }
#endif

#ifdef GPIO_INPUT_GETLEVEL
  // Set RPI pin P1-15 to be an input
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
  //  with a pullup
  bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);
  // Blink
  while (1)
  {
  	// Read some data
  	uint8_t value = bcm2835_gpio_lev(PIN);
  	printf("read from pin 15: %d\n", value);
  	// wait a bit
  	delay(500);
  }
#endif

bcm2835_close();
return 0;

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/