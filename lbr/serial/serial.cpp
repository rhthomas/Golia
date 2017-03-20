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
SerialClass Serial;

SerialClass::SerialClass()
{ /* Left empty */ }

SerialClass::~SerialClass()
{ /* Left empty */ }

void SerialClass::begin(unsigned long setBaud)
{
    baud = F_CPU/(setBaud*16UL)-1;
	UBRR0H = baud >> 8;
	UBRR0L = baud;
	// enable the tx and rx
	UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
	// uart config 8N1
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

void SerialClass::print(const char *string)
{
    while(*string != '\0') {
		uart_tx(*string++);
	}
}

void SerialClass::println(const char *string)
{
    print(string);
    uart_tx('\n');
}

uint8_t SerialClass::read()
{
    return uart_rx();
}

char *SerialClass::readString()
{
    // read bytes until \n
}

void SerialClass::uart_tx(char data)
{
	// if there's a newline, send a carriage return
	if (data == '\n') {
		uart_tx('\r');
	}
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

char SerialClass::uart_rx()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
