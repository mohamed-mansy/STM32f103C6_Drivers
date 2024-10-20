/*
 * Keypad.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Administrator
 */

#include "Keypad.h"

#define F_CPU 	1000000UL

int Keypad_Row[] = {R0, R1, R2, R3};
int Keypad_Column[] = {C0, C1, C2, C3};

void Keypad_Init()
{
	//make all Rows input
	//Keypad_Direction &= ~(1 << R0) | (1 << R1) | (1 << R2) | (1 << R3);

	//PA1 High-Z (floating) input
	pinCfig.GPIO_PinNumber = R0;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = R1;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = R2;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = R3;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = C0;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = C1;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = C2;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	pinCfig.GPIO_PinNumber = C3;
	pinCfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinCfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(keypad_port, &pinCfig);

	//make all columns output
	//Keypad_Direction |= (1 << C4) | (1 << C5) | (1 << C6) | (1 << C7);


	MCAL_GPIO_WritePort(keypad_port, 0xFF);
}

char KeypadPressed()
{
	int i, j;
	//i for column and j for row
	for(i = 0; i < 4; i++)
	{
		//keypad_port |= (1 << Keypad_Column[0]) | (1 << Keypad_Column[1]) | (1 << Keypad_Column[2]) | (1 << Keypad_Column[3]);
		MCAL_GPIO_WritePin(keypad_port, Keypad_Column[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(keypad_port, Keypad_Column[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(keypad_port, Keypad_Column[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(keypad_port, Keypad_Column[3], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(keypad_port, Keypad_Column[i], GPIO_PIN_RESET);
		//keypad_port &= ~(1 << Keypad_Column[i]);

		for(j = 0; j < 4; j++)
		{
			if((MCAL_GPIO_ReadPin(keypad_port, Keypad_Row[j]) == 0)) // check if key is pressed
			{
				while((MCAL_GPIO_ReadPin(keypad_port, Keypad_Row[j]) == 0)) //wait for to be released (single press)
					switch(i)
					{
					case 0:
					{
						if(j == 0) return '7';
						if(j == 1) return '4';
						if(j == 2) return '1';
						if(j == 3) return '?';
						break;
					}
					case 1:
					{
						if(j == 0) return '8';
						if(j == 1) return '5';
						if(j == 2) return '2';
						if(j == 3) return '0';
						break;
					}
					case 2:
					{
						if(j == 0) return '9';
						if(j == 1) return '6';
						if(j == 2) return '3';
						if(j == 3) return '=';
						break;
					}
					case 3:
					{
						if(j == 0) return '/';
						if(j == 1) return '*';
						if(j == 2) return '-';
						if(j == 3) return '+';
						break;
					}


					}
			}
		}
	}

	return 'A' ; // Return A if no key is pressed
}
