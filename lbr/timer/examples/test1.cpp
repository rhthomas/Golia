#include "../timer.h"

#include <util/delay.h>

int main()
{
	// make a timer
	Timer T0(TCC0);

	// set frequency 
	T0.setFreq(1000);

	// output waves on port pins 
	// see output pins in header
	T0.portOverride(true, true, true, true); 

	// set duty cycle of pins
	T0.setDuty(0.10, 0.35, 0.55, 0.80);

	while(1)
	{
		_delay_ms(1000); // do nothing 
	}

	return 0;
}