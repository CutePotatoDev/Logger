/*
 * timer.h
 *
 * Created: 2017-02-20 04:47:49
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "avr/io.h"

//Timer 0.
#define TIMER_MODE_NORMAL  0
#define TIMER_MODE_PWM     1
#define TIMER_MODE_CTC     2
#define TIMER_MODE_FASTPWM 3

#define TIMER0_PRESCALER_NONE   (1 << CS00)
#define TIMER0_PRESCALER_8      (1 << CS01)
#define TIMER0_PRESCALER_64     ((1 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_256    (1 << CS02)
#define TIMER0_PRESCALER_1024   ((1 << CS02) | (1 << CS00))

#define TIMER0_EBABLE_COMP_INT  (1 << OCIE0A)

//Timer 2.
#define TIMER2_PRESCALER_NONE   (1 << CS20)
#define TIMER2_PRESCALER_8      (1 << CS21)
#define TIMER2_PRESCALER_32     ((1 << CS21) | (1 << CS20))
#define TIMER2_PRESCALER_64     (1 << CS22)
#define TIMER2_PRESCALER_128    ((1 << CS22) | (1 << CS20))
#define TIMER2_PRESCALER_256    ((1 << CS22) | (1 << CS21))
#define TIMER2_PRESCALER_1024   ((1 << CS22) | (1 << CS21) | (1 << CS20))

#define TIMER2_EBABLE_COMP_INT  (1 << OCIE2A)

void TIMER_0_Init(uint8_t mode, uint8_t prescaler, uint8_t interrupt, uint8_t ocr0a);
void TIMER_2_Init(uint8_t mode, uint8_t prescaler, uint8_t interrupt, uint8_t ocr0a);

#endif /* TIMER_H_ */