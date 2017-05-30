/*
 * rtc.h
 *
 * Created: 2017-03-30 13:33:43
 */ 


#ifndef RTC_H_
#define RTC_H_

struct Time {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t months;
    uint8_t years;
} time;

//Set RTC time.
void RTC_Set(struct Time);
//Start RTC.
void RTC_Start();
//Stop RTC.
void RTC_Stop();
//Get status of RTC. Running or Stoped.
uint8_t RTC_Status();
//Get string formated time.
char* RTC_GetTimeString();

#endif /* RTC_H_ */