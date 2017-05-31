#include "../virtualPorts.h"

#define vPortA VPORT0

int main()
{
	// set up virtual port 0 to be port A
	setVP(0, 'A');

	// use of virtual port is the same as normal
	
	// set up all pins as outputs
	vPortA.DIR = 0xFF;

	unsigned char counter = 0xFF;

	while(true) // binary counter on port A
	{
		vPortA.OUT = counter;
		++counter;
	}
}