/*
 * ADC.c
 *
 * Created: 9/22/2022 11:43:33 AM
 *  Author: lenovo
 */ 
#include "ADC.h"
#include <avr/interrupt.h>
Uint16 intr;
extern Uint16 x;
void ADC_Init(void)
{
	/*Voltages References*/
	ADMUX= (ADC_Voltage_Ref<<6)|(ADMUX & 0X3F);
	/*ADC Right\Left Adjust*/
	ADMUX= (ADC_Data_Presentation<<5)|(ADMUX & 0XDF);
	/*ADC Modes*/
	ADCSRA=(ADC_Conv_Mode<<5)|(ADCSRA & 0XDF);
	/*ADC: Auto-Triggered Mode*/
	SFIOR=(ADC_Auto_Triggered_Mode<<5)|(SFIOR & 0X1F);
	/*ADC Clock*/
	ADCSRA=(ADC_CLK)|(ADCSRA & 0XF8);
	/*Global & Peripherals Enable\Disable*/
	SREG|=Global_INT<<7;
	ADCSRA=(ADC_INT<<3)|(ADCSRA & 0XF7);
	/*ADC Enable*/
	ADCSRA=(1<<7)|(ADCSRA & 0X7F);
}

Uint16 ADC_Read(Uint8 Pin)
{
	Uint16 value=0;
	ADMUX=Pin | (ADMUX & 0XE0);
	ADCSRA=(1<<6)|(ADCSRA & 0XBF);
	while(!Get_Bit(ADCSRA,4));
	value=ADCR;
	return value;	
}
void ADC_Disable(void)
{
	Clear_Bit(ADCSRA,7);
}
ISR(ADC_vect)
{
}