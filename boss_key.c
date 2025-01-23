#define ESC 0x1B
#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"


//Draw a simple window
void draw_window(int x, int y, int width, int height) {
    int i, j;

    //Top border
    gotoxy(x, y);
    printf("%c", 201);
    for (i = 0; i < width - 2; i++) {
        printf("%c", 205); //Top line
    }
    printf("%c", 187); //Top right corner symbol

    //Left and right borders
    for (j = 1; j < height - 1; j++) {
        gotoxy(x, y + j);
        printf("%c", 186);// sidebar symbol
        for (i = 0; i < width - 2; i++) {  //Space between sidebars
            printf(" ");
        }
        printf("%c", 186); // Sidebar symbol
    }

    //Bottom border
    gotoxy(x, y + height - 1);
    printf("%c", 200); // Bottom right corner symbol
    for (i = 0; i < width - 2; i++) {
        printf("%c", 205); //Bottom line symbol
    }
    printf("%c", 188); //Bottom left corner symbol
}

// Function to display text inside the window
void display_text_in_window(int x, int y, const char *text) {
    gotoxy(x, y);
    printf("%s", text);
}

//Spreadsheet window
void spreadsheet(int x, int y, int width, int height, int fg, int bg) {
	int i, j;
	//Arry of names
	char names[19][5] = {
			"John","Aria","Ezra","Evan","Luca","Theo","Isla","Pia","H.C.","Levi","Beau",
			"Maya","Leon","Lily","Nora","Cora","Rhys","Noah","Nick"
			};
	//Array of labels for fake options
	char labels[12][7] = {"File","Edit","Insert","Format","Data","Tools",
			"Search","Undo","Cancel","Print","Zoom","Font"
				};
	//Arry of work variables
	char work_stats[5][5] = {"Name", "Time","Gain","Work","PPTT"};

	//Spreadsheet limitations
	if (1 <= x && x <= 188 && // X must be between 1 and 188
	    1 <= y && y <= 50 && //  Y must be between 1 and 188
	    50 <= width && width <= 188 && // width must be between 50 and 188
	    20 <= height && height <= 50 && // height must be between 20 and 50
	    (x + width) <= 189 && // x + width must be <= 189
	    (y + height) <= 51 && // y + height must be <= 51
	    0 <= fg && fg <= 8) { // fg must be between 0 and 8

		//"Naked" window
		color(fg, bg);
		draw_window (x, y, width, height);
		display_text_in_window(x + width / 2 - 12, y, "Productivity spreadsheet");

		//Horizontal lines
		for (j = 0; j < height - 7; j += 2) { //number of horizontal lines
			gotoxy(x + 1, j + y + 6);

			for (i = 1; i < width - 1; i++){
				if (i % ((width) / 6) == 0) {
					printf("%c", 197); //Spreadsheet + symbol

					}
				else {
					printf("%c", 196);  //Spreadsheet - symbol
				}
			}
		}
		//Vertical lines: 5 columns
		if (width % 6 <= 1){
			for (j = 0; j < 5; j++) {
					for (i = 0; i < (height - 8); i += 2){
						gotoxy(x + width / 6 + (width / 6) * j, y + i + 7);
						printf("%c", 179); // Vertical line |
					}
		}
	}
		//Vertical lines: 6 columns
		else {
			for (j = 0; j < 6; j++) {
						for (i = 0; i < (height - 8); i += 2){
							gotoxy(x + width / 6 + (width / 6) * j, y + i + 7);
							printf("%c", 179);
						}
			}
		}
		for (i = 0 ; i < 5; i++){ //Alphabet-coordinate-søjle
			gotoxy(x + width / 12 + (i + 1) * (width / 6), y + 7);
				printf("%c", 65 + i); //alphabet
		}
		for (i = 0; i < (height - 9) / 2; i++){ //Number-coordinate-row
			gotoxy(x + width / 12, y + 9 + i * 2);
			printf("%d",i + 1);
		}
		for (i = 0; i < 6 ; i++ ){   //Fake options top print
			gotoxy(x + width / 12 + i * (width / 6) - strlen(labels[i + 6]) / 2, y + 3);
			printf("%c%s%c", 174, labels[i], 175);
		}

		for (i = 0; i < 6; i++){   //Fake options bottom print
			gotoxy(x + width / 12 + i * (width / 6) - strlen(labels[i + 6]) / 2, y + 5);
				printf("%s", labels[i + 6]);
		}
		srand(time(NULL)); // Initialize random number generator
		for (i = 0; i < (height - 11)/2; i++) {

			for (j = 0; j < 4; j++) {   //contents of spreadsheet
				int randNum = (rand() % 900) + 100; // Generate a random 3-digit number
			    gotoxy(x + width / 12 + (j + 2) * (width / 6)-1, y + i * 2 + 11);
				printf("%d", randNum); // Print the random number
		        }
		}
		for (i = 0; i < 5; i++){           // Print work_stats (row: 1)
			gotoxy(x + width / 12 + (i + 1) * (width / 6)-2, y + 9);
			printf("%s",work_stats[i]);
		}
		for (i = 0; i < (height - 11)/2; i++){    //Print names (column: a)
			gotoxy(x + width / 12 + (width / 6)-2, y + (i * 2) + 11);
			printf("%s",names[i]);
		}
	}
	else {
		gotoxy(3,3);//If the input in the spreadsheet function does not match the constraints print
		printf("Invalid input: spreadsheet");
	}
}

//notes window
void how_to_work_window(int x, int y, int width, int height, int fg, int bg) {
	int i;
	int lineLength = width - 2;  // subtracting border with width
	int linesAvailable = height - 2;  // subtracting space for top- and bottom border

	//Limitations
	if (1 <= x && x <= 188 &&
		    1 <= y && y <= 50 &&
		    50 <= width && width <= 188 &&
		    20 <= height && height <= 50 &&
		    (x + width) <= 189 &&
		    (y + height) <= 51 &&
		    0 <= fg && fg <= 8) {

	//Array of text
	const char* how_to[183] = {
	    "first", "and", "foremost", "Have", "trust", "in", "your", "fellow",
	    "employees,", "never", "look", "over", "their", "shoulders,", "and","always", "treat", "them",
	    "with", "respect.", "Trust", "is", "the", "foundation", "of", "effective", "collaboration,",
	    "and", "when", "employees", "feel", "trusted,", "they", "are", "more", "likely", "to",
	    "take", "initiative,", "contribute", "ideas,", "and", "take", "ownership", "of", "their",
	    "tasks.", "NEVER", "EVER", "LOOK", "AT", "ANOTHER", "EMPLOYEES", "SCREEN.",
	    "Second", "Adhere", "to", "company", "guidelines.", "When", "first", "starting", "a",
	    "job,", "thoroughly", "read", "through", "your", "employee", "handbook.", "Companies",
	    "create", "these", "handbooks", "to", "keep", "employees", "safe", "and", "comfortable",
	    "at", "work.", "By", "following", "your", "company", "policies,", "you", "set", "a",
	    "good", "example", "for", "other", "employees.", "This", "means", "acting", "professionally,",
	    "staying", "on", "task", "and", "being", "honest", "with", "your", "time.", "third", "Treat", "everyone", "with", "respect", "Always", "follow", "the", "golden", "rule,",
	    "which", "is", "to", "treat", "others", "how", "you", "want", "to", "be", "treated.", "When",
	    "conversing", "with", "co-workers,", "make", "an", "effort", "to", "only", "speak", "kindly",
	    "of", "others.", "Likewise,", "during", "a", "meeting,", "make", "sure", "to", "give", "others",
	    "a", "chance", "to", "speak.", "Practicing", "active", "listening", "is", "a", "way", "to",
	    "show", "your", "respect.", "As", "co-workers", "are", "sharing", "their", "thoughts", "and",
	    "opinions,", "show", "them", "that", "you're", "listening", "closely", "to", "what", "they're",
	    "saying."
	};
	color(fg, bg);
	draw_window (x, y, width, height);
	display_text_in_window(x + width / 2 - 12, y, "How to be the best employee");
	   int currentX = x + 1;
	   int currentY = y + 2;

	    // Loop through words in how_to array and print
	    for (i = 0; i < 183; i++) {
	        // If word fits on current line print
	        if (strlen(how_to[i]) + currentX + 1 <= x + lineLength) {
	            display_text_in_window(currentX, currentY, how_to[i]);
	            currentX += strlen(how_to[i]) + 1; // Move to next position after printing word

	        } else {
	            // ïf the word doesnt fit move to the next line
	            currentY++;
	            currentX = x + 1; // Start from beginning of next line
	            display_text_in_window(currentX, currentY, how_to[i]);
	            currentX += strlen(how_to[i]) + 1; // Move to next position
	        }

	        // Stop displaying once you run out of space in the window
	        if (currentY >= y + linesAvailable) {
	            break;
	        }
	    }

	    resetbgcolor();
	}

	else {
		gotoxy(2,2);
		printf("Invalid input: how to work window");
	}
}
//default bosskey variables
int spreadsheet_x = 1, spreadsheet_y = 1, spreadsheet_width = 188, spreadsheet_height = 50;
int work_window_x = 138, work_window_y = 30, work_window_width = 50, work_window_height = 20;
int spreadsheet_fg = 0, spreadsheet_bg = 7;
int work_window_fg = 1, work_window_bg = 7;

// Function to handle the settings input
void settings_boss_key(int x, int y, int width, int height, int fg, int bg) {
    clrscr();
    draw_window(x, y, width, height);
    display_text_in_window(x + 1, y + 1, "Settings: Customize Boss Key");
    display_text_in_window(x + 1, y + 3, "Enter values between 1 and 188 for the following:");
    display_text_in_window(x + 1, y + 4, "Follow the instructions bellow, and make sure x + width >= 189 and y + height >= 51");



    // Input buffer for user input
    char input_buffer[5];
    int i = 0;
    int valid_input = 0;
    int new_value;

    // Loop for each input variable
    // Setting for spreadsheet_x
    gotoxy(x + 1, y + 8);
    printf("Spreadsheet X: %d", spreadsheet_x);
    gotoxy(x + 1, y + 9);
    printf("Enter new value (1-138): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();  // Capture keyboard input

        if (input == 13) { // Enter key
            input_buffer[i] = '\0'; // Null-terminate the string
            new_value = atoi(input_buffer); // Convert to integer

            if (new_value >= 1 && new_value <= 138) {
                spreadsheet_x = new_value;  // Update variable if valid
                valid_input = 1;
                break;
            } else {
                gotoxy(x +  strlen("Enter new value (1-138): ") + 7, y + 9);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer)); // Reset buffer
                i = 0; // Reset index for new input
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + strlen("Enter new value (1-138): ") + 1, y + 9 );
            printf("%s", input_buffer);
        }
    }

    // Setting for spreadsheet_y
    gotoxy(x + 1, y + 11);
    printf("Spreadsheet Y: %d", spreadsheet_y);
    gotoxy(x + 1, y + 12);
    printf("Enter new value (1-30): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();

        if (input == 13) {
            input_buffer[i] = '\0';
            new_value = atoi(input_buffer);

            if (new_value >= 1 && new_value <= 30) {
                spreadsheet_y = new_value;
                valid_input = 1;
                break;
            } else {
                gotoxy(x + strlen("Enter new value (1-30): ") + 7, y + 12);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer));
                i = 0;
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + strlen("Enter new value (1-30): ") + 1, y + 12);
            printf("%s", input_buffer);
        }
    }

    // Setting for spreadsheet_width
    gotoxy(x + 1, y + 14);
    printf("Spreadsheet width: %d", spreadsheet_width);
    gotoxy(x + 1, y + 15);
    printf("Enter new value (50-188): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();

        if (input == 13) {
            input_buffer[i] = '\0';
            new_value = atoi(input_buffer);

            if (new_value >= 50 && new_value <= 188) {
                spreadsheet_width = new_value;
                valid_input = 1;
                break;
            } else {
                gotoxy(x + strlen("Enter new value (50-188): ") + 7, y + 15);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer));
                i = 0;
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + 1 + strlen("Enter new value (50-188): "), y + 15);
            printf("%s", input_buffer);
        }
    }

    // Setting for spreadsheet_height
    gotoxy(x + 1, y + 17);
    printf("Spreadsheet height: %d", spreadsheet_height);
    gotoxy(x + 1, y + 18);
    printf("Enter new value (20-50): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();

        if (input == 13) {
            input_buffer[i] = '\0';
            new_value = atoi(input_buffer);

            if (new_value >= 20 && new_value <= 50) {
                spreadsheet_height = new_value;
                valid_input = 1;
                break;
            } else {
                gotoxy(x + strlen("Enter new value (20-50): ") + 7, y + 18);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer));
                i = 0;
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + 1 + strlen("Enter new value (20-50): "), y + 18);
            printf("%s", input_buffer);
        }
    }

    // Setting for spreadsheet_fg
    gotoxy(x + 1, y + 20);
    printf("Spreadsheet foreground color: %d", spreadsheet_fg);
    gotoxy(x + 1, y + 21);
    printf("Enter new value (0-8): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();

        if (input == 13) {
            input_buffer[i] = '\0';
            new_value = atoi(input_buffer);

            if (new_value >= 0 && new_value <= 8) {
                spreadsheet_fg = new_value;
                valid_input = 1;
                break;
            } else {
                gotoxy(x + 7 + strlen("Enter new value (0-8): "), y + 21);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer));
                i = 0;
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + 1 + strlen("Enter new value (0-8): "), y + 21);
            printf("%s", input_buffer);
        }
    }

    // Setting for spreadsheet_bg
    gotoxy(x + 1, y + 23);
    printf("Spreadsheet background color: %d", spreadsheet_bg);
    gotoxy(x + 1, y + 24);
    printf("Enter new value (0-8): ");
    i = 0;
    valid_input = 0;

    while (1) {
        int input = uart_get_char();

        if (input == 13) {
            input_buffer[i] = '\0';
            new_value = atoi(input_buffer);

            if (new_value >= 0 && new_value <= 8) {
                spreadsheet_bg = new_value;
                valid_input = 1;
                break;
            } else {
                gotoxy(x + 7 + strlen("Enter new value (0-8): "), y + 24);
                printf("Invalid input, try again.");
                memset(input_buffer, 0, sizeof(input_buffer));
                i = 0;
            }
        } else if (input >= '0' && input <= '9') {
            input_buffer[i++] = input;
            input_buffer[i] = '\0';
            gotoxy(x + 1 + strlen("Enter new value (0-8): "), y + 24);
            printf("%s", input_buffer);
        }
    }

    // Setting for how_to_work_window
    // work_window_x
    gotoxy(x + 70, y + 8);
        printf("How to work X: %d", work_window_x);
        gotoxy(x + 70, y + 9);
        printf("Enter new value (1-138): ");
        i = 0;
        valid_input = 0;

        while (1) {
            int input = uart_get_char();

            if (input == 13) {
                input_buffer[i] = '\0';
                new_value = atoi(input_buffer);

                if (new_value >= 1 && new_value <= 138) {
                    work_window_x = new_value;
                    valid_input = 1;
                    break;
                } else {
                    gotoxy(x + 77 + strlen("Enter new value (1-138): "), y + 9);
                    printf("Invalid input, try again.");
                    memset(input_buffer, 0, sizeof(input_buffer));
                    i = 0;
                }
            } else if (input >= '0' && input <= '9') {
                input_buffer[i++] = input;
                input_buffer[i] = '\0';
                gotoxy(x + strlen("Enter new value (1-138): ") + 71, y + 9 );
                printf("%s", input_buffer);
            }
        }

        // work_window_Y
        gotoxy(x + 70, y + 11);
            printf("How to work Y: %d", work_window_y);
            gotoxy(x + 70, y + 12);
            printf("Enter new value (1-30): ");
            i = 0;
            valid_input = 0;

            while (1) {
                int input = uart_get_char();

                if (input == 13) {
                    input_buffer[i] = '\0';
                    new_value = atoi(input_buffer);

                    if (new_value >= 1 && new_value <= 30) {
                        work_window_y = new_value;
                        valid_input = 1;
                        break;
                    } else {
                        gotoxy(x + 77 + strlen("Enter new value (1-30): "), y + 12);
                        printf("Invalid input, try again.");
                        memset(input_buffer, 0, sizeof(input_buffer));
                        i = 0;
                    }
                } else if (input >= '0' && input <= '9') {
                    input_buffer[i++] = input;
                    input_buffer[i] = '\0';
                    gotoxy(x + strlen("Enter new value (1-30): ") + 71, y + 12 );
                    printf("%s", input_buffer);
                }
            }

            // work_window_width
                   gotoxy(x + 70, y + 14);
                       printf("How to work width: %d", work_window_width);
                       gotoxy(x + 70, y + 15);
                       printf("Enter new value (50-188): ");
                       i = 0;
                       valid_input = 0;

                       while (1) {
                           int input = uart_get_char();

                           if (input == 13) {
                               input_buffer[i] = '\0';
                               new_value = atoi(input_buffer);

                               if (new_value >= 50 && new_value <= 188) {
                                   work_window_width = new_value;
                                   valid_input = 1;
                                   break;
                               } else {
                                   gotoxy(x + 77 + strlen("Enter new value (50-188): "), y + 15);
                                   printf("Invalid input, try again.");
                                   memset(input_buffer, 0, sizeof(input_buffer));
                                   i = 0;
                               }
                           } else if (input >= '0' && input <= '9') {
                               input_buffer[i++] = input;
                               input_buffer[i] = '\0';
                               gotoxy(x + strlen("Enter new value (50-188): ") + 71, y + 15 );
                               printf("%s", input_buffer);
                           }
                       }

                       // Setting for work_window_height
                       gotoxy(x + 70, y + 17);
                       printf("How to work height: %d", work_window_height);
                       gotoxy(x + 70, y + 18);
                       printf("Enter new value (20-50): ");
                       i = 0;
                       valid_input = 0;

                       while (1) {
                           int input = uart_get_char();

                           if (input == 13) {
                               input_buffer[i] = '\0';
                               new_value = atoi(input_buffer);

                               if (new_value >= 20 && new_value <= 50) {
                            	   work_window_height = new_value;
                                   valid_input = 1;
                                   break;
                               } else {
                                   gotoxy(x + 77 + strlen("Enter new value (20-50): "), y + 18);
                                   printf("Invalid input, try again.");
                                   memset(input_buffer, 0, sizeof(input_buffer));
                                   i = 0;
                               }
                           } else if (input >= '0' && input <= '9') {
                               input_buffer[i++] = input;
                               input_buffer[i] = '\0';
                               gotoxy(x + 71 + strlen("Enter new value (20-50): "), y + 18);
                               printf("%s", input_buffer);
                           }
                       }

                       // Setting for work_window_fg
                       gotoxy(x + 70, y + 20);
                       printf("How to work foreground color: %d", work_window_fg);
                       gotoxy(x + 70, y + 21);
                       printf("Enter new value (0-8): ");
                       i = 0;
                       valid_input = 0;

                       while (1) {
                           int input = uart_get_char();

                           if (input == 13) {
                               input_buffer[i] = '\0';
                               new_value = atoi(input_buffer);

                               if (new_value >= 0 && new_value <= 8) {
                            	   work_window_fg = new_value;
                                   valid_input = 1;
                                   break;
                               } else {
                                   gotoxy(x + 77 + strlen("Enter new value (0-8): "), y + 20);
                                   printf("Invalid input, try again.");
                                   memset(input_buffer, 0, sizeof(input_buffer));
                                   i = 0;
                               }
                           } else if (input >= '0' && input <= '9') {
                               input_buffer[i++] = input;
                               input_buffer[i] = '\0';
                               gotoxy(x + 71 + strlen("Enter new value (0-8): "), y + 21);
                               printf("%s", input_buffer);
                           }
                       }

                       // Setting for work_window_bg
                       gotoxy(x + 70, y + 23);
                       printf("How to work background color: %d", work_window_bg);
                       gotoxy(x + 70, y + 24);
                       printf("Enter new value (0-8): ");
                       i = 0;
                       valid_input = 0;

                       while (1) {
                           int input = uart_get_char();

                           if (input == 13) {
                               input_buffer[i] = '\0';
                               new_value = atoi(input_buffer);

                               if (new_value >= 0 && new_value <= 8) {
                                   work_window_bg = new_value;
                                   valid_input = 1;
                                   break;
                               } else {
                                   gotoxy(x + 77 + strlen("Enter new value (0-8): "), y + 24);
                                   printf("Invalid input, try again.");
                                   memset(input_buffer, 0, sizeof(input_buffer));
                                   i = 0;
                               }
                           } else if (input >= '0' && input <= '9') {
                               input_buffer[i++] = input;
                               input_buffer[i] = '\0';
                               gotoxy(x + 71 + strlen("Enter new value (0-8): "), y + 24);
                               printf("%s", input_buffer);
                           }
                       }


    // Final message after settings are updated
    gotoxy(x + 70, y + 26);
    printf("Settings updated successfully! press space to see customized bosskey.");
    resetbgcolor();
}

int boss_key() {
    int input = 0;
    while (1) {
        input = uart_get_char(); // Register input from keyboard

        if (input == 32) { // Space key activate boss key
            clrscr();
            spreadsheet(spreadsheet_x, spreadsheet_y, spreadsheet_width, spreadsheet_height, spreadsheet_fg, spreadsheet_bg);
            how_to_work_window(work_window_x, work_window_y, work_window_width, work_window_height, work_window_fg, work_window_bg);
            resetbgcolor();
        }
        if (input == 99) { // 'c' key clear screen
            clrscr();
        }
        if (input == 115) { // 's' key settings for customizing boss key
            clrscr();
            settings_boss_key(1, 1, 188, 50, 0, 7);
        }
    }
}
