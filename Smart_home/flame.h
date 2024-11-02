#ifndef ECAL_FLAME_H_
#define ECAL_FLAME_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define FLAME_DATA_PORT_ID                 PORTD_ID
#define FLAME_DATA_PIN_ID                  PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes the flame sensor pin direction.
*/
void FlameSensor_init(void);

/*
 * Description :
 * Reads the value from the flame sensor and returns it.
*/
uint8 FlameSensor_getValue(void);

#endif /* ECAL_FLAME_H_ */
