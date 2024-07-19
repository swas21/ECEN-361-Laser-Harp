/*
 *
    __  ___
   /  |/  /__  ____  __  __
  / /|_/ / _ \/ __ \/ / / /
 / /  / /  __/ / / / /_/ /
/_/  /_/\___/_/ /_/\__,_/

 *
 *  Created on: Jul 10, 2024
 *      Author: Jared Swasey
 */

#include "menu.h"
#include "screen.h"
#include "tranposition.h"
#include "sustain.h"
#include <stdio.h>
#include <string.h>

#define LCD_WIDTH 16

static MenuItem current_menu_item = MENU_ITEM_OCTAVE;
static int current_setting_value = 0;

char buffer[33];

int sustain_flag = 0;

void menu_init(void) {
    current_menu_item = MENU_ITEM_SUSTAIN;
    current_setting_value = 0;
    lcd_init();
    menu_update_display();
}

void menu_handle_button_left(void) {
    if (current_menu_item > 0) {
        current_menu_item--;
    } else {
        current_menu_item = MENU_ITEM_COUNT - 1;
    }
    menu_update_display();
}

void menu_handle_button_right(void) {
    if (current_menu_item < MENU_ITEM_COUNT - 1) {
        current_menu_item++;
    } else {
        current_menu_item = 0;
    }
    menu_update_display();
}

void menu_handle_button_up(void) {
    switch (current_menu_item) {
        case MENU_ITEM_OCTAVE:
            // Handle up button for octave
            break;
        case MENU_ITEM_INSTRUMENT:
            // Handle up button for instrument
            break;
        case MENU_ITEM_ECHO_DELAY:
            // Handle up button for echo/delay
            break;
        case MENU_ITEM_SUSTAIN:
            // set flag to on
            sustain_flag = 1;
            break;
        case MENU_ITEM_TRANSPOSITION:
            tranposition__increment_octave();
            break;
        default:
            break;
    }
    menu_update_display();
}

void menu_handle_button_down(void) {
    switch (current_menu_item) {
        case MENU_ITEM_OCTAVE:
            // Handle down button for octave
            break;
        case MENU_ITEM_INSTRUMENT:
            // Handle down button for instrument
            break;
        case MENU_ITEM_ECHO_DELAY:
            // Handle down button for echo/delay
            break;
        case MENU_ITEM_SUSTAIN:
            // set flag to off
            sustain_flag = 0;
            break;
        case MENU_ITEM_TRANSPOSITION:
            tranposition__decrement_octave();
            break;
        default:
            break;
    }
    menu_update_display();
}

void menu_update_display(void) {
    lcd_clear();
    switch (current_menu_item) {
        case MENU_ITEM_OCTAVE:
            snprintf(buffer, sizeof(buffer), "Octave: ");
            lcd_set_cursor(0, 0);
            lcd_write_multiline_string(buffer);
            break;
        case MENU_ITEM_INSTRUMENT:
            snprintf(buffer, sizeof(buffer), "Instrument: ");
            lcd_set_cursor(0, 0);
            lcd_write_multiline_string(buffer);
            break;
        case MENU_ITEM_ECHO_DELAY:
            snprintf(buffer, sizeof(buffer), "Echo/Delay: ");
            lcd_set_cursor(0, 0);
            lcd_write_multiline_string(buffer);
            break;
        case MENU_ITEM_SUSTAIN:
            if (sustain_flag) {
                snprintf(buffer, sizeof(buffer), "Sustain: ON 10s duration");
            } else {
                snprintf(buffer, sizeof(buffer), "Sustain: OFF");
            }
            lcd_set_cursor(0, 0);
            lcd_write_multiline_string(buffer);
            break;
        case MENU_ITEM_TRANSPOSITION:
            snprintf(buffer, sizeof(buffer), "Transposition:  up inc, down dec");
            lcd_set_cursor(0, 0);
            lcd_write_multiline_string(buffer);
            break;
        default:
            break;
    }
}

void poll_buttons(void) {
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_UP_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_up();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_UP_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
        menu_update_display();
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_DOWN_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_down();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_DOWN_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
        menu_update_display();
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_LEFT_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_left();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_LEFT_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
        menu_update_display();
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_RIGHT_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_right();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_RIGHT_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
        menu_update_display();
    }
}
