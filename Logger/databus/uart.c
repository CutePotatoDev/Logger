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
static unsigned char UART1_RXBuffer[UART1_RX_BUFFER_SIZE];
static volatile unsigned char UART_RXHead;
static volatile unsigned char UART_RXTail;
static unsigned char UART_TXBuffer[UART1_TX_BUFFER_SIZE];
static volatile unsigned char UART_TXHead;
static volatile unsigned char UART_TXTail;

void UART1_Init(){
    unsigned char x = 0;
    //Init empty buffers.
    //     UART_RXHead = x;
    //     UART_RXTail = x;
    UART_TXHead = x;
    UART_TXTail = x;
    
    //Baud rate data from util/setbaud.h
    USART1_BAUD_RATE_H = UBRRH_VALUE;
    USART1_BAUD_RATE_L = UBRRL_VALUE;

    //Double speed if baud calculation enable it.
    #if USE_2X
        UCSR1A |= USART1_DOUBLE_TRANSMISSION_SPEED;
    #else
        UCSR1A &= ~(USART1_DOUBLE_TRANSMISSION_SPEED);
    #endif
    
    //Enable receiver, transmitter.
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    //8 bit packet size.
    UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
    
    //Enable global interrupts.
    sei();
}

ISR(USART1_RECEIVE_INTERRUPT){
 	  unsigned char data;
 	  unsigned char tmphead;
 	  
 	  data = UDR1;                                      //Read the received data.
 	  //calculate buffer index
 	  tmphead = (UART_RXHead + 1) & UART1_RX_BUFFER_MASK;
 	  UART_RXHead = tmphead;                           //store new index
 	  if (tmphead == UART_RXTail){
// 		  /* ERROR! Receive buffer overflow */
 	  }
 	  UART1_RXBuffer[tmphead] = data;                  //store received data in buffer
}

ISR(USART1_TRANSMIT_INTERRUPT){
    //check if all data is transmitted.
    if (UART_TXHead != UART_TXTail){
        //calculate buffer index.
        unsigned char tmptail = (UART_TXTail + 1) & UART1_TX_BUFFER_MASK;
        UART_TXTail = tmptail;	//store new index
        UDR1 = UART_TXBuffer[tmptail];	//start transmittion.
    } else {
        UCSR1B &= ~(1 << UDRIE1);	//disable UDRE interrupt.
    }
}

void UART1_SendByte(unsigned char data){
    //Calculate buffer index.
    unsigned char tmphead = (UART_TXHead + 1) & UART1_TX_BUFFER_MASK; 

    //Wait for free space in buffer.
    while (tmphead == UART_TXTail);
    UART_TXBuffer[tmphead] = data; //Store data in buffer.
    UART_TXHead = tmphead;  //Store new index.
    UCSR1B |= (1 << UDRIE1);  //Enable UDRE interrupt.
}

void UART1_SendString(const char* data){	
    //Here we check if there is still more chars to send, 
    //this is done checking the actual char and see if it is different from the null char.
    
    while(*data){
        //Using the simple send function we send one char at a time.
        UART1_SendByte(*data);
        //Increment the pointer so we can read the next char.
        data++;
    }        	
}

void UART1_Println(const char* data){
    //Send line.
    UART1_SendString(data);
    //Send new line break.
    UART1_SendString("\n\r");	
}

unsigned char UART1_ReceiveByte(void){
    unsigned char tmptail;
    
    while (UART_RXHead == UART_RXTail);    //wait for incoming data.
    
    tmptail = (UART_RXTail + 1) & UART1_RX_BUFFER_MASK;     //calculate buffer index.
    UART_RXTail = tmptail;      //store new index.
    return UART1_RXBuffer[tmptail];     //return data.
}

uint8_t UART1_DataInReceiveBuffer(void){
    return (UART_RXHead != UART_RXTail);  //return 0 (FALSE) if the receive buffer is empty.
}

void UART1_Readln(char* data){
    while(UART1_DataInReceiveBuffer()){
        *data = UART1_ReceiveByte();
        data++;
    }
    UART1_RXBuffer[0] = '\0';        
}