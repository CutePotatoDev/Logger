/*
 * uart.h
 *
 * Created: 2016-12-10 21:11:54
 */ 

#ifndef UART_H_
#define UART_H_

#include "../config.h"

#define USART_DOUBLE_TRANSMISSION_SPEED		(1 << U2X0)

#define USART_BAUD_RATE_H   UBRR0H
#define USART_BAUD_RATE_L   UBRR0L

#define USART_RECEIVE_INTERRUPT     USART_RX_vect
#define USART_TRANSMIT_INTERRUPT    USART_UDRE_vect


#ifndef F_CPU
	#warning "F_CPU not defined for <uart.h>, setting default."
	#define F_CPU 1000000UL	//Default CPU speed.
#endif

#ifndef BAUD
	#warning "BAUD not defined for <uart.h>, setting default."
	#define BAUD 9600	//Default baud rate.
#endif

//UART Buffer Defines
#ifndef UART_RX_BUFFER_SIZE
	#warning "UART_RX_BUFFER_SIZE not defined for <uart.h>, setting default."
	#define UART_RX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#ifndef UART_TX_BUFFER_SIZE
	#warning "UART_TX_BUFFER_SIZE not defined for <uart.h>, setting default."
	#define UART_TX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE - 1)
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE - 1)

#if (UART_RX_BUFFER_SIZE & UART_RX_BUFFER_MASK)
	#error RX buffer size is not a power of 2
#endif


// /* Prototypes */
// void InitUART( unsigned char baudrate );
// unsigned char ReceiveByte( void );
// void TransmitByte( unsigned char data );

//Init uart.
void UART_Init();

//Send one symbol;
void UART_SendByte(unsigned char data);
//Send char array;
void UART_SendString(const char* data);
//Send char array with new line break.
void UART_Println(const char* data);



#endif /* UART_H_ */