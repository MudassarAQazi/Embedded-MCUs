#ifndef INC_DRV_IP5306_H_
#define INC_DRV_IP5306_H_

#include "stm32f0xx_hal.h"
#include "stdbool.h"
#include "stdio.h"

#define IP5306_DEFAULT_SETUP    0x37  // set power boost keep on by default

//#define IP5306_ADDR             {0x75 << 1}



class IP5306 {
    public:
        void begin(I2C_HandleTypeDef* i2c);//(uint8_t sdaPin, uint8_t sclPin);
        HAL_StatusTypeDef writeBytes(uint16_t addr, uint8_t* reg, uint8_t *data, uint8_t quantity);
        HAL_StatusTypeDef readBytes(uint16_t addr, uint8_t* reg, uint8_t *data, uint8_t quantity);
        HAL_StatusTypeDef setup(uint8_t initPrms = IP5306_DEFAULT_SETUP);
        uint8_t isChargerConnected();
        uint8_t isChargeFull();
        uint8_t getBatteryLevel();

        uint16_t IP5306_ADDR			=	0xEA;
        uint8_t IP5306_REG_SYS_CTL0		=	0x00;  // initialize
        uint8_t IP5306_REG_READ0		=	0x70;  // charge en
        uint8_t IP5306_REG_READ1		=	0x71;  // charge full
        uint8_t IP5306_REG_UNKNOW		=	0x78;  // bat level
};

#endif
