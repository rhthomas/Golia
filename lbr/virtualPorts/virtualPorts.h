/*******************************************************************************
* @file   virtualPorts.h
* @author Thomas Darlison
* @date   2017-03-30
* @brief  Virtual Port mapping for I/O Ports
*******************************************************************************/

#ifndef VIRTUALPORTS_H
#define VIRTUALPORTS_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Setup of Virtual Ports.
 * @param Virtual Port Number and Port to be mapped.
 *
 * Initalise one of the virtual ports to map to a real port. Allows full bit
 * manimulation that would otherwise be inaccessable on memory I/O. Also once 
 * set up, only takes 1 clock cycle to change a pin.
 */
void setVP(const uint8_t virtualPort, const char Port);

#endif // VIRTUALPORTS_H