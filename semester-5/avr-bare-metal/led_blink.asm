;
; zv53855-1.asm
;
; Created: 10/29/2024 1:18:20 PM
; Author : Student
;
.include "tn104def.inc"
.ORG 0

; Replace with your application code

//LDI R16, 0xD8
//OUT CCP, R16
//LDI R16, 0x00
//OUT CLKMSR, R16

// ustawienie wspolczynnika podzialu sygnalu zegarowego 8 razy szybciej 
LDI R16, 0xD8
OUT CCP, R16
LDI R16, 0x00
OUT CLKPSR, R16

LDI R16, (1<<PORTB3)
OUT DDRB, R16

MAIN:
	COM R16
	OUT PORTB, R16
	RCALL DELAY
	RJMP MAIN

DELAY:
	LDI R19, 3	; 1 
	LOOP1:
		LDI R18, 217 ; 1
		LOOP2:
			LDI R17, 255
			LOOP3:
				DEC R17 ; 1
				BRNE LOOP3 ; 2
			DEC R18 ; 1
			BRNE LOOP2 ; 2
		DEC R19		 ; 1
		BRNE LOOP1   ; 2
	RET ; 6
; 1+3*(1+217*(1+255*3+3)+3) = 500632