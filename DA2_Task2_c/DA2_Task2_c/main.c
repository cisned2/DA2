/*
 * DA2_Task2_c.c
 *
 * Created: 3/15/2018 6:03:57 PM
 * Author : Damian Cisneros	
 * Description: Program lights up LED in PORTB2 1s after Pushbutton is pressed
 *				which stays lit for 2s before it turns off again.
 */ 
#define F_CPU 8000000UL //define 8MHz
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 4; //set PIND2 to input
	DDRB = 4; //set PINB2 to output
	PORTB |= 0b00000100; //Turn on pull-up resistor
	
    while (1) 
    {
		if(PIND & 0b00000100){ //check if PIND2 is set
			_delay_ms(1000); //delay 1s
			PORTB |= (PINB2 << 1); //turn on LED	
			_delay_ms(2000); //delay 2s
		}
		else{
			PORTB &= ~(PINB2 << 1); //turn off LED	
		}
    }
}