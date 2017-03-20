/**
    \file sipo.h
    \author Rhys Thomas
    \date 2017-03-14
    \brief Library for 74HC595 shift register.

    Interfaces 74HC595 serial-in/parallel-out shift registers with AVR
    micro-controllers.
*/

#ifndef _SIPO_H_
#define _SIPO_H_

// includes
#include <avr/io.h>

/**
    \class Sipo
    \brief Contains functions to initialise and use the 595 chip.
*/
class Sipo
{
public: // methods
    Sipo(int, int, int); //!< Constructor. (AVR take registers as arguments?)
    ~Sipo();             //!< Destructor.
public: // members
private: // methods
private: // members
    int _data_pin;
    int _clock_pin;
    int _latch_pin;
};

#endif // _SERIAL_H_
