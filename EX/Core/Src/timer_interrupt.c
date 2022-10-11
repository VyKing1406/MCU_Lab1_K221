/*
 * timer_interrupt.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Vuong
 */

#include "timer_interrupt.h"

int timer1_counter = 0;
int timer1_flag = 0;

void set_timer1(int duration) {
	timer1_counter = duration;
	timer1_flag = 0;
}
void timer1_run() {
	if (timer1_counter > 0) {
		timer1_counter--;
		if (timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}
}



int timer2_counter = 0;
int timer2_flag = 0;

void set_timer2(int duration) {
	timer2_counter = duration;
	timer2_flag = 0;
}
void timer2_run() {
	if (timer2_counter > 0) {
		timer2_counter--;
		if (timer2_counter <= 0) {
			timer2_flag = 1;
		}
	}
}


int timer3_counter = 0;
int timer3_flag = 0;

void set_timer3(int duration) {
	timer3_counter = duration;
	timer3_flag = 0;
}
void timer3_run() {
	if (timer3_counter > 0) {
		timer3_counter--;
		if (timer3_counter <= 0) {
			timer3_flag = 1;
		}
	}
}



int timer4_counter = 0;
int timer4_flag = 0;

void set_timer4(int duration) {
	timer4_counter = duration;
	timer4_flag = 0;
}
void timer4_run() {
	if (timer4_counter > 0) {
		timer4_counter--;
		if (timer4_counter <= 0) {
			timer4_flag = 1;
		}
	}
}



int timer5_counter = 0;
int timer5_flag = 0;

void set_timer5(int duration) {
	timer5_counter = duration;
	timer5_flag = 0;
}
void timer5_run() {
	if (timer5_counter > 0) {
		timer5_counter--;
		if (timer5_counter <= 0) {
			timer5_flag = 1;
		}
	}
}
