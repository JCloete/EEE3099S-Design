/*
 * logic.h
 *
 *  Created on: 19 Sep 2019
 *      Author: Jason Cloete
 */

#ifndef LOGIC_H_
#define LOGIC_H_

// ******* Global Variables ********

// This states whether a sensor is detecting something or not
extern char sensors[5];

// Logic state robot is in
extern char error;
extern char pastError;
extern char finished;

// Stores all Path information
extern char path[10][100][2];
extern char attempt;
extern char turnNum;

// ******* Functions ********
void followLine();
void checkIntersection();

void makeCorrections(char error);
void makeTurn(char direction);

void delay(int delay);

void addInfo(char intersection);
void finish(void);

// char equalArrays(char arr1, char arr2);

#endif /* LOGIC_H_ */
