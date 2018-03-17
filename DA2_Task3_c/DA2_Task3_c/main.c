/*
 * DA2_Task3_c.c
 *
 * Created: 3/16/2018 10:49:48 AM
 * Author : Damian Cisneros
 * Description : This program works with 1MHz clock and toggles an LED in PINB2
 *				 every .5s with a duty cycle of 50% which toggles at .25s rate
 */ 

//clock is 1MHz

#include <avr/io.h>

int main(void)
{
	DDRB = 4; //set PINB2 as output
    TCCR1B = 5; //set CTC mode with 1024 prescale
	TCNT1 = 65293; //calculated count for 0.5s/2 for 50% duty cycle

	while (1) 
    {	
		if (TIFR1 & (1 << TOV1)){ //check overflow flag
			PORTB ^= DDRB; //toggle LED
			TCNT1 = 65293; // reload calculated count for 0.5s/2 for 50% duty cycle
			TIFR1 |= (1 << TOV1); //clear overflow flag
		}
    }
}

