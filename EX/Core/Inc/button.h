/*
 * button.h
 *
 *  Created on: Oct 21, 2022
 *      Author: Vuong
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#define N_BUTTON 3
#define MAX_MODE 3


int MODE=0;
void button_reading();
unsigned char is_pressed(int idx);
void fsm_for_input_processing();

#endif /* INC_BUTTON_H_ */
