/**
 * @file test1.cpp
 * @author Tom Darlison
 * @date 2017-05-01
 * @brief Turns on LED1 and toggles indefinitely
 */
#include "../led.h"
#include <util/delay.h>

int main()
{
	leds_toggle();
	led1_on();
	while(1)
	{
		_delay_ms(500);
		leds_toggle();
	}
	return 0;
}