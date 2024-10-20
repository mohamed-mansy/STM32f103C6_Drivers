/****************************************************************************************************
 * 	FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------
 *  File:			common_macro.h
 *
 *  DESCRIPTION:    Bit manipulation
 *
 *  -------------------------------------------------------------------------------------------------
 *  Author: 		Mohamed_Ayman
 ***************************************************************************************************/

#ifndef COMMON_MACRO_H_
#define COMMON_MACRO_H_

#define SET_BIT(REG , BIT) (REG) |=(1 << BIT)

#define CLEAR_BIT(REG , BIT) (REG) &=~(1 << BIT)

#define TOGGLE_BIT(REG , BIT) (REG) ^=(1 << BIT)

#define GET_BIT(REG , BIT) ((REG >> BIT) & 1)

#define BIT_IS_SET(REG , BIT) (REG & (1 << BIT))

#define BIT_IS_CLEAR(REG , BIT) (!(REG & (1 << BIT)))

#define GET_BIT2(REG , BIT) ((REG & (1 << BIT)) >> BIT)


#endif /* COMMON_MACRO_H_ */
