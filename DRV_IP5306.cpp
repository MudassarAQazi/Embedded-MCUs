#include <DRV_IP5306.h>
#include "string.h"

I2C_HandleTypeDef* bmsI2c;

void IP5306::begin(I2C_HandleTypeDef* i2c){//(uint8_t sdaPin, uint8_t sclPin) {
	bmsI2c = i2c;
}

HAL_StatusTypeDef IP5306::writeBytes(uint16_t addr, uint8_t *reg, uint8_t *data, uint8_t quantity) {
	uint8_t regData[30];
	regData[0]	=	*reg;
	for(uint8_t i = 1; i <= quantity; i++) regData[i] = data[i-1]; /// Added i"-1".
	HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(bmsI2c, addr, regData, (size_t)(quantity + 1), 100);
    if (res != HAL_OK) {
		#ifdef debugBms
			sprintf(msg, "IP5306 i2c write error: %d", res);
			LOG(msg);
		#endif
    	return res;
    }
    return HAL_OK;
}
HAL_StatusTypeDef IP5306::readBytes(uint16_t addr, uint8_t* reg, uint8_t *data, uint8_t quantity) {

	HAL_StatusTypeDef
	res = HAL_I2C_Master_Transmit(bmsI2c, (uint16_t)addr, reg, 1, 100); if(res != HAL_OK) return res;
	res	= HAL_I2C_Master_Receive(bmsI2c, (uint16_t)addr, data, 1, 100);

    if (res != HAL_OK) {
		#ifdef debugBms
			sprintf(msg, "IP5306 i2c write error: %d", res);
			LOG(msg);
		#endif
        return res;
    }
    return HAL_OK;
}

HAL_StatusTypeDef IP5306::setup(uint8_t initPrms /*= IP5306_DEFAULT_SETUP*/) {
    return this->writeBytes(IP5306_ADDR, &IP5306_REG_SYS_CTL0, &initPrms, 1);
}

uint8_t IP5306::isChargerConnected() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, &IP5306_REG_READ0, &data, 1);
    return (data & (1 << 3)) ? 1 : 0;
}

uint8_t IP5306::isChargeFull() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, &IP5306_REG_READ1, &data, 1);
    return (data & (1 << 3)) ? 1 : 0;
}

uint8_t IP5306::getBatteryLevel() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, &IP5306_REG_UNKNOW, &data, 1);
    switch (data & 0xF0) {
        case 0xE0: return 25;
        case 0xC0: return 50;
        case 0x80: return 75;
        case 0x00: return 100;
        default: return 0;
    }
}
