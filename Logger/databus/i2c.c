/*
 * i2c.c
 *
 * Created: 2017-03-29 10:18:44
 */ 

#include "../config.h"
#include <avr/io.h>
#include <compat/twi.h>
#include "i2c.h"


void I2C_Init(void) {   
    TWSR = 0;   // TWPS = 0 as prescaller = 1
    TWBR = ((F_CPU/I2C_SCL_CLOCK) - 16) / 2;    //I2C Clock speed.
}

uint8_t I2C_Start(uint8_t address) {

    TWCR = TWI_INTERRUPT | TWI_START_COND | TWI_ENABLE; //Enable TWI send start condition.

    while(!(TWCR & TWI_INTERRUPT)); //Wait until transmission completed.

    
    if ((TWI_STATUS != TW_START) && (TWI_STATUS != TW_REP_START)) //Check value of TWI Status Register. Mask prescaller bits.
        return 1;
    
    TWDR = address;
    TWCR = TWI_INTERRUPT | TWI_ENABLE; // Send device address.

    while(!(TWCR & TWI_INTERRUPT)); // wail until transmission completed and ACK/NACK has been received.

    // Check value of TWI Status Register. Mask prescaler bits.
    if ((TWI_STATUS != TW_MT_SLA_ACK) && (TWI_STATUS != TW_MR_SLA_ACK))
        return 1;

    return 0;
}

uint8_t I2C_Write(uint8_t data) {
    uint8_t   twst;
    
    //Send data to the previously addressed device.
    TWDR = data;
    TWCR = TWI_INTERRUPT | TWI_ENABLE;

    //Wait until transmission completed.
    while(!(TWCR & TWI_INTERRUPT));

    //Check value of TWI Status Register. Mask prescaler bits.
    if(TWI_STATUS != TW_MT_DATA_ACK) 
        return 1;
    return 0;
}

uint8_t I2C_ReadACK(void) {
    TWCR = TWI_INTERRUPT | TWI_ENABLE | TWI_ENABLE_ACK; //Enable TWI ACK condition.
    while(!(TWCR & TWI_INTERRUPT));

    return TWDR;
}

uint8_t I2C_ReadNACK(void) {
    TWCR = TWI_INTERRUPT | TWI_ENABLE;
    while(!(TWCR & TWI_INTERRUPT));
    
    return TWDR;
}

void I2C_Stop(void) {
    TWCR = TWI_INTERRUPT | TWI_ENABLE | TWI_STOP;
    
    while(TWCR & TWI_STOP); //Wait until stop condition is executed and bus released.
}