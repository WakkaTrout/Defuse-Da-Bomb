#include "rand.h"

void rand_init()
{
	CLR_BIT(DDRA, 0);
	CLR_BIT(PORTA, 0);
	get_sample();
	srand(get_sample());
}

int
get_sample()
{
	ADMUX = 0x40;
	ADCSRA = 0xC0;
	while(GET_BIT(ADCSRA,ADSC));
	return ADC;
}