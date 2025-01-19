/*
 * ansi.h
 *
 *  Created on: 6. jan. 2025
 *      Author: frikk
 */
#include "stdint.h"
#include"stdio.h"
#include "charset.h"

#ifndef _ANSI_H_
#define _ANSI_H_




void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char *string, int style);

void ballwindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void sincalc();

void clrscr();
void clreol();

void underline();
void blink();
void inverse();
void underlineOFF();
void blinkOFF();
void inverseOFF();
void startcursor();

void setLED(int R, int G, int B);






void graphicss();


//void lcd_write_string(char string[], int location);







uint8_t vertline();
uint8_t strline();
uint8_t TLcnr();
uint8_t TRcnr();
uint8_t BLcnr();
uint8_t BRcnr();



void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);

#endif
