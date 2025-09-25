/*
*<<<<<<<<<<TIMER_private.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  Timer
*
*/

#ifndef _TIMER_PRIVATE_H_
#define _TIMER_PRIVATE_H_

        /*                       Timer 0                       */

#define TCCR0   *((v_u_8 *) 0x53)
#define CS00    0
#define CS01    1
#define CS02    2
#define WFG01   3
#define COM00   4
#define COM01   5
#define WFG00   6
#define FOC0    7

#define TCNT0   *((v_u_8 *) 0x52)

#define OCR0    *((v_u_8 *) 0x5C)

#define TIMSK   *((v_u_8 *) 0x59)
#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOIE2   6
#define OCIE2   7

#define TIFR    *((v_u_8 *) 0x58)   
#define TOV0    0
#define OCF0    1
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
#define TOV2    6
#define OCF2    7


        /*                       Timer 1                       */

#define TCCR1A  *((v_u_8 *) 0x4F)
#define COM1A1	7
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4
#define WGM11	1
#define WGM10	0

#define TCCR1B  *((v_u_8 *) 0x4E)
#define ICNC1	7
#define ICES1	6
#define WGM13	4
#define WGM12	3

#define TCNT1H  *((v_u_8 *) 0x4D)
#define TCNT1L  *((v_u_8 *) 0x4C)
#define TCNT1  *((v_u_16 *) 0x4C)
#define OCR1AH  *((v_u_8 *) 0x4B)
#define OCR1AL  *((v_u_8 *) 0x4A)
#define OCR1A  *((v_u_16 *) 0x4A)
#define OCR1BH  *((v_u_8 *) 0x49)
#define OCR1BL  *((v_u_8 *) 0x48)
#define OCR1B  *((v_u_16 *) 0x48)
#define ICR1H   *((v_u_8 *) 0x47)
#define ICR1L   *((v_u_8 *) 0x46)
#define ICR1   *((v_u_16 *) 0x46)


        /*                       Timer 2                       */

#define TCCR2   *((v_u_8 *) 0x45)
#define CS20    0
#define CS21    1
#define CS22    2
#define WFG21   3
#define COM20   4
#define COM21   5
#define WFG20   6
#define FOC2    7

#define TCNT2   *((v_u_8 *) 0x44)

#define OCR2    *((v_u_8 *) 0x43)


        /*                       WatchDog                       */

#define WDTCR   *((v_u_8 *) 0x41)
#define	WDTOE 	4
#define	WDE		3
#define	WDP2	2
#define	WDP1	1
#define	WDP0	0

#define	BIT_MASKING				  0b11111000    // For watch dog and timer prescaler

#endif
