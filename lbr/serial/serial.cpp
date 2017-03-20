/**
    \file serial.cpp
    \author Rhys Thomas
    \date 2017-03-14
    \brief Custom serial library.

    This library is based heavily on the Arduino serial, with a number of
    functions removed and able to be used in avr-libc applications. No need
    for Arduino dependancies.
*/

#include "serial.h"

// instanciate serial object
SerialClass Serial(UART);
SerialClass Serial1(UART1);
SerialClass Serial2(UART2);
SerialClass Serial3(UART3);
SerialClass Serial4(UART4);

/**
    \brief Constructor.

    Initialises the UART register that will be used, since the xmega series
    have more than one UART peripheral.

    \param uart_register Selects the register to be used for UART.
*/
SerialClass::SerialClass(int uart_register)
{
    _uart_register = uart_register;
}

/**
    \brief Destructor.
*/
SerialClass::~SerialClass()
{ /* Left empty */ }

/**
    \brief Setup baudrate and register config for UART.
*/
void SerialClass::begin(unsigned long baud)
{
    _baud = F_CPU/(baud*16UL)-1;
    UBRR0H = _baud >> 8;
    UBRR0L = _baud;
    // enable the tx and rx
    UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
    // uart config 8N1
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

/**
    \brief Print string to UART.
*/
void SerialClass::print(const char *string)
{
    while(*string != '\0') {
        uart_tx(*string++);
    }
}

/**
    \brief Prints string to UART and a newline character.
    \see SerialClass::println
*/
void SerialClass::println(const char *string)
{
    print(string);
    uart_tx('\n');
}

/**
    \brief Read byte in from UART.
*/
uint8_t SerialClass::read()
{
    return uart_rx();
}

/**
    \brief Read string in from UART.

    Terminates at newline character.
*/
char *SerialClass::readString()
{
    // read bytes until \n
}

/**
    \brief Transmit byte over UART.
*/
void SerialClass::uart_tx(char data)
{
    // if there's a newline, send a carriage return
    if (data == '\n') {
        uart_tx('\r');
    }
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

/**
    \brief Receive byte over UART.
*/
char SerialClass::uart_rx()
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}
