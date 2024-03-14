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

//Macros

//Device modes
#define SPI_DEVCE_MODE_MASTER 1
#define SPI_DEVCE_MODE_SLAVE 0

//Bus Cnfiguration - full dupex, half duplex, Simplex TX only, Simplex RX only
#define SPI_BUS_CONFIG_FDUPLEX	1
#define SPI_BUS_CONFIG_HDDUPLEX	2
#define SPI_BUS_CONFIG_SIMPLEX_TX	3
#define SPI_BUS_CONFIG_SIMPLEX_RX	4

//Serial Clock Speed
#define SPI_SCLK_SPEED_DIV2		0
#define SPI_SCLK_SPEED_DIV4		1
#define SPI_SCLK_SPEED_DIV8		2
#define SPI_SCLK_SPEED_DIV16	3
#define SPI_SCLK_SPEED_DIV32	4
#define SPI_SCLK_SPEED_DIV64	5
#define SPI_SCLK_SPEED_DIV128	6
#define SPI_SCLK_SPEED_DIV256	7

//Data Frame size DFF
#define SPI_DFF_8BITS	0
#define SPI_DFF_16BITS	1

//CPOL Clock Polarity
#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

//CPAH Clock phase
#define SPI_CPAH_LOW 0
#define SPI_CPAH_HIGH 1

//SSM Config
#define SPI_SSM_SW 0
#define SPI_SSM_HW 1


//Methods defiintion

/*
 * Peripherial clock enabling and disabling
 */
void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, uint8_t ENorDI);

/*
 * Peripherial Initiaozation and DEinitaization
 */
void SPI_Init(SPI_Handle_t* pSPIHandle);
void SPI_DeInit(SPI_RegDef_t* pSPIx);

/*
 * Data send and receive
 */
void SPI_SendData(SPI_RegDef_t* pSPIHandle, uint8_t* pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t* pSPIHandle, uint8_t* pRxBuffer, uint32_t len);

/*
 * IRQ configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t* pHandleSPI);











#endif /* INC_STM32F407_SPI_DRIVER_H_ */
