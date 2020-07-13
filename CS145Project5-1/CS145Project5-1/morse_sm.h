#ifndef _MORSE_SM_H_
#define _MORSE_SM_H_

enum AVR__Morse_States { MRSE_START, MRSE_PASS, MRSE_FAIL} Morse_State;

void mled_init();

void TickFct_Morse();


#endif /*_MORSE_SM_H_*/