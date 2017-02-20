/*
 * uart.c
 *
 * Created: 2016-12-10 20:39:31
 */ 

#include "../config.h"
#include "uart.h"

#include <avr/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>


//Static Variables
// static unsigned char UART_RXBuffer[UART_RX_BUFFER_SIZE];
// static volatile unsigned char UART_RXHead;
// static volatile unsigned char UART_RXTail;
static unsigned char UART_TXBuffer[UART_TX_BUFFER_SIZE];
static volatile unsigned char UART_TXHead;
static volatile unsigned char UART_TXTail;

void UART_Init(){
    unsigned char x = 0;
    //Init empty buffers.
    //     UART_RXHead = x;
    //     UART_RXTail = x;
    UART_TXHead = x;
    UART_TXTail = x;
    
    //Baud rate data from util/setbaud.h
    USART_BAUD_RATE_H = UBRRH_VALUE;
    USART_BAUD_RATE_L = UBRRL_VALUE;

    //Double speed if baud calculation enable it.
    #if USE_2X
        UCSR0A |= USART_DOUBLE_TRANSMISSION_SPEED;
    #else
        UCSR0A &= ~(USART_DOUBLE_TRANSMISSION_SPEED);
    #endif
    
    //Enable receiver, transmitter.
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    //8 bit packet size.
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    
    //Enable global interrupts.
    sei();
}

// ISR(USART_RX_vect){
// 	  unsigned char data;
// 	  unsigned char tmphead;
// 	  
// 	  data = UDR;                                      /* read the received data */
// 	  /* calculate buffer index */
// 	  tmphead = ( UART_RxHead + 1 ) & UART_RX_BUFFER_MASK;
// 	  UART_RxHead = tmphead;                           /* store new index */
// 	  if ( tmphead == UART_RxTail )
// 	  {
// 		  /* ERROR! Receive buffer overflow */
// 	  }
// 	  UART_RxBuf[tmphead] = data;                      /* store received data in buffer */
// }

ISR(USART_TRANSMIT_INTERRUPT){
    //check if all data is transmitted.
    if (UART_TXHead != UART_TXTail){
        //calculate buffer index.
        unsigned char tmptail = (UART_TXTail + 1) & UART_TX_BUFFER_MASK;
        UART_TXTail = tmptail;	//store new index
        UDR0 = UART_TXBuffer[tmptail];	//start transmittion.
    } else {
        UCSR0B &= ~(1 << UDRIE0);	//disable UDRE interrupt.
    }
}

void UART_SendByte(unsigned char data){
    //Calculate buffer index.
    unsigned char tmphead = (UART_TXHead + 1) & UART_TX_BUFFER_MASK; 

    //Wait for free space in buffer.
    while (tmphead == UART_TXTail);
    UART_TXBuffer[tmphead] = data; //Store data in buffer.
    UART_TXHead = tmphead;  //Store new index.
    UCSR0B |= (1 << UDRIE0);  //Enable UDRE interrupt.
}

void UART_SendString(const char* data){	
    //Here we check if there is still more chars to send, 
    //this is done checking the actual char and see if it is different from the null char.
    
    while(*data){
        //Using the simple send function we send one char at a time.
        UART_SendByte(*data);
        //Increment the pointer so we can read the next char.
        data++;
    }        	
}

void UART_Println(const char* data){
    //Send line.
    UART_SendString(data);
    //Send new line break.
    UART_SendString("\n\r");	
}