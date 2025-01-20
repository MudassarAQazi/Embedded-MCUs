/*
 * Internal_RTC_Functionality.h
 *
 *  Created on: JUL 5, 2024
 *      Author: MUDASSAR AHMED
 */

#ifndef INC_API_Internal_RTC_Functionality_H_
#define INC_API_Internal_RTC_Functionality_H_

#include <API_Timer_milliseconds.h>
#include <API_Data_Buffers_Structures.h>
#include "main.h"
//#include "eeprom.h"
#include <time.h>
#include "stm32f0xx_hal.h"

RTC_HandleTypeDef RTC_t;
RTC_TimeTypeDef gTime;
RTC_DateTypeDef gDate;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

///*------- Suppress Warning of Unused Functions STARTs -------**/
//#define UNUSED(x) (void(x))
static uint32_t rtcTime2UnixTime(RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate) __attribute__((unused));
static HAL_StatusTypeDef unixTime2RtcTime(uint32_t& unixTime, RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate) __attribute__((unused));

///*^^^^^^^^ Suppress Warning of Unused Functions ENDs ^^^^^^^^**/
///
///
///
///*--------------------------------- [RTC Initialization Function STARTs] ----------------------------------*/
HAL_StatusTypeDef rtcInit(RTC_HandleTypeDef& RTC_ini)
{
	RTC_t			=	RTC_ini;
	return HAL_OK;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [RTC Initialization Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
///
///
///
///*---------------------------------- [RTC Communication Function STARTs] ----------------------------------*/
HAL_StatusTypeDef getRTCTime(RTC_DATA_t& rtcData_f)
{
	/// Read Time.
	status = HAL_RTC_GetTime(&RTC_t, &gTime, RTC_FORMAT_BIN);
	if(status != HAL_OK) return status;

	/// Read Date.
	status = HAL_RTC_GetDate(&RTC_t, &gDate, RTC_FORMAT_BIN);
	if(status != HAL_OK) return status;

	/// Update Time and Dates.
	rtcData_f.hour		=	gTime.Hours;
	rtcData_f.minute	=	gTime.Minutes;
	rtcData_f.second	=	gTime.Seconds;
	rtcData_f.date		=	gDate.Date;
	rtcData_f.weekday	=	gDate.WeekDay;
	rtcData_f.month		=	gDate.Month;
	rtcData_f.year		=	gDate.Year;
	return HAL_OK;
}

HAL_StatusTypeDef setRTCTime(RTC_DATA_t& rtcData_f)
{
	/// Update Time and Dates.
	sTime.Hours		=	rtcData_f.hour;
	sTime.Minutes	=	rtcData_f.minute;
	sTime.Seconds	=	rtcData_f.second;
	sDate.Date		=	rtcData_f.date;
	sDate.WeekDay	=	rtcData_f.weekday;
	sDate.Month		=	rtcData_f.month;
	sDate.Year		=	rtcData_f.year;

	/// Read Time.
	status = HAL_RTC_SetTime(&RTC_t, &sTime, RTC_FORMAT_BIN);
	if(status != HAL_OK) return status;

	/// Read Date.
	status = HAL_RTC_SetDate(&RTC_t, &sDate, RTC_FORMAT_BIN);
	if(status != HAL_OK) return status;

	return HAL_OK;
}

HAL_StatusTypeDef getUnixTime(uint32_t& unixTime_f, RTC_DATA_t& rtcData_f)
{
	time_t currentTime = {0};
	struct tm tim = {0};
	tim.tm_year = rtcData_f.year + 100;
	tim.tm_mon 	= rtcData_f.month - 1;
	tim.tm_mday = rtcData_f.date;
	tim.tm_hour = rtcData_f.hour;
	tim.tm_min	= rtcData_f.minute;
	tim.tm_sec	= rtcData_f.second;
	currentTime = mktime(&tim);

	unixTime_f	=	(uint32_t)currentTime;
	return HAL_OK;
}

HAL_StatusTypeDef getTimeFromEpoch(RTC_DATA_t& rtcData_f, uint32_t& unixTime_f)
{
	const time_t t	=	(const time_t)unixTime_f;
	struct tm tim	=	{0};
	tim 			= 	*localtime(&t);

	rtcData_f.year		=    tim.tm_year - 100;
	rtcData_f.month  	=    tim.tm_mon + 1;
	rtcData_f.date		=    tim.tm_mday;
	rtcData_f.hour		=    tim.tm_hour;
	rtcData_f.minute	=    tim.tm_min;
	rtcData_f.second	=    tim.tm_sec;

	return HAL_OK;
}

HAL_StatusTypeDef getRTCEpoch(uint32_t& epoch)
{
	getRTCTime(rtcdata);
	if(status != HAL_OK) return status;
	return getUnixTime(epoch, rtcdata);
}

/** Working */
static uint32_t rtcTime2UnixTime(RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate)
{
//	 uint16_t yr = (uint16_t)((rtcData_f->year));
	uint32_t currentTime	=	{0};
	struct tm tim	=	{0};
	tim.tm_year		=	(int)rDate.Year + 100;
	tim.tm_mon		=	(int)rDate.Month;
	tim.tm_mday		=	(int)rDate.Date;
	tim.tm_hour		=	(int)rTime.Hours;
	tim.tm_min		=	(int)rTime.Minutes;
	tim.tm_sec		=	(int)rTime.Seconds;
	currentTime		=	(uint32_t)mktime(&tim);

	#ifdef debugIntRTC
		char mesg[200] = {0};
		sprintf(mesg,
				"[DIAGNOSE][RTC][FUNCTION][rtcTime2UnixTime()]:\t ------- Before Conversion Time [%02d:%02d:%02d - %02d/%02d/%02d]\r\n",
				rTime.Hours,	rTime.Minutes,	rTime.Seconds,
				rDate.Date,		rDate.Month,	rDate.Year
		);	LOG(mesg);
		sprintf(mesg,
				"[DIAGNOSE][RTC][FUNCTION][rtcTime2UnixTime()]:\t ------- After Conversion Time [%02d:%02d:%02d - %02d/%02d/%02d]\t\t\t[%ld]\r\n",
				tim.tm_hour,	tim.tm_min,	tim.tm_sec,
				tim.tm_mday,	tim.tm_mon,	(tim.tm_year - 100), currentTime
		);	LOG(mesg);
	#endif
	return currentTime;
}

/** Working */
static HAL_StatusTypeDef unixTime2RtcTime(uint32_t& unixTime, RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate)
{
	const time_t t	=	(const time_t)unixTime;
	struct tm tim	=	{0};
	tim 			= *localtime(&t);
	rDate.Year    	= (uint8_t)tim.tm_year - 100;
	rDate.Month   	= (uint8_t)tim.tm_mon;
	rDate.Date    	= (uint8_t)tim.tm_mday;
	rTime.Hours    	= (uint8_t)tim.tm_hour;
	rTime.Minutes	= (uint8_t)tim.tm_min;
	rTime.Seconds	= (uint8_t)tim.tm_sec;

	#ifdef debugIntRTC
		char mesg[200] = {0};
		sprintf(mesg,
				"[DIAGNOSE][RTC][FUNCTION][unixTime2RtcTime()]:\t ------- Before Conversion Time [%02d:%02d:%02d - %02d/%02d/%02d]\r\n",
				tim.tm_hour,	tim.tm_min,	tim.tm_sec,
				tim.tm_mday,	tim.tm_mon,	(tim.tm_year - 100)
		);	LOG(mesg);

		sprintf(mesg,
				"[DIAGNOSE][RTC][FUNCTION][unixTime2RtcTime()]:\t ------- After Conversion Time [%02d:%02d:%02d - %02d/%02d/%02d]\r\n",
				rTime.Hours,	rTime.Minutes,	rTime.Seconds,
				rDate.Date,		rDate.Month,	rDate.Year
		);	LOG(mesg);
	#endif

	return HAL_OK;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [RTC Communications Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#endif /* Internal_RTC_Functionality_H */
