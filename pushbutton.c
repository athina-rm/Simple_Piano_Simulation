#include <avr/io.h>
#include "pushbutton.h"

void button_init() {
		DDRB &= ~(1<<DDB0);									//pin connected to switch as input
		
}