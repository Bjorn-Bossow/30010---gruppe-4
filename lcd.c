/*
 * lcd.c
 *
 *  Created on: 19. jan. 2025
 *      Author: frikk
 */
#include "lcd.h"
#include "game.h"
#include "string.h"

int8_t Selector() {
    int ability = 1;
    int weapon = 1;
    int line = 3; // LCD LINE 3 AND 4 ARE USED TO DISPLAY WEAPONS AND ABILITIES

    if (readJoystick() == 3) { // WHEN LEFT IS PRESSED
        while (readJoystick() != 5) { // WHILE CENTER IS NOT PRESSED
            if (readJoystick() == 4 && line == 3) { // SWITCH BETWEEN WEAPONS
                if (weapon < 2) {
                    weapon += 1;
                }
            }
            if (readJoystick() == 3 && line == 3) { // SWITCH BETWEEN WEAPONS
                if (weapon > 1) {
                    weapon -= 1;
                }
            }
            if (readJoystick() == 2) { // SWITCH BETWEEN LINES
                if (line < 4) {
                    line += 1;
                }
            }
            if (readJoystick() == 1) { // SWITCH BETWEEN LINES
                if (line > 3) {
                    line -= 1;
                }
            }
            if (readJoystick() == 4 && line == 4) { // SWITCH BETWEEN ABILITIES
                if (ability < 2) {
                    ability += 1;
                }
            }
            if (readJoystick() == 3 && line == 4) { // SWITCH BETWEEN ABILITIES
                if (ability > 1) {
                    ability -= 1;
                }
            }

            if (weapon == 1 && ability == 1) {
                char result[200] = " Score Highscore Health  ";  // Ensure the destination array is large enough
                char highscore_value[] =      "  123    ";
                char score_value[] = "123    ";
                char health_value[] = "<3<3<3<3<3";
                char weapon_blaster[] = "[Blaster]        ";
                char weapon_cannon[] = " Cannon ";
                char ability_speed[] =      " [Speed]          ";
                char ability_damage[] = " Damage ";
                strcat(result, highscore_value);
                strcat(result, score_value);
                strcat(result, health_value);
                strcat(result, weapon_blaster);
                strcat(result, weapon_cannon);
                strcat(result, ability_speed);
                strcat(result, ability_damage);
                lcd_write_string(result, 1);
            }
            else if (weapon == 1 && ability == 2) {
                char result[200] = " Score Highscore Health  ";  // Ensure the destination array is large enough
                char highscore_value[] =      "  123    ";
                char score_value[] = "123    ";
                char health_value[] = "<3<3<3<3<3";
                char weapon_blaster[] = "[Blaster]        ";
                char weapon_cannon[] = " Cannon ";
                char ability_speed[] =      "  Speed           ";
                char ability_damage[] = "[Damage]";
                strcat(result, highscore_value);
                strcat(result, score_value);
                strcat(result, health_value);
                strcat(result, weapon_blaster);
                strcat(result, weapon_cannon);
                strcat(result, ability_speed);
                strcat(result, ability_damage);
                lcd_write_string(result, 1);
            }
            else if (weapon == 2 && ability == 1) {
                char result[200] = " Score Highscore Health  ";  // Ensure the destination array is large enough
                char highscore_value[] =      "  123    ";
                char score_value[] = "123    ";
                char health_value[] = "<3<3<3<3<3";
                char weapon_blaster[] = " Blaster         ";
                char weapon_cannon[] = "[Cannon]";
                char ability_speed[] =      " [Speed]          ";
                char ability_damage[] = " Damage ";

                strcat(result, highscore_value);
                strcat(result, score_value);
                strcat(result, health_value);
                strcat(result, weapon_blaster);
                strcat(result, weapon_cannon);
                strcat(result, ability_speed);
                strcat(result, ability_damage);
                lcd_write_string(result, 1);
            }
            else {
                char result[200] = " Score Highscore Health  ";  // Ensure the destination array is large enough
                char highscore_value[] =      "  123    ";
                char score_value[] = "123    ";
                char health_value[] = "<3<3<3<3<3";
                char weapon_blaster[] = " Blaster         ";
                char weapon_cannon[] = "[Cannon]";
                char ability_speed[] =      "  Speed           ";
                char ability_damage[] = "[Damage]";
        	    strcat(result, highscore_value);
        	    strcat(result, score_value);
        	    strcat(result, health_value);
        	    strcat(result, weapon_blaster);
        	    strcat(result, weapon_cannon);
        	    strcat(result, ability_speed);
        	    strcat(result, ability_damage);
        	    lcd_write_string(result, 1);
        }

        }

        // Return the value based on the weapon and ability selection
        if (weapon == 1 && ability == 1) {
            return (1);
        }
        if (weapon == 2 && ability == 1) {
            return (2);
        }
        if (weapon == 1 && ability == 2) {
            return (3);
        }
        if (weapon == 2 && ability == 2) {
            return (4);
    }
    }
    return (0); // Default return value if no valid selection
}
