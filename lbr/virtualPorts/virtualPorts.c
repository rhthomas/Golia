/*******************************************************************************
* @file   virtualPorts.c
* @author Thomas Darlison
* @date   2017-03-30
* @brief  Virtual Port mapping for I/O Ports
*******************************************************************************/

#include "virtualPorts.h"

/**
 * @brief Setup of Virtual Ports.
 * @param Virtual Port Number and Port to be mapped.
 *
 * Initalise one of the virtual ports to map to a real port. Allows full bit
 * manimulation that would otherwise be inaccessable on memory I/O. Also once 
 * set up, only takes 1 clock cycle to change a pin.
 */
void setVP(const uint8_t virtualPort, const char Port)
{
	unsigned char portHex = 0x00;
	switch(Port)
	{
		case 'A': portHex = 0x00; break;
		case 'B': portHex = 0x01; break;
		case 'C': portHex = 0x02; break;
		case 'D': portHex = 0x03; break;
		case 'E': portHex = 0x04; break;
		case 'F': portHex = 0x05; break;
		case 'G': portHex = 0x06; break;
		case 'H': portHex = 0x07; break;
		// 'I': not used
		case 'J': portHex = 0x08; break;
		case 'K': portHex = 0x09; break;
		case 'L': portHex = 0x0A; break;
		case 'M': portHex = 0x0B; break;
		case 'N': portHex = 0x0C; break;
		// 'O': not used
		case 'P': portHex = 0x0D; break;
		case 'Q': portHex = 0x0E; break;
		case 'R': portHex = 0x0F; break;
		default: return;
	}
	switch(virtualPort)
	{
		case 0: 
			PORTCFG.VPCTRLA |= 0x0F;
			PORTCFG.VPCTRLA &= (0xF0 | (portHex));
			break;
		case 1: 
			PORTCFG.VPCTRLA |= 0xF0;
			PORTCFG.VPCTRLA &= ((portHex << 4) | 0x0F);
			break;
		case 2:
			PORTCFG.VPCTRLB |= 0x0F;
			PORTCFG.VPCTRLB &= (0xF0 | (portHex));
			break;
		case 3:
			PORTCFG.VPCTRLB |= 0xF0;
			PORTCFG.VPCTRLB &= ((portHex << 4) | 0x0F);
			break;
		default: break;
	}
}
