#include "speaker.h"

/* Initializes the speaker */
inline void
speaker_init(void)
{
	/* Set pin as output*/
	SET_BIT(DDRB,3);
	CLR_BIT(PORTB,3);
}

void
play_note(int freq, int duration)
{
	int k = (long)(freq) * (duration)/1000;
	if(freq == 0 || k <= 0)
	{
		CLR_BIT(PORTB,3);
		avr_tmicrowait((duration)*100);
		return;
	}
	unsigned int mH = (50000)/(freq);
	unsigned int mL = 100000/(freq)-mH;
	
	
	for(int i = 0; i < k; ++i)
	{
		
		SET_BIT(PORTB,3);
		avr_tmicrowait(mH);
		CLR_BIT(PORTB,3);
		avr_tmicrowait(mL);
	}
	
}