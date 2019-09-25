/*
 * robot.h
 *
 *  Created on: Aug 6, 2019
 *      Author: Jason Cloete
 *
 *  Header file to declare all functions to be used in EEE3099S Robot code
 */
#ifndef ROBOT_H_
#define ROBOT_H_

// Basic assumption of what we will use. Adjust as necessary.

// Initialisations (Ideally would be run once. i.e initialise all ADC's in here)
// void init_ADC(void);
void init_PWM(void);
void init_EXTI(void);
void init_inputs(void);
void init_outputs(void);
// void init_buttons(void);

// Run commands
// void run_ADC(void);

#endif /* ROBOT_H_ */
