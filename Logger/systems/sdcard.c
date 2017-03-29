/*
 * sdcard.c
 *
 * Created: 2017-02-21 10:52:28
 */ 

#include "../config.h"
#include "sdcard/diskio.h"
#include "sdcard/ff.h"
#include "timer.h"
#include "log.h"
#include "uclock.h"

#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include <util/delay.h>

char str[64];
static FRESULT err_code;
char filename[12];

uint8_t SDCARD_Mount(void){
    static FATFS FATFS_Obj;
    
    //Card disk init.
    BYTE status = disk_initialize(DRV_MMC);
    sprintf(str,"SDCARD -> Initialize return: %X", status);
    if(status != 0){
        LOG_Error(str);
        HIGH(SD_INIT_FAIL);
        return status;
    } else {
        LOG_Info(str);
        LOW(SD_INIT_FAIL);
    }
    
    //Disk mount.
    err_code = f_mount(&FATFS_Obj, "0:", 1);
    sprintf(str,"SDCARD -> f_mount return: %X", err_code);
    if(err_code != 0){
        LOG_Error(str);
        HIGH(SD_INIT_FAIL);
        return err_code;
    } else {
        LOG_Info(str);
        LOW(SD_INIT_FAIL);
    }
    
    sprintf(filename, "%s.txt", UCLOCK_Uptime_Dellimiter(""));
    
    return 0;
}

void SDCARD_Reinit(void){
    for(int i = 1; i < 11; i++){ // 10 aptemts to init card.
        if(SDCARD_Mount() != 0) { //If not 0 then init failed... Probably good idea try to reinit.
            LOG_Error("SDCARD -> Init Failed. Try one more time after 25 sec.");
            _delay_ms(25000); //Try every 30 sec.
            } else {
            LOG_Info("SDCARD -> Init OK. File name:");
            LOG_Info(filename);
            break;
        }
    }
    //Need something like master error...
}

void SDCARD_Init(void) {
    //Set timer with interrupt at almost 10 ms.
    TIMER_2_Init(TIMER_MODE_CTC, TIMER2_PRESCALER_1024, TIMER_MODE_CTC, 0x9C);

    SDCARD_Reinit();
}


uint8_t SDCARD_Write(char * var){
    FIL file;
    UINT ByteWrite = 0;

    err_code = f_open(&file, filename, FA_WRITE | FA_OPEN_APPEND);
    //err_code = f_lseek(&file, f_size(&file));
    
    if(err_code != 0){
        sprintf(str,"SDCARD -> f_open return: %X", err_code);
        LOG_Error(str);
        HIGH(SD_TRANSFER_FAIL);
        return err_code;
    }    


    err_code = f_write(&file, var, strlen(var), &ByteWrite);
    
    if(err_code != 0){
        sprintf(str,"SDCARD -> f_write return: %X, byte wrote: %d", err_code, ByteWrite);
        LOG_Error(str);
        HIGH(SD_TRANSFER_FAIL);
        return err_code;
    } else 
        LOW(SD_TRANSFER_FAIL);

    f_close(&file);

    return 0;
}

ISR(TIMER2_COMPA_vect) {
    disk_timerproc();
}