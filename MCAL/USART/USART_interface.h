/*
*<<<<<<<<<<USART_interface.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  USART
*
*/

#ifndef _USART_INTERFACE_H_
#define _USART_INTERFACE_H_

#define ENABLE                          1
#define DISABLE                         0

#define ONE_BIT                         1
#define TWO_BIT                         0

#define USART_X1                        1
#define USART_X2                        0

#define ASYNCHRONOUS                    1
#define SYNCHRONOUS                     0

#define DATA_SiZE_BIT_5                 0
#define DATA_SiZE_BIT_6                 1
#define DATA_SiZE_BIT_7                 2
#define DATA_SiZE_BIT_8                 3
#define DATA_SiZE_BIT_9                 4

#define XCK_RISING_TX_XCH_FALLING_RX    1
#define XCK_FALLING_TX_XCH_RISING_RX    0

void USART_voidInit(void);

#endif
