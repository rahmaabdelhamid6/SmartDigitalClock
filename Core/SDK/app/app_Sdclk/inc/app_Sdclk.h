/*
 * app_Sdclk.h
 *
 *  Created on: Dec 27, 2022
 *      Author: Rahma
 */



#ifndef SDK_APP_APP_SDCLK_INC_APP_SDCLK_H_
#define SDK_APP_APP_SDCLK_INC_APP_SDCLK_H_

/*******************************************************************************
 *Definitions
 *******************************************************************************/
#define SENSOR_MAX_VOLT_VALUE     330
#define ADC_MAXIMUM_VALUE         4096
/*******************************************************************************
 *Extern Variables                                                                *
 *******************************************************************************/
extern volatile uint8_t g_ui8Tick;
/*******************************************************************************
 *Functions Prototypes
 *******************************************************************************/
uint8_t APP_CheckSum(uint8_t aui8buffer[], uint8_t ui8Size);
uint8_t APP_LM35_CalculateTemp(uint16_t ui8AdcValue );
void APP_SDCLK_Start(void);


#endif /* SDK_APP_APP_SDCLK_INC_APP_SDCLK_H_ */
