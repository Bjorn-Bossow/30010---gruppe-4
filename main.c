#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#include "clut.h"
#include "ansi.h"
#include "game.h"
#include "lcd.h"
#include "menu.h"
#include "stm32f30x_rcc.h"
#include "assert.h"
#include "charset.h"

int main(void) {
	uart_init(115200);
	clrscr();
	timerdisplay2();

	menu();

//	border();
//	player();

	while (1) {}
}

//	setLED(0,1,0);
//
//	while (1) {
//	clrscr();
//	gotoxy();
//	if (readJoystick() == 0) {
//		printf("no button pressed");
//	}
//	if (readJoystick() == 1) {
//		printf("UP being pressed");
//		}
//	if (readJoystick() == 2) {
//		printf("DOWN being pressed");
//		}
//	if (readJoystick() == 3) {
//		printf("LEFT being pressed");
//		}
//	if (readJoystick() == 4) {
//		printf("RIGHT being pressed");
//		}
//	if (readJoystick() == 5) {
//		printf("CENTER being pressed");
//	}
//}



//	ballwindow(2,2,75,30);
//
//	gotoxy();
//
//	float x = 15.0, y = 15.0;
//	float velx = 1, vely = 0.4;
//
//	while (1) {
//		ballpos(&x, &y, velx, vely);
//		ball(x, y);
