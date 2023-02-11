/*
 * Timer.c
 *
 * Created: 9/23/2022 8:00:38 PM
 *  Author: Saif Mohamed
 */ 
#include "Timer.h"
#include <avr/interrupt.h>
#include "LED.h"
Uint16 No_OVFs_0=0;
Uint16 x=0;
Uint8  Init_Val_0=0;
Uint16 No_OVFs_1_A=0;
Uint16 No_OVFs_1_B=0;
Uint8  Init_Val_1_A=0;
Uint8  Init_Val_1_B=0;
Uint16 No_OVFs_2=0;
Uint8  Init_Val_2=0;
 Uint16 Showed_Val;
Uint8 counter=0;
 Uint16 Showed_Val_1;
/*------------------------------------>Timer0<-----------------------------------------------*/

void Timer0_Init(void)
{
	/*Global Interrupts Enable/Disable*/
	SREG|= Global_INT<<7;
	/*Timer0 Modes*/
	#if Timer0_Mode==Timer0_OVF
	Clear_Bit(TCCR0,3);
	Clear_Bit(TCCR0,6);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer0_OVF_INT)|(TIMSK & 0XFE);
	#elif Timer0_Mode==Timer0_P_PWM
	Clear_Bit(TCCR0,3);
	Set_Bit(TCCR0,6);
	/*Phase Correct PWM Mode*/
	TCCR0=(F_OC0_Mode<<4)|(TCCR0 & 0XCF);
	DIO_SetPin_Dir(DIO_PORTB,PIN_3,PIN_OUT);
	#elif Timer0_Mode==Timer0_CTC
	Set_Bit(TCCR0,3);
	Clear_Bit(TCCR0,6);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer0_CTC_INT<<1)|(TIMSK & 0XFD);
	#elif Timer0_Mode==Timer0_F_PWM
	Set_Bit(TCCR0,6);
	Set_Bit(TCCR0,3);
	/*Fast PWM Mode*/
	TCCR0=(F_OC0_Mode<<4)|(TCCR0 & 0XCF);
	DIO_SetPin_Dir(DIO_PORTB,PIN_3,PIN_OUT);
#endif	
}
void Timer0_SetDelay(Uint32 delay_ms)
{
	Uint8 Tick_Time_us=0;
	Uint32 Tick_num=0;

	Tick_Time_us=Timer0_Freq_Divder / MC_Freq_Mhz;
	Tick_num=(delay_ms*1000)/Tick_Time_us;
	#if Timer0_Mode==Timer0_OVF
	if(Tick_num<=256)
	{
		Init_Val_0=256-Tick_num;
		TCNT0=Init_Val_0;
		No_OVFs_0=1;
	}
	else
	{
		No_OVFs_0=!(Tick_num%256)?(Tick_num/256):(Tick_num/256)+1;
		Init_Val_0=256-(Tick_num % 256);
		TCNT0=Init_Val_0;
	}
	#elif Timer0_Mode==Timer0_CTC
	if(Tick_num<=256)
	{
		Init_Val_0=256-Tick_num-1;
		OCR0=Init_Val_0;
		No_OVFs_0=1;
	}
	else
	{
		No_OVFs_0=!(Tick_num%256)?(Tick_num/256):(Tick_num/256)+1;
		Init_Val_0=(Tick_num % 256)-1;
		OCR0=Init_Val_0;
	}

#endif
}
void PWM0_Gen(f32 Duty_Cycle)
{
	if (Duty_Cycle<0)
	{
		Duty_Cycle=0;
	}
	else if (Duty_Cycle>100)
	{
		Duty_Cycle=100;
	}
	#if Timer0_Mode==Timer0_F_PWM
	
	#if F_OC0_Mode==F_OC0_C_Comp_S_Top
	OCR0=!Duty_Cycle? 0:(Duty_Cycle*256/100)-1;

	#elif F_OC0_Mode==F_OC0_S_Comp_C_Top
	OCR0=Duty_Cycle==100? 0:255-(Duty_Cycle*256/100);
#endif
	
	#elif Timer0_Mode==Timer0_P_PWM
	#if   P_OC0_Mode==P_OC0_C_CompU_S_CompD
	OCR0= Duty_Cycle*255/100;
	#elif P_OC0_Mode==P_OC0_S_CompU_C_CompD
	OCR0=255-(Duty_Cycle*255/100);
#endif

#endif
}
void Timer0_Start(void)
{ 
	TCCR0=(Timer0_CLK)|(TCCR0 &0XF8);
}
void Timer0_Stop(void)
{
	TCCR0&=0XF8;  

}
ISR(TIMER0_OVF_vect)
{
	static int count=0;
	count++;
	if (No_OVFs_0==count)
	{
		//Write your code here
		
		counter++;
		if (counter%4==0)
		{
			x=1;
			
		}
		if (counter%5==0)
		{
			x=2;
			
		}
		if (counter%6==0)
		{
			x=3;
			
		}
		if (counter==60)
		{
			counter=0;
		}
		
		Showed_Val++;
		count=0;
		TCNT0=Init_Val_0;
	}
}
ISR(TIMER0_COMP_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Count == 1 && No_OVFs_0 == Count)
	{
		// Write your code here
		Showed_Val++;
		
		Count = 0;
		OCR0 = Init_Val_0;
	}
	else if(Count == 1)
	OCR0 = 255;
	else if(No_OVFs_0 == Count)
	{
		// Write your code here
		Showed_Val++;
		
		Count = 0;
		OCR0 = Init_Val_0;
	}
}
	
	

/*------------------------------------>Timer1<-----------------------------------------------*/

void Timer1_Init(void)
{
	/*Global Interrupts Enable/Disable*/
	SREG|= Global_INT<<7;
	/*Timer1 Modes*/
	#if Timer1_Mode==Timer1_OVF
	/* TCCR1A */
	Clear_Bit(TCCR1A,0);
	Clear_Bit(TCCR1A,1);
	/* TCCR1B */
	Clear_Bit(TCCR1B,3);
	Clear_Bit(TCCR1B,4);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer1_OVF_INT<<2)|(TIMSK & 0XFB);
	#elif Timer1_Mode==Timer1_P_PWM_ICR1
	Clear_Bit(TCCR1A,1);
	Set_Bit(TCCR1A,3);

	Clear_Bit(TCCR1B,3);
	Set_Bit(TCCR1B,4);
	/*Phase Correct PWM Mode*/
	TCCR1A=(P_OC1A_Mode<<4)|(P_OC1B_Mode<<4)|(TCCR1A & 0X0F);

	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer1_OVF_INT<<2)|(Timer1_CTCA_INT<<4)|(Timer1_CTCB_INT<<3)|(TIMSK & 0XE3);
	
	DIO_SetPin_Dir(DIO_PORTD,PIN_5,PIN_OUT);
	DIO_SetPin_Dir(DIO_PORTD,PIN_4,PIN_OUT);

	#elif Timer1_Mode==Timer1_CTC
	Clear_Bit(TCCR1A,0);
	Clear_Bit(TCCR1A,1);
	
	Set_Bit(TCCR1B,3);
	Clear_Bit(TCCR1B,4);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer1_CTCA_INT<<4)|(Timer1_CTCB_INT<<3)|(TIMSK & 0XFD);
	#elif Timer1_Mode==Timer1_F_PWM_ICR1
	Clear_Bit(TCCR1A,0);
	Set_Bit(TCCR1A,1);
	
	Set_Bit(TCCR1B,3);
	Set_Bit(TCCR1B,4);
	/*Fast PWM Mode*/
	TCCR1A=(F_OC1A_Mode<<6)|(F_OC1B_Mode<<4)|(TCCR0 & 0X0F);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer1_OVF_INT<<2)|(Timer1_CTCA_INT<<4)|(Timer1_CTCB_INT<<3)|(TIMSK & 0XE3);
	
	DIO_SetPin_Dir(DIO_PORTD,PIN_5,PIN_OUT);
	DIO_SetPin_Dir(DIO_PORTD,PIN_4,PIN_OUT);
	#endif
}
void Timer1_SetDelay(Uint32 delay_ms_A,Uint32 delay_ms_B)
{
	Uint8 Tick_Time_us=0;
	Uint32 Tick_num_A=0;
	Uint32 Tick_num_B=0;
	Tick_Time_us=Timer1_Freq_Divder / MC_Freq_Mhz;
	Tick_num_A=(delay_ms_A*1000)/Tick_Time_us;
	Tick_num_B=(delay_ms_B*1000)/Tick_Time_us;
	#if Timer1_Mode==Timer1_OVF
	if(Tick_num_A<=65535)
	{
		Init_Val_1_A=256-Tick_num_A;
		TCNT1=Init_Val_1_A;
		No_OVFs_1_A=1;
	}
	else
	{
		No_OVFs_1_A=!(Tick_num_A%65535)?(Tick_num_A/65535):(Tick_num_A/65535)+1;
		Init_Val_1_A=65535-(Tick_num_A % 65535);
		TCNT1=Init_Val_1_A;
	}
	#elif Timer1_Mode==Timer1_CTC
	if(Tick_num_A<=65535)
	{
		Init_Val_1_A=65535-Tick_num_A-1;
		OCR1A=Init_Val_1_A;
		No_OVFs_1_A=1;
	}
	else
	{
		No_OVFs_1_A=!(Tick_num_A%65535)?(Tick_num_A/65535):(Tick_num_A/65535)+1;
		Init_Val_1_A=(Tick_num_A % 65535)-1;
		OCR1A=Init_Val_1_A;
	}
	if(Tick_num_B<=65535)
	{
		Init_Val_1_B=65535-Tick_num_B-1;
		OCR1B=Init_Val_1_B;
		No_OVFs_1_B=1;
	}
	else
	{
		No_OVFs_1_B=!(Tick_num_B%65535)?(Tick_num_B/65535):(Tick_num_B/65535)+1;
		Init_Val_1_B=(Tick_num_B % 65535)-1;
		OCR1B=Init_Val_1_B;
	}
	#endif	
}
void Timer1_Stop(void)
{
	TCCR1B&=0XF8;  
}
void Timer1_Start(void)
{
	TCCR1B=(Timer1_CLK)|(TCCR1B &0XF8);
}
void PWM1_Gen(f32 Duty_Cycle_A,f32 Duty_Cycle_B,f32 F_OC1_AB_Khz)
{
	ICR1=(MC_Freq_Mhz*1000)/(Timer1_Freq_Divder*F_OC1_AB_Khz);
	if (Duty_Cycle_A<0)
	{
		Duty_Cycle_A=0;
	}
	else if (Duty_Cycle_A>100)
	{
		Duty_Cycle_A=100;
	}
	if (Duty_Cycle_B<0)
	{
		Duty_Cycle_B=0;
	}
	else if (Duty_Cycle_B>100)
	{
		Duty_Cycle_B=100;
	}
	#if Timer1_Mode==Timer1_F_PWM
	
	#if F_OC1A_Mode==F_OC1A_C_Comp_S_Top
	OCR1A=!Duty_Cycle_A? 0:(Duty_Cycle_A*(ICR1+1)/100)-1;

	#elif F_OC1A_Mode==F_OC1A_S_Comp_C_Top
	OCR1A=Duty_Cycle_A==100? 0:ICR1-(Duty_Cycle_A*ICR1/100);
	#endif
	
	#if F_OC1B_Mode==F_OC1B_C_Comp_S_Top
	OCR1B=!Duty_Cycle_B? 0:(Duty_Cycle_B*(ICR1+1)/100)-1;

	#elif F_OC1B_Mode==F_OC1B_S_Comp_C_Top
	OCR1B=Duty_Cycle_B==100? 0:ICR1-(Duty_Cycle_B*ICR1/100);
	#endif
	
	#elif Timer1_Mode==Timer1_P_PWM
	#if   P_OC1A_Mode==P_OC1A_C_CompU_S_CompD
	OCR1A= Duty_Cycle_A*ICR1/100;
	#elif P_OC1A_Mode==P_OC1A_S_CompU_C_CompD
	OCR1A=ICR1-(Duty_Cycle_A*ICR1/100);
	#endif
	
	#if   P_OC1B_Mode==P_OC1B_C_CompU_S_CompD
	OCR1B= Duty_Cycle_B*ICR1/100;
	#elif P_OC1B_Mode==P_OC1B_S_CompU_C_CompD
	OCR1B=ICR1-(Duty_Cycle_B*ICR1/100);
	#endif

	#endif
}

/*------------------------------------>Timer2<-----------------------------------------------*/
void Timer2_Init(void)
{
	/*Global Interrupts Enable/Disable*/
	SREG|= Global_INT<<7;
	/*Timer2 Modes*/
	#if Timer2_Mode==Timer2_OVF
	Clear_Bit(TCCR2,3);
	Clear_Bit(TCCR2,6);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer2_OVF_INT<<6)|(TIMSK & 0XBF);
	#elif Timer2_Mode==Timer2_P_PWM
	Clear_Bit(TCCR2,3);
	Set_Bit(TCCR2,6);
	#elif Timer2_Mode==Timer2_CTC
	Set_Bit(TCCR0,3);
	Clear_Bit(TCCR0,6);
	/*Peripheral Interrupts Enable/Disable*/
	TIMSK=(Timer2_CTC_INT<<7)|(TIMSK & 0X0F);
		#elif Timer2_Mode==Timer2_F_PWM
	Set_Bit(TCCR0,6);
	Set_Bit(TCCR0,3);

	#endif
}
void Timer2_SetDelay(Uint32 delay_ms)
{
	Uint8 Tick_Time_us=0;
	Uint32 Tick_num=0;

	Tick_Time_us=Timer2_Freq_Divder / MC_Freq_Mhz;
	Tick_num=(delay_ms*1000)/Tick_Time_us;
	#if Timer2_Mode==Timer2_OVF
	if(Tick_num<=256)
	{
		Init_Val_2=256-Tick_num;
		TCNT2=Init_Val_2;
		No_OVFs_2=1;
	}
	else
	{
		No_OVFs_2=!(Tick_num%256)?(Tick_num/256):(Tick_num/256)+1;
		Init_Val_2=256-(Tick_num % 256);
		TCNT2=Init_Val_2;
	}
	#elif Timer2_Mode==Timer2_CTC
	if(Tick_num<=256)
	{
		Init_Val_2=256-Tick_num-1;
		OCR2=Init_Val_2;
		No_OVFs_2=1;
	}
	else
	{
		No_OVFs_2=!(Tick_num%256)?(Tick_num/256):(Tick_num/256)+1;
		Init_Val_2=(Tick_num % 256)-1;
		OCR2=Init_Val_2;
	}

	#endif
}
void PWM2_Gen(f32 Duty_Cycle)
{
	if (Duty_Cycle<0)
	{
		Duty_Cycle=0;
	}
	else if (Duty_Cycle>100)
	{
		Duty_Cycle=100;
	}
	#if Timer2_Mode==Timer2_F_PWM
	
	#if F_OC2_Mode==F_OC2_C_Comp_S_Top
	OCR2=!Duty_Cycle? 0:(Duty_Cycle*256/100)-1;

	#elif F_OC2_Mode==F_OC2_S_Comp_C_Top
	OCR2=Duty_Cycle==100? 0:-(Duty_Cycle*256/100);
	#endif
	
	#elif Timer2_Mode==Timer2_P_PWM
	#if   P_OC2_Mode==P_OC2_C_CompU_S_CompD
	OCR2= Duty_Cycle*255/100;
	#elif P_OC2_Mode==P_OC2_S_CompU_C_CompD
	OCR2=255-(Duty_Cycle*255/100);
	#endif

	#endif
}
void Timer2_Start(void)
{
	TCCR2=(Timer2_CLK)|(TCCR2 &0XF8);
}
void Timer2_Stop(void)
{
	TCCR2&=0XF8;

}
ISR(TIMER2_OVF_vect)
{
	static int count=0;
	count++;
	if (No_OVFs_2==count)
	{
		//Write your code here
		
		
		count=0;
		TCNT2=Init_Val_2;
	}
}
ISR(TIMER2_COMP_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Count == 1 && No_OVFs_2 == Count)
	{
		// Write your code here
		Showed_Val_1++;
		
		Count = 0;
		OCR2 = Init_Val_2;
	}
	else if(Count == 1)
	OCR2 = 255;
	else if(No_OVFs_2 == Count)
	{
		// Write your code here
		Showed_Val_1++;
		
		Count = 0;
		OCR2 = Init_Val_2;
	}
}