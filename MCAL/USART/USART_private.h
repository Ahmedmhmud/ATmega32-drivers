/*
*<<<<<<<<<<USART_private.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  USART
*
*/

#ifndef _USART_PRIVATE_H_
#define _USART_PRIVATE_H_

// Data register
#define UDR   *((v_u_8 *) 0x2C)

//Control register A Being accessed when The control bus has rad/write signal
#define UCSRA *((v_u_8 *) 0x2B)
#define UCSRA_RXC        7
#define UCSRA_TXC        6
#define UCSRA_UDRE       5
#define UCSRA_FE         4
#define UCSRA_DOR        3
#define UCSRA_PE         2
#define UCSRA_U2X        1
#define UCSRA_MPOM       0

//Control register B
#define UCSRB *((v_u_8 *) 0x2A)
#define UCSRB_RXCIE      7
#define UCSRB_TXCIE      6
#define UCSRB_UDRIE      5
#define UCSRB_RXEN       4
#define UCSRB_TXEN       3
#define UCSRB_UCSZ2      2
#define UCSRB_RXB8       1
#define UCSRB_TXB8       0

//Control register C (Being accessed when setting bit 7)
#define UCSRC *((v_u_8 *) 0x40)
#define UCSRC_URSEL      7
#define UCSRC_UMSEL      6
#define UCSRC_UPM1       5
#define UCSRC_UPM0       4
#define UCSRC_USBS       3
#define UCSRC_UCSZ1      2
#define UCSRC_UCSZ0      1
#define UCSRC_UCPOL      0

#define UBRRL *((v_u_8 *) 0x29)

#define UBRRH *((v_u_8 *) 0x40)
#define UBRRH_URSEL		 7


#endif