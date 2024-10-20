/****************************************************************************************************
 * 	FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------
 *  File:			lcd.h
 *
 *  DESCRIPTION:    implementation file for the LCD driver
 *
 *  -------------------------------------------------------------------------------------------------
 *  Author: 		Mohamed_Ayman
 ***************************************************************************************************/

#include"LCD.h"

void my_wait1(uint32_t time)
{
	uint32_t i, j;
	for(i = 0; i< time; i++)
		for(j =0; j < 255; j++);
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */

GPIO_PINConfig_t pinCfig;

void IntLCD(void)
{
	my_wait1(20);

	/* 1- Configure the Enable and RS as output ports */
	pinCfig.GPIO_PinNumber = LCD_RS_PIN_ID; // RS
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = LCD_E_PIN_ID;// Enable
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	my_wait1(15);

#if(LCD_BIT_MODE == 8)
	/* 2 - Configure the data portA as output port with speed 10MHz */
	//GPIO_SetPortDirection(LCD_DATA_PORT_ID, 0xff);
	pinCfig.GPIO_PinNumber = GPIO_PIN_0;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_1;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_2;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);
	pinCfig.GPIO_PinNumber = GPIO_PIN_3;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_4;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_5;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_6;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = GPIO_PIN_7;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	//Clear the LCD
	LCD_clearScreen();

	/* 3 - LCD Power ON delay always > 15ms */


	/* 4 - send command 2 lines 8 bits*/
	LCD_Sendcommand(LCD_TWO_LINES_8_MODE);

#elif(LCD_BIT_MODE == 4)

	/* 2 - Configure the data pins as output port */
	pinCfig.GPIO_PinNumber = LCD_DATA_PIN0_ID;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = LCD_DATA_PIN1_ID;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = LCD_DATA_PIN2_ID;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);

	pinCfig.GPIO_PinNumber = LCD_DATA_PIN3_ID;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinCfig);


	/* 3 - LCD Power ON delay always > 15ms */


	/* 3.2 - send commands 0x33 0x32 0x28 to init lcd*/
//	LCD_Sendcommand(LCD_TWO_LINES_4_BITS_MODE_INIT1);
//	LCD_Sendcommand(LCD_TWO_LINES_4_BITS_MODE_INIT2);
	LCD_Sendcommand(LCD_GO_TO_HOME);
	LCD_Sendcommand(LCD_TWO_lines_4_mode);
#endif


	/* 5 - send command cursor off*/
	LCD_Sendcommand(LCD_CURSOR_BLINK);

	/* 6 - send command clear screen */
	LCD_Sendcommand(LCD_CLEAR_SCREEN);

}


/*
 * Description :
 * Send the required command to the screen
 */
void LCD_Sendcommand(uint8_t command)
{
	/* 1 - Clear RS */
	MCAL_GPIO_WritePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, 0);

	/* 2 - delay for tas*/
	my_wait1(1);

	/* 3 - set enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);

	/* 4 - delay for 1us*/
	my_wait1(1);

#if(LCD_BIT_MODE == 8)

	/* 5 - send our command */
	MCAL_GPIO_WritePort(LCD_DATA_PORT_ID, command);

	/* 6 - delay for 1us*/
	my_wait1(1);

	/* 7 - clear enable*/
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);

	/* 8 - delay 1us*/
	my_wait1(1);

#elif(LCD_BIT_MODE == 4)

	/* 5 - send the 4 MSBs of command*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN0_ID,GET_BIT(command,4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN1_ID,GET_BIT(command,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN2_ID,GET_BIT(command,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN3_ID,GET_BIT(command,7));
	my_wait1(1);

	/* 5.1 - clear enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);

	/* 5.2 - delay for 1us*/
	my_wait1(1);

	/* 6.1 - set enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);

	/* 6.2 - delay for 1us*/
	my_wait1(1);

	/* 6.3 - send the 4 LSBs of command*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN0_ID,GET_BIT(command,0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN1_ID,GET_BIT(command,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN2_ID,GET_BIT(command,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN3_ID,GET_BIT(command,3));
	my_wait1(1);

	/* 7 - clear enable*/
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);

	/* 8 - delay 1us*/
	my_wait1(1);

#endif


}

/*
 * Description :
 * Send the required data to the screen
 */
void LCD_displayCharacter(uint8_t data)
{
	/* 1 - set RS */
	MCAL_GPIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,1);

	/* 2 - delay for tas*/
	my_wait1(1);

	/* 3 - set enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);

	/* 4 - delay for 1us*/
	my_wait1(1);

#if(LCD_BIT_MODE == 8)

	/* 5 - send our command */
	MCAL_GPIO_WritePort(LCD_DATA_PORT_ID,data);

	/* 6 - delay for 1us*/
	my_wait1(1);

#elif(LCD_BIT_MODE == 4)

	/* 5 - send the 4 MSBs of command*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN0_ID,GET_BIT(data,4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN1_ID,GET_BIT(data,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN2_ID,GET_BIT(data,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN3_ID,GET_BIT(data,7));
	my_wait1(1);

	/* 5.1 - clear enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);

	/* 5.2 - delay for 1us*/
	my_wait1(1);

	/* 6.1 - set enable */
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);

	/* 6.2 - delay for 1us*/
	my_wait1(1);

	/* 6.3 - send the 4 LSBs of command*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN0_ID,GET_BIT(data,0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN1_ID,GET_BIT(data,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN2_ID,GET_BIT(data,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT_ID,LCD_DATA_PIN3_ID,GET_BIT(data,3));
	my_wait1(1);

#endif

	/* 7 - clear enable*/
	MCAL_GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);

	/* 8 - delay 1us*/
	my_wait1(1);
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const uint8_t *str)
{
	uint8_t i;
	for(i=0;str[i]!='\0';i++)
		LCD_displayCharacter(str[i]);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integerToString(uint32_t data)
{
	char arr[16];

	/* store the integer number to arr & 10 is for decimal numbering system*/
	itoa(data,arr,10);

	LCD_displayString(arr);
}

/*
 * Description :
 * A function which change the cursor position according to given row and column
 */
void LCD_moveCursor(uint8_t row, uint8_t column)
{
	/* first row position is 0x00 + column
	 * second row position is 0x040 + column
	 * third row position is 0x01 + column
	 * fourth row position is 0x50 + column
	 * and then we should set the MSB of position by
	 * or it with 0b10000000 which is 0x80
	 */
	uint8_t position;
	switch(row)
	{
	case 0 :
		position=0x00+column;
		break;
	case 1 :
		position=0x40+column;
		break;
	case 2 :
		position=0x10+column;
		break;
	case 3 :
		position=0x40+column;
		break;
	}
	LCD_Sendcommand(position|LCD_CURSOR_FIRST_LINE);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str)
{
	/*Move cursor to that position*/
	LCD_moveCursor(row,col);

	/* Display the string*/
	LCD_displayString(Str);
}

/*
 * Description :
 * remove the text displayed on the screen
 */
void LCD_clearScreen()
{
	LCD_Sendcommand(LCD_CLEAR_SCREEN);
}
