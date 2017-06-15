/***************************************************************************//**
 * @file   timer.h
 * @author Tom Darlison
 * @date   2017-06-09
 * @brief  Custom library for the AVR xmega series for timer0/1/2.
 ******************************************************************************/

#ifndef TIMER_H
#define TIMER_H

// includes
#include <avr/io.h>
#include <stdint.h>

#define MAX_TOP 65535 // = 1<<16 - 1

typedef enum {TC0 = 0, TC1, TC2} timerType;

class Timer
{
public: // members
public: // methods
	// c/d-tor
	Timer(TC0_struct TC);
	Timer(TC1_struct TC);
	Timer(TC2_struct TC);
	~Timer();

	// set freqency of timer
	void setFreq(const float & freq);
	void setPeriod_s(const float & period);
	void setPeriod_ms(const float & period);
	float getFreq() const;
	uint16_t getTop() const;

	// set mode and output of waves
	void setMode(const unsigned char mode);
	void portOverride(const bool A, const bool B, const bool C, const bool D);

	// set Comparitor values
	void setCompare (const unsigned int A, const unsigned int B, 
					 const unsigned int C, const unsigned int D);
	void setCompareA(const unsigned int A);
	void setCompareB(const unsigned int B);
	void setCompareC(const unsigned int C);
	void setCompareD(const unsigned int D);

	// set duty cycle for in PWM mode
	void setDuty (const float & A, const float & B, 
				  const float & C, const float & D);
	void setDutyA(const float & A);
	void setDutyB(const float & B);
	void setDutyC(const float & C);
	void setDutyD(const float & D);
private: // members
	timerType type;
	union {
		TC0_struct* p_TC0;
		TC1_struct* p_TC1;
		TC2_struct* p_TC2;
	}; // only need 1 of these pointers in the class once made
	float _frequency; 
	uint16_t _TOP;
private: // methods
	void clockSetUp(const unsigned char &clkDivider, const int &TOP);
};

#endif // TIMER_H

/*
PIN		TCn0	TCn1

PC0	 	OC0A
PC1	 	OC0B
PC2	 	OC0C
PC3	 	OC0D
PC4				OC1A
PC5				OC1B
PC6	 
PC7	 

PD0		OC0A
PD1		OC0B
PD2		OC0C
PD3		OC0D
PD4				OC1A
PD5				OC1B
PD6	 
PD7	 

PE0		OC0A
PE1		OC0B
PE2		OC0C
PE3		OC0D
	
*/