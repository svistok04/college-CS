/*
 * usart.c
 *
 * Created: 1/14/2025 12:26:38 PM
 * Author : Student
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR 6 //FOSC/16/BAUD-1

#define RED1 PORTA0
#define YEL1 PORTA1
#define GRN1 PORTA3

#define RED2 PORTA4
#define YEL2 PORTA5
#define GRN2 PORTA6

#define SW1 PINA7
#define SW2 PINB0

#define LIMIT 100

volatile uint8_t btn_before;
volatile uint8_t btn_current;
volatile uint8_t debounce_cnt;
volatile uint8_t state;
typedef struct {
	volatile uint8_t btn_before;
	volatile uint8_t btn_current;
	volatile uint8_t debounce_cnt;
	volatile uint8_t state;
} ButtonState;
volatile uint8_t data1;
volatile uint8_t data2;
volatile uint8_t impulse;
void light_up_impulse_1();
void light_up_impulse_2();
void USART_Init(uint16_t ubrr);
void USART_Transmit(uint8_t data);
void right_click() {
	++data1;
	if (data1 > 7) {
		data1 = 0;
	}
	impulse = data2 << 3 | data1;
	light_up_impulse();
	//light_up_impulse_1();
}

void left_click() {
}


void debounce(ButtonState *btn, void (*on_click)());


ISR(USART_RXS_vect) {
		data2 = UDR;
		impulse = data2 << 3 | data1;
		light_up_impulse();
		//light_up_impulse_2(data2);
}

ISR(USART_TXC_vect) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = data1;
}

int main(void)
{
    /* Replace with your application code */
	USART_Init(MYUBRR);

	data1 = 0;
	data2 = 0;
	ButtonState btn_left = {0, 0, 0, 0};
	ButtonState btn_right = {0, 0, 0, 0};
	btn_left.btn_before = (PINA & (1 << SW1));
	btn_right.btn_before = (PINB & (1 << SW2));
	state = 0;
	DDRA = (1 << RED2) | (1 << YEL2) | (1 << GRN2) | (1 << RED1) | (1 << YEL1) | (1 << GRN1);
	DDRA &= ~(1 << SW1);
	DDRB &= ~(1 << SW2);
		
	PUEA |= 1 << SW1;
	PUEB |= 1 << SW2;
	PORTA = 0;
	sei();
	while (1)
	{
		btn_left.btn_current = PINA & (1 << SW1);
		btn_right.btn_current = PINB & (1 << SW2);
		debounce(&btn_left, left_click);
		debounce(&btn_right, right_click);
	}
}

void USART_Init(uint16_t ubrr)
{
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << UCSZ0) | (1 << UCSZ1);
}




/*
void light_up_impulse_1() {
	PORTA &= (0 << RED2) | (0 << YEL2) | (0 << GRN2);
	for (int i = 0; i <= 2; ++i) {
		if (data1 & (1 << i)) {
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
			}
		}
	}
}

void light_up_impulse_2() {
	PORTA &= (0 << RED1) | (0 << YEL1) | (0 << GRN1);
	for (int i = 0; i <= 2; ++i) {
		if (data2 & (1 << i)) {
			switch (i) {
				case 0:
				PORTA |= 1 << RED1;
				break;
				case 1:
				PORTA |= 1 << YEL1;
				break;
				case 2:
				PORTA |= 1 << GRN1;
				break;
			}
		}
	}
} */


void debounce(ButtonState *btn, void (*on_click)()) {
	switch(btn->state) {
		case 0:
			//PORTA |= 1 << RED1;
			if (btn->btn_before != btn->btn_current) {
				btn->state = 1;
				btn->btn_before = btn->btn_current;
				break;
			}
			break;	
		case 1:
			//PORTA |= 1 << YEL1;
			if (btn->btn_before == btn->btn_current) {
				if (btn->debounce_cnt >= LIMIT) {
					btn->state = 2;
					on_click();
					impulse = data2 << 3 | data1;
					light_up_impulse();
					/*light_up_impulse_1();
					light_up_impulse_2();*/
					btn->debounce_cnt = 0;
					} else {
					++btn->debounce_cnt;
				}
				} else {
				btn->state = 0;
				btn->btn_before = btn->btn_current;
				btn->debounce_cnt = 0;
			}
			break;
		case 2:
			//PORTA |= 1 << GRN1;
			if (btn->btn_before != btn->btn_current) {
				btn->state = 0;
				btn->btn_before = btn->btn_current;
				btn->debounce_cnt = 0;
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