/*
 * ansi.h
 *
 *  Created on: 6. jan. 2025
 *      Author: frikk
 */
#include "stdint.h"
#include"stdio.h"
#include "charset.h"

#ifndef _GAME_H_
#define _GAME_H_


void movexy(uint8_t x, uint8_t y);
void border();
void player_movement();
int8_t readJoystick();
int8_t Selector();
void Asteroid();


void timerdisable();

void initFlag(void);
void initTime(void);
void timerdisplay2();
void TIM1_BRK_TIM15_IRQHandler(void);
void draw_boss_sprite();



struct flag {
	volatile int status;
};
volatile struct flag globalFlag;






#endif
