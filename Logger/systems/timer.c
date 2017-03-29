/*
 * timer.c
 *
 * Created: 2017-02-20 04:47:36
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

//8-bit timer.
void TIMER_0_Init(uint8_t mode, uint8_t prescaler, uint8_t interrupt, uint8_t ocr0a) {
    
    //Set prescaler.
    TCCR0B = prescaler;
    
    //Set mode of timer.
    switch (mode) {
    case TIMER_MODE_NORMAL:
        //TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
        //TCCR0B &= ~(1 << WGM02);
    	break;
    case TIMER_MODE_PWM:
        TCCR0A |= 1 << WGM00;
        break;
    case TIMER_MODE_CTC:
        TCCR0A |= 1 << WGM01;
        break;
    case TIMER_MODE_FASTPWM:
        TCCR0A |= (1 << WGM01) | (1 << WGM00);
        break;
    }
    
    //Set compare match register to desired timer count.
    OCR0A = ocr0a;
    
    //Enable timer interrupt.
    if(interrupt != 0) {
        TIMSK0 = interrupt;
        sei();
    }
}


//8-bit timer.
void TIMER_2_Init(uint8_t mode, uint8_t prescaler, uint8_t interrupt, uint8_t ocr0a) {
    
    //Set prescaler.
    TCCR2B = prescaler;
    
    //Set mode of timer.
    switch (mode) {
        case TIMER_MODE_NORMAL:
        //TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
        //TCCR0B &= ~(1 << WGM02);
        break;
        case TIMER_MODE_PWM:
        TCCR2A |= 1 << WGM20;
        break;
        case TIMER_MODE_CTC:
        TCCR2A |= 1 << WGM21;
        break;
        case TIMER_MODE_FASTPWM:
        TCCR2A |= (1 << WGM21) | (1 << WGM20);
        break;
    }
    
    //Set compare match register to desired timer count.
    OCR2A = ocr0a;
    
    //Enable timer interrupt.
    if(interrupt != 0) {
        TIMSK2 = interrupt;
        sei();
    }
}