/*

    __  ___                   __
   /  |/  /__  ____  __  __  / /_
  / /|_/ / _ \/ __ \/ / / / / __ \
 / /  / /  __/ / / / /_/ / / / / /
/_/  /_/\___/_/ /_/\__,_(_)_/ /_/

 *
 *  Created on: Jul 10, 2024
 *      Author: Jared Swasey
 */
#ifndef MENU_H
#define MENU_H

/* Button pins */
#define BUTTON_UP_PIN GPIO_PIN_12
#define BUTTON_DOWN_PIN GPIO_PIN_13
#define BUTTON_LEFT_PIN GPIO_PIN_14
#define BUTTON_RIGHT_PIN GPIO_PIN_15
#define BUTTON_GPIO_PORT GPIOB

typedef enum {
    MENU_ITEM_OCTAVE,
    MENU_ITEM_INSTRUMENT,
    MENU_ITEM_ECHO_DELAY,
    MENU_ITEM_SUSTAIN,
	MENU_ITEM_TRANSPOSITION,
	MENU_ITEM_COUNT
} MenuItem;

void menu_init(void);
void menu_handle_button_up(void);
void menu_handle_button_down(void);
void menu_handle_button_left(void);
void menu_handle_button_right(void);
void menu_update_display(void);
void check_buttons(void);

#endif // MENU_H
