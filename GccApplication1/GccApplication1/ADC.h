/*
 * ADC.h
 *
 * Created: 9/22/2022 11:42:22 AM
 *  Author: lenovo
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ADC_Configration.h"
/* Voltage References */
#define AREF								0
#define AVCC								1
#define Reserved							2
#define Internal_2_56						3
/* Clock Sources*/
#define CLK_2								1
#define CLK_4								2
#define CLK_8								3
#define CLK_16								4
#define CLK_32								5
#define CLK_64								6
#define CLK_128								7
/*ADC Mode*/
#define Single_Conv_Mode					0
#define Auto_Triggered_Mode					1
/*Auto Triggered Modes */
#define Free_Runnig_Mode					0
#define Analog_Comprator					1
#define External_Interrupt_Request0			2
#define Timer_Counter0_Compare_Match		3
#define Timer_Counter0_Overflow				4
#define Timer_Counter1_Compare_Match_B		5
#define Timer_Counter1_Overflow				6
#define Timer_Counter1_Capture_Event		7
/* ADC LEFT\RIGHT Adjust Modes*/
#define ADC_Right_Adjust					0
#define ADC_Left_Adjust					    1
/*ADC PIN*/
#define ADC_PIN0							0
#define ADC_PIN1							1
#define ADC_PIN2							2
#define ADC_PIN3							3
#define ADC_PIN4							4
#define ADC_PIN5							5
#define ADC_PIN6							6
#define ADC_PIN7							7

void ADC_Init(void);
Uint16 ADC_Read(Uint8 Pin);
void ADC_Disable(void);

#endif /* ADC_H_ */