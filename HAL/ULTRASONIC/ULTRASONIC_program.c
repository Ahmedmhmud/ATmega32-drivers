/*
*<<<<<<<<<<ULTRASONIC_program.c>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  HAL
*   SWC     :  Ultrasonic Sensor
*
*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"

#include "ULTRASONIC_interface.h"

#define ULTRASONIC_PORT    ULTRASONIC_PORTA
#define TRIG_PIN           ULTRASONIC_PIN6
#define ECHO_PIN           ULTRASONIC_PIN7

u_8 Global_counter = 0;

void ULTRASONIC_voidInit(void)
{
    DIO_enumSetPinDirection(ULTRASONIC_PORTA, TRIG_PIN, DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection(ULTRASONIC_PORTA, ECHO_PIN, DIO_PIN_INPUT);
    TIMER0_voidInit();
    TIMER_u8SetCallBack(Timer_ISR, TIMER0_OVF_VECTOR_ID);
}

u_16 ULTRASONIC_u8GetDistance(void)
{
    DIO_enumSetPinValue(ULTRASONIC_PORTA, TRIG_PIN, DIO_PIN_HIGH);
    _delay_us(10);
    DIO_enumSetPinValue(ULTRASONIC_PORTA, TRIG_PIN, DIO_PIN_LOW);
    while(DIO_enumGetPinValue(ULTRASONIC_PORTA, ECHO_PIN) == DIO_PIN_LOW);
    Global_counter = 0;
    TIMER0_voidSetPreload(0);
    while(DIO_enumGetPinValue(ULTRASONIC_PORTA, ECHO_PIN) == DIO_PIN_HIGH);
    u_8 time_fraction = TIMER0_u8GetTimerCounterValue();
    u_32 time_microseconds = (255UL * Global_counter) + time_fraction;
    u_16 distance_cm = time_microseconds / 58;
    _delay_ms(60);
    return distance_cm;
}

void Timer_ISR(void)
{
    Global_counter++;
}