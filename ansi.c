/*
 * ansi.c
 *
 *  Created on: 6. jan. 2025
 *      Author: frikk
 */
#include "ansi.h"
#include "stdint.h"
#include"stdio.h"
#include "string.h"
#include "30010_io.h"
#include "charset.h"
#define ESC 0x1B

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
	printf("%c[2J",ESC);
}

void clreol() {
	printf("%c[2K",ESC);
}






void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char *string, int style) {

	if (style == 1) {
		int lengths = strlen(&string); //COMMAND TO FIND LENGTH OF STRING
		int i;
		int len = 0;
		uint8_t TL = 218;

		printf("%c[%d;%dH",ESC,y1,x1); //TOPLEFT
		printf("%c",TL);
		printf("%c",180);

		while (string[len] != '\0') {
			printf("%c",string[len]);
			len++;
		}

		printf("%c",195);

		for (i=5+len; i <= x2; i++) {
			printf("%c",45);
		}

		printf("%c",191); //TOPRIGHT

		for (int j = y1 + 1-lengths; j <= y2; j++) {     //SIDEBARS

			printf("%c[%d;%dH",ESC,j,x1);
			printf("%c",179);

			printf("%c[%d;%dH",ESC,j,x2);
			printf("%c",179);
		}

		printf("%c[%d;%dH",ESC,y2,x1);
		printf("%c",192);
		for (i=x1 + 2; i <= x2+lengths; i++) {
			printf("%c",45);
			}
			printf("%c",217);
		}
	}

void ballwindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int i;
	int h = 0;
	uint8_t TL = 218;
	uint8_t TR = 191;
	uint8_t BL = 192;
	uint8_t BR = 217;
	uint8_t HorzLine = 196;
	uint8_t VertLine = 179;

	printf("%c[%d;%dH",ESC,y1,x1); //TOPLEFT
	printf("%c",TL);

	for (i=x1+1; i < x2; i++) {
		printf("%c",HorzLine);
	}

	printf("%c",TR); //TOPRIGHT

	for (int j = y1 + 1; j < y2; j++) {     //SIDEBARS

		printf("%c[%d;%dH",ESC,j,x1);
		printf("%c",VertLine);

		printf("%c[%d;%dH",ESC,j,x2);
		printf("%c",VertLine);

	}
	printf("%c[%d;%dH",ESC,y2,x1);

	printf("%c",BL);

	for (i=x1 + 1; i < x2; i++) {
		printf("%c",HorzLine);
	}
	printf("%c",BR);


	//MIDDLE

	int8_t xx1 = x2/2 - 3;
	int8_t yy1 = y2/2 - 1;
	int8_t xx2 = xx1 + 7;
	int8_t yy2 = yy1 + 2;


	printf("%c[%d;%dH",ESC,yy1,xx1);
	printf("%c",TL); //TL CNR

	for (int j = 0; j < (xx2 - xx1 - 1); j++) { //MIDDLE TOP
		printf("%c",HorzLine);
		}
	printf("%c",TR);

	for (int j = yy1+1; j < yy2; j++) {

		printf("%c[%d;%dH",ESC,j,xx1);
		printf("%c",VertLine);

		printf("%c[%d;%dH",ESC,j,xx2);
		printf("%c",VertLine);
	}

	printf("%c[%d;%dH",ESC,yy2,xx2);
	printf("%c",BR);

	printf("%c[%d;%dH",ESC,yy2,xx1);
	printf("%c",BL);

	for (int j = 0; j < (xx2 - xx1 - 1); j++) { //MIDDLE TOP
		printf("%c",HorzLine);
		}

	printf("%c[%d;%dH",ESC,yy1+1,xx1+1);
	printf("Hits:%d",h); //h is a placeholder for hits here

}

int8_t readJoystick() {
	uint16_t val;

	// UP
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	// Set pin PA4 to input
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |=  (0x00000000 << (4 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |=  (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)


	if (val = ((GPIOA->IDR) & (0x0001 << 4))) {
		return (1);
	}

	// DOWN

	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

	// Set pin PB0 to input
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)


	if (val = ((GPIOB->IDR) & (0x0001 << 0))) {
		return (2);
	}

	// LEFT

	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port B

	// Set pin PC1 to input
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |=  (0x00000000 << (1 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |=  (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)


	if (val = ((GPIOC->IDR) & (0x0001 << 1))) {
		return (3);
		}

	// RIGHT

	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port B

	// Set pin PC0 to input
	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)


	if (val = ((GPIOC->IDR) & (0x0001 << 0))) {
		return (4);
		}

	// CENTER

	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

	// Set pin PB5 to input
	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |=  (0x00000000 << (5 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |=  (0x00000002 << (5	 * 2)); // Set push/pull register (0x00 -No pull, 0x01 -Pull-up, 0x02 -Pull-down)


	if (val = ((GPIOB->IDR) & (0x0001 << 5))) {
		return (5);
	}
}


void setLED(int R, int G, int B) {


	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port A

	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
	GPIOB->OSPEEDR |=  (0x00000002 << (4 * 2)); // set speed register (0x01 -10 MHz, 0x02 -2 MHz, 0x03 -50 MHz)
	GPIOB->OTYPER &= ~(0x0001 << (4 * 1)); // Clear output type register
	GPIOB->OTYPER |=  (0x0000 << (4)); // Set output type register (0x00 -Push pull, 0x01 -Open drain)
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |=  (0x00000001 << (4 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)

	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port A

	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
	GPIOC->OSPEEDR |=  (0x00000002 << (7 * 2)); // set speed register (0x01 -10 MHz, 0x02 -2 MHz, 0x03 -50 MHz)
	GPIOC->OTYPER &= ~(0x0001 << (7 * 1)); // Clear output type register
	GPIOC->OTYPER |=  (0x0000 << (7)); // Set output type register (0x00 -Push pull, 0x01 -Open drain)
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |=  (0x00000001 << (7 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
	GPIOA->OSPEEDR |=  (0x00000002 << (9 * 2)); // set speed register (0x01 -10 MHz, 0x02 -2 MHz, 0x03 -50 MHz)
	GPIOA->OTYPER &= ~(0x0001 << (9 * 1)); // Clear output type register
	GPIOA->OTYPER |=  (0x0000 << (9)); // Set output type register (0x00 -Push pull, 0x01 -Open drain)
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |=  (0x00000001 << (9 * 2)); // Set mode register (0x00 –Input, 0x01 -Output, 0x02 -Alternate Function, 0x03 -Analog in/out)

	GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to LOW
	GPIOC->ODR |= (0x0001 << 7); //Set pin PB4 to LOW
	GPIOA->ODR |= (0x0001 << 9); //Set pin PB4 to LOW

	if (R == 1) {
		GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to LOW
	}


	if (G == 1) {
		GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to LOW
	}


	if (B == 1) {
		GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to LOW
	}




}




void graphicss() {
	uint8_t buffer[512];
	memset(buffer,0xAA,512); // set each element of the buffer to 0xAA
	lcd_init(); //Start screen
	lcd_push_buffer(buffer); //Transmit byte array
}


//void lcd_write_string(char string[], int location) {
//    lcd_init();
//    uint8_t buffer[512];
//    memset(buffer, 0x00, 512);
//        for (int i = 0; string[i] != '\0'; i++){
//        buffer[location + i*5 + 0] = (character_data[(int)string[i]-32][0]);
//        buffer[location + i*5 + 1] = (character_data[(int)string[i]-32][1]);
//        buffer[location + i*5 + 2] = (character_data[(int)string[i]-32][2]);
//        buffer[location + i*5 + 3] = (character_data[(int)string[i]-32][3]);
//        buffer[location + i*5 + 4] = (character_data[(int)string[i]-32][4]);
//    }
//    lcd_push_buffer(buffer);
//}



//void underline() {
//	printf("%c[4m",ESC);
//}
//
//void underlineOFF() {
//	printf("%c[24m",ESC);
//}
//
//
//void blink() {
//	printf("%c[5m",ESC);
//}
//
//void blinkOFF() {
//	printf("%c[25m",ESC);
//}
//
//void inverse() {
//	printf("%c[7m",ESC);
//}
//
//void inverseOFF() {
//	printf("%c[27m",ESC);
//}

