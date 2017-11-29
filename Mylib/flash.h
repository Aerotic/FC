#ifndef __FLASH_H__
#define __FLASH_H__

#include "board.h"

#define FLASH_USER_START_ADDR   (uint32_t)0x080E0000
#define FLASH_USER_END_ADDR     (uint32_t)0x080FFFFF

#define PAGE_BYTES	2048
#define PAGE_NUM		64

#define True    1
#define False   0


u8 ClearDataFlash(void);
u8 ClearFlash(uint16_t sector);
u8 GetActPage(void);
u8 GetActPage(void);

u8 WriteFloat(uint32_t start_addr, uint16_t cnt, float data);
u8 WriteInt(uint32_t start_addr, uint16_t cnt, uint32_t data);
float ReadFloat(uint32_t start_addr, uint16_t cnt);
uint32_t ReadInt(uint32_t start_addr, uint16_t cnt);

#endif













