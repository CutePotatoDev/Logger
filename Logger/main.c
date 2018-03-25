/*
* Logger.c
* Created: 2017-02-20 02:09:16
*/ 

//This include must go first. gave FCU and other imostant defines.
#include "config.h"


#include <avr/io.h>
#include <util/delay.h>
// #include <avr/pgmspace.h>
#include <string.h>
// #include <stdio.h>

#include "systems/uclock.h"
#include "databus/uart.h"
// #include "databus/spi.h"
// #include "databus//i2c.h"
#include "systems/log.h"
// #include "systems/rtc.h"

// #include "systems/sdcard.h"
// #include "systems/sdcard/diskio.h"


void UART_Exception(char* port, char* message){
    LOG_Error(message);   
}

void UART0_NMEAEvent(char* message){
    // LOG_Info(message);
    char msgtype[6]; 
    strncpy(msgtype, message, 6);  
    // LOG_Info(msgtype);

    if(strcmp(msgtype, "$GPGGA") == 0){
        UART1_SendString(message);
        // LOG_Info(message);
    } else if (strcmp(msgtype, "$GPRMC") == 0){
        UART1_SendString(message);
        // LOG_Info(message);
    }

    // switch(strsep(&message, ",")){
    //     case "$$GPGGA":
    //         LOG_Info(message);
    //     break;
    //     case "$GPRMC":
    //         LOG_Info(message);   
    //     break;
    // }   
}

// uint8_t StartWith(const char *str, const char *pre){
//     size_t lenpre = strlen(pre),
//     lenstr = strlen(str);
//     return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
// }

// uint8_t ASCIItoBCD(char number[2]){
//     uint8_t bcd_value;

//     bcd_value = (number[0] - 48)  << 4 ;   // 48 for '0' ASCII offset
//     bcd_value |= (number[1] - 48) ; // 97 for 'a' ASCII offset

//     return bcd_value;
// }

// void CommandsRoutine(void){
//     if(UART1_DataInReceiveBuffer()){
//         char command[24];
//         for(int i = 0; i < sizeof(command); i++)
//             command[i] = '\0';

//         char out[32];

//         UART1_Readln(command);

//         #ifdef UART1_ECHO_COMMANDS
//             UART1_Println(command);
//         #endif

//         if(strcmp(command, "RTC") == 0){
//             //UART1_Println(RTC_GetTimeString());
//             sprintf(out, "\nStatus: %s\nTime: %s", RTC_Status() == 1 ? "RUNNING" : "STOPED", RTC_GetTimeString());
//             LOG_Info(out);
//         } else if(StartWith(command, "RTCSET ")){

//             uint8_t commandlen = strlen(command);
//             if(commandlen < 19 || commandlen > 19){
//                 LOG_Error("Incorrect command format.");
//                 return;
//             }

//             char tmp[2];

//             strncpy(tmp, command + 7, 2);
//             time.years = ASCIItoBCD(tmp);
//             strncpy(tmp, command + 9, 2);
//             time.months = ASCIItoBCD(tmp);
//             strncpy(tmp, command + 11, 2);
//             time.days = ASCIItoBCD(tmp);
//             strncpy(tmp, command + 13, 2);
//             time.hours = ASCIItoBCD(tmp);
//             strncpy(tmp, command + 15, 2);
//             time.minutes = ASCIItoBCD(tmp);
//             strncpy(tmp, command + 17, 2);
//             time.seconds = ASCIItoBCD(tmp);

//             RTC_Set(time);
//             LOG_Info("RTC configured.");
//             sprintf(out, "\nStatus: %s\nTime: %s", RTC_Status() == 1 ? "RUNNING" : "STOPED", RTC_GetTimeString());
//             LOG_Info(out);               
//         } else if(StartWith(command, "RTCSTART")){
//             RTC_Start();
//             LOG_Info("RTC Started.");
//             sprintf(out, "\nStatus: %s\nTime: %s", RTC_Status() == 1 ? "RUNNING" : "STOPED", RTC_GetTimeString());
//             LOG_Info(out);
//         } else if(StartWith(command, "RTCSTOP")){
//             RTC_Stop();
//             LOG_Info("RTC Stopped.");
//             sprintf(out, "\nStatus: %s\nTime: %s", RTC_Status() == 1 ? "RUNNING" : "STOPED", RTC_GetTimeString());
//             LOG_Info(out);
//         }   

//     }
// }    


int main(void) {
  OUTPUT(SD_INIT_FAIL);
  OUTPUT(SD_TRANSFER_FAIL);
  OUTPUT(SD_CSPIN);
  OUTPUT(A5);

  for(int i = 7; i > 4; i--){
    if(i < 7)
      PORTA &= ~(1 << (i + 1));
    if(i == 5) break;

    PORTA |= 1 << i;
    _delay_ms(500);
  }

  UCLOCK_Init();
  UART0_Init();
  UART1_Init();
    // SPI_InitMaster();
    // SDCARD_Init();

    // I2C_Init();

  char sec[16];

  while (1){
        //CommandsRoutine();


//         if(UART0_DataInReceiveBuffer()){
//             char command[64];

// //         char out[32];
//             // command[0] = '\0';
//             // UART0_Readln(command);

//             UART1_SendByte(UART0_ReceiveByte());
//         }


         // uint8_t status = SDCARD_Write("Testas.\r\n");

         // if (status == 9 || status == 1) {
             // LOG_Error("MAIN -> Write fail. Possibly removed cart. Reinit Card.");
             // SDCARD_Reinit();
         // }
//          

//          
//          
//          
        // LOG_Info(sec);
    _delay_ms(1500);
  }

}

