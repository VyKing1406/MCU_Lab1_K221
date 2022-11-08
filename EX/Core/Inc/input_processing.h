/*
 * button.h
 *
 *  Created on: Oct 21, 2022
 *      Author: Vuong
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
////////////////////////////////////////////////


////////////////////////////////////////////////

#include "main.h"
#include "display.h"
#include "interrupt_timer.h"
#include "input_reading.h"

extern int MODE;
extern int buffer_led[3];
void button_process(uint16_t BUTTON);
void display_system();
void add_MODE();
void add_buffer(int MODE);
void confirm();

#endif /* INC_BUTTON_H_ */
