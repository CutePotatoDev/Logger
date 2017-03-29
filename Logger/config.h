/*
 * config.h
 *
 * Created: 2016-12-10 21:30:34
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

#include "globals.h"

//Micro controller tactical frequency.  
#define F_CPU 16000000UL

//Enable logs.
#define LOG

//UART Config.
#define UART    //UART Module enable.
#define BAUD 9600
//#define UART_RX_BUFFER_SIZE  32
#define UART1_TX_BUFFER_SIZE  32

//Uptime clock.
//#define UCLOCK

//ADC
#define ADC_REFERENCE_AVCC


//SD Card
#define SD_CSPIN B,0
#define DRV_MMC 0
  
  
//Test leds.
#define SD_INIT_FAIL A,7
#define SD_TRANSFER_FAIL A,6
#define A5 A,5
 
  
  
#endif /* CONFIG_H_ */