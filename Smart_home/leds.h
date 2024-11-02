#ifndef ECAL_LEDS_H_
#define ECAL_LEDS_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
// If negative logic comment the next line
#define Positive_logic
//Led id
typedef enum
{
	RED,GREEN,BLUE
}LED_ID;

#define LEDS_RED_PORT_ID                 PORTB_ID
#define LEDS_RED_PIN_ID                  PIN5_ID

#define LEDS_GREEN_PORT_ID               PORTB_ID
#define LEDS_GREEN_PIN_ID                PIN6_ID

#define LEDS_BLUE_PORT_ID                PORTB_ID
#define LEDS_BLUE_PIN_ID                 PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes all Leds (red, green, blue) pins direction.
   Turn off all the Leds
*/
void LEDS_init(void);

/*
 * Description :
 Turns on the specified LED.
*/
void LED_on(LED_ID id);

/*
 * Description :
 Turns off the specified LED.
*/
void LED_off(LED_ID id);

#endif /* ECAL_LEDS_H_ */
