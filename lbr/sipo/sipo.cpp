/***************************************************************************//**
 * @file   sipo.cpp
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Library for 74HC595/74HC164 shift register.
 *******************************************************************************
 * Interfaces 74HC595/74HC164 serial-in/parallel-out shift registers with AVR
 * micro-controllers.
 ******************************************************************************/

#include "sipo.h"

Sipo::Sipo(int dataPin, int clockPin, int latchPin)
{
    init(dataPin, clockPin, latchPin);
}

// TODO constructor for 74HC164
/*
Sipo::Sipo(int dataPin, int clockPin)
{
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;

    // TODO make DDRB/PORTB set based on dataPin etc.
    // set control pins as outputs and initialise low
    DDRB |= (sipo.data | sipo.latch | sipo.clock);
    PORTB &= ~(sipo.data | sipo.latch | sipo.clock);
}
*/

/**
 * @brief Initialise SIPO.
 */
void init(int dataPin, int clockPin, int latchPin)
{
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;

    // TODO make DDRB/PORTB set based on dataPin etc.
    // set control pins as outputs and initialise low
    DDRB |= (sipo.data | sipo.latch | sipo.clock);
    PORTB &= ~(sipo.data | sipo.latch | sipo.clock);
}

/**
 * @brief
 * @todo Make PORTB a private member.
 */
void shiftOut(byte aByte)
{
    for (uint8_t i=0; i<8; i++) {
        // tests MSB of val
        if(val & 0x80)
            PORTB |= sipo.data;
        else
            PORTB &= ~sipo.data;
        // pulse the clock
        PORTB |= sipo.clock;
        PORTB &= ~sipo.clock;
        val<<=1; // move next bit to MSB
    }
    // data set, move to output
    PORTB |= sipo.latch;
    PORTB &= ~sipo.latch;
}

/*
void shiftOut(int aNumber)
{
    for (uint8_t i=0; i<8*sizeof(aNumber); i++) {
        // TODO shiftOut function that checks number of bytes to be shifted.
    }
}
*/
