;
; DA2_Task2_asm.asm
;
; Created: 3/15/2018 7:10:59 PM
; Author : Damian Cisneros
; Description : This program lights up LED on PINB2 1s after a pushbutton is
;				pressed on PORTD2 (8MHz clock)

.ORG 0

CBI DDRD, 2 ;set PIND2 to input
SBI DDRB, 2 ;set PINB2 to output

LDI R20, 0XFF ;Turn on pull-up resistor for PIND2
OUT PORTD, R20 

LDI R20, 13
STS TCCR1B, R20 ;Set CTC mode with prescalar 1024

LOOP:
	IN R20, PIND ;grab PIND 
	NEG R20 ;Pull-up resistor logic
	ANDI R20, 4 ;check PIND2 input
	BREQ LOOP

	LDI R20,0x00
	STS TCNT1H,R20 ;resetting the counter to 0
	LDI R20,0x00
	STS TCNT1L,R20 ;resetting the counter to 0
	
	RCALL delay ;delay 1s

	LDI R20, 4
	OUT PORTB, R20 ;turn on LED for 1s
	RCALL delay ;delay 1s
	LDI R20, 0
	OUT PORTB, R20 ;turn off LED 
	RJMP LOOP 

delay:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28
	CPI R28, 0x41 ;comparing if lower is 0x41
	BRSH body ;if false repeat
	RJMP delay ;if true repeat
body:
	CPI R29,0x0f ;comparing if higher is 0x0f
	BRSH done
	RJMP delay
done:
	LDI R20,0x00
	STS TCNT1H,R20 ;resetting the counter to 0 for next round
	LDI R20,0x00
	STS TCNT1L,R20 ;resetting the counter to 0 for next round
 RET