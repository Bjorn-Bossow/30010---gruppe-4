/*
 * menu.h
 *
 *  Created on: 19. jan. 2025
 *      Author: frikk
 */

#include "stdint.h"
#include"stdio.h"
#include "charset.h"
#include "ansi.h"
#include "game.h"



#ifndef MENU_H_
#define MENU_H_

void gotoxy(uint8_t x, uint8_t y);
void menu();
void difficulty_select();
void help_screen();

#endif /* MENU_H_ */
