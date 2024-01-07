/*
 * app.c
 *Created on: Dec 27, 2022
 * Author: Rahma
 */
#include "stm32l4xx_hal.h"
#include "app_Sdclk.h"
#include "main.h"
#include "hal_DS1307.h"
#include "hal_LED.h"
/*******************************************************************************
 * Global Variable                                                              *
 ********************************************************************************/
uint16_t g_ui8AdcValue;
uint8_t g_ui8TempValue ;
volatile uint8_t g_ui8Tick;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
/*******************************************************************************
 *Functions Definition                                                         *
 *******************************************************************************/
uint8_t APP_CheckSum(uint8_t aui8buffer[], uint8_t ui8Size)
{
	uint8_t ui8Sum= 0;
	for(uint8_t i=1; i<ui8Size-1; i++)
	{
		ui8Sum=ui8Sum+ aui8buffer[i];
	}
	if (ui8Sum== aui8buffer[ui8Size-1])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
uint8_t APP_LM35_CalculateTemp(uint16_t ui8AdcValue )
{
	uint8_t ui8TempValue=0;
	ui8TempValue=(uint8_t)(((uint32_t)ui8AdcValue*SENSOR_MAX_VOLT_VALUE)/ADC_MAXIMUM_VALUE);
	return ui8TempValue;
}
void APP_SDCLK_Start(void)
{

	static uint8_t ui8Flag=0;
	if(g_ui8Tick==1 && ui8Flag==0)
	{
		HAL_DS1307_GetTime (&hi2c1,1);
		HAL_UART_Transmit(&huart2, &g_stDS1307Time.ui8Seconds, 3, HAL_MAX_DELAY);/* transmit time*/
		HAL_LED_SetState(LED_STATUS_ON);
		HAL_Delay(200);
		HAL_LED_SetState(LED_STATUS_OFF);
		HAL_Delay(200);
		ui8Flag=1;
	}
	else if(g_ui8Tick==2 && ui8Flag==1)
	{
		HAL_DS1307_GetTime (&hi2c1,0);
		HAL_UART_Transmit(&huart2, &g_stDS1307Time.ui8Day, 4, HAL_MAX_DELAY); /*transmit date*/
		ui8Flag=2;
	}
	else if(g_ui8Tick==3 && ui8Flag==2)
	{
		g_ui8AdcValue = HAL_LM35_GetAdcValue(&hadc1);
		g_ui8TempValue = APP_LM35_CalculateTemp(g_ui8AdcValue );
		HAL_UART_Transmit(&huart2,&g_ui8TempValue, 1, HAL_MAX_DELAY);/*transmit temp*/

		g_ui8Tick=0;
		ui8Flag=0;
	}
	else
	{
		/*Do nothing*/
	}
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
