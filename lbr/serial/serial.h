/**
    \file serial.h
    \author Rhys Thomas
    \date 2017-03-14
    \brief Custom serial library for the AVR xmega series.

    This library is based heavily on the Arduino serial, with a number of
    functions removed and able to be used in avr-libc applications. No need
    for Arduino dependancies.

    https://morf.lv/guide-to-xmega-usart-aka-serial-communication
*/

#ifndef _SERIAL_H_
#define _SERIAL_H_

// includes
#include <avr/io.h>

// UART peripheral addresses
// these were already defined
// #define USARTC0 0x08A0
// #define USARTC1 0x08B0
// #define USARTD0 0x09A0
// #define USARTD1 0x09B0
// #define USARTE0 0x0AA0

// USART register addresses
#define DATA      0x00
#define STATUS    0x01
#define CTRLA     0x03
#define CTRLB     0x04
#define CTRLC     0x05
#define BAUDCTRLA 0x06
#define BAUDCTRLB 0x07

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
    char *readString();
public: // members
private: // methods
    void uart_tx(char data);
    char uart_rx();
private: // members
    unsigned long _baud;
    uint8_t *_uart_register;
    uint8_t *_data_register;
    uint8_t *_status_register;
    uint8_t *_ctrlA_regiser;
    uint8_t *_ctrlB_regiser;
    uint8_t *_ctrlC_regiser;
    uint8_t *_baudA_regiser;
    uint8_t *_baudB_regiser;
};

/* the library autogenerates an object called Serial so the user can simply
include the library and call Serial.begin() */
extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
extern SerialClass Serial3;
extern SerialClass Serial4;

#endif // _SERIAL_H_
