#ifndef _GM_SM_H_
#define _GM_SM_H_

enum AVR_GM_States { GM_START, GM_WIN, GM_LOSE} GM_State;

struct GM_Flags
{
	unsigned char defuse:1;
	unsigned char combo:1;
	unsigned char unused:6;
}	gm_flags;

void init_gm();

void TickFct_GM();


#endif /*_GM_SM_H_*/