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
	{0,8,8,6,6, 6,6,6,6,6, 6,8,8,8,8, 8,8,8,0,0, 0,0,0,0,0}, /* row 23 */
	{0,8,8,6,6, 6,6,6,6,6, 6,8,8,8,8, 8,8,0,0,0, 0,0,0,0,0}, /* row 24 */
	};

	uint8_t current_row = 0;
	uint8_t current_column = 0;

	/*
	* drawing the top half of the sprite
	*/

	for (current_row = 0; current_row <= 23; current_row++) {
		for (current_column = 0; current_column <= 24; current_column++) {
			gotoxy(160 + current_column, 2 + current_row);
			fgcolor(boss_sprite[current_row][current_column]);
			printf("%c", 219);
		}
	}

	/*
	 * drawing the bottom half of the sprite by going through the array in reverse
	 */

	for (current_row = 23; current_row > 0; current_row--) {
		for (current_column = 0; current_column <= 24; current_column++) {
			gotoxy(160 + current_column, 4 + 45 - current_row);
			fgcolor(boss_sprite[current_row][current_column]);
			printf("%c", 219);
		}
	}
