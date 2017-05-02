/***************************************************************************//**
* @file   led.h
* @author Tom Darlison
* @date   2017-05-01
* @brief  Library for easy use of onboard LEDs
*******************************************************************************
* Functions to allow easy use of the two onboard LEDs
******************************************************************************/
 
#include "led.h"

LED::LED(int _onBoardLED)
{
	_LED1 = (_onBoardLED == 1 ? true : false);
	PORTR.DIR = (_LED1 ? PIN0_bm : PIN1_bm);
}

LED::~LED()
{
	// left blank
}

void LED::on()
{
	PORTR.OUTSET = (_LED1 ? PIN0_bm : PIN1_bm);
}

void LED::off()
{
	PORTR.OUTCLR = (_LED1 ? PIN0_bm : PIN1_bm);
}

void LED::toggle()
{
	PORTR.OUTTGL = (_LED1 ? PIN0_bm : PIN1_bm);
}