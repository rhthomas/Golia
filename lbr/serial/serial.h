/**
    \file serial.h
    \author Rhys Thomas
    \date 2017-03-14
    \brief Custom serial library for the AVR xmega series.
*/

#ifndef _SERIAL_H_
#define _SERIAL_H_

// includes
#include <avr/io.h>

/**
    \class Serial
    \brief Contains functions to begin and print to serial via UART pins.
 */
class SerialClass
{
public: // methods
    SerialClass(int);
    ~SerialClass();
    void begin(unsigned long);
    void print(const char*);
    void println(const char*);
    uint8_t read();
    const char *readString();
public: // members
private: // methods
    void uart_tx(char data);
    char uart_rx();
private: // members
    unsigned long _baud;
    USART_t _uart_register;
};

/* the library autogenerates an object called Serial so the user can simply
include the library and call Serial.begin() */
extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
extern SerialClass Serial3;
extern SerialClass Serial4;

#endif // _SERIAL_H_
