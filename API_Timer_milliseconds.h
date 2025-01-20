
#ifndef INC_API_Timer_milliseconds_H_
#define INC_API_Timer_milliseconds_H_
#include "stm32f0xx_hal.h"

class API_Timer_milliseconds{

public:
	bool completed(uint32_t& LastTime, const uint32_t& Duration);
	bool completed(uint32_t& LastTime, uint32_t& Duration, bool timerReset);
};
#endif
