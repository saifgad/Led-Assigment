/*
 * GccApplication1.c
 *
 * Created: 2/11/2023 10:57:07 AM
 * Author : lenovo
 */ 

#define  F_CPU 16000000
#include <util/delay.h>
#include "ADC.h"
#include "DIO.h"
#include "Timer.h"
#include "LED.h"
int main(void)
{
	ADC_Init();
	Timer0_Init();
	LED0_Init();
	LED1_Init();
	LED2_Init();
	extern Uint16 x;
	Timer0_Start();
	Timer0_SetDelay(500);
	
    /* Replace with your application code */
    while (1) 
    {
	if (x==1)
	{
		LED0_Toggle();
	}
	if (x==2)
	{
		LED1_Toggle();
	}
	if (x==3)
	{
		LED2_Toggle();
	}
	}
}

