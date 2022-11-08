/*
 * display.c
 *
 *  Created on: Nov 8, 2022
 *      Author: Vuong
 */

#include "display.h"


int current_SEG = 0;
int led_index_1 = 0;
int led_index_2 = 2;
uint16_t Pin_Led_1[3] = { Red_1_Pin, Yellow_1_Pin, Green_1_Pin };
uint16_t Pin_Led_2[3] = { Red_2_Pin, Yellow_2_Pin, Green_2_Pin };
int buffer_7seg[2];


void display_led(int MODE) {
	// horizontal and vertical will have its own timer
	//buffer led will save duration of led red, yellow and green
	//led_index to alternate display
	if (MODE == 1) {
		if (timer_flag[0] == 1) {
			buffer_7seg[0]=buffer_led[led_index_1];
			setTimer(0, buffer_led[led_index_1] * 1000);
			HAL_GPIO_WritePin(GPIOB, Pin_Led_1[0] | Pin_Led_1[1] | Pin_Led_1[2],
					1);
			HAL_GPIO_WritePin(GPIOB, Pin_Led_1[led_index_1], GPIO_PIN_RESET);
			led_index_1++;
			if (led_index_1 == 3) {
				led_index_1 = 0;
			}
		}
		if (timer_flag[1] == 1) {
			buffer_7seg[1]=buffer_led[led_index_2];
			setTimer(1, buffer_led[led_index_2] * 1000);
			HAL_GPIO_WritePin(GPIOB, Red_2_Pin | Yellow_2_Pin | Green_2_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, Pin_Led_2[led_index_2], GPIO_PIN_RESET);
			led_index_2--;
			if (led_index_2 == -1) {
				led_index_2 = 2;
			}
		}
	}
	// if MODE is not 1, work is only to blink led corresponding, and turn of remainning led
	// used only 1 timer_interrupt to control blink
	if (MODE == 2) {
		if (timer_flag[2] == 1) {
			setTimer(2, 500);
			HAL_GPIO_WritePin(GPIOB,
					Pin_Led_1[1] | Pin_Led_2[1] | Pin_Led_1[2] | Pin_Led_2[2],
					1);
			HAL_GPIO_TogglePin(GPIOB, Pin_Led_1[0] | Pin_Led_2[0]);
		}
	}
	if (MODE == 3) {
		if (timer_flag[2] == 1) {
			setTimer(2, 500);
			HAL_GPIO_WritePin(GPIOB,
					Pin_Led_1[0] | Pin_Led_2[0] | Pin_Led_1[2] | Pin_Led_2[2],
					1);
			HAL_GPIO_TogglePin(GPIOB, Pin_Led_1[1] | Pin_Led_2[1]);
		}
	}
	if (MODE == 4) {
		if (timer_flag[2] == 1) {
			setTimer(2, 500);
			HAL_GPIO_WritePin(GPIOB,
					Pin_Led_1[1] | Pin_Led_2[1] | Pin_Led_1[0] | Pin_Led_2[0],
					1);
			HAL_GPIO_TogglePin(GPIOB, Pin_Led_1[2] | Pin_Led_2[2]);
		}
	}
	return;
}

void change_7SEG() {
	if (timer_flag[3] == 1) {
		setTimer(3, 250);
		update_val_7SEG(MODE);
		if (current_SEG == 0) {
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin, 1);
		}
		if (current_SEG == 1) {
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, 1);
		}
		if (current_SEG == 2) {
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN0_Pin | EN3_Pin, 1);
		}
		if (current_SEG == 3) {
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN0_Pin, 1);
		}
		current_SEG++;
		if (current_SEG == 4) {
			current_SEG = 0;
		}
	}
}
// if Mode is 1, 7seg led have a timer to alternate one time.
//buffer_7seg is duration of led, it only virtual and not effect to prime time
void update_val_7SEG(int MODE) {
	if (MODE == 1) {
		if (timer_flag[4] == 1) {
			setTimer(4, 1000);
			buffer_7seg[0]--;
			buffer_7seg[1]--;
		}
		if (current_SEG == 0) {//display dozens of horizontal
			display_SEG(buffer_7seg[1] / 10);
		}
		if (current_SEG == 1) {//display units of horizontal
			display_SEG(buffer_7seg[1] % 10);
		}
		if (current_SEG == 2) {//display dozens of vertical
			display_SEG(buffer_7seg[0] / 10);
		}
		if (current_SEG == 3) {//display units of vertical
			display_SEG(buffer_7seg[0] % 10);
		}
	}
	// mode is not 1, only display Mode in 2 7seg, and duration of buffer_led[MODE-2].
	if (MODE != 1) {
		int temp = buffer_led[MODE-2];
		if (current_SEG == 0) {
			display_SEG(0);
		}
		if (current_SEG == 1) {
			display_SEG(MODE);
		}
		if (current_SEG == 2) {
			display_SEG(temp / 10);
		}
		if (current_SEG == 3) {
			display_SEG(temp % 10);
		}
	}
	return;
}




void display_SEG(int num) {
	uint16_t temp = GPIOB->ODR & 0xffffff80;
	switch (num) {
	case 0:
		temp = temp | 0x00000040; // hex to display 0 in 7SEG
		break;
	case 1:
		temp = temp | 0x00000079; //similar
		break;
	case 2:
		temp = temp | 0x00000024; //similar
		break;
	case 3:
		temp = temp | 0x00000030; //similar
		break;
	case 4:
		temp = temp | 0x00000019; //similar
		break;
	case 5:
		temp = temp | 0x00000012;
		break;
	case 6:
		temp = temp | 0x00000002;
		break;
	case 7:
		temp = temp | 0x00000078;
		break;
	case 8:
		temp = temp | 0x00000000;
		break;
	case 9:
		temp = temp | 0x00000010;
		break;
	}
	GPIOB->ODR = temp;
}
