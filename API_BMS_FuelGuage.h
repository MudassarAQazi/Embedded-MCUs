/*
 * API_BMS_FuelGuage.h
 *
 *  Created on: MPV 2, 2024
 *      Author: MUDASSAR AHMED
 */

#ifndef INC_API_BMS_FUELGUAGE_H_
#define INC_API_BMS_FUELGUAGE_H_

#include <API_Timer_milliseconds.h>
#include <DRV_IP5306.h>
#include <API_Data_Buffers_Structures.h>
#include <DRV_Battery_State_of_Charge_Timers_Interrupts.h>
#include <API_LCD_Display.h>
#include <DRV_LOG_uart.h>

/* Object of Timer */
API_Timer_milliseconds timer;

/* Object of BMS IC */
IP5306 BMS;

uint32_t 	chargerDisconnectEpoch		=	0,
			chargerDisconnectDuration	=	300;

uint32_t	chargerConnectedEpoch		=	0,
			chargerConnectedDuration	=	chargerDisconnectDuration;

/* API Usable in Main Function */
inline void bms_fuelguage_ini_api(I2C_HandleTypeDef& _i2c_, TIM_HandleTypeDef& _timer_, uint32_t _channel_) {
	///HAL_Delay(100);
	BMS.begin(&_i2c_);

	/** LCD_MODEL_3 **/
	battLevelTimerInit(&_timer_, _channel_);

	/* Enable the Booster of BMS IC (Provide a LOW To HIGH Signal for 30ms to 2000ms default is 50ms) */
	/* No Need to provide LOW signal it is by default set to Low Level at start. HAL_GPIO_WritePin(BMS_Key_GPIO_Port, BMS_Key_Pin, GPIO_PIN_RESET); */
	HAL_Delay(50);
	HAL_GPIO_WritePin(BMS_Key_GPIO_Port, BMS_Key_Pin, GPIO_PIN_SET);
}

/* API Usable in Main Function While Loop */
inline void bms_fuelguage_api(uint32_t& _time_, uint32_t& _interval_) {
	if(!chargingInterlock_Flag && timer.completed(chargerConnectedEpoch, chargerConnectedDuration)) {
		if(BMS.isChargerConnected()) {
			post_data_buffer.hub_data.hub_bat_soc	=	BMS.getBatteryLevel();
			uint8_t chargedCellCounts = 	uint8_t((float)(post_data_buffer.hub_data.hub_bat_soc*7)/100);
			LCD.hubBatteryStatus(chargedCellCounts, SET);
			chargingInterlock_Flag	=	SET;

			/* Power Turn ON CO Sensor */
			HAL_GPIO_WritePin(PWR_CO_GPIO_Port, PWR_CO_Pin, GPIO_PIN_SET);
			/* Power Turn ON PM2.5 Sensor */
			HAL_GPIO_WritePin(PWR_PM2p5_GPIO_Port, PWR_PM2p5_Pin, GPIO_PIN_SET);
		}
	}
	else
	{
		if(timer.completed(_time_, _interval_))
		{
			post_data_buffer.hub_data.hub_bat_soc	=	BMS.getBatteryLevel();
			uint8_t chargedCellCounts = 	uint8_t((float)(post_data_buffer.hub_data.hub_bat_soc*7)/100);
			//lcd_print_hub_bat_status(chargedCellCounts);
			LCD.hubBatteryStatus(chargedCellCounts, chargingInterlock_Flag); //(chargingInterlock_Flag ? RESET : SET)

			#if defined(bmsDebug) || defined(batteryDebug)
				sprintf(
						msg,
						"[BATTERY][UNPLUGGED][Cells]: Cell Counts = %d\r\n",
						chargedCellCounts
				);	LOG(msg, norm);
			#endif/*debugBattery*/
		}

		/* Check for Charger Disconnected */
		if(		timer.completed(chargerDisconnectEpoch, chargerDisconnectDuration)
				&& chargingInterlock_Flag
				&& !BMS.isChargerConnected()
		)
		{
			/* Turn OFF power hungry sensors */
			if(post_data_buffer.hub_data.hub_bat_soc <= 20)
			{
				/* Power Turn OFF CO Sensor */
				HAL_GPIO_WritePin(PWR_CO_GPIO_Port, PWR_CO_Pin, GPIO_PIN_RESET);
				/* Power Turn OFF PM2.5 Sensor */
				HAL_GPIO_WritePin(PWR_PM2p5_GPIO_Port, PWR_PM2p5_Pin, GPIO_PIN_RESET);
			}
			//batteryTimerStop();
			chargingInterlock_Flag	=	RESET;
			#if defined(bmsDebug) || defined(batteryDebug)
				sprintf(
						msg,
						"[BATTERY][CHARGING][Timer]: Timer Stopped!!!\r\n"
				);	LOG(msg);
			#endif
		}
	}
}

#endif /* INC_API_BMS_FUELGUAGE_H_ */

/** OLD VERSION FOR LCD_MODEL_3 **/
///* API Usable in Main Function While Loop */
//inline void bms_fuelguage_api(uint32_t& _time_, uint32_t& _interval_)
//{
//	if(BMS.isChargerConnected())
//	{
//		if(batteryTimerCompleted)
//		{
//			uint8_t chargedCellCounts = 	uint8_t((float)(BMS.getBatteryLevel()*6)/100);
//			if(++cellCounts > 6) cellCounts = chargedCellCounts;
//
//			//lcd_print_hub_bat_status(cellCounts);
//			LCD.hubBatteryStatus(cellCounts);
//			#if defined(bmsDebug) || defined(batteryDebug)
//				sprintf(
//						msg,
//						"[BATTERY][CHARGING][Cells]: Cell Counts = %d\r\n",
//						cellCounts
//				);	LOG(msg, norm);
//			#endif
//			batteryTimerCompleted = RESET;
//		}
//		if(chargingInterlock_Flag)
//		{
//			batteryTimerStart();
//			chargingInterlock_Flag = RESET;
//
//			#if defined(bmsDebug) || defined(batteryDebug)
//				sprintf(
//						msg,
//						"[BATTERY][CHARGING][Timer]: Timer Started!!!!!!!!!!!\r\n"
//				);	LOG(msg, norm);
//			#endif /*debugBattery*/
//		}
//	}
//	else
//	{
//		if(timerCompleted(_time_, _interval_))
//		{
//			uint8_t chargedCellCounts = 	uint8_t((float)(BMS.getBatteryLevel()*6)/100);
//			//lcd_print_hub_bat_status(chargedCellCounts);
//			LCD.hubBatteryStatus(chargedCellCounts);
//
//			#if defined(bmsDebug) || defined(batteryDebug)
//				sprintf(
//						msg,
//						"[BATTERY][UNPLUGGED][Cells]: Cell Counts = %d\r\n",
//						chargedCellCounts
//				);	LOG(msg, norm);
//			#endif/*debugBattery*/
//		}
//
//		if(!chargingInterlock_Flag)
//		{
//			batteryTimerStop();
//			chargingInterlock_Flag	=	SET;
//			#if defined(bmsDebug) || defined(batteryDebug)
//				sprintf(
//						msg,
//						"[BATTERY][CHARGING][Timer]: Timer Stopped!!!\r\n"
//				);	LOG(msg);
//			#endif
//		}
//	}
//}
