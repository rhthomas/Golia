/**
    \file serial.h
    \author Rhys Thomas
    \date 2017-03-14
    \brief Custom serial library.

    This library is based heavily on the Arduino serial, with a number of
    functions removed and able to be used in avr-libc applications. No need
    for Arduino dependancies.
*/

#ifndef _SERIAL_H_
#define _SERIAL_H_

// includes
#include <avr/io.h>

/**
    UARTC0's config register starts at 0x08A0 and each register has a fixed
    offset from that. In which case we won't need lots of #define's.

    USARTC0 0x08A0
    USARTC1 0x08B0
    USARTD0 0x09A0
    USARTD1 0x09B0
    USARTE0 0x0AA0

    DATA      0x00
    STATUS    0x01
    CTRLA     0x03
    CTRLB     0x04
    CTRLC     0x05
    BAUDCTRLA 0x06
    BAUDCTRLB 0x07
 */

/**
    \class Serial
    \brief Contains functions to begin and print to serial via UART pins.
 */
class SerialClass
{
public: // methods
    void begin(unsigned long);
    void print(const char*);
    void println(const char*);
    uint8_t read();
    char *readString();
public: // members
private: // methods
    /* constructor and destructor are private since Serial, Serial1, etc objects
    have already been instanciated. */
    SerialClass();    // uses serial on PORTC0
    SerialClass(int); // uses serial on PORTC1,...,PORTE0
    ~SerialClass();
    void uart_tx(char data);
    char uart_rx();
private: // members
    unsigned long _baud;
    int _uart_register;
};

/* the library autogenerates an object called Serial so the user can simply
include the library and call Serial.begin() */
extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
extern SerialClass Serial3;
extern SerialClass Serial4;

#endif // _SERIAL_H_
