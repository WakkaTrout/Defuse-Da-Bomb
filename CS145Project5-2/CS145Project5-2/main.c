/*
 * CS145Project5-2.c
 *
 * Created: 6/7/2020 9:54:44 PM
 * Author : AJVer
 */ 

#include "avr.h"
#include "kbd.h"
#include "defusal_sm.h"
#include "defuse.h"
#include "bus2.h"
#include "kbd_sm.h"

volatile unsigned char TimerFlag = 0; // ISR raises, main() lowers
unsigned char rnd;
void rand_init();

/* This function initializes timer 1 for use by the state machine*/
void
timer_init()
{
	TCCR1A = 0x00;
	TCCR1B = 3;
	TCNT1 = (unsigned short)(65536 - (XTAL_FRQ / 64)*0.25);   // for 250 msec at 16 MHz
	TIMSK = (1 << TOIE1) ;
	SET_BIT(TIFR, TOV1);
	sei();
}

/* Timer 1 interrupt used for the clock the system is displaying */
ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	TimerFlag = 1;
	TCNT1 = (unsigned short)(65536 - (XTAL_FRQ / 64)*0.25);   // for 250 msec at 16 MHz
	SET_BIT(TIFR, TOV1);
}

int main(void)
{
	bus2_init();
    kbd_init();
	defuse_init();
	rand_init();
	timer_init();
	Defusal_State = DEFU_START;
	KBD_State = KBD_START;
    while (1) 
    {
		TickFct_Defusal();
		TickFct_KBD();
		while (!TimerFlag){}  // Wait for BL's period
		TimerFlag = 0;        // Lower flag
    }
}

void 
rand_init()
{
	while (!GET_BIT(PINA, 0));
	rnd = (PINA >> 1) & 0x03;
}