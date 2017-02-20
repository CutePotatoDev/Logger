/*
 * uclock.c
 *
 * Created: 2017-01-10 01:18:13
 */ 

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>

//Useful Constants.
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

//Useful Macros for getting elapsed time.
#define Seconds(_time_) ((_time_ / 1000) % SECS_PER_MIN)
#define Minutes(_time_) (((_time_ / 1000) / SECS_PER_MIN) % SECS_PER_MIN)
#define Hours(_time_) (((_time_ / 1000) % SECS_PER_DAY) / SECS_PER_HOUR)
#define Days(_time_) ((_time_ / 1000) / SECS_PER_DAY)

unsigned long milliseconds;

void UCLOCK_Init(){
	//Set compare match register to desired timer count.
	//F9 for one millisecond.
	OCR0A = 0xF9;
	
	//Turn on CTC mode.
	TCCR0A = (1 << WGM01);
	
	//Set /64 prescaler.
	TCCR0B = (1 << CS01) | (1 << CS00);
	
	//Enable timer compare interrupt.
	TIMSK0 = (1 << OCIE0A);
	
	//Enable global interrupts.
	sei();
}

ISR(TIMER0_COMPA_vect){
	//Increase millisecond on interruopt;
	milliseconds++;
}

unsigned long UCLOCK_Millis(){
	unsigned long millis;
	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		millis = milliseconds;
	}
	return millis;
}

void NumberFormat(char* s, unsigned int val){
	char tmp[3];
	
	//Convert unsigned long int to string.
	ltoa(val, tmp, 10);
	
	//Add zero before one digit number.
	if(val < 10){
		strcat(s, "0");
		strcat(s, tmp);
	} else
		strcat(s, tmp);
}

char uptime[12];

char* UCLOCK_Uptime(){
	//Init uptime.
	*uptime = 0;
	unsigned long millis = UCLOCK_Millis();
	
	NumberFormat(uptime, Days(millis));
	strcat(uptime, ":");
	NumberFormat(uptime, Hours(millis));
	strcat(uptime, ":");
	NumberFormat(uptime, Minutes(millis));
	strcat(uptime, ":");
	NumberFormat(uptime, Seconds(millis));
	
	return uptime;
}