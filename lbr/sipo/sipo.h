/***************************************************************************//**
 * @file   sipo.h
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Library for 74HC595/74HC164 shift register.
 *******************************************************************************
 * Interfaces 74HC595/74HC164 serial-in/parallel-out shift registers with AVR
 * micro-controllers.
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
    Sipo(int dataPin, int clockPin, int latchPin); ///< 74HC595 constructor.
    ~Sipo(){} ///< Destructor.
    void init(int dataPin, int clockPin, int latchPin); ///< Initialiser
    void shiftOut(uint8_t aByte); ///< Shift byte to register outputs.
public: // members
private: // methods
private: // members
    int dataPin;
    int clockPin;
    int latchPin;
};

#endif // SIPO_H
