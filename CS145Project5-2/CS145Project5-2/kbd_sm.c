#include "kbd_sm.h"
#include "avr.h"
#include "kbd.h"

extern unsigned char rnd;
unsigned char flash;

char combos[4][4] =
{{'8', 'A', '4', '#'},
 {'D', '2', '*', 'B'},
 {'#', '5', '9', '7'},
 {'6', '9', 'D', '4'}};

inline void
TickFct_KBD()
{
	char key;
	switch(KBD_State) {   // Transitions
		case KBD_START:  // Initial transition
			key = get_kbd_char();
			if(key == combos[rnd][0])
			{
				KBD_State = KBD_ONE;
				SET_BIT(PORTB, 0);
			}
			else if(key != ' ')
			{
				KBD_State = KBD_FAIL;
				flash = 1;
				SET_BIT(PORTB, 0);
				SET_BIT(PORTB, 1);
				SET_BIT(PORTB, 2);
				SET_BIT(PORTB, 3);
				CLR_BIT(PORTA, 6);
				SET_BIT(PORTA, 5);
			}
			break;
		
		case KBD_ONE://State signifying the correct wire have been "cut"
			key = get_kbd_char();
			if(key == combos[rnd][1])
			{
				KBD_State = KBD_TWO;
				SET_BIT(PORTB, 1);
			}
			else if(key != ' ')
			{
				KBD_State = KBD_FAIL;
				flash = 1;
				SET_BIT(PORTB, 0);
				SET_BIT(PORTB, 1);
				SET_BIT(PORTB, 2);
				SET_BIT(PORTB, 3);
				CLR_BIT(PORTA, 6);
				SET_BIT(PORTA, 5);
			}
			break;
		
		case KBD_TWO://State signifying the correct wire have been "cut"
			key = get_kbd_char();
			if(key == combos[rnd][2])
			{
				KBD_State = KBD_THREE;
				SET_BIT(PORTB, 2);
			}
			else if(key != ' ')
			{
				KBD_State = KBD_FAIL;
				flash = 1;
				SET_BIT(PORTB, 0);
				SET_BIT(PORTB, 1);
				SET_BIT(PORTB, 2);
				SET_BIT(PORTB, 3);
				CLR_BIT(PORTA, 6);
				SET_BIT(PORTA, 5);
			}
			break;
		
		case KBD_THREE:
			key = get_kbd_char();
			if(key == combos[rnd][3])
			{
				KBD_State = KBD_PASS;
				SET_BIT(PORTB, 3);
				SET_BIT(PORTA, 6);
				SET_BIT(PORTA, 5);
			}
			else if(key != ' ')
			{
				KBD_State = KBD_FAIL;
				flash = 1;
				SET_BIT(PORTB, 0);
				SET_BIT(PORTB, 1);
				SET_BIT(PORTB, 2);
				SET_BIT(PORTB, 3);
				CLR_BIT(PORTA, 6);
				SET_BIT(PORTA, 5);
			}
			break;

		case KBD_PASS://State signifying the correct wire have been "cut"
			KBD_State = KBD_PASS;
			break;

		case KBD_FAIL://State signifying an incorrect wire has been "cut"
			KBD_State = KBD_FAIL;
			if(flash == 1)
			{
				CLR_BIT(PORTB, 0);
				CLR_BIT(PORTB, 1);
				CLR_BIT(PORTB, 2);
				CLR_BIT(PORTB, 3);
				flash = 0;
			}
			else
			{
				SET_BIT(PORTB, 0);
				SET_BIT(PORTB, 1);
				SET_BIT(PORTB, 2);
				SET_BIT(PORTB, 3);
				flash = 1;
			}
			break;
		
		default:
			KBD_State = KBD_START;
			break;
	} // Transitions
	
}