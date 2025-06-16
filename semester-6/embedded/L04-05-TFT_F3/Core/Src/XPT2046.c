#include "XPT2046.h"

uint8_t xpt2046_write_byte(uint8_t chData)
{
		uint8_t r_val;
		HAL_SPI_TransmitReceive(&hspi1,&chData,&r_val,1,0xff);
    return r_val;
}


void xpt2046_init(void)
{		
	__XPT2046_CS_SET();
}

uint16_t xpt2046_read_ad_value(uint8_t chCmd)
{
    uint16_t hwData = 0;
    
    __XPT2046_CS_CLR();
    xpt2046_write_byte(chCmd);
    hwData = xpt2046_write_byte(0x00);
    hwData <<= 8;
    hwData |= xpt2046_write_byte(0x00);
    hwData >>= 4;
   __XPT2046_CS_SET();
    
    return hwData;
}

#define READ_TIMES  5
#define LOST_NUM    1
uint16_t xpt2046_read_average(uint8_t chCmd)
{
    uint8_t i, j;
    uint16_t hwbuffer[READ_TIMES], hwSum = 0, hwTemp;

    for (i = 0; i < READ_TIMES; i ++) {
        hwbuffer[i] = xpt2046_read_ad_value(chCmd);
    }
    for (i = 0; i < READ_TIMES - 1; i ++) {
        for (j = i + 1; j < READ_TIMES; j ++) {
            if (hwbuffer[i] > hwbuffer[j]) {
                hwTemp = hwbuffer[i];
                hwbuffer[i] = hwbuffer[j];
                hwbuffer[j] = hwTemp;
            }
        }
    }
    for (i = LOST_NUM; i < READ_TIMES - LOST_NUM; i ++) {
        hwSum += hwbuffer[i];
    }
    hwTemp = hwSum / (READ_TIMES - 2 * LOST_NUM);

    return hwTemp;
}


void xpt2046_read_xy(uint16_t *phwXpos, uint16_t *phwYpos)
{
	*phwXpos = xpt2046_read_average(0xD0);
	*phwYpos = xpt2046_read_average(0x90);
}


#define ERR_RANGE 50
bool xpt2046_twice_read_xy(uint16_t *phwXpos, uint16_t *phwYpos)
{
	uint16_t hwXpos1, hwYpos1, hwXpos2, hwYpos2;

	xpt2046_read_xy(&hwXpos1, &hwYpos1);
	xpt2046_read_xy(&hwXpos2, &hwYpos2);

	if (((hwXpos2 <= hwXpos1 && hwXpos1 < hwXpos2 + ERR_RANGE) || (hwXpos1 <= hwXpos2 && hwXpos2 < hwXpos1 + ERR_RANGE))
	&& ((hwYpos2 <= hwYpos1 && hwYpos1 < hwYpos2 + ERR_RANGE) || (hwYpos1 <= hwYpos2 && hwYpos2 < hwYpos1 + ERR_RANGE))) {
		*phwXpos = (hwXpos1 + hwXpos2) / 2;
		*phwYpos = (hwYpos1 + hwYpos2) / 2;
		return true;
	}

	return false;
}


