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
void forward(void);
void backwards(void);
void stop(void);

void correctPath(char direction);
void turn(char direction);
void turnAround(void);

// Defines
// Defining some common commands we could use (DEFAULT VALUES. CHANGE ONCE TESTING MOTOR and PWM)

#define LEFT 0
#define STRAIGHT 1
#define RIGHT 2


#endif /* MOTOR_H_ */
