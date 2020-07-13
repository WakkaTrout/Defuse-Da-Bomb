/**
 * kbd.c
 */

#include "avr.h"
#include "kbd.h"

static char keys[] = {' ', '1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0','#','D'};

/* Gets key from keyboard and converts it to a char*/
inline char 
get_kbd_char(void)
{
	return keys[get_key()];
}

/* Scans keyboard for the first instance of a pressed key */
inline int 
get_key(void)
{
	int r, c;
	
	for(r = 0; r < ROWS; ++r)
	{
		for(c = 0; c < COLS; ++c)
		{
			if(is_pressed(r,c))
			{
				return r*4 + c + 1;
			}
		}
	}
	return 0;
}

/* Checks to see if a key is pressed or not at a given row and column*/
inline unsigned char
is_pressed(int r, int c)
{
	unsigned char set = 0;
	
	/* Set column to weak 1 and row to s0*/
	SET_BIT(PORTC, c);
	SET_BIT(DDRC, 4+r);
	CLR_BIT(PORTC,4+r);
	
	/* read column if pressed*/
	set = !GET_BIT(PINC, c);
	
	/* Reset row to input and everything to n/c */
	CLR_BIT(DDRC, 4+r);
	PORTC = 0x00;
	
	return set;
	
}

/* Initializes the keyboard */
inline void 
kbd_init(void)
{
	/* Set pins as input and initialize pins to no connect (pull-up off)*/
	DDRC = 0x00;
	PORTC = 0x00;
	
	SET_BIT(DDRB,0);
	SET_BIT(DDRB,1);
	SET_BIT(DDRB,2);
	SET_BIT(DDRB,3);
	CLR_BIT(PORTB,0);
	CLR_BIT(PORTB,1);
	CLR_BIT(PORTB,2);
	CLR_BIT(PORTB,3);
	
}