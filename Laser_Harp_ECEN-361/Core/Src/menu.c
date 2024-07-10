#include "menu.h"
#include "screen.h"
#include "tranposition.h"
#include <stdio.h>

static MenuItem current_menu_item = MENU_ITEM_OCTAVE;
static int current_setting_value = 0;

void menu_init(void) {
    current_menu_item = MENU_ITEM_OCTAVE;
    current_setting_value = 0;
    lcd_init();  // Assuming lcd_init() initializes your LCD display
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
            // Handle up button for sustain
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
            // Handle down button for sustain
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
    char buffer[32];
    lcd_clear();  // Assuming lcd_clear() clears the LCD display
    switch (current_menu_item) {
        case MENU_ITEM_OCTAVE:
            snprintf(buffer, sizeof(buffer), "Octave: ");
            lcd_set_cursor(0, 0);  // Assuming lcd_set_cursor(row, col) sets LCD cursor position
            lcd_write_string(buffer);  // Assuming lcd_write_string(str) writes string to LCD
            break;
        case MENU_ITEM_INSTRUMENT:
            snprintf(buffer, sizeof(buffer), "Instrument: ");
            lcd_set_cursor(0, 0);
            lcd_write_string(buffer);
            break;
        case MENU_ITEM_ECHO_DELAY:
            snprintf(buffer, sizeof(buffer), "Echo/Delay: ");
            lcd_set_cursor(0, 0);
            lcd_write_string(buffer);
            break;
        case MENU_ITEM_SUSTAIN:
            snprintf(buffer, sizeof(buffer), "Sustain: ");
            lcd_set_cursor(0, 0);
            lcd_write_string(buffer);
            break;
        case MENU_ITEM_TRANSPOSITION:
            snprintf(buffer, sizeof(buffer), "Transposition: ");
            lcd_set_cursor(0, 0);
            lcd_write_string(buffer);
            break;
        default:
            break;
    }
}

void pull_buttons(void) {
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_UP_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_up();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_UP_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_DOWN_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_down();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_DOWN_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_LEFT_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_left();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_LEFT_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
    }
    if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_RIGHT_PIN) == GPIO_PIN_RESET) {
        menu_handle_button_right();
        HAL_Delay(100);
        while (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_RIGHT_PIN) == GPIO_PIN_RESET) {
            HAL_Delay(100); // Debounce delay
        }
    }
}
