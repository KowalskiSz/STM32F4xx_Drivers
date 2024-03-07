/*
 * STM32F407_SPI_Driver.h
 *
 *  Created on: Mar 7, 2024
 *      Author: szymo
 */

#ifndef INC_STM32F407_SPI_DRIVER_H_
#define INC_STM32F407_SPI_DRIVER_H_
#include "stm32f407xx.h"
#include <stdint.h>

/*
 * Configuration structure for SPIx peripherial
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_Sclkspeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPAH;
	uint8_t SPI_SSM;

}SPI_Config_t;


/*
 * Handle structure of SPIx peripherial
 */
typedef struct
{
	SPI_RegDef_t* pSPIx; //-> base address of SPIx register
	SPI_Config_t SPIConfig;

}SPI_Handle_t;

//Methods defiintion

/*
 * Peripherial clock enabling and disabling
 */
void SPI_PeriClockControl(SPI_RegDef_t* pspix, uint8_t ENorDI);

/*
 * Peripherial Initiaozation and DEinitaization
 */
void SPI_Init(SPI_RegDef_t* pSPIHandle);
void SPI_DeInit(SPI_RegDef_t* pSPIx);

/*
 * Data send and receive
 */




#endif /* INC_STM32F407_SPI_DRIVER_H_ */
