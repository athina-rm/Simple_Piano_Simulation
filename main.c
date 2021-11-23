//ASMA KHALID PATEL
//IOT 2020
//Running on Arduino uno Atmega 328p
//UART Arduino communication through serial monitor,  rx connected to Tx of esp32
//open an empty arduino code run it while pressing reset button on esp32, open serial monitor (BAUD rate 38400)
//when loading up this sketch press on the Esp32s reset button utill uploaded and visa versa

#include <avr/io.h>
#include <avr/pgmspace.h> //Program Space Utilities
#include <util/delay.h>
#include <stdio.h>

#include "serial.h"
#define Blue_pin 0
#define Green_pin 1
#define Red_pin 2


void main(void)
{
    DDRB |= (1 << Red_pin);
    DDRB |= (1 << Green_pin);
    DDRB |= (1 << Blue_pin);
    
    uart_init();

    uint8_t notes = 0;
    

    while (1)

    {
        notes = uart_getchar();
        printf_P(PSTR("%c\n"), notes);
        switch (notes)
        {
        case 'A':
            //frequency of A4 440Hz
            // tones[] = 440;
            PORTB |= (1 << Blue_pin);
            PORTB &= ~(1 << Green_pin);
            PORTB &= ~(1 << Red_pin);
            break;
        case 'B':
            //frequency of B4 493Hz
            PORTB &= ~(1 << Blue_pin);
            PORTB &= ~(1 << Red_pin);
            PORTB |= (1 << Green_pin);
            break;

        case 'C':
            //frequency of C4 261Hz
            PORTB |= (1 << Red_pin);
            PORTB &= ~(1 << Blue_pin);
            PORTB &= ~(1 << Green_pin);

        case 'D':
            //frequency of D4 293Hz

            break;
        case 'E':
            //frequency of E4 329Hz
            break;
        case 'F':
            //frequency of F4 349Hz
            break;
        case 'G':
            //frequency of G4 392Hz
            break;
        case 'P':
            break;
        }
        notes = 0;
    }
}

