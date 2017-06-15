/***************************************************************************//**
 * @file   timer.h
 * @author Tom Darlison
 * @date   2017-06-09
 * @brief  Custom library for the AVR xmega series for timer0/1/2.
 ******************************************************************************/

// switch(type)
// 	{
// 		case TC0: break;
// 		case TC1: break;
// 		case TC2: break;
// 		default: break;
// 	}

#include "timer.h"

Timer::Timer(TC0_struct TC)
{
	p_TC0 = &TC;
	type = TC0;
}
Timer::Timer(TC1_struct TC)

{
	p_TC1 = &TC;
	type = TC1;
}
Timer::Timer(TC2_struct TC)
{
	p_TC2 = &TC;
	type = TC2;
}

Timer::~Timer()
{
	switch(type)
	{
		case TC0: p_TC0 = 0; break;
		case TC1: p_TC1 = 0; break;
		case TC2: p_TC2 = 0; break;
		default: break;
	}
}

void Timer::setFreq(const float & freq)
{
	(F_CPU/(freq*1)   < MAX_TOP) ? clockSetUp(0x01, F_CPU/(freq*1)   ) :
	(F_CPU/(freq*2)   < MAX_TOP) ? clockSetUp(0x02, F_CPU/(freq*2)   ) :
	(F_CPU/(freq*4)   < MAX_TOP) ? clockSetUp(0x03, F_CPU/(freq*4)   ) :
	(F_CPU/(freq*8)   < MAX_TOP) ? clockSetUp(0x04, F_CPU/(freq*8)   ) :
	(F_CPU/(freq*64)  < MAX_TOP) ? clockSetUp(0x05, F_CPU/(freq*64)  ) :
	(F_CPU/(freq*265) < MAX_TOP) ? clockSetUp(0x06, F_CPU/(freq*265) ) :
		clockSetUp(0x07, (F_CPU/(freq*1024)>MAX_TOP ? MAX_TOP : (F_CPU/(freq*1024))));
}

void Timer::setPeriod_s(const float & period)
{
	setFreq(1.0f/period);
}

void Timer::setPeriod_ms(const float & period)
{
	setFreq(1000.0f/period);
}

float Timer::getFreq() const 
{
	return _frequency;
}

uint16_t Timer::getTop() const 
{
	return _TOP;
}

void Timer::setMode(const unsigned char mode)
{
	switch(type)
	{
		case TC0: 
			p_TC0->CTRLB &= 0xF0;
			p_TC0->CTRLB |= mode;
			break;
		case TC1: 
			p_TC1->CTRLB &= 0xF0;
			p_TC2->CTRLB |= mode;
			break;
		case TC2: break; // implement
		default: break;
	}
}

void Timer::portOverride(const bool A, const bool B, const bool C, const bool D)
{
	switch(type)
	{
		case TC0: 
			p_TC0->CTRLB &= 0x0F;
			p_TC0->CTRLB |= (A<<4 || B<<5 || C<<6 || D<<7);
			break;
		case TC1: 
			p_TC1->CTRLB &= 0x0F;
			p_TC1->CTRLB |= (A<<4 || B<<5 || C<<6 || D<<7);
			break;
		case TC2: break;
		default: break;
	}
}

void Timer::setCompare(const unsigned int A, const unsigned int B, 
					   const unsigned int C, const unsigned int D)
{
	setCompareA(A);
	setCompareB(B);
	setCompareC(C);
	setCompareD(D);
}

void Timer::setCompareA(const unsigned int A)
{
	switch(type)
	{
		case TC0: p_TC0->CCA = A; break;
		case TC1: p_TC1->CCA = A; break;
		case TC2: break; // implement
		default: break;
	}
	//_timerID.CCA = A;
}

void Timer::setCompareB(const unsigned int B)
{
	switch(type)
	{
		case TC0: p_TC0->CCB = B; break;
		case TC1: p_TC1->CCB = B; break;
		case TC2: break; // implement
		default: break;
	}
	//_timerID.CCB = B;
}

void Timer::setCompareC(const unsigned int C)
{
	switch(type)
	{
		case TC0: p_TC0->CCC = C; break;
		case TC1: break;
		case TC2: break; // implement
		default: break;
	}
	//_timerID.CCC = C;
}

void Timer::setCompareD(const unsigned int D)
{
	switch(type)
	{
		case TC0: p_TC0->CCD = D; break;
		case TC1: break;
		case TC2: break; // implement
		default: break;
	}
	//_timerID.CCD = D;
}

void Timer::setDuty(const float & A, const float & B, 
					const float & C, const float & D)
{
	setDutyA(A);
	setDutyB(B);
	setDutyC(C);
	setDutyD(D);
}

void Timer::setDutyA(const float & A)
{
	switch(type)
	{
		case TC0: p_TC0->CCA = _TOP * A; break;
		case TC1: p_TC1->CCA = _TOP * A; break;
		case TC2: break; // implement
		default: break;
	}
//	_timerID.CCA = _TOP * A;
}

void Timer::setDutyB(const float & B)
{
	switch(type)
	{
		case TC0: p_TC0->CCB = _TOP * B; break;
		case TC1: p_TC1->CCB = _TOP * B; break;
		case TC2: break; // implement
		default: break;
	}
}

void Timer::setDutyC(const float & C)
{
	switch(type)
	{
		case TC0: p_TC0->CCC = _TOP * C; break;
		case TC1: break;
		case TC2: break; // implement
		default: break;
	}
}

void Timer::setDutyD(const float & D)
{
	switch(type)
	{
		case TC0: p_TC0->CCD = _TOP * D; break;
		case TC1: break;
		case TC2: break; // implement
		default: break;
	}
}

void Timer::clockSetUp(const unsigned char & clkDivider, const int & TOP) 
{
	// Timer dependant code
	switch(type)
	{
		case TC0: 
			p_TC0->CTRLA = clkDivider; 
			p_TC0->PER = TOP;
			break;
		case TC1: 
			p_TC1->CTRLA = clkDivider; 
			p_TC1->PER = TOP;
			break;
		case TC2: //implement
			break;	
		default: break;
	}
	// Universal code
	_TOP = TOP;
	_frequency = (F_CPU/(float)(TOP* (clkDivider > 0x04 ? 
					(1<<((clkDivider - 2) *2)) : (1<<(clkDivider-1))) ));
}