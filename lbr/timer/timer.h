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
#include <avr/interrupt.h>

#define MAX_TOP  65535	// = 1<<16 - 1
#define MAX_TOP2 255	// = 1<<8  - 1

typedef enum {TC0 = 0, TC1, TC2} timerType;

// todo
// 
// add in all timer 2 functionailty 
// 		- make sure timer 0 runs in normal mode
// 		- timer 2 runs in split mode
// add in timer 2 set compare and port output
// ISR for timer 2 in normal mode
// set compare/duty -> optimise for 2 chanel on timer 1
// 

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
	void setPeriod_s (const float & period);
	void setPeriod_ms(const float & period);
	void setPeriod_us(const float & period);
	float getFreq() const;
	uint16_t getTop() const;

	// set mode and output of waves
	void setTick(const float & freq); // OVF_vect
	void setMode(const unsigned char mode);
	void portOverride(const bool A, const bool B, const bool C, const bool D);

	// set Comparitor values
	void setCompare (const unsigned int A, const unsigned int B, 
					 const unsigned int C, const unsigned int D);
	void setCompareA(const unsigned int A);
	void setCompareB(const unsigned int B);
	void setCompareC(const unsigned int C);
	void setCompareD(const unsigned int D);

	// PWM mode
	void initPWM (const float & freq, 
				  const float & A, const float & B, 
				  const float & C, const float & D);
	void setDuty (const float & A, const float & B, 
				  const float & C, const float & D);
	void setDutyA(const float & A);
	void setDutyB(const float & B);
	void setDutyC(const float & C);
	void setDutyD(const float & D);
private: // members
	const timerType _type;
	union {
		TC0_struct* p_TC0;
		TC1_struct* p_TC1;
		TC2_struct* p_TC2;
	}; // only need 1 of these pointers in the class once made
	float _frequency; 
	uint16_t _TOP;
private: // methods
	void clockSetUp(const unsigned char & clkDivider, const int & TOP);
};

#endif // TIMER_H

/*

// NOTE: TC0 and TC2 use same hardware 
// therefore cannot coexist on same port

PIN		TCn0	TCn1	TCn2

PC0	 	OC0A			LCMPA
PC1	 	OC0B			LCMPB
PC2	 	OC0C			LCMPC
PC3	 	OC0D			LCMPD
PC4				OC1A	HCMPA
PC5				OC1B	HCMPB
PC6	 					HCMPC
PC7	 					HCMPD

PD0		OC0A			LCMPA
PD1		OC0B			LCMPB
PD2		OC0C			LCMPC
PD3		OC0D			LCMPD
PD4				OC1A	HCMPA
PD5				OC1B	HCMPB
PD6	 					HCMPC
PD7	 					HCMPD

PE0		OC0A			
PE1		OC0B			
PE2		OC0C			
PE3		OC0D			
	
*/