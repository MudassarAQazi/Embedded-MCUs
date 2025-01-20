/*
 * Buttons_Functionality.h
 *
 *  Created on: JUL 3, 2024
 *      Author: MUDASSAR AHMED
 */
#ifndef INC_API_Buttons_LcdBacklit_Functionality_H_
#define INC_API_Buttons_LcdBacklit_Functionality_H_

#include <API_RF.h>
#include <API_Timer_milliseconds.h>
#include <DRV_CO_Led_Buzzer_Functionality.h>
#include <DRV_WIFI_RTL.h>
//#include "main.h"
//#include "stm32f0xx_hal.h"
//#include "eeprom.h"

/// LCD Back-Light LED Panel CTRL Signals Timing Variables. @ New
/* @ NEW
 * TIM1_CH1N is used for LCD Back-lit Timer
 * Timer Used contains Timing Variables as following:
 	 *	Pre-Scaler (PSC): 			10-1 	{Calculated using PSC	=	Input_APB_Timer_Clock / Output_Timer_Clock}		=	{48MHz / 4.8MHz}.
 	 *	Auto Reload Register (ARR):	1000-1	{Calculated using ARR	=	Output_Timer_Clock / Frequency}					=	{4.8MHz / 4.8kHz}.
 	 *	Pulse (CCRx):				550-1	{Calculated using CCrx	=	(Duty% x ARR)/ 100}.							=	{(550% x 1000) / 100}.
*/

/// LCD Back-Light LED Panel CTRL Signals Timing Variables. @ Old
/* @ OLD
 * TIM1_CH1N is used for LCD Back-lit Timer
 * Timer Used contains Timing Variables as following:
 	 *	Pre-Scaler (PSC): 			10-1 	{Calculated using PSC	=	Input_APB_Timer_Clock / Output_Timer_Clock}		=	{48MHz / 5MHz}.
 	 *	Auto Reload Register (ARR):	100-1	{Calculated using ARR	=	Output_Timer_Clock / Frequency}					=	{5MHz / 50kHz}.
 	 *	Pulse (CCRx):				30-1	{Calculated using CCrx	=	(Duty% x ARR)/ 100}.							=	{(30% x 2) / 100}.
*/

/// LCD ON-Time Duration Timing Variables.
// Long Button Press Timer.
/* TIM17_CH1 for LCD ON-Time Duration Timer.
 * Timer Used contains Timing Variables as following:
 	 *	Pre-Scaler (PSC): 			48000-1 {Calculated using PSC	=	Input_APB_Timer_Clock / Output_Timer_Clock}		=	{48MHz / 1kHz}.
 	 *	Auto Reload Register (ARR):	10000-1	{Calculated using ARR	=	Output_Timer_Clock / Frequency}					=	{1kHz / 0.1Hz}.
 	 *	Pulse (CCRx):				100-1	{Calculated using CCrx	=	(Duty% x ARR)/ 100}.							=	{0.1% -> 100% Duty = 1 -> 1000 Value}.
*/

TIM_HandleTypeDef *lcd_on_duration_t;
uint32_t lcd_on_duration_timerChannel_t;

TIM_HandleTypeDef *lcdBackLitTimer_t;
uint32_t lcdBackLitTimerChannel_t;

uint32_t	lcdBacklitTime			=	150;
uint32_t	lcdBacklitTime_Temp		=	0;
uint8_t		lcdBrightnessStates		=	0;
uint8_t 	lcdBtnPressCount		=	0;

bool lcdBtnInterlock	=	RESET;
bool longBtnPressStatus	=	RESET;
bool lcdBacklitStatus	=	RESET;

///*--------------------------------- [Buttons Control Initialization Function STARTs] ----------------------------------*/
HAL_StatusTypeDef buttonsTimerInit(TIM_HandleTypeDef& btnPressTimer, uint32_t btnPressTimerChannel)
{
	lcd_on_duration_t				=	&btnPressTimer;
	lcd_on_duration_timerChannel_t	=	btnPressTimerChannel;

	HAL_TIM_Base_Start_IT(lcd_on_duration_t);

	return HAL_OK;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [Buttons Control Initialization Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
///
///
///
///
///
///*--------------------------------- [Buttons Control Initialization Function STARTs] ----------------------------------*/
HAL_StatusTypeDef lcdTimerInit(TIM_HandleTypeDef& lcdBackLitTimer, uint32_t lcdBackLitTimerChannel)
{
	lcdBackLitTimer_t			=	&lcdBackLitTimer;
	lcdBackLitTimerChannel_t	=	lcdBackLitTimerChannel;

	/* Unlock the Flash Program Erase controller */
	//HAL_FLASH_Unlock();
	/* EEPROM Initialize */
	//EE_Init();
	///HAL_Delay(10000);

	/// LCD ON.
	HAL_TIM_Base_Start_IT(lcdBackLitTimer_t);
	lcdBackLitTimer_t->Instance->CCR1	=	lcdBacklitTime;				// Set LCD Brightness.
	HAL_TIMEx_PWMN_Start(lcdBackLitTimer_t, lcdBackLitTimerChannel_t);	// Timer for LCD Back-Light LED Control.
	lcdBacklitStatus	=	SET;

	/// Start LCD ON Duration Timer.
	lcd_on_duration_t->Instance->CNT	=	0;
	HAL_TIM_PWM_Start_IT(lcd_on_duration_t, lcd_on_duration_timerChannel_t);	// Start the Timer.
	return HAL_OK;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [Buttons Control Initialization Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
///
///
///
///
///
//////*----------------------------------------- [Buttons Function STARTs] --------------------------------------------*/
// Function to Update CO Led Status based on timer.
/**
 * @brief  Update CO LED based on Threshold Level.
 * @param  *coGasConcentrationValue: 	Pointer to the Variable that stores CO Gas Concentration Level.
 * @param  *pm2p5ConcentrationValue: 	Pointer to the Variable that stores Dust Particles Concentration Level.
 * @retval return:						Returns Status based on function execution.
 */
HAL_StatusTypeDef updateBrightnessLevel()
{
	return HAL_OK;
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [CO LED Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
///
///
///
///
///
///*----------------------------------- [Buttons Interrupt Service Routines STARTs] -----------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/// __________________LCD Back-Light LED Control Button Interrupt Callback.__________________
	/// Falling Edge(LCD Button).
	if ((GPIO_Pin == nLCD_Backlight_btn_Pin) && (!HAL_GPIO_ReadPin(nLCD_Backlight_btn_GPIO_Port, nLCD_Backlight_btn_Pin)) && (!lcdBtnInterlock))
	{
		lcdBtnInterlock		=	SET;	// Button Press Edges Inter-Locking.
		lcdBacklitStatus	=	SET;

		///HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_SET);
		//HAL_TIM_PWM_Start(buzzerTimer_t, buzzerTimerChannel);

		/// Start LCD ON Duration Timer.
		if(lcd_on_duration_t->State == HAL_TIM_STATE_BUSY) HAL_TIM_PWM_Stop_IT(lcd_on_duration_t, lcd_on_duration_timerChannel_t);	// Stop the Timer.
		lcd_on_duration_t->Instance->CNT	=	0;			// Set btnLongPressTimer_t Duration for 2 Seconds time.
		HAL_TIM_PWM_Start_IT(lcd_on_duration_t, lcd_on_duration_timerChannel_t);	// Start the Timer.

		//rtlState = DEVICE_MAC_CMD;
		//case_txrx_oper_interlock	=	RESET;
	}
	/// Rising Edge (LCD Button).
	else if ((GPIO_Pin == nLCD_Backlight_btn_Pin) && HAL_GPIO_ReadPin(nLCD_Backlight_btn_GPIO_Port, nLCD_Backlight_btn_Pin) && lcdBtnInterlock)
	{
		lcdBtnInterlock	=	RESET;
		///HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_RESET);
		//		HAL_TIM_PWM_Stop(buzzerTimer_t, buzzerTimerChannel);

		if (lcdBtnPressCount >= 1)
		{
			switch (lcdBrightnessStates) {
			case 0:
				lcdBacklitTime_Temp		=	150;
				lcdBrightnessStates 	=	1;
				break;
			case 1:
				lcdBacklitTime_Temp		=	550;
				lcdBrightnessStates 	=	2;
				break;
			default:
				lcdBacklitTime_Temp		=	850;
				lcdBrightnessStates 	=	0;
				break;
			}
			lcdBackLitTimer_t->Instance->CCR1	=	lcdBacklitTime_Temp;
		}
		else
		{
			lcdBackLitTimer_t->Instance->CCR1	=	lcdBacklitTime;
			HAL_TIMEx_PWMN_Start(lcdBackLitTimer_t, lcdBackLitTimerChannel_t);		// Timer for LCD Back-Light LED Control.

			lcdBtnPressCount++;
		}
	}
	/// __________________RF Module Configuration Control Button Interrupt Callback.__________________
	/// Falling Edge.
//	if ((GPIO_Pin == nRF_Config_btn_Pin) && (!HAL_GPIO_ReadPin(nRF_Config_btn_GPIO_Port, nRF_Config_btn_Pin)))
//	{
//		HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_SET);
//	}
//	/// Rising Edge
//	if ((GPIO_Pin == nRF_Config_btn_Pin) && HAL_GPIO_ReadPin(nRF_Config_btn_GPIO_Port, nRF_Config_btn_Pin))
//	{
//		HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_RESET);
//	}
	/// RF Chip Interrupt Triggered
	/// Rising Edge Check
	if(		(GPIO_Pin	== RF_nIRQ_Pin)
			&& /// Falling Edge Check
			(!HAL_GPIO_ReadPin(RF_nIRQ_GPIO_Port, RF_nIRQ_Pin)))
	{
		HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_SET);
		rfInterrupt_flag = SET;
	}
	/// Falling Edge Check
	if(		(GPIO_Pin	== RF_nIRQ_Pin)
			&& /// Rising Edge Check
			(HAL_GPIO_ReadPin(RF_nIRQ_GPIO_Port, RF_nIRQ_Pin)))
	{
		HAL_GPIO_WritePin(LED_RF_GPIO_Port, LED_RF_Pin, GPIO_PIN_RESET);
	}
	/// __________________HDC2080 Interrupt Callback.__________________
	/// Falling Edge.
	if(GPIO_Pin == DRDY_INT_Pin) // If The INT Source Is EXTI Line9 (A9 Pin)
	{
		tempHumidDataReady_flag = SET;
	}

	/// RF Configuration Button Interrupt Triggered
	/// Falling Edge Check
	if(	(GPIO_Pin	== nRF_Config_btn_Pin)
		&& /// Falling Edge Check
		(!HAL_GPIO_ReadPin(nRF_Config_btn_GPIO_Port, nRF_Config_btn_Pin))
	)
	{
		rfConfigBtn_PressingEdge();
	}
	/// Rising Edge Check
	else if(	(GPIO_Pin	== nRF_Config_btn_Pin)
		&& /// Falling Edge Check
		(HAL_GPIO_ReadPin(nRF_Config_btn_GPIO_Port, nRF_Config_btn_Pin))
	)
	{
		rfConfigBtn_ReleasingEdge();
	}


	/// WiFi Configuration Button Interrupt Triggered
	/// Falling Edge Check
	if(	(GPIO_Pin	== nWiFi_Config_btn_Pin)
		&& /// Falling Edge Check
		(!HAL_GPIO_ReadPin(nWiFi_Config_btn_GPIO_Port, nWiFi_Config_btn_Pin))
	)
	{
		wifiConfigBtn_PressingEdge();
	}
	/// Rising Edge Check
	else if(	(GPIO_Pin	== nWiFi_Config_btn_Pin)
		&& /// Falling Edge Check
		(HAL_GPIO_ReadPin(nWiFi_Config_btn_GPIO_Port, nWiFi_Config_btn_Pin))
	)
	{
		wifiConfigBtn_ReleasingEdge();
	}
}
///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [Buttons Interrupt Service Routines ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#endif /* Buttons_LcdBacklit_Functionality_H */
