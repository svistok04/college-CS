/*
 * state-machine.c
 *
 * Created: 11/19/2024 12:33:40 PM
 * Author : Student
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define RED1 PORTA0
#define YEL1 PORTA1
#define GRN1 PORTA3

#define RED2 PORTA4
#define YEL2 PORTA5
#define GRN2 PORTA6

volatile uint8_t MAX_INTERVAL = 8;

volatile uint8_t counter;
volatile uint8_t state;

volatile uint8_t flag = 0;

ISR (TIM0_COMPA_vect) {
		if (++counter > MAX_INTERVAL) {
			counter = 0;
			flag = 1;
		}

}

int main(void)
{
	DDRA = (1 << RED2) | (1 << YEL2) | (1 << GRN2) | (1 << RED1) | (1 << YEL1) | (1 << GRN1);
	state = 1;
	// timer
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0B |= (1 << WGM02) |  (1 << CS02) | (1 << CS00);
	// clock compare value
	OCR0A = 200;
	// interrupt mask
	TIMSK0 |= (1 << OCIE0A);
	sei();
	
	while (1) {
		if (flag) {
			switch(state) {
				case 0:
					PORTA = (1 << RED1) | (1 << GRN2);
					MAX_INTERVAL = 30;
					break;
				case 1:
					PORTA = (1 << RED1) | (1 << YEL2);
					MAX_INTERVAL = 8;
					break;
				case 2:
					PORTA = (1 << RED1) | (1 << RED2);
					MAX_INTERVAL = 16;
					break;
				case 3:
					PORTA = (1 << RED1) | (1 << YEL1) | (1 << RED2);
					MAX_INTERVAL = 8;
					break;
				case 4:
					PORTA = (1 << GRN1) | (1 << RED2);
					MAX_INTERVAL = 30;
					break;
				case 5:
					PORTA = (1 << YEL1) | (1 << RED2);
					MAX_INTERVAL = 8;
					break;
				case 6:
					PORTA = (1 << RED1) | (1 << RED2);
					MAX_INTERVAL = 16;
					break;
				case 7:
					PORTA = (1 << RED1) | (1 << RED2) | (1 << YEL2);
					MAX_INTERVAL = 8;
					break;
			}
			state = ++state % 8;
			flag = 0;
		}
	}
	
}

