#include <avr/io.h>
#include <util/delay.h>

#define C 	3822		// These 'magic numbers' are the periods of the musical notes
#define E 	3033		// (T = 1/f) in microseconds.
#define F   2863
#define G 	2551
#define Ab  2407
#define Bb	2145
#define TENOR_C   1911 
#define D	1703
#define Gb	1351

void delay_us(int us) {					// This is a user-defined delay function. 
	for(int i = 0; i <= us; i+=10) {		// I could not use the built in delay function because in the while loop, 
		_delay_us(10);				// if I held a button down _delay_us() would be called nearly every clock cycle.
	}						// This really bogged the CPU down and made the notes sound weird and glitchy.
}							// This function only delays 10 microseconds at a time so it gives the CPU a bit of breathing space

void play_note(int note) {				// This function plays the note allocated to the relevent pushbutton by
	PORTD |= (1 << PORTD0);				// switching the piezo on and off very fast at the correct frequency
       	delay_us(note);					// TODO maybe look into using the 'toggle bit' bitmask?
 	PORTD &= ~(1 << PORTD0);
	delay_us(note);
}

int main() {
	while(1) {
		DDRD |= (1 << DDD0);			// DDD0 is the piezo and is configured as an output pin
		DDRB &= ~(1 << PINB);			// all the pushbuttons are wired to PINB and set as inputs

        switch(PINB) {

            case(0x01):					// These numbers correlate to individual pins for the B bank on the atmega
                play_note(F);				// TODO get rid of magic numbers.
            break;

            case(0x02):
                play_note(G);
            break;

            case(0x04):
                play_note(Ab);
            break;

            case(0x08):
                play_note(Bb);
            break;
            
            case(0x10):
                play_note(TENOR_C);
            break;

            case(0x20):
                play_note(Gb);
            break;

            default: PORTD = 0x00;
        }
	}
}
