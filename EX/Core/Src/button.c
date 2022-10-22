/*
 * button.c
 *
 *  Created on: Oct 21, 2022
 *      Author: Vuong
 */

# include <stdio.h>
# include "main.h"
# include "button.h"
# include "timer_interrupt.h"

GPIO_PinState DEBOUNCE_BUFFER_1[N_BUTTON] = { GPIO_PIN_SET, GPIO_PIN_SET,
		GPIO_PIN_SET};
GPIO_PinState DEBOUNCE_BUFFER_2[N_BUTTON] = { GPIO_PIN_SET, GPIO_PIN_SET,
		GPIO_PIN_SET};
GPIO_PinState BUTTON_BUFFER[N_BUTTON] = { GPIO_PIN_SET, GPIO_PIN_SET,
		GPIO_PIN_SET};
uint16_t BUTTON_PIN[N_BUTTON] = {MODE_Pin, ADD_Pin, CONFIRM_Pin};
int DEB_TIME = 100;

void button_reading() {
	for (int idx = 0; idx < N_BUTTON; idx++) {
		DEBOUNCE_BUFFER_2[idx] = DEBOUNCE_BUFFER_1[idx];
		DEBOUNCE_BUFFER_1[idx] = HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN[idx]);
		if (DEBOUNCE_BUFFER_1[idx] == DEBOUNCE_BUFFER_2[idx]) {
			BUTTON_BUFFER[idx] = DEBOUNCE_BUFFER_1[idx];
		}
	}
}
unsigned char is_pressed(int idx) {
	if (idx >= N_BUTTON)
		return 0;
	return (BUTTON_BUFFER[idx] == GPIO_PIN_RESET);
}
void fsm_for_input_processing() {
	// BUTTON ’MODE ’
	if (is_pressed(0) && timer_mode_debounce_flag == 1) {
		MODE++;
		if (MODE >= MAX_MODE)
			MODE = 0;
		setTimer_mode_debounce(DEB_TIME);
	}
	// BUTTON ’ADD ’
	if (MODE != 0 && is_pressed(1) && timer_add_debounce_flag == 1) {
		TERM++;
		setTimer_add_debounce(DEB_TIME);
	}
	// BUTTON ’CONFIRM
	if (is_pressed(2)) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		if (TERM != 0) {
			UPDATE_LED_TIME(MODE);
		}
		else{
			MODE = 0;
		}
	}
}
