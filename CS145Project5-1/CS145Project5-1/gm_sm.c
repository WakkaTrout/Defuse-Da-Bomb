#include "gm_sm.h"
#include "bus1.h"

char GAME_DONE = 0;
char WIN = 0;

void 
init_gm()
{
	gm_flags.defuse = 0;
	gm_flags.combo = 0;
	gm_flags.unused = 0;	
}

void 
TickFct_GM()
{
		
		char read_bus = bus1_read();
		if((read_bus&3) > 0)
		{
			if((read_bus&3) == 1)
			{
				gm_flags.defuse = 1;
			}
			else
			{
				GAME_DONE = 1;
				WIN = 0;
			}
		}
		if(((read_bus>>2)&3) > 0)
		{
			if(((read_bus>>2)&3) == 1)
			{
				gm_flags.combo = 1;
			}
			else
			{
				GAME_DONE = 1;
				WIN = 0;
			}
		}
		if(gm_flags.defuse == 1 && gm_flags.combo == 1 && GAME_DONE != 1)
		{
			GAME_DONE = 1;
			WIN = 1;
		}
}