/*
 * log.c
 *
 * Created: 2017-01-10 00:35:31
 */ 

#include <stdlib.h>
#include <string.h>
#include "uclock.h"
#include "../databus/uart.h"

char log_[256];

void LOG_Config(char* s){

	strcpy(log_, UCLOCK_Uptime());
	strcat(log_, " [C] ");
	strcat(log_, s);
	
	UART_Println(log_);
}

void LOG_Info(char* s){
	
	strcpy(log_, UCLOCK_Uptime());
	strcat(log_, " [I] ");
	strcat(log_, s);
	
	UART_Println(log_);
}

void LOG_Warning(char* s){
	
	strcpy(log_, UCLOCK_Uptime());
	strcat(log_, " [W] ");
	strcat(log_, s);
	
	UART_Println(log_);
}

void LOG_Error(char* s){
	
	strcpy(log_, UCLOCK_Uptime());
	strcat(log_, " [E] ");
	strcat(log_, s);
	
	UART_Println(log_);
}
