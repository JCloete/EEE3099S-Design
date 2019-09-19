/*
 * logic.c
 *
 *  Created on: 19 Sep 2019
 *  Author: Jason Cloete
 *  Note: For use in EEE3099S Project
 *
 *  This file is to store Robot logic for determining path decisions and also
 *  stores the states of the robot. These states all link to each other and determine
 *  how the robot should handle the sensor input depending on the state
 *
 *  State 1: Line Following/Detection
 *  This state is to keep the robot detecting lines and keep it on path while looking out
 *  for turns and intersections and the end. Main State
 *
 *  State 2: Turning
 *  This state is accessed once the robot has detected a turn. It decides on the direction
 *  to take at a intersection and initiates the turn while using the sensors to detect the
 *  end of the turn
 *  *NOTE* : For turns: || value = 0 -> LEFT TURN || value = 1 -> STRAIGHT TURN || value = 2 -> RIGHT TURN
 *
 *  State 3: End of Maze
 *  This state is accessed once State 1 has detected the end of the maze. This state stops the robot
 *  and saves the last path into an array while also handling all processes like blinking LED's
 *  after the maze detection section is finished
 */

// Includes
#include "stm32f0xx.h"
#include <stdio.h>
#include "logic.h"
#include "motor.h"

char sensors[5] = {0, 1, 1, 0, 0};

// Logic state robot is in
char state = 1; // Start default state at Line Following
signed char error = 0; // Start with on correct path
signed char pastError = 0;

void followLine()
{
	if (state == 1)
	{
		// This section keeps it following the line
		// Smaller If statements inside check if its just a correction or turn
		if (sensors[1] == 0 && sensors[2] == 1 && sensors[3] == 0)
		{
			error = 0;
		} else if (sensors[1] == 0 && sensors[2] == 1 && sensors[3] == 1) {
			if (sensors[4] == 1)
			{
				state = 2;
				checkIntersection();
				return;
			} else {
				error = 1;
			}
		} else if (sensors[1] == 0 && sensors[2] == 0 && sensors[3] == 1) {
			error = 2;
		} else if (sensors[1] == 1 && sensors[2] == 1 && sensors[3] == 0) {
			if (sensors[0] == 1)
			{
				state = 2;
				checkIntersection();
				return;
			} else {
				error = -1;
			}
		} else if (sensors[1] == 1 && sensors[2] == 0 && sensors[3] == 0) {
			error = -2;
		} else {
			printf("DEAD END");
			state = 2;
			checkIntersection();
		}


		// Add in a check for if the sensors are truly fucked up
		correctPath(error); // Adds in what the error is for corrections to be made

	} else {
		printf("Not in correct state for line following!");
	}
}

void checkIntersection()
{
	// Check dead end
	if (sensors[0] == 0 && sensors[1] == 0 && sensors[2] == 0 && sensors[3] == 0 && sensors[4] == 0)
	{
		turnAround();
	} else if (sensors[0] == 1 && sensors[1] == 1 && sensors[2] == 1 && sensors[3] == 1 && sensors[4] == 1) {
		forward();
		delay(100);
		stop();
	}
}

void makeCorrections(signed char error)
{
	if (state == 1)
	{
		if (error != pastError)
		{
			switch (error)
			{
			case 0:
				pastError = 0;
				correctPath(STRAIGHT);
				break;

			case 1:
				pastError = 1;
				correctPath(LEFT);
				break;

			case -1:
				pastError = -1;
				correctPath(RIGHT);
				break;

			default:
				printf("Undefined correction");
			}
		}
	} else {
		printf("Not correct state to make corrections to path!");
	}
}

void makeTurn(char direction)
{
	if (state == 2)
	{
		// Add in a command to turn robot 90 degrees left or right then stop
		switch (direction)
		{
		case 0:
			turn(LEFT);
			break;

		case 1:
			turn(STRAIGHT);
			break;

		case 2:
			turn(RIGHT);
			break;

		default:
			printf("Not a valid direction");
		}

		while(sensors[2] != 1); // Constantly check for if turn is completed
		turn(STRAIGHT);
		state = 1;

	} else {
		printf("Not in a valid state for turning");
	}
}

// Suggested delay between 1000 - 20000 gives between 0.4 - 3
void delay(int delay)
{
	for (int i = 0; i < delay; i++)
		for (int j = 0; j < 100000; j++);
}

/*
char equalArrays(char arr1, char arr2)
{
	for (int i = 0;i<5;i++)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}

	return 1;
}
*/
