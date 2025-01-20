/*
 * DRV_I2C_Scan.h
 *
 *  Created on: NOV 4, 2024
 *      Author: MUDASSAR AHMED
 */

#ifndef INC_DRV_I2C_SCAN_H_
#define INC_DRV_I2C_SCAN_H_

/* Driver Included */
#include <DRV_LOG_uart.h>

/////* ---------------- [i2c Scanning Variables STARTs] ----------------------*/
uint8_t Buffer[25] = {0};
uint8_t Space[] = " - ";
uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
uint8_t EndMSG[] = "Done! \r\n\r\n";
HAL_StatusTypeDef ret = HAL_OK;
size_t size = 0;
/////* ----------------- [i2c Scanning Variables ENDs] -----------------------*/

/* API Usable in both Main Function and its While Loop */
inline void i2c_scan_api(I2C_HandleTypeDef& _i2c_, UART_HandleTypeDef& _uart_)
{
	HAL_UART_Transmit(&_uart_, StartMSG, sizeof(StartMSG), 100);
	for (uint8_t i = 0; i < 128; i++)
	{
		ret = HAL_I2C_IsDeviceReady(&_i2c_, (uint16_t) (i << 1), 3, 5);
		if (ret != HAL_OK) // No ACK Received At That Address
		{
			HAL_UART_Transmit(&_uart_, Space, sizeof(Space), 100);
		} else if (ret == HAL_OK) {
			size = sprintf((char*)Buffer, "0x%x", i);
			HAL_UART_Transmit(&_uart_, Buffer, size, 100);
		}
		//HAL_Delay(0);
	}
	HAL_UART_Transmit(&_uart_, EndMSG, sizeof(EndMSG), 100);
}



#endif /* INC_DRV_I2C_SCAN_H_ */
