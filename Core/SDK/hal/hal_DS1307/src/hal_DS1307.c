/*
 * rtc.c
 *
 *  Created on: Dec 20, 2022
 *  Author: Rahma
 */

#include "stm32l4xx_hal.h"
#include "hal_DS1307.h"

/*******************************************************************************
 *Global Variables                               *
 *******************************************************************************/
DS1307_st g_stDS1307Time;
uint8_t g_aui8DS1307SetTime[7];
uint8_t g_aui8DS1307GetTime[7];
/*******************************************************************************
 *Functions Definitions                                  *
 *******************************************************************************/
/* intialization Ds1307 RTC module*/
void HAL_DS1307_Init(I2C_HandleTypeDef *hi2c1)
{
	HAL_DS1307_SetClockHalt(hi2c1,0);
}
/* Convert normal decimal numbers to binary coded decimal*/
uint8_t HAL_DS1307_decToBcd(int32_t val)
{
	return (uint8_t)( (val/10*16) + (val%10) );
}
/* Convert binary coded decimal to normal decimal numbers*/
int32_t HAL_DS1307_bcdToDec(uint8_t val)
{
	return (int)( (val/16*10) + (val%16) );
}
/* function to set clock halt*/
void HAL_DS1307_SetClockHalt(I2C_HandleTypeDef *hi2c1,uint8_t halt)
{
	uint8_t ch = (halt ? 1 << 7 : 0);
	HAL_DS1307_SetRegByte(hi2c1,DS1307_SECONDS, ch | (HAL_DS1307_GetRegByte(hi2c1,DS1307_SECONDS) & 0x7f));
	//HAL_Ds1307_SetRegByte(hi2c1,DS1307_HOURS, 0 | (HAL_Ds1307_GetClockHalt(hi2c1,DS1307_HOURS) & 0xBf));
}

/* function to get clock halt*/
uint8_t HAL_DS1307_GetClockHalt(I2C_HandleTypeDef *hi2c1)
{
	return ((HAL_DS1307_GetRegByte(hi2c1,DS1307_SECONDS) & 0x80) >> 7);
}
/* function to set reg byte*/
void HAL_DS1307_SetRegByte(I2C_HandleTypeDef *hi2c1,uint8_t ui8RegAddr, uint8_t ui8Value)
{
	uint8_t aui8bytes[2] = { ui8RegAddr, ui8Value };
	HAL_I2C_Master_Transmit(hi2c1, DS1307_I2C_ADDR, aui8bytes, 2, HAL_MAX_DELAY);
}
/* function to get reg byte*/
uint8_t HAL_DS1307_GetRegByte(I2C_HandleTypeDef *hi2c1,uint8_t ui8RegAddr)
{
	uint8_t ui8Value;
	HAL_I2C_Master_Transmit(hi2c1, DS1307_I2C_ADDR, &ui8RegAddr, 1,HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(hi2c1, DS1307_I2C_ADDR , &ui8Value, 1, HAL_MAX_DELAY);
	return ui8Value;
}
/* function to set time */
void HAL_DS1307_SetTime (I2C_HandleTypeDef *hi2c1, uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{

	g_aui8DS1307SetTime[0] = HAL_DS1307_decToBcd(sec);
	g_aui8DS1307SetTime[1] = HAL_DS1307_decToBcd(min);
	g_aui8DS1307SetTime[2] = HAL_DS1307_decToBcd(hour);
	g_aui8DS1307SetTime[3] = HAL_DS1307_decToBcd(day);
	g_aui8DS1307SetTime[4] = HAL_DS1307_decToBcd(date);
	g_aui8DS1307SetTime[5] = HAL_DS1307_decToBcd(month);
	g_aui8DS1307SetTime[6] = HAL_DS1307_decToBcd(year);

	HAL_I2C_Mem_Write(hi2c1, DS1307_I2C_ADDR, DS1307_SECONDS, 1, g_aui8DS1307SetTime, 7,HAL_MAX_DELAY);
}
void HAL_DS1307_GetTime (I2C_HandleTypeDef *hi2c1, uint8_t ui8TimeOrDate)
{

	HAL_I2C_Mem_Read(hi2c1, DS1307_I2C_ADDR, DS1307_SECONDS, 1, g_aui8DS1307GetTime, 7, HAL_MAX_DELAY);
	if(ui8TimeOrDate==1)
	{
		g_stDS1307Time.ui8Seconds = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[2]);
		g_stDS1307Time.ui8Minutes = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[1]);
		g_stDS1307Time.ui8Hour = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[0]);
	}
	else
	{
		g_stDS1307Time.ui8Day= HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[3]);
		g_stDS1307Time.ui8Date = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[4]);
		g_stDS1307Time.ui8Month = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[5]);
		g_stDS1307Time.ui8Year = HAL_DS1307_bcdToDec(g_aui8DS1307GetTime[6]);
	}
}

