/*
 * input_reading.h
 *
 *  Created on: Oct 23, 2022
 *      Author: Vuong
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#define NO_OF_BUTTONS 3
#define NU_OF_DEBOUNCE 100
#define NU_OF_AUTO_COUNTER 50
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET



#include "main.h"
#include "display.h"
#include "input_processing.h"
#include "interrupt_timer.h"

void button_reading();

#endif /* INC_INPUT_READING_H_ */
