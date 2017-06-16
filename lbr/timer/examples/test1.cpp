#include "../timer.h"

#include <util/delay.h>

// example 1

void example1()
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
}

// example 2

void example2()
{
	// make a timer
	Timer T0(TCC0);

	// init PWM
	T0.initPWM(10000, 0.45, 0.50, 0.60, 0.80);

	while(1)
	{
		_delay_ms(1000); // do nothing
	}
}

// example 3

ISR(TCC0_OVF_vect)
{
	PORTR.OUTTGL = PIN0_bm;
}

void example3()
{
	// set pin as output
	PORTR.DIR = PIN0_bm;

	// make timer 
	Timer T0(TCC0);

	// set tick frequency
	T0.setTick(10);

	while(1)
	{
		_delay_ms(1000); // do nothing
	}
}

// main 

int main()
{
//	example1();
//	example2();
	example3();
	return 0;
}