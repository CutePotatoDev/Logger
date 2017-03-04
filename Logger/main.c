/*
 * Logger.c
  * Created: 2017-02-20 02:09:16
 */ 

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "databus/uart.h"
#include "databus/spi.h"
#include "systems/log.h"
#include "systems/uclock.h"
#include "systems/sdcard/diskio.h"
#include "systems/sdcard/ff.h"
#include "systems/sdcard/integer.h"
#include "systems/sdcard/mmc_avr.h"

#define DRV_MMC 0

int main(void) {
  
  UART_Init();
  SPI_InitMaster();
  
  static FRESULT f_err_code;
  static FATFS FATFS_Obj;
  FIL fil_obj;
  UINT ByteWrite = 0;

  char str[48];
  char* var="Testas.";

  //Korteles inicializacija.
  BYTE status = disk_initialize(DRV_MMC);
  status = disk_initialize(DRV_MMC);
  sprintf(str,"Initialize return: %X",status);
  LOG_Info(str);

  //Loginio disko uþmountinimas.
  f_err_code = f_mount(&FATFS_Obj, "", 0);
  sprintf(str,"f_mount return: %X",f_err_code);
  LOG_Info(str);
  
  //Failo atydarymas ir sukûrimas jei jo nëra.
  f_err_code = f_open(&fil_obj, "logger.txt", FA_WRITE | FA_CREATE_ALWAYS);
  sprintf(str,"f_open return: %X",f_err_code);
  LOG_Info(str);

  //Teksto áraðymas á failà.
  f_err_code = f_write(&fil_obj,var,strlen(var),&ByteWrite);
  sprintf(str,"f_write return: %X, byte wrote: %d",f_err_code,ByteWrite);
  LOG_Info(str);

  f_close(&fil_obj);

}

