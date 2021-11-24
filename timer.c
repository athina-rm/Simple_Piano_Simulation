#include <avr/io.h>

#include "timer.h"

void timer2_init() 
{
		TCNT2=0;
	//Timer2 CTC mode (WGM22:0 = 2)         
		TCCR2B &= ~(1<<WGM22);
		TCCR2A |= (1<<WGM21);		
		TCCR2A &= ~(1<<WGM20);
		
		//Prescaler = 8 CS2[2:0]=010
		TCCR2B |=  (1<<CS21);
        TCCR2B &= ~((1<<CS22) | (1<<CS20));

		OCR2A=45;				//value that corresponds to 44kHz
		//TIMSK2:when OCIE2A bit is written to one,the Timer/Counter2 compare match A interrupt is enabled
		TIMSK2 |= (1<<OCIE2A);		
}

void timer0_init() 
{
		TCNT0=0;			//initialize timer0 with value 0

		//Fast PWM-mod, 0xFF som TOP (WGM02:0 = 3), Non-inverting mode (COMnx1:0 = 2)
		TCCR0B &= ~(1<<WGM02);
		TCCR0A |= (1<<WGM01) | (1<<WGM00);
		TCCR0A |= (1<<COM0A1);
		TCCR0A &= ~(1<<COM0A0);
		//TCCR0A |= 1<<COM0A0;
		
		//Prescaler = 1 CS0[2:0]=001
		TCCR0B |= (1<<CS00) ;
		TCCR0B &= ~((1<<CS02) | (1<<CS01));	 

		//the data direction register (DDR) bit corresponding to the OC0A pin must be set in order to enable the output driver.
		DDRD |= (1<<DDD6);
}