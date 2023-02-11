/*
 * Timer_Configration.h
 *
 * Created: 9/23/2022 8:01:20 PM
 *  Author: Saif Mohamed
 */ 


#ifndef TIMER_CONFIGRATION_H_
#define TIMER_CONFIGRATION_H_

#include "DIO.h"
#include "Interrupts.h"
#define MC_Freq_Mhz			16
/*Timer0 Mode*/
#define Timer0_Mode			Timer0_OVF				
#define Timer0_CLK			Timer0_Freq_1024
#define Timer0_Freq_Divder	Timer0__Freq_Div_1024
#define F_OC0_Mode			F_OC0_C_Comp_S_Top  
#define P_OC0_Mode			P_OC0_C_CompU_S_CompD
/*Timer1 Mode*/
#define Timer1_Mode			Timer1_CTC
#define Timer1_CLK			Timer1_Freq_1024
#define Timer1_Freq_Divder	Timer1__Freq_Div_1
#define F_OC1A_Mode			F_OC1A_C_Comp_S_Top
#define F_OC1B_Mode			F_OC1B_C_Comp_S_Top
#define P_OC1A_Mode			P_OC1A_C_CompU_S_CompD
#define P_OC1B_Mode			P_OC1B_C_CompU_S_CompD
/*Timer2 Mode*/
#define Timer2_Mode		    Timer2_CTC
#define Timer2_CLK			Timer2__Freq_1024
#define Timer2_Freq_Divder	Timer2__Freq_Div_1024
#define F_OC2_Mode			F_OC2_C_Comp_S_Top
#define P_OC2_Mode			P_OC2_C_CompU_S_CompD 

#endif /* TIMER_CONFIGRATION_H_ */
