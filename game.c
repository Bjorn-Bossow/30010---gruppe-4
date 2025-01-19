/*
 * ansi.c
 *
 *  Created on: 6. jan. 2025
 *      Author: frikk
 */
#include "game.h"
#include "lcd.h"
#include "stdint.h"
#include"stdio.h"
#include <stdlib.h>
#include "string.h"
#include "30010_io.h"
#include "charset.h"
#include "ansi.h"
#include <time.h>
#define ESC 0x1B



void movexy(uint8_t x, uint8_t y) {
	printf("%c[%d;%dH",ESC,y,x);
}


void border() {
	uint8_t TL = 218;
	uint8_t TR = 191;
	uint8_t BL = 192;
	uint8_t BR = 217;
	uint8_t HorzLine = 196;
	uint8_t VertLine = 179;

	movexy(1,1);
	printf("%c",TL);
	for (int i = 1; i < 188; i++) {
		printf("%c",HorzLine);
	}
	printf("%c",TR);
	for (int i = 2; i < 50; i++) {
		movexy(1,i);
		printf("%c", VertLine);
		movexy(189,i);
		printf("%c", VertLine);
	}
	movexy(1,50);
	printf("%c", BL);
	for (int i = 1; i < 15; i++) {
		printf("%c",HorzLine);
	}
	printf("%c",VertLine);
	printf("\033[31m<3<3<3<3<3\033[0m");
	printf("%c",VertLine);
	for (int i = 1; i < 162; i++) {
		printf("%c",HorzLine);
	}
	printf("%c",BR);
}


void timerdisable() {

	RCC->APB2ENR|= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	TIM15->CR1 &= ~(0x0001 << 0); // disable counter
}

void timerdisplay1() {
	initFlag();

	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;



	TIM15->CR1 &= ~(0x0001 << 11); // Configure timer 15
	TIM15->CR1 |= (0x0003 << 8); // Configure timer 15
	TIM15->CR1 &= ~(0x0001 << 7); // Configure timer 15
	TIM15->CR1 &= ~(0x0001 << 3); // Configure timer 15
	TIM15->CR1 &= ~(0x0001 << 2); // Configure timer 15
	TIM15->CR1 &= ~(0x0001 << 1); // Configure timer 15
	TIM15->CR1 |= (0x0001 << 0);


	TIM15->ARR = 0xF9FF; // Set reload value

	TIM15->PSC = 0x0063; // Set prescale value

	TIM15->DIER |= 0x0001; // Set interrupt value

	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt

}

void timerdisplay2() { // fast
	initFlag();

	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;



	TIM15->CR1 &= ~(0x0001 << 11); // Configure timer 15
	TIM15->CR1 |= (0x0003 << 8);
	TIM15->CR1 &= ~(0x0001 << 7);
	TIM15->CR1 &= ~(0x0001 << 3);
	TIM15->CR1 &= ~(0x0001 << 2);
	TIM15->CR1 &= ~(0x0001 << 1);
	TIM15->CR1 |= (0x0001 << 0);


	TIM15->ARR = 0xF9FF; // Set reload value

	TIM15->PSC = 0x0032; // Set prescale value

	TIM15->DIER |= 0x0001; // Set interrupt value

	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt

}

void TIM1_BRK_TIM15_IRQHandler(void) {

globalFlag.status = 1;

//Do whatever you want here, but make sure it doesn’t take too much Time.
TIM15->SR &= ~0x0001; // Clear interrupt bit

}


volatile struct flag globalFlag;

void initFlag(void) {
	globalFlag.status = 0;
}


void initialize_bullets(PlayerBullet bullets[], int MAX_BULLETS) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].active = 0;
    }
}

void initialize_bullets2(PlayerBullet2 bullets2[], int MAX_BULLETS2) {
    for (int i = 0; i < MAX_BULLETS2; i++) {
        bullets2[i].x = 0;
        bullets2[i].y = 0;
        bullets2[i].active = 0;
    }
}


void player(void) {
	uint8_t PlayerPos = 25; // Player y location
	int times = 0;
    int MAX_BULLETS = 10;
    int MAX_BULLETS2 = 3;
    int MAX_ASTEROIDS = 10;
    int ASTEROID_HEALTH = 10;
    PlayerBullet bullets[MAX_BULLETS]; // Array of bullets for weapon 1
    PlayerBullet2 bullets2[MAX_BULLETS2]; // Array of bullets for weapon 2
    asteroid asteroids[MAX_ASTEROIDS]; // Array for asteroids

    srand(time(NULL));


    // Initialize bullets array
    initialize_bullets(bullets, MAX_BULLETS);

    // Initialize bullets array 2
    initialize_bullets2(bullets2, MAX_BULLETS2);

    // Initialize asteroid array
    initialize_asteroids(asteroids, MAX_ASTEROIDS, ASTEROID_HEALTH);


    // Draw the player initially
    movexy(3, PlayerPos);
    printf("\033[35m>\033[0m"); // Player model

    int selector_value = 1; // Store the result of the selector
    lcd_init();
    while (1) {

        // Wait until 100ms has passed (timerFlag should be set by interrupt)
        if (globalFlag.status == 1) {
        	times++;
            // Check joystick for selecting the weapon and ability
            if (readJoystick() == 3) {
                selector_value = Selector(); // Store the result of the selector
            }
            PlayerPos = player_move_update(PlayerPos, selector_value);

            // Check joystick input for shooting
            shoot(selector_value, bullets, bullets2, MAX_BULLETS, MAX_BULLETS2, PlayerPos);

            // Update bullets' positions
            bullet_update(bullets, MAX_BULLETS);

            bullet_update2(bullets2, MAX_BULLETS2);

            asteroid_spawn(asteroids, MAX_ASTEROIDS, ASTEROID_HEALTH, times);

            asteroid_update(asteroids, MAX_ASTEROIDS, ASTEROID_HEALTH, times);

            asteroid_collision(asteroids, bullets, MAX_ASTEROIDS, MAX_BULLETS);

            asteroid_collision2(asteroids, bullets2, MAX_ASTEROIDS, MAX_BULLETS2);



            globalFlag.status = 0;
        }
    }
}

void shoot(int selector_value, PlayerBullet bullets[], PlayerBullet2 bullets2[], int MAX_BULLETS,int MAX_BULLETS2, uint8_t PlayerPos) {
    // Check joystick input for shooting
    if (readJoystick() == 5) { // Shoot
        if (selector_value == 1 || selector_value == 3) {
            // Use the first set of bullets (based on selector result)
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) { // Use the first inactive bullet slot
                    bullets[i].x = 3 + 1; // Start just to the right of the player
                    bullets[i].y = PlayerPos;    // Match player's vertical position
                    bullets[i].active = 1;       // Mark the bullet as active
                    break;
                }
            }
        }
        else {
            // Use the second set of bullets (based on selector result)
            for (int i = 0; i < MAX_BULLETS2; i++) {
                if (!bullets2[i].active) { // Use the first inactive bullet slot
                    bullets2[i].x = 3 + 1; // Start just to the right of the player
                    bullets2[i].y = PlayerPos;    // Match player's vertical position
                    bullets2[i].active = 1;       // Mark the bullet as active
                    break;
                }
            }
        }
    }
}



void bullet_update(PlayerBullet bullets[], int MAX_BULLETS) {
    // Update bullets' positions
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            // Erase the bullet at the current position
            movexy(bullets[i].x, bullets[i].y);
            printf(" ");

            // Move the bullet to the right
            bullets[i].x++;

            // Check if the bullet is out of bounds
            if (bullets[i].x >= 187) {
                bullets[i].active = 0; // Deactivate the bullet
            } else {
                // Draw the bullet at the new position
                movexy(bullets[i].x, bullets[i].y);
                printf("\033[35m-\033[0m");
            }
        }
    }
}

void bullet_update2(PlayerBullet2 bullets2[], int MAX_BULLETS2) {
    for (int i = 0; i < MAX_BULLETS2; i++) {
        if (bullets2[i].active) {
            // Erase the bullet at the current position
            movexy(bullets2[i].x, bullets2[i].y);
            printf(" ");

            // Move the bullet to the right
            bullets2[i].x++;

            // Check if the bullet is out of bounds
            if (bullets2[i].x >= 187) {
                bullets2[i].active = 0; // Deactivate the bullet
            } else {
                // Draw the bullet at the new position
                movexy(bullets2[i].x, bullets2[i].y);
                printf("\033[35mo\033[0m");
            }
        }
    }
}


uint8_t player_move_update(uint8_t PlayerPos, int selector_value) {
    // Check joystick input for player movement
    if ((readJoystick() == 1) && (PlayerPos != 2)) { // MOVE UP
    	if ((selector_value == 1 || selector_value == 2) && PlayerPos != 3) {
    		movexy(3, PlayerPos);
    		printf(" "); // Clear previous position
    		PlayerPos -= 2;
    		movexy(3, PlayerPos);
    		printf("\033[35m>\033[0m"); // Draw new position
    	}
    	else {
            movexy(3, PlayerPos);
            printf(" "); // Clear previous position
            PlayerPos -= 1;
            movexy(3, PlayerPos);
            printf("\033[35m>\033[0m"); // Draw new position
        	}
    	}

    if ((readJoystick() == 2) && (PlayerPos != 49)) { // MOVE DOWN
    	if ((selector_value == 1 || selector_value == 2)  && PlayerPos != 48) {
    		movexy(3, PlayerPos);
    		printf(" "); // Clear previous position
    		PlayerPos += 2;
        	movexy(3, PlayerPos);
        	printf("\033[35m>\033[0m"); // Draw new position
    	}
    	else {
    		movexy(3, PlayerPos);
    		printf(" "); // Clear previous position
    		PlayerPos += 1;
        	movexy(3, PlayerPos);
        	printf("\033[35m>\033[0m"); // Draw new position
    }
    }
    return PlayerPos;
}

void initialize_asteroids(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH) {
	 for (int i = 0; i < MAX_ASTEROIDS; i++) {
		 asteroids[i].x = 0;
		 asteroids[i].y = 0;
		 asteroids[i].j = ASTEROID_HEALTH;
		 asteroids[i].active = 0;
	 }
}

void asteroid_spawn(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH,  int time) {
	if (time % 50 == 0) {
        for (int i = 0; i < MAX_ASTEROIDS; i++) {
            if (!asteroids[i].active) { // Use the first inactive bullet slot
            	asteroids[i].x = 170; // Start just to the right of the player
            	asteroids[i].y = 8 + rand() % (44 - 8 + 1);    // Match player's vertical position
            	asteroids[i].j = ASTEROID_HEALTH;
            	asteroids[i].active = 1;       // Mark the bullet as active
                break;
            }
        }
    }
}

void asteroid_update(asteroid asteroids[], int MAX_ASTEROIDS, int ASTEROID_HEALTH, int times) {
	if (times % 20 == 0) {
		for (int i = 0; i < MAX_ASTEROIDS; i++) {
			if (asteroids[i].active) {
				// Erase the bullet at the current position
				movexy(asteroids[i].x, asteroids[i].y);
				printf(" ");

				// Move the asteroid to the left
				asteroids[i].x--;

				// Check if the asteroid is out of bounds
				if (asteroids[i].x <= 4) {
					asteroids[i].active = 0; // Deactivate the asteroid
				}
				else {
					// Draw the a at the new position
					movexy(asteroids[i].x, asteroids[i].y);
					printf("O");
				}
			}
		}
	}
}

void asteroid_collision(asteroid asteroids[], PlayerBullet bullets[], int MAX_ASTEROIDS, int MAX_BULLETS) {
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		for (int k = 0; k < MAX_BULLETS; k++) {

			if ((asteroids[i].x == bullets[k].x + 1) && (asteroids[i].y == bullets[k].y)) {


				bullets[k].active = 0;
				asteroids[i].j--;

			}

			if (asteroids[i].j == 0) {
				asteroids[i].active = 0;
				movexy(asteroids[i].x,asteroids[i].y);
				printf(" ");
				movexy(asteroids[i].x-1,asteroids[i].y);
				printf(" ");
				movexy(asteroids[i].x-2,asteroids[i].y);
				printf(" ");
				movexy(asteroids[i].x-3,asteroids[i].y);
				printf(" ");
				movexy(asteroids[i].x-4,asteroids[i].y);
				printf(" ");
			}
		}
	}
}

void asteroid_collision2(asteroid asteroids[], PlayerBullet2 bullets2[], int MAX_ASTEROIDS, int MAX_BULLETS2) {
	for (int i = 0; i < MAX_ASTEROIDS; i++) {
		for (int k = 0; k < MAX_BULLETS2; k++) {
			if ((asteroids[i].x == bullets2[k].x + 2) && (asteroids[i].y == bullets2[k].y)) {

				bullets2[k].active = 0;
			}
			if ((asteroids[i].x == bullets2[k].x + 1) && (asteroids[i].y == bullets2[k].y)) {


				bullets2[k].active = 0;

				asteroids[i].j--;
			}
			if ((asteroids[i].x == bullets2[k].x) && (asteroids[i].y == bullets2[k].y)) {

				bullets2[k].active = 0;
			}
			if (asteroids[i].j == 0) {
				asteroids[i].active = 0;
				movexy(asteroids[i].x,asteroids[i].y);
				printf(" ");
			}
		}
	}
}



typedef struct {
    int x;          // x location
    int y;          // y location
    int health;     // health of the asteroid
    int active;     // 0 for inactive, 1 for active
} Asteroid;

void lcd_write_string(char string[], int location) {
	uint8_t buffer[512];
	memset(buffer, 0x00, 512);
		for (int i = 0; string[i] != '\0'; i++){
		buffer[location + i*5 + 0] = (character_data[(int)string[i]-32][0]);
		buffer[location + i*5 + 1] = (character_data[(int)string[i]-32][1]);
		buffer[location + i*5 + 2] = (character_data[(int)string[i]-32][2]);
		buffer[location + i*5 + 3] = (character_data[(int)string[i]-32][3]);
		buffer[location + i*5 + 4] = (character_data[(int)string[i]-32][4]);
	}
	lcd_push_buffer(buffer);
}






void draw_boss_sprite() {

	// function for drawing boss sprite

	/*
	 * array containing the color of each ASCII character
	 * index[y][x] is the color of the character at terminal position -
	 * (row : 2 + y, column : 160 + x)
	 * */

	uint16_t boss_sprite[][25] = {
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0}, /* row 1 */
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,8,8,8,8, 8,0,0,0,0}, /* row 2 */
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,8,8, 8,8,8,8,8, 8,0,0,0,0}, /* row 3 */
		{0,0,0,0,0, 0,0,0,0,0, 8,8,8,8,8, 8,8,8,8,8, 8,0,0,0,0}, /* row 4 */
		{0,0,0,0,0, 0,0,0,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,0,0}, /* row 5 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,3,0,8,0}, /* row 6 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 1,1,3,3,0}, /* row 7 */
		{0,0,0,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 5,5,1,1,3}, /* row 8 */
		{0,0,1,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 5,5,1,1,3}, /* row 9 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 1,1,3,3,0}, /* row 10 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,3,0,8,0}, /* row 11 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,0,0}, /* row 12 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,3,0,8,0}, /* row 13 */
		{0,0,0,0,0, 0,0,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 1,1,3,3,0}, /* row 14 */
		{0,0,0,8,8, 8,8,8,8,8, 8,7,8,7,8, 7,8,7,8,8, 5,5,1,1,3}, /* row 15 */
		{0,0,1,8,8, 8,8,8,8,8, 7,8,7,8,7, 8,7,8,7,8, 5,5,1,1,3}, /* row 16 */
		{0,0,0,0,0, 0,8,8,8,7, 8,8,8,8,8, 8,8,8,8,8, 1,1,3,3,0}, /* row 17 */
		{0,0,0,0,0, 0,8,8,7,8, 8,8,8,8,8, 8,8,8,8,8, 8,3,0,8,0}, /* row 18 */
		{0,0,0,0,0, 0,8,7,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,0,0}, /* row 19 */
		{0,0,0,0,8, 8,8,7,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,0,0,0,0}, /* row 20 */
		{0,0,0,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,8,8,8,8, 8,0,0,0,0}, /* row 21 */
		{0,0,8,8,8, 6,6,6,6,6, 8,8,8,8,8, 8,8,8,8,8, 0,0,0,0,0}, /* row 22 */
		{0,8,8,6,6, 6,6,6,6,6, 6,8,8,8,8, 8,0,0,0,0, 0,0,0,0,0}, /* row 23 */
		{0,8,8,6,6, 6,6,6,6,6, 6,8,8,8,8, 8,0,0,0,0, 0,0,0,0,0}, /* row 24 */
		};

		uint8_t current_row = 0;
		uint8_t current_column = 0;

		/*
		 * drawing top half of sprite
		 */

		for (current_row = 0; current_row <= 23; current_row++) {
			for (current_column = 0; current_column <= 24; current_column++) {
				movexy(160 + current_column, 2 + current_row);
				fgcolor(boss_sprite[current_row][current_column]);
				printf("%c", 219);
			}
		}

		/*
		 * drawing bottom half of sprite by going through array in reverse
		 */

		for (current_row = 23; current_row > 0; current_row--) {
			for (current_column = 0; current_column <= 24; current_column++) {
				movexy(160 + current_column, 3 + 45 - current_row);
				fgcolor(boss_sprite[current_row][current_column]);
				printf("%c", 219);
			}
		}
}


