/*
 * display.h
 *
 *  Created on: Nov 8, 2022
 *      Author: Vuong
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
#include "main.h"
#include "input_processing.h"
#include "interrupt_timer.h"
#include "input_reading.h"
extern int led_index_1;
extern int led_index_2;
extern uint16_t Pin_Led_1[3];
extern uint16_t Pin_Led_2[3];
void display_SEG(int num);
void update_val_7SEG(int MODE);
void change_7SEG();
void display_led(int MODE);

#endif /* INC_DISPLAY_H_ */
