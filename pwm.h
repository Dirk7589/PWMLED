/* 
 * File:   pwm.h
 * Author: Dirk
 *
 * Created on June 26, 2013, 8:45 PM
 */
#ifndef PWM_H
#define PWM_H

#define TIM2_PRESCALE 16 /**<Sets the Timer 2 prescale value, only 1, 4, and 16 are valid values*/

void openPWM(unsigned int period);

void closePWM(void);

void setDCPWM(unsigned int dutyCycle);

#endif