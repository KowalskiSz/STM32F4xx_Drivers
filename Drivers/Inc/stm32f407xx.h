#include "STM32F407_GPIO_Driver.h"
#include "STM32F407_SPI_Driver.h"
#include <stdint.h>


/*
 * Processor specific macros
 */

//ARM CORTEX-M4 NVIC ISER register addresses
#define NVIC_ISER0	((uint32_t*)0xE000E100)
#define NVIC_ISER1	((uint32_t*)0xE000E104)
#define NVIC_ISER2	((uint32_t*)0xE000E108)
#define NVIC_ISER3	((uint32_t*)0xE000E10C)

//ARM CORTEX-M4 NVIC ICER register addresses
#define NVIC_ICER0	((uint32_t*)0XE000E180)
#define NVIC_ICER1	((uint32_t*)0XE000E184)
#define NVIC_ICER2	((uint32_t*)0XE000E188)
#define NVIC_ICER3	((uint32_t*)0XE000E18C)

#define NVIC_PR_REG	((uint32_t*)0xE000E400)

/*
 * Driver file containing all the necessary MCU registers and other memory locations
 */
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#define voilate __vo
//Base addresses of the FLASH and RAM Memory of the MCU
#define FLASH_BASEADDR	0x08000000U
#define SRAM1_BASEADDR	0x20000000U
#define SRAM SRAM1_BASEADDR //SRAM1 is a main SRAM memory of the MCU
//#define SRAM3 0x20020000U
#define ROM 0x1FFF0000U //System memory

//define base addreses of the BUS Registers
#define PERIPH_BASE 0x40000000U
#define APB1_BASEADDR PERIPH_BASE
#define APB2_BASEADDR 0x40010000U
#define AHB1_BASEADDR 0x40020000U
#define AHB2_BASEADDR 0x50000000U

//Base addresses of desire peripherials on AHB1
#define GPIOA_BASEADDR (AHB1_BASEADDR + 0x0000)
#define GPIOB_BASEADDR (AHB1_BASEADDR + 0x0400)
#define GPIOC_BASEADDR (AHB1_BASEADDR + 0x0800)
#define GPIOD_BASEADDR (AHB1_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR (AHB1_BASEADDR + 0x1000)
#define GPIOF_BASEADDR (AHB1_BASEADDR + 0x1400)
#define GPIOG_BASEADDR (AHB1_BASEADDR + 0x1800)
#define GPIOH_BASEADDR (AHB1_BASEADDR + 0x1C00)
#define RCC_BASEADDR (AHB1_BASEADDR + 0x3800)


//Base addresses of desire peripherials on APB1
#define I2C_1_BASEADDR (APB1_BASEADDR + 0x5400)
#define I2C_2_BASEADDR (APB1_BASEADDR + 0x5800)
#define I2C_3_BASEADDR (APB1_BASEADDR + 0x5C00)

#define SPI_2_BASEADDR (APB1_BASEADDR + 0x3800)
#define SPI_3_BASEADDR (APB1_BASEADDR + 0x3C00)

//Base addresses of desire peripherials on APB2
#define SPI_1_BASEADDR (APB2_BASEADDR + 0x3000)
#define EXTI_BASEADDR (APB2_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR (APB2_BASEADDR + 0x3800)


//Peripherial registers definition structures - describe all the available registers to set the behavior of the peripherials

typedef struct
{
	uint32_t volatile SPI_CR1;
	uint32_t volatile SPI_CR2;
	uint32_t volatile SPI_SR;
	uint32_t volatile SPI_DR;
	uint32_t volatile SPI_CRCPR;
	uint32_t volatile SPI_RXCRCR;
	uint32_t volatile SPI_TXCRCR;
	uint32_t volatile SPI_I2SCFGR;
	uint32_t volatile SPI_I2SPR;
}SPI_RegDef_t;


typedef struct
{
	uint32_t MODER; //GPIO port mode register
	uint32_t OTYPER; //GPIO port output type register
	uint32_t OSPEEDR; //GPIO port output speed register
	uint32_t PUPDR; //GPIO port pull-up/pull-down register
	uint32_t IDR; //GPIO port input data register
	uint32_t ODR; //GPIO port output data register
	uint32_t BSRR; //GPIO port bit set/reset register
	uint32_t LCKR; //GPIO port configuration lock register
	uint32_t AFRL; //GPIO alternate function low register
	uint32_t AFRH; //GPIO alternate function high register
}GPIO_RegDef_t;


typedef struct
{
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;
}EXTI_RegDef_t;


typedef struct
{
	uint32_t MEMRMP;
	uint32_t PMC;
	uint32_t EXTICR[4];
	uint32_t CMPCR;
}SYSCFG_RegDef_t;


typedef struct
{
	uint32_t RCC_CR;
	uint32_t RCC_PLLCFGR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_AHB1RSTR;
	uint32_t RCC_AHB2RSTR;
	uint32_t RCC_AHB3RSTR;
	uint32_t Reserved_1;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_APB2RSTR;
	uint32_t Reserved_2;
	uint32_t Reserved_3;
	uint32_t RCC_AHB1ENR;
	uint32_t RCC_AHB2ENR;
	uint32_t RCC_AHB3ENR;
	uint32_t Reserved_4;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_APB2ENR;
	uint32_t Reserved_5;
	uint32_t Reserved_6;
	uint32_t RCC_AHB1LPENR;
	uint32_t RCC_AHB2LPENR;
	uint32_t RCC_AHB3LPENR;
	uint32_t Reserved_7;
	uint32_t RCC_APB1LPENR;
	uint32_t RCC_APB2LPENR;
	uint32_t Reserved_8;
	uint32_t Reserved_9;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
	uint32_t Reserved_10;
	uint32_t Reserved_11;
	uint32_t RCC_SSCGR;
	uint32_t RCC_PLLI2SCFGR;
}RCC_RegDef_t;

//Peripherials definition - ready to use
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)

//Peripherial definition -> SPI
#define SPI1	((SPI_RegDef_t*)SPI_1_BASEADDR)
#define SPI2	((SPI_RegDef_t*)SPI_2_BASEADDR)
#define SPI3	((SPI_RegDef_t*)SPI_3_BASEADDR)

//Clock register defnition
#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)

//EXTI register definition
#define EXTI ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

//Enablign the GPIOx macros
#define GPIOA_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 0)
#define GPIOB_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 1)
#define GPIOC_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 2)
#define GPIOD_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 3)
#define GPIOE_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 4)
#define GPIOF_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 5)
#define GPIOG_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 6)
#define GPIOH_RCLK_EN() RCC->RCC_AHB1ENR |= (1 << 7)

//Enablign the I2C macros
#define I2C_1_RCLK_EN() (RCC->RCC_APB1ENR |= (1 << 21))
#define I2C_2_RCLK_EN() (RCC->RCC_APB1ENR |= (1 << 22))
#define I2C_3_RCLK_EN() (RCC->RCC_APB1ENR |= (1 << 23))

//Enablign the SPI macros
#define SPI_1_RCLK_EN() (RCC->RCC_APB2ENR |= (1 << 12))
#define SPI_2_RCLK_EN() (RCC->RCC_APB1ENR |= (1 << 14))
#define SPI_3_RCLK_EN() (RCC->RCC_APB1ENR |= (1 << 15))

//Enablign the SYSCFG macros
#define SYSCFG_RCLK_EN() (RCC->RCC_APB2ENR |= (1 << 14))


//Disabling the GPIOx Macros
#define GPIOA_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 0)
#define GPIOB_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 1)
#define GPIOC_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 2)
#define GPIOD_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 3)
#define GPIOE_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 4)
#define GPIOF_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 5)
#define GPIOG_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 6)
#define GPIOH_RCLK_DI() RCC->RCC_AHB1ENR &= ~(1 << 7)

//Disabling the I2C macros
#define I2C_1_RCLK_DI() (RCC->RCC_APB1ENR &= ~(1 << 21))
#define I2C_2_RCLK_DI() (RCC->RCC_APB1ENR &= ~(1 << 22))
#define I2C_3_RCLK_DI() (RCC->RCC_APB1ENR &= ~(1 << 23))

//Disabling the SPI macros
#define SPI_1_RCLK_DI() (RCC->RCC_APB2ENR &= ~(1 << 12))
#define SPI_2_RCLK_DI() (RCC->RCC_APB1ENR &= ~(1 << 14))
#define SPI_3_RCLK_DI() (RCC->RCC_APB1ENR &= ~(1 << 15))

//Disabling the SYSCFG macros
#define SYSCFG_RCLK_DI() (RCC->RCC_APB2ENR &= ~(1 << 14))

/*
 * Macros to RESET the GPIO peripherials (A - H)
 */
#define GPIOA_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 0)); (RCC->RCC_AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 1)); (RCC->RCC_AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 2)); (RCC->RCC_AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 3)); (RCC->RCC_AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 4)); (RCC->RCC_AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 5)); (RCC->RCC_AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 6)); (RCC->RCC_AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET() 	do {(RCC->RCC_AHB1RSTR |= (1 << 7)); (RCC->RCC_AHB1RSTR &= ~(1 << 7));}while(0)

//Generic macros
#define ENABLE 1
#define DISABLE 0

#define SET ENABLE
#define RESET DISABLE

//IRQ (interrupt request number -> define according to vector table)
#define IRQ_EXTI0	6
#define IRQ_EXTI1	7
#define IRQ_EXTI2	8
#define IRQ_EXTI3	9
#define IRQ_EXTI4	10
#define IRQ_EXTI9_5	23
#define IRQ_EXTI10_15	40

//Number of priority bits in Priorty register according to ARM CORTEX CPU
#define NO_BITS_IMPLEMENTED 4
















#endif /* INC_STM32F407XX_H_ */
