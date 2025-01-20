/*
 * DRV_INTERNAL_RTC.h
 *
 *  Created on: OCT 21, 2024
 *      Author: MUDASSAR AHMED
 */
#include "stm32l0xx_hal.h"
#include <time.h>
#include <DRV_LOG_uart.h>

/** Un-Comment Below Line to see Diagnosis Logs **/
//#define	debugIntRTC

#ifndef INC_DRV_INTERNAL_RTC_H_
#define INC_DRV_INTERNAL_RTC_H_

#define SECONDS_FROM_1970_TO_2000	946684800 ///< Unix time for 2000-01-01 00:00:00, useful for initialization

extern RTC_HandleTypeDef hrtc;

void getTime();
void setTime();
void adjustTimeDate(uint32_t unixTime);
void adjustTimeDate(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t weekday, uint8_t month, uint8_t date, uint8_t year);
void adjustTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
void adjustDate(uint8_t weekday, uint8_t month, uint8_t date, uint8_t year);
void setAlarm(uint32_t unixTime);
void setAlarm(uint32_t h, uint32_t m, uint32_t s);
//static HAL_StatusTypeDef rtcTime2UnixTime(RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate, uint32_t& unixTime);
static uint32_t rtcTime2UnixTime(RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate);
static HAL_StatusTypeDef unixTime2RtcTime(uint32_t& unixTime, RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate);

uint16_t date2days(uint16_t year, uint8_t month, uint8_t day);
uint32_t time2Seconds(uint16_t days, uint8_t h, uint8_t m, uint8_t s);
uint32_t dateTime2unixtime(RTC_TimeTypeDef& sTime, RTC_DateTypeDef& sDate);
void unixTime2DateTime(uint32_t& t, RTC_TimeTypeDef& sTime, RTC_DateTypeDef& sDate);

/** Working */
/* Initialize Time to the Start Date */
void initializeTime(){
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};
  sTime.Hours	= 00;
  sTime.Minutes = 00;
  sTime.Seconds = 00;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 1;
  DateToUpdate.Year = 24;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

/** Working */
/* SET TIME ON INTERNAL RTC IN UNIX FORMAT */
void setTime(uint32_t unixTime)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};
	unixTime2RtcTime(unixTime, sTime, sDate);
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}


/* SET TIME ON INTERNAL RTC IN SIMPLE FORMAT */
void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t weekday, uint8_t month, uint8_t date, uint8_t year)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};
	sTime.Hours	= hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	DateToUpdate.WeekDay = weekday;
	DateToUpdate.Month = month;
	DateToUpdate.Date = date;
	DateToUpdate.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* GET TIME FROM INTERNAL RTC IN UNIX FORMAT */
uint32_t nowDateTime()
{
	RTC_TimeTypeDef nTime = {0};
	RTC_DateTypeDef nDate = {0};
	HAL_RTC_GetTime(&hrtc, &nTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &nDate, RTC_FORMAT_BIN);
//	return dateTime2unixtime(&sTime, &sDate);
	uint32_t unixTime = rtcTime2UnixTime(nTime, nDate);
	#ifdef debugIntRTC
		char masg[200]	=	{ 0 };
		sprintf(masg,
				"[DIAGNOSE][RTC][FUNCTION][nowDateTime()]:\t ------- Before Conversion Time [%02d:%02d:%02d - %02d/%02d/%02d]\r\n",
				nTime.Hours,	nTime.Minutes,	nTime.Seconds,
				nDate.Date,		nDate.Month,	nDate.Year
		);	LOG(masg);
		sprintf(masg,
				"[DIAGNOSE][RTC][FUNCTION][nowDateTime()]:\t ------- After Conversion Unix Time: [%ld]\r\n", unixTime
		);	LOG(masg);
	#endif

	return unixTime;
}

/* GET TIME AND DATE FROM INTERNAL RTC IN SIMPLE FORMAT */
void nowDateTime(RTC_TimeTypeDef& sTime, RTC_DateTypeDef& sDate)
{
	HAL_RTC_GetTime(&hrtc, (RTC_TimeTypeDef*)&sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, (RTC_DateTypeDef*)&sDate, RTC_FORMAT_BIN);
}

/* ADJUST TIME IN UNIX FORMAT */
void adjustTimeDate(uint32_t unixTime)
{
	RTC_TimeTypeDef TimeToUpdate = {0};
	RTC_DateTypeDef DateToUpdate = {0};
	//unixTime2DateTime(&unixTime, &TimeToUpdate, &DateToUpdate);

	if (HAL_RTC_SetTime(&hrtc, &TimeToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* ADJUST TIME IN SIMPLE FORMAT */
void adjustTimeDate(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t weekday, uint8_t month, uint8_t date, uint8_t year)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};
	sTime.Hours	= hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	DateToUpdate.WeekDay = weekday;
	DateToUpdate.Month = month;
	DateToUpdate.Date = date;
	DateToUpdate.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* ADJUST TIME IN SIMPLE FORMAT */
void adjustTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	RTC_TimeTypeDef sTime = {0};
	sTime.Hours	= hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* ADJUST DATE IN SIMPLE FORMAT */
void adjustDate(uint8_t weekday, uint8_t month, uint8_t date, uint8_t year)
{
	RTC_DateTypeDef DateToUpdate = {0};
	DateToUpdate.WeekDay = weekday;
	DateToUpdate.Month = month;
	DateToUpdate.Date = date;
	DateToUpdate.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* SET ALARM ON INTERNAL RTC IN UNIX TIME FORMAT */
void setAlarm(uint32_t unixTime)
{
	char masg[200] = {0};
	RTC_DateTypeDef alarm_date;
	RTC_TimeTypeDef alarm_time;
	unixTime2RtcTime(unixTime, alarm_time, alarm_date);

	sprintf(masg,"[RTC][ALARM][TIME][NOW]:\t\t\t[%02d:%02d:%02d]\r\n",alarm_time.Hours, alarm_time.Minutes, alarm_time.Seconds);
	LOG(masg);
//	alarm_time.Seconds +=s;
//	alarm_time.Minutes +=m;
//	alarm_time.Hours +=h;
	if(alarm_time.Seconds >=60)
	{
		alarm_time.Minutes++;
		alarm_time.Seconds = 0;//alarm_time.Seconds - 60;
	}
	if(alarm_time.Minutes>=60)
	{
		alarm_time.Hours++;
		alarm_time.Minutes = 0;//alarm_time.Minutes - 60;
	}
	if(alarm_time.Hours >23)
		alarm_time.Hours = 0;

	RTC_AlarmTypeDef sAlarm = {0};
	sAlarm.AlarmTime.Hours = alarm_time.Hours;
	sAlarm.AlarmTime.Minutes = alarm_time.Minutes;
	sAlarm.AlarmTime.Seconds = alarm_time.Seconds;
	sAlarm.AlarmTime.SubSeconds = 0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = alarm_date.WeekDay;
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/* SET ALARM ON INTERNAL RTC IN SIMPLE TIME FORMAT */
void setAlarm(uint32_t h, uint32_t m, uint32_t s)
{
	char masg[200] = {0};
	RTC_TimeTypeDef alarm_time;
	RTC_DateTypeDef alarm_date;
	HAL_RTC_GetTime(&hrtc, &alarm_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &alarm_date, RTC_FORMAT_BIN);

	sprintf(masg,"[RTC][TIME][NOW]:\t\t\t[%02d:%02d:%02d]\r\n",alarm_time.Hours, alarm_time.Minutes, alarm_time.Seconds);
	//HAL_UART_Transmit(&huart1, (uint8_t*)time, si, 10);
	LOG(masg);
	alarm_time.Seconds +=s;
	alarm_time.Minutes +=m;
	alarm_time.Hours +=h;
	if(alarm_time.Seconds >=60)
	{
		alarm_time.Minutes++;
		alarm_time.Seconds = alarm_time.Seconds - 60;
	}
	if(alarm_time.Minutes>=60)
	{
		alarm_time.Hours++;
		alarm_time.Minutes = alarm_time.Minutes - 60;
	}
	if(alarm_time.Hours >23)
	{
		alarm_date.Date++;
		alarm_time.Hours = 0;
	}

	RTC_AlarmTypeDef sAlarm = {0};
	sAlarm.AlarmTime.Hours = alarm_time.Hours;
	sAlarm.AlarmTime.Minutes = alarm_time.Minutes;
	sAlarm.AlarmTime.Seconds = alarm_time.Seconds;
	sAlarm.AlarmTime.SubSeconds = 0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY; /* It will Mask Date and Weekday from changing. */
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = alarm_date.WeekDay;
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

/** Working */
//static HAL_StatusTypeDef rtcTime2UnixTime(RTC_TimeTypeDef& rTime, RTC_DateTypeDef& rDate, uint32_t& unixTime)
//{
////	 uint16_t yr = (uint16_t)((rtcData_f->year));
//	uint32_t currentTime	=	{0};
//	struct tm tim	=	{0};
//	tim.tm_year		=	(int)rDate.Year + 100;
//	tim.tm_mon 		=	(int)rDate.Month;
//	tim.tm_mday		=	(int)rDate.Date;
//	tim.tm_hour		=	(int)rTime.Hours;
//	tim.tm_min		=	(int)rTime.Minutes;
//	tim.tm_sec		=	(int)rTime.Seconds;
//	currentTime		=	(uint32_t)mktime(&tim);
//
//	unixTime		=	(uint32_t)currentTime;
//
//	return HAL_OK;
//}

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

/**-----------------------Working OLD-----------------------*/

void setTime()
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};
	sTime.Hours	= 15;
	sTime.Minutes = 51;
	sTime.Seconds = 00;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
	DateToUpdate.Month = RTC_MONTH_OCTOBER;
	DateToUpdate.Date = 16;
	DateToUpdate.Year = 24;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

  //HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 100);
}

char timee[30] = {0};
void alarmSetup(uint32_t h, uint32_t m, uint32_t s)
{
  RTC_TimeTypeDef alarm_time;
  HAL_RTC_GetTime (&hrtc, &alarm_time, RTC_FORMAT_BIN);
  int si = sprintf((char*)timee,"%02d:%02d:%02d\r\n",alarm_time.Hours, alarm_time.Minutes, alarm_time.Seconds);
  HAL_UART_Transmit(&huart1, (uint8_t*)timee, si, 100);
  alarm_time.Seconds +=s;
  alarm_time.Minutes +=m;
  alarm_time.Hours +=h;
  if(alarm_time.Seconds >=60){
    alarm_time.Minutes++;
    alarm_time.Seconds = alarm_time.Seconds - 60;
  }
  if(alarm_time.Minutes>=60){
    alarm_time.Hours++;
    alarm_time.Minutes = alarm_time.Minutes - 60;
  }
  if(alarm_time.Hours >23)
    alarm_time.Hours = 0;
  RTC_AlarmTypeDef sAlarm = {0};
  sAlarm.AlarmTime.Hours = alarm_time.Hours;
  sAlarm.AlarmTime.Minutes = alarm_time.Minutes;
  sAlarm.AlarmTime.Seconds = alarm_time.Seconds;
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}
/**-----------------------Working OLD-----------------------*/


/* NUMBER OF DAYS IN EACH MONTH */
const uint8_t daysInMonth[] = {31, 28, 31, 30, 31, 30,	31, 31, 30, 31, 30};

/* DATE TO DAYS CONVERTER FUNCTION */
uint16_t date2days(uint16_t year, uint8_t month, uint8_t day) {
  if (year >= 2000U)
    year -= 2000U;
  uint16_t days = day;
  for (uint8_t i = 1; i < month; ++i)
    days += *(daysInMonth + i - 1);
  if (month > 2 && year % 4 == 0)
    ++days;
  return days + 365 * year + (year + 3) / 4 - 1;
}

/* DAY AND TIME TO SECONDS CONVERTER */
uint32_t time2Seconds(uint16_t days, uint8_t h, uint8_t m, uint8_t s)
{
  return ((days * 24UL + h) * 60 + m) * 60 + s;
}

/* TIME AND DATE TO UNIX TIME CONVERTER */
uint32_t dateTime2unixtime(RTC_TimeTypeDef& sTime, RTC_DateTypeDef& sDate)
{
  uint32_t t	=	0;
  uint16_t days = date2days(sDate.Year, sDate.Month, sDate.Date);
  t	= time2Seconds(days, sTime.Hours, sTime.Minutes, sTime.Seconds);
  t += SECONDS_FROM_1970_TO_2000; // seconds from 1970 to 2000

  return t;
}

///* UNIX TIME TO DATE AND TIME CONVERTER */
void unixTime2DateTime(uint32_t& t, RTC_TimeTypeDef& sTime, RTC_DateTypeDef& sDate)
{
	t -= SECONDS_FROM_1970_TO_2000; // bring to 2000 timestamp from 1970

	sTime.Seconds = t % 60;	t /= 60;
	sTime.Minutes = t % 60;	t /= 60;
	sTime.Hours = t % 24;
	uint16_t days = t / 24;
	uint8_t leap;
	for (sDate.Year = 0;; ++sDate.Year) {
	leap = sDate.Year % 4 == 0;
	if (days < 365U + leap)
	  break;
	days -= 365 + leap;
	}
	for (sDate.Month = 1; sDate.Month < 12; ++sDate.Month) {
	uint8_t daysPerMonth = *(daysInMonth + sDate.Month - 1);
	if (leap && sDate.Month == 2)
	  ++daysPerMonth;
	if (days < daysPerMonth)
	  break;
	days -= daysPerMonth;
	}
	sDate.Date = days + 1;
}

#endif /* INC_DRV_INTERNAL_RTC_H_ */
