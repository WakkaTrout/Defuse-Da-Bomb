/**
 * kbd.h
 */

#ifndef _KBD_H_
#define _KBD_H_

#define ROWS 4
#define COLS 4

void kbd_init(void);

int get_key(void);

char get_kbd_char(void);

unsigned char is_pressed(int r, int c);

#endif /* _AVR_H_ */