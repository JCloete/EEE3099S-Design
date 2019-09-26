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
#include "logic.h"


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
	// RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	GPIOB->MODER |= GPIO_MODER_MODER10_1;
	GPIOB->MODER |= GPIO_MODER_MODER11_1;
	GPIOB->AFR[1] |= (2 << (4*(10-8)));
	GPIOB->AFR[1] |= (2 << (4*(11-8)));

	TIM2->ARR=4000;
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1);
	TIM2->CCMR2 |= (TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1);
	TIM2->CCR3 = 100 * 40;
	TIM2->CCR4 = 100 * 40;

	TIM2->CCER |= TIM_CCER_CC3E;
	TIM2->CCER |= TIM_CCER_CC4E;

	TIM2->CR1 |= TIM_CR1_CEN;
}

// ***
// Sets all inputs for buttons and sensors probably
void init_inputs()
{
	// Enable bus to port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Init Buttons
	// Init PA0 for button pull to ground
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0;

	// Init PA1 for button pull to ground
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0;

	// Init Sensors
	// Init PA2 for sensors input (Pulls to HIGH)
	GPIOA->MODER &= ~GPIO_MODER_MODER2;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_1;

	// Init PA3 for sensors input (Pulls to HIGH)
	GPIOA->MODER &= ~GPIO_MODER_MODER3;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_1;

	// Init PA4 for sensors input (Pulls to HIGH)
	//GPIOA->MODER &= ~GPIO_MODER_MODER4;
	//GPIOA->PUPDR |= GPIO_PUPDR_PUPDR4_1;

	// Init PA5 for sensors input (Pulls to HIGH)
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR5_1;

	// Init PA6 for sensors input (Pulls to HIGH)
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_1;

	// Init PA7 for sensors input (Pulls to HIGH)
	GPIOA->MODER &= ~GPIO_MODER_MODER7;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR7_1;


}



// ***
// Interrupt enables.
void init_EXTI()
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;	// ENABLE EXTI BUS CLK
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI2_PA | SYSCFG_EXTICR1_EXTI3_PA;	// Map interruption to PA[0,1,2,3]
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PA | SYSCFG_EXTICR2_EXTI5_PA | SYSCFG_EXTICR2_EXTI6_PA;	// Map interruption to PA[4,5,6]
	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR2 | EXTI_IMR_MR3 | EXTI_IMR_MR4 | EXTI_IMR_MR5 | EXTI_IMR_MR6;	//
	EXTI->FTSR |= EXTI_FTSR_TR0; //| EXTI_FTSR_TR1;
	EXTI->FTSR |= EXTI_FTSR_TR2 | EXTI_FTSR_TR3 | EXTI_FTSR_TR4 | EXTI_FTSR_TR5 | EXTI_FTSR_TR6;
	EXTI->RTSR |= EXTI_RTSR_TR2 | EXTI_RTSR_TR3 | EXTI_RTSR_TR4 | EXTI_RTSR_TR5 | EXTI_RTSR_TR6;
	NVIC_EnableIRQ(EXTI0_1_IRQn);// SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA | EXTI_IMR_MR0 | EXTI_IMR_MR1 |
	NVIC_EnableIRQ(EXTI2_3_IRQn);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}


void EXTI0_1_IRQHandler(void)
{
	delay(2);

	if(EXTI->PR & EXTI_PR_PR0)
	{
		finished = 0;

		EXTI->PR |= EXTI_PR_PR0; // unmasks the flag of the interrupt
	}

	/*
	if (EXTI->PR & EXTI_PR_PR1){
		asm("nop");

		EXTI->PR |= EXTI_PR_PR1; // unmasks the flag of the interrupt
	} */

}


// TEST
void EXTI2_3_IRQHandler(void)
{
	if (GPIOA->IDR & GPIO_IDR_2)
	{
		//GPIOB->ODR |= GPIO_ODR_7;
		sensors[4] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_7;
		sensors[4] = 0;
	}

	EXTI->PR |= EXTI_PR_PR2; // unmasks the flag of the interrupt
	if (GPIOA->IDR & GPIO_IDR_3)
	{
		//GPIOB->ODR |= GPIO_ODR_6;
		sensors[3] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_6;
		sensors[3] = 0;
	}

	EXTI->PR |= EXTI_PR_PR3; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_4)
	{
		//GPIOB->ODR |= GPIO_ODR_5;
		sensors[2] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_5;
		sensors[2] = 0;
	}

	EXTI->PR |= EXTI_PR_PR4; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_5)
	{
		//GPIOB->ODR |= GPIO_ODR_4;
		sensors[1] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_4;
		sensors[1] = 0;
	}

	EXTI->PR |= EXTI_PR_PR5; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_6)
	{
		//GPIOB->ODR |= GPIO_ODR_3;
		sensors[0] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_3;
		sensors[0] = 0;
	}

	EXTI->PR |= EXTI_PR_PR6; // unmasks the flag of the interrupt
}

void EXTI4_15_IRQHandler(void)
{

	if (GPIOA->IDR & GPIO_IDR_2)
	{
		//GPIOB->ODR |= GPIO_ODR_7;
		sensors[4] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_7;
		sensors[4] = 0;
	}

	EXTI->PR |= EXTI_PR_PR2; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_3)
	{
		//GPIOB->ODR |= GPIO_ODR_6;
		sensors[3] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_6;
		sensors[3] = 0;
	}

	EXTI->PR |= EXTI_PR_PR3; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_4)
	{
		//GPIOB->ODR |= GPIO_ODR_5;
		sensors[2] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_5;
		sensors[2] = 0;
	}

	EXTI->PR |= EXTI_PR_PR4; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_5)
	{
		//GPIOB->ODR |= GPIO_ODR_4;
		sensors[1] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_4;
		sensors[1] = 0;
	}

	EXTI->PR |= EXTI_PR_PR5; // unmasks the flag of the interrupt

	if (GPIOA->IDR & GPIO_IDR_6)
	{
		//GPIOB->ODR |= GPIO_ODR_3;
		sensors[0] = 1;
	} else {
		//GPIOB->ODR &= ~GPIO_ODR_3;
		sensors[0] = 0;
	}

	EXTI->PR |= EXTI_PR_PR6; // unmasks the flag of the interrupt
}



// ***
// These pins set motor highs and LED highs
void init_outputs()
{
    //Initialize the LED's to be used to output data

    RCC  ->AHBENR |= RCC_AHBENR_GPIOBEN;	// Connecting GPIO Port B to the clock through the bus using bit 18
    // GPIOB->MODER  |= 0x00001555;        // Setting modes of the PB[0-7] to outputs
    GPIOB->MODER  |= 0x00005555; // For testing purposes
}

/*
void init_buttons()
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
*/
