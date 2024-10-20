/*
 * Keypad.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Administrator
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "stm32f103x8.h"
#include "stm32f103c6_GPIO_driver.h"

#define keypad_port			GPIOB

GPIO_PINConfig_t pinCfig;

//Keypad information
#define R0	GPIO_PIN_0
#define R1	GPIO_PIN_1
#define R2	GPIO_PIN_3
#define R3	GPIO_PIN_4
#define C0	GPIO_PIN_5
#define C1	GPIO_PIN_6
#define C2	GPIO_PIN_7
#define C3	GPIO_PIN_8

//Functions

void Keypad_Init();

char KeypadPressed();



#endif /* HAL_KEYPAD_H_ */
