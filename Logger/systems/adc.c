/*
 * adc.c
 *
 * Created: 2017-02-20 03:06:33
 */ 

#include <avr/io.h>

#include "../config.h"


void ADC_Init(uint8_t reference) {
    //ADC enable.
    ADCSRA = 1 << ADEN;
    
    //By default, the successive approximation circuitry requires an input clock frequency between 50kHz and
    //200kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the input clock frequency to the
    //ADC can be higher than 200kHz to get a higher sample rate.
    ADCSRA |= (1 << ADPS2) |(1 << ADPS1) | (1 << ADPS0);
    
    #ifdef ADC_REFERENCE_AREF
        #pragma message "ADC reference AREF."
        ADMUX &= ~((1 << REFS1) | (1 << REFS0));
    #endif
    
    #ifdef ADC_REFERENCE_AVCC
        #pragma message "ADC reference AVCC."
        ADMUX |= 1 << REFS0;
    #endif
    
    #ifdef ADC_REFERENCE_INTERNAL
        #pragma message "ADC reference INTERNAL."
        ADMUX |= (1 << REFS1 | 1 << REFS0);
    #endif
}

uint16_t ADC_Read(uint8_t adcx) {  //ADC function.
    
    ADMUX |= adcx;  //adcx pin number in use.
    ADCSRA |= 1 << ADSC; //This starts the conversion.

    while ((ADCSRA & (1 << ADSC)));

    return ADC; //Return ADC.
}