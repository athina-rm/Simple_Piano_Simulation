#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>

#include "serial.h"
#include "timer.h"
#include "pushbutton.h"

volatile uint32_t  f, time_tracker, newTone;


ISR (TIMER2_COMPA_vect)
{	
        time_tracker++;        
}

int main (void) 
{
        uart_init();
        timer2_init();
        timer0_init();
        sei();                                  //status register (SREG) – I: Global Interrupt Enable in the is set (one) to enable interrupts	
        //button_init();        
        char input;        
        
        while (1) {
                                            
        }
}