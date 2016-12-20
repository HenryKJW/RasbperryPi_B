/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <bcm2835.h>
#include <stdio.h>
#include "pwm.h"

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define PWM_Algorithm_Test 0
#define MS_Algorithm_Test  1

#define RunCode MS_Algorithm_Test


#define PIN RPI_GPIO_P1_12	/**< PWM output on RPi Plug P1 pin 12 (which is GPIO pin 18) in alt fun 5. */
#define PWM_CHANNEL 0		/**< it is controlled by PWM channel 0.*/

#if (RunCode==MS_Algorithm_Test)
#define RANGE 1024		/**< This controls the max range of the PWM signal.*/
#elif (RunCode==PWM_Algorithm_Test)
#define RANGE 8			/**< This controls the max range of the PWM signal.*/
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
	\brief	main

	Shows how to use PWM to control GPIO pins
	\param	NONE
	\return	bool: true=initial fail, false= programming is ok.
	\note	gcc -o pwm -I ../../src ../../src/bcm2835.c pwm.c
**/
int main(int argc, char **argv)
{
  if(!bcm2835_init())
    return 1;

//  printf("RunCode=%d, MS_Algorithm_Test=%d \n",RunCode,MS_Algorithm_Test);
  // Set the output pin to Alt Fun 5, to allow PWM channel 0 to be output there
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);

#if (RunCode==MS_Algorithm_Test)
  // 19.2MHz/1024/2 = 9375Hz, suitable for driving a DC motor with PWM
  bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_2);
  bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);//markspace 0:PWM alg, 1:M/S tran
#elif (RunCode==PWM_Algorithm_Test)
  bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_4);
  bcm2835_pwm_set_mode(PWM_CHANNEL, 0, 1);//markspace 0:PWM alg, 1:M/S tran
#endif
  bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

  // Vary the PWM m/s ratio between 1/RANGE and (RANGE-1)/RANGE
#if (RunCode==MS_Algorithm_Test)
  int direction = 1;
  int data = 1;
  while (1)
  {
    if (data == 1)
      direction = 1;
    else if (data == RANGE-1)
      direction = -1;
    data += direction;
    bcm2835_pwm_set_data(PWM_CHANNEL, data);
    bcm2835_delay(50);
  }
#elif (RunCode==PWM_Algorithm_Test)
  int data = 4;
  bcm2835_pwm_set_data(PWM_CHANNEL, data);
//  while (1)
  {
  	    bcm2835_delay(5000);
  }
#endif
  bcm2835_close();
  return 0;
}
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
