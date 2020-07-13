#include "count_sm.h"
#include "lcd.h"
#include "speaker.h"

extern char GAME_DONE;
extern char WIN;
extern char bombChar;

void
TickFct_Count()
{
	switch(Count_State) {   // Transitions
		case CNT_START:  // Initial transition
		{		
			Count_State = CNT_DOWN;
			counter.min = 1;
			counter.sec = 35;
			counter.hmsec = 0;
		}
			break;
			
		case CNT_DOWN:
			if(GAME_DONE)
			{
				if(WIN)
					Count_State = CNT_DONE;
				else
					Count_State = CNT_FAIL;
				lcd_clr();
			}
			else if(counter.hmsec == 0)
			{
				if(counter.sec == 0)
				{
					if(counter.min == 0)
					{
						GAME_DONE = 1;
						WIN = 0;
						Count_State = CNT_FAIL;
						lcd_clr();
					}
					else
					{
						--counter.min;
						counter.sec = 59;
						counter.hmsec = 9;
					}
				}
				else
				{
					--counter.sec;
					counter.hmsec = 9;
				}
			}
			else
			{
				--counter.hmsec;
			}
			if(counter.sec %30 == 0 && counter.hmsec == 0)
			{
				lcd_pos(0,0);
				lcd_put(bombChar);
				++bombChar;
			}
			break;

		case CNT_DONE://State signifying the correct wire have been "cut"
			Count_State = CNT_DONE;
			break;

		case CNT_FAIL://State signifying an incorrect wire has been "cut"
			 Count_State = CNT_FAIL;
			break;
		
		default:
			Count_State = CNT_START;
			break;
	} // Transitions
	char buf[8];
	switch(Count_State) {   // State actions
		case CNT_START://Display a welcome screen
		{
		}
		break;
		
		case CNT_DOWN://Display the date and time
		buf[1] = '0' + (counter.min % 10);
		buf[0] ='0' + (counter.min  / 10);
		buf[2] = ':';
		buf[4] = '0' + (counter.sec % 10);
		buf[3] ='0' + (counter.sec / 10);
		buf[5] = '.';
		buf[6] = '0' + counter.hmsec;
		buf[7] = '\0';
		lcd_pos(0,4);
		lcd_puts(buf);
		break;

		case CNT_DONE:
			lcd_pos(0,0);
			lcd_puts("BOMB DEFUSED!");
			
		break;
		
		case CNT_FAIL:
			lcd_pos(0,0);
			lcd_puts("BOMB LOST...");
			while(bombChar < 8)
			{
				lcd_pos(0, 12);
				lcd_put(bombChar);
				++bombChar;
				avr_wait(150);
			}
			lcd_pos(0, 12);
			lcd_put(' ');
			
		break;

		default:
		break;
	} // State actions
}