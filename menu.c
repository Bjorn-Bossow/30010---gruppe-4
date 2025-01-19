#define ESC 0x1B
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "string.h"
#include "stdio.h"
#include "charset.h"
#include "Rumspil.h"

void menu() {
	float x1 = 1, x2 = 177, y1 = 1, y2 = 61;
	int bredde = 10;
	int hojde = 5;
	resetbgcolor();
		clrscr();
		gotoxy(x1,y1);

		printf("%c", corner1);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
				printf("%c", horisontal);
			}

		printf("%c", corner2);

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x1,i);

				printf("%c", vertical);
					}

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x2,i);

				printf("%c", vertical);
						}
		gotoxy(x2, y2);
			printf("%c", corner3);

		gotoxy(x1, y2);
			printf("%c", corner4);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
			printf("%c", horisontal);
		}




		int8_t xx1 = x2/2 -5;
		int8_t yy1 = y2/2 -1;

		int8_t xx2 = xx1 + bredde -1;
		int8_t yy2 = yy1 + hojde - 1;


		gotoxy(xx1, yy1);

		printf("%c", corner1);

		for (int i = 0; i < (xx2 - xx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yy1+1; i < yy2; i++) {

				gotoxy(xx1,i);

				printf("%c", vertical);
			}

		for (int i = yy1+1; i < yy2; i++) {

				gotoxy(xx2,i);

				printf("%c", vertical);
			}

		gotoxy(xx2, yy2);
		printf("%c", corner3);

		gotoxy(xx1, yy2);
		printf("%c", corner4);


		for (int i = 0; i < (xx2 - xx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xx1+1,yy1+1);
		printf("Play");


		int8_t xxx1 = (xx1 - 15);
		int8_t yyy1 = yy1;

		int8_t xxx2 = xxx1 + bredde -1;
		int8_t yyy2 = yyy1 + hojde -1;


		gotoxy(xxx1, yyy1);

		printf("%c", corner1);

		for (int i = 0; i < (xxx2 - xxx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yyy1+1; i < yyy2; i++) {

				gotoxy(xxx1,i);

				printf("%c", vertical);
			}

		for (int i = yyy1+1; i < yyy2; i++) {

				gotoxy(xxx2,i);

				printf("%c", vertical);
			}

		gotoxy(xxx2, yyy2);
		printf("%c", corner3);

		gotoxy(xxx1, yyy2);
		printf("%c", corner4);


		for (int i = 0; i < (xxx2 - xxx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xxx1+1,yyy1+1);
		printf("Help");

		int8_t xxxx1 = (xx1 + 15);
		int8_t yyyy1 = yy1;

		int8_t xxxx2 = xxxx1 + bredde -1;
		int8_t yyyy2 = yyyy1 + hojde -1;


		gotoxy(xxxx1, yyyy1);

		printf("%c", corner1);

		for (int i = 0; i < (xxxx2 - xxxx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yyyy1+1; i < yyyy2; i++) {

				gotoxy(xxxx1,i);

				printf("%c", vertical);
			}

		for (int i = yyyy1+1; i < yyyy2; i++) {

				gotoxy(xxxx2,i);

				printf("%c", vertical);
			}

		gotoxy(xxxx2, yyyy2);
		printf("%c", corner3);

		gotoxy(xxxx1, yyyy2);
		printf("%c", corner4);


		for (int i = 0; i < (xxxx2 - xxxx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xxxx1+1,yyyy1+1);
		printf("Quit");

		int8_t StatePos = 0;
		gotoxy(xx1+1, yy1+1);
		while(1) {
			RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

		    // Set pin PC1 to input
		    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
		    GPIOC->MODER |=  (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
		    GPIOC->PUPDR |=  (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t left = GPIOC->IDR & (0x0001 << 1); //Read from pin PC1



			RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

		    // Set pin PC0 to input
		    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
		    GPIOC->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
		    GPIOC->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t right = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

			RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

		    // Set pin PA4 to input
		    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
		    GPIOA->MODER |=  (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
		    GPIOA->PUPDR |=  (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t up = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

		    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

		    // Set pin PB5 to input
		    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
		    GPIOB->MODER |=  (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
		    GPIOB->PUPDR |=  (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t center = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5



		    if(StatePos == 0){
		    	if(right >= 1){
		    		gotoxy(xxxx1+1,yyyy1+1);
		    		StatePos = 2;
		    	}
		    	else if(left >= 1){
		    		gotoxy(xxx1+1, yyy1+1);
		    		StatePos = 1;
		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}
		    	else {
		    		StatePos = 0;
		    	}
		    }
		    else if(StatePos == 1){
		    	if(right >= 1){
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;

		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}

		    }

		    else if(StatePos == 2){
		    	if(left >= 1) {
		    		gotoxy(xx1+1, yy1+1);
		    		StatePos = 0;

		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}
		    }


		    if(center >= 1 && StatePos == 0) {
		    	difficulty_select();
		    }
		    if(center >= 1 && StatePos == 1) {
		    	help_screen();
		    }
		    if(center >= 1 && StatePos == 2) {
		    	clrscr();
		    	break;
		    }

		}

}

void difficulty_select() {
	float x1 = 1, x2 = 177, y1 = 1, y2 = 61;
	int bredde = 10;
	int hojde = 5;
	resetbgcolor();
		clrscr();
		gotoxy(x1,y1);

		printf("%c", corner1);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
				printf("%c", horisontal);
			}

		printf("%c", corner2);

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x1,i);

				printf("%c", vertical);
					}

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x2,i);

				printf("%c", vertical);
						}
		gotoxy(x2, y2);
			printf("%c", corner3);

		gotoxy(x1, y2);
			printf("%c", corner4);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
			printf("%c", horisontal);
		}




		int8_t xx1 = x2/2 -5;
		int8_t yy1 = y2/2 -1;

		int8_t xx2 = xx1 + bredde -1;
		int8_t yy2 = yy1 + hojde - 1;


		gotoxy(xx1, yy1);

		printf("%c", corner1);

		for (int i = 0; i < (xx2 - xx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yy1+1; i < yy2; i++) {

				gotoxy(xx1,i);

				printf("%c", vertical);
			}

		for (int i = yy1+1; i < yy2; i++) {

				gotoxy(xx2,i);

				printf("%c", vertical);
			}

		gotoxy(xx2, yy2);
		printf("%c", corner3);

		gotoxy(xx1, yy2);
		printf("%c", corner4);


		for (int i = 0; i < (xx2 - xx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xx1+1,yy1+1);
		printf("Medium");


		int8_t xxx1 = (xx1 - 15);
		int8_t yyy1 = yy1;

		int8_t xxx2 = xxx1 + bredde -1;
		int8_t yyy2 = yyy1 + hojde -1;


		gotoxy(xxx1, yyy1);

		printf("%c", corner1);

		for (int i = 0; i < (xxx2 - xxx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yyy1+1; i < yyy2; i++) {

				gotoxy(xxx1,i);

				printf("%c", vertical);
			}

		for (int i = yyy1+1; i < yyy2; i++) {

				gotoxy(xxx2,i);

				printf("%c", vertical);
			}

		gotoxy(xxx2, yyy2);
		printf("%c", corner3);

		gotoxy(xxx1, yyy2);
		printf("%c", corner4);


		for (int i = 0; i < (xxx2 - xxx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xxx1+1,yyy1+1);
		printf("Easy");

		int8_t xxxx1 = (xx1 + 15);
		int8_t yyyy1 = yy1;

		int8_t xxxx2 = xxxx1 + bredde -1;
		int8_t yyyy2 = yyyy1 + hojde -1;


		gotoxy(xxxx1, yyyy1);

		printf("%c", corner1);

		for (int i = 0; i < (xxxx2 - xxxx1 - 1); i++) {
				printf("%c", horisontal);

		}

		printf("%c", corner2);

		for (int i = yyyy1+1; i < yyyy2; i++) {

				gotoxy(xxxx1,i);

				printf("%c", vertical);
			}

		for (int i = yyyy1+1; i < yyyy2; i++) {

				gotoxy(xxxx2,i);

				printf("%c", vertical);
			}

		gotoxy(xxxx2, yyyy2);
		printf("%c", corner3);

		gotoxy(xxxx1, yyyy2);
		printf("%c", corner4);


		for (int i = 0; i < (xxxx2 - xxxx1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(xxxx1+1,yyyy1+1);
		printf("HARD");
		int8_t StatePos = 0;

		while(1) {
			RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

		    // Set pin PC1 to input
		    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
		    GPIOC->MODER |=  (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
		    GPIOC->PUPDR |=  (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t left = GPIOC->IDR & (0x0001 << 1); //Read from pin PC1



			RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

		    // Set pin PC0 to input
		    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
		    GPIOC->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
		    GPIOC->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t right = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

			RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

		    // Set pin PA4 to input
		    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
		    GPIOA->MODER |=  (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
		    GPIOA->PUPDR |=  (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t up = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

		    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

		    // Set pin PB5 to input

		    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
		    GPIOB->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
		    GPIOB->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t down = GPIOB->IDR & (0x0001 << 0); //Read from pin PB0

		    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

		    // Set pin PB5 to input
		    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
		    GPIOB->MODER |=  (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
		    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
		    GPIOB->PUPDR |=  (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

		    uint16_t center = GPIOB->IDR & (0x0001 << 5); //Read from pin PB5

		    if(StatePos == 0){
		    	if(right >= 1){
		    		gotoxy(xxxx1+1,yyyy1+1);
		    		StatePos = 2;
		    	}
		    	else if(left >= 1){
		    		gotoxy(xxx1+1, yyy1+1);
		    		StatePos = 1;
		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}
		    	else {
		    		StatePos = 0;
		    	}
		    }
		    else if(StatePos == 1){
		    	if(right >= 1){
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;

		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}

		    }

		    else if(StatePos == 2){
		    	if(left >= 1) {
		    		gotoxy(xx1+1, yy1+1);
		    		StatePos = 0;

		    	}
		    	else if(up >= 1) {
		    		gotoxy(xx1+1,yy1+1);
		    		StatePos = 0;
		    	}
		    }

		    if(down) {
		    	menu();
		    }

		    if(StatePos == 1 && center >= 1) {
		    	clrscr();
		    	border();
		    	player_movement();
		    }
		}
}

void help_screen() {
	float x1 = 1, x2 = 177, y1 = 1, y2 = 61;

	resetbgcolor();
		clrscr();
		gotoxy(x1,y1);

		printf("%c", corner1);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
				printf("%c", horisontal);
			}

		printf("%c", corner2);

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x1,i);

				printf("%c", vertical);
					}

		for (int i = y1+1; i < y2; i++) {

				gotoxy(x2,i);

				printf("%c", vertical);
						}
		gotoxy(x2, y2);
			printf("%c", corner3);

		gotoxy(x1, y2);
			printf("%c", corner4);

		for (int i = 0; i < (x2 - x1 - 1); i++) {
			printf("%c", horisontal);
		}

		gotoxy(x2/2, y2/2);
		printf("Info");
		while(1) {
	    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	    GPIOB->MODER |=  (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	    GPIOB->PUPDR |=  (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -   No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	    uint16_t down = GPIOB->IDR & (0x0001 << 0); //Read from pin PB0

		if(down >= 1) {
			menu();
		}
		}
}

