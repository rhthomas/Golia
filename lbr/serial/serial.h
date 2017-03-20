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
    \todo Write defines for UART regisers etc. Note that there are 5 UART
    peripherals onboard the xmega chip.
 */
#if defined(__AVR_ATmega644P__)
    // define UART registers
#elif defined(__AVR_ATmega328P__)
    // #define UART registers
#elif defined(__AVR_ATxmega64A4U__)
    // #define UART registers
    /*
        #define <...> USARTC0_DATA
        #define <...> USARTC0_STATUS
        #define <...> USARTC0_CTRLA
        #define <...> USARTC0_CTRLB
        #define <...> USARTC0_CTRLC
        #define <...> USARTC0_BAUDCTRLA
        #define <...> USARTC0_BAUDCTRLB
    */
    /*
        #define <...> USARTC1_DATA
        #define <...> USARTC1_STATUS
        #define <...> USARTC1_CTRLA
        #define <...> USARTC1_CTRLB
        #define <...> USARTC1_CTRLC
        #define <...> USARTC1_BAUDCTRLA
        #define <...> USARTC1_BAUDCTRLB
    */
    /*
        ............
    */
#endif

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
    SerialClass(int);
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
