#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void){
	// initialization
	DDRD = 0xFF;
	// main application loop
	while(1){
		PORTD = 0x00;
		_delay_ms(500);
		PORTD = 0xFF;
		_delay_ms(500);
	}

}
