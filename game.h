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
void player();
int8_t readJoystick();

uint8_t player_move_update(uint8_t PlayerPos, int selector_value);

void select_weapon();
void lcd_write_string(char string[], int location);





// PLAYER SHOOT
typedef struct { //Weapon 1
    int x; // Bullet's horizontal position
    int y; // Bullet's vertical position
    int active; // 1 if the bullet is active, 0 otherwise
} PlayerBullet;

typedef struct { //Weapon 2
    int x; // Bullet's horizontal position
    int y; // Bullet's vertical position
    int active; // 1 if the bullet is active, 0 otherwise
} PlayerBullet2;

void initialize_bullets(PlayerBullet bullets[], int MAX_BULLETS);
void initialize_bullets2(PlayerBullet2 bullets2[], int MAX_BULLETS2);

void shoot(int selector_value, PlayerBullet bullets[], PlayerBullet2 bullets2[], int MAX_BULLETS, int MAX_BULLETS2, uint8_t PlayerPos);

void bullet_update(PlayerBullet bullets[], int MAX_BULLETS);
void bullet_update2(PlayerBullet2 bullets2[], int MAX_BULLETS2);


// ASTEROIDS
typedef struct {
    int x; // Asteroid's horizontal position
    int y; // Asteroid's vertical position
    int j; // Asteroid's health
    int active; // 1 if the Asteroid is active, 0 otherwise
} asteroid;

void initialize_asteroids(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH);

void asteroid_spawn(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH, int time);

void asteroid_update(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH, int times);

void asteroid_collision(asteroid asteroids[], PlayerBullet bullets[], int MAX_ASTEROIDS, int MAX_BULLETS);

void asteroid_collision2(asteroid asteroids[], PlayerBullet2 bullets2[], int MAX_ASTEROIDS, int MAX_BULLETS2);





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
