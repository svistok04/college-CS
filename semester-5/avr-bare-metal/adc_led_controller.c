/*
 * ADC.c
 *
 * Created: 12/10/2024 12:33:44 PM
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

volatile uint8_t old_adc;
volatile uint8_t adc;
uint8_t state;


volatile uint8_t colorful_PORTA;
volatile uint8_t counter;
volatile uint8_t max_interval;

ISR(ADC_vect) {
	adc = ADCH;
	ADCSRA |= (1 << ADSC);
}

ISR(TIM0_COMPA_vect) {
	if (++counter > max_interval) {
		//PORTA ^= 1 << RED2 | 1 << YEL2 | 1 << GRN2 | 1 << GRN1 | 1 << YEL1 | 1 << RED1;
		if (PORTA) {
			PORTA = 0;
		} else {
			PORTA = colorful_PORTA;
		}
		counter = 0;
	}
}

int main(void)
{
	DDRA = (1 << RED2) | (1 << YEL2) | (1 << GRN2) | (1 << RED1) | (1 << YEL1) | (1 << GRN1);
	
	ADMUX |= 1 << MUX2 | 1 << MUX0;
	
	ADCSRA |= 1 << ADEN;
	ADCSRA |= 1 << ADPS2 | 1 << ADPS1;
	ADCSRA |= 1 << ADIE;
	
	ADCSRB |= 1 << ADLAR;
	
	TCCR0A = 0;
	TCCR0B = 0;
	OCR0A = 200;
	TCCR0B |= (1 << WGM02) |  (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	
	sei();
	ADCSRA |= (1 << ADSC);
    /* Replace with your application code */
    while (1) 
    {	
		while(ADCSRA & (1 << ADSC)) {}
		
		max_interval = adc / 70;
		switch(adc) {
			case 0 ... 37:
				colorful_PORTA = 0;
				break;
			case 38 ... 76:
				colorful_PORTA = 1 << RED2;
				break;
			case 77 ... 113:
				colorful_PORTA = 1 << RED2 | 1 << YEL2;
				break;
			case 114 ... 148:
				colorful_PORTA = 1 << RED2 | 1 << YEL2 | 1 << GRN2;
				break;
			case 149 ... 183:
				colorful_PORTA = 1 << RED2 | 1 << YEL2 | 1 << GRN2 | 1 << GRN1;
				break;
			case 184 ... 219:
				colorful_PORTA = 1 << RED2 | 1 << YEL2 | 1 << GRN2 | 1 << GRN1 | 1 << YEL1;
				break;
			case 220 ... 255:
				colorful_PORTA = 1 << RED2 | 1 << YEL2 | 1 << GRN2 | 1 << GRN1 | 1 << YEL1 | 1 << RED1;
				break;
		}
    }
}

