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

char sensors[5] = {0, 0, 1, 0, 0};

// Logic state robot is in
char error = 0; // Start with on correct path
char pastError = 9; //  Start at an error that is impossible
char finished = 1; // Indicates when the robot has found the maze

// Path array to store information about path (1st entry is Intersection type, 2nd entry is time taken to get to this intersection from last intersection)
char path[10][100][2];
char attempt = 0;
char turnNum = 0; // This gets incremented with each intersection discovered

void followLine()
{
	// This section keeps it following the line
	// Smaller If statements inside check if its just a correction or turn
	if (sensors[1] == 0 && sensors[2] == 1 && sensors[3] == 0)
	{
		error = STRAIGHT;
	} else if (sensors[1] == 0 && sensors[3] == 1) {
		if (sensors[4] == 1)
		{
			checkIntersection();
			return;
		} else {
			error = RIGHT;
		}
	} else if (sensors[1] == 1 && sensors[3] == 0) {
		if (sensors[0] == 1)
		{
			checkIntersection();
			return;
		} else {
			error = LEFT;
		}
	} else {
		printf("DEAD END or T-Junction");
		checkIntersection();
		return;
	}


	// Add in a check for if the sensors are truly fucked up
	makeCorrections(error); // Adds in what the error is for corrections to be made

}

void checkIntersection()
{
	stop();
	delay(1);
	// Check dead end
	if (sensors[0] == 0 && sensors[1] == 0 && sensors[2] == 0 && sensors[3] == 0 && sensors[4] == 0)
	{
		addInfo(6, 4);
		turnAround();
	} else if (sensors[0] == 1 || sensors[4] == 1) {
		// Check what kind of intersection
		if (sensors[0] == 1 && sensors[4] == 1)
		{
			// This is a T-section or crossroads
			// Move forward to check for a continuation straight
			forward();
			delay(20);
			stop();

			if (sensors[0] == 1 && sensors[4] == 1)
			{
				// This is the circle
				finished = 1;
				stop();
				return;
			}
			else if (sensors[2] == 1)
			{
				// Add in a flag to indicate there is a straight
				addInfo(4, 1);
			} else {
				addInfo(3, 1);
			}

			makeTurn(LEFT);
		}
		else if (sensors[0] == 1)
		{
			// This is a left turn
			// Move forward to check for a continuation straight
			forward();
			delay(20);
			stop();

			if (sensors[2] == 1)
			{
				// Add in a flag to indicate there is a straight
				addInfo(2,1);
			} else {
				addInfo(1,1);
			}

			makeTurn(LEFT);
		} else if (sensors[4] == 1)
		{
			// This is a right turn
			// Move forward to check for a continuation straight
			forward();
			delay(20);
			stop();

			if (sensors[2] == 1)
			{
				// Add in a flag to indicate there is a straight
				addInfo(6, 3);
			} else {
				addInfo(5, 3);
			}

			makeTurn(RIGHT);
		}
	} else {
		printf("Either false alarm or unable to determine intersection type");
	}
}

// Decides on what corrections to be made depending on error
void makeCorrections(char error)
{
	if (error != pastError)
	{
		switch (error)
		{
		case STRAIGHT:
			pastError = STRAIGHT;
			correctPath(STRAIGHT);
			break;

		case LEFT:
			pastError = LEFT;
			correctPath(LEFT);
			break;

		case RIGHT:
			pastError = RIGHT;
			correctPath(RIGHT);
			break;

		default:
			printf("Undefined correction");
		}
	}
}

void makeTurn(char direction)
{
	// Add in a command to turn robot 90 degrees left or right then stop
	switch (direction)
	{
	case 0:
		forward();
		delay(20);
		stop();
		turn(LEFT);
		break;

	case 1:
		forward();
		delay(20);
		stop();
		turn(STRAIGHT);
		break;

	case 2:
		forward();
		delay(20);
		stop();
		turn(RIGHT);
		break;

	default:
		printf("Not a valid direction");
	}

	while(sensors[2] == 1); // Wait for the sensor to get off original path and move into transition mode (Otherwise below line executes immediately)
	while(sensors[2] != 1); // Constantly check for if turn is completed
	turn(STRAIGHT);
	turnNum++;
}

// Suggested delay between 1000 - 20000 gives between 0.4 - 3
void delay(int delay)
{
	for (int i = 0; i < delay; i++)
		for (int j = 0; j < 10000; j++);
}

// intersection is a set of defined numbers assinged to types of intersections defined below
// 0 - Ignore intersection | 1 - Left Turn | 2 - Left Turn str | 3 - T-junction | 4 - Crossroads | 5 - Right Turn | 6 - Right Turn str | 7 - Dead-End
// 0 - Skip Turn | 1 - LEFT Turn | 2 - Straight | 3 - RIGHT Turn | 4 - Turn Around
void addInfo(char intersection, char turnTaken)
{
	// Adds information to the path array
	path[attempt][turnNum][0] = intersection;
	path[attempt][turnNum][1] = turnTaken;
}

void finish()
{
	// Optimise path just taken
	// Start new array
	int length = 0;
	int deadend = 0;

	for (int i = 0; i<100; i++)
	{
		if (path[attempt][i][0] == 6)
		{
			deadend = i;
			path[attempt][i][1] = 0;
			i++;
			while(path[attempt][i][0] == 1 || path[attempt][i][0] == 5)
			{
				path[attempt][i][0] = 0;
				length++;
			}

			for (int j = 0; j < length; j++)
			{
				path[attempt][deadend-j][0] = 0;
			}

			// Turn recorded turn into something different and change intersection into a Intersection that removes the path down the dead end

		}

	}


	attempt++;
	turnNum = 0;
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
