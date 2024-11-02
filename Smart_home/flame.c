#include "flame.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initializes the flame sensor pin direction.
*/
void FlameSensor_init(void)
{
	//Initializes the flame sensor pin direction
	GPIO_setupPinDirection(FLAME_DATA_PORT_ID,FLAME_DATA_PIN_ID,PIN_INPUT);
}

/*
 * Description :
 * Reads the value from the flame sensor and returns it.
*/
uint8 FlameSensor_getValue(void)
{
	return GPIO_readPin(FLAME_DATA_PORT_ID,FLAME_DATA_PIN_ID);
}
