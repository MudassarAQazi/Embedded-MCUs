// DisplayDriver_AiP16C22

// Header Files of the Libraries required
#include <DRV_DisplayDriver_CNKD1103_HT16C24A.h>
//#include <Wire.h>

static const uint8_t memSize = 52; // 52 Bytes of LCD Segments Data.

/// Memory Map of the LCD Screen
	/*
		Formating for AT16C24A for CNKD1103 LCD
		-
		- memoryMap[0]      {	S25		S24		S23		S22		S27		S51		S50		S29	} LSB	1. Hub Humidity 'Humid Icon', 'Dry|Comfort|Wet Icon'.							2. 'Forecast Icon', 'Sunny Icon', 'Moon Icon', and 'Stars Icon'.
		- memoryMap[1]      {	13D		13E		13C		13G		13F		13B		13A		--	}		1. Hub Humidity 'Tenth Digit'.
		- memoryMap[2]      {	14D		14E		14C		14G		14F		14B		14A		S26	}		1. Hub Humidity 'Unit Digit', and '% Icon'.
		- memoryMap[3]      {	28D		28E		28C		28G		28F		28B		28A		S39	}		1. Date 'Day Tenth Digit', 'D Icon'.
		- memoryMap[4]      {	29D		29E		29C		29G		29F		29B		29A		L6	}		1. Date 'Day Unit Digit'.																								3. Line 'L6'.
		- memoryMap[5]      {	30D		30E		30C		30G		30F		30B		30A		D9	}		1. Date 'Month Tenth Digit', '- Icon'.
		- memoryMap[6]      {	31D		31E		31C		31G		31F		31B		31A		S40	}		1. Date 'Month Unit Digit', 'M Icon'.
		- memoryMap[7]      {	32D		32E		32C		32G		32F		32B		32A		S60	}		1. Time 'Hours Tenth Digit', '24h Icon'.
		- memoryMap[8]      {	33D		33E		33C		33G		33F		33B		33A		D10	}		1. Time 'Hours Unit Digit', and ': Icon'.
		- memoryMap[9]      {	34D		34E		34C		34G		34F		34B		34A		S42	}		1. Time 'Minutes Tenth Digit', and 'PM Icon'.
		- memoryMap[10]     {	35D		35E		35C		35G		35F		35B		35A		S41	}		1. Time 'Minutes Unit Digit', and 'AM Icon'.
		- memoryMap[11]     {	15D		15E		15C		15G		15F		15B		15A		L7	}		1. AQI Out 'Hundredth Digit'.																							3. Line 'L7'.
		- memoryMap[12]     {	16D		16E		16C		16G		16F		16B		16A		L9	}		1. AQI Out 'Tenth Digit'.																								3. Line 'L9'.
		- memoryMap[13]     {	17D		17E		17C		17G		17F		17B		17A		S28	}		1. AQI Out 'Unit Digit'.														2. 'Snowy Cloud Icon'.
		- memoryMap[14]     {	22D		22E		22C		22G		22F		22B		22A		S33	}		1. Sunset 'Hours Tenth Digit'.													2. 'Sunset Icon'.
		- memoryMap[15]     {	23D		23E		23C		23G		23F		23B		23A		S31	}		1. Sunset 'Hours Unit Digit'.													2. 'AQI Out Icon'.
		- memoryMap[16]     {	24D		24E		24C		24G		24F		24B		24A		D8	}		1. Sunset 'Minutes Tenth Digit'.												2. ': Icon'.
		- memoryMap[17]     {	25D		25E		25C		25G		25F		25B		25A		S32	}		1. Sunset 'Minutes Unit Digit'.													2. 'Sunrise Icon'.
		- memoryMap[18]     {	18D		18E		18C		18G		18F		18B		18A		S44	}		1. Sunrise 'Hours Tenth Digit'.													2. 'Snow Icon'.
		- memoryMap[19]     {	19D		19E		19C		19G		19F		19B		19A		S46	}		1. Sunrise 'Hours Unit Digit'.													2. 'Partially Sunny Icon'.
		- memoryMap[20]     {	20D		20E		20C		20G		20F		20B		20A		D7	}		1. Sunrise 'Minutes Tenth Digit'.												2. ': Icon'.
		- memoryMap[21]     {	21D		21E		21C		21G		21F		21B		21A		S45	}		1. Sunrise 'Minutes Unit Digit'.												2. 'Rain Icon'.
		- memoryMap[22]     {	L8		L10		S37		S36		S35		S34		S49		--	}		1. Node Humidity 'Humid Icon', 'Dry|Comfort|Wet Icons', and 'Thunder Icon'.												3. Line 'L8', and 'L10'.
		- memoryMap[23]     {	26D		26E		26C		26G		26F		26B		26A		S30	}		1. Node Humidity 'Tenth Digit'.													2. Rainy Cloud Icon.
		- memoryMap[24]     {	27D		27E		27C		27G		27F		27B		27A		S38	}		1. Node Humidity 'Unit Digit' and '% Sign'.
		- memoryMap[25]     {	--		36A		36F		36H		36G		36E		36L		36M	}		1. Day '1st Digit Part-2'.
		- memoryMap[26]     {	--		36I		36J		36B		36K		36C		36N		36D	}		1. Day '1st Digit Part-1'.
		- memoryMap[27]     {	--		37A		37F		37H		37G		37E		37L		37M	}		1. Day '2nd Digit Part-2'.
		- memoryMap[28]     {	--		37I		37J		37B		37K		37C		37N		37D	}		1. Day '2nd Digit Part-1'.
		- memoryMap[29]     {	S43		38A		38F		38H		38G		38E		38L		38M	}		1. Day '3rd Digit Part-2'.														2. 'Day Icon'.
		- memoryMap[30]     {	--		38I		38J		38B		38K		38C		38N		38D	}		1. Day '3rd Digit Part-1'.
		- memoryMap[31]     {	39A		39B		39F		39G		39C		39E		39D		S5	}		1. Node 'Node Number'.															2. 'Out House Icon'.
		- memoryMap[32]     {	--		--		X1		X2		X3		X4		S55		S6	}		1. Node 'RF Signals', 'RF Out of Range'.										2. 'Out Icon'.
		- memoryMap[33]     {	T8		T9		T10		T11		T12		T13		T14		L2	}		1. Node 'Battery Cells'.																								3. Line 'L2'.
		- memoryMap[34]     {	D6		12D		12E		12C		12G		12F		12B		12A	}		1. Node Temperature 'Decimal Digit', and 'Decimal Point'.
		- memoryMap[35]     {	S56		--		--		--		S58		S59		S21		S20	}		1. Node Temperature 'DegreeFahrenheit', and 'DegreeCelsius' Signs.				2. 'NODE', PM'1', PM'10' Icon.
		- memoryMap[36]     {	L5		11D		11E		11C		11G		11F		11B		11A	}		1. Node Temperature 'Unit Digit'.																						3. Line 'L5'.
		- memoryMap[37]     {	--		10D		10E		10C		10G		10F		10B		10A	}		1. Node Temperature 'Tenth Digit', and 'Decimal Point'.
		- memoryMap[38]     {	--		--		--		--		D4		D5		S19		L11	}		1. Node Temperature 'ThermoIcon', 'Negative Sign', and 'Hundredth Position'.											3. Line 'L11'.
		- memoryMap[39]     {	L4		9D		9E		9C		9G		9F		9B		9A	}		1. Hub 'CO Unit Digit'.																									3. Line 'L4'.
		- memoryMap[40]     {	S12		8D		8E		8C		8G		8F		8B		8A	}		1. Hub 'CO Tenth Digit'.														2. AQI Indoor 'Good Icon'.
		- memoryMap[41]     {	--		7D		7E		7C		7G		7F		7B		7A	}		1. Hub 'CO Hundredth Digit'.
		- memoryMap[42]     {	--		6D		6E		6C		6G		6F		6B		6A	}		1. Hub 'AQI Unit Digit'.
		- memoryMap[43]     {	S47		5D		5E		5C		5G		5F		5B		5A	}		1. Hub 'AQI Tenth Digit'.														2. 'CO Icon'.
		- memoryMap[44]     {	S10		4D		4E		4C		4G		4F		4B		4A	}		1. Hub 'AQI Hundredth Digit'.													2. 'PM2.5 Icon'.
		- memoryMap[45]     {	S16		S17		S18		S14		S13		S2		S3		S57	}		1. Hub 'Indoor Icon', 'Indoor Air Quality Icon', AQI Indoor 'Moderate|USG|Poor|Very Poor|Hazardous Icon', 'PM'10 'UG/m3' Icon.
		- memoryMap[46]     {	--		T1		T2		T3		T4		T5		T6		T7	}		1. Hub 'Battery Cells'.
		- memoryMap[47]     {	L12		3D		3E		3C		3G		3F		3B		3A	}		1. Hub Temperature 'Decimal Digit'.																						3. Line 'L12'.
		- memoryMap[48]     {	W4		W3		W2		S54		W1		S53		S9		S8	}		1. Hub Temperature 'DegreeFahrenheit', and 'DegreeCelsius' Signs.				2. 'WiFi RSSI, Limited, NotConfigured'.
		- memoryMap[49]     {	D3		2D		2E		2C		2G		2F		2B		2A	}		1. Hub Temperature 'Tenth Digit', and 'Decimal Point'.
		- memoryMap[50]     {	L3		1D		1E		1C		1G		1F		1B		1A	}		1. Hub Temperature 'Unit Digit'.																						3. Line 'L3'.
		- memoryMap[51]     {	--		--		--		D1		D2		S7		L1		S1	}		1. Hub Temperature 'ThermoIcon', 'Negative Sign', and 'Hundredth Position'.		2. 'In House Icon'.						3. Line 'L1'.
		-
	*/
	static uint8_t memoryMap[memSize] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00
	}; /// 52 Bytes of LCD Formating Data.

	/// Communication Sequence
	//		3-Bytes are required to Setup Successful Data Read and Write Operation.
	//		1.	Slave I2C Address (With Write Mode).
	//		2.	Command Byte.
	//		3.	Register Address.

	/// LCD I2C Address storage for use after initialization
	static uint16_t		i2cReadAddress		=	0x0000;
	static uint16_t		i2cWriteAddress		=	0x0000;
	///static uint8_t		commandByte			=	0x80;
	///static uint8_t		addressPointer		=	0x00;

	static UART_HandleTypeDef	Uart;
	static I2C_HandleTypeDef	i2cPort;
	static uint16_t				i2cAddress;
	static HAL_StatusTypeDef	i2cState	=	HAL_OK;

/// -------------------------------------------- Registers Addresses ---------------------------------------------

	/// Control Registers Addresses
	static const uint8_t
		driveModeRegAddress		=	0x82,
		systemModeRegAddress	=	0x84,
		framFrequencyRegAddress	=	0x86,
		blinkRegAddress			=	0x88,
		vlcdSegEnableAddress	=	0x8A,
		brightCtrlEnAddress		=	0x8A;

	/// Segments Registers Addresses
	static const uint8_t

		hubBatteryAddress		=	0x2E,
		hubTempSignAddress		=	0x33,
		hubTempMsdAddress		=	0x33,
		hubTempPointAddress		=	0x31,
		hubWifiAddress			=	0x30,
		hubDegreeSymbolsAddress	=	0x30,
		hubHumidityIconsAddress	=	0x00,

		nodeNumberAddress		=	0x1F,
		nodeRfSignalsAddress	=	0x20,
		nodeBatteryAddress		=	0x21,
		nodeTempSignAddress		=	0x26,
		nodeTempMsdAddress		=	0x26,
		nodeTempPointAddress	=	0x22,
		nodeDegreeSymbolsAddress=	0x23,
		nodeHumidityIconsAddress=	0x16,

		AMAddress				=	0x0A,
		PMAddress				=	0x09,
		_24hAddress				=	0x07;


	/// Lines Location Addresses
	/*
		LCD Lines Separator Addresses
		- L1RegAddr		=	0x51,
		- L2RegAddr		=	0x33,
		- L3RegAddr		=	0x50,
		- L4RegAddr		=	0x39,
		- L5RegAddr		=	0x36,
		- L6RegAddr		=	0x04,
		- L7RegAddr		=	0x11,
		- L8RegAddr		=	0x22,
		- L9RegAddr		=	0x12,
		- L10RegAddr	=	0x22,
		- L11RegAddr	=	0x38,
		- L12RegAddr	=	0x47
		Total of 12 Lines Addresses.
	*/
	static const uint8_t linesAddress[12] =
	{
		0x33, 0x21, 0x32, 0x27, 0x24,
		0x04, 0x0B, 0x16, 0x0C, 0x16,
		0x26, 0x2F
	};

	/// Icons Location Addresses
	/*
		Addresses for Icons
		- hubHouseIconAddr			=	0x51,
		- hubBatteryIconAddr		=	0x46,
		- indoorIconAddr			=	0x45,
		- indoorAQIconAddr			=	0x45,
		- nodeHouseIconAddr			=	0x31,
		- nodeIconAddr				=	0x32,
		- nodeBattIconAddr			=	0x33,
		- hubhermoIconAddr			=	0x51,
		~/- hubDegFIconAddr			=	0x48,
		~/- hubDegCIconAddr			=	0x48,
		- aqiIconAddr				=	0x41,
		~/- goodAqiIconAddr			=	0x40,
		~/- moderateAqiIconAddr		=	0x45,
		~/- usgAqiIconAddr			=	0x45,
		~/- poorAqiIconAddr			=	0x45,
		~/- vPoorAqiIconAddr		=	0x45,
		~/- hazardAqiIconAddr		=	0x45,
		~/- pm2p5IconAddr			=	0x44,
		- nodeThermoIconAddr		=	0x38,
		~/- nodeDegFIconAddr		=	0x35,
		~/- nodeDegCIconAddr		=	0x35,
		- coPpmIconAddr				=	0x43,
		- hubHumidIconAddr			=	0x0,
		~/- dryHubHumidIconAddr		=	0x0,
		~/- comfortHumidIconAddr	=	0x0,
		~/- webHubHumidIconAddr		=	0x0,
		- percentHubHumidIconAddr	=	0x2,
		- forcastIconAddr			=	0x0,
		~/- moonIconAddr			=	0x0,
		~/- starsIconAddr			=	0x0,
		~/- snowyCloudIconAddr		=	0x13,
		~/- snowIconAddr			=	0x18,
		~/- sunnyIconAddr			=	0x0,
		~/- partialySunnyIconAddr	=	0x19,
		~/- rainyCloudIconAddr		=	0x23,
		~/- thunderIconAddr			=	0x22,
		~/- rainIconAddr			=	0x21,
		- aqiOutIconAddr			=	0x15,
		- sunriseIconAddr			=	0x17,
		- sunsetIconAddr			=	0x14,
		- nodeHumidIconAddr			=	0x22,
		~/- dryNodeHumidIconAddr	=	0x22,
		~/- comfortNodeHumidIconAddr=	0x22,
		~- wetNodeHumidIconAddr		=	0x22,
		- percentNodeHumidIconAddr	=	0x24,
		- dIconAddr					=	0x03,
		- mIconAddr					=	0x06,
		~/- amIconAddr				=	0x10,
		~/- pmIconAddr				=	0x09,
		- dayIconAddr				=	0x29
		Total of 50 Icon Addresses.
	*/
	static const uint8_t iconAddress[50] =
	{
		0x33,	0x2E,	0x2D,	0x2D,	0x1F,
		0x20,	0x23,	0x21,	0x33,	//0x30,	0x30,
		//0x29,	0x28,	0x2D,	0x2D,	0x2D,
		//0x2D,	0x2D,
						0x2C,	0x26,	//0x23,
		//0x23,
				0x2B,	0x0,	//0x0,	0x0,
		//0x0,
				0x02,	0x0,	//0x0,	0x0,
		//0x0D,	0x12,	0x0,	0x13,	0x17,
		//0x16,	0x15,
						0x0F,	0x11,	0x0E,
		0x16,	//0x16,	0x16,	0x16,
										0x18,
		0x03,	0x06,	//0x0A,	0x09,
										0x1D
	};

	/// 7-Segments Addresses
	//	Hub Temperature
	static const uint8_t hubTemperatureAddress[3] =
	{
		0x32,	0x31,	0x2F
	};

//	// Hub Degree Symbols
//	static const uint8_t hubDegreeSymbolsAddress[2] =
//	{
//
//	};

	//	Hub Humidity
	static const uint8_t hubHumidityAddress[2] =
	{
		0x01,	0x02
	};

	//	Node Temperature
	static const uint8_t nodeTemperatureAddress[3] =
	{
		0x25,	0x24,	0x22
	};

	//	Node Humidity
	static const uint8_t nodeHumidityAddress[2] =
	{
		0x17,	0x18
	};

	//	Hub AQI
	static const uint8_t hubAqiAddress[3] =
	{
		0x2C,	0x2B,	0x2A
	};

	// Hub PM Icon Type Address
	static const uint8_t hubPmIconAddress[4]	=
	{
		0x23,	0x2C,	0x23,	0x2D
	};

	//	Hub AQI Labels
	static const uint8_t hubAqiIconsAddress[6] =
	{
		0x28,	0x2D,	0x2D,	0x2D,	0x2D,	0x2D
	};

	//	Hub CO
	static const uint8_t hubCoAddress[3] =
	{
		0x29,	0x28,	0x27
	};

	//	AQI out
	static const uint8_t aqiOutAddress[3] =
	{
		0x0B,	0x0C,	0x0D
	};

	//	Weather out Address
	static const uint8_t weatherAddress[9] =
	{
		0x0,	0x0,	0x0D,	0x12,	0x0,
		0x13,	0x17,	0x16,	0x15
	};

	//	Sunrise Time
	static const uint8_t sunriseTimeAddress[5] =
	{
		0x12,	0x13,	0x14,	0x14,	0x15
	};

	//	Sunset Time
	static const uint8_t sunsetTimeAddress[5] =
	{
		0x0E,	0x0F,	0x10,	0x10,	0x11
	};

	//	Date
	static const uint8_t dateAddress[5] =
	{
		0x03,	0x04,	0x05,	0x05,	0x06
	};

	//	Time
	static const uint8_t timeAddress[5] =
	{
		0x07,	0x08,	0x08,	0x09,	0x0A
	};

	//	Weekday Digits
	static const uint8_t weekdayAddress[6] =
	{
		0x19,	0x1A,	0x1B,	0x1C,	0x1D,	0x1E
	};

	/// ------------------------------------------------ Icons Masks -------------------------------------------------

	/// Control Function Masks
	/*
		Control Functions
		- {0	0	0	0	Duty1	Bias1	Duty0	Bias1	} LSB	82H
		- {0	0	0   0   0		0		S		E		} LSB	84H		System Mode
		- {0	0	0   0   0		0		0		F		} LSB	86H		Frame Frequency
		- {0	0	0   0   0		0		BK1		BK0		} LSB	88H		Blinking Frequency
		- {0	0	DE  VE  DA3		DA2		DA1		DA0		} LSB	8AH
	*/
	static const uint8_t
		BIAS_DISP_Mask				=	0x05,   // Use it for 82H	Bias Select
		DUTY_DISP_Mask				=	0x0A,   // Use it for 82H	Duty Select e.g. 1/8 for 8 COM's
		OSC_DISP_Mask				=	0x02,   // Use it for 84H	Oscillator Select
		OFF_DISP_Mask				=	0x01,   // Use it for 84H	LCD Display ON/OFF Select
		FREQ_DISP_Mask				=	0x01,   // Use it for 86H	LCD Display Update Frequency Select
		BLNK_DISP_Mask				=	0x03,   // Use it for 88H	Blinking
		BRIGT_DISP_Mask				=	0x0F,   // Use it for 8AH	VLCD output Voltage for Brightness
		IVA_DISP_EN_Mask			=	0x10,   // Use it for 8AH	Internal Voltage Adjustment OFF/ON
		IVA_VLCD_DISP_PIN_EN_Mask	=	0x30;   // Use it for 8AH	VLCD/Segment71 Select

	/// Icons & 7 Segments Masks
	/*
		Icons Masks for Turning an Icon ON or OFF.
		- HUB_HOUSE_ICON_Mask			=	0x01,	//	S1 Mask		->	Use it on memoryMap[51]
		- HUB_BATT_ICON_Mask			=	0x40,	//	T1 Mask		->	Use it on memoryMap[46]
		- INDOOR_ICON_Mask				=	0x04,	//	S2 Mask		->	Use it on memoryMap[45]
		- INDOOR_AQ_ICON_Mask			=	0x02,	//	S3 Mask		->	Use it on memoryMap[45]
		- NODE_HOUSE_ICON_Mask			=	0x01,	//	S5 Mask		->	Use it on memoryMap[31]
		- NODE_ICON_Mask				=	0x01,	//	S6 Mask		->	Use it on memoryMap[32]
		- NODE_BATT_ICON_Mask			=	0x80,	//	T8 Mask		->	Use it on memoryMap[33]
		- HUB_THERMO_ICON_Mask			=	0x04,	//	S7 Mask		->	Use it on memoryMap[51]
		- HUB_DEG_F_ICON_Mask			=	0x01,	//	S8 Mask		->	Use it on memoryMap[48]
		- HUB_DEG_C_ICON_Mask			=	0x02,	//	S9 Mask		->	Use it on memoryMap[48]
		- HUB_AQI_ICON_Mask				=	0x80,	//	S15 Mask	->	Use it on memoryMap[41]
		- GOOD_AQI_ICON_Mask			=	0x80,	//	S12 Mask	->	Use it on memoryMap[40]
		- MODERATE_AQI_ICON_Mask		=	0x08,	//	S13 Mask	->	Use it on memoryMap[45]
		- USG_AQI_ICON_Mask				=	0x10,	//	S14 Mask	->	Use it on memoryMap[45]
		- POOR_AQI_ICON_Mask			=	0x80,	//	S16 Mask	->	Use it on memoryMap[45]
		- V_POOR_AQI_ICON_Mask			=	0x40,	//	S17 Mask	->	Use it on memoryMap[45]
		- HAZARD_AQI_ICON_Mask			=	0x20,	//	S18 Mask	->	Use it on memoryMap[45]
		- PM2P5_ICON_Mask				=	0x80,	//	S10 Mask	->	Use it on memoryMap[44]
		- Node_THERMO_ICON_Mask			=	0x02,	//	S19 Mask	->	Use it on memoryMap[38]
		- Node_DEG_F_ICON_Mask			=	0x01,	//	S20 Mask	->	Use it on memoryMap[35]
		- Node_DEG_C_ICON_Mask			=	0x02,	//	S21 Mask	->	Use it on memoryMap[35]
		- CO_PPM_ICON_Mask				=	0x80,	//	S47 Mask	->	Use it on memoryMap[43]
		- HUB_HUMID_ICON_Mask			=	0x10,	//	S22 Mask	->	Use it on memoryMap[0]
		- DRY_HUB_HUMID_ICON_Mask		=	0x20,	//	S23 Mask	->	Use it on memoryMap[0]
		- COMFORT_HUB_HUMID_ICON_Mask	=	0x40,	//	S24 Mask	->	Use it on memoryMap[0]
		- WET_HUB_HUMID_ICON_Mask		=	0x80,	//	S25 Mask	->	Use it on memoryMap[0]
		- PERCENT_HUB_HUMID_ICON_Mask	=	0x01,	//	S26 Mask	->	Use it on memoryMap[2]
		- FORECAST_ICON_Mask			=	0x08,	//	S27 Mask	->	Use it on memoryMap[0]
		- MOON_ICON_Mask				=	0x02,	//	S50 Mask	->	Use it on memoryMap[0]
		- STARS_ICON_Mask				=	0x04,	//	S51 Mask	->	Use it on memoryMap[0]
		- SNOWY_CLOUD_ICON_Mask			=	0x01,	//	S28 Mask	->	Use it on memoryMap[13]
		- SNOW_ICON_Mask				=	0x01,	//	S44 Mask	->	Use it on memoryMap[18]
		- SUNNY_ICON_Mask				=	0x01,	//	S29 Mask	->	Use it on memoryMap[0]
		- PARTIALY_SUNNY_ICON_Mask		=	0x01,	//	S46 Mask	->	Use it on memoryMap[19]
		- RAINY_CLOUD_ICON_Mask			=	0x01,	//	S30 Mask	->	Use it on memoryMap[23]
		- THUNDER_ICON_Mask				=	0x02,	//	S49 Mask	->	Use it on memoryMap[22]
		- RAIN_ICON_Mask				=	0x01,	//	S45 Mask	->	Use it on memoryMap[21]
		- AQI_OUT_ICON_Mask				=	0x01,	//	S31 Mask	->	Use it on memoryMap[15]
		- SUNRISE_ICON_Mask				=	0x01,	//	S32 Mask	->	Use it on memoryMap[17]
		- SUNSET_ICON_Mask				=	0x01,	//	S33 Mask	->	Use it on memoryMap[14]
		- NODE_HUMID_ICON_Mask			=	0x04,	//	S34 Mask	->	Use it on memoryMap[22]
		- DRY_NODE_HUMID_ICON_Mask		=	0x08,	//	S35 Mask	->	Use it on memoryMap[22]
		- COMFORT_NODE_HUMID_ICON_Mask	=	0x10,	//	S36 Mask	->	Use it on memoryMap[22]
		- WET_NODE_HUMID_ICON_Mask		=	0x20,	//	S37 Mask	->	Use it on memoryMap[22]
		- PERCENT_NODE_HUMID_ICON_Mask	=	0x01,	//	S38 Mask	->	Use it on memoryMap[24]
		- D_ICON_Mask					=	0x01,	//	S39 Mask	->	Use it on memoryMap[3]
		- M_ICON_Mask					=	0x01,	//	S40 Mask	->	Use it on memoryMap[6]
		- AM_ICON_Mask					=	0x01,	//	S41 Mask	->	Use it on memoryMap[10]
		- PM_ICON_Mask					=	0x01,	//	S42 Mask	->	Use it on memoryMap[9]
		- DAY_ICON_Mask					=	0x80,	//	S43 Mask	->	Use it on memoryMap[29]
		Total of 50 Masks Available.
	*/
	static const uint8_t iconMasks[50] =
	{
		0x01,	0x40,	0x04,	0x02,	0x01,
		0x01,	0x80,	0x80,	0x04,	//0x01,	0x02,
		//0x80,	0x80,	0x08,	0x10,	0x80,
		//0x40,	0x20,
						0x80,	0x02,	//0x01,
		//0x02,
				0x80,	0x10,	//0x20,	0x40,
		//0x80,
				0x01,	0x08,	//0x02,	0x04,
		//0x01,	0x01,	0x01,	0x01,	0x01,
		//0x02,	0x01,
						0x01,	0x01,	0x01,
		0x04,	//0x08,	0x10,	0x20,
										0x01,
		0x01,	0x01,	//0x01,	0x01,
										0x80
	};

	/// Lines Masks
	/*
		Lines Masks for Turning Lines ON/OFF.
		- LINE1_Mask	=	0x02,	//	L1 Mask		->	Use it on memoryMap[51]
		- LINE2_Mask	=	0x01,	//	L2 Mask		->	Use it on memoryMap[33]
		- LINE3_Mask 	=	0x80,	//	L3 Mask		->	Use it on memoryMap[50]
		- LINE4_Mask	=	0x80,	//	L4 Mask		->	Use it on memoryMap[39]
		- LINE5_Mask	=	0x80,	//	L5 Mask		->	Use it on memoryMap[36]
		- LINE6_Mask	=	0x01,	//	L6 Mask		->	Use it on memoryMap[4]
		- LINE7_Mask	=	0x01,	//	L7 Mask		->	Use it on memoryMap[11]
		- LINE8_Mask	=	0x80;	//	L8 Mask		->	Use it on memoryMap[22]
		- LINE9_Mask	=	0x80;	//	L9 Mask		->	Use it on memoryMap[12]
		- LINE10_Mask	=	0x80;	//	L10 Mask	->	Use it on memoryMap[22]
		- LINE11_Mask	=	0x80;	//	L11 Mask	->	Use it on memoryMap[38]
		- LINE12_Mask	=	0x80;	//	L12 Mask	->	Use it on memoryMap[47]
		-
		Total of 12 Lines Masks.
	*/
	static const uint8_t linesMasks[12] =
	{
		0x02,	0x01,	0x80,	0x80,	0x80,
		0x01,	0x01,	0x80,	0x01,	0x40,
		0x01,	0x80
	};

	/// RF Signals Masks
	/*
		RF Signals Masks to Turn Signal ON/OFF.
		- NODE_RF_SIGNAL0_Mask		=	0x20,		//	X1 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL1_Mask		=	0x30,		//	X2 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL2_Mask		=	0x38,		//	X3 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL3_Mask		=	0x3D,		//	X4 Mask		->	Use it on memoryMap[32]
		- NODE_RF_SIGNAL4_Mask		=	0x3E,		//	X5 Mask		->	Use it on memoryMap[32]
		Total of 5 RF Signal Masks
	*/
	static const uint8_t nodeRfSignalsMasks[6] =
	{
		0x00,	0x20,	0x30,	0x38,	0x3C,	0x02
	};

	/// Hub WiFi Masks
	/*
		Hub Battery Cell ON/OFF
		- HUB_W0_Mask			=	0x08,		//	W1 Mask			->	Use it on memoryMap[48]
		- HUB_W1_Mask			=	0x20,		//	W2 Mask			->	Use it on memoryMap[48]
		- HUB_W2_Mask			=	0x40,		//	W3 Mask			->	Use it on memoryMap[48]
		- HUB_W3_Mask			=	0x80,		//	W4 Mask			->	Use it on memoryMap[48]
		- HUB_LIMIT_Mask		=	0x10,		//	S54 Mask		->	Use it on memoryMap[48] // It should be used WiFi Limited Connectivity icon
		- HUB_NOTCONFIG_Mask	=	0x04,		//	S53 Mask		->	Use it on memoryMap[48] // It should be used WiFi Not Configured icon
		Total of 6 WiFi Signals Status Masks.
	*/
	static const uint8_t hubWifiMasks [7] =
	{
		0x00,	0x08,	0x28,	0x68,	0xE8,	0x10,	0x04
	};

	/// Hub Battery Masks
	/*
		Hub Battery Cell ON/OFF
		- HUB_BAT0_Mask		=	0x01,		//	T7 Mask		->	Use it on memoryMap[46]
		- HUB_BAT1_Mask		=	0x03,		//	T6 Mask		->	Use it on memoryMap[46]
		- HUB_BAT2_Mask		=	0x07,		//	T5 Mask		->	Use it on memoryMap[46]
		- HUB_BAT3_Mask		=	0x0F,		//	T4 Mask		->	Use it on memoryMap[46]
		- HUB_BAT4_Mask		=	0x1F,		//	T3 Mask		->	Use it on memoryMap[46]
		- HUB_BAT5_Mask		=	0x3F,		//	T2 Mask		->	Use it on memoryMap[46] // It should be used during re-enabling HUB BAT icon
		- HUB_BATCHARG_MASK	=	0x80		//	Flash Mask	->	Use it on memoryMap[46] // It should be used during Charging HUB BAT icon
		Total of 6 Battery Cells Masks.
	*/
	static const uint8_t hubBatteryMasks [8] =
	{
		0x00,	0x01,	0x03,	0x07,	0x0F,	0x1F,	0x3F,	0x80
	};

	/// Node Battery Masks
	/*
		Node Battery Cell ON/OFF
		- NODE_BAT0_Mask	=	0x02,		//	T14 Mask	->	Use it on memoryMap[33]
		- NODE_BAT1_Mask	=	0x06,		//	T13 Mask	->	Use it on memoryMap[33]
		- NODE_BAT2_Mask	=	0x0E,		//	T12 Mask	->	Use it on memoryMap[33]
		- NODE_BAT3_Mask	=	0x1E,		//	T11 Mask	->	Use it on memoryMap[33]
		- NODE_BAT4_Mask	=	0x3E,		//	T10 Mask	->	Use it on memoryMap[33]
		- NODE_BAT5_Mask	=	0x7E,		//	T9	Mask	->	Use it on memoryMap[33] // It should be used during re-enabling NODE BAT icon
		Total of 6 Battery Cells Masks.
	*/
	static const uint8_t nodeBatteryMasks[7] =
	{
		0x00,	0x02,	0x06,	0x0E,	0x1E,	0x3E,	0x7E
	};

	//	Hub AQI Icons Masks
	static const uint8_t hubAqiIconsMasks[6] =
	{
		0x80,	0x08,	0x10,	0x80,	0x40,	0x20
	};

	// Hub PM Icon Types Masks
	static const uint8_t hubPmIconMasks[4]	=
	{
		0x08,	0x80,	0x0C,	0x01
	};

//	// Hub/Node Degree Symbols
//	const uint8_t degreeSymbolsMasks[2] =
//	{
//		0x02,	0x01
//	};

	//	Hub Humidity Icons Masks
	static const uint8_t hubHumidityIconsMasks[3] =
	{
		0x20,	0x40,	0x80
	};

	//	Node Humidity Icons Masks
	static const uint8_t nodeHumidityIconsMasks[3] =
	{
		0x08,	0x10,	0x20
	};

	//	Node Humidity Icons Masks
	static const uint8_t weatherMasks[9] =
	{
		0x02,	0x04,	0x01,	0x01,	0x01,
		0x01,	0x01,	0x02,	0x01
	};

	/// 7-Segment Digits and Separator Masks.
	static const uint8_t
		sSeg_Mask_D1_D12			=	0x7F,	//	Digit 1 - 12				->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
		sSeg_Mask_D13_D35			=	0xFE,	//	Digit 13 - 35, & 39 		->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]

//		sSeg_upNibble_Mask_D1_D12		=	0x7F,	//	Digit 1 - 12			->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
//		sSeg_downNibble_Mask_D1_D12		=	0x0F,	//	Digit 1 - 12			->	Use it on memoryMap[34, 36, 37, 39, 40, 41, 42, 43, 44, 47, 49, 50]
//		sSeg_upNibble_Mask_D13_D35		=	0xFE,	//	Digit 13 - 35, & 39 	->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]
//		sSeg_downNibble_Mask_D13_D35	=	0x0E,	//	Digit 13 - 35, & 39 	->	Use it on memoryMap[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20 ,21, 23, 24]

		NODE_NUMBER_MASK			=	0xFE,	//	Digit 39					->	Use it on memoryMap[31]

		WEEKDAY_DIGIT_Mask			=	0x7F,	//	Digit 36 - 38				->	Use it on memoryMap[25, 26, 27, 28, 29, 30] e.g. {MON, TUE, WED, THU, FRI, SAT, SUN}

		HUB_TEMP_NEG_SIGN_Mask		=	0x10,	//	D1 Mask						->	Use it on memoryMap[51]
		HUB_TEMP_MSD_Mask			=	0x08,	//	D2 Mask						->	Use it on memoryMap[51]		MSD Most Significant Digit
		HUB_HUMID_ICONS_CLEAR_Mask	=	0xE0,	//	S23 - S25 Clear Mask		->	Use it on memoryMap[00]		MSD Most Significant Digit
		HUB_AQI_ICONS_CLEAR_Mask	=	0xF8,	//	S14 - S18 Clear Mask		->	Use it on memoryMap[45]		MSD Most Significant Digit

		POINT_Mask					=	0x80,	//	D3, D6 Mask					->	Use it on memoryMap[34, 49]
		DEG_FAHRENHEIT_Mask			=	0x01,	//	S8, s20 Mask				->	Use it on memoryMap[35, 48]
		DEG_CELCIUS_Mask			=	0x02,	//	S9, s21 Mask				->	Use it on memoryMap[35, 48]

		NODE_TEMP_NEG_SIGN_Mask		=	0x08,	//	D4 Mask						->	Use it on memoryMap[38]		MSD Most Significant Digit
		NODE_TEMP_MSD_Mask			=	0x04,	//	D5 Mask						->	Use it on memoryMap[38]		MSD Most Significant Digit
		NODE_HUMID_ICONS_CLEAR_MASK	=	0x38,	//	S35 - S37 Clear Mask		->	Use it on memoryMap[22]		MSD Most Significant Digit

		TIME_DATE_SEPARATOR_Mask	=	0x01,	//	D7, D8, D9, & D10 Mask		-> Use it on memoryMap[5, 8, 16, 20]
		AM_PM_24h_Mask				=	0x01;	//	S41, & S42 Mask				->	Use it on memoryMap[9 ,10]		MSD Most Significant Digit

//		WEATHER_CLEAR_1_Mask		=	0x07,	//	S29, S50, & S51 Mask		-> Use it on memoryMap[00]
//		WEATHER_CLEAR_2_Mask		=	0x01;	//	S28, S30, S40, & S44-46 Mask-> Use it on memoryMap[6, 13, 18, 19, 21, 23]

	/// ------------------------------------------ Class Private Variables -------------------------------------------
	/// This variable will store Last status of Battery upon disabling event for re-enabling.
	static uint8_t
		lastHubBatStatus	=	0x00,
		///lastNodeBatStauts	=	0x00,
	// Drive Mode settings storing variable.
		driveModeSettings	=	0x03,
	// System Mode Settings storing variable.
		systemModeSettings	=	0x02,
	// Frame Frequency settings storing variable.
		frameFrequency		=	0x01,
	// Blinking Frequency settings storing variable.
		blinkFrequency		=	0x00,
	// VLCD/Segment71 selector settings storing variable.
		segVlcdSelect		=	0x00,
	// Brightness Level storing variable.
		brightnessValue		=	0x08,
	// Battery Level storing variable.
		///lastBatStatus		=	0x02,
	// Null Segment ( - ) value storing variable.
		nullSegment			=	0x0B,
	// Zero Segment ( 0 ) value storing variable.
		zeroSegment			=	0x0,
	// Empty Digit for 7-Segments Display.
		emptyDigit			=	0x0A;

	// Air Quality Index Icons Levels.
	static uint16_t
		aqiGoodLevel 			=	50,  // Air Quality Index (AQI) of 50.
		aqiModerateLevel		=	100, // Air Quality Index (AQI) of 100.
		aqiUsgLevel				=	150, // Air Quality Index (AQI) of 150.
		aqiPoorLevel			=	200, // Air Quality Index (AQI) of 200.
		aqiVeryPoorLevel		=	300, // Air Quality Index (AQI) of 250.
		aqiHazardousLevel		=	301; // Air Quality Index (AQI) of 300.
	// Humidity Labels Levels.
	static uint8_t
		humidityDryLevel 			=	39,
		humidityComfortLowerLevel	=	40, // Relative Humidity of 40%
		humidityComfortUpperLevel	=	60, // Relative Humidity of 60%
		humidityWetLowerLevel		=	61, // Relative Humidity of 61%
		humidityWetUpperLevel		=	99; // Relative Humidity of 61%

	// Variable array to get 7-Segments data.
	static uint8_t
		displayValue[3] = { 0 };

	// Variable array to get 14-Segments Day Data.
//	uint8_t
//		dayDisplayValue[6] = { 0 };

	// Variable to store communication status of the functions.
	static HAL_StatusTypeDef status = HAL_OK;

	// Variable for passing value to floatTo7Segments Converter.
	static float value = 0;
	/// 7-Segment data storing variables.
	/*
	float
		hubTemperatrue	=	0.0,
		hubHumidity		=	0.0,
		nodeTemperature	=	0.0,
		nodeHumidity	=	0.0,

		hubAqiLevel		=	0.0,
		coLevel			=	0.0,

		aqiOutLevel		=	0.0;

	uint8_t
		sunriseHours	=	0,
		surnriseMinutes	=	0,
		sunsetHours		=	0,
		sunsetMinutes	=	0,

		day				=	0,
		month			=	0,

		timeHour		=	0,
		timeMinute		=	0;
	*/

	/// Function to calculate absolute value for floating point number
	static float abs(float* number);

	/// Function to convert a floating point number to 7-segment display format
	static HAL_StatusTypeDef floatTo7Segment(float* number, uint8_t* display, bool node);

	/// Function to convert a BCD number to 7-segment display format
	static uint8_t bcdTo7Segments(uint8_t* bcdDigit);
	static uint8_t nodeBcdTo7Segments(uint8_t* bcdDigit);

	/// ------------------------------------------ Class Private Functions -------------------------------------------
	/*
		Helper Function to update display
		- Use this function into the main loop to maintain segments consistency
		-
	*/
	static HAL_StatusTypeDef updateDisplay();

	/*
		Private helper function for I2C communication with AiP16C22
		- I2C Address
		- Data Memory Array
		-
	*/
	static HAL_StatusTypeDef writeCommandToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	static HAL_StatusTypeDef writeDataToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	//	HAL_StatusTypeDef writeToDisplayI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);
	//	HAL_StatusTypeDef writeToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size);

	/*
			Function to read "Entire RAM" contents after wake up from deep sleep.
			- No arguments.
			-
	*/
	static HAL_StatusTypeDef readDisplayRAM(void);


/// Constructor for LCD Object Creation
//DisplayDriver_CNKD1103_HT16C24A::DisplayDriver_CNKD1103_HT16C24A()//uint8_t address)
//{
//}
//DisplayDriver_CNKD1103_HT16C24A::DisplayDriver_CNKD1103_HT16C24A(
//		I2C_HandleTypeDef&		hi2c,
//		const uint16_t&			address,
//		UART_HandleTypeDef&		huart)//uint8_t address)
//void DisplayDriver_CNKD1103_HT16C24A::lcd_begin(
//				I2C_HandleTypeDef&		hi2c,
//				const uint16_t&			address,
//				UART_HandleTypeDef&		huart)
////:i2cPort(hi2c), i2cAddress(address), Uart(huart)
//{
//	i2cPort		=	hi2c;
//	i2cAddress	=	address;
//	Uart		=	huart;
//}

/// Use this function at the start of the program in Main Subroutine.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::lcdPortInit(
		I2C_HandleTypeDef&		hi2c,
		const uint16_t&			address,
		UART_HandleTypeDef&		huart)
{
	/*
		Function to initialize the I2C Port, I2C Address, and Debug UART Port of the display
		- 	LCD I2C Port
		-	LCD I2C Address
		-	Debug UART
	*/

	/* Get these from User API */
	i2cPort		=	hi2c;
	i2cAddress	=	address;
	Uart		=	huart;

	// Slave Write and Read Address Initialization
	i2cWriteAddress = {(uint16_t)(i2cAddress << 1)};
	i2cReadAddress = {(uint16_t)(i2cWriteAddress | (uint16_t)0x01)};

	status = readDisplayRAM();

	return status;
}

/// Use this function after the lcdPortInit function.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayInit()
{
	// Implementation for I2C RAM based display initialization

	status = biasOfDisplay(0x01); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = dutyOfDisplay(0x01); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = frequency(false); 				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = segVlcdSetting(0x01); 			HAL_Delay(1);	if(status != HAL_OK) return status;
	status = brightness(0x2);				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = display(true); 				HAL_Delay(1);	if(status != HAL_OK) return status;
	status = enableDisplayDriver(true);		HAL_Delay(1);	if(status != HAL_OK) return status;

	status = displayClear();				HAL_Delay(1);	if(status != HAL_OK) return status;
#ifndef testSingleElement
	status = icon(HUB_HOUSE_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_BATT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_THERMO_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(HUB_HUMID_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(PERCENT_HUB_HUMID_ICON,	true);			if(status != HAL_OK) return status;
	status = icon(D_ICON,					true);			if(status != HAL_OK) return status;
	status = icon(M_ICON,					true);			if(status != HAL_OK) return status;

	status = icon(INDOOR_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(INDOOR_AQ_ICON,			true);			if(status != HAL_OK) return status;
	//status = icon(HUB_AQI_ICON,				true);			if(status != HAL_OK) return status;
	//status = icon(PM2P5_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(CO_PPM_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(FORECAST_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(AQI_OUT_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(SUNRISE_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(SUNSET_ICON,				true);			if(status != HAL_OK) return status;

	status = icon(NODE_HOUSE_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_OUT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_ICON,				true);			if(status != HAL_OK) return status;
	status = icon(NODE_BATT_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_THERMO_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(NODE_HUMID_ICON,			true);			if(status != HAL_OK) return status;
	status = icon(PERCENT_NODE_HUMID_ICON,	true);			if(status != HAL_OK) return status;
	status = icon(DAY_ICON,					true);			if(status != HAL_OK) return status;

	status = linesEnable(true);								if(status != HAL_OK) return status;

	status = hubWifiStatus(3);

	status = printNodeNumber(nullSegment);					if(status != HAL_OK) return status;
	status = printHubTemperature(200.0, noDegree);			if(status != HAL_OK) return status;
	status = printNodeTemperature(200.0, noDegree);			if(status != HAL_OK) return status;

	status = printHubHumidity(100);							if(status != HAL_OK) return status;
	status = printNodeHumidity(100);						if(status != HAL_OK) return status;

	status = printSunriseTime(25, 60);						if(status != HAL_OK) return status;
	status = printSunsetTime(25, 60);						if(status != HAL_OK) return status;
	status = printDate(32, 13, Monday);						if(status != HAL_OK) return status;
	status = printTime(25, 60, noMeridiem);					if(status != HAL_OK) return status;

	status = printIndoorAirQualityIndex(1000);				if(status != HAL_OK) return status;
	status = printIndoorCoLevel(1000);						if(status != HAL_OK) return status;
	status = printOutdoorAirQualityIndex(1000);				if(status != HAL_OK) return status;
#endif
	return status;
}

/// Function to Set Duty settings of the display  
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::dutyOfDisplay(uint8_t mode)// = (uint8_t)0x01)
{
	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Drive	Mode Selection
		[Mode]	[Duty]
		- 0		 1/4
		- 1		 1/8	(default for CNKD1103 LCD)
		- 2		 1/16
	*/
	switch (mode)
	{
		case 0: // 1/4 Duty:	4 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x00;
			break;
		case 1: // 1/8 Duty:	8 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x02;
			break;
		case 2: // 1/16 Duty:	16 COM's
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x08;
			break;
		default: // 1/8 Duty:	8 COM's specific for the Display Hub Design Version T2SV
			driveModeSettings = (driveModeSettings & ~DUTY_DISP_Mask) | 0x02;
	}

	return writeCommandToI2C(&driveModeRegAddress , &driveModeSettings, sizeof(driveModeSettings));
}

/// Function to set bias Display values
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::biasOfDisplay(uint8_t value)// = (uint8_t)0x01)
{
	/*
		LCD display off address 80H
		- { 0	0	0	0	Duty1	Bias1	Duty0	Bias0 }	LSB
		Select		Bias the Display
		[Value]		[Bias]
		 - 0		  1/3
		 - 1		  1/4
		 - 2		  1/5
	*/
	switch (value)
	{
		case 0: // 1/3 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x00;
			break;
		case 1: // 1/4 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x01;
			break;
		case 2: // 1/5 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x04;
			break;
		default: // 1/3 Bias.
			driveModeSettings = (driveModeSettings & ~BIAS_DISP_Mask) | 0x00;
	}
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&driveModeRegAddress, &driveModeSettings, sizeof(driveModeSettings));
}

/// Function to Enable/Disable Display Driver
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::enableDisplayDriver(bool enable = true)
{

	/*
		Function to Disable/Enable Display Driver IC (AiP16C22)
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [Internal System Oscillator(S)]
		 - 0         off
		 - 1         on
	*/
	if (enable) systemModeSettings |= OSC_DISP_Mask; else systemModeSettings &= (~OSC_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&systemModeRegAddress, &systemModeSettings, sizeof(systemModeSettings));
}

/// Function to Enable/Disable LCD Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::display(bool enable = true)
{

	/*
		Function to turn ON/OFF the Display
		- { 0	0	0	0	0	0	S	E }	LSB
		[Enable]   [LCD Display]
		 - 0         off
		 - 1         on
	*/
	if (enable) systemModeSettings |= OFF_DISP_Mask; else systemModeSettings &= (~OFF_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&systemModeRegAddress, &systemModeSettings, sizeof(systemModeSettings));

}

/// Function to Set Frame frequency
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::frequency(bool freq = false)
{
	/*
		Function to Select Frame Frequency of Display
		- { 0	0	0	0	0	0	0	F }	LSB
		[Frequency]	[Frame Frequency]
		 - 0         80 Hz
		 - 1         160 Hz
	*/
	if (freq) frameFrequency |= FREQ_DISP_Mask; else frameFrequency &= (~FREQ_DISP_Mask);
	//writeToI2C(modeSettings);
	return writeCommandToI2C(&framFrequencyRegAddress, &frameFrequency, sizeof(frameFrequency));
}

/// Function to Blink Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::blinkDisplay(uint8_t mode = (uint8_t)0x00)
{

	/*
		Function to Blink Display
		- { 0	0	0	0	0	0	BK1	BK0 }	LSB
		[Mode]     [Blinking Frequency]
		- 0          Blink off
		- 1          2 Hz
		- 2          1 Hz
		- 3          0.5 Hz
		-
	*/
	blinkFrequency = (blinkFrequency & ~BLNK_DISP_Mask) | mode;
	//writeToI2C(blinkValue);
	return writeCommandToI2C(&blinkRegAddress, & blinkFrequency, sizeof(blinkFrequency));
}

/// Function to Set SEG/VLCD pins settings
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::segVlcdSetting(uint8_t settings)// = (uint8_t)0x01)
{
	/*
		Function to Select SEG/VLCD Settings
		- { 0	0	DE	VE	DA3	DA2	DA1	DA0 }	LSB
		[DE]    [VE]    [Pin Selected]  [Internal Voltage Adjustment]
		- 0      0        VLCD Pin          off
		- 0      1        VLCD Pin          on
		- 1      0        SEG Pin           off
		- 1      1        SEG Pin           on
		-
	*/
	segVlcdSelect	&=	~IVA_VLCD_DISP_PIN_EN_Mask;
	segVlcdSelect	|=	(settings << 4);
//	segVlcdSelect |= brightnessValue;
	//writeToI2C(intVoltageCtrlValue);
	return writeCommandToI2C(&vlcdSegEnableAddress, &segVlcdSelect, sizeof(segVlcdSelect));
}

/// Function to Control LCD Display Brightness
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::brightness(uint8_t bright)
{
	/*  Function to set Brightness of the LCD
	    [Bright]    [Display]
	    - 0          Low Brightness
	    - .          .
	    - .          .
	    - 15         Full Brightness
	    -
	*/
	brightnessValue	&=	~BRIGT_DISP_Mask;
	brightnessValue	|=	bright;
//	brightnessValue |= segVlcdSelect;
	//writeToI2C(brightnessValue);
	return writeCommandToI2C(&brightCtrlEnAddress, &brightnessValue, sizeof(brightnessValue));
}

/// Use this function to clear content of the whole display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayClear()
{
	// Implementation for clearing the display
	for (uint8_t i = 0; i < memSize; i++) memoryMap[i] = 0x00; //Clearing all the memory map
//	linesEnable(true);
	return updateDisplay();
}

/// Use this function to Turn on All the Segments.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::displayFill()
{
	// Implementation for clearing the display
	for (uint8_t i = 0; i < memSize; i++) memoryMap[i] = 0xFF; //Populating all the memory map
//	linesEnable(true);
	return updateDisplay();
}

/// Use this function to turn on all the Lines
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::linesEnable(bool enable)
{
	/*
		Function to Set/Reset Division Lines
		- Enables/Disables Lines Separators..
	*/
	if (enable)
	{
		memoryMap[linesAddress[0]]	|=	linesMasks[0];
		memoryMap[linesAddress[1]]	|=	linesMasks[1];
		memoryMap[linesAddress[2]]	|=	linesMasks[2];
		memoryMap[linesAddress[3]]	|=	linesMasks[3];
		memoryMap[linesAddress[4]]	|=	linesMasks[4];
		memoryMap[linesAddress[5]]	|=	linesMasks[5];
		memoryMap[linesAddress[6]]	|=	linesMasks[6];
		memoryMap[linesAddress[7]]	|=	linesMasks[7];
		memoryMap[linesAddress[8]]	|=	linesMasks[8];
		memoryMap[linesAddress[9]]	|=	linesMasks[9];
		memoryMap[linesAddress[10]]	|=	linesMasks[10];
		memoryMap[linesAddress[11]]	|=	linesMasks[11];
	}
	else
	{
		memoryMap[linesAddress[0]]	&=	(~linesMasks[0]);
		memoryMap[linesAddress[1]]	&=	(~linesMasks[1]);
		memoryMap[linesAddress[2]]	&=	(~linesMasks[2]);
		memoryMap[linesAddress[3]]	&=	(~linesMasks[3]);
		memoryMap[linesAddress[4]]	&=	(~linesMasks[4]);
		memoryMap[linesAddress[5]]	&=	(~linesMasks[5]);
		memoryMap[linesAddress[6]]	&=	(~linesMasks[6]);
		memoryMap[linesAddress[7]]	&=	(~linesMasks[7]);
		memoryMap[linesAddress[8]]	&=	(~linesMasks[8]);
		memoryMap[linesAddress[9]]	&=	(~linesMasks[9]);
		memoryMap[linesAddress[10]]	&=	(~linesMasks[10]);
		memoryMap[linesAddress[11]]	&=	(~linesMasks[11]);
	}
	return updateDisplay();
}

/// Use this function to Set/Clear icon in the Loop Block
HAL_StatusTypeDef  DisplayDriver_CNKD1103_HT16C24A::icon(uint8_t iconType, bool enable)
{
	//// Implementation for enabling or disabling specified icon
	if (enable) memoryMap[iconAddress[iconType]] |= iconMasks[iconType];	else memoryMap[iconAddress[iconType]] &= (~iconMasks[iconType]);
	//uint8_t data[] = {0x80, iconAddress[iconType], memoryMap[iconAddress[iconType]]};
	status = writeDataToI2C(&iconAddress[iconType], &memoryMap[iconAddress[iconType]], sizeof(memoryMap[iconAddress[iconType]]));
	return status;
}

/// Function to display Hub WiFi Status.
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::hubWifiStatus(uint8_t rssi, bool limited, bool configured)
{
	/*  Function to set battery cells status
		[RSSi]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 4          Full
		-
	*/
	if(rssi <= 4)
	{
		memoryMap[hubWifiAddress]	&=	~hubWifiMasks[4];
		memoryMap[hubWifiAddress]	|=	hubWifiMasks[rssi];
		//lastHubBatStatus = hubWifiMasks[rssi];
	}
	else
	{
		//memoryMap[hubWifiAddress]	&=	~hubWifiMasks[7];
		//memoryMap[hubWifiAddress]	|=	hubWifiMasks[6];
		//lastHubBatStatus = hubBatteryMasks[6];
	}

	//WiFi Limited connectivity Icon.
	if(limited) {	memoryMap[hubWifiAddress] |= hubWifiMasks[5];	}
	else		{	memoryMap[hubWifiAddress] &= ~hubWifiMasks[5];	}

	//WiFi Configuration Status Icon.
	if(configured)	{	memoryMap[hubWifiAddress] &= ~hubWifiMasks[6];	}
	else			{	memoryMap[hubWifiAddress] |= hubWifiMasks[6];	}

	return writeDataToI2C(&hubWifiAddress, &memoryMap[hubWifiAddress], sizeof(memoryMap[hubWifiAddress]));
}

/// Function to display Hub Battery Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::hubBatteryStatus(uint8_t batteryCells, bool charging)
{
	/*  Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 6          Full
		-
	*/
	if(batteryCells <= 6)
	{
		memoryMap[hubBatteryAddress]	&=	~hubBatteryMasks[6];
		memoryMap[hubBatteryAddress]	|=	hubBatteryMasks[batteryCells];
		lastHubBatStatus = hubBatteryMasks[batteryCells];
	}
	else
	{
		memoryMap[hubBatteryAddress]	&=	~hubBatteryMasks[6];
		memoryMap[hubBatteryAddress]	|=	hubBatteryMasks[6];
		lastHubBatStatus = hubBatteryMasks[6];
	}

	// Check for Battery Charging.
	if(charging)	{	memoryMap[hubBatteryAddress]	|=	hubBatteryMasks[7];		}
	else			{	memoryMap[hubBatteryAddress]	&=	~hubBatteryMasks[7];	}

	return writeDataToI2C(&hubBatteryAddress, &memoryMap[hubBatteryAddress], sizeof(memoryMap[hubBatteryAddress]));
}

/// Function to Display Hub Temperature Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printHubTemperature(float temperatureValue, degree_t degree)
{
	/*
		Function to print Hub Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	// Setting Negative Sign for the Temperature Value.
	if(temperatureValue < 0)
	{
		memoryMap[hubTempSignAddress] |= HUB_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&hubTempSignAddress, &memoryMap[hubTempSignAddress], sizeof(memoryMap[hubTempSignAddress]));
		if(status != HAL_OK) return status;
	}
	else
	{
		memoryMap[hubTempSignAddress] &= ~HUB_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&hubTempSignAddress, &memoryMap[hubTempSignAddress], sizeof(memoryMap[hubTempSignAddress]));
		if(status != HAL_OK) return status;
	}

	// Printing Null Segment " - " for the Value Greater than the Range.
	if (abs(&temperatureValue) >= 200.0)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
		memoryMap[hubTempPointAddress] &= ~POINT_Mask;
	}
	else
	{
		// Generating 7-Segment values from floating point number
		status = floatTo7Segment(&temperatureValue, displayValue, false);
		memoryMap[hubTempPointAddress] |= POINT_Mask;
	}

	// Temperature Degree Type Selection.
	if(degree == degreeCelcius)
	{
		memoryMap[hubDegreeSymbolsAddress] &= ~DEG_FAHRENHEIT_Mask;
		memoryMap[hubDegreeSymbolsAddress] |= DEG_CELCIUS_Mask;
	}
	else if(degree == degreeFahrenheit)
	{
		memoryMap[hubDegreeSymbolsAddress] &= ~DEG_CELCIUS_Mask;
		memoryMap[hubDegreeSymbolsAddress] |= DEG_FAHRENHEIT_Mask;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		if((abs(&temperatureValue) >= 100.0) && (abs(&temperatureValue) < 200.0)) memoryMap[hubTempMsdAddress] |= HUB_TEMP_MSD_Mask;
		else	memoryMap[hubTempMsdAddress] &= ~HUB_TEMP_MSD_Mask;

		memoryMap[hubTemperatureAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[0]] |= displayValue[0];
		memoryMap[hubTemperatureAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[1]] |= displayValue[1];
		memoryMap[hubTemperatureAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubTemperatureAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&hubTempPointAddress, &memoryMap[hubTempPointAddress], sizeof(memoryMap[hubTempPointAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTempMsdAddress, &memoryMap[hubTempMsdAddress], sizeof(memoryMap[hubTempMsdAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[0], &memoryMap[hubTemperatureAddress[0]], sizeof(memoryMap[hubTemperatureAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[1], &memoryMap[hubTemperatureAddress[1]], sizeof(memoryMap[hubTemperatureAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubTemperatureAddress[2], &memoryMap[hubTemperatureAddress[2]], sizeof(memoryMap[hubTemperatureAddress[2]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&hubDegreeSymbolsAddress, &memoryMap[hubDegreeSymbolsAddress], sizeof(memoryMap[hubDegreeSymbolsAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;

//	for (uint8_t i = 1; i <= 6; i++)	memoryMap[i] &= (~sSeg_upNibble_Mask);
//	for (uint8_t j = 2; j <= 7; j++)		memoryMap[j] &= (~sSeg_downNibble_Mask);
//	// Updating corresponding bytes of temperature on Memory Map
//	if (temperatureValue >= 100.0) memoryMap[3] |= tSeg_S3_Mask;   else	memoryMap[3] &= (~tSeg_S3_Mask);
//	memoryMap[3] |= (temperatureDisplay[0] & sSeg_upNibble_Mask);	memoryMap[4] |= (temperatureDisplay[0] & sSeg_downNibble_Mask);
//	memoryMap[2] |= (temperatureDisplay[1] & sSeg_upNibble_Mask);	memoryMap[3] |= (temperatureDisplay[1] & sSeg_downNibble_Mask);
//	memoryMap[1] |= (temperatureDisplay[2] & sSeg_upNibble_Mask);	memoryMap[2] |= (temperatureDisplay[2] & sSeg_downNibble_Mask);
//	memoryMap[2] |= POINT_Mask;
//
//	// Updating corresponding bytes of humidity value on Memory Map
//	memoryMap[6] |= (humidDisplay[0] & sSeg_upNibble_Mask);			memoryMap[7] |= (humidDisplay[0] & sSeg_downNibble_Mask);
//	memoryMap[5] |= (humidDisplay[1] & sSeg_upNibble_Mask);			memoryMap[6] |= (humidDisplay[1] & sSeg_downNibble_Mask);
//	memoryMap[4] |= (humidDisplay[2] & sSeg_upNibble_Mask);			memoryMap[5] |= (humidDisplay[2] & sSeg_downNibble_Mask);
//	memoryMap[5] |= Point_Mask;
//
//	return updateDisplay();
	return HAL_OK;

}

/// Function to Display Hub Humidity Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printHubHumidity(uint8_t humidityValue)
{
	/*
		Function to print Hub Humidity Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (humidityValue >= 100)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float) humidityValue;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}
	//delay(100);
	//Serial.print("Humidity : \t");

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Humidity Label Selection based on Humidity input Level.
		if(humidityValue <= humidityDryLevel)
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[0];
		}
		else if((humidityValue >= humidityComfortLowerLevel) && (humidityValue <= humidityComfortUpperLevel))
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[1];
		}
		else if((humidityValue >= humidityWetLowerLevel) && (humidityValue <= humidityWetUpperLevel))
		{
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;
			memoryMap[hubHumidityIconsAddress] |= hubHumidityIconsMasks[2];
		}
		else
			memoryMap[hubHumidityIconsAddress] &= ~HUB_HUMID_ICONS_CLEAR_Mask;

		memoryMap[hubHumidityAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[hubHumidityAddress[0]] |= displayValue[0];
		memoryMap[hubHumidityAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[hubHumidityAddress[1]] |= displayValue[1];

		// Label Updates.
		status = writeDataToI2C(&hubHumidityIconsAddress, &memoryMap[hubHumidityIconsAddress], sizeof(memoryMap[hubHumidityIconsAddress]));
		if(status != HAL_OK) return status;

		// Levels Updates.
		status = writeDataToI2C(&hubHumidityAddress[0], &memoryMap[hubHumidityAddress[0]], sizeof(memoryMap[hubHumidityAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubHumidityAddress[1], &memoryMap[hubHumidityAddress[1]], sizeof(memoryMap[hubHumidityAddress[1]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Indoor Air Quality Index
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printIndoorAirQualityIndex(uint16_t airQuality, particulate_matter_t pmType)
{

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (airQuality >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)airQuality/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (airQuality <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(airQuality <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(airQuality<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Air Quality Index Label Selection based on AQI Level.
		if(airQuality <= aqiGoodLevel)
		{
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[0]] |= hubAqiIconsMasks[0];
		}
		else if((airQuality > aqiGoodLevel) && (airQuality <= aqiModerateLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[1]] |= hubAqiIconsMasks[1];
		}
		else if((airQuality > aqiModerateLevel) && (airQuality <= aqiUsgLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[2]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[2]] |= hubAqiIconsMasks[2];
		}
		else if((airQuality > aqiUsgLevel) && (airQuality <= aqiPoorLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[3]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[3]] |= hubAqiIconsMasks[3];
		}
		else if((airQuality > aqiPoorLevel) && (airQuality <= aqiVeryPoorLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[4]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[4]] |= hubAqiIconsMasks[4];
		}
		else if((airQuality >= aqiHazardousLevel))
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[5]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
			memoryMap[hubAqiIconsAddress[5]] |= hubAqiIconsMasks[5];
		}
		else
		{
			memoryMap[hubAqiIconsAddress[0]] &= ~hubAqiIconsMasks[0];
			memoryMap[hubAqiIconsAddress[1]] &= ~HUB_AQI_ICONS_CLEAR_Mask;
		}

		// Offset for PM UG/m3 for PM1 and PM10 in Address and Masks
		const uint8_t pm1or10Icon	=	0x03;
		switch(pmType)
		{
		case PM1p0:	{
			memoryMap[hubPmIconAddress[PM2p5]]			&=	~hubPmIconMasks[PM2p5];
			memoryMap[hubPmIconAddress[PM10]]			&=	~hubPmIconMasks[PM10];
			memoryMap[hubPmIconAddress[pm1or10Icon]]	|=	hubPmIconMasks[pm1or10Icon];
			memoryMap[hubPmIconAddress[PM1p0]]			|=	hubPmIconMasks[PM1p0];
		}	break;
		case PM2p5:	{
			memoryMap[hubPmIconAddress[pm1or10Icon]]	&=	~hubPmIconMasks[pm1or10Icon];
			memoryMap[hubPmIconAddress[PM1p0]]			&=	~hubPmIconMasks[PM1p0];
			memoryMap[hubPmIconAddress[PM10]]			&=	~hubPmIconMasks[PM10];
			memoryMap[hubPmIconAddress[PM2p5]]			|=	hubPmIconMasks[PM2p5];
		}	break;
		case PM10:	{
			memoryMap[hubPmIconAddress[PM1p0]]			&=	~hubPmIconMasks[PM1p0];
			memoryMap[hubPmIconAddress[PM2p5]]			&=	~hubPmIconMasks[PM2p5];
			memoryMap[hubPmIconAddress[pm1or10Icon]]	|=	hubPmIconMasks[pm1or10Icon];
			memoryMap[hubPmIconAddress[PM10]]			|=	hubPmIconMasks[PM10];
		}	break;
		default:	{
			memoryMap[hubPmIconAddress[pm1or10Icon]]	&=	~hubPmIconMasks[pm1or10Icon];
			memoryMap[hubPmIconAddress[PM1p0]]			&=	~hubPmIconMasks[PM1p0];
			memoryMap[hubPmIconAddress[PM10]]			&=	~hubPmIconMasks[PM10];
			memoryMap[hubPmIconAddress[PM2p5]]			|=	hubPmIconMasks[PM2p5];
		}
		}

		memoryMap[hubAqiAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[0]] |= displayValue[0];
		memoryMap[hubAqiAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[1]] |= displayValue[1];
		memoryMap[hubAqiAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubAqiAddress[2]] |= displayValue[2];

		// Label Updates.
		status = writeDataToI2C(&hubAqiIconsAddress[0], &memoryMap[hubAqiIconsAddress[0]], sizeof(memoryMap[hubAqiIconsAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiIconsAddress[1], &memoryMap[hubAqiIconsAddress[1]], sizeof(memoryMap[hubAqiIconsAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubPmIconAddress[pm1or10Icon], &memoryMap[hubPmIconAddress[pm1or10Icon]], sizeof(memoryMap[hubPmIconAddress[pm1or10Icon]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubPmIconAddress[PM1p0], &memoryMap[hubPmIconAddress[PM1p0]], sizeof(memoryMap[hubPmIconAddress[PM1p0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubPmIconAddress[PM2p5], &memoryMap[hubPmIconAddress[PM2p5]], sizeof(memoryMap[hubPmIconAddress[PM2p5]]));
		if(status != HAL_OK) return status;
		//status = writeDataToI2C(&hubPmIconAddress[PM10], &memoryMap[hubPmIconAddress[PM10]], sizeof(memoryMap[hubPmIconAddress[PM10]]));
		//if(status != HAL_OK) return status;

		// Levels Updates.
		status = writeDataToI2C(&hubAqiAddress[0], &memoryMap[hubAqiAddress[0]], sizeof(memoryMap[hubAqiAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiAddress[1], &memoryMap[hubAqiAddress[1]], sizeof(memoryMap[hubAqiAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubAqiAddress[2], &memoryMap[hubAqiAddress[2]], sizeof(memoryMap[hubAqiAddress[2]]));
		if(status != HAL_OK) return status;

	}
	else return status;
	return HAL_OK;
}

/// Function to Display Indoor CO Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printIndoorCoLevel(uint16_t coLevel)
{

	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	if (coLevel >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)coLevel/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (coLevel <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(coLevel <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(coLevel<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
	}

	if(status == HAL_OK)
	{
		memoryMap[hubCoAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[0]] |= displayValue[0];
		memoryMap[hubCoAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[1]] |= displayValue[1];
		memoryMap[hubCoAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[hubCoAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&hubCoAddress[0], &memoryMap[hubCoAddress[0]], sizeof(memoryMap[hubCoAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubCoAddress[1], &memoryMap[hubCoAddress[1]], sizeof(memoryMap[hubCoAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&hubCoAddress[2], &memoryMap[hubCoAddress[2]], sizeof(memoryMap[hubCoAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Node Number
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeNumber(uint8_t nodeNumber)
{

	/*
			Function to print Outdoor Node Number on the display
			- (Node_Number)
			- Address of Node Number,
			-
	*/
	value = (float)nodeNumber;
	displayValue[0] = 0;
	status = floatTo7Segment(&value, &displayValue[0], true);
	memoryMap[nodeNumberAddress]	&=	~NODE_NUMBER_MASK;
	memoryMap[nodeNumberAddress]	|=	displayValue[0];
	if(status == HAL_OK)
	{
		return writeDataToI2C(&nodeNumberAddress, &memoryMap[nodeNumberAddress], sizeof(memoryMap[nodeNumberAddress]));
	}
	else
		return status;
}

/// Function to Display Node Signals Strength Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::nodeRfSignals(uint8_t strength, bool nodeOutOfRange)
{
	/*  Function to set battery cells status
		[Signals]	[Strength]
		- 0          No Signals
		- .          .
		- .          .
		- 4          Strong
		-
	*/
	if(strength <= 4)
	{
		memoryMap[nodeRfSignalsAddress]	&=	~nodeRfSignalsMasks[strength];
		memoryMap[nodeRfSignalsAddress]	|=	nodeRfSignalsMasks[strength];
	}
	else
	{
		memoryMap[nodeRfSignalsAddress]	&=	~nodeRfSignalsMasks[4];
		memoryMap[nodeRfSignalsAddress]	|=	nodeRfSignalsMasks[4];
	}

	// Set Node Out of Range status.
	if(nodeOutOfRange)	{	memoryMap[nodeRfSignalsAddress]	|=	nodeRfSignalsMasks[5];	}
	else				{	memoryMap[nodeRfSignalsAddress]	&=	~nodeRfSignalsMasks[5];	}
	return writeDataToI2C(&nodeRfSignalsAddress, &memoryMap[nodeRfSignalsAddress], sizeof(memoryMap[nodeRfSignalsAddress]));
}

/// Function to Display Node Battery Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::nodeBatteryStatus(uint8_t batteryCells)
{
	/*  
		Function to set battery cells status
		[Cells]     [Status]
		- 0          Empty
		- .          .
		- .          .
		- 5          Full
		-
	*/
	if(batteryCells <= 7)
	{
		memoryMap[nodeBatteryAddress]	&=	~nodeBatteryMasks[batteryCells];
		memoryMap[nodeBatteryAddress]	|=	nodeBatteryMasks[batteryCells];
	}
	else
	{
		memoryMap[nodeBatteryAddress]	&=	~nodeBatteryMasks[6];
		memoryMap[nodeBatteryAddress]	|=	nodeBatteryMasks[6];
	}
	return writeDataToI2C(&nodeBatteryAddress, &memoryMap[nodeBatteryAddress], sizeof(memoryMap[nodeBatteryAddress]));

	/*switch (batteryCells) {
	case 0:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT0_Mask;	lastBatStatus = BAT0_Mask;  break;
	case 1:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT1_Mask;	lastBatStatus = BAT1_Mask;  break;
	case 2:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT2_Mask;	lastBatStatus = BAT2_Mask;  break;
	case 3:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT3_Mask;	lastBatStatus = BAT3_Mask;  break;
	case 4:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT4_Mask;	lastBatStatus = BAT4_Mask;  break;
	case 5:	 memoryMap[0] = (memoryMap[0] &= 0x03) | BAT5_Mask;	lastBatStatus = BAT5_Mask;  break;
	}*/
}

/// Function to Display Node Temperature Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeTemperature(float temperatureValue, degree_t degree)
{
	/*
		Function to print Node Temperature Value on the display
		- (Temperature)
		- Address of Temperature Value,
		-
	*/
	// Setting Negative Sign for the Temperature Value.
	if(temperatureValue < 0)
	{
		memoryMap[nodeTempSignAddress] |= NODE_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&nodeTempSignAddress, &memoryMap[nodeTempSignAddress], sizeof(memoryMap[nodeTempSignAddress]));
		if(status != HAL_OK) return status;
	}
	else
	{
		memoryMap[nodeTempSignAddress] &= ~NODE_TEMP_NEG_SIGN_Mask;
		status =  writeDataToI2C(&nodeTempSignAddress, &memoryMap[nodeTempSignAddress], sizeof(memoryMap[nodeTempSignAddress]));
		if(status != HAL_OK) return status;

	}

	// Printing Null Segment " - " for the Value Greater than the Range.
	if (abs(&temperatureValue) >= 200)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment);
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
		memoryMap[nodeTempPointAddress] &= ~POINT_Mask;
	}
	else
	{
		// Generating 7-Segment values from floating point number.
		memoryMap[nodeTempPointAddress] |= POINT_Mask;
		status = floatTo7Segment(&temperatureValue, displayValue, false);
	}

	// Temperature Degree Type Selection.
	if(degree == degreeCelcius)
	{
		memoryMap[nodeDegreeSymbolsAddress] &= ~DEG_FAHRENHEIT_Mask;
		memoryMap[nodeDegreeSymbolsAddress] |= DEG_CELCIUS_Mask;
	}
	else if(degree == degreeFahrenheit)
	{
		memoryMap[nodeDegreeSymbolsAddress] &= ~DEG_CELCIUS_Mask;
		memoryMap[nodeDegreeSymbolsAddress] |= DEG_FAHRENHEIT_Mask;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		if((abs(&temperatureValue) >= 100.0) && (abs(&temperatureValue) < 200.0)) memoryMap[nodeTempMsdAddress] |= NODE_TEMP_MSD_Mask;
		else	memoryMap[nodeTempMsdAddress] &= ~NODE_TEMP_MSD_Mask;

		memoryMap[nodeTemperatureAddress[0]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[0]] |= displayValue[0];
		memoryMap[nodeTemperatureAddress[1]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[1]] |= displayValue[1];
		memoryMap[nodeTemperatureAddress[2]] &= ~sSeg_Mask_D1_D12; memoryMap[nodeTemperatureAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&nodeTempPointAddress, &memoryMap[nodeTempPointAddress], sizeof(memoryMap[nodeTempPointAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTempMsdAddress, &memoryMap[nodeTempMsdAddress], sizeof(memoryMap[nodeTempMsdAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[0], &memoryMap[nodeTemperatureAddress[0]], sizeof(memoryMap[nodeTemperatureAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[1], &memoryMap[nodeTemperatureAddress[1]], sizeof(memoryMap[nodeTemperatureAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeTemperatureAddress[2], &memoryMap[nodeTemperatureAddress[2]], sizeof(memoryMap[nodeTemperatureAddress[2]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&nodeDegreeSymbolsAddress, &memoryMap[nodeDegreeSymbolsAddress], sizeof(memoryMap[nodeDegreeSymbolsAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Node Humidity Level
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printNodeHumidity(uint8_t humidityValue)
{
	/*
		Function to print Node Humidity Value on the display
		- (Humidity)
		- Address of Node Humidity Value,
		-
	*/
	// Printing Null Segment " - " for the Value Greater than the Range.
	if (humidityValue >= 100)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float) humidityValue;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}
	//delay(100);
	//Serial.print("Humidity : \t");

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		// Humidity Label Selection based on Humidity input Level.
		if(humidityValue <= humidityDryLevel)
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[0];
		}
		else if((humidityValue >= humidityComfortLowerLevel) && (humidityValue <= humidityComfortUpperLevel))
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[1];
		}
		else if((humidityValue >= humidityWetLowerLevel) && (humidityValue <= humidityWetUpperLevel))
		{
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;
			memoryMap[nodeHumidityIconsAddress] |= nodeHumidityIconsMasks[2];
		}
		else
			memoryMap[nodeHumidityIconsAddress] &= ~NODE_HUMID_ICONS_CLEAR_MASK;

		memoryMap[nodeHumidityAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[nodeHumidityAddress[0]] |= displayValue[0];
		memoryMap[nodeHumidityAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[nodeHumidityAddress[1]] |= displayValue[1];

		status = writeDataToI2C(&nodeHumidityIconsAddress, &memoryMap[nodeHumidityIconsAddress], sizeof(memoryMap[nodeHumidityIconsAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeHumidityAddress[0], &memoryMap[nodeHumidityAddress[0]], sizeof(memoryMap[nodeHumidityAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&nodeHumidityAddress[1], &memoryMap[nodeHumidityAddress[1]], sizeof(memoryMap[nodeHumidityAddress[1]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Turn Weather Icons ON/OFF on the Display
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printOutdoorWeather(uint8_t weather, bool enable)
{
	/*
		Function to print Outdoor Weather on the display
		- (Weather)
		-
	*/
	if(enable)	memoryMap[weatherAddress[weather]] |= weatherMasks[weather];
	else		memoryMap[weatherAddress[weather]] &= (~weatherMasks[weather]);

//	for(uint8_t i = 0; i < 9; i++)	memoryMap[weatherAddress[i]] &= (~weatherMasks[i]);
//	memoryMap[weatherAddress[weather]] |= weatherMasks[weather];
//	for(uint8_t i = 0; i < 9; i++)
//	{
		status = writeDataToI2C(&weatherAddress[weather], &memoryMap[weatherAddress[weather]], sizeof(memoryMap[weatherAddress[weather]]));
		if(status != HAL_OK)
		{
			return status;
		}
//	}
	return HAL_OK;
}

/// Function to Display Outdoor Air Quality Index
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printOutdoorAirQualityIndex(uint16_t airQuality)
{
	/*
		Function to print Dust/Air Quality Value on the display
		- (Humidity)
		- Address of Humidity Value,
		-
	*/
	// Printing Null Segment " - " for the Value Greater than the Range.
	if (airQuality >= 1000)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
		displayValue[2] = displayValue[0];
	}
	else
	{
		value = (float)airQuality/10;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Removing 7-Segments Display of "0" to "Empty Digit" Segments and Adding when MSB is present.
		if((displayValue[1] == bcdTo7Segments(&zeroSegment)) && (airQuality <= 9))
			displayValue[1] = bcdTo7Segments(&emptyDigit);

		// Shifting Digit towards Left i.e. Left Justified.
		if(airQuality <= 9)
		{
			displayValue[0] = bcdTo7Segments(&zeroSegment);
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}
		else if(airQuality<=99)
		{
			displayValue[0] = displayValue[1];
			displayValue[1] = displayValue[2];
			displayValue[2] = bcdTo7Segments(&emptyDigit);
		}

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
		displayValue[2] <<= 1;


	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[aqiOutAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[0]] |= displayValue[0];
		memoryMap[aqiOutAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[1]] |= displayValue[1];
		memoryMap[aqiOutAddress[2]] &= ~sSeg_Mask_D13_D35; memoryMap[aqiOutAddress[2]] |= displayValue[2];

		status = writeDataToI2C(&aqiOutAddress[0], &memoryMap[aqiOutAddress[0]], sizeof(memoryMap[aqiOutAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&aqiOutAddress[1], &memoryMap[aqiOutAddress[1]], sizeof(memoryMap[aqiOutAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&aqiOutAddress[2], &memoryMap[aqiOutAddress[2]], sizeof(memoryMap[aqiOutAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

/// Function to Display Sunrise Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printSunriseTime(uint8_t hours, uint8_t minutes)
{
	/*
		Function to print Sunrise Time on the display
		- (Hour, Minute, Meridiem)
		- Address of Hour,
		- Address of Minute,
		- Address of Meridiem
	*/

	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunriseTimeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[0]] |= displayValue[0];
		memoryMap[sunriseTimeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[1]] |= displayValue[1];
		memoryMap[sunriseTimeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&sunriseTimeAddress[0], &memoryMap[sunriseTimeAddress[0]], sizeof(memoryMap[sunriseTimeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[1], &memoryMap[sunriseTimeAddress[1]], sizeof(memoryMap[sunriseTimeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[2], &memoryMap[sunriseTimeAddress[2]], sizeof(memoryMap[sunriseTimeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunriseTimeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[3]] |= displayValue[0];
		memoryMap[sunriseTimeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[sunriseTimeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&sunriseTimeAddress[3], &memoryMap[sunriseTimeAddress[3]], sizeof(memoryMap[sunriseTimeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunriseTimeAddress[4], &memoryMap[sunriseTimeAddress[4]], sizeof(memoryMap[sunriseTimeAddress[4]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;
}

///// Function to Display Sunset Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printSunsetTime(uint8_t hours, uint8_t minutes)
{
	/*
		Function to print Sunset Time on the display
		- (Hour, Minute, Meridiem)
		- Address of Hour,
		- Address of Minute,
		- Address of Meridiem
	*/
	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunsetTimeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[0]] |= displayValue[0];
		memoryMap[sunsetTimeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[1]] |= displayValue[1];
		memoryMap[sunsetTimeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&sunsetTimeAddress[0], &memoryMap[sunsetTimeAddress[0]], sizeof(memoryMap[sunsetTimeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[1], &memoryMap[sunsetTimeAddress[1]], sizeof(memoryMap[sunsetTimeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[2], &memoryMap[sunsetTimeAddress[2]], sizeof(memoryMap[sunsetTimeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[sunsetTimeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[3]] |= displayValue[0];
		memoryMap[sunsetTimeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[sunsetTimeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&sunsetTimeAddress[3], &memoryMap[sunsetTimeAddress[3]], sizeof(memoryMap[sunsetTimeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&sunsetTimeAddress[4], &memoryMap[sunsetTimeAddress[4]], sizeof(memoryMap[sunsetTimeAddress[4]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}

///// Function to Display Date and Day Name
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printDate(uint8_t day, uint8_t month, uint8_t dayName)
{
	/*
		Function to print Date on the display
		- (Day, Month, Day_Name)
		- Address of Day,
		- Address of Month,
		- Address of DayName
	*/
	/// Variable array to get 14-Segments Day Data.
	uint8_t
		dayDisplayValue[6] = { 0 };

	/// Day Updating Functionality
	// Limiting Hours
	if (day >= 32)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) day;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[dateAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[0]] |= displayValue[0];
		memoryMap[dateAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[1]] |= displayValue[1];
		memoryMap[dateAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&dateAddress[0], &memoryMap[dateAddress[0]], sizeof(memoryMap[dateAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[1], &memoryMap[dateAddress[1]], sizeof(memoryMap[dateAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[2], &memoryMap[dateAddress[2]], sizeof(memoryMap[dateAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Month Updating Functionality
	// Limiting Minutes
	if (month >= 13)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) month;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	status = dayTo14Segment(dayName, dayDisplayValue);
	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[dateAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[3]] |= displayValue[0];
		memoryMap[dateAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[dateAddress[4]] |= displayValue[1];

		memoryMap[weekdayAddress[0]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[0]] |= dayDisplayValue[0];
		memoryMap[weekdayAddress[1]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[1]] |= dayDisplayValue[1];
		memoryMap[weekdayAddress[2]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[2]] |= dayDisplayValue[2];
		memoryMap[weekdayAddress[3]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[3]] |= dayDisplayValue[3];
		memoryMap[weekdayAddress[4]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[4]] |= dayDisplayValue[4];
		memoryMap[weekdayAddress[5]] &= ~WEEKDAY_DIGIT_Mask;	memoryMap[weekdayAddress[5]] |= dayDisplayValue[5];

		status = writeDataToI2C(&dateAddress[3], &memoryMap[dateAddress[3]], sizeof(memoryMap[dateAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&dateAddress[4], &memoryMap[dateAddress[4]], sizeof(memoryMap[dateAddress[4]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&weekdayAddress[0], &memoryMap[weekdayAddress[0]], sizeof(memoryMap[weekdayAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[1], &memoryMap[weekdayAddress[1]], sizeof(memoryMap[weekdayAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[2], &memoryMap[weekdayAddress[2]], sizeof(memoryMap[weekdayAddress[2]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[3], &memoryMap[weekdayAddress[3]], sizeof(memoryMap[weekdayAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[4], &memoryMap[weekdayAddress[4]], sizeof(memoryMap[weekdayAddress[4]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&weekdayAddress[5], &memoryMap[weekdayAddress[5]], sizeof(memoryMap[weekdayAddress[5]]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}

///// Function to Display Time
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::printTime(uint8_t hours, uint8_t minutes, meridiem_t MERIDIEM)
{
	/*
		Function to print Time on the display
		- (Hour, Minute, MERIDIEM)
		- Address of Hour,
		- Address of Minute,
		- Address of MERIDIEM
	*/
	/// Hours Updating Functionality
	// Limiting Hours
	if (hours >= 24)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) hours;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
		memoryMap[timeAddress[0]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[0]] |= displayValue[0];
		memoryMap[timeAddress[1]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[1]] |= displayValue[1];
		memoryMap[timeAddress[2]] |= TIME_DATE_SEPARATOR_Mask;

		status = writeDataToI2C(&timeAddress[0], &memoryMap[timeAddress[0]], sizeof(memoryMap[timeAddress[0]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[1], &memoryMap[timeAddress[1]], sizeof(memoryMap[timeAddress[1]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[2], &memoryMap[timeAddress[2]], sizeof(memoryMap[timeAddress[2]]));
		if(status != HAL_OK) return status;
	}
	else return status;

	/// Hours Updating Functionality
	// Limiting Minutes
	if (minutes >= 60)
	{
		displayValue[0] = bcdTo7Segments(&nullSegment) << 1;
		displayValue[1] = displayValue[0];
	}
	else
	{
		value = (float) minutes;
		// Generating 7-Segment values from floating point number.
		status = floatTo7Segment(&value, displayValue, false);

		// Shifting Values to left due to shift in segments position.
		displayValue[0] <<= 1;
		displayValue[1] <<= 1;
	}

	// Updating Screen RAM connected on I2C.
	if(status == HAL_OK)
	{
//		// AM / PM Selection.
//		if(MERIDIEM == AM)
//		{
//			memoryMap[AMAddress] |= AM_PM_Mask; memoryMap[PMAddress] &= ~AM_PM_Mask;
//		}
//		else if(MERIDIEM == PM)
//		{
//			memoryMap[PMAddress] |= AM_PM_Mask; memoryMap[AMAddress] &= ~AM_PM_Mask;
//		}
//		else
//		{
//			memoryMap[PMAddress] &= ~AM_PM_Mask;
//			memoryMap[AMAddress] &= ~AM_PM_Mask;
//		}
		// Updating Screen RAM connected on I2C.
		// AM / PM / 24h Selection.
		switch(MERIDIEM){
		case AM:
		{
			memoryMap[AMAddress]	|=	AM_PM_24h_Mask;
			memoryMap[PMAddress]	&=	~AM_PM_24h_Mask;
			memoryMap[_24hAddress]	&=	~AM_PM_24h_Mask;

		}
		break;

		case PM:
		{
			memoryMap[PMAddress]	|=	AM_PM_24h_Mask;
			memoryMap[AMAddress]	&=	~AM_PM_24h_Mask;
			memoryMap[_24hAddress]	&=	~AM_PM_24h_Mask;
		}
		break;

		case _24h:
		{
			memoryMap[_24hAddress] |= AM_PM_24h_Mask;
			memoryMap[PMAddress] &= ~AM_PM_24h_Mask;
			memoryMap[AMAddress] &= ~AM_PM_24h_Mask;
		}
		break;

		default:
		{
			memoryMap[PMAddress]	&=	~AM_PM_24h_Mask;
			memoryMap[AMAddress]	&=	~AM_PM_24h_Mask;
			memoryMap[_24hAddress]	&=	~AM_PM_24h_Mask;
		}
		}

		memoryMap[timeAddress[3]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[3]] |= displayValue[0];
		memoryMap[timeAddress[4]] &= ~sSeg_Mask_D13_D35; memoryMap[timeAddress[4]] |= displayValue[1];

		status = writeDataToI2C(&timeAddress[3], &memoryMap[timeAddress[3]], sizeof(memoryMap[timeAddress[3]]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&timeAddress[4], &memoryMap[timeAddress[4]], sizeof(memoryMap[timeAddress[4]]));
		if(status != HAL_OK) return status;

		status = writeDataToI2C(&AMAddress, &memoryMap[AMAddress], sizeof(memoryMap[AMAddress]));
		if(status != HAL_OK) return status;
		status = writeDataToI2C(&PMAddress, &memoryMap[PMAddress], sizeof(memoryMap[PMAddress]));
		if(status != HAL_OK) return status;
	}
	else return status;
	return HAL_OK;

}


/// Function to Print Hub Temperature value to 7-Segments Displays


//float DisplayDriver_CNKD1103_HT16C24A::abs(float* number)
static float abs(float* number)
{
	if(*number < 0)
		return (-(float)(*number));
	else return ((float)*number);
}

// Sub Function to convert a floating point number to 7-segment display format
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::floatTo7Segment(float* number, uint8_t* display, bool node)
static HAL_StatusTypeDef floatTo7Segment(float* number, uint8_t* display, bool node)
{

	// Extract the whole number and decimal parts
	uint8_t wholePart = (uint8_t)(abs(number));
	uint8_t decimalPart = (uint8_t)((abs(number) - wholePart) * 10);

	// Extract individual digits
	uint8_t tens = (wholePart / 10) % 10;
	uint8_t units = wholePart % 10;

	//if(wholePart < 10) tens = 0;
	// Convert each digit to 7-segment display format
	if(node)
	{
		*display = nodeBcdTo7Segments(&wholePart);
	}
	else
	{
		if (tens >= (uint8_t)1 || wholePart >= 100)
			display[0] = bcdTo7Segments(&tens);
		else display[0] = bcdTo7Segments(&zeroSegment); // emptyDigit.
		display[1] = bcdTo7Segments(&units);
		display[2] = bcdTo7Segments(&decimalPart);
	}
	/*for (int i = 0; i < 3; i++) { Serial.print('\t'); Serial.print(display[i]); }
	Serial.println();
	Serial.print("Number: ");			Serial.print(*number);
	Serial.print("\tWhole Part: ");		Serial.print(wholePart);
	Serial.print("\tTens: ");			Serial.print(tens);
	Serial.print("\tUnits: ");			Serial.print(units);
	Serial.print("\tDecimal Part: ");	Serial.println(decimalPart);*/
	return HAL_OK;
}

// Sub Function to convert Day into 14-segment display format
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::dayTo14Segment(uint8_t day, uint8_t (&dayDisplay)[6]) {
	switch (day) {			//b0AFHGELM							0b0IJBKCND
	case Monday:
		dayDisplay[0]	=	 0b00110100;	dayDisplay[1]	=	0b00110100; // Digit-A	->	'M'.
		dayDisplay[2]	=	 0b01100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'O'.
		dayDisplay[4]	=	 0b00110100;	dayDisplay[5]	=	0b00010110; // Digit-C	->	'N'.
		break;
	case Tuesday:
		dayDisplay[0]	=	 0b01000001;	dayDisplay[1]	=	0b01000000; // Digit-A	->	'T'.
		dayDisplay[2]	=	 0b00100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'U'.
		dayDisplay[4]	=	 0b01101100;	dayDisplay[5]	=	0b00000001; // Digit-C	->	'E'.
		break;
	case Wednesday:
		dayDisplay[0]	=	 0b00100110;	dayDisplay[1]	=	0b00010110; // Digit-A	->	'W'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00000001; // Digit-B	->	'E'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01010101; // Digit-C	->	'D'.
		break;
	case Thursday:
		dayDisplay[0]	=	 0b01000001;	dayDisplay[1]	=	0b01000000; // Digit-A	->	'T'.
		dayDisplay[2]	=	 0b00101100;	dayDisplay[3]	=	0b00011100; // Digit-B	->	'H'.
		dayDisplay[4]	=	 0b00100100;	dayDisplay[5]	=	0b00010101; // Digit-C	->	'U'.
		break;
	case Friday:
		dayDisplay[0]	=	 0b01101100;	dayDisplay[1]	=	0b00000000; // Digit-A	->	'F'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00011010; // Digit-B	->	'R'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01000001; // Digit-C	->	'I'.
		break;
	case Saturday:
		dayDisplay[0]	=	 0b01101000;	dayDisplay[1]	=	0b00001101; // Digit-A	->	'S'.
		dayDisplay[2]	=	 0b01101100;	dayDisplay[3]	=	0b00011100; // Digit-B	->	'A'.
		dayDisplay[4]	=	 0b01000001;	dayDisplay[5]	=	0b01000000; // Digit-C	->	'T'.
		break;
	case Sunday:
		dayDisplay[0]	=	 0b01101000;	dayDisplay[1]	=	0b00001101; // Digit-A	->	'S'.
		dayDisplay[2]	=	 0b00100100;	dayDisplay[3]	=	0b00010101; // Digit-B	->	'U'.
		dayDisplay[4]	=	 0b00110100;	dayDisplay[5]	=	0b00010110; // Digit-C	->	'N'.
		break;
	default:
		dayDisplay[0]	=	 0b00001000;	dayDisplay[1]	=	0b00001000; // Digit-A	->	'--'.
		dayDisplay[2]	=	 0b00001000;	dayDisplay[3]	=	0b00001000; // Digit-B	->	'--'.
		dayDisplay[4]	=	 0b00001000;	dayDisplay[5]	=	0b00001000; // Digit-C	->	'--'.
		break;
	}
	return HAL_OK;
}
// Sub Function to convert a BCD digit to 7-segment display format
//uint8_t DisplayDriver_CNKD1103_HT16C24A::bcdTo7Segments(uint8_t* bcdDigit)
static uint8_t bcdTo7Segments(uint8_t* bcdDigit)
{
	switch (*bcdDigit) {//b0DECGFBA		0bCGB0DEFA		0bGFEDCBA
	case 0:		return	 0b01110111;//	0b10101111;	//	0b0111111;	//	Actual 7 Segments should looks like ---
	case 1:		return	 0b00010010;//	0b10100000;	//	0b0000110;	//	<-- this but I had replaced it with ---
	case 2:		return	 0b01101011;//	0b01101101;	//	0b1011011;	//	the one that matches our RAM maping ---
	case 3:		return	 0b01011011;//	0b11101001;	//	0b1001111;	//	And to decrease data manipulation complexity.
	case 4:		return	 0b00011110;//	0b11100010;	//	0b1100110;
	case 5:		return	 0b01011101;//	0b11001011;	//	0b1101101;
	case 6:		return	 0b01111101;//	0b11001111;	//	0b1111101;
	case 7:		return	 0b00010011;//	0b10100001;	//	0b0000111;
	case 8:		return	 0b01111111;//	0b11101111;	//	0b1111111;
	case 9:		return	 0b01011111;//	0b11101011;	//	0b1101111;
	case 10:	return	 0b00000000;//	0b00000000;	//	0b0000000;
	default:	return	 0b00001000;//	0b01000000;	//	0b1000000;	// Invalid BCD digit
	}
}

// Sub Function to convert a BCD digit to 7-segment display format
//uint8_t DisplayDriver_CNKD1103_HT16C24A::nodeBcdTo7Segments(uint8_t* bcdDigit)
static uint8_t nodeBcdTo7Segments(uint8_t* bcdDigit)
{
	switch (*bcdDigit) {//bABFGCED0		0bCGB0DEFA		0bGFEDCBA
	//case 0:		return	 0b11101110;//	0b10101111;	//	0b0111111;	//	Actual 7 Segments should looks like ---
	case 1:		return	 0b01001000;//	0b10100000;	//	0b0000110;	//	<-- this but I had replaced it with ---
	case 2:		return	 0b11010110;//	0b01101101;	//	0b1011011;	//	the one that matches our RAM maping ---
	case 3:		return	 0b11011010;//	0b11101001;	//	0b1001111;	//	And to decrease data manipulation complexity.
	case 4:		return	 0b01111000;//	0b11100010;	//	0b1100110;
	case 5:		return	 0b10111010;//	0b11001011;	//	0b1101101;
	case 6:		return	 0b10111110;//	0b11001111;	//	0b1111101;
	case 7:		return	 0b11001000;//	0b10100001;	//	0b0000111;
	case 8:		return	 0b11111110;//	0b11101111;	//	0b1111111;
	case 9:		return	 0b11111010;//	0b11101011;	//	0b1101111;
	default:	return	 0b00010000;//	0b00000000;	//	0b0000000;	// Invalid BCD digit
	}
}
// Function to Send updated LCD Display values to RAM (AiP16C22) 
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::updateDisplay()
static HAL_StatusTypeDef updateDisplay()
{
	uint8_t writeCommand[54] = {0x80, 0x00};
	for(uint8_t i = 0; i < sizeof(memoryMap); i++)
	{
		writeCommand[i + 2] = memoryMap[i];
	}
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7);
	//i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, memoryMap, sizeof(memoryMap), 100);
	return i2cState;
}

// Function to Write control Registers settings through I2C 
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeCommandToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
static HAL_StatusTypeDef writeCommandToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
{
	uint8_t commandByte[] = {*regAddr, *regData};
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, commandByte, sizeof(commandByte), 1);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, (uint8_t*)regAddr, (uint8_t)1, (uint32_t)10);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, regData, size, 100);
	return i2cState;
}

// Function to Write Whole Data Memory Settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeDataToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
static HAL_StatusTypeDef writeDataToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
{
	uint8_t writeCommand[] = {0x80, *regAddr, *regData};
	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 1);
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cAddress, regData, size, 100);
	return i2cState;
}

// Function to Read Registers settings through I2C
HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readRAM(const uint8_t& regAddr, uint8_t& regData, size_t size)
{
	uint8_t writeCommand[] = {0x80, regAddr};

	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7); // Actual Time is 6 MillisSeconds.
	if(i2cState == HAL_OK)
		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, &regData, size, 1000);
#ifdef debug
	char str[100] = {'\0'};
	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
#endif
	return i2cState;
}

// Function to Read RAM Registers settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readDisplayRAM(void)
static HAL_StatusTypeDef readDisplayRAM(void)
{
	uint8_t writeCommand[] = {0x80, 0x00};

	status = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 7); // Actual Time is 6 MillisSeconds.
	HAL_Delay(10);
	if(i2cState == HAL_OK)
		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, memoryMap, sizeof(memoryMap), 1000);
#ifdef debug
	char str[100] = {'\0'};
	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
#endif
	return i2cState;
}

HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeDigitTest(uint8_t regAddr, uint8_t& regData, size_t size)
{
	return writeDataToI2C((const uint8_t*)&regAddr, &regData, size);
}
//// Function to Write Data Registers settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeToI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, (uint16_t)i2cWriteAddress, (uint8_t*)regData, size, 100);
//	return i2cState;
//}
//
//// Function to Write Registers settings through I2C (Currently, Not in Use).
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::writeToDisplayI2C(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//	i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, (uint8_t*)regData, size, 100);
//	return i2cState;
//}
//
//// Function to Read control Registers settings through I2C
//HAL_StatusTypeDef DisplayDriver_CNKD1103_HT16C24A::readRegister(const uint8_t* regAddr, uint8_t* regData, size_t size)
//{
//	uint8_t writeCommand[] = {*regAddr};
//
//		i2cState = HAL_I2C_Master_Transmit(&i2cPort, i2cWriteAddress, writeCommand, sizeof(writeCommand), 100);
//	if(i2cState == HAL_OK)
//		i2cState = HAL_I2C_Master_Receive(&i2cPort, i2cReadAddress, regData, size, 100);
//
//	char str[100] = {'\0'};
//#ifdef debug
//	size_t Size = sprintf((char*)str, "I2c Read Address: 0x%x, I2C Write Address: 0x%x,  Register Address: 0x%x,\tRegister Data: 0x%x\r\n", i2cReadAddress, i2cWriteAddress, *regAddr, *regData);
//	HAL_UART_Transmit(&Uart, (uint8_t*)str, Size, 2000); memset(str, 0, sizeof(str));
//#endif
//	return i2cState;
//}
