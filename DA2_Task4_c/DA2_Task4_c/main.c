/*
 * DA2_Task4_c.c
 *
 * Created: 3/15/2018 9:26:13 PM
 * Author : Damian Cisneros
 * Description : This program blinks LED connected to PINB2 with a square wave
 *				 at a rate 0.25s which is 50% duty cycle of 0.5s using TIMER1 
 *				 OVF interrupt (1MHz clock)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect){
	PORTB ^= DDRB; //toggle LED 
	TCNT1 = 65293; //reset TCNT1 to 0.25s calculated based on 50% duty cycle of 0.5s
}

int main(void)
{
	DDRB = 4; //set PORTB2 as output
	TCCR1B = 5; //set prescalar 1024
	TCNT1 = 65293; //set TCNT1 to 0.25s calculated based on 50% duty cycle of 0.5s
	TIMSK1 |= (1 << TOIE1);	//enable OVF interrupt
	sei();	//enable global interrupts

	while (1) 
    {
    }
}

