/*
 * STM32F407_SPI_Driver.c
 *
 *  Created on: Mar 7, 2024
 *      Author: szymo
 */
#include "STM32F407_SPI_Driver.h"


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

}


