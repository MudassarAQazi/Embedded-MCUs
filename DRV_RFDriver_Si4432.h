/*
 * RFDriver_Si4432.h
 *
 *  Created on: MAY 16, 2024
 *      Author: MUDASSAR AHMED
 */
/**
*   This RF driver covers All the functionality of the SI4432 RF Module
*   connected with STM32 MCU.
*/
#include "stm32f0xx_hal.h"

#ifdef debug
#include <stdio.h>  // For s_print_f function
#include "string.h"	// For string manipulation
#endif

#ifndef RFDriver_Si4432_H
#define RFDriver_Si4432_H

//#define noDelay

class RFDriver_Si4432 {

public:

	/// Variables
	uint32_t	MAX_TRANSMIT_TIMEOUT	=	2000;
	/// Interrupts Type Definition
	enum interrupt_t
	{
		INT_RX_CRC_ERROR			=	0x0001,
		INT_RX_VALID_PACKET			=	0x0002,
		INT_TX_PACKET_SENT			=	0x0004,
		INT_EXTERNAL				=	0x0008,
		INT_RX_FIFO_ALMOST_FUL		=	0x0010,
		INT_TX_FIFO_ALMOST_EMPTY	=	0x0020,
		INT_TX_FIFO_ALMOST_FUL		=	0x0040,
		INT_FIFO_ERROR				=	0x0080,
		INT_POWER_ON_RESET			=	0x0100,
		INT_CHIP_READY				=	0x0200,
		INT_LOW_BATTERY_DETECT		=	0x0400,
		INT_WAKE_UP_TIMER			=	0x0800,
		INT_RSSI_HIGH				=	0x1000,
		INT_INVALID_PREAMBLE_DET	=	0x2000,
		INT_VALID_PREAMBLE_DET		=	0x4000,
		INT_SYNC_WORD_DET			=	0x8000,
		INT_ALL						=	0xFFFF
	};

	/// Operating Mode Type Definition
	enum opMode_t
	{
		STANDBY		=	0x00,
		IDLE_READY	=	0x01,
		TUNE		=	0x02,
		RX			=	0x04,
		TX			=	0x08,
		XTAL32		=	0x10,
		SLEEP		=	0x20,
		SENSOR		=	0x40,
		Soft_Reset	=	0x80
	};

	/// Modulation Type Definitions
	enum modulation_t
	{
		UNMODULATED,
		OOK,
		FSK,
		GFSK
	};

	/// CRC Polynomials Type Definition.
	enum crcPolynomial_t
	{
		CCIT,
		CRC_16_IBM,
		IEC_16,
		BIACHEVA
	};

	/// RF Interrupts Status Holding Register.
	uint16_t 		interruptStatus			=	0;

	/// Parametric Constructor.
	HAL_StatusTypeDef RFDriver_begin(	SPI_HandleTypeDef*	hspi,
										GPIO_TypeDef* 		nselport,	uint16_t	nselpin,
										GPIO_TypeDef*		sdnport,	uint16_t	sdnpin,
										GPIO_TypeDef*		nirqport,	uint16_t	nirqpin);

	//Constructor Overloading.
	/// Parametric Constructor.
	HAL_StatusTypeDef RFDriver_begin(	SPI_HandleTypeDef*	hspi,
										GPIO_TypeDef* 		nselport,	uint16_t	nselpin,
										//GPIO_TypeDef*		sdnport,	uint16_t	sdnpin,
										GPIO_TypeDef*		nirqport,	uint16_t	nirqpin);

	///-1-
	/*
		@brief:		Function to Read Device Type.
		@input:
					-	*type:	Variable to get device Type.
					Expected Type.
					->	EZRadioPRO: 01000.
		@output:	Status
	*/
	HAL_StatusTypeDef getDeviceType(uint8_t* type);

	///-2-
	/*
		@brief:		Function to Read Device Version.
		@input
					-	*version:	Variable to get device Version.
					Expected Versions.
					->	Si4430/31/32 REV B1: 00110.
					->	Si100x REV C, Si101x REV A, Si102x/3x REV A: 00110.
					->	Si100x REV E, Si101x REV B: Si102x/3x REV B: 00111.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef getDeviceVersion(uint8_t* version);

	///-3-
	/*
		@brief:		Function to Read Device Status.
		@input:		none.
		@output:
					-	*deviceStatus:	Variable to get device Status.
					Expected Status.
					->	FIFO Overflow both TX/RX.
					->	FIFO Underflow both TX/RX.
					->	FIFO Empty RX only.
					->	Header Error.
					->	Frequency Error.
					->	Chip Power State.
						->	00: Idle State.
						->	01:	RX State.
						->	10:	TX State.
		@return:	status.
	*/
	HAL_StatusTypeDef getDeviceStatus(uint8_t* deviceStatus);

	///-4-
	/*
		@brief:		Function to Read Interrupts Status.
		@input:		none.
		@output:
					-	*interrupt:	Interrupts vector Table.
					** Note: This function gets triggered when "nIRQ" pin transition from HIGH to LOW.
		@return:	status.
	*/
	HAL_StatusTypeDef readAndClearInterrupts(uint16_t* interrupts);

	///-5-
	HAL_StatusTypeDef readAndClearInterrupts();

	///-6-
	/*
		@brief:		Function to Set Interrupts.
		@input:
					-	setInterruptValue:	Interrupts vector Table.
					** Note: This function sets triggers of "nIRQ" pin transition from HIGH to LOW.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setInterrupts(uint16_t setInterruptValue);

	///-6-
//	HAL_StatusTypeDef clearInterrupts();

	///-7-
	HAL_StatusTypeDef resetInterrupts();

	///-8-
	/*
	 	 @brief:	Function to Shutdown the Module using SDN pin.
	 	 @input:
					 -	sdnEn:	Shutdown Enable | Disable (true | false).
					 **Note:	"RF_SDN" Must be defined in the main program to use this function.
								Otherwise it will return "HAL_ERROR".
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef shutdown(bool sdnEn);

	///-9-
	/*
		@brief:		Function to Set Operating Mode.
		@input:
					-	mode:	Variable to Set Operating Mode.
					Expected Modes.
					->	Idle Mode.
						 ->	 Standby Mode.
						 ->	 Sleep Mode.
						 ->	 Sensor Mode (Low Battery Detect | Temperature Sensor).
						 ->	 Idle Ready Mode (Default).
						 ->	 Tune Mode.
					->	TX State.
					->	RX State.
					-
					 ** Shutdown can be achieved by using SDN Pin Only.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setOperatingMode(uint8_t mode); /* opMode_t */

	///-10-
	/*
		@brief:		Function to set Frequency of the RF Module.
		@input:
					-	*Frequency (in MHz): 240.00 MHz -> 960.00 MHz.
					-	frequencyOffset(in KHz):
					-	channel (Multiples of StepSize)	:	0 -> 255	 => ( 0 -> 2.56MHz if stepSize is 1 ).
					-	stepSize (Multiples of 10kHz)	:	0 -> 255	 =>	( 0 -> 2.56MHz).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setFrequency(float frequency, float frequencyOffset, uint8_t channel, uint8_t stepSize);

	///-11-
	/*
		@brief:		Function to set Frequency Hopping Channel of the RF Module.
		@input:
					-	channel (Multiples of StepSize)	:	0 -> 255	 => ( 0 -> 2.56MHz if stepSize is 1 ).
					-	stepSize (Multiples of 10kHz)	:	0 -> 255	 =>	( 0 -> 2.56MHz)
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setFrequencyHoppingChannel(uint8_t channel, uint8_t stepSize);

	///-12-
		/*
			@brief:		Function to Read Frequency Setting from the RF Module.
			@input:		none.
			@output:
						-	channel (Multiples of StepSize)	:	0 -> 255	 => ( 0 -> 2.56MHz if stepSize is 1 ).
						-	stepSize (Multiples of 10kHz)	:	0 -> 255	 =>	( 0 -> 2.56MHz)
			@return:	status.
		*/
	HAL_StatusTypeDef readFrequencySettings(float* frequency, float* frequencyOffsetValue);

	///-13-
	/*
		@brief:		Function to Set TX Data Rate.
		@input:
					-	*txDataRate:	Data Rate (in KBPS) 0.123 -> 256.
					**Note: In case of MANCHESTER Encoding Data rate is Limited to 128k.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setTxDataRate(uint32_t txDataRate);

	///-14-
	/*
		@brief:		Function to Set Modulation Type.
		@input:
					-	Modulation Type (OOK, FSK, GFSK).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setModulationType(modulation_t modulation);

	///-15-
	/*
		@brief:		Function to Set Modulation Type
		@input:
					-	modulation:		Modulation Type (OOK, FSK, GFSK).
					-	freqDeviation:	Frequency Deviation (625 Hz -> 320'000 Hz).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setFrequencyParametersSettings(modulation_t modulation, uint32_t freqDeviation);

	///-16-
	/*
		@brief:		Function to Set Modulation Type.
		@input:
					-	TX Power Options for.
						-	SI4432:			+1,	+2,	+5,	+8,	+11, +14, +17, +20.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setTxPower(uint8_t txPower);

	///-17-
	/*
		@brief:		Function to Set Encoding.
		@input:
					-	dataWhiteningEn:		Data Whitening Enable|Disable (true|false).
					-	manchEncodingEn:		MANCHESTER Encoding Enable|Disable (true|false).
					-	manchEncInvEn:			Inversion of MANCHESTER Encoding Enable|Disable (true|false).
					-	manPreamblePolarity:	Pre-amble Polarity of MANCHESTER Encoding Set|Reset (true|false).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setEncoding(
			bool dataWhiteningEn, bool manchEncodingEn,
			bool manchInvEn, bool manchPreambPolarity);

	///-18-
	/*
		@brief:		Function to Set Data Access Control like CRC, Enable TX/RX Packet Handling, LSB First & etc.
		@input:
					-	crcEn:					CRC Cyclic Redundancy Check Enable | Disable (true | false).
					-	crcDataOnlyEn:			CRC on Data Bytes only Enable | Disable (true | false).
					-	crcPolySlct:			CRC Polynomials Selection from type definition of crcPolynomial_t.
					-	txPackHandleEn:			TX Packet Handling Enable | Disable (true | false).
					-	txPackHandleEn:			RX Packet Handling Enable | Disable (true | false).
					-	lsbFirstEn:				LSB Least Significant Bit First Enable | Disable (true | false).
					-	skip2ndPhPreambDet:		Skip 2nd Phase of Pre-amble Detection Set | Reset (true | false).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setDataAccessControl(
			bool crcEn, bool crcDataOnlyEn, crcPolynomial_t crcPolySlct,
			bool txPackHandleEn, bool rxPackHandleEn, bool lsbFirstEn, bool skip2ndPhPreambDet);

	///-19-
	/*
		@brief:		Function to Set Pre-amble Length (Must be used on Transmitting End).
		@input:
					-	preambLength:		Pre-amble Length (1 -> 511 Nibbles).
					-	preambThresh:		Pre-amble Detection Threshold (1 -> 15 Nibbles).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setPreamble(uint16_t preambLength, uint8_t preambThresh);

	///-20-
	/*
		@brief:		Function to Set Synchronization Word.
		@input:
					-	syncWord:	Synchronization Word (usually 1 -> 4 bytes).
					-	size:		Size of Synch Word.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setSyncWord(uint8_t* syncWord, size_t size);

	///-21-
	/*
		@brief:		Function to Set Transmit Header Word.
		@input:
					-	*txHeader:	Header Word (usually 1 -> 4 bytes).
					-	size:		Size of Synch Word.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setTxHeader(uint8_t* txHeader, size_t size);

	///-22-
	/*
		@brief:		Function to set Received Header Check Word.
		@input:
					-	*rxHeader:	Receive Header Check Word (usually 1 -> 4 bytes)
					-	size:		Size of Synch Word.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setRxCheckHeader(uint8_t* rxCheckHeader, size_t size);

	///-23-
	/*
		@brief:		Function to get Received Header Word.
		@input:		none.
		@output:
					-	*rxHeader:	Synchronization Word (usually 1 -> 4 bytes).
					-	size:		Size of Synch Word.
		@return:	status.
	*/
	HAL_StatusTypeDef getRxHeader(uint8_t* receivedHeader, size_t size);

	///-24-
	/*
		 @brief:	Function to Enable/Disable Low Battery Mode.
		 @input:
					 -	lowBattThresh:	Input Low Battery Threshold Level (0% -> 100%) Means (1.7V -> 3.2599V) Volts.
					 -	interruptEnable:	Input Interrupt Enable (true/false).
					 ** Note: To use this function Enable Sensor Mode using operatingMode Function.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setLowBatteryLevel(uint8_t lowBattThresh, bool interruptEnable);

	///-25-
	/*
		 @brief:	Function to Enable/Disable Low Battery Mode.
		 @input:	none.
		 @output:
		 	 	 	 -	*batteryVoltLevel:	Output Battery Voltage Level (1.7 -> 3.25) Volts.
		 @return:	status.
	*/
	HAL_StatusTypeDef getBatteryLevel(uint8_t* batteryVoltLevel);

	///-26-
	/*
		@brief:		Function to Set Encoding.
		@input:
					-	*time:		Wake-up Time after (in Milliseconds).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setWakeupTimer(uint8_t* time);

	///-27-
	/*
		@brief:		Function to Set Encoding.
		@input:
					-	*dutyCycle:		Low Power On Time Duty (in Milliseconds).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setLowDutyCycleMode(uint8_t* dutyCycle);

	/// GPIO Configuration. Antenna Diversity.

	///-28-
	/*
		@brief:		Function to Set Minimum RSSI Threshold.
		@input:
					-	rssiThresh:		RSSI Threshold for indication of Low Signals Level (in dB).
					**Note:	Check the status of iRSSI in Interrupt/Status 2 Register.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setRssiThresh(const uint8_t rssiThresh);

	///-29-
	/*
		@brief:		Function to Set Minimum RSSI Threshold.
		@input:
					-	rssiOffset:		Offset value to RSSI Calculation (1 -> 7) => (+4dB -> 28dB).
					**Note:	Check the status of iRSSI in Interrupt/Status 2 Register.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef setRssiOffset(const uint8_t rssiOffset);

	///-30-
	/*
		@brief:		Function to Get RSSI Value.
		@input:
					-	*rssiValue:		RSSI Threshold for indication of Low Signals Level (in dB).
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef getRSSI(int8_t* rssiValue);

	///-30-
	/*
		@brief:		Function to Read Received Data from the RF Module.
		@input:		none.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef startListening();

//	///-31-
//	/*
//		Function to Check, does the Data Packet Received.
//		-
//		-
//	*/
//	uint8_t isDataPacketReceived();
//
//	///-32-
//	/*
//		Function to Send Data from the RF Module.
//		-	*data:		Data to Write on the Transmit Registers.
//		-	size:		Size of the TX Data.
//	*/
//	uint8_t sendDataPacket(uint8_t* data, uint8_t size, bool waitForAckResponse, uint32_t responseTimeout, uint8_t* responseBuffer, uint8_t* responseSize);
//
//	uint8_t sendDataPacket(uint8_t* data, uint8_t size);
//
//	///-33-
//	uint8_t waitForAckPacket(uint32_t waitingTime);

	///-31-
	/*
		@brief:		Function to Check, does the Data Packet Received.
		@input:		none.
		@output:	none.
		@return:	status.
	 */
	bool isDataPacketReceived();

	///-32-
	/*
		@brief:		Function to Send Data from the RF Module.
		@input:
						-	*data:				Data to Write on the Transmit Registers.
						-	size:				Size of the TX Data.
						-	waitForAckResponse:	Enable Wait.
						-	responseTimeout:	Provide Timeout in milliseconds.
		@output:
						-	*responseBuffer:	Response/received data Buffer pointer.
						-	*responseSize:		Response/received buffer size pointer.
		@return:	status.
	 */
	bool sendDataPacket(uint8_t* data, uint8_t size, bool waitForAckResponse, uint32_t responseTimeout, uint8_t* responseBuffer, uint8_t* responseSize);

	/*
		@brief:		Function to Send Data from the RF Module.
		@input:
							-	*data:		Data to Write on the Transmit Registers.
							-	size:		Size of the TX Data.
		@output:	none.
		@return:	status.
	 */
	bool sendDataPacket(uint8_t* data, uint8_t size);

	///-33-
	/*
		@brief:		Function to Wait for Acknowledgment packet.
		@input:
						-	waitingTime:		Waiting Time in milliseconds.
		@output:	none.
		@return:	status.
	 */
	bool waitForAckPacket(uint32_t waitingTime);

	///-32-
	/*
		@brief:		Function to Get Received Data from the RF Module.
		@input:		none.
		@output:
					-	*data:		Data to Read from the Received Registers.
					-	size:		Size of the RX Data.
		@return:	status.
	*/
	HAL_StatusTypeDef getReceivedDataPacket(uint8_t* data, uint8_t* size);

	///-33-
	HAL_StatusTypeDef clearTxFIFO();

	///-34-
	HAL_StatusTypeDef clearRxFIFO();

	///-35-
	HAL_StatusTypeDef clearFIFOs();

	///-36-
	HAL_StatusTypeDef softReset();

	///-37-
	HAL_StatusTypeDef hardReset();

	///-38-
	HAL_StatusTypeDef reloadConfigurations();

	///-39-
	/*
		@brief:		Function to Read Module Setting from the RF Module.
		@input:		none.
		@output:
					-	*settings: Acquire Setting from the RF Module.
		@return:	status.
	*/
	HAL_StatusTypeDef readSettings(uint8_t* settings);

	///-40-
	/*
			@brief:		Function to Read Settings from the RF module through SPI.
			@input:		-	size:		size of the output array.
			@output:
						-	*settings:	Acquire Setting from the RF Module.
			@return:	status.
		*/
	HAL_StatusTypeDef readRegisters(uint8_t* registers, uint8_t size);

	///-45-
	double power(float x, int y);
private:

	SPI_HandleTypeDef	*rf_spi;

	GPIO_TypeDef		*nSelPort;
	uint16_t			nSelPin	=	0;

	GPIO_TypeDef		*sdnPort;
	uint16_t			sdnPin	=	0;

	GPIO_TypeDef		*nIrqPort;
	uint16_t			nIrqPin	=	0;

	/// Addresses of Data Register
	uint8_t			deviceTypeRegAddr		=	0x00,
					intrEn1RegAddr			=	0x05,
					intrEn2RegAddr			=	0x06,
					opFuncCtrlReg1Addr		=	0x07,
					opFuncCtrlReg2Addr		=	0x08,
					dataAcsCtrlRegAddr		=	0x30,
					headerCtrl1RegAddr		=	0x32,
					headerCtrl2RegAddr		=	0x33,
					moduloModeCtrl1RegAddr	=	0x70,
					moduloModeCtrl2RegAddr	=	0x71,
					fifoBaseRegAddr			=	0x7F;

	/// Data Registers
	uint8_t 		interruptEnable1Reg 	=	0,	// 0x05 | 05h.
					interruptEnable2Reg 	=	0,	// 0x06 | 06h.
					operAndFuncCtrl1Reg 	=	0,	// 0x07 | 07h.
					dataAcsCtrlReg			=	0,	// 0x30 | 30h.
					headerCtrl1Reg			=	0,	// 0x32 | 32h.
					headerCtrl2Reg 			=	0,	// 0x33 | 33h.
					preambDetectionCtrlReg	=	0,	// 0x35 | 35h.
					moduloModeCtrl1Reg		=	0,	// 0x70 | 70h.
					moduloModeCtrl2Reg		=	0;	// 0X71 | 71h.

	uint8_t 		txRxReg[10] 				=	{ 0 };

	HAL_StatusTypeDef status 				= 	HAL_ERROR;


	///-41-
	/*
		@brief:		Function to Read Received Data from the RF Module.
		@input:		none.
		@output:
					-	*fifo:		Data to Read from the FIFO.
					-	size:		Size of the RX Data.
		@return:	status.
	*/
	HAL_StatusTypeDef readDataFromRF(uint8_t* fifo, uint8_t* size);

	///-42-
	/*
		@brief:		Function to Write Transmitting Data to the RF Module.
		@input:
					-	*fifo:		Data to Send to the FIFO.
					-	size:		Size of the RX Data.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef writeDataToRF(uint8_t* fifo, size_t size);

	///-43-
	/*
		@brief:		Function to write data to RF SPI.
		@input:
					-	*address:	Address Pointer for the register to be written.
					-	*data:		Data Pointer for the data array to be written.
					-	size:		Data Array size to be written.
		@output:	none.
		@return:	status.
	*/
	HAL_StatusTypeDef write_Reg_To_RF_SPI(uint8_t* address, uint8_t* data, size_t size);

	///-44-
	/*
		@brief:		Function to Read data from RF SPI.
		@input:
					-	*address:	Address Pointer for the register to be written.
					-	size:		Data Array size to be written.
		@output:
					-	*data:		Data Pointer for the data array to be written.
		@return:	status.
	*/
	HAL_StatusTypeDef read_Reg_From_RF_SPI(uint8_t* address, uint8_t* data, size_t size);

};

#endif /* RFDriver_Si4432_H */
