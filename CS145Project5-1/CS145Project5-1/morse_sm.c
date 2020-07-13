#include "morse_sm.h"
#include "avr.h"

static unsigned char index;
extern unsigned char rnd;
extern char GAME_DONE;

#define NUM_CYCLE 45

char MorseArray[4][NUM_CYCLE]= {
	{1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
		
inline void
TickFct_Morse()
{
	if(!GAME_DONE)
	{		
		if(MorseArray[rnd][index])
		{
			SET_BIT(PORTA, 3);
		}
		else
		{
			CLR_BIT(PORTA, 3);
		}
		index = (index+1) % NUM_CYCLE;
	}
	else
	{
		CLR_BIT(PORTA,3);
	}
}

void
mled_init()
{
	index = 0;
	SET_BIT(DDRA, 3);
	CLR_BIT(PORTA, 3);
}