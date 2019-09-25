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

// ******* NOTICE: ALL CURRENT PINS HAVE TO BE SWITCHED TO PWM. CURRENTLY LIKE THIS FOR TESTING PURPOSES.

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

	GPIOB->ODR |= GPIO_ODR_5;
	GPIOB->ODR &= ~GPIO_ODR_6;
}

// Use this for braking i think
// amount should be between 0 and 100
void backwards(void)
{
	// Add in PWM commands that move motors backwards
	GPIOB->ODR &= ~GPIO_ODR_3;
	GPIOB->ODR |= GPIO_ODR_4;

	GPIOB->ODR &= ~GPIO_ODR_5;
	GPIOB->ODR |= GPIO_ODR_6;
}

void stop(void)
{
	// PWM commands to make robot stop
	GPIOB->ODR |= GPIO_ODR_3;
	GPIOB->ODR |= GPIO_ODR_4;

	GPIOB->ODR |= GPIO_ODR_5;
	GPIOB->ODR |= GPIO_ODR_6;
}

// Use defines LEFT or RIGHT to make minor adjustments
void correctPath(char direction)
{
	switch (direction)
	{
	case LEFT:
		// PWM Code to make it turn the robot left
		TIM2->CCR3 = 40 * 80;
		TIM2->CCR4 = 50 * 80;
		break;

	case STRAIGHT:
		// PWM code to make it go straight
		TIM2->CCR3 = 50 * 80;
		TIM2->CCR4 = 50 * 80;
		break;

	case RIGHT:
		// PWM code to make it go right
		TIM2->CCR3 = 50 * 80;
		TIM2->CCR4 = 40 * 80;
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
		GPIOB->ODR |= GPIO_ODR_3;
		GPIOB->ODR &= ~GPIO_ODR_4;

		GPIOB->ODR &= ~GPIO_ODR_5;
		GPIOB->ODR |= GPIO_ODR_6;
		break;

	case STRAIGHT:
		// Add in PWM commands to turn straight
		GPIOB->ODR |= GPIO_ODR_3;
		GPIOB->ODR &= ~GPIO_ODR_4;

		GPIOB->ODR |= GPIO_ODR_5;
		GPIOB->ODR &= ~GPIO_ODR_6;
		break;

	case RIGHT:
		// Add in PWM commands to turn in a direction
		GPIOB->ODR &= ~GPIO_ODR_3;
		GPIOB->ODR |= GPIO_ODR_4;

		GPIOB->ODR |= GPIO_ODR_5;
		GPIOB->ODR &= ~GPIO_ODR_6;
		break;

	default:
		printf("Not a valid direction");
	}


}

void turnAround(void)
{
	// Add in a command to turn robot 180 degrees then stop
	/*
	turn(LEFT);
	while(sensors[2] != 1);
	stop();
	*/
}
