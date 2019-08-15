/*
 * Author: Jason Cloete
 * Date: 15 Aug 2019
 * Note: For use in EEE3099S Project
 *
 * This file is here to provide easy access to the motors through use of this library.
 * Will store some defaults such as full speed, braking, and neutral states.
 * Everything here will mainly be controlled through PWM
 */

/*
 *  Note that all registers and pins are probably going to change because we aren't using dev board.
 *  Everything marked with // *** means its pins are definitely wrong and havent been chosen yet/ coded
 */

// Includes
#include "stm32f0xx.h"
#include <stdio.h>
#include "motor.h"

//***
// amount should be between 0 and 100
void forward(int amount)
{
    // Add in a command that makes PWM move robot forward by a proportional amount
}

// Use this for braking i think
// amount should be between 0 and 100
void backwards(int amount)
{
	// Add in PWM commands that move motors backwards
}

// Use defines LEFT or RIGHT to turn 90 degrees left or right
void turn(int amount)
{
	// Add in a command to turn robot 90 degrees left or right then stop
}

void turnAround(void)
{
	// Add in a command to turn robot 180 degrees then stop
}
