/**
    \file serial.cpp
    \author Rhys Thomas
    \date 2017-03-14
    \brief Custom serial library for the AVR xmega series.

    This library is based heavily on the Arduino serial, with a number of
    functions removed and able to be used in avr-libc applications. No need
    for Arduino dependancies.

    https://morf.lv/guide-to-xmega-usart-aka-serial-communication
*/

#include "serial.h"

// instanciate serial object
SerialClass Serial(0);
SerialClass Serial1(1);
SerialClass Serial2(2);
SerialClass Serial3(3);
SerialClass Serial4(4);

/**
    \brief Constructor.
    \param uart_register Selects the register to be used for UART.

    Initialises the UART register that will be used, since the xmega series
    have more than one UART peripheral.
*/
SerialClass::SerialClass(int uart_register)
{
    switch(uart_register) {
        case 0: _uart_register = USARTC0; break;
        case 1: _uart_register = USARTC1; break;
        case 2: _uart_register = USARTD0; break;
        case 3: _uart_register = USARTD1; break;
        case 4: _uart_register = USARTE0; break;
    }

    _data_register   = _uart_register + DATA;
    _status_register = _uart_register + STATUS;
    _ctrlA_regiser   = _uart_register + CTRLA;
    _ctrlB_regiser   = _uart_register + CTRLB;
    _ctrlC_regiser   = _uart_register + CTRLC;
    _baudA_regiser   = _uart_register + BAUDCTRLA;
    _baudB_regiser   = _uart_register + BAUDCTRLB;
}

/**
    \brief Destructor.
*/
SerialClass::~SerialClass()
{ /* Left empty */ }

/**
    \brief Setup baudrate and register config for UART.
    \param baud Baudrate for UART communications.
*/
void SerialClass::begin(unsigned long baud)
{
    _baud = (32000000 / (2^0 * 16 * baud)) - 1;

    _baudB_regiser = 0; // make sure bscale is 0
    _baudA_regiser = baud | 0x0FF; // register A takes 8 LSBs
    _baudB_regiser = (0xF00 | baud) >> 8; // register B takes 4 MSBs

    // disable interrupts, just for safety
    _ctrlA_regiser = 0;
    // 8 data bits, no parity, 1 stop bits
    _ctrlC_regiser = USART_CHSIZE_8BIT_gc;

    // enable tx and rx
    _ctrlB_regiser = USART_TXEN_bm | USART_RXEN_bm;
}

/**
    \brief Print string to UART.
    \param string String to be sent over UART.
*/
void SerialClass::print(const char *string)
{
    while(*string) {
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
*/
char *SerialClass::readString()
{
    int i=0;
    char *string;
    char character;

    while(character != '\n') {
        string[i] = character;
        i++;
    }
    return string;
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
    while(!(_status_register & USART_DREIF_bm));
    _data_register = data;
}

/**
    \brief Receive byte over UART.
    \return Byte received.
*/
char SerialClass::uart_rx()
{
    while(!(_status_register & USART_RXCIF_bm));
    return _data_register;
}
