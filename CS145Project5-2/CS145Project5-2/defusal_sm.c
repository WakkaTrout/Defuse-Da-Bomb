#include "defusal_sm.h"
#include "avr.h"
#include "defuse.h"

inline void
TickFct_Defusal()
{
	unsigned char check;
	
	switch(Defusal_State) {   // Transitions
		case DEFU_START:  // Initial transition
		{
			check = CheckWires();
			if(check == 0)
			{
				Defusal_State = DEFU_START;
			}
			else if (check == 1)
			{
				Defusal_State = DEFU_PASS;
				SET_BIT(PORTD, 0);
				SET_BIT(PORTA, 4);
				SET_BIT(PORTA, 3);
			}
			else
			{
				Defusal_State = DEFU_FAIL;
				SET_BIT(PORTD, 1);
				CLR_BIT(PORTA, 4);
				SET_BIT(PORTA, 3);
			}
			
		}
		break;

		case DEFU_PASS://State signifying the correct wire have been "cut"
		Defusal_State = DEFU_PASS;
		break;

		case DEFU_FAIL://State signifying an incorrect wire has been "cut"
		Defusal_State = DEFU_FAIL;
		break;
		
		default:
		Defusal_State = DEFU_START;
		break;
	} // Transitions
	
}