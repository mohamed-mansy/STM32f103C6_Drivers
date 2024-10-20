/*
 * SevenSegment.h
 *
 *  Created on: Oct 19, 2024
 *      Author: Administrator
 */

#ifndef SevenSegment_H_
#define SevenSegment_H_

#include "stm32f103x8.h"
#include "stm32f103c6_GPIO_driver.h"

#define Seven_Segment_Port			GPIOB
#define Seven_SEGMENT_PIN0			GPIO_PIN_9
#define Seven_SEGMENT_PIN1			GPIO_PIN_10
#define Seven_SEGMENT_PIN2			GPIO_PIN_11
#define Seven_SEGMENT_PIN3			GPIO_PIN_12
#define Seven_SEGMENT_PIN4			GPIO_PIN_13
#define Seven_SEGMENT_PIN5			GPIO_PIN_14
#define Seven_SEGMENT_PIN6			GPIO_PIN_15


//7segment
#define ZERO		0x01
#define ONE			0x79
#define TWO			0x24
#define There		0x30
#define Four		0x4C
#define FIVE		0x12
#define SIX			0x02
#define SEVEN		0x19
#define EIGHT		0x00
#define NINE		0x10



#endif /* 7SEGMENT_SEVENSEGMENT_H_ */
