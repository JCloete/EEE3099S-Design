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


/* ** Probably not using ADC's but leaving this here just in case something changes
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
*/

// ***
// No idea how this code works. Figure it out sometime. Perhaps reuse this to make a flashing LED. The Timer interrupt part not the PWM
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
// Sets all inputs for buttons and sensors probably
void init_inputs()
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

void init_buttonPress()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //enable buttons
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0; //enable switch 0
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0; // enable switch 1
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;	// ENABLE EXTI BUS CLK
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA;	// Map interruption to PA2
	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR1;	//
	EXTI->FTSR |= EXTI_FTSR_TR0 | EXTI_FTSR_TR1; // sets to falling edge trigger
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}
void EXTI0_1_IRQHandler(void)
{
	if(EXTI->PR &= EXTI_PR_PR0)
	{
		asm("nop");
}
	else
{
	asm("nop");
}
	EXTI->PR |= EXTI_PR_PR0; // unmasks the flag of the interrupt
}

// ***
// These pins set motor highs and LED highs
void init_outputs()
{
    //Initialize the LED's to be used to output data

    RCC  ->AHBENR |= RCC_AHBENR_GPIOBEN;             // Connecting GPIO Port B to the clock through the bus using bit 18
    GPIOB->MODER  |= 0x00005555;        // Setting modes of the LED's to outputs

    GPIOB->ODR |= GPIO_ODR_2; // Turn enable 1 on
}
