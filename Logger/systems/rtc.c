/*
 * rtc.c
 *
 * Created: 2017-03-30 13:33:26
 */ 

#include "../config.h"
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#include "../databus/i2c.h"
#include "./rtc.h"


void RTC_Set(struct Time tim){
    I2C_Start(RTC_ADDRESS + I2C_WRITE);
    I2C_Write(0x00); //Set address.
    I2C_Write(tim.seconds | 0x80); //Keep clock disabled.
    I2C_Write(tim.minutes);
    I2C_Write(tim.hours);
    I2C_Write(0x00);  //Don't care about week day.
    I2C_Write(tim.days);
    I2C_Write(tim.months);
    I2C_Write(tim.years);
    I2C_Stop();    
}

void RTC_Start(){
    I2C_Start(RTC_ADDRESS + I2C_WRITE);
    I2C_Write(0x00); //Set address.
    I2C_Write(0x00); //Write data.
    I2C_Stop();
}

void RTC_Stop(){
    I2C_Start(RTC_ADDRESS + I2C_WRITE);
    I2C_Write(0x00); //Set address.
    I2C_Write(0x80); //Write data.
    I2C_Stop();
}

uint8_t RTC_Status(){
    I2C_Start(RTC_ADDRESS + I2C_WRITE);
    I2C_Write(0x00);
    I2C_Start(RTC_ADDRESS + I2C_READ);
    uint8_t status = I2C_ReadNACK() & 0x80;
    I2C_Stop();
    
    return status == 0;
}

struct Time RTC_GetTime(){
    I2C_Start(RTC_ADDRESS + I2C_WRITE);
    I2C_Write(0x00);    //Set Read address.
    I2C_Start(RTC_ADDRESS + I2C_READ);
    
    //Start reading time;
    time.seconds = I2C_ReadACK() & 0x7F;
    time.minutes = I2C_ReadACK();
    time.hours = I2C_ReadACK();
                 I2C_ReadACK(); // Dummy read for day of week.
    time.days = I2C_ReadACK();
    time.months = I2C_ReadACK();
    time.years = I2C_ReadNACK();
    
    I2C_Stop();
    
    return time;
}

char* RTC_GetTimeString(){
    RTC_GetTime();
    char* currenttime = malloc(17 * sizeof(char));
    //Format time as String.
    sprintf(currenttime, "%02X-%02X-%02X %02X:%02X:%02X", time.years, time.months, time.days, time.hours, time.minutes, time.seconds);
    
    return currenttime;
}