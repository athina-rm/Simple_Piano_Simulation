#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>

#include "serial.h"
#include "timer.h"
#include "pushbutton.h"

volatile uint32_t f, time_tracker, newTone;


ISR (TIMER2_COMPA_vect)
{        
        if((time_tracker<5556 && time_tracker>0) || newTone){                      
                newTone=0;
                //printf("%u\n",f);
                uint32_t value = (sin(0.0001414285*f*time_tracker)+1)/2*255;
                OCR0A = value;
                time_tracker++;
                if (time_tracker >= 5556){
                        time_tracker=0;
                }
        }
        else{
                OCR0A = 255;
        }
           
}

int main (void) 
{
        uart_init();
        timer2_init();
        timer0_init();
        sei();                                  //status register (SREG) – I: Global Interrupt Enable in the is set (one) to enable interrupts	
        //button_init();        
        char input;
        uint32_t t=0;        
        
        while (1) {
                if (UCSR0A & (1 << RXC0)){
                        input=UDR0;                        
                        newTone=1;
                        t=1;
                        switch(input){
                                case 'c' : f=261;
                                        break;
                                case 'd' : f = 294;
                                        break;
                                case 'e' : f=329;
                                        break;
                                case 'f' : f = 349;
                                        break;
                                case 'g' : f = 392;
                                        break;
                                case 'a' : f = 440;
                                        break;
                                case 'b' : f = 493;
                                        break;
                        }                        
                }
                /*if((t < 44445 && t>0) || newTone){                      
                        newTone=0;                        
                        uint32_t x = (sin(0.0001414285*f*t)+1)/2*255;  //2*3.14*22.5*10^-6 = 0.0001414285
                        printf ("%u ",t);
                        printf ("%u\n",x);
                        t+=100;
                        if (t >= 44445){
                                t=0;
                        }
                } */                 
                                        
        }
}