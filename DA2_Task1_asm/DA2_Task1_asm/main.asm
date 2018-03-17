;
; DA2_Task1_asm.asm
;
; Created: 3/15/2018 2:18:30 PM
; Author : Damian Cisneros
; Description : Program generates waveform with 0.5s period and 50% duty cycle
;		 		waveform is output to LED connected to PINB2 (uses 8MHz clock)		
;

.ORG 0

LDI R21, 0 ;Used to toggle LED
SBI DDRB, 2 ;Set PINB2 to output
LDI R20, 8 
//STS TCCR1B, R20 ;Set to CTC mode
LDI R20, 13
STS TCCR1B, R20 ;Set prescalar to 1024

LDI R20, 0X0A ;Higher bits of 3905 calculated as 0.25s
LDI R21, 0X07 ;Lower bits of 3905 calculated as 0.25s
STS OCR1AH, R21 ;Set output compare register high bits
STS OCR1AL, R20 ;Set output compare register low bits

LOOP:
	IN R20, TIFR1 ;Grab TIFR0 (Interrupt Flag Register)
	ANDI R20, 4 ;Isolate OCFA (Output compare A match flag)
	BREQ LOOP ;Check if OCFA flag is set. If it is move on to next instruction.
			  ;Else loop back
	EOR R21, R20;Toggle LED
	OUT PORTB, R21 ;Output LED
	LDI R20, 4 ;Used to clear TIFR flag
	OUT TIFR1, R20 ; Clear TIFR flag
	RJMP LOOP