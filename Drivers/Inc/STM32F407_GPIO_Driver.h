#ifndef INC_STM32F407_GPIO_DRIVER_H_
#define INC_STM32F407_GPIO_DRIVER_H_

#include "stm32f407xx.h"
#include <stdint.h>

//GPIO Pin Configuration Struct
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConf_t;


//Handle struct of the GPIO pin
typedef struct
{
	GPIO_RegDef_t* pGPIOx;	//Reference to certain GPIOx Pin type
	GPIO_PinConf_t GPIO_PinConfig; //COnfiguration of the GPIO Pin that is pointed on

}GPIO_Handle_t;


#endif /* INC_STM32F407_GPIO_DRIVER_H_ */
