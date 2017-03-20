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
    \todo Write defines for UART regisers etc.
 */
#if defined(__AVR_ATmega644P__) || defined(__AVR_ATmega328P__)
    // #define
#elif defined(__AVR_ATxmega64A4U__)
    // #define
#endif

/**
    \class Serial
    \brief Contains functions to begin and print to serial via UART pins.
 */
class SerialClass
{
public: // methods
    SerialClass();             //!< Constructor.
    ~SerialClass();            //!< Destructor.
    void begin(unsigned long); //!< Set baudrate.
    void print(const char*);   //!< Print without newline.
    void println(const char*); //!< Print with newline.
    void print(int);           //!< Print without newline.
    void println(int);         //!< Print with newline.
    void print(float);         //!< Print without newline.
    void println(float);       //!< Print with newline.
    uint8_t read();            //!< Read byte in from serial port.
    char *readString();        //!< Read string in from serial port.
public: // members
private: // methods
    void uart_tx(char data);   //!< Send byte over UART.
    char uart_rx();            //!< Receive byte over UART.
private: // members
    unsigned long baud;        //!< Baudrate.
};

/* the library autogenerates an object called Serial so the user can simply
include the library and call Serial.begin() */
extern SerialClass Serial;

#endif // _SERIAL_H_
