/*
 * adc.h
 *
 * Created: 2017-02-20 03:06:09
 */ 

#ifndef ADC_H_
#define ADC_H_

#define VREF 5.0

#define ADC_STEP VREF/1024.0
#define	ADC_TMP   			3  //Temperature.
#define	ADC_PRESS1			4  //Pressure 1.
#define	ADC_PRESS2			5  //Pressure 2.

#define ADC_REFERENCE_AREF; //Or ADC_REFERENCE_AVCC, ADC_REFERENCE_INTERNAL

uint16_t ADC_Read(uint8_t adcx);  // ADC Read function.

#endif /* ADC_H_ */