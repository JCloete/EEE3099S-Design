/*
 * Author: Jason Cloete
 * Date: 6 Aug 2019
 * Note: For use in EEE3099S Project
 *
 * File to store all possible commands that would be commonly used in the implementation of the robot.
 * Stuff like initialising ADC, PWM and other commonly used pins as shown in the tutorial
 */

/*
 *  Note that all registers and pins are probably going to change because we aren't using dev board.
 *  Everything marked with // *** means its pins are definitely wrong and havent been chosen yet/ coded
 */

// Includes
#include "stm32f0xx.h"
#include <stdio.h>
#include "robot.h"

// ***
void init_ADC(void)
{
	// Temporary code storage

	// Enabling ADC, Clock and Mode
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA -> MODER |= GPIO_MODER_MODER5;
	RCC -> APB2ENR |= RCC_APB2ENR_ADCEN;

	// ADC Settings
	ADC1 -> CFGR1 |= ADC_CFGR1_RES_1;
	ADC1 -> CFGR1 &= ~ADC_CFGR1_ALIGN;
	ADC1 -> CFGR1 &= ~ADC_CFGR1_CONT;
	ADC1 -> CHSELR |= ADC_CHSELR_CHSEL5;

	// Starting ADC ---- Note: This potentially should be in run_ADC. Need to have a closer look.
	ADC1 -> CR |= ADC_CR_ADEN;
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0);
}

// ***
// Have to time this right because if its always sampling it leaves time for nothing else. Have a look at threading?
void run_ADC(void)
{
	ADC1 -> CR |= ADC_CR_ADSTART;
	while((ADC1->ISR & ADC_ISR_EOC) == 0);

	//ADC_value = ADC1->DR;
}

// ***
// No idea how this code works. Figure it out sometime
void init_PWM(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	GPIOB->MODER |= GPIO_MODER_MODER10_1;
	GPIOB->MODER |= GPIO_MODER_MODER11_1;
	GPIOB->AFR[1] |= (2 << (4*(10-8)));
	GPIOB->AFR[1] |= (2 << (4*(11-8)));

	TIM2->ARR=3999;
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1);
	TIM2->CCMR2 |= (TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1);
	TIM2->CCR3 = 50 * 40;
	TIM2->CCR4 = 50 * 40;

	TIM2->CCER |= TIM_CCER_CC3E;
	TIM2->CCER |= TIM_CCER_CC4E;

	TIM2->CR1 |= TIM_CR1_CEN;
}

// ***
// Interrupt enable. Clashes with ADC code. Have to sense like every 100ms or something to allow Interrupts?
void init_EXTI()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;	// ENABLE EXTI BUS CLK
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;	// Map interruption to PA2
	EXTI->IMR |= EXTI_IMR_MR2;	//
	EXTI->FTSR |= EXTI_FTSR_TR2;
	NVIC_EnableIRQ(EXTI2_3_IRQn);
}

// ***
// Does what it says. Probably used for the two buttons to start stop robot.
void init_buttons()
{
	// Init buttons
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Init Switch 0
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0;

	// Init Switch 1
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0;
}

// ***
// Actual values are going to change because not on STM32F051C6 UCT Devboard
void init_LED()
{
    //Initialize the LED's to be used to output data

    RCC  ->AHBENR |= 1<<18;             // Connecting GPIO Port B to the clock through the bus using bit 18
    GPIOB->MODER  |= 0x00005555;        // Setting modes of the LED's to outputs
}
