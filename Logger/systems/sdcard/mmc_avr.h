#ifndef _MMC_DEFINED
#define _MMC_DEFINED

#include "diskio.h"

#ifdef __cplusplus
    extern "C" {
#endif

DSTATUS mmc_disk_initialize (void);
DSTATUS mmc_disk_status (void);
DRESULT mmc_disk_read (BYTE* buff, DWORD sector, UINT count);
DRESULT mmc_disk_write (const BYTE* buff, DWORD sector, UINT count);
DRESULT mmc_disk_ioctl (BYTE cmd, void* buff);
void mmc_disk_timerproc (void);

#ifdef __cplusplus
    }
#endif
#endif
