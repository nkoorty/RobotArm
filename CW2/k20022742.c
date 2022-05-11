	#include "librobot.h"

void init_button_sensor(void){
	DDRD = 0b00000000; // Set all D Pin's to input
	PORTD = 0b10000000; // Create Pull-up resistor by turning on PIND7
	return;
}

int read_button_sensor(void){
	int pressed;
	if(PIND&(1<<PD7)){
		pressed = 0;
	}
	// Create if statement that checks whether PIND7 is on, and if it is, pressed
	// is initialized to 0
	else{
		pressed = 1;
	}
	// Else statement that sets pressed back to 1
	return pressed;
}

float read_knob_sensor(int knob){
	float reading = 0; /* Sensor reading, normalised
						  (i.e., scaled) to be between
						  zero and one. */

	DDRC = 0x00; // Set all C Pins 	to Input
	if (knob == 0){
	ADMUX |= (0<<MUX0); // Set MUX Pin to 0 if reading from knob0 is required
	}
	else if(knob == 1){
		ADMUX |= (1<<MUX0); // Overwrite MUX Pin to 1 if reading from knob1 is
		// required
	}
	ADCSRA |= (1<<ADSC); // Start conversion

	while(ADCSRA & (1<<ADSC));

	reading=(float)ADCH/256; // Scaling down the values that ADCH can take
	// which are usually from 0 to 255 down.
	ADMUX &=~(1<<MUX0);  // Using bitwise operators in order to set the MUX Pin

	return reading;
}


void init_arm_motors(void) {
	DDRB = (1<<PB1)|(1<<PB2); // Configure Pin B1 and Pin B2 as outputs

	TCCR1A = (1<<COM1A1)|(1<<COM1B1);  // Compare output mode
	TCCR1A |= (1<<WGM11); // Set Wave Generation Mode for TCCR1A
	TCCR1B = (1<<WGM13) | (1<<WGM12); // Set Wave Generation Mode for TCCR1B
	TCCR1B |= (1<<CS11); // Set clock and prescaling

	ICR1 = (F_CPU/1000000)*(20000L/8); // Set TOP
	OCR1A = 3000; // Set Angle of 90º for arm 1
	OCR1B = 3000; // Set Angle of 90º for arm 2
	return;
}
