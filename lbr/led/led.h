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

// init
void led1_init();
void led2_init();
void leds_init();

// on 
void led1_on();
void led2_on();
void leds_on();

// off
void led1_off();
void led2_off();
void leds_off();

// toggle
void led1_toggle();
void led2_toggle();
void leds_toggle();

#endif // LED_H