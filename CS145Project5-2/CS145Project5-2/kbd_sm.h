#ifndef _KBD_SM_H_
#define _KBD_SM_H_

enum AVR__KBD_States { KBD_START, KBD_ONE, KBD_TWO, KBD_THREE, KBD_PASS, KBD_FAIL} KBD_State;

void TickFct_KBD();


#endif /*_KBD_SM_H_*/