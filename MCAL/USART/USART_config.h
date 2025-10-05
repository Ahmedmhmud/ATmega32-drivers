/*
*<<<<<<<<<<USART_config.h>>>>>>>>>>
*
*   Author  :  Ahmed Mahmoud
*   Layer   :  MCAL
*   SWC     :  USART
*
*/

#ifndef _USART_CONFIG_H_
#define _USART_CONFIG_H_

/*
Options for frame error
1- DISABLE
2- ENABLE
*/
#define USART_PARITY_MODE    DISABLE

/*
Options for stop bits no.
1- ONE_BIT
2- TWO_BIT
*/
#define USART_STOP_BITS      ONE_BIT

/*
Options for data overrun
1- DISABLE
2- ENABLE
*/
#define USART_DATA_OVERRUN   DISABLE

#define USART_BAUD_RATE      9600UL

/*
Options for speed mode
1- USART_X1
2- USART_X2
*/
#define USART_SPEED_MODE     USART_X1

/*
Options for multi-processor communication mode
1- DISABLE
2- ENABLE
*/
#define USART_MPCM_MODE      DISABLE

/* Timeout for polling */
#define USART_TIMEOUT  10000UL

/*
Options for RX complete interrupt
1- DISABLE
2- ENABLE
*/
#define USART_RX_COMPLETE_INTERRUPT   DISABLE

/*
Options for TX complete interrupt
1- DISABLE
2- ENABLE
*/
#define USART_TX_COMPLETE_INTERRUPT   DISABLE

/*
Options fordata register empty interrupt
1- DISABLE
2- ENABLE
*/
#define USART_UDR_EMPTY_INTERRUPT     DISABLE

/*
Options for receiver enable
1- DISABLE
2- ENABLE
*/
#define USART_RECEIVER_ENABLE      ENABLE

/*
Options for transmitter enable
1- DISABLE
2- ENABLE
*/
#define USART_TRANSMITTER_ENABLE   ENABLE



#endif
