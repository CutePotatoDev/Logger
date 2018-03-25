/*
 * uart.h
 *
 * Created: 2016-12-10 21:11:54
 */ 

#ifndef UART_H_
#define UART_H_

#include "avr/io.h"
#include "../config.h"

#define USART0_DOUBLE_TRANSMISSION_SPEED        (1 << U2X0)
#define USART1_DOUBLE_TRANSMISSION_SPEED		(1 << U2X1)

#define USART0_BAUD_RATE_H   UBRR0H
#define USART0_BAUD_RATE_L   UBRR0L
#define USART1_BAUD_RATE_H   UBRR1H
#define USART1_BAUD_RATE_L   UBRR1L

#define USART0_RECEIVE_INTERRUPT     USART0_RX_vect
#define USART0_TRANSMIT_INTERRUPT    USART0_UDRE_vect
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

// UART Buffer Defines
// UART 0
#ifndef UART0_RX_BUFFER_SIZE
    #warning "UART0_RX_BUFFER_SIZE not defined for <uart.h>, setting default."
    #define UART0_RX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#ifndef UART0_TX_BUFFER_SIZE
    #warning "UART0_TX_BUFFER_SIZE not defined for <uart.h>, setting default."
    #define UART0_TX_BUFFER_SIZE  32      //1,2,4,8,16,32,64,128 or 256 bytes
#endif

#define UART0_RX_BUFFER_MASK (UART0_RX_BUFFER_SIZE - 1)
#define UART0_TX_BUFFER_MASK (UART0_TX_BUFFER_SIZE - 1)

#if (UART0_RX_BUFFER_SIZE & UART0_RX_BUFFER_MASK)
    #error UART0 RX buffer size is not a power of 2
#endif

// UART 1 
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
	#error UART1 RX buffer size is not a power of 2
#endif


// /* Prototypes */
// void InitUART( unsigned char baudrate );
// unsigned char ReceiveByte( void );
// void TransmitByte( unsigned char data );

// Init uart.
void UART0_Init();
void UART1_Init();

// Send one symbol;
void UART1_SendByte(unsigned char data);
// Send char array;
void UART1_SendString(const char* data);
// Send char array with new line break.
void UART1_Println(const char* data);
// Read one symbol from receive buffer.
unsigned char UART0_ReceiveByte(void);
unsigned char UART1_ReceiveByte(void);
// Check or there is something in receive buffer.
uint8_t UART0_DataInReceiveBuffer(void);
uint8_t UART1_DataInReceiveBuffer(void);
// Read all data from buffer.
void UART0_Readln(char*);
void UART1_Readln(char*);

#ifdef UART_EXCEPTION_EVENTS
    extern void UART_Exception(char*, char*);
#endif
#ifdef UART0_NMEA_EVENT
    extern void UART0_NMEAEvent(char*);
#endif

#endif // UART_H_ 