/*
 * uart.h
 *
 * Created: 2016-12-10 21:11:54
 */ 

#ifndef UART_H_
#define UART_H_

#include "../config.h"

#define USART1_DOUBLE_TRANSMISSION_SPEED		(1 << U2X1)

#define USART1_BAUD_RATE_H   UBRR1H
#define USART1_BAUD_RATE_L   UBRR1L

#define USART1_RECEIVE_INTERRUPT     USART1_RX_vect
#define USART1_TRANSMIT_INTERRUPT    USART1_UDRE_vect


#ifndef F_CPU
	#warning "F_CPU not defined for <uart.h>, setting default."
	#define F_CPU 1000000UL	//Default CPU speed.
#endif

#ifndef BAUD
	#warning "BAUD not defined for <uart.h>, setting default."
	#define BAUD 9600	//Default baud rate.
#endif

//UART Buffer Defines
#ifndef UART1_RX_BUFFER_SIZE
	#warning "UART1_RX_BUFFER_SIZE not defined for <uart.h>, setting default."
	#define UART1_RX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#ifndef UART1_TX_BUFFER_SIZE
	#warning "UART1_TX_BUFFER_SIZE not defined for <uart.h>, setting default."
	#define UART1_TX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#define UART1_RX_BUFFER_MASK (UART1_RX_BUFFER_SIZE - 1)
#define UART1_TX_BUFFER_MASK (UART1_TX_BUFFER_SIZE - 1)

#if (UART1_RX_BUFFER_SIZE & UART1_RX_BUFFER_MASK)
	#error RX buffer size is not a power of 2
#endif


// /* Prototypes */
// void InitUART( unsigned char baudrate );
// unsigned char ReceiveByte( void );
// void TransmitByte( unsigned char data );

//Init uart.
void UART1_Init();

//Send one symbol;
void UART1_SendByte(unsigned char data);
//Send char array;
void UART1_SendString(const char* data);
//Send char array with new line break.
void UART1_Println(const char* data);



#endif /* UART_H_ */