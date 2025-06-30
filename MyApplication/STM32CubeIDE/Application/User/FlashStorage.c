#include "FlashStorage.h"

#define FLASH_USER_START_ADDR   ((uint32_t)0x080E0000)
#define FLASH_SECTOR_USED       FLASH_SECTOR_11
#define DEFAULT_VALUE           0xFFFFFFFF

uint32_t Flash_ReadHighScore(void)
{
    uint32_t value = *(uint32_t*)FLASH_USER_START_ADDR;

    if (value == DEFAULT_VALUE || value > 1000){
    	return 0;
    }else{
    	return value;
    }

}

void Flash_WriteHighScore(uint32_t score)
{

    HAL_FLASH_Unlock();
    uint32_t currentValue = *(uint32_t*)FLASH_USER_START_ADDR;
    if (currentValue == score) {
        HAL_FLASH_Lock();
        return;
    }

    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SectorError = 0;

    EraseInitStruct.TypeErase    = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector       = FLASH_SECTOR_USED;
    EraseInitStruct.NbSectors    = 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) == HAL_OK)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR, score);
    }

    HAL_FLASH_Lock();
}
void Flash_Clear(void)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SectorError = 0;

    EraseInitStruct.TypeErase    = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector       = FLASH_SECTOR_USED;
    EraseInitStruct.NbSectors    = 1;

    HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError);
    HAL_FLASH_Lock();
}



