/*
 * DA2_Task5_c.c
 *
 * Created: 3/15/2018 9:47:24 PM
 * Author : Damian Cisneros
 * Description : Program lights up LED 1s after INT0 interrupt occurs by
 *				 pressing the button. It stays on for 2s then turns off
 *				 (1MHz clock, LED connected to PINB2, pushbutton INT0 pin)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 4; //set PORTB2 as output for LED
	DDRD &= ~(1 << PIND2); //set PORTD2 as input for pushbutton switch
	EIMSK = (1 << INT0); //enable INT0 interrupt
	EICRA = 3; //enable INT0 flag on rising edge
	sei(); //enable global interrupt
    while (1) 
    {
	}
}

ISR(INT0_vect){
	_delay_ms(5); //debounce
	if (PIND & 0x04){
	_delay_ms(1000); //initial 1s delay after pressing button
	PORTB |= (1 << PINB2); //turn on LED connected to PINB2 for 2s
	_delay_ms(2000); //delay on mode for 2s
	PORTB &= ~(1 << PINB2); //turn off LED
	}
}