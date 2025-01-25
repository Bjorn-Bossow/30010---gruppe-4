void draw_station_sprite() {
	uint8_t station_sprite[][16] = {
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, // row 0
	{0,0,7,9, 7,0,8,8, 8,0,0,0, 8,0,0,0}, // row 0
	{0,0,7,9, 7,0,8,8, 8,8,8,8, 8,8,8,0}, // row 1
	{0,0,7,9, 7,0,8,8, 8,8,8,8, 8,8,8,0}, // row 2
	{0,0,7,9, 7,0,8,8, 8,8,8,8, 8,8,8,0}, // row 3
	{0,0,7,9, 7,0,8,8, 8,0,0,0, 8,0,0,0}, // row 4
	{0,0,0,10, 0,0,8,8, 8,0,0,8, 8,8,0,0}, // row 5
	{0,8,8,8, 8,8,8,8, 8,0,0,8, 1,8,0,0}, // row 6
	{0,8,8,8, 8,8,8,8, 8,0,0,8, 8,8,0,0}, // row 7
	{0,0,0,10, 0,0,8,8, 8,0,0,8, 1,8,0,0}, // row 8
	{0,0,7,9, 7,0,8,8, 8,0,0,8, 8,8,0,0}, // row 9
	{0,0,7,9, 7,0,8,8, 8,0,0,8, 1,8,0,0}, // row 10
	{0,0,7,9, 7,0,8,8, 8,0,0,8, 8,8,0,0}, // row 11
	{0,0,7,9, 7,0,8,8, 8,0,0,8, 1,8,0,0}, // row 12
	{0,0,7,9, 7,0,8,8, 8,0,0,8, 8,8,0,0}, // row 13
	{0,0,0,0, 0,0,8,8, 8,0,0,0, 0,0,0,0}, // row 14
	{0,0,0,0, 0,0,0,8, 0,0,0,0, 0,0,0,0}, // row 15
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 16
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 17
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 18
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 19
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 20
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 21
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 7,7,7,0}, // row 22
	{0,0,0,0, 0,8,8,8, 8,8,0,7, 7,7,7,0}, // row 23
	{0,0,0,0, 0,8,8,8, 8,8,8,7, 6,7,7,0}, // row 24
	{0,0,0,0, 0,8,8,8, 8,8,8,7, 7,7,7,0}, // row 25
	{0,0,0,0, 0,8,8,8, 8,8,8,7, 6,7,7,0}, // row 26
	{0,0,0,0, 0,8,8,8, 8,8,0,7, 7,7,7,0}, // row 27
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 7,7,7,0}, // row 28
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 29
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 30
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 31
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 32
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 33
	{0,0,0,0, 0,8,8,8, 8,8,0,0, 0,0,0,0}, // row 34
	{0,0,0,0, 0,0,0,8, 0,0,0,0, 0,0,0,0}, // row 35
	{0,0,0,0, 0,0,8,8, 8,0,0,0, 0,0,0,0}, // row 36
	{0,0,0,0, 0,0,8,8, 8,0,0,0, 0,0,0,0}, // row 37
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 38
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 39
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 40
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 41
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 42
	{0,0,0,10, 0,0,8,8, 8,0,0,10, 0,0,0,0}, // row 43
	{0,8,8,8, 8,8,8,8, 8,8,8,8, 8,8,0,0}, // row 44
	{0,8,8,8, 8,8,8,8, 8,8,8,8, 8,8,0,0}, // row 45
	{0,0,0,10, 0,0,8,8, 8,0,0,10, 0,0,0,0}, // row 46
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 47
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 48
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 49
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 50
	{0,0,4,9, 4,0,8,8, 8,0,4,9, 4,0,0,0}, // row 52
	};

	uint8_t current_row = 0;
	uint8_t current_column = 0;

	for (current_row = 0; current_row <= 52; current_row++) {
		for (current_column = 0; current_column <= 15; current_column++) {
			movexy(6 + current_row, 50 - 17 + current_column);
			if (station_sprite[current_row][current_column] < 9) {
			fgcolor(station_sprite[current_row][current_column]);
			printf("%c", 219);
			} else if (station_sprite[current_row][current_column] == 9) {
			fgcolor(8);
			printf("%c", 206);
			} else if (station_sprite[current_row][current_column] == 10) {
			fgcolor(8);
			printf("%c", 205);
			}
		}
	}

}

void station_fuel_unload(uint16_t counter) {
	if ((counter % 10) == 3) {
		gotoxy(6, 45);
		fgcolor(7);
		printf("%c", 205);
	}
	if (counter == 4) {
		gotoxy(5, 45);
		fgcolor(7);
		printf("%c", 205);
	}
	if (counter == 5) {
		gotoxy(19, 45);
		fgcolor(7);
		printf("%c", 219);

		gotoxy(5, 45);
		fgcolor(1);
		printf("%c", 205);

		gotoxy(6, 45);
		fgcolor(1);
		printf("%c", 205);
	}
	if (counter== 6) {
		gotoxy(17, 45);
		fgcolor(7);
		printf("%c", 219);
	}
	if (counter== 7) {
		gotoxy(15, 45);
		fgcolor(7);
		printf("%c", 219);
	}
	if (counter== 8) {
		gotoxy(13, 45);
		fgcolor(7);
		printf("%c", 219);

		gotoxy(5, 45);
		fgcolor(7);
		printf("%c", 205);

		gotoxy(6, 45);
		fgcolor(7);
		printf("%c", 205);
	}
	if (counter == 9) {
		gotoxy(5, 45);
		printf("%c", 32);
	}
	if (counter== 10) {
		gotoxy(6, 45);
		printf("%c", 32);
		}
}

void station_wipe() {
	uint8_t x = 0;
	uint8_t y = 0;

	for (x = 0; x <= 52; x++) {
		for (y = 0; y <= 15; y++) {
			movexy(6 + x, 50 - 17 + y);
			printf("%c", 32);
			}
	}
}


void check_player_pos(uint8_t PlayerPos) {
	// checks the players position, if player is at station, then initialize docking
	static uint16_t counter = 0;
	static uint16_t counter2 = 0;

	if (!counter2) {
	printf("\e[?25l");

	if (!counter) {
	draw_station_sprite();
	counter++;
	}
	if (PlayerPos == 45 & (counter2 == 0)) {
	gotoxy(90, 25);
	printf("                                        \n");
	while(1) {
	if (globalFlag.status == 1) {
		counter++;
		if ((counter % 20) == 0) {
			counter2++;
		}
		globalFlag.status = 0;
	}
	gotoxy(5,5);
	printf("%d", counter2);

	station_fuel_unload(counter2);
	if (counter2 == 11) {
		station_wipe();
		printf("\e[?25h");
		break;
	  }
	 }
	} else {
	fgcolor(15);
	gotoxy(80, 10);
	printf("Dock to station to proceed to next stage\n");
	}
	}
}
