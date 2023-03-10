/*
 * LED.c
 *
 * Created: 9/8/2022 1:55:21 PM
 *  Author: Dell
 */ 
#include "LED.h"

/*---------------LED0--------------*/
void LED0_Init(void)
{
	DIO_SetPin_Dir(LED0_Port, LED0_Pin, PIN_OUT);
	DIO_SetPin_Value(LED0_Port, LED0_Pin, PIN_OFF);
}

void LED0_ON(void)
{
	DIO_SetPin_Value(LED0_Port, LED0_Pin, PIN_ON);
}
void LED0_OFF(void)
{
	DIO_SetPin_Value(LED0_Port, LED0_Pin, PIN_OFF);
}

void LED0_Toggle(void)
{
	DIO_TogglePin_Value(LED0_Port, LED0_Pin);
}

/*---------------LED1--------------*/
void LED1_Init(void)
{
	DIO_SetPin_Dir(LED1_Port, LED1_Pin, PIN_OUT);
	DIO_SetPin_Value(LED1_Port, LED1_Pin, PIN_OFF);
}

void LED1_ON(void)
{
	DIO_SetPin_Value(LED1_Port, LED1_Pin, PIN_ON);
}
void LED1_OFF(void)
{
	DIO_SetPin_Value(LED1_Port, LED1_Pin, PIN_OFF);
}

void LED1_Toggle(void)
{
	DIO_TogglePin_Value(LED1_Port, LED1_Pin);
}

/*---------------LED2--------------*/
void LED2_Init(void)
{
	DIO_SetPin_Dir(LED2_Port, LED2_Pin, PIN_OUT);
	DIO_SetPin_Value(LED2_Port, LED2_Pin, PIN_OFF);
}

void LED2_ON(void)
{
	DIO_SetPin_Value(LED2_Port, LED2_Pin, PIN_ON);
}
void LED2_OFF(void)
{
	DIO_SetPin_Value(LED2_Port, LED2_Pin, PIN_OFF);
}

void LED2_Toggle(void)
{
	DIO_TogglePin_Value(LED2_Port, LED2_Pin);
}
