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

#include <stdlib.h>

//Static Variables
static unsigned char UART0_RXBuffer[UART0_RX_BUFFER_SIZE];
static volatile unsigned char UART0_RXHead;
static volatile unsigned char UART0_RXTail;
// static unsigned char UART0_TXBuffer[UART0_TX_BUFFER_SIZE];
static volatile unsigned char UART0_TXHead;
static volatile unsigned char UART0_TXTail;

static unsigned char UART1_RXBuffer[UART1_RX_BUFFER_SIZE];
static volatile unsigned char UART1_RXHead;
static volatile unsigned char UART1_RXTail;
static unsigned char UART1_TXBuffer[UART1_TX_BUFFER_SIZE];
static volatile unsigned char UART1_TXHead;
static volatile unsigned char UART1_TXTail;


void UART0_Init(){
    unsigned char x = 0;
    //Init empty buffers.
    UART0_TXHead = x;
    UART0_TXTail = x;
    
    //Baud rate data from util/setbaud.h
    USART0_BAUD_RATE_H = UBRRH_VALUE;
    USART0_BAUD_RATE_L = UBRRL_VALUE;

    //Double speed if baud calculation enable it.
    #if USE_2X
        UCSR0A |= USART0_DOUBLE_TRANSMISSION_SPEED;
    #else
        UCSR0A &= ~(USART0_DOUBLE_TRANSMISSION_SPEED);
    #endif
    
    //Enable receiver, transmitter.
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    //8 bit packet size.
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    
    //Enable global interrupts.
    sei();
}
// char mydata[64]; //= (char*)malloc(1 * sizeof(char));

ISR(USART0_RECEIVE_INTERRUPT){
    unsigned char data;
    unsigned char tmphead;
    
    data = UDR0;                                      //Read the received data.
    //calculate buffer index
    tmphead = (UART0_RXHead + 1) & UART0_RX_BUFFER_MASK;
    UART0_RXHead = tmphead;                           //store new index
    #ifdef UART_EXCEPTION_EVENTS
        if (tmphead == UART0_RXTail){
            UART_Exception("UART0", "ERROR! Receive buffer overflow");
        }
    #endif

    UART0_RXBuffer[tmphead] = data;                  // Store received data in buffer
    
    #ifdef UART0_NMEA_EVENT
        if (data == 0x0A){ //Last char of GPS line.
            // Search says that use malloc and free is not really good. Exist posibility of memory fragmentation.
            // Check this teory here.
            char* mydata = (char*)malloc(1 * sizeof(char)); // Allocate default size of dynamic array. 
            int i = 0;  // Counter for dynamic array.

            while(UART0_DataInReceiveBuffer()){ // Read untill receive buffer become empty.
                unsigned char ttmptail = (UART0_RXTail + 1) & UART0_RX_BUFFER_MASK; // Calculate buffer index.
                UART0_RXTail = ttmptail;    // Store new index.
                mydata[i++] = UART0_RXBuffer[ttmptail]; // Add byte to array.
                mydata = (char*)realloc(mydata, (i + 1) * sizeof(char));    // Reallocate size of array.
            }
            mydata[i++] = '\0';

            UART0_NMEAEvent(mydata);
            free(mydata);   // Free up allocated memory.
        }
    #endif
}

ISR(USART0_TRANSMIT_INTERRUPT){
    // //check if all data is transmitted.
    // if (UART0_TXHead != UART0_TXTail){
    //     //calculate buffer index.
    //     unsigned char tmptail = (UART0_TXTail + 1) & UART0_TX_BUFFER_MASK;
    //     UART0_TXTail = tmptail; //store new index
    //     UDR0 = UART0_TXBuffer[tmptail]; //start transmittion.
    // } else {
    //     UCSR0B &= ~(1 << UDRIE0);   //disable UDRE interrupt.
    // }
}

unsigned char UART0_ReceiveByte(void){
    unsigned char tmptail;
    
    while (UART0_RXHead == UART0_RXTail);    //wait for incoming data.
    
    tmptail = (UART0_RXTail + 1) & UART0_RX_BUFFER_MASK;     //calculate buffer index.
    UART0_RXTail = tmptail;      //store new index.
    return UART0_RXBuffer[tmptail];     //return data.
}

uint8_t UART0_DataInReceiveBuffer(void){
    return (UART0_RXHead != UART0_RXTail);  //return 0 (FALSE) if the receive buffer is empty.
}

void UART0_Readln(char* data){
    while(UART0_DataInReceiveBuffer()){
        *data = UART0_ReceiveByte();
        data++;
    }
    UART0_RXBuffer[0] = '\0';        
}


void UART1_Init(){
    unsigned char x = 0;
    //Init empty buffers.
    UART1_TXHead = x;
    UART1_TXTail = x;
    
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
 	tmphead = (UART1_RXHead + 1) & UART1_RX_BUFFER_MASK;
 	UART1_RXHead = tmphead;                           //store new index
 	#ifdef UART_EXCEPTION_EVENTS
        if (tmphead == UART1_RXTail){
            UART_Exception("UART1", "ERROR! UART1 Receive buffer overflow");
        }
    #endif
 	UART1_RXBuffer[tmphead] = data;                  //store received data in buffer
}

ISR(USART1_TRANSMIT_INTERRUPT){
    //check if all data is transmitted.
    if (UART1_TXHead != UART1_TXTail){
        //calculate buffer index.
        unsigned char tmptail = (UART1_TXTail + 1) & UART1_TX_BUFFER_MASK;
        UART1_TXTail = tmptail;	//store new index
        UDR1 = UART1_TXBuffer[tmptail];	//start transmittion.
    } else {
        UCSR1B &= ~(1 << UDRIE1);	//disable UDRE interrupt.
    }
}

void UART1_SendByte(unsigned char data){
    //Calculate buffer index.
    unsigned char tmphead = (UART1_TXHead + 1) & UART1_TX_BUFFER_MASK; 

    //Wait for free space in buffer.
    while (tmphead == UART1_TXTail);
    UART1_TXBuffer[tmphead] = data; //Store data in buffer.
    UART1_TXHead = tmphead;  //Store new index.
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
    
    while (UART1_RXHead == UART1_RXTail);    //wait for incoming data.
    
    tmptail = (UART1_RXTail + 1) & UART1_RX_BUFFER_MASK;     //calculate buffer index.
    UART1_RXTail = tmptail;      //store new index.
    return UART1_RXBuffer[tmptail];     //return data.
}

uint8_t UART1_DataInReceiveBuffer(void){
    return (UART1_RXHead != UART1_RXTail);  //return 0 (FALSE) if the receive buffer is empty.
}

void UART1_Readln(char* data){
    while(UART1_DataInReceiveBuffer()){
        *data = UART1_ReceiveByte();
        data++;
    }
    UART1_RXBuffer[0] = '\0';        
}