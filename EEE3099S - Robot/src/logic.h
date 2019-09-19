/*
 * logic.h
 *
 *  Created on: 19 Sep 2019
 *      Author: Jason Cloete
 */

#ifndef LOGIC_H_
#define LOGIC_H_

// ******* Global Variables ********

//// This states whether a sensor is detecting something or not
extern char sensors[5];

// Logic state robot is in
extern char state;
extern signed char error;
signed char pastError;

// ******* Functions ********
void followLine();
void checkIntersection();

void makeCorrections(signed char error);
void makeTurn(char direction);

void delay(int delay);

// char equalArrays(char arr1, char arr2);

#endif /* LOGIC_H_ */
