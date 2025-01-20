/*
 * API_Timer_milliseconds.cpp
 *
 *  Created on: DEC 30, 2024
 *      Author: MUDASSAR AHMED
 */

#include <API_Timer_milliseconds.h>
#include "stm32f0xx_hal.h"

///*------------------------------------------ [Timer STARTs] --------------------------------------------*/
// Timer for running timed based tasks.
/**
 * @brief  Reports Either the Assigned timer is Completed or Not.
 * @param  Time: Pointer to the variable that stores Last Function Accessed Time.
 * @param  Duration: Pointer to the Variable that stores timer overflow duration.
 * @retval True or False.
 */
bool API_Timer_milliseconds::completed(uint32_t& LastTime, const uint32_t& Duration)
{
	bool tick = 0;
	// Getting Time Stamp
	uint32_t TimeStamp_ms = HAL_GetTick();

	LastTime = (LastTime >= TimeStamp_ms)? (uint32_t)NULL:LastTime;
	// HearBeat
	if ((TimeStamp_ms - LastTime) >= Duration) {
		LastTime = TimeStamp_ms;
		tick = 1;
	}
	return tick;
}

/* Function Overloading */
bool API_Timer_milliseconds::completed(uint32_t& LastTime, uint32_t& Duration, bool timerReset)
{
	bool tick = 0;
	// Getting Time Stamp
	uint32_t TimeStamp_ms = HAL_GetTick();

	LastTime = (LastTime >= TimeStamp_ms)? (uint32_t)NULL:LastTime;
	// HearBeat
	if (((TimeStamp_ms - LastTime) >= Duration) || timerReset) {
		LastTime = TimeStamp_ms;
		tick = 1;
	}
	return tick;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [Timer ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/




