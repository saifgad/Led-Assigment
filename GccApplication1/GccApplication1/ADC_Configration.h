/*
 * ADC_Configration.h
 *
 * Created: 9/22/2022 11:42:59 AM
 *  Author: lenovo
 */ 


#ifndef ADC_CONFIGRATION_H_
#define ADC_CONFIGRATION_H_

#include "DIO.h"
#include "Interrupts.h"

/* ADC Voltages References*/
#define ADC_Voltage_Ref				AVCC

/* ADC Prescaler*/
#define ADC_CLK						CLK_128		

/*ADC Right\Left Adjust*/
#define ADC_Data_Presentation		ADC_Right_Adjust

/* ADC Conversion Mode*/
#define ADC_Conv_Mode				Auto_Triggered_Mode
/* ADC Auto triggered Type*/
#define ADC_Auto_Triggered_Mode		Free_Runnig_Mode
	
#endif /* ADC_CONFIGRATION_H_ */