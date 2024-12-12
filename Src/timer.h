/**
 ******************************************************************************
 * @file           : timer.c
 * @author         : Nidhi Gupta
 * @brief          : Header file for timer, GPIO, and SysTick initialization
 * @details        : This file contains function declarations and macro definitions for:
 *                     - GPIO initialization
 *                     - Timer configuration (e.g., PWM generation, delays)
 *                     - SysTick timer handling
 * @reference      : Referred code from Elecia White Github account
 ******************************************************************************
 */

#include <stdio.h>         /* For using printf in debug mode */
#include <stm32f091xc.h>   /* STM32 board-specific definitions */
#include "utilities.h"     /* For utility macros and definitions */
#include <stdbool.h>       /* For using boolean data type */

#include "sensor.h"

#ifndef _TIMER_H_
#define _TIMER_H_


/**
 * @brief SysTick control register configuration.
 * @details Enables SysTick timer with interrupt and uses the processor clock.
 */
#define SYSTICK_CTRL_INT 0x07

/**
 * @brief Initializes GPIO pins for peripheral control.
 * @details Configures GPIO pins for various functions such as triggering, alternate
 *          function selection, or general I/O operations.
 */
void init_gpio();

/**
 * @brief Initializes Timer 1 for time-based control.
 * @details Configures the timer for operations such as delays, PWM generation, or
 *          other time-sensitive tasks.
 */
void init_timer();

/**
 * @brief Delays execution for a specified amount of time in milliseconds.
 * @param ms Number of milliseconds to delay.
 */
void delaymS(uint32_t ms);

/**
 * @brief Delays execution for a specified amount of time in microseconds.
 * @param us Number of microseconds to delay.
 */
void delayuS(uint32_t us);

#endif /* _TIMER_H_ */
