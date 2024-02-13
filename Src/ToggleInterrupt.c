/*
 * ToggleInterrupt.c
 *
 *  Created on: Feb 13, 2024
 *      Author: szymo
 */
#include <stdint.h>
#include "stm32f407xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


//toggling the LED by pressing button (PA0) -> toggling triggered by the interrupt
int main(void)
{

	//Button Conf
	GPIO_Handle_t GPIOButton;

	GPIOButton.pGPIOx = GPIOA;

	GPIOButton.GPIO_PinConfig.GPIO_PinNumber = 0;
	GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HS;
	//GPIOButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
	GPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PULLUPDOWN_PU;

	//Clock activation
	GPIO_PeriClockControl(GPIOA, ENABLE);

	//GPIO init
	GPIO_Init(&GPIOButton);

	//Interrupt configuration
	IRQInterruptConfig(IRQ_EXTI0,ENABLE);


	//LED configuration
	GPIO_Handle_t GPIOLedToggle;

	GPIOLedToggle.pGPIOx = GPIOD;

	GPIOLedToggle.GPIO_PinConfig.GPIO_PinNumber = 12;
	GPIOLedToggle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GPIOLedToggle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LS;
	GPIOLedToggle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
	GPIOLedToggle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PULLUPDOWN_NOPUPD;

	//Clock activation
	GPIO_PeriClockControl(GPIOD, ENABLE);
	//LED Init
	GPIO_Init(&GPIOLedToggle);

}
