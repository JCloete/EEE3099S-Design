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

// Variables
