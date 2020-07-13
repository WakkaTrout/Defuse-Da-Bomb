#include "bus1.h"
extern unsigned char rnd;

void
bus1_init()
{
	/*initialize bus to read*/
	DDRC = 0x00;
	PORTC =	0x00;
	
	/*initialize first 3 bits of bus to write*/
	SET_BIT(DDRC, 0);
	SET_BIT(DDRC, 1);
	SET_BIT(DDRC, 2);
	PORTC = (rnd &0x03)<<1;
	SET_BIT(PORTC, 0);
}

char 
bus1_read()
{
	char bus = 0;
	if(GET_BIT(PINC,3) > 0)
	{
		if(GET_BIT(PINC,4) > 0)
		{
			bus |= 0x1;
		}
		else
		{
			bus |= 0x2;
		}
	}
	if(GET_BIT(PINC,5) > 0)
	{
		if(GET_BIT(PINC,6) > 0)
		{
			bus |=  0x4;
		}
		else
		{
			bus |= 0x8;
		}
	}
		
	
	return bus;
}