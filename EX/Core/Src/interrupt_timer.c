/*
 * timer_interrupt.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Vuong
 */

#include "interrupt_timer.h"

int timer_counter[NU_OF_TIMER] = { 0, 0, 0, 0, 0, 0, 0 };
int timer_flag[NU_OF_TIMER] = { 0, 0, 0, 0, 0, 0, 0 };

///////////////////////////////////////////////////////////////////////

void setTimer(int index, int duration) {
	timer_counter[index] = duration / TIMER_CYCLE;
	timer_flag[index] = 0;
}

void timer_run() {
	for (int i = 0; i < NU_OF_TIMER; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
		} else if (timer_counter[i] <= 0) {
			timer_flag[i] = 1;
		}
	}
}

