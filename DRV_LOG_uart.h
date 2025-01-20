/*
 * LOG_uart.h
 *
 *  Created on: OCT 1, 2024
 *      Author: MUDASSAR AHMED
 */

#ifndef INC_DRV_LOG_UART_H_
#define INC_DRV_LOG_UART_H_

#include <_Main_T2SV_V3_v2p3_.h>
#include <stdio.h>
#include "stm32f0xx_ll_usart.h"

//#define LL_Printf
//#define noColors

/* Header file for HAL UART to _write() Function used for PRINTF() */
#include  <errno.h>
#include  <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO

const char	err[]		=	"\33[31m";
const char	ok[]		=	"\33[32m";
const char	warn[]		=	"\33[33m";
const char	norm[]		=	"\33[0m";

#ifdef debug
	UART_HandleTypeDef LOGUart;
	void LOGInit(UART_HandleTypeDef& _uart_)
	{
		LOGUart = _uart_;
	}
	///*-------------------------------- [PRINTF UART Function STARTs] ----------------------------------*/
	#ifdef HAL_Printf
		int _write(int file, char *ptr, int len)
		{
//		   if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
//		   {
//			  errno = EBADF;
//			  return -1;
//		   }

		   /* Arbitrary Max Timeout is 250ms */
		   HAL_StatusTypeDef status =	HAL_UART_Transmit(&LOGUart, (uint8_t*)ptr, len, 250);

		   /* Returns Number of bytes written - as best can be told */
		   return (status == HAL_OK ? len : 0);
		}
	#endif
	#ifdef LL_Printf
		int _write(int file, uint8_t *buf, int nbytes)
		{
			uint8_t num_of_byte = 0;
	//		const USART_TypeDef* loguart = &LOGUart;
			while(num_of_byte <= (nbytes - 1))
			{
				//waiting until the Transmit Empty flag is set
				while(!LL_USART_IsActiveFlag_TXE((const USART_TypeDef*)&LOGUart));
				//send data byte by byte
				LL_USART_TransmitData8(USART2, buf[num_of_byte++]);
			}
			//Wait until the transmit complete Flag to be raised
			while (!LL_USART_IsActiveFlag_TC((const USART_TypeDef*)&LOGUart));
			return nbytes;
		}
	#endif
	///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [PRINTF UART Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	///*---------------------------------- [LOG UART Function STARTs] -----------------------------------*/
	void LOG(char* buffer, const char* errorColor = norm)
	{
		#ifndef noColors
			HAL_UART_Transmit(&LOGUart, (const uint8_t*)errorColor, strlen(errorColor), 10);
		#endif
		HAL_UART_Transmit(&LOGUart, (const uint8_t*)buffer, strlen(buffer), 1000);
		#ifndef noColors
			HAL_UART_Transmit(&LOGUart, (const uint8_t*)norm, strlen(norm), 10);
		#endif
		memset(buffer, 0, strlen(buffer));
	}
	///*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ [LOG UART Function ENDs] ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#endif /* debugUart */
#endif /* INC_DRV_LOG_UART_H_ */




