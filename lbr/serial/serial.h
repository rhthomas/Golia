/***************************************************************************//**
 * @file   serial.h
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Custom serial library for the AVR xmega series.
 ******************************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

// includes
#include <avr/io.h>

/**
 * @class Serial
 * @brief Contains functions to begin and print to serial via UART pins.
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
    unsigned long baud;
    USART_t uartRegister;
};

/* the library autogenerates an object called Serial so the user can simply
include the library and call Serial.begin() */
extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
extern SerialClass Serial3;
extern SerialClass Serial4;

#endif // SERIAL_H
