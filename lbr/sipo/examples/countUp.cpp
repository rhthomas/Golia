/**
 * @file countUp.cpp
 * @author Rhys Thomas
 * @date 2017-04-30
 * @brief Counts from 0 to 255 and displays on 8 LEDs.
 */

#include <avr/io.h>
#include <sipo.h>
#include <util/delay.h>

int main(void)
{
	Sipo mySipo(1,2,3);

	for (uint8_t i=0; i<0xff; i++) {
		mySipo.shiftOut(i);
		_delay_ms(1000);
	}
}
