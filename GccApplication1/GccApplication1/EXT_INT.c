/*
 * EXT_INT.c
 *
 * Created: 9/21/2022 12:29:25 PM
 *  Author: AMIT
 */ 

#include "EXT_INT.h"

void INT0_Init(void)
{
	/*Global & Peripherals Enable/ Disable*/
	SREG |= Global_INT << 7;
	GICR |= EXT0_INT << 6;
	
	/*INT0 pin Direction*/
	DIO_SetPin_Dir(DIO_PORTD, PIN_2, PIN_IN);
	
	/*EXT INT0 Trigger*/
	MCUCR |= EXT_INT0_Trigger; 
}
void INT1_Init(void)
{
	/*Global & Peripherals Enable/ Disable*/
	SREG |= Global_INT << 7;
	GICR |= EXT1_INT << 7;
	
	/*INT1 pin Direction*/
	DIO_SetPin_Dir(DIO_PORTD, PIN_3, PIN_IN);
	
	/*EXT INT1 Trigger*/
	MCUCR |= EXT_INT1_Trigger;
}
void INT2_Init(void)
{
	/*Global & Peripherals Enable/ Disable*/
	SREG |= Global_INT << 7;
	GICR |= EXT2_INT << 5;
	
	/*INT0 pin Direction*/
	DIO_SetPin_Dir(DIO_PORTB, PIN_2, PIN_IN);
	
	/*EXT INT2 Trigger*/
	MCUCR |= EXT_INT2_Trigger;
}