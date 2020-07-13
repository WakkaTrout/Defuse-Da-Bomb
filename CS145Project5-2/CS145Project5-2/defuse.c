#include "defuse.h"

void
defuse_init()
{
	/* Initialize fuses to input with pull-up*/
	DDRD = 0x00;
	PORTD = 0xFC;
	
	/* Initialize finished LED*/
	SET_BIT(DDRD, 0);
	SET_BIT(DDRD, 1);

}
extern unsigned char rnd;
char wires[4] = {0x34,0x58,0x2C,0x54};

unsigned char CheckWires()
{
	char count  = 0;
	char port = PIND;
	for(char i = LOWER_WIRES; i < UPPER_WIRES_P1; ++i)
	{
		if(((port>>i)&1) == ((wires[rnd]>>i)&1))
		{
			if(((port>>i)&1) == 1)
			{
				++count;
			}
		}
		else
		{
			if(((port>>i)&1) == 1)
			{
				return 2;
			}
		}
		
		
	}
	if(count == 3)
		return 1;
	return 0;
	
}