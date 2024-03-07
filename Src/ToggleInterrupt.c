/*
 * ToggleInterrupt.c
 *
 *  Created on: Feb 13, 2024
 *      Author: szymo
 */
#include <string.h>
#include <stdint.h>
#include "stm32f407xx.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void EXTI0_IRQHandler()
{
	IRQHandling(GPIO_PIN_NO_0);
	GPIOToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}


//toggling the LED by pressing button (PA0) -> toggling triggered by the interrupt
int main(void)
{

	//Button Conf
	GPIO_Handle_t GPIOButton, GPIOLedToggle;

	memset(&GPIOButton, 0, sizeof(GPIO_Handle_t));
	memset(&GPIOLedToggle, 0, sizeof(GPIO_Handle_t));

	GPIOButton.pGPIOx = GPIOA;

	GPIOButton.GPIO_PinConfig.GPIO_PinNumber = 0;
	GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;//4
	GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HS;//2
	//GPIOButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
	GPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PULLUPDOWN_PU;//1

	//Clock activation
	GPIO_PeriClockControl(GPIOA, ENABLE);

	//GPIO init
	GPIO_Init(&GPIOButton);

	//Interrupt configuration
	IRQInterruptConfig(IRQ_EXTI0,ENABLE);

	//LED configuration

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


	while(1);

	return 0;

}
