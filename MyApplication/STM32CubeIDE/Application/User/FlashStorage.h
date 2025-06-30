#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

uint32_t Flash_ReadHighScore(void);
void Flash_WriteHighScore(uint32_t score);
void Flash_Clear(void);

#ifdef __cplusplus
}
#endif

#endif
