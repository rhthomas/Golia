/**
    \file printing.cpp
    \author Rhys Thomas
    \date 2017-03-20
    \brief Testing the serial library by printing a string over UART.
*/

// includes
#include <util/delay.h>

// libraries
#include "../serial.h"

int main()
{
    Serial.begin(115200);

    while(1) {
        Serial.println("Hello, World!");
        _delay_ms(1000);
    }
}
