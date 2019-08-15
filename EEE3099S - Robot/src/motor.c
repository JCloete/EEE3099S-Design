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
void forward(int amount)
{
    // Add in a command that makes PWM move robot forward by a proportional amount
}