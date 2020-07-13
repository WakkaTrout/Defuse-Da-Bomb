/**
 * lcd.h
 * Copyright (C) 2001-2020, Tony Givargis
 */

#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);

void lcd_clr(void);

void lcd_pos(unsigned char r, unsigned char c);

void lcd_put(char c);

void lcd_puts(const char *s);

void lcd_write_to_ram(char* new_chars, int size);

#endif /* _LCD_H_ */