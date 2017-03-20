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
SerialClass Serial();
SerialClass Serial1(1);
SerialClass Serial2(2);
SerialClass Serial3(3);
SerialClass Serial4(4);

/**
    \brief Constructor.

    Initialises the UART register that will be used, since the xmega series
    have more than one UART peripheral.
*/
SerialClass::SerialClass()
{

}

/**
    \brief Constructor.
    \param uart_register Selects the register to be used for UART.

    Initialises the UART register that will be used, since the xmega series
    have more than one UART peripheral.
*/
SerialClass::SerialClass(int uart_register)
{

}

/**
    \brief Destructor.
*/
SerialClass::~SerialClass()
{ /* Left empty */ }

/**
    \brief Setup baudrate and register config for UART.
    \param baud Baudrate for UART communications.
    \todo Currently not implimented. This is UART code for the Il Matto to be
    used as a reference.
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
    \param string String to be sent over UART.
*/
void SerialClass::print(const char *string)
{
    while(*string != '\0') {
        uart_tx(*string++);
    }
}

/**
    \brief Prints string to UART and a newline character.
    \param string String to be sent over UART.
*/
void SerialClass::println(const char *string)
{
    print(string);
    uart_tx('\n');
}

/**
    \brief Read byte in from UART.
    \return Byte read from UART.
*/
uint8_t SerialClass::read()
{
    return uart_rx();
}

/**
    \brief Read string in from UART.
    \return String received.

    Terminates at newline character.
*/
char *SerialClass::readString()
{
    //!< \todo Write this.
}

/**
    \brief Transmit byte over UART.
    \param data Byte to be sent.
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
    \return Byte received.
*/
char SerialClass::uart_rx()
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}
