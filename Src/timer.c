/**
 ******************************************************************************
 * @file           : timer.c
 * @author         : Nidhi Gupta
 * @brief          : Source file for timer, GPIO, and SysTick initialization
 * @details        : This file contains the implementation of functions for:
 *                     - Timer initialization and configuration
 *                     - Delays using timers and SysTick
 *                     - PWM signal generation using Timer 3
 *                     - Reading Timer 3 counter values
 *                     - System tick handling for delays
 *                   These functions are essential for precise time control and
 *                   pulse-width modulation operations in embedded systems.
 * @reference      : Referred code from Elecia White Github account
 ******************************************************************************
 */

#include "timer.h" /* Include the header file for timer-related functions and macros */

/**
 * @brief Initializes Timer 1 for generating microsecond delays.
 */
void init_timer()
{
    // Enable the clock for Timer 1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  /* Enable TIM1 clock */

    // Configure the prescaler to divide the clock by 48 (48 MHz / 48 = 1 MHz)
    TIM1->PSC = 48 - 1;  /* Prescaler value */

    // Set the auto-reload value to 1 to create a 1 microsecond interval
    TIM1->ARR = 1;  /* Auto-reload value */

    // Reset the counter
    TIM1->CNT = 0;

    // Enable the counter by setting the CEN bit in the CR1 register
    TIM1->CR1 = 1;  /* Start the timer */
}

/**
 * @brief Delays execution for a specified number of milliseconds using SysTick.
 * @param ms Number of milliseconds to delay.
 */
void delaymS(uint32_t ms) {
    // Load the SysTick timer for 1 ms interval (48 MHz clock / 48000 = 1 ms)
    SysTick->LOAD = 48000 - 1;
    SysTick->VAL = 0;  /* Clear the current value register */

    // Enable SysTick, enable interrupt, and use the processor clock
    SysTick->CTRL = SYSTICK_CTRL_INT;

    // Loop for the specified number of milliseconds
    for (uint32_t i = 0; i < ms; i++) {
        // Wait until the COUNTFLAG bit is set
        while (!(SysTick->CTRL & 0x10000)) {
        }
    }

    // Disable SysTick
    SysTick->CTRL = 0;
}

/**
 * @brief Delays execution for a specified number of microseconds using Timer 1.
 * @param us Number of microseconds to delay.
 */
void delayuS(uint32_t us) {
    for (uint32_t i = 0; i < us; i++) {
        // Wait until the update interrupt flag (UIF) is set
        while (!(TIM1->SR & 1)) {
        }

        // Clear the update interrupt flag
        TIM1->SR &= ~1;
    }
}
