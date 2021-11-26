#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>

#include "serial.h"
#include "timer.h"
#include "pushbutton.h"

volatile uint32_t f, time_tracker, newTone,t;
const static uint32_t sine_values[223] ={127,131,134,138,141,145,149,152,156,159,163,166,169,173,176,179,183,186,189,192,195,198,201,204,207,
210,213,215,218,220,223,225,227,229,232,234,236,237,239,241,242,244,245,247,248,249,250,251,252,252,253,253,254,254,254,254,254,254,254,254,253,
253,252,252,251,250,249,248,247,245,244,243,241,239,238,236,234,232,230,227,225,223,220,218,215,213,210,207,204,202,199,196,193,189,186,183,180,
176,173,170,166,163,159,156,152,149,145,142,138,135,131,127,124,120,117,113,109,106,102,99,95,92,88,85,82,78,75,72,68,65,62,59,56,53,50,47,44,
42,39,37,34,32,29,27,25,23,21,19,17,15,13,12,10,9,8,6,5,4,3,2,2,1,1,0,0,0,0,0,0,0,0,0,1,2,2,3,4,5,6,7,8,10,11,13,15,16,18,20,22,24,26,29,31,33,
36,38,41,44,46,49,52,55,58,61,64,67,71,74,77,81,84,87,91,94,98,101,105,108,112,116,119,123,126};


ISR (TIMER2_COMPA_vect)                         //configured to occur every 22.5us
{       
        /*t++;
        if(t>44444){
                printf("1 sec\n");
                t=0;
        }*/
        if((time_tracker<44445 && time_tracker>0) || newTone){                      
                newTone=0;
                //uint32_t i=(time_tracker*(f/200))%223;
                //printf ("%u : ",i);
                OCR0A = sine_values[(time_tracker*(f/200))%223];
                //printf ("%u \n",sine_values[i]);                        
                time_tracker++;
                if (time_tracker > 44444){
                        time_tracker=0;
                }                               
        }
        else{
                OCR0A = 0;
        }    
}

int main (void) 
{
        uart_init();
        timer2_init();
        timer0_init();        
        char input;
        //uint32_t t=0;
               
        //generating a table for one sine wave with frequency 200Hz-min freq expected with samples at 44.44kHz/22.5us       
        //uint32_t sine_values[445];
            
        /*f=200;
        uint32_t sine_values[223];
        double sampling_pd = 22.5*pow(10,-6);
        double t= 0;
        uint32_t i;
        printf_P(PSTR("creating lookuptable"));
        while (i<223){
                uint32_t value = (sin(2*3.142*f*t)+1)/2*255;  //f=20, t=i*22.5*pow(10,-6)           
                sine_values[i++] = value;                
                printf ("%u,",value);
                t+=sampling_pd;                
        }*/
        /*printf_P(PSTR("lookuptable : {"));
        for(int j=0;j<sizeof(sine_values)/sizeof(sine_values[0]);j++){
                //printf_P(PSTR("%u"),pgm_read_byte(&sine_values[j]));
                printf_P(PSTR("%u"),sine_values[j]);
                printf (", ");
        }
        printf ("}");*/
        
        sei();                                  //status register (SREG) – I: Global Interrupt Enable in the is set (one) to enable interrupts
        
        while (1) {
                if (UCSR0A & (1 << RXC0)){
                        input=UDR0;                        
                        newTone=1;
                        //t=1;
                        switch(input){
                                case 'C' : f=261;    //f=261;
                                        break;
                                case 'D' : f = 294;
                                        break;
                                case 'E' : f=329;
                                        break;
                                case 'F' : f = 349;
                                        break;
                                case 'G' : f = 392;
                                        break;
                                case 'A' : f = 440;
                                        break;
                                case 'B' : f = 1000; //f = 493;
                                        break;
                        }                        
                }
                /*if((t < 5000 && t>0) || newTone){                      
                        newTone=0;                        
                        uint32_t i=(t*(f/200))%223;
                        printf ("%u : ",i);
                        printf ("%u \n",sine_values[i]);                        
                        t+=1;
                        if (t >=5000){
                                t=0;
                        }
                }*/                                        
        }
}