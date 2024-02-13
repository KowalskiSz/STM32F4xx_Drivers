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
	uint32_t temp = 0;

	//Configure the MODE of a certain PIN
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//Get certain value based on PIN MODE and PIN NUMBER then write the value
		//into the PIN REGISTER
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clearing the BITfield
		pGPIOHandle->pGPIOx->MODER |= temp; // Setting  the BITfield
	}
	else
	{
		//Refering to IBTERRUPT MODES
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//configure both (FALLING AND RISING EGDE )
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		//configure GPIO port selection in SYSCFG_EXTICR
		uint8_t EXTICR_RegNum = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t EXTICR_BitPosition = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;

		SYSCFG_RCLK_EN();
		uint8_t portCode = CodeFromPinNum(pGPIOHandle->pGPIOx);
		SYSCFG->EXTICR[EXTICR_RegNum] |= (portCode << EXTICR_BitPosition*4); //TO CHECK ON MCU Program

		//enable EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	//init the rest - pincofig values write into the pin register
	//output type
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//configure the speed
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//Pull up/pull down conf
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	//Alternative function configuration
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUN)
	{
		//LOW
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7)
		{
			pGPIOHandle->pGPIOx->AFRL &= ~(0xF << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
			pGPIOHandle-> pGPIOx->AFRL |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		}
		else{
		//HIGH
			pGPIOHandle->pGPIOx->AFRH &= ~(0xF << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
			pGPIOHandle-> pGPIOx->AFRH |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		}
	}

}


void GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	//else if(pGPIOx == GPIOH)
	//{
		//GPIOH_REG_RESET();
	//}
}

/*
 * GPIOx Input read INPUT from certain PIN
 */
/*
 * - Function name
 * - Description
 *
 * - parameter
 * - parameter
 * - return		0 or 1
 *
 */

uint8_t GPIO_ReadFromPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> pinNumber) & 0x00000001);
	return value;
}

/*
 * GPIOx Input read INPUT from entire register
 */
/*
 * - Function name
 * - Description
 *
 * - parameter
 * - parameter
 * - return		16 bit value
 *
 */
uint16_t GPIO_ReadFromPort(GPIO_RegDef_t* pGPIOx)
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}

/*
 * GPIOx Output write by certain PIN
 */
/*
 * - Function name
 * - Description Write to output register value 0 or 1
 *
 * - parameter
 * - parameter
 * - return
 *
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << pinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << pinNumber);
	}
}

/*
 * GPIOx Output write by entire GPIOx register
 */
/*
 * - Function name
 * - Description Write to output register entire 16 bit value
 *
 * - parameter
 * - parameter
 * - return
 *
 */
void GRIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}


/*
 * GPIOx Output toggle the coresponding pin
 */
/*
 * - Function name
 * - Description Changes coressonding bit value to opposite by XOR logic
 *
 * - parameter
 * - parameter
 * - return
 *
 */
void GPIOToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber)
{
	pGPIOx->ODR ^= (1 << pinNumber);
}




uint8_t CodeFromPinNum(GPIO_RegDef_t* pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		return 0;
	}
	else if(pGPIOx == GPIOB)
	{
		return 1;
	}
	else if(pGPIOx == GPIOC)
	{
		return 2;
	}
	else if(pGPIOx == GPIOD)
	{
		return 3;
	}
	else if(pGPIOx == GPIOE)
	{
		return 4;
	}
	else if(pGPIOx == GPIOF)
	{
		return 5;
	}
	else if(pGPIOx == GPIOG)
	{
		return 6;
	}
	else if(pGPIOx == GPIOH)
	{
		return 7;
	}

	return 10;
}

//Interrupt configuration based on position value-> vector table (IRQ Number)
void IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI)
{
	//Check for enabling the interrupt
	if(ENorDI == ENABLE)
	{
		if(IRQNumber <= 31) //0 -> 31
		{
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64) //32 -> 63
		{
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96) //64 -> 95
		{
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{

			*NVIC_ICER0 |= (1 << IRQNumber); //0 -> 31
		}
		else if(IRQNumber > 31 && IRQNumber < 64) //32 -> 63
		{
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96) //64 -> 95
		{
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}


//NVIC Priority register configuration based on IRQ NUMBER and IRQ Priority value
void IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//Get Priority Reg number based on IRQNumber
	uint8_t PR_REG_Num = IRQNumber / 4;
	uint8_t PR_Section = IRQNumber % 4;


	uint8_t shift_calculation = ( 8 * PR_Section) - (8 - NO_BITS_IMPLEMENTED);
	*(NVIC_PR_REG + (PR_REG_Num * 4)) |= (IRQNumber << shift_calculation);

}


void IRQHandling(uint8_t pinNumber)
{
	//Bit position of pending register corresponds to pin number
	if(EXTI->PR & (1 << pinNumber))
	{
		//clear PR assiging 1 to bitfield
		EXTI->PR |= (1 << pinNumber);
	}
}





