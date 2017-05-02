/***************************************************************************//**
 * @file   led.h
 * @author Tom Darlison
 * @date   2017-05-01
 * @brief  Library for easy use of onboard LEDs
 *******************************************************************************
 * Functions to allow easy use of the two onboard LEDs
 ******************************************************************************/
 
#ifndef LED_H
#define LED_H

// includes 
#include <avr/io.h>

class LED
{
public: // methods
	LED(int _onBoardLED);
	~LED();
	void on();
	void off();
	void toggle();
public: // members
private: // methods
private: // members
	bool _LED1;
};

#endif // LED_H