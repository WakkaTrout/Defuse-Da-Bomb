/*
 * CS145Project5-1.c
 *
 * Created: 6/7/2020 9:52:10 PM
 * Author : Anthony VerBurg and Christopher VerBurg
 * ID:      30173461        and 15935028
 */ 

#include "avr.h"
#include "lcd.h"
#include "speaker.h"
#include "rand.h"
#include "stdlib.h"
#include "bus1.h"
#include "morse_sm.h"
#include "count_sm.h"
#include "gm_sm.h"

unsigned char rnd;
char bombChar;

volatile unsigned char TimerFlag = 0; // ISR raises, main() lowers

/* This function initializes timer 1 for use by the state machine*/
void
timer_init(void)
{
	
	TCCR1A = 0x00;
	TCCR1B = 3;
	TCNT1 = (unsigned short)(65536 - (XTAL_FRQ / 64) * 0.1);   // for 100 msec at 16 MHz
	TIMSK = (1 << TOIE1) ;
	SET_BIT(TIFR, TOV1);
	sei();
}

/* Timer 1 interrupt used for the clock the system is displaying */
ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	TimerFlag = 1;
	TCNT1 = (unsigned short)(65536 - (XTAL_FRQ / 64) * 0.1);   // for 100 msec at 16 MHz
	SET_BIT(TIFR, TOV1);
}

char EXPLOSIVE_CHARS[] =
{
	/* Full bomb */
	0b11000,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01110,
	
	/* -1 bomb */
	0b01000,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01110,
	
	/* -2 bomb */
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01110,
	
	
	/* -3 bomb */
	0b00000,
	0b00000,
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01110,
	
	/* Explosion 1 */
	0b00000,
	0b00000,
	0b00000,
	0b00110,
	0b01110,
	0b00110,
	0b01100,
	0b00000,
	
	/* Explosion 2 */
	0b00000,
	0b00010,
	0b01000,
	0b10110,
	0b01110,
	0b00110,
	0b01100,
	0b10010,
	
	/* Explosion 3 */
	0b10000,
	0b00001,
	0b01000,
	0b10110,
	0b00010,
	0b10010,
	0b01000,
	0b10001,
	
	/* Explosion 4 */
	0b00100,
	0b10010,
	0b00000,
	0b10010,
	0b00010,
	0b00010,
	0b10000,
	0b00010,
};

int main(void)
{
	rand_init();
	rnd = (rand() >> 4) % 4;
	bus1_init();
	lcd_init();
	lcd_write_to_ram(EXPLOSIVE_CHARS,8);
	speaker_init();
	mled_init();
	timer_init();
	init_gm();
	
	Count_State = CNT_START;
	lcd_clr();
	bombChar = 0;
	lcd_pos(0,0);
	lcd_put(bombChar);
	//lcd_pos(1,2);
	//lcd_put(rnd+'0');
	
    while (1) 
    {
		TickFct_Count();
		TickFct_Morse();
		TickFct_GM();
		
		while (!TimerFlag){}  // Wait for BL's period
		TimerFlag = 0;        // Lower flag
    }
}

