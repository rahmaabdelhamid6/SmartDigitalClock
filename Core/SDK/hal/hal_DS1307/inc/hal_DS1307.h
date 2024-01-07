/*
 * hal_DS1307.h
 *
* \Created on: Dec 20, 2022
 * \ Author: Rahma
 */

#ifndef SDK_HAL_HAL_DS1307_INC_HAL_DS1307_H_
#define SDK_HAL_HAL_DS1307_INC_HAL_DS1307_H_

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/* I2C slave address for DS1307 */
#define DS1307_I2C_ADDR				0xD0
/* Registers location */
#define DS1307_SECONDS				0x00
#define DS1307_MINUTES				0x01
#define DS1307_HOURS				0x02
#define DS1307_DAY					0x03
#define DS1307_DATE					0x04
#define DS1307_MONTH				0x05
#define DS1307_YEAR					0x06
#define DS1307_CONTROL				0x07

/* Bits in control register */
#define DS1307_CONTROL_OUT			7
#define DS1307_CONTROL_SQWE			4
#define DS1307_CONTROL_RS1			1
#define DS1307_CONTROL_RS0			0
/*----------------------------------------------------------------------------*/

typedef struct
{
	uint8_t ui8Seconds;
	uint8_t ui8Minutes;
	uint8_t ui8Hour;
	uint8_t ui8Day;
	uint8_t ui8Date;
	uint8_t ui8Month;
	uint8_t ui8Year;
} DS1307_st;

/*******************************************************************************
 * Extern Variables
 *******************************************************************************/
extern DS1307_st g_stDS1307Time;
/*******************************************************************************
 * Functions Prototypes
 *******************************************************************************/
void HAL_DS1307_Init(I2C_HandleTypeDef *hi2c1);
uint8_t HAL_DS1307_ConvertdecToBcd(int32_t val);
int32_t HAL_DS1307_bcdToDec(uint8_t val);
void HAL_DS1307_SetClockHalt(I2C_HandleTypeDef *hi2c1,uint8_t halt);
uint8_t HAL_DS1307_GetClockHalt(I2C_HandleTypeDef *hi2c1);
void HAL_DS1307_SetRegByte(I2C_HandleTypeDef *hi2c1,uint8_t ui8RegAddr, uint8_t ui8Value);
uint8_t HAL_DS1307_GetRegByte(I2C_HandleTypeDef *hi2c1,uint8_t ui8RegAddr);
void HAL_DS1307_SetTime (I2C_HandleTypeDef *hi2c1, uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void HAL_DS1307_GetTime (I2C_HandleTypeDef *hi2c1, uint8_t ui8TimeOrDate);


#endif /* SDK_HAL_HAL_DS1307_INC_HAL_DS1307_H_ */
