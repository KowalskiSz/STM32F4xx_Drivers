#include "STM32F407_GPIO_Driver.h"


/*
 * Peripherial clock setup
 */

/*
 * - Function name
 * - Description	Function to enable or disable peripherial clock for certain GPIO port
 *
 * - parameter	base address of the GPIO paripherial port
 * - parameter 	ENABLE or DISABLE macro
 *
 * - return		NONE
 *
 */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_RCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_RCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_RCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_RCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_RCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_RCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_RCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_RCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
			{
				GPIOA_RCLK_DI();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_RCLK_DI();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_RCLK_DI();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_RCLK_DI();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_RCLK_DI();
			}
			else if(pGPIOx == GPIOF)
			{
				GPIOF_RCLK_DI();
			}
			else if(pGPIOx == GPIOG)
			{
				GPIOG_RCLK_DI();
			}
			else if(pGPIOx == GPIOH)
			{
				GPIOH_RCLK_DI();
			}
	}


}

/*
 * Peripherial initialization setup
 */
/*
 * - Function name
 * - Description	Function to enable or disable peripherial clock for certain GPIO port
 *
 * - parameter	base address of the GPIO paripherial port
 * - parameter 	ENABLE or DISABLE macro
 *
 * - return		NONE
 *
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle)
{
	//Temporary value
	uint8_t temp = 0;

	//Configure the MODE of a certain PIN
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//Get certain value based on PIN MODE and PIN NUMBER then write the value
		//into the PIN REGISTER
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER = temp;
	}
	else
	{
		//Refering to IBTERRUPT MODES
	}

	temp = 0;

	//init the rest - pincofig values write into the pin register

}


