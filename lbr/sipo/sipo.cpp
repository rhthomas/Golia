/***************************************************************************//**
 * @file   sipo.cpp
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Library for 74HC595/74HC164 shift register.
 ******************************************************************************/

#include "sipo.h"

/**
 * @brief     Constructor initialises port and control pins.
 * @param[in] port Port in which the register is connected to.
 * @param[in] dataPin Pin which register data input is connected to.
 * @param[in] latchPin Pin which register latch is connected to.
 * @param[in] clockPin Pin which register clock is connected to.
 */
Sipo::Sipo(PORT_t port, int dataPin, int clockPin, int latchPin)
{
	this->port = port;
    this->dataPin = (1<<dataPin);
    this->clockPin = (1<<clockPin);
    this->latchPin = (1<<latchPin);

    // TODO make PORTB set based on dataPin etc.
    // set control pins as outputs and initialise low
    this->port.DIR |= (this->dataPin | this->latchPin | this->clockPin);
	this->port.OUT &= ~(this->dataPin | this->latchPin | this->clockPin);

}

/**
 * @brief Shifts byte to output pins of shift register.
 */
void Sipo::shiftOut(uint8_t aByte)
{
	// set latch low
    this->port.OUT &= ~this->latchPin;
    for (uint8_t i=0; i<8; i++) {
        // tests MSB of val
        if(aByte & 0x80)
            this->port.OUT |= this->dataPin;
        else
            this->port.OUT &= ~this->dataPin;
        // pulse the clock
        this->port.OUT |= this->clockPin;
        this->port.OUT &= ~this->clockPin;
        aByte<<=1; // move next bit to MSB
    }
	// set latch high, output appears on '595 pins
    this->port.OUT |= this->latchPin;
}

/*
// TODO used for daisy-chained registers
void shiftOut(int aNumber)
{
    for (uint8_t i=0; i<8*sizeof(aNumber); i++) {
        // TODO shiftOut function that checks number of bytes to be shifted.
    }
}
*/
