/*
*<<<<<<<<<<ULRASONIC_interface.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  HAL
*   SWC     :  Ultrasonic sensor
*
*/

#ifndef _ULRASONIC_INTERFACE_H_
#define _ULRASONIC_INTERFACE_H_


#define ULTRASONIC_PORTA    0
#define ULTRASONIC_PORTB    1
#define ULTRASONIC_PORTC    2
#define ULTRASONIC_PORTD    3

#define ULTRASONIC_PIN0     0
#define ULTRASONIC_PIN1     1
#define ULTRASONIC_PIN2     2
#define ULTRASONIC_PIN3     3
#define ULTRASONIC_PIN4     4
#define ULTRASONIC_PIN5     5
#define ULTRASONIC_PIN6     6
#define ULTRASONIC_PIN7     7

void ULTRASONIC_voidInit        ( void );
u_16 ULTRASONIC_u8GetDistance   ( void );


#endif
