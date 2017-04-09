/***************************************************************************//**
 * @file   spi.h
 * @author Rhys Thomas
 * @date   2017-03-20
 * @brief  SPI library for the Goila board.
 ******************************************************************************/

#ifndef _SPI_H_
#define _SPI_H_

// includes
#include <avr/io.h>

/**
 * @class SPIClass
 * @brief
*/
class SPIClass
{
public: // methods
    SPIClass();
    ~SPIClass();
    void begin();
    uint8_t xfer();
public: // members
private: // methods
private: // members
};

extern SPIClass SPI;

#endif // _SPI_H_
