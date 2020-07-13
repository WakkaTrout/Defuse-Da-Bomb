#ifndef _COUNT_SM_H_
#define _COUNT_SM_H_

enum AVR_Count_States { CNT_START, CNT_DOWN, CNT_DONE, CNT_FAIL} Count_State;

struct Counter
{
	unsigned char min;
	unsigned char sec;
	unsigned char hmsec;
	}	counter;

void TickFct_Count();


#endif /*_COUNT_SM_H_*/