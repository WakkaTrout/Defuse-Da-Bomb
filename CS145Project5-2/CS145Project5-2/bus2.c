#include "bus2.h"

void
bus2_init()
{
	/*initialize bus to write*/
	DDRA = 0xFF;
	PORTA =	0x00;
	
	/*initialize first 3 bits of bus to read*/
	CLR_BIT(DDRA, 0);
	CLR_BIT(DDRA, 1);
	CLR_BIT(DDRA, 2);
}