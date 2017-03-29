/*
 * uclock.h
 *
 * Created: 2017-01-09 22:22:48
 */ 


#ifndef UCLOCK_H_
#define UCLOCK_H_

//Init UCLOCK;
void UCLOCK_Init();

//Get milliseconds from system start.
unsigned int UCLOCK_Millis();
//Return String formated uptime value.
char* UCLOCK_Uptime();
char* UCLOCK_Uptime_Dellimiter(char * del);
#endif /* UCLOCK_H_ */