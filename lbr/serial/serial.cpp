/***************************************************************************//**
 * @file   serial.cpp
 * @author Rhys Thomas
 * @date   2017-03-14
 * @brief  Custom serial library for the AVR xmega series.
 ******************************************************************************/

#include "serial.h"

// instanciate serial object
SerialClass Serial(0);
SerialClass Serial1(1);
SerialClass Serial2(2);
SerialClass Serial3(3);
SerialClass Serial4(4);

/**
 * @brief Constructor.
 * @param uart_register Selects the register to be used for UART.
 *
 * Initialises the UART register that will be used, since the xmega series have
 * more than one UART peripheral.
 */
SerialClass::SerialClass(int uart_register)
{
    switch (uart_register) {
        case 0: _uart_register = USARTC0; break;
        case 1: _uart_register = USARTC1; break;
        case 2: _uart_register = USARTD0; break;
        case 3: _uart_register = USARTD1; break;
        case 4: _uart_register = USARTE0; break;
    }
}

/**
 * @brief Destructor.
 */
SerialClass::~SerialClass()
{ /* Left empty */ }

/**
 * @brief Setup baudrate and register config for UART.
 * @param baud Baudrate for UART communications.
 *
 * See line 2493 of include/avr/iox64a4u.h for USART_t structure definintion.
 */
void SerialClass::begin(unsigned long baud)
{
    _baud = (32000000 / (2^0 * 16 * baud)) - 1;

    // make sure BSCALE is 0
    _uart_register.BAUDCTRLB = 0;
    // register A has 8 LSBs
    _uart_register.BAUDCTRLA = _baud | 0x0FF;
    // register B has 4 MSBs
    _uart_register.BAUDCTRLB = (0xF00 | _baud) >> 8;
    // disable interrupts
    _uart_register.CTRLA = 0;
    // 8 data bits, no parity, 1 stop bit
    _uart_register.CTRLC = USART_CHSIZE_8BIT_gc;
    // enable tx and rx
    _uart_register.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
}

/**
 * @brief Print string to UART.
 * @param string String to be sent over UART.
 */
void SerialClass::print(const char *string)
{
    while(*string) {
        uart_tx(*string++);
    }
}

/**
 * @brief Prints string to UART and a newline character.
 * @param string String to be sent over UART.
 */
void SerialClass::println(const char *string)
{
    print(string);
    uart_tx('\n');
}

/**
 * @brief  Read byte in from UART.
 * @return Byte read from UART.
 */
uint8_t SerialClass::read()
{
    return uart_rx();
}

/**
 * @brief  Read string in from UART.
 * @return String received.
 */
const char *SerialClass::readString()
{
    int i=0;
    char *string;
    char character = uart_rx();

    while(character != '\n') {
        string[i] = character;
        i++;
    }
    return string;
}

/**
 * @brief Transmit byte over UART.
 * @param data Byte to be sent.
 */
void SerialClass::uart_tx(char data)
{
    // if there's a newline, send a carriage return
    if (data == '\n') {
        uart_tx('\r');
    }
    while(!(_uart_register.STATUS & USART_DREIF_bm));
    _uart_register.DATA = data;
}

/**
 * @brief  Receive byte over UART.
 * @return Byte received.
*/
char SerialClass::uart_rx()
{
    while(!(_uart_register.STATUS & USART_RXCIF_bm));
    return _uart_register.DATA;
}
