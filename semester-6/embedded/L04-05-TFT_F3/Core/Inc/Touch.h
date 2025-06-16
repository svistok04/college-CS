#ifndef __TOUCH_H_
#define __TOUCH_H_

#include <stdint.h>

#define TP_PRESS_DOWN           0x80
#define TP_PRESSED              0x40

typedef struct {
	uint16_t hwXpos0;
	uint16_t hwYpos0;
	uint16_t hwXpos;
	uint16_t hwYpos;
	uint8_t chStatus;
	uint8_t chType;
	short iXoff;
	short iYoff;
	float fXfac;
	float fYfac;
} tp_dev_t;

extern void tp_init(void);
extern void tp_adjust(void);
extern void tp_dialog(void);
extern void tp_draw_board(void);

#endif



