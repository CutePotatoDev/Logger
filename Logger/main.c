/*
 * Logger.c
  * Created: 2017-02-20 02:09:16
 */ 

//This include must go first. gave FCU and other imostant defines.
#include "config.h"


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "systems/uclock.h"
#include "databus/uart.h"
#include "databus/spi.h"
#include "systems/log.h"

#include "systems/sdcard.h"
#include "systems/sdcard/diskio.h"


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
    UART1_Init();
    SPI_InitMaster();
    SDCARD_Init();

    while (1){

         uint8_t status = SDCARD_Write("Testas.\r\n");
         
         if (status == 9 || status == 1) {
             LOG_Error("MAIN -> Write fail. Possibly removed cart. Reinit Card.");
             SDCARD_Reinit();
         }
         
         _delay_ms(1000);
    }

}

