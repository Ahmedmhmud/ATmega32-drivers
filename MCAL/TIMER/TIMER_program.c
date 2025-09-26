/*
*<<<<<<<<<<TIMER_program.c>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  Timer
*
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

static void (*TIMERS_pvCallBackFunc[16])(void) = {NULL} ;

void TIMER0_voidInit                ( void                 )
{
		#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

			CLR_BIT(TCCR0 , WFG00) ;
			CLR_BIT(TCCR0 , WFG01) ;

			TCNT0 = TIMER0_PRELOAD_VAL ;

			#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , TOIE0) ;
			#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
				SET_BIT(TIMSK , TOIE0) ;
			#else
				#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
			#endif

		#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
			SET_BIT(TCCR0 , WGM00) ;
			CLR_BIT(TCCR0 , WGM01) ;

			#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
					CLR_BIT(TCCR0 , COM00) ;
					CLR_BIT(TCCR0 , COM01) ;
			#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC
					CLR_BIT(TCCR0 , COM00) ;
					SET_BIT(TCCR0 , COM01) ;
			#elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC
					SET_BIT(TCCR0 , COM00) ;
					SET_BIT(TCCR0 , COM01) ;
			#else
					#error "Wrong TIMER0_CTC_PWM_MODE Config"
			#endif

			OCR0 = TIMER0_CTC_VAL ;

		#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

			CLR_BIT(TCCR0 , WGM00) ;
			SET_BIT(TCCR0 , WGM01) ;

			OCR0 = TIMER0_CTC_VAL ;

			#if TIMER0_CTC_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , OCIE0) ;
			#elif TIMER0_CTC_INTERRUPT == ENABLE
				SET_BIT(TIMSK , OCIE0) ;
			#else
				#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
			#endif

		#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

			SET_BIT(TCCR0 , WGM00) ;
			SET_BIT(TCCR0 , WGM01) ;

			#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
					CLR_BIT(TCCR0 , COM00) ;
					CLR_BIT(TCCR0 , COM01) ;
			#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC
					CLR_BIT(TCCR0 , COM00) ;
					SET_BIT(TCCR0 , COM01) ;
			#elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC
					SET_BIT(TCCR0 , COM00) ;
					SET_BIT(TCCR0 , COM01) ;
			#else
					#error "Wrong TIMER0_CTC_PWM_MODE Config"
			#endif

			OCR0 = TIMER0_CTC_VAL ;

		#else
			#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

		#endif

	TCCR0 &= 0b11111000 ;
	TCCR0 |= TIMER0_PRESCALER ;
}

void TIMER0_voidSetPreload          ( u_8 Copy_u8Preload   )
{
    TCNT0 = Copy_u8Preload;
}
void TIMER0_voidSetCTC              ( u_8 Copy_u8CTC       )
{
    OCR0 = Copy_u8CTC;
}

u_8  TIMER0_u8GetTimerCounterValue  ( void                 )
{
    return TCNT0;
}

void TIMER1_voidInit(void)
{
    /*Set Configurable Modes*/

    #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

        /*Set Waveform generation mode as Normal mode */
        CLR_BIT(TCCR1A, WGM10);
        CLR_BIT(TCCR1A, WGM11);
        CLR_BIT(TCCR1B, WGM12);
        CLR_BIT(TCCR1B, WGM13);

        /*Set the required Preload Value*/
        TCNT1 = TIMER1_PRELOAD_VAL;

        /*Timer1 Overflow Interrupt Enable*/
        #if TIMER1_OVERFLOW_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TOIE1);
        #elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TOIE1);
        #else
            #error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
        #endif

    #elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE)

        /*Set Waveform generation mode as CTC modes */
        #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #else
            #error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
        #endif

        /*Set the required CTC Values*/
        OCR1A = TIMER1_CTCA_VAL;
        OCR1B = TIMER1_CTCB_VAL;

        /*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
        #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE
            ICR1 = TIMER1_ICR1_VAL;

            #if TIMER1_ICR_EDGE == RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICR_EDGE == FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #else
                #error "Wrong TIMER1_ICR_EDGE Config"
            #endif

        #else
            /*Do nothing*/
        #endif

        /*Set OCR1A mode*/
        #if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_OC_TOGGEL
            SET_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_OC_LOW
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_OC_HIGH
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "Wrong TIMER1_OCR1A_MODE Config"
        #endif

        /*Set OCR1B mode*/
        #if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_OC_TOGGEL
            SET_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_OC_LOW
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_OC_HIGH
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "Wrong TIMER1_OCR1B_MODE Config"
        #endif

        /*Timer1 CTC Interrupt Enable*/
        #if TIMER1_CTCA_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1A);
        #elif TIMER1_CTCA_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1A);
        #else
            #error "Wrong TIMER1_CTCA_INTERRUPT Config"
        #endif

        #if TIMER1_CTCB_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1B);
        #elif TIMER1_CTCB_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1B);
        #else
            #error "Wrong TIMER1_CTCB_INTERRUPT Config"
        #endif

    #elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE) ||(TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE)

        /*Set Waveform generation mode as PWM modes */
        #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10_BIT_MODE
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9_BIT_MODE
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8_BIT_MODE
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #else
            #error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
        #endif

        /*Set the required CTC Values*/
        OCR1A = TIMER1_CTCA_VAL;
        OCR1B = TIMER1_CTCB_VAL;

        /*Set ICR1*/
        #if ((TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE))
            ICR1 = TIMER1_ICR1_VAL;

            #if TIMER1_ICR_EDGE == RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICR_EDGE == FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #else
                #error "Wrong TIMER1_ICR_EDGE Config"
            #endif
        #else
            /*Do nothing*/
        #endif

        /*Set OCR1A mode*/
        #if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "Wrong TIMER1_OCR1A_MODE Config"
        #endif

        /*Set OCR1B mode*/
        #if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "Wrong TIMER1_OCR1B_MODE Config"
        #endif

        /*Timer1 PWM Interrupt Enable*/
        #if TIMER1_OVERFLOW_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TOIE1);
        #elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TOIE1);
        #else
            #error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
        #endif

        #if TIMER1_CTCA_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1A);
        #elif TIMER1_CTCA_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1A);
        #else
            #error "Wrong TIMER1_CTCA_INTERRUPT Config"
        #endif

        #if TIMER1_CTCB_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1B);
        #elif TIMER1_CTCB_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1B);
        #else
            #error "Wrong TIMER1_CTCB_INTERRUPT Config"
        #endif

        #if TIMER1_ICR_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TICIE1);
        #elif TIMER1_ICR_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TICIE1);
        #else
            #error "Wrong TIMER1_ICR1_INTERRUPT Config"
        #endif

    #elif (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE)

        /*Set Waveform generation mode as Fast PWM modes */
        #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10_BIT_MODE
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9_BIT_MODE
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8_BIT_MODE
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
        #else
            #error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
        #endif

        /*Set the required CTC Values*/
        OCR1A = TIMER1_CTCA_VAL;
        OCR1B = TIMER1_CTCB_VAL;

        /*Set ICR1*/
        #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE
            ICR1 = TIMER1_ICR1_VAL;

            #if TIMER1_ICR_EDGE == RISING_EDGE
                SET_BIT(TCCR1B, ICES1);
            #elif TIMER1_ICR_EDGE == FALLING_EDGE
                CLR_BIT(TCCR1B, ICES1);
            #else
                #error "Wrong TIMER1_ICR_EDGE Config"
            #endif
        #else
            /*Do nothing*/
        #endif

        /*Set OCR1A mode*/
        #if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
        #else
            #error "Wrong TIMER1_OCR1A_MODE Config"
        #endif

        /*Set OCR1B mode*/
        #if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
        #else
            #error "Wrong TIMER1_OCR1B_MODE Config"
        #endif

        /*Timer1 Fast PWM Interrupt Enable*/
        #if TIMER1_OVERFLOW_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TOIE1);
        #elif TIMER1_OVERFLOW_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TOIE1);
        #else
            #error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
        #endif

        #if TIMER1_CTCA_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1A);
        #elif TIMER1_CTCA_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1A);
        #else
            #error "Wrong TIMER1_CTCA_INTERRUPT Config"
        #endif

        #if TIMER1_CTCB_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, OCIE1B);
        #elif TIMER1_CTCB_INTERRUPT == ENABLE
            SET_BIT(TIMSK, OCIE1B);
        #else
            #error "Wrong TIMER1_CTCB_INTERRUPT Config"
        #endif

        #if TIMER1_ICR_INTERRUPT == DISABLE
            CLR_BIT(TIMSK, TICIE1);
        #elif TIMER1_ICR_INTERRUPT == ENABLE
            SET_BIT(TIMSK, TICIE1);
        #else
            #error "Wrong TIMER1_ICR1_INTERRUPT Config"
        #endif
        
    #else
        #error "Wrong TIMER1_WAVEFORM_GENERATION_MODE Config"
    #endif

    TCCR1B &= 0b11111000;
    TCCR1B |= TIMER1_PRESCALER;
}

void TIMER1_voidSetPreload          ( u_16 Copy_u16Preload )
{
    TCNT1 = Copy_u16Preload;
}

void TIMER1_voidSetCTCA             ( u_16 Copy_u16CTCA    )
{
    OCR1A = Copy_u16CTCA;
}

void TIMER1_voidSetCTCB             ( u_16 Copy_u16CTCB    )
{
    OCR1B = Copy_u16CTCB;
}

void TIMER1_voidSetICR1             ( u_16 Copy_u16ICR1    )
{
    ICR1 = Copy_u16ICR1;
}

u_16 TIMER1_u16GetTimerCounterValue ( void                 )
{
    return TCNT1;
}

void TIMER2_voidInit                ( void                 )
{
    
		#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

			CLR_BIT(TCCR2 , WGM20) ;
			CLR_BIT(TCCR2 , WGM21) ;

			TCNT2 = TIMER2_PRELOAD_VAL ;

			#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , TOIE2) ;
			#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
				SET_BIT(TIMSK , TOIE2) ;
			#else
				#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
			#endif

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE
			SET_BIT(TCCR2 , WFG20) ;
			CLR_BIT(TCCR2 , WFG21) ;

			#if TIMER2_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
					CLR_BIT(TCCR2 , COM20) ;
					CLR_BIT(TCCR2 , COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC
					CLR_BIT(TCCR2 , COM20) ;
					SET_BIT(TCCR2 , COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC
					SET_BIT(TCCR2 , COM20) ;
					SET_BIT(TCCR2 , COM21) ;
			#else
					#error "Wrong TIMER2_CTC_PWM_MODE Config"
			#endif

			OCR2 = TIMER2_CTC_VAL ;

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

			CLR_BIT(TCCR2 , WGM20) ;
			SET_BIT(TCCR2 , WGM21) ;

			OCR2 = TIMER2_CTC_VAL ;

			#if TIMER2_CTC_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , OCIE2) ;
			#elif TIMER2_CTC_INTERRUPT == ENABLE
				SET_BIT(TIMSK , OCIE2) ;
			#else
				#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
			#endif

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

			SET_BIT(TCCR2 , WFG20) ;
			SET_BIT(TCCR2 , WFG21) ;

			#if TIMER2_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
					CLR_BIT(TCCR2 , COM20) ;
					CLR_BIT(TCCR2 , COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC
					CLR_BIT(TCCR2 , COM20) ;
					SET_BIT(TCCR2 , COM21) ;
			#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC
					SET_BIT(TCCR2 , COM20) ;
					SET_BIT(TCCR2 , COM21) ;
			#else
					#error "Wrong TIMER2_CTC_PWM_MODE Config"
			#endif

			OCR2 = TIMER2_CTC_VAL ;

		#else
			#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

		#endif

	TCCR2 &= 0b11111000 ;
	TCCR2 |= TIMER2_PRESCALER;
}

void TIMER2_voidSetPreload          ( u_8 Copy_u8Preload   )
{
    TCNT2 = Copy_u8Preload;
}

void TIMER2_voidSetCTC              ( u_8 Copy_u8CTC       )
{
    OCR2 = Copy_u8CTC;
}

u_8  TIMER2_u8GetTimerCounterValue  ( void                 )
{
    return TCNT2;
}

void TIMER_voidICUInitEnable        ( void                 )
{
    #if (TIMER_u8_ICP_INIT_STATE == TIMER_u8_ICP_RAISING_EDGE)
		SET_BIT(TCCR1B, ICES1);
	#elif(TIMER_u8_ICP_INIT_STATE == TIMER_u8_ICP_FALLING_EDGE)
		CLR_BIT(TCCR1B, ICES1);
	#endif

    SET_BIT(TIMSK, TICIE1);
}

u_8  TIMER_voidICUSetTriggerEdge    ( u_8 Copy_u8Edge      )
{
    u_8 Local_u8ErrorStatus = OK;

    if(Copy_u8Edge == TIMER_u8_ICP_RAISING_EDGE)
    {
        SET_BIT(TCCR1B, ICES1);
    }
    else if(Copy_u8Edge == TIMER_u8_ICP_FALLING_EDGE)
    {
        CLR_BIT(TCCR1B, ICES1);
    }
    else
    {
        Local_u8ErrorStatus = NOK;
    }

    return Local_u8ErrorStatus;
}

void TIMER_voidICUEnableInterrupt   ( void                 )
{
    SET_BIT(TIMSK, TICIE1);
}

void TIMER_voidICUDisableInterrupt  ( void                 )
{
    CLR_BIT(TIMSK, TICIE1);
}

u_16 TIMER_u16GetICR                ( void                 )
{
    return ICR1;
}

void TIMER_voidSetPWM               ( u_16 Copy_u16CompareValue   )
{
	OCR1A = Copy_u16CompareValue;
}

void TIMER_voidWDTSleep             ( void                        )
{
    WDTCR &= BIT_MASKING;
    WDTCR |= WDT_PRESCALER;
}

void TIMER_voidWDTEnable            ( void                        )
{
    SET_BIT(WDTCR, WDE);
}

void TIMER_voidWDTDisable           ( void                        )
{
    WDTCR |= 0b00011000;
    CLR_BIT(WDTCR, WDE);
}

void TIMER_voidWDTRefresh(void)
{
    __asm__ __volatile__("wdr");
}

u_8  TIMER_u8SetCallBack            ( void (*Copy_pvCallBackFunc)(void) , u_8 Copy_u8VectorID)
{
	u_8 Local_u8ErrorState = OK ;

	if (Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFunc[Copy_u8VectorID] = Copy_pvCallBackFunc ;
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;
}

void __vector_11 (void)		__attribute__((signal)) ;
void __vector_11 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID]() ;
	}
}

void __vector_10 (void)		__attribute__((signal)) ;
void __vector_10 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID]() ;
	}
}

void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID]() ;
	}
}

void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID]() ;
	}
}

void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID]() ;
	}
}

void __vector_6 (void)		__attribute__((signal)) ;
void __vector_6 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID]() ;
	}
}

void __vector_5 (void)		__attribute__((signal)) ;
void __vector_5 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID]() ;
	}
}

void __vector_4 (void)		__attribute__((signal)) ;
void __vector_4 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID]() ;
	}
}
