/*
 * stm32f103c6_GPIO_driver.c
 *
 *      Author: Mohamed_Ayman
 */

#include "stm32f103c6_GPIO_driver.h"


/*==================================================================================================
 * @Fn 				-Get_CRLH_Position
 * @brief 			-get the position number pin in register
 * @param [in ]			-PinNumber: select pin from register from 0 >>> 15 @ref GPIO_PINS_define
 * @param [out ]		-NONE
 * @retval 			-return the position pin number
 * Note 			-NONE
 *==================================================================================================
 */

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;

	}

	return 0;

}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_Init
 * @brief 			-Initializes the GPIOx PINy according to specified parameters in the PinConfig
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-PinConfig: pointer to a GPIO_PINConfig_t structure that contains
 * 				 the configuration information for the specified GPIO peripheral.
 * @param [out ]		-NONE
 * @retval 			-NONE
 * Note 			-stm32f103c6 MCU has GPIO A, B, C, D, E Modules
 * 					 But lQFP48 package has only GPIO A, B, part of C and D expected as external pins from the MCU
 *==================================================================================================
 */

void MCAL_GPIO_Init(GPIO_Typedef *GPIOx, GPIO_PINConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) configure PINS from 0 >>> 7
	//Port configuration register High (GPIOx_CRH) configure PINS from 8 >>> 15

	volatile uint32_t *configre_register = NULL;
	uint8_t pin_config = 0;

	configre_register = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH;

	//clear CNFy[1:0] MODEx[1:0]
	(*configre_register) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if pin is output
	if((PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP) ||
			(PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP))
	{
		//Set CNFy[1:0] MODEx[1:0]
		pin_config = (((PinConfig->GPIO_Mode - 4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0f;

	}
	// if pin is input
	else // mode = 00: Input mode (reset state)
	{
		if((PinConfig->GPIO_Mode == GPIO_MODE_Analog) || (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO))
		{
			//Set CNFy[1:0] MODEx[1:0]00
			pin_config = (((PinConfig->GPIO_Mode ) << 2) | (0X0)) & 0x0f;

		}
		else if((PinConfig->GPIO_Mode == GPIO_MODE_INPUT_AF))//consider it as input floating
		{
			pin_config = (((GPIO_MODE_INPUT_FLO ) << 2) | (0X0)) & 0x0f;
		}
		else // PU PD input
		{
			pin_config = (((GPIO_MODE_INPUT_PU ) << 2) | (0X0)) & 0x0f;

			if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
			{
				// PxODR = 1 Input pull-up Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				// PxODR = 0 Input pull-down Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}

	(*configre_register) |= (pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_DeInit
 * @brief 			-Reset all the GPIO Registers
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [out ]		-NONE
 * @retval 			-NONE
 * Note 			-NONE
 *==================================================================================================
 */

void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx)
{
	//	GPIOx->CRL = 0x44444444;
	//	GPIOx->CRH = 0x44444444;
	//	//GPIOx->IDR = Read_only;
	//	GPIOx->ODR = 0x00000000;
	//	GPIOx->BRR = 0x00000000;
	//	GPIOx->BSRR = 0x00000000;
	//	GPIOx->LCKR = 0x00000000;

	/*
	 * or you can use the reset controller
	 * APB2 peripheral reset register (RCC_APB2RSTR)
	 * set and cleared by software
	 */
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1 << 2); //Bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR &= ~(1 << 2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1 << 3); //Bit 3 IOPBRST: IO port B reset
		RCC->APB2RSTR &= ~(1 << 3);
	}

	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1 << 4); //Bit 4 IOPBRST: IO port C reset
		RCC->APB2RSTR &= ~(1 << 4);
	}

	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1 << 5); //Bit 5 IOPBRST: IO port D reset
		RCC->APB2RSTR &= ~(1 << 5);
	}

	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1 << 6); //Bit 6 IOPBRST: IO port E reset
		RCC->APB2RSTR &= ~(1 << 6);
	}

}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_ReadPin
 * @brief 			-Read specific PIN
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-PinNumber: set pin number according @ref GPIO_PINS_define
 * @param [out ]		-NONE
 * @retval 			-the input pin value (two values based on @ref GPIO_PIN_State)
 * Note 			-NONE
 *==================================================================================================
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx, uint16_t PinNumber)
{
	uint8_t bit_status;
	if(((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET )
	{
		bit_status = GPIO_PIN_SET;
	}
	else
	{
		bit_status = GPIO_PIN_RESET;
	}


	return bit_status;

}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_ReadPort
 * @brief 			-Read the input PORT
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [out ]		-NONE
 * @retval 			-the input port value
 * Note 			-NONE
 *==================================================================================================
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx)
{
	uint16_t port_value;

	port_value = (uint16_t)(GPIOx->IDR);

	return port_value;

}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_WritePin
 * @brief 			-Write on the specific pin
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-PinNumber: specifies (write) the port pin bit .Set by @ref GPIO_PIN_State
 * @param [in ]			-value: Pin value
 * @param [out ]		-NONE
 * @retval 			-NONE
 * Note 			-NONE
 *==================================================================================================
 */

void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx, uint16_t PinNumber, uint8_t value)
{
	if(value != GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= (PinNumber);
		//or

		//Port bit set/reset register (GPIOx_BSRR)

		/*Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Set the corresponding ODRx bit*/
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		/*Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit*/
		GPIOx->BRR = (uint32_t)PinNumber;
	}

}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_WritePort
 * @brief 			-Write on the output port
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-value: port value
 * @param [out ]		-NONE
 * @retval 			-NONE
 * Note 			-NONE
 *==================================================================================================
 */

void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx, uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_TogglePin
 * @brief 			-Toggle the specified GPIO pin
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-PinNumber: specifies the pin bit. set by @ref GPIO_PIN_State
 * @param [out ]		-NONE
 * @retval 			-NONE
 * Note 			-NONE
 *==================================================================================================
 */

void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (uint32_t)PinNumber;
}

/*==================================================================================================
 * @Fn 				-MCAL_GPIO_LockPin
 * @brief 			-The locking mechanism pin allow the IO configuration to be frozen
 * @param [in ]			-GPIOx: where x can be (A...E depending on device used) to select the GPIO peripheral
 * @param [in ]			-PinNumber: specifies the pin bit. set by @ref GPIO_PIN_State
 * @param [out ]		-NONE
 * @retval 			-OK if pin Config is locked or error if pin not locked defined @ref GPIO_lock_state
 * Note 			-NONE
 *==================================================================================================
 */


uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx , uint16_t PinNumber)
{
	/*Bit 16 LCKK[16]: Lock key
		This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
		0: Port configuration lock key not active
		1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
		LOCK key writing sequence:
		Write 1
		Write 0
		Write 1
		Read 0
		Read 1 (this read is optional but confirms that the lock is active)
		Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
		Any error in the lock sequence will abort the lock.
		Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
		These bits are read write but can only be written when the LCKK bit is 0.
		0: Port configuration not locked
		1: Port configuration locked.*/

	//Set LCKK[16]
	volatile uint32_t temp = (1<<16);
	//Set LCKy
	temp |= PinNumber;

	//	Write 1
	GPIOx->LCKR = temp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = temp;
	//	Read 0
	temp = GPIOx->LCKR;
	//	Read 1
	if( (uint32_t) (GPIOx->LCKR) & (1 << 16))
		return GPIO_lock_Enable;

	else
		return GPIO_lock_error;

}

