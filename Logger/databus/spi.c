/*
 * spi.c
 *
 * Created: 2017-01-25 08:01:26
 */ 

#include <avr/io.h>

#include "../globals.h"
#include "spi.h"

void SPI_InitMaster(void){
    //Set MOSI and SCK as output.
     OUTPUT(CS);
     OUTPUT(SCK);
     OUTPUT(MOSI);
     INPUT(MISO);
         
//      HIGH(MOSI);
//      HIGH(MISO);
//      LOW(SCK);
//      HIGH(CS);
    
    //Set double speed of SPI -> F_CPU/2.
    SPSR0 |= SPI_DOUBLE_SPEED;
    
    //Enable SPI.
    SPCR0 |= SPI_ENABLE | SPI_MASTER_ENABLE;
}

uint8_t SPI_Send(uint8_t data){
    // Load data into shift register.
    SPI_DATA_REGISTER = data;
    
    //Wait until transmission complete.
    while(!(SPSR0 & SPI_INTERRUP_ENABLE));
    
    // Return received data.
    return(SPI_DATA_REGISTER);
}