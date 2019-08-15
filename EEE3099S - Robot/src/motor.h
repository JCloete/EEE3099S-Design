/*
 * motor.h
 *
 *  Created on: Aug 15, 2019
 *      Author: Jason Cloete
 *
 *  Library of all motor functions to be used in robot.
 */

#ifndef MOTOR_H_
#define MOTOR_H_

// Just setting up some templates of what i think will be useful.
// Will add more as necessary
void forward(int amount);
void backwards(int amount);

void turn(int amount);
void turnAround(void);

// Defines
// Defining some common commands we could use (DEFAULT VALUES. CHANGE ONCE TESTING MOTOR and PWM)
#define FULL 2
#define HALF 1
#define NONE 0

#define LEFT 1
#define RIGHT 1

#endif /* MOTOR_H_ */
