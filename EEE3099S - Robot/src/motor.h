/*
 * motor.h
 *
 *  Created on: Aug 15, 2019
 *      Author: Jason Cloete
 *
 *  Libary of all motor functions to be used in robot.
 */

#ifndef MOTOR_H_
#define MOTOR_H_

// Just setting up some templates of what i think will be useful.
// Will add more as necessary
void forward(int amount);
void backwards(int amount);
void brake(int amount);

void turnLeft(void);
void turnRight(void);
void turnAround(void);

#endif /* MOTOR_H_ */