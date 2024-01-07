/*
 * hal_Lm35Sensor.c
 *
*\Created on: Dec 19, 2022
 *\Author: Rahma
 */
#include "stm32l4xx_hal.h"
#include "hal_Lm35Sensor.h"

/*******************************************************************************
 *Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
void HAL_LM35_Init(ADC_HandleTypeDef *hadc1)
{

}
uint16_t HAL_LM35_GetAdcValue(ADC_HandleTypeDef *hadc1)
{
	uint16_t ui8AdcValue = 0;
	HAL_ADC_Start(hadc1);
	if(HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY)== HAL_OK)
	{
		/* Read ADC channel where the temperature sensor is connected */
		ui8AdcValue = HAL_ADC_GetValue(hadc1);
	}
	return ui8AdcValue;
}


