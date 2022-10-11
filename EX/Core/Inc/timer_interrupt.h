/*
 * timer_interrupt.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Vuong
 */

#ifndef INC_TIMER_INTERRUPT_H_
#define INC_TIMER_INTERRUPT_H_



extern int timer1_flag;
void set_timer1(int duration);
void timer1_run();


extern int timer2_flag;
void set_timer2(int duration);
void timer2_run();

extern int timer3_flag;
void set_timer3(int duration);
void timer3_run();


extern int timer1_flag;
void set_timer4(int duration);
void timer4_run();

extern int timer1_flag;
void set_timer5(int duration);
void timer5_run();
#endif /* INC_TIMER_INTERRUPT_H_ */
