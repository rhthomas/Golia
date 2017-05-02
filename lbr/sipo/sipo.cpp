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
	
}
*/

/**
 * @brief Initialise SIPO.
 */
void Sipo::init(int dataPin, int clockPin, int latchPin)
{
    this->dataPin = (1<<dataPin);
    this->clockPin = (1<<clockPin);
    this->latchPin = (1<<latchPin);

    // TODO make PORTB set based on dataPin etc.
    // set control pins as outputs and initialise low
    PORTB_DIR |= (this->dataPin | this->latchPin | this->clockPin);
    PORTB_OUT &= ~(this->dataPin | this->latchPin | this->clockPin);
}

/**
 * @brief
 * @todo Make PORTB a private member.
 */
void Sipo::shiftOut(uint8_t aByte)
{
	// set latch low
    PORTB_OUT &= ~this->latchPin;
    for (uint8_t i=0; i<8; i++) {
        // tests MSB of val
        if(aByte & 0x80)
            PORTB_OUT |= this->dataPin;
        else
            PORTB_OUT &= ~this->dataPin;
        // pulse the clock
        PORTB_OUT |= this->clockPin;
        PORTB_OUT &= ~this->clockPin;
        aByte<<=1; // move next bit to MSB
    }
	// set latch high, output appears on '595 pins
    PORTB_OUT |= this->latchPin;
}

/*
void shiftOut(int aNumber)
{
    for (uint8_t i=0; i<8*sizeof(aNumber); i++) {
        // TODO shiftOut function that checks number of bytes to be shifted.
    }
}
*/
