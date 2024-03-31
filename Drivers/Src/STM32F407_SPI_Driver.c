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
	if(pSPIx->SPI_SR & FlagName)
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
/*
 * Sending the data - get the data from function and write it to DR then the data is being written to
 * TX buffer (we have no permission to TX and RX buffer - it can only be accessed by Data Register DR)
 *
 * Function is blocking call fun - it needs to be implemented without the while loops
 * Just using the interrupts
 */
//Send data function implementation
void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t* pTxBuffer, uint32_t len)
{
	//Loop till the len of the data message is greater than 0
	while(len > 0)
	{
		//Checking the TXE bit of SR register - if the transmit buffer is empty - waiting for buffer to become 1
		while(GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		//Check the DFF bit of CR1 - verify the data format
		if(pSPIx->SPI_CR1 & (1 << DFF))
		{
			//16 bit data frame - write to DR
			pSPIx->SPI_DR = *((uint16_t)pTxBuffer);

			//Decrement the data len of two bytes (16 bits)
			len--;
			len--;

			(uint16_t*)pTxBuffer++; //moving over two bytes

		}
		else
		{
			//8 bit data
			pSPIx->SPI_DR = *pTxBuffer;
			len--;

			pTxBuffer++;
		}

	}
}













