#ifndef INC_STM32F407_GPIO_DRIVER_H_
#define INC_STM32F407_GPIO_DRIVER_H_

#include "stm32f407xx.h"
#include <stdint.h>

//GPIO Pin Configuration Struct
typedef struct
{
	uint8_t GPIO_PinNumber; //Possible pin number @GPIO_PIN_NUMBER
	uint8_t GPIO_PinMode; 	//Possible modes @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;	// Possible speed modes @GPIO_SPEED_MODES
	uint8_t GPIO_PinPuPdControl; //Possible pull up/ pull down modes @GPIO_PULLUP_PULLDOWN_CONTROL
	uint8_t GPIO_PinOPType; //Possible output modes @GPIO_PIN_OUTPUTMODES
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConf_t;


//Handle struct of the GPIO single pin
typedef struct
{
	GPIO_RegDef_t* pGPIOx;	//Reference to certain GPIOx Port register address
	GPIO_PinConf_t GPIO_PinConfig; //COnfiguration of the GPIO Pin that is pointed on

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBER
 * GPIO possible pin numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_INPUT		0
#define GPIO_MODE_OUTPUT	1
#define GPIO_MODE_ALTFUN	2
#define GPIO_MODE_ANALOG	3

//interrupt modes
#define GPIO_MODE_IT_FT 	4
#define GPIO_MODE_IT_RT 	5
#define GPIO_MODE_IT_RFT 	6

/*
 * @GPIO_PIN_OUTPUTMODES
 * GPIO pin output modes
 */
#define GPIO_OUTPUT_PP		0
#define GPIO_OUTPUT_OD		1

/*
 * @GPIO_SPEED_MODES
 *GPIO Speed modes
 */
#define GPIO_SPEED_LS		0
#define GPIO_SPEED_MS		1
#define GPIO_SPEED_HS		2
#define GPIO_SPEED_VHS		3

/*
 * @GPIO_PULLUP_PULLDOWN_CONTROL
 * GPIO Pull down pull up modes
 */
#define GPIO_PULLUPDOWN_NOPUPD			0
#define GPIO_PULLUPDOWN_PU				1
#define GPIO_PULLUPDOWN_PD				2

/*
 * Alternative function modes
 */
#define GPIO_AF_0	0
#define GPIO_AF_1	1
#define GPIO_AF_2	2
#define GPIO_AF_3	3
#define GPIO_AF_4	4
#define GPIO_AF_5	5
#define GPIO_AF_6	6
#define GPIO_AF_7	7
#define GPIO_AF_8	8
#define GPIO_AF_9	9
#define GPIO_AF_10	10
#define GPIO_AF_11	11
#define GPIO_AF_12	12
#define GPIO_AF_13	13
#define GPIO_AF_14	14
#define GPIO_AF_15	15




//Declaring the GPIO API's (Methods) to manage the behavior of the PIN/Entire PORT
//Init and deinit of GPIO Port and RCC
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t ENorDI);

void GPIO_Init(GPIO_Handle_t* pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);


//Configuration of the input
uint8_t GPIO_ReadFromPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber);
uint16_t GPIO_ReadFromPort(GPIO_RegDef_t* pGPIOx);

//Configuration of the output
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber, uint8_t value);
void GRIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value);

//Toggle config
void GPIOToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber);

//Interrupt configuration and handling
void IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t ENorDI);
void IRGHandling(uint8_t pinNumber);



#endif /* INC_STM32F407_GPIO_DRIVER_H_ */
