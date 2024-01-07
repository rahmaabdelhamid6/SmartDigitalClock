/*
 * hal_Lm35Sensor.h
 *
*\Created on: Dec 19, 2022
 *\Author: Rahma
 */

#ifndef SDK_HAL_HAL_LM35SENSOR_INC_HAL_LM35SENSOR_H_
#define SDK_HAL_HAL_LM35SENSOR_INC_HAL_LM35SENSOR_H_


/*******************************************************************************
 *Definitions
 *******************************************************************************/
#define SENSOR_CHANNEL_ID         5
/*******************************************************************************
 *Functions Prototypes
 *******************************************************************************/
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
void HAL_LM35_Init(ADC_HandleTypeDef *hadc1);
uint16_t HAL_LM35_GetAdcValue(ADC_HandleTypeDef *hadc1);

#endif /* SDK_HAL_HAL_LM35SENSOR_INC_HAL_LM35SENSOR_H_ */
