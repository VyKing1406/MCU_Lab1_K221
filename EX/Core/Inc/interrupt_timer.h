/*
 * interrupt_timer.h
 *
 *  Created on: Oct 22, 2022
 *      Author: Vuong
 */

#ifndef INC_INTERRUPT_TIMER_H_
#define INC_INTERRUPT_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;

extern int TIMER_CYCLE;
void set_Timer0 ( int duration );
void set_Timer1 ( int duration );
void set_Timer2 ( int duration );

void timer_Run();
#endif /* INC_INTERRUPT_TIMER_H_ */
