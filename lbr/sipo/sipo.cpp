/**
    \file sipo.cpp
    \author Rhys Thomas
    \date 2017-03-14
    \brief Library for 74HC595 shift register.

    Interfaces 74HC595 serial-in/parallel-out shift registers with AVR
    micro-controllers.
*/

#include "sipo.h"

Sipo::Sipo(int data_pin, int clock_pin, int latch_pin)
{
    _data_pin = data_pin;
    _clock_pin = clock_pin;
    _latch_pin = latch_pin;
}

Sipo::~Sipo()
{ /* Left empty */ }
