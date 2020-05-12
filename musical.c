#include <avr/io.h>
#include <util/delay.h>

#define C 	3822
#define E 	3033
#define F   2863
#define G 	2551
#define Ab  2407
#define Bb	2145
#define TENOR_C   1911 
#define D	1703
#define Gb	1351

void delay_us(int us) {
	for(int i = 0; i <= us; i+=10) {
		_delay_us(10);
	}
}

void play_note(int note) {
	PORTD |= (1 << PORTD0);
       	delay_us(note);
 	PORTD &= ~(1 << PORTD0);
	delay_us(note);
}

int main() {
	while(1) {
		DDRD |= (1 << DDD0);
		DDRB &= ~(1 << PINB0);

        switch(PINB) {

            case(0x01):
                play_note(F);
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
