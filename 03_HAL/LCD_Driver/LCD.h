/****************************************************************************************************
 * 	FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------
 *  File:			lcd.h
 *
 *  DESCRIPTION:    Header file for the LCD driver
 *
 *  -------------------------------------------------------------------------------------------------
 *  Author: 		Mohamed_Ayman
 ***************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "stdint.h"
#include "stm32f103x8.h"
#include "stm32f103c6_GPIO_driver.h"

/****************************************************************************************************
 *											Definitions
 ***************************************************************************************************/

#define GET_BIT(REG , BIT) 		((REG >> BIT) & 1)

#define LCD_BIT_MODE       		4

#define LCD_RS_PORT_ID          GPIOA
#define LCD_RS_PIN_ID			GPIO_PIN_8

#define LCD_E_PORT_ID			GPIOA
#define LCD_E_PIN_ID			GPIO_PIN_9

#if(LCD_BIT_MODE == 4)
#define LCD_DATA_PORT_ID		GPIOA
#define LCD_DATA_PIN0_ID		GPIO_PIN_4
#define LCD_DATA_PIN1_ID		GPIO_PIN_5
#define LCD_DATA_PIN2_ID		GPIO_PIN_6
#define LCD_DATA_PIN3_ID		GPIO_PIN_7

#elif(LCD_BIT_MODE == 8)
#define LCD_DATA_PORT_ID		GPIOA
#endif


/*LCD commands */
#define LCD_CLEAR_SCREEN 				0x01
#define LCD_GO_TO_HOME 					0x02
#define LCD_TWO_LINES_8_MODE 			0x38
#define LCD_TWO_lines_4_mode 			0x28
#define LCD_CURSOR_OFF 					0x0C
#define LCD_CURSOR_on 					0x0E
#define LCD_CURSOR_BLINK 				0x0F
#define LCD_TWO_LINES_4_BITS_MODE_INIT1	0x33
#define LCD_TWO_LINES_4_BITS_MODE_INIT2	0x32
#define LCD_CURSOR_FIRST_LINE			0x80
#define LCD_CURSOR_SECOND_LINE			0xc0

/****************************************************************************************************
 *											Functions
 ***************************************************************************************************/

void LCD_Sendcommand(uint8_t command);

/*before used while(1) write this function */
void IntLCD(void);

void LCD_displayCharacter(uint8_t data);

void LCD_displayString(const uint8_t *Str);

void LCD_integerToString(uint32_t Data);

void LCD_clearScreen(void);

void LCD_MoveCursor(uint8_t Row , uint8_t Col);

void LCD_displayStringRowColumn(uint8_t Row , uint8_t Col , const uint8_t* Str);

#endif
