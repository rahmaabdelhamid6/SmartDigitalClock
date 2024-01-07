/*
 * hal_LED.h
 *
*  Created on: Dec 26, 2022
 *      Author: Rahma
 */

#ifndef SDK_HAL_HAL_LED_INC_HAL_LED_H_
#define SDK_HAL_HAL_LED_INC_HAL_LED_H_

/*******************************************************************************
 *Definition
 *******************************************************************************/
typedef enum {
	LED_STATUS_OFF,
	LED_STATUS_ON
}LedState_et;
/*******************************************************************************
 *Functions Prototypes
 *******************************************************************************/
LedState_et HAL_LED_GetState(void);
void HAL_LED_SetState(LedState_et etLedState);



#endif /* SDK_HAL_HAL_LED_INC_HAL_LED_H_ */
