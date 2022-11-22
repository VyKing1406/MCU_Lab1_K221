///*
// * input_reading.c
// *
// *  Created on: Oct 26, 2022
// *      Author: Vuong
// */
//
//#include "input_reading.h"
//
//static GPIO_PinState debounceButtonBuffer0[NO_OF_BUTTONS];
//static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
//static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
//static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];
//int timer_buttonpress_counter[NO_OF_BUTTONS];
//int flag_auto = 0;
//uint16_t Pin_input[3] = { button_Pin };
//void button_reading() {
//	for (int i = 0; i < NO_OF_BUTTONS; i++) {
//		debounceButtonBuffer0[i] = debounceButtonBuffer1[i];
//		debounceButtonBuffer1[i] = debounceButtonBuffer2[i];
//		debounceButtonBuffer2[i] = HAL_GPIO_ReadPin(GPIOA, Pin_input[i]);
//		if ((debounceButtonBuffer0[i] == debounceButtonBuffer1[i])
//				&& (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])) {
//			if (debounceButtonBuffer3[i] != debounceButtonBuffer2[i]) {
//				debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
//
//				if (debounceButtonBuffer2[i] == BUTTON_IS_PRESSED) {//button is press less 3s
//					button_process(Pin_input[i]); //function to perform the function corresponding to each mode
//					timer_buttonpress_counter[i] = NU_OF_DEBOUNCE; //timer for press it will be 3s
//					//if over this, it mean the button is being pressed.
//				}
//			} else {
//				timer_buttonpress_counter[i]--;
//				if (timer_buttonpress_counter[i] == 0) { //button is being pressed
//					if (debounceButtonBuffer2[i] == BUTTON_IS_PRESSED) {
//						button_process(Pin_input[i]);
//					}
//					timer_buttonpress_counter[i] = NU_OF_AUTO_COUNTER;
//					//change timer to count only 1s similar auto pressed
//				}
//			}
//		}
//	}
//}
