/*
* debounce-zad1.c
*
* Created: 11/26/2024 12:39:55 PM
* Author : Student
*/

#include <avr/io.h>


#define RED1 PORTA0
#define YEL1 PORTA1
#define GRN1 PORTA3

#define RED2 PORTA4
#define YEL2 PORTA5
#define GRN2 PORTA6

#define SW1 PINA7
#define SW2 PINB0

#define LIMIT 100
#define IMPULSE_LIMIT 63;

volatile uint8_t impulse;
volatile uint8_t test_cnt;
volatile uint8_t btn_before;
volatile uint8_t btn_current;
volatile uint8_t debounce_cnt;
volatile uint8_t state;

typedef struct {
	volatile uint8_t btn_before;
	volatile uint8_t btn_current;
	volatile uint8_t state;
} ButtonState;

void light_up_impulse();
void impulse_increase();
void impulse_decrease();
void debounce(ButtonState *btn, void (*on_click)());


int main(void)
{
	impulse = 0;
	ButtonState btn_left = {0, 0, 0};
	ButtonState btn_right = {0, 0, 0};
	btn_before = (PINA & (1 << SW1));
	state = 0;
	DDRA = (1 << RED2) | (1 << YEL2) | (1 << GRN2) | (1 << RED1) | (1 << YEL1) | (1 << GRN1);
	DDRA &= ~(1 << SW1);
	DDRB &= ~(1 << SW2);
	
	PUEA |= 1 << SW1;
	PUEB |= 1 << SW2;
	
	while (1)
	{
		btn_left.btn_current = PINA & (1 << SW1);
		btn_right.btn_current = PINB & (1 << SW2);
		debounce(&btn_left, impulse_decrease);
		debounce(&btn_right, impulse_increase);
	}
}

void debounce(ButtonState *btn, void (*on_click)()) {
	switch(btn->state) {
		case 0:
			if (btn->btn_before != btn->btn_current) {
				btn->state = 1;
				btn->btn_before = btn->btn_current;
				break;
			}
			break;
		case 1:
			if (btn->btn_before == btn->btn_current) {
				if (debounce_cnt >= LIMIT) {
					btn->state = 2;
					impulse++;
					on_click();
					light_up_impulse();
					debounce_cnt = 0;
					} else {
					++debounce_cnt;
				}
			} else {
				btn->state = 0;
				btn->btn_before = btn->btn_current;
				debounce_cnt = 0;
			}
			break;
		case 2:
			if (btn->btn_before != btn->btn_current) {
				btn->state = 0;
				btn->btn_before = btn->btn_current;
				debounce_cnt = 0;
			}
			break;
	}
}

void light_up_impulse() {
	PORTA = 0;
	for (int i = 0; i <= 5; ++i) {
		if (impulse & (1 << i)) {
			switch (i) {
				case 0:
				PORTA |= 1 << RED2;
				break;
				case 1:
				PORTA |= 1 << YEL2;
				break;
				case 2:
				PORTA |= 1 << GRN2;
				break;
				case 3:
				PORTA |= 1 << RED1;
				break;
				case 4:
				PORTA |= 1 << YEL1;
				break;
				case 5:
				PORTA |= 1 << GRN1;
				break;
			}
		}
	}
}

void impulse_increase() {
	++impulse;
	if (impulse > 63) {
		impulse = 0;
	}
}

void impulse_decrease() {
	--impulse;
	if (impulse > 63) {
		impulse = 0;
	}
}