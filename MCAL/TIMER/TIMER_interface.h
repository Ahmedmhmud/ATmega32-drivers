/*
*<<<<<<<<<<TIMER_interface.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  Timer
*
*/

#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#define TIMER0_OVF_VECTOR_ID		11
#define TIMER0_CTC_VECTOR_ID		10

#define TIMER1_OVF_VECTOR_ID		9
#define TIMER1_CTCB_VECTOR_ID		8
#define TIMER1_CTCA_VECTOR_ID		7
#define TIMER1_ICU_VECTOR_ID		6

#define TIMER2_OVF_VECTOR_ID		5
#define TIMER2_CTC_VECTOR_ID		4

#define TIMER_NORMAL_MODE         0
#define TIMER_PWM_MODE            1
#define TIMER_CTC_MODE            2
#define TIMER_FAST_PWM_MODE       3

#define TIMER_NO_CLOCK_SOURCE     0
#define TIMER_NO_PRESCALING       1
#define TIMER_PRESCALER_8         2
#define TIMER_PRESCALER_64        3
#define TIMER_PRESCALER_256       4
#define TIMER_PRESCALER_1024      5
#define TIMER0_EXT_CLK_FALLING    6
#define TIMER0_EXT_CLK_RISING     7

#define ENABLE                    1
#define DISABLE                   0

#define TIMER_OC_DISCONNECTED     0
#define TIMER_CLR_ON_CTC          1
#define TIMER_SET_ON_CTC          2

#define TIMER_OC_HIGH             0
#define TIMER_OC_LOW              1
#define TIMER_OC_TOG              2

#define FALLING_EDGE		      0
#define RISING_EDGE               1

#define TIMER_u8_ICP_FALLING_EDGE     0
#define TIMER_u8_ICP_RAISING_EDGE     1

#define	WDT_PS_16_3_MS			  0
#define	WDT_PS_32_5_MS	    	  1
#define	WDT_PS_65_MS	    	  2
#define	WDT_PS_0_13_S			  3
#define	WDT_PS_0_26_S			  4
#define	WDT_PS_0_52_S			  5
#define	WDT_PS_1_0_S			  6
#define	WDT_PS_2_1_S			  7

#define TIMER1_NORMAL_MODE								0
#define TIMER1_PWM_8_BIT_MODE							1
#define TIMER1_PWM_9_BIT_MODE							2
#define TIMER1_PWM_10_BIT_MODE							3
#define TIMER1_CTC_OCR1A_MODE							4
#define TIMER1_FAST_PWM_8_BIT_MODE						5
#define TIMER1_FAST_PWM_9_BIT_MODE 						6
#define TIMER1_FAST_PWM_10_BIT_MODE						7
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE		8
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE	9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE				10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE				11
#define TIMER1_CTC_ICR1_MODE							12
#define TIMER1_FAST_PWM_ICR1_MODE						14
#define TIMER1_FAST_PWM_OCR1A_MODE						15



void TIMER0_voidInit                ( void                 );
void TIMER0_voidSetPreload          ( u_8 Copy_u8Preload   );
void TIMER0_voidSetCTC              ( u_8 Copy_u8CTC       );
u_8  TIMER0_u8GetTimerCounterValue  ( void                 );

void TIMER1_voidInit                ( void                 );
void TIMER1_voidSetPreload          ( u_16 Copy_u16Preload );
void TIMER1_voidSetCTCA             ( u_16 Copy_u16CTCA    );
void TIMER1_voidSetCTCB             ( u_16 Copy_u16CTCB    );
void TIMER1_voidSetICR1             ( u_16 Copy_u16ICR1    );
u_16 TIMER1_u16GetTimerCounterValue ( void                 );

void TIMER2_voidInit                ( void                 );
void TIMER2_voidSetPreload          ( u_8 Copy_u8Preload   );
void TIMER2_voidSetCTC              ( u_8 Copy_u8CTC       );
u_8  TIMER2_u8GetTimerCounterValue  ( void                 );

void TIMER_voidICUInitEnable        ( void                 );
u_8  TIMER_voidICUSetTriggerEdge    ( u_8 Copy_u8Edge      );
void TIMER_voidICUEnableInterrupt   ( void                 );
void TIMER_voidICUDisableInterrupt  ( void                 );
u_16 TIMER_u16GetICR                ( void                 );

void TIMER_voidSetPWM               ( u_16 Copy_u16CompareValue   );
void TIMER_voidWDTSleep             ( void                        );
void TIMER_voidWDTEnable            ( void                        );
void TIMER_voidWDTDisable           ( void                        );
void TIMER_voidWDTRefresh           ( void                        );

u_8  TIMER_u8SetCallBack            ( void (*Copy_pvCallBackFunc)(void) , u_8 Copy_u8VectorID) ;

#endif
