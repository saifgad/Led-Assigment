/*
 * EXT_INT.h
 *
 * Created: 9/21/2022 12:29:37 PM
 *  Author: AMIT
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "EXT_INT_CFG.h"

/*EXT INT0 Triggers*/
#define EXT0_Low_Level					0
#define EXT0_Level_Change				1
#define EXT0_Falling_Edge				2
#define EXT0_Rising_Edge				3

/*EXT INT1 Triggers*/
#define EXT1_Low_Level					0
#define EXT1_Level_Change				1
#define EXT1_Falling_Edge				2
#define EXT1_Rising_Edge				3

/*EXT INT0 Triggers*/
#define EXT2_Falling_Edge				0
#define EXT2_Rising_Edge				1

void INT0_Init(void);
void INT1_Init(void);
void INT2_Init(void);



#endif /* EXT_INT_H_ */