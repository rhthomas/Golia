/***************************************************************************//**
* @file   led.h
* @author Tom Darlison
* @date   2017-05-01
* @brief  Library for easy use of onboard LEDs
*******************************************************************************
* Functions to allow easy use of the two onboard LEDs
******************************************************************************/
 
#include "led.h"

void led1_init()
{
	PORTR.DIR = PIN0_bm;
}

void led2_init()
{
	PORTR.DIR = PIN1_bm;
}

void leds_init()
{
	led1_init();
	led2_init();
}

void led1_on()
{
	PORTR.OUTSET = PIN0_bm;
}

void led2_on()
{
	PORTR.OUTSET = PIN1_bm;
}

void leds_on()
{
	led1_on();
	led2_on();
}

void led1_off()
{
	PORTR.OUTCLR = PIN0_bm;
}

void led2_off()
{
	PORTR.OUTCLR = PIN1_bm;
}

void leds_off()
{
	led1_off();
	led2_off();
}

void led1_toggle()
{
	PORTR.OUTTGL = PIN0_bm;
}

void led2_toggle()
{
	PORTR.OUTTGL = PIN1_bm;
}

void leds_toggle()
{
	led1_toggle();
	led2_toggle();
}