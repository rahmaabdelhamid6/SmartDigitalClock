/*
 * hal_Led.c
 *
 *  Created on: Dec 26, 2022
 *      Author: Rahma
 */
#include "stm32l4xx_hal.h"
#include "hal_LED.h"
/*******************************************************************************
 *Global Variables                                                             *
 *******************************************************************************/

/*******************************************************************************
 *Function definition                                                             *
 *******************************************************************************/
LedState_et HAL_LED_GetState(void)
{
	uint8_t ui8LEDStatus;
	ui8LEDStatus= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
	return ui8LEDStatus;
}
void HAL_LED_SetState(LedState_et etLEDState)
{
	if(etLEDState==LED_STATUS_ON)
	{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	}
	else if (etLEDState==LED_STATUS_OFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}
	else
	{
		/*do nothing*/
	}
}

