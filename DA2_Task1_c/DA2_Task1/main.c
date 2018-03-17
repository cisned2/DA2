/*
 * DA2_Task1.c
 *
 * Created: 3/15/2018 1:02:45 PM
 * Author : Damian Cisneros
 * Description : Program generates waveform with 0.5s period and 50% duty cycle
 *	 			 waveform is output to LED connected to PINB2 (uses 8MHz clock)
 */ 

#include <avr/io.h>

int main(void)
{
	int maxCT=3905; //set max calculated for 0.5s
	
	DDRB= 0b00000100; //set PINB2 to output	
	TCCR1A = 0; //normal mode
	TCCR1B = 5; //set prescale: 1024
	
	while (1)
	{
		if(TCNT1>=(maxCT/2)) //50% duty cycle
		{
			TCNT1=0; //reset count
			PORTB ^= DDRB; //toggle led
		}
	}
	return 0;
}