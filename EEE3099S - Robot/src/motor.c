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
#include "logic.h"

//***
// amount should be between 0 and 100
void forward(void)
{
    // Add in a command that makes PWM move robot forward by a proportional amount
	GPIOB->ODR |= GPIO_ODR_3;
	GPIOB->ODR &= ~GPIO_ODR_4;
}

// Use this for braking i think
// amount should be between 0 and 100
void backwards(void)
{
	// Add in PWM commands that move motors backwards
	GPIOB->ODR &= ~GPIO_ODR_3;
	GPIOB->ODR |= GPIO_ODR_4;
}

void stop(void)
{
	// PWM commands to make robot stop
	GPIOB->ODR &= ~GPIO_ODR_3;
	GPIOB->ODR &= ~GPIO_ODR_4;
}

// Use defines LEFT or RIGHT to make minor adjustments
void correctPath(char direction)
{
	switch (direction)
	{
	case LEFT:
		// PWM Code to make it turn the robot left
		asm("nop");
		break;

	case STRAIGHT:
		// PWM code to make it go straight
		asm("nop");
		break;

	case RIGHT:
		// PWM code to make it go right
		asm("nop");
		break;
	}
}

// Use defines LEFT or RIGHT to turn 90 degrees left or right
void turn(char direction)
{
	// Add in a command to turn robot 90 degrees left or right then stop
	switch (direction)
	{
	case LEFT:
		// Add in PWM commands to turn LEFT
		break;

	case STRAIGHT:
		// Add in PWM commands to turn straight
		break;

	case RIGHT:
		// Add in PWM commands to turn in a direction
		break;

	default:
		printf("Not a valid direction");
	}


}

void turnAround(void)
{
	// Add in a command to turn robot 180 degrees then stop
}
