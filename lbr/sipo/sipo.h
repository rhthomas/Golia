/***************************************************************************//**
 * @file   sipo.h
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Library for 74HC595/74HC164 shift register.
 ******************************************************************************/

#ifndef SIPO_H
#define SIPO_H

// includes
#include <avr/io.h>

/**
 * @class Sipo
 * @brief Contains functions to initialise and use the 595 chip.
 */
class Sipo
{
public: // methods
    Sipo(PORT_t port, int dataPin, int clockPin, int latchPin);
    ~Sipo(){}
    void init(int dataPin, int clockPin, int latchPin);
    void shiftOut(uint8_t aByte);
public: // members
private: // methods
private: // members
	PORT_t port;
    int dataPin;
    int clockPin;
    int latchPin;
};

#endif // SIPO_H
