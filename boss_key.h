#ifndef BOSS_KEY_H
#define BOSS_KEY_H

#define ESC 0x1B
#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

// Function to draw a simple window
void draw_window(int x, int y, int width, int height);

// Function to display text inside the window
void display_text_in_window(int x, int y, const char *text);

// Function to create a spreadsheet window
void spreadsheet(int x, int y, int width, int height, int fg, int bg);

// Function to create a "how to work" window
void how_to_work_window(int x, int y, int width, int height, int fg, int bg);

// Default bosskey variables
extern int spreadsheet_x;
extern int spreadsheet_y;
extern int spreadsheet_width;
extern int spreadsheet_height;
extern int work_window_x;
extern int work_window_y;
extern int work_window_width;
extern int work_window_height;
extern int spreadsheet_fg;
extern int spreadsheet_bg;
extern int work_window_fg;
extern int work_window_bg;

// Function to configure settings for boss key
void settings_boss_key(int x, int y, int width, int height, int fg, int bg);

//the boss_key function
int boss_key(void);


#endif // BOSS_KEY_H
