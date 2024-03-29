/*
 * STM32F407_SPI_Driver.c
 *
 *  Created on: Mar 7, 2024
 *      Author: szymo
 */
#include "STM32F407_SPI_Driver.h"

//Helper function implementation
uint8_t GetFlagStatus(SPI_RegDef_t* pSPIx, uint32_t FlagName)
{
	if(pSPIx->SPI_SR & SPI_TXE_FLAG)
	{
		return FLAG_SET;
	}
	else
	{
		return FLAG_RESET;
	}
}



//Main function implementation
void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			 SPI_1_RCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			 SPI_2_RCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			 SPI_3_RCLK_EN();
		}
	}
	else if(ENorDI == DISABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI_1_RCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI_2_RCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI_3_RCLK_DI();
		}
	}
}

void SPI_Init(SPI_Handle_t* pSPIHandle)
{
	//Initial 32 bit variable to configure all the bits
	uint32_t tempReg = 0;

	//Configure the device mode
	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	//Bus configuration
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FDUPLEX)
	{
		//BIDI Bit cleared
		tempReg &= ~(1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HDDUPLEX)
	{
		//BIDI Bit set
		tempReg |= (1 << 15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX)
	{
		//BIDI cleared
		//RXONLY BIT set

		tempReg &= ~(1 << 15);
		tempReg |= (1 << 10);
	}

	//Speed configuration
	tempReg |= pSPIHandle->SPIConfig.SPI_Sclkspeed << 3;

	//DFF configuration
	tempReg |= pSPIHandle->SPIConfig.SPI_DFF << 11;

	//CPOL Configuration
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	//CPAH Configuration
	tempReg |= pSPIHandle->SPIConfig.SPI_CPAH << 0;

	//SSM Configuration
	tempReg |= pSPIHandle->SPIConfig.SPI_SSM << 9;

}

//Send data function implementation
void SPI_SendData(SPI_RegDef_t* pSPIHandle, uint8_t* pTxBuffer, uint32_t len)
{

}













