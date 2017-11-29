#include "flash.h"

/* Base address of the Flash sectors */ 
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */


u8 ClearDataFlash(void)
{
	return ClearFlash(FLASH_Sector_11);
}

u8 ClearFlash(uint16_t sector)
{
	u8 _return = False;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	if (FLASH_EraseSector(sector, VoltageRange_3) != FLASH_COMPLETE)
    { 
      _return = False;// ß∞‹
    }
	FLASH_Lock(); 
	_return = True;	//≥…π¶
	return _return;
}

u8 GetActPage(void)
{
	u8 i;
	for(i=0;i<PAGE_NUM;i++)
	{
		if((*(__IO uint32_t*)(FLASH_USER_START_ADDR+i*PAGE_BYTES))==0xffffffff)
		{
			return i;
		}
	}
	return 0xff;
}

u8 WriteFloat(uint32_t start_addr, uint16_t cnt, float data)
{
	uint32_t temp;
	if(cnt>510)
		return False;

	temp = *(uint32_t *)(&data);
	if(FLASH_ProgramWord(start_addr+(cnt*4), temp) == FLASH_COMPLETE)
		return True;
	else 
		return False;	//–¥»Î ß∞‹
}

u8 WriteInt(uint32_t start_addr, uint16_t cnt, uint32_t data)
{
	if(cnt>510)
		return False;

	if(FLASH_ProgramWord(start_addr+(cnt*4), data) == FLASH_COMPLETE)
		return True;
	else 
		return False;	//–¥»Î ß∞‹
}

float ReadFloat(uint32_t start_addr, uint16_t cnt)
{
	uint32_t temp = *(__IO uint32_t*)(start_addr+(cnt*4));
	return *(float *)(&temp);
}

uint32_t ReadInt(uint32_t start_addr, uint16_t cnt)
{
	return *(__IO uint32_t*)(start_addr+(cnt*4));
}

