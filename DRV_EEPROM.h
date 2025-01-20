#ifndef DRV_EEPROM_H
#define DRV_EEPROM_H
//#include <string.h>
#include <stdio.h>
#include <stm32l0xx_hal.h>

#define MAX_DATAPOINT_LIMIT_EEPROM				50U		/* Max Limit of Data point storage*/
#define DATAPOINT_STORAGE_ALLOCATION_EEPROM		0x18U	/* 0x18 = 24	Storage Allocated per DATAPOINT */

#define MAC_ADDRESS_EEPROM_ADDR					0x00U	/* 0x00 = 0		Erase-able */
#define NODE_ADDRESS_EEPROM_ADDR				0x08U	/* 0x08 = 8		Erase-able */
#define NODE_INTERVAL_EEPROM_ADDR				0x0CU	/* 0x0C = 12	Erase-able */

#define TEMPERATURE_UP_LIMIT_ADDR				0x10U	/* 0x10 = 16	Erase-able */
#define TEMPERATURE_LOW_LIMIT_ADDR				0x14U	/* 0x14	= 20	Erase-able */
#define HUMIDITY_UP_LIMIT_ADDR					0x18U	/* 0x18 = 24	Erase-able */
#define HUMIDITY_LOW_LIMIT_ADDR					0x1CU	/* 0x1C = 28	Erase-able */

#define TOTAL_DATAPOINTS_STORED_EEPROM_ADDR		0x20U	/* 0x20 = 32	Erase-able	*/
#define CURRENT_DATAPOINT_EEPROM_ADDR			0x24U	/* 0x24 = 36	Erase-able*/
//#define LAST_DATAPOINT_EEPROM_ADDR			0x26U	/* 0x26 = 38		Attached with Above */
#define DATAPOINT_START_EEPROM_ADDR				0x28U	/* 0x18 = 40	Erase-able	*/

/*
 * (MAX_DATAPOINT_LIMIT_EEPROM 	x DATAPOINT_STORAGE_ALLOCATION_EEPROM + DATAPOINT_START_EEPROM_ADDR)
 * 		0x32 (50U)	x	0x18 (24U)	+	0x28 (40U)
*/
#define DATAPOINT_END_EEPROM_ADDR				0x4D8U	/* 0x4D8 = 1240	Erase-able	*/

const char*	EEPROM_WRITE_ERROR_STR			= 	"[EEPROM]%s: Write Error-%d!\n";
const char*	EEPROM_READ_ERROR_STR			=	"[EEPROM]%s: Read Error-%d!\n";
const char*	EEPROM_ERASE_ERROR_STR			=	"[EEPROM]%s: Erase Error-%d!\n";
const char* EEPROM_WRITE_OK_STR				=	"[EEPROM]%s: Write OK!\n";
const char* EEPROM_READ_OK_STR				=	"[EEPROM]%s: Read OK!\n";
const char* EEPROM_ERASE_OK_STR				=	"[EEPROM]%s: Erase OK!\n";

const char* EEPROM_MAC						=	"[MAC ADDRESS]";
const char* EEPROM_N_ADDRESS				=	"[NODE ADDRESS]";
const char* EEPROM_INTERVAL					=	"[INTERVAL]";
const char* EEPROM_TEMP_LIMIT				=	"[TEMP LIMIT]";
const char* EEPROM_HUMI_LIMIT				=	"[HUMI LIMIT]";
const char* EEPROM_DATAPOINT				=	"[DATAPOINT]";

//typedef struct     //--Data Structure for Storing DataPoint to EEPROM (12 Bytes to EEPROM).
//{
//    float		nodeTemperature;              	// 4 bytes data.
//    uint8_t		nodeHumidity;               // 1 bytes data.
//    uint8_t		nodeBatteryLevel;           // 1 byte data.
//    uint8_t		nodeRSSI;					// 1 byte for RSSI received on Node.
//	uint32_t	nodeEpoch;						// 4 bytes of Time and Date.
//}
//DATAPOINT_STRUCTURE_t;

typedef struct  {                               //--Data Structure for Transmitting Data (20 Bytes to RTL).  24 Bytes on STM32.
	uint64_t  nMAC;                      		// 4 byte data = 32 bit data ~4.3 Billion Devices Addresses.
	uint8_t   nADDR;                          	// 1 byte Address = 255 Number of Nodes with each HUB.
	int8_t    nRSSI;                          	// 1 byte for RSSI received on Node.
	float     nTEMP;                   			// 4 bytes data.
	uint8_t   nUMID;                     		// 1 bytes data.
	uint8_t   nBATLEV;                     		// 1 byte data.
	uint32_t  nEPOCH;                         	// 4 bytes of Time and Date.
} DATAPOINT_STRUCTURE_t;


/* Structure Object */
DATAPOINT_STRUCTURE_t DATAPOINT_WRITE_TO_EEPROM_o	=	{ 0 };
DATAPOINT_STRUCTURE_t DATAPOINT_READ_FROM_EEPROM_o	=	{ 0 };
HAL_StatusTypeDef status	=	HAL_ERROR;

HAL_StatusTypeDef EEPROM_ReadBytes(uint32_t address, uint8_t* dataBuf, size_t len);
HAL_StatusTypeDef EEPROM_WriteBytes(uint32_t address, uint8_t* dataBuf, size_t len);
HAL_StatusTypeDef EEPROM_Erase(uint32_t address, size_t len);

/*
 	Function to Write MAC Address to EEPROM
 	- *macAddr:	Pointer to 8-Bytes MAC Address Memory.
*/
HAL_StatusTypeDef Write_MAC_Address_EEPROM(uint64_t *macAddr, char* error) {
	uint8_t mac_Length			=	8; /* 8 Bytes */
	uint8_t inputMacAddress[8]	=	{ 0 };
	HAL_StatusTypeDef status	=	HAL_ERROR;

	/* Convert uint64_t to uint8_t Array */
	inputMacAddress[0]	=	(uint8_t)(*macAddr >> 56);
	inputMacAddress[1]	=	(uint8_t)(*macAddr >> 48);
	inputMacAddress[2]	=	(uint8_t)(*macAddr >> 40);
	inputMacAddress[3]	=	(uint8_t)(*macAddr >> 32);
	inputMacAddress[4]	=	(uint8_t)(*macAddr >> 24);
	inputMacAddress[5]	=	(uint8_t)(*macAddr >> 16);
	inputMacAddress[6]	=	(uint8_t)(*macAddr >> 8);
	inputMacAddress[7]	=	(uint8_t)(*macAddr >> 0);

	uint8_t storedMacAddress[8] =	{ 0 }; /* Temporary Variable to Avoid Unnecessary Erase Cycle */
	/* Read Previously Stored MAC Address from EEPROM */
	status = EEPROM_ReadBytes((uint32_t)MAC_ADDRESS_EEPROM_ADDR, storedMacAddress, mac_Length);	/* Read Already Stored MAC Address */
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_MAC,status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_MAC);

	/* Check for Match to Avoid a Write Cycle */
	if(
		(storedMacAddress[0] == inputMacAddress[0]) &&	//*(macAddr + 0x0)
		(storedMacAddress[1] == inputMacAddress[1]) &&    //*(macAddr + 0x1)
		(storedMacAddress[2] == inputMacAddress[2]) &&    //*(macAddr + 0x2)
		(storedMacAddress[3] == inputMacAddress[3]) &&    //*(macAddr + 0x3)
		(storedMacAddress[4] == inputMacAddress[4]) &&    //*(macAddr + 0x4)
		(storedMacAddress[5] == inputMacAddress[5]) &&    //*(macAddr + 0x5)
		(storedMacAddress[6] == inputMacAddress[6]) &&    //*(macAddr + 0x6)
		(storedMacAddress[7] == inputMacAddress[7])       //*(macAddr + 0x7)
	)
		return HAL_OK;
	else {
		/* Erase Previous Stored MAC Address from EEPROM */
		status = EEPROM_Erase(MAC_ADDRESS_EEPROM_ADDR, mac_Length/sizeof(int)); 	/* 1st Word (4-Bytes) of MAC Address */
		if(status != HAL_OK) {sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_MAC, status); return status;}	else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_MAC);

		/* Write New MAC Address to EEPROM */
		status = EEPROM_WriteBytes(MAC_ADDRESS_EEPROM_ADDR, inputMacAddress, mac_Length);
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_MAC, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_MAC);
	}
	return status;
}/* Write_MAC_Address_EEPROM */

/*
 	Function to Read MAC Address from EEPROM
 	- *macAddr:	Pointer to 8-Bytes MAC Address Memory.
*/
HAL_StatusTypeDef Read_MAC_Address_EEPROM(uint64_t* macAddr, char* error) {
	size_t macLength			=	8;		/* 8 Bytes */
	uint8_t outputMacAddress[8]	=	{ 0 };	/* 8 Bytes */
	/* Read MAC Address from EEPROM */
	status = EEPROM_ReadBytes(MAC_ADDRESS_EEPROM_ADDR, outputMacAddress, macLength);
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_MAC, status); 	else sprintf(error, EEPROM_READ_OK_STR, EEPROM_MAC);
	/* Update the input MAC Address Pointer */
	*macAddr	=	(	((uint64_t)outputMacAddress[0] << 56)	|
	          	  	 	((uint64_t)outputMacAddress[1] << 48)	|
						((uint64_t)outputMacAddress[2] << 40)	|
						((uint64_t)outputMacAddress[3] << 32)	|
						((uint64_t)outputMacAddress[4] << 24)	|
						((uint64_t)outputMacAddress[5] << 16)	|
						((uint64_t)outputMacAddress[6] << 8)	|
						((uint64_t)outputMacAddress[7] << 0)

	);
	return status;
} /* Read_MAC_Address_EEPROM */

/*
 	Function to Write Node Address to EEPROM
 	- *nodeAddr:	Pointer to 1-Byte of Node Address Memory.
*/
HAL_StatusTypeDef Write_Node_Address_EEPROM(uint8_t* nodeAddr, char* error) {
	uint8_t nodeAddrLength		=	1;	/* 1 Bytes */
	uint8_t storedNodeAddress	=	0;	/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	HAL_StatusTypeDef status	=	HAL_ERROR;

	/* Read Previously Stored Node Address form EEPROM */
	status = EEPROM_ReadBytes(NODE_ADDRESS_EEPROM_ADDR, &storedNodeAddress, nodeAddrLength);
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_N_ADDRESS, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_N_ADDRESS);

	/* Check for Match to Avoid a Write Cycle */
	if(storedNodeAddress == *nodeAddr)
		return HAL_OK;
	else {
		/* Erase Previously Stored Node Address from EEPROM */
		status = EEPROM_Erase((NODE_ADDRESS_EEPROM_ADDR/sizeof(int)), nodeAddrLength); 	/* Node Address Location */
		if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_N_ADDRESS, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_N_ADDRESS);
		/* Write New Node Address to EEPROM */
		status =  EEPROM_WriteBytes(NODE_ADDRESS_EEPROM_ADDR, nodeAddr, nodeAddrLength);
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_N_ADDRESS, status);	else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_N_ADDRESS);
	}
	return status;
}/* Write_Node_Address_EEPROM */

/*
 	Function to Read Node Address from EEPROM
 	- *nodeAddr:	Pointer to 1-Byte of Node Address Memory.
*/
HAL_StatusTypeDef Read_Node_Address_EEPROM(uint8_t* nodeAddr, char* error) {
	uint8_t nodeAddrLength	=	1; /* 1 Bytes */
	/* Read Node Address from EEPROM */
	status = EEPROM_ReadBytes(NODE_ADDRESS_EEPROM_ADDR, nodeAddr, nodeAddrLength);
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_N_ADDRESS, status);	else sprintf(error, EEPROM_READ_OK_STR, EEPROM_N_ADDRESS);
	return status;
}/* Read_Node_Address_EEPROM */

/*
 	Function to Write Node Interval to EEPROM
 	- *interval:	Pointer to 2-Byte of Node Interval Memory.
*/
HAL_StatusTypeDef Write_Node_Interval_EEPROM(uint16_t* interval, char* error) {
	uint8_t		intervalLength		=	2;			/* 2 Bytes */
//	uint16_t	Interval			=	*interval;
	uint8_t		inputInterval[2]	=	{ 0 };		/* uint16_t to uint8_t Array */
	uint8_t		storedInterval[2]	=	{ 0 };		/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	HAL_StatusTypeDef status		=	HAL_ERROR;

	/* Convert uint16_t to uint8_t Array */
	inputInterval[0] = (uint8_t)(*interval >> 8);	inputInterval[1] = (uint8_t)(*interval);

	/* Read New Node Data Update Interval to EEPROM */
	status = EEPROM_ReadBytes(NODE_INTERVAL_EEPROM_ADDR, storedInterval, intervalLength);
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_INTERVAL, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_INTERVAL);

	/* Check for Match to Avoid a Write Cycle */
	if(
		(storedInterval[0] == inputInterval[0]) &&
		(storedInterval[1] == inputInterval[1])
	)
		return HAL_OK;
	else {
		/* Erase Previously Stored Node Data Update Interval from EEPROM */
		status = EEPROM_Erase((NODE_INTERVAL_EEPROM_ADDR/sizeof(int)), sizeof(int)/sizeof(int)); 	/* Node Address Location */
		if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_INTERVAL, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_INTERVAL);
		/* Write New Node Data Update Interval to EEPROM */
		status =  EEPROM_WriteBytes(NODE_INTERVAL_EEPROM_ADDR, inputInterval, intervalLength);
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_INTERVAL, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_INTERVAL);
	}
	return status;
}/* Write_Node_Interval_EEPROM */

/*
 	Function to Read Node Interval from EEPROM
 	- *interval:	Pointer to 2-Byte of Node Interval Memory.
*/
HAL_StatusTypeDef Read_Node_Interval_EEPROM(uint16_t* interval, char* error) {
	uint8_t intervalLength 		=	2;		/* 2 Bytes */
	uint8_t outputInterval[2]	=	{ 0 };	/* Read array from EEPROM */
	/* Read Node Data Update Interval from EEPROM */
	status = EEPROM_ReadBytes(NODE_INTERVAL_EEPROM_ADDR, outputInterval, intervalLength);
	*interval	=	((uint16_t)outputInterval[0] << 8) | outputInterval[1];
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_INTERVAL, status); else sprintf(error, EEPROM_READ_OK_STR, EEPROM_INTERVAL);
	return status;
}/* Read_Node_Interval_EEPROM */

/*
 	Function to Write Temperature HIGH and LOW Limits to EEPROM
 	- *_high_limit_:	Pointer to 2-Byte of Node Temperature High Limit Memory.
 	- *_low_limit_:		Pointer to 2-Byte of Node Temperature High Limit  Memory.
 	- *error:			Pointer to error.
*/
HAL_StatusTypeDef Write_Temp_Limits_EEPROM(float* _high_limit_, float* _low_limit_, char* error) {
	/* Serialize the input Values */
	typedef union {	float value;	uint8_t stream[sizeof(float)];	}inputLimits_t;	/* float to uint8_t Array */
	inputLimits_t 		uLimit 			=	{ .value = *_high_limit_ };
	inputLimits_t 		dLimit 			=	{ .value = *_low_limit_ };

	/* Convert both uint16_t values to uint8_t Array */
	inputLimits_t		uStoredLimit	=	{ 0 };	/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	inputLimits_t		dStoredLimit	=	{ 0 };	/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	HAL_StatusTypeDef	status			=	HAL_ERROR;

	/* Read Limits from the EEPROM */
	status = EEPROM_ReadBytes(TEMPERATURE_UP_LIMIT_ADDR, uStoredLimit.stream, sizeof(inputLimits_t));
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_TEMP_LIMIT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_TEMP_LIMIT);
	status = EEPROM_ReadBytes(TEMPERATURE_LOW_LIMIT_ADDR, dStoredLimit.stream, sizeof(inputLimits_t));
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_TEMP_LIMIT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_TEMP_LIMIT);

	/* Check for Match to Avoid a Write Cycle */
	if(
		(uStoredLimit.value == uLimit.value) &&
		(dStoredLimit.value == dLimit.value)
	)
		return HAL_OK;
	else {
		/* Erase Previously Stored Limit from EEPROM */
		status = EEPROM_Erase((TEMPERATURE_UP_LIMIT_ADDR/sizeof(int)), 2*sizeof(int)/sizeof(int)); 	/* Erase both Temperature UP & DOWN Location Addresses */
		if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_TEMP_LIMIT, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_TEMP_LIMIT);
		/* Write New Limits in EEPROM */
		status =  EEPROM_WriteBytes(TEMPERATURE_UP_LIMIT_ADDR, uLimit.stream, sizeof(inputLimits_t));
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_TEMP_LIMIT, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_TEMP_LIMIT);
		/* Write New Limits in EEPROM */
		status =  EEPROM_WriteBytes(TEMPERATURE_LOW_LIMIT_ADDR, dLimit.stream, sizeof(inputLimits_t));
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_TEMP_LIMIT, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_TEMP_LIMIT);
	}
	return status;
}/* Write_Temp_Limits_EEPROM */

/*
 	Function to Read Temperature HIGH and LOW Limits to EEPROM
 	- *_high_limit_:	Pointer to 2-Byte of Node Temperature High Limit Memory.
 	- *_low_limit_:		Pointer to 2-Byte of Node Temperature High Limit  Memory.
 	- *error:			Pointer to error.
*/
HAL_StatusTypeDef Read_Temp_Limits_EEPROM(float* _up_limit_, float* _low_limit_, char* error) {
	typedef union {	float value;	uint8_t stream[sizeof(float)];	}outputLimits_t;	/* float to uint8_t Array */
	outputLimits_t 		uLimit 			=	{ 0 };
	outputLimits_t 		dLimit 			=	{ 0 };
	/* Read Limits from EEPROM */
	status = EEPROM_ReadBytes(TEMPERATURE_UP_LIMIT_ADDR, uLimit.stream, sizeof(outputLimits_t));
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_TEMP_LIMIT, status); else sprintf(error, EEPROM_READ_OK_STR, EEPROM_TEMP_LIMIT);
	status = EEPROM_ReadBytes(TEMPERATURE_LOW_LIMIT_ADDR, dLimit.stream, sizeof(outputLimits_t));
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_TEMP_LIMIT, status); else sprintf(error, EEPROM_READ_OK_STR, EEPROM_TEMP_LIMIT);
	/* Inflate the output Pointer */
	*_up_limit_		=	uLimit.value;
	*_low_limit_	=	dLimit.value;

	return status;
}/* Read_Temp_Limits_EEPROM */

/*
 	Function to Write Humidity HIGH and LOW Limits to EEPROM
 	- *_high_limit_:	Pointer to 2-Byte of Node Humidity High Limit Memory.
 	- *_low_limit_:		Pointer to 2-Byte of Node Humidity High Limit  Memory.
 	- *error:			Pointer to error.
*/
HAL_StatusTypeDef Write_Humi_Limits_EEPROM(float* _high_limit_, float* _low_limit_, char* error) {
	/* Serialize the input Values */
	typedef union {	float value;	uint8_t stream[sizeof(float)];	}inputLimits_t;	/* float to uint8_t Array */
	inputLimits_t 		uLimit 			=	{ .value = *_high_limit_ };
	inputLimits_t 		dLimit 			=	{ .value = *_low_limit_ };

	/* Convert both uint16_t values to uint8_t Array */
	inputLimits_t		uStoredLimit	=	{ 0 };	/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	inputLimits_t		dStoredLimit	=	{ 0 };	/* Temporary Variable to Avoid Unnecessary Erase Cycle */
	HAL_StatusTypeDef	status			=	HAL_ERROR;

	/* Read New Node Data Update Interval to EEPROM */
	status = EEPROM_ReadBytes(HUMIDITY_UP_LIMIT_ADDR, uStoredLimit.stream, sizeof(inputLimits_t));
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_HUMI_LIMIT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_HUMI_LIMIT);
	status = EEPROM_ReadBytes(HUMIDITY_LOW_LIMIT_ADDR, dStoredLimit.stream, sizeof(inputLimits_t));
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_HUMI_LIMIT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_HUMI_LIMIT);

	/* Check for Match to Avoid a Write Cycle */
	if(
		(uStoredLimit.value == uLimit.value) &&
		(dStoredLimit.value == dLimit.value)
	)
		return HAL_OK;
	else {
		/* Erase Previously Stored Limits from EEPROM */
		status = EEPROM_Erase((HUMIDITY_UP_LIMIT_ADDR/sizeof(int)), 2*sizeof(int)/sizeof(int)); 	/* Erase both Temperature UP & DOWN Location Addresses */
		if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_HUMI_LIMIT, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_HUMI_LIMIT);
		/* Write New Limits in EEPROM */
		status =  EEPROM_WriteBytes(HUMIDITY_UP_LIMIT_ADDR, uLimit.stream, sizeof(inputLimits_t));
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_HUMI_LIMIT, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_HUMI_LIMIT);
		/* Write New Limits in EEPROM */
		status =  EEPROM_WriteBytes(HUMIDITY_LOW_LIMIT_ADDR, dLimit.stream, sizeof(inputLimits_t));
		if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_HUMI_LIMIT, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_HUMI_LIMIT);
	}
	return status;
}/* Write_Humi_Limits_EEPROM */

/*
 	Function to Read Humidity HIGH and LOW Limits to EEPROM
 	- *_high_limit_:	Pointer to 2-Byte of Node Humidity High Limit Memory.
 	- *_low_limit_:		Pointer to 2-Byte of Node Humidity High Limit  Memory.
 	- *error:			Pointer to error.
*/
HAL_StatusTypeDef Read_Humi_Limits_EEPROM(float* _up_limit_, float* _low_limit_, char* error) {
	typedef union {	float value;	uint8_t stream[sizeof(float)];	}outputLimits_t;	/* float to uint8_t Array */
	outputLimits_t 		uLimit 			=	{ 0 };
	outputLimits_t 		dLimit 			=	{ 0 };
	/* Read Node Data Update Interval from EEPROM */
	status = EEPROM_ReadBytes(HUMIDITY_UP_LIMIT_ADDR, uLimit.stream, sizeof(outputLimits_t));
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_HUMI_LIMIT, status); else sprintf(error, EEPROM_READ_OK_STR, EEPROM_HUMI_LIMIT);
	status = EEPROM_ReadBytes(HUMIDITY_LOW_LIMIT_ADDR, dLimit.stream, sizeof(outputLimits_t));
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_HUMI_LIMIT, status); else sprintf(error, EEPROM_READ_OK_STR, EEPROM_HUMI_LIMIT);
	*_up_limit_		=	uLimit.value;
	*_low_limit_	=	dLimit.value;
	return status;
}/* Read_Humi_Limits_EEPROM */

/*
 	Function to Write Node DataPoint to EEPROM
 	- *data-point:	Pointer to 12-Byte of Node DataPoint Structure Memory.
*/
HAL_StatusTypeDef Write_DataPoint_EEPROM(char* error) {	//uint8_t* DATAPOINT
	//uint8_t 	datapoint_Length 					=	sizeof(DATAPOINT_STRUCTURE_t); /* ~12 Bytes */
	uint8_t 	current_Datapoint_Addr_Length		=	2;	/* 2 Bytes */
	uint8_t		total_datapoints_stored_Length		=	2;	/* 2 Byte */

	uint8_t 	current_datapoint_addr_value[2]		=	{ 0 };
	uint8_t		next_datapoint_addr_value[2]		=	{ 0 };
	uint8_t		total_datapoints_stored_value[2]	=	{ 0 };
	uint32_t 	current_datapoint_addr				=	0;
	uint32_t	next_datapoint_addr					=	0;
	uint32_t	total_datapoints_stored				=	0;
	HAL_StatusTypeDef status						=	HAL_ERROR;

	/* Read Current DataPoint Value from EEPROM */
	status = EEPROM_ReadBytes(CURRENT_DATAPOINT_EEPROM_ADDR, current_datapoint_addr_value, current_Datapoint_Addr_Length);
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_DATAPOINT);
	/* Read Total Numbers DataPoint Stored on EEPROM */
	status = EEPROM_ReadBytes(TOTAL_DATAPOINTS_STORED_EEPROM_ADDR, total_datapoints_stored_value, total_datapoints_stored_Length);
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_DATAPOINT);

	/* Convert the Array into the Single Variable */
	total_datapoints_stored =	((uint32_t)total_datapoints_stored_value[0] << 8)	| 	total_datapoints_stored_value[1];
	current_datapoint_addr	=	((uint32_t)current_datapoint_addr_value[0] << 8)	|	current_datapoint_addr_value[1];

	/* Total DataPoints Maximum Limit */
	if(total_datapoints_stored > MAX_DATAPOINT_LIMIT_EEPROM) total_datapoints_stored = MAX_DATAPOINT_LIMIT_EEPROM - 1;
	///
	///sprintf(error, "Stored Data Points: %ld",total_datapoints_stored); return status;

	/* Protection In case of Empty value from current_datapoint_addr */
	if((current_datapoint_addr < DATAPOINT_START_EEPROM_ADDR) || (current_datapoint_addr > DATAPOINT_END_EEPROM_ADDR))
		current_datapoint_addr	=	DATAPOINT_START_EEPROM_ADDR;

	/* Tries to Erase Previous DataPoint into the EEPROM */
	status = EEPROM_Erase((current_datapoint_addr/sizeof(int)), (sizeof(DATAPOINT_STRUCTURE_t)/sizeof(int)));
	//sprintf(error, "Address: %lx, Length: %x\r\n",current_datapoint_addr/sizeof(int), (sizeof(DATAPOINT_STRUCTURE_t)/sizeof(int))); if(status != HAL_OK) return status;
	if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_DATAPOINT);
	/* Tries to Write New DataPoint into the EEPROM */
	if(status	==	HAL_OK)
	{
		/* Writes DataPoint into EEPROM */
		status = EEPROM_WriteBytes(current_datapoint_addr, (uint8_t*)(&DATAPOINT_WRITE_TO_EEPROM_o), sizeof(DATAPOINT_STRUCTURE_t));
		if(status != HAL_OK) { sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_DATAPOINT);

		/* Checks for Next Available Space to Store DataPoint */
		if((current_datapoint_addr + sizeof(DATAPOINT_STRUCTURE_t)) <= DATAPOINT_END_EEPROM_ADDR)
		{
			if(total_datapoints_stored < MAX_DATAPOINT_LIMIT_EEPROM)
			{
				total_datapoints_stored		+=	1;
				next_datapoint_addr			=	DATAPOINT_START_EEPROM_ADDR + total_datapoints_stored * sizeof(DATAPOINT_STRUCTURE_t);
			}
			else
			{
				total_datapoints_stored		+=	1;
				next_datapoint_addr			=	current_datapoint_addr + sizeof(DATAPOINT_STRUCTURE_t);
			}
		}
		else
		{
			next_datapoint_addr		=	DATAPOINT_START_EEPROM_ADDR;
		}

		/* Convert Single Variable into an Array*/
		next_datapoint_addr_value[0]		=	(uint8_t)(next_datapoint_addr >> 8);		next_datapoint_addr_value[1]		=	(uint8_t)next_datapoint_addr;
		/* Erase previous DataPoint Address */
		status = EEPROM_Erase(CURRENT_DATAPOINT_EEPROM_ADDR/sizeof(int), sizeof(int)/sizeof(int));
		if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_DATAPOINT);
		/* Write New Data Point Address */
		status = EEPROM_WriteBytes(CURRENT_DATAPOINT_EEPROM_ADDR, next_datapoint_addr_value, current_Datapoint_Addr_Length);
		if(status != HAL_OK) return status;

		/* Check Total DataPoints Counting Limit */
		if(total_datapoints_stored <= MAX_DATAPOINT_LIMIT_EEPROM)
		{
			/* Convert Single Variable into an Array */
			total_datapoints_stored_value[0]	=	(uint8_t)(total_datapoints_stored >> 8);	total_datapoints_stored_value[1]	=	(uint8_t)total_datapoints_stored;
			/* Erase Previous Counting of DataPoints */
			status = EEPROM_Erase(TOTAL_DATAPOINTS_STORED_EEPROM_ADDR/sizeof(int), sizeof(int)/sizeof(int));
			if(status != HAL_OK) { sprintf(error, EEPROM_ERASE_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_DATAPOINT);
			/* Write New Counting of DataPoints */
			status = EEPROM_WriteBytes(TOTAL_DATAPOINTS_STORED_EEPROM_ADDR, total_datapoints_stored_value, total_datapoints_stored_Length);
			if(status != HAL_OK) sprintf(error, EEPROM_WRITE_ERROR_STR, EEPROM_DATAPOINT, status); else sprintf(error, EEPROM_WRITE_OK_STR, EEPROM_DATAPOINT);
		}
	}
	else return HAL_ERROR;

	return status;

}/* Write_Node_Interval_EEPROM */

/*
 	Function to Read Node DataPoint from EEPROM
 	- *data-point:	Pointer to 12-Byte of Node DataPoint Structure Memory.
*/
HAL_StatusTypeDef Read_DataPoint_EEPROM(char* error)	//uint8_t* datapoint
{
//	uint8_t datapoint_Length = sizeof(DATAPOINT_STRUCTURE_t); /* ~12 Bytes */
	uint8_t 	current_Datapoint_Addr_Length		=	2;	/* 2 Bytes */
	uint8_t 	current_datapoint_addr_value[2]		=	{ 0 };
	uint32_t 	current_datapoint_addr				=	0;

	/* Read Current DataPoint Address */
	status = EEPROM_ReadBytes(CURRENT_DATAPOINT_EEPROM_ADDR, current_datapoint_addr_value, current_Datapoint_Addr_Length);
	if(status != HAL_OK) { sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_DATAPOINT, status); return status;} else sprintf(error, EEPROM_READ_OK_STR, EEPROM_DATAPOINT);
	uint32_t calc_Address	=	((uint32_t)current_datapoint_addr_value[0] << 8)	|	current_datapoint_addr_value[1];
	if(	(calc_Address > (uint32_t)DATAPOINT_START_EEPROM_ADDR) &&
		(calc_Address < (uint32_t)DATAPOINT_END_EEPROM_ADDR)
	)
		current_datapoint_addr	=	calc_Address - sizeof(DATAPOINT_STRUCTURE_t);
	else
		current_datapoint_addr	=	(uint32_t)DATAPOINT_START_EEPROM_ADDR;

	/* Read DataPoint Structure that is Stored at Current DataPoint Address */
	status = EEPROM_ReadBytes(current_datapoint_addr, (uint8_t*)(&DATAPOINT_READ_FROM_EEPROM_o), sizeof(DATAPOINT_STRUCTURE_t));
	if(status != HAL_OK) sprintf(error, EEPROM_READ_ERROR_STR, EEPROM_DATAPOINT, status); else sprintf(error, EEPROM_ERASE_OK_STR, EEPROM_DATAPOINT);
	return status;
}/* Write_Node_Interval_EEPROM */


/* ZEESHAN CODE STARTS HERE */
HAL_StatusTypeDef EEPROM_ReadBytes(uint32_t address, uint8_t* dataBuf, size_t len)
{
    uint32_t start_addr = DATA_EEPROM_BASE + address;
    uint32_t end_addr = start_addr + len - 1;

	/* Memory overflowed error */
	if((end_addr) > DATA_EEPROM_END)  {
		return HAL_ERROR;     
	}

	/* Process Locked */
	__HAL_LOCK(&pFlash);

//	/* Unlock EEPROM access */
//	if(HAL_FLASHEx_DATAEEPROM_Unlock()!= HAL_OK) {
//		return HAL_ERROR;
//	}
	/*Check the parameter is OK */
	assert_param(IS_FLASH_DATA_ADDRESS(start_addr));

    /* Flash operation timeout FLASH_TIMEOUT_VALUE == 50s. Wait for last operation to complete if not there is timeout error */
	if (FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE) != HAL_OK){
		return HAL_ERROR;          
	}

	/* Clear Flash errors */
	pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

	/* Reading the Flash Data memory*/
	for (uint32_t i = 0; i <= (len-1); i++){
		dataBuf[i] = *(uint8_t *)(start_addr++);
	}

	if (FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE) != HAL_OK){
		return HAL_ERROR;          
	}

	/* Process Unlocked */
   __HAL_UNLOCK(&pFlash);

//   /* Lock EEPROM access */
//   	if(HAL_FLASHEx_DATAEEPROM_Lock()!= HAL_OK) {
//		return HAL_ERROR;
//	}

   return HAL_OK;
}

HAL_StatusTypeDef EEPROM_WriteBytes(uint32_t address, uint8_t* dataBuf, size_t len)
{
	uint32_t start_addr = DATA_EEPROM_BASE + address;
    uint32_t end_addr = start_addr + len - 1;

//    /* Memory Underflow Protection */
//    if(end_addr < DATA_EEPROM_BASE)
//    	end_addr = DATA_EEPROM_BASE;

    /* Memory overflowed error */
	if((end_addr) > DATA_EEPROM_END)  {
		return HAL_ERROR;     
	}
	/* Unlock EEPROM access */
	if(HAL_FLASHEx_DATAEEPROM_Unlock()!= HAL_OK) {
		return HAL_ERROR;   
	}
	for(uint32_t i=0; i<=(len-1); i++){
		if(HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, start_addr++, dataBuf[i]) != HAL_OK){
			return HAL_ERROR;
		}
	}
	/* Lock EEPROM access */
	if(HAL_FLASHEx_DATAEEPROM_Lock()!= HAL_OK) {
		return HAL_ERROR;   
	}
		
	return HAL_OK;
}

HAL_StatusTypeDef EEPROM_Erase(uint32_t address, size_t len)
{
	    uint32_t start_addr = DATA_EEPROM_BASE + (sizeof(int) * address);	//	(4 * address);
	    uint32_t end_addr = start_addr + sizeof(int) * (len-1);				//	4 * (len-1);
		if((end_addr) > DATA_EEPROM_END)  {
			return HAL_ERROR;
		}

		/* Unlock EEPROM access */
		if(HAL_FLASHEx_DATAEEPROM_Unlock()!= HAL_OK) {
			return HAL_ERROR;
		}
		for(uint32_t addr = start_addr; addr <= end_addr; addr += sizeof(int))
			if(HAL_FLASHEx_DATAEEPROM_Erase(addr) != HAL_OK){
				return HAL_ERROR;
		}
		/* Lock EEPROM access */
		if(HAL_FLASHEx_DATAEEPROM_Lock()!= HAL_OK) {
			return HAL_ERROR;
		}
		return HAL_OK;
}
/* ZEESHAN CODE ENDS HERE */

#endif/*DRV_EEPROM_H*/
