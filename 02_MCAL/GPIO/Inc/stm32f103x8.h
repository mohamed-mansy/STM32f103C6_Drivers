/*
 * stm32f103x8.h
 *
 *  Created on: Oct 12, 2024
 *      Author: Administrator
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_
//Device Header //

//---------------------------
//Includes
//---------------------------

#include <stdlib.h>
#include "stdint.h"

//---------------------------
//Base addresses for Memories
//---------------------------

#define FlashMemory_Base			0x08000000UL
#define SystemMemory_Base			0x1ffff000UL
#define SRAM_Base					0x20000000UL

#define peripherals_Base			0x40000000UL

#define CortexM3_peripherals_Base	0xE0000000UL

//---------------------------
//Base addresses for AHB peripherals
//---------------------------

//RCC
#define RCC_Base		0x40021000UL
//#define RCC	(peripherals_Base +	0x00021000UL)

//---------------------------
//Base addresses for APB2 peripherals
//---------------------------

//GPIO
//A,B fully included in lQFP48 Package
#define GPIOA_Base		0x40010800UL
#define GPIOB_Base		0x40010C00UL

//C,D partial included in lQFP48 Package
#define GPIOC_Base		0x40011000UL
#define GPIOD_Base		0x40011400UL

//E not included in lQFP48 Package
#define GPIOE_Base		0x40018000UL
//-----------------------------------

//EXTI
#define EXTI_Base		0x40010400UL

//AFIO
#define AFIO_Base		0x40010000UL

//---------------------------
//Base addresses for APB1 peripherals
//---------------------------

//------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
}RCC_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_Typedef;
//-----------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//peripheral Instants:-
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// GPIO_Typedef *GPIOA = (GPIO_Typedef*)GPIOA_Base

#define GPIOA		((GPIO_Typedef*)GPIOA_Base)
#define GPIOB		((GPIO_Typedef*)GPIOB_Base)
#define GPIOC		((GPIO_Typedef*)GPIOC_Base)
#define GPIOD		((GPIO_Typedef*)GPIOD_Base)
#define GPIOE		((GPIO_Typedef*)GPIOE_Base)

#define RCC 		((RCC_Typedef*)RCC_Base)

#define EXTI 		((EXTI_Typedef*)EXTI_Base)

#define AFIO		((AFIO_Typedef*)AFIO_Base)
//-----------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Clock enable Macros:-
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1 << 2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1 << 3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1 << 4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1 << 5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1 << 6)

//AFIO
#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1 << 0)


#endif /* INC_STM32F103X8_H_ */
