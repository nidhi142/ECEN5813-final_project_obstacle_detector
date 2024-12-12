/**
 ****************************************************************************
 * @file           : sensor.c
 * @author         : Nidhi Gupta
 * @brief          : C file for controlling User LED and Finite State Machine (FSM).
 *                   Contains all functions related to FSM behavior and GPIO control.
 *
 * @details        : This file provides initialization and functionality for
 *                   controlling GPIOs, including user LEDs and input pins.
 *                   It also implements ultrasonic sensor functions for
 *                   measuring distance using trigger and echo signals.
 *
 * @reference      : Referred code from Elecia White Github account
 *
 ****************************************************************************
 */

#include "sensor.h"
#include <stdio.h>         /* For using printf in debug mode */
#include <stm32f091xc.h>   /* STM32 board-specific definitions */
#include "utilities.h"     /* For utility macros and definitions */
#include <stdbool.h>       /* For using boolean data type */
#include "timer.h"

/* Global Variables */
volatile uint32_t duration;       /* Duration of the echo signal */
volatile uint32_t distance;       /* Calculated distance based on echo duration */

/* System time in sixteenths of a second */
volatile ticktime_t system_time = 0;

/**
 * @brief  Initializes GPIOs for enabling the Clock for User LED, External LED, and Switch.
 *
 * @details
 * - Enables GPIOA and GPIOB clocks.
 * - Configures GPIOA pin PA0 as an output for sensor TRIG signal
 * - Configures GPIOA pin PA1 as an input for sensor echo signals, with pull-up resistors.
 * - Enables the I2C1 clock on APB1 for OLED display
 */
void init_gpio() {
    /* Enable GPIOA and GPIOB clocks */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

    /* Enable I2C1 clock on APB1 bus */
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* Configure PA0 as output */
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODER0, ESF_GPIO_MODER_OUTPUT);

    /* Configure PA1 as input */
    MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODER1, ESF_GPIO_MODER_INPUT);

    /* Enable pull-up resistor on PA1 */
    MODIFY_FIELD(GPIOA->PUPDR, GPIO_PUPDR_PUPDR1, GPIO_PULL_UP_VALUE);
}

/**
 * @brief  Reads the echo signal and calculates its duration.
 *
 * @param  timeout: Maximum wait time in microseconds for the signal.
 *
 * @retval Pulse duration in microseconds. Returns 0 if timeout occurs.
 */
uint32_t read_echo(uint32_t timeout) {
    uint32_t duration = 0;
    printf("In read_echo\r\n");

    /* Wait for the signal to go HIGH */
    while (!((GPIOA->IDR) & GPIO_IDR_1)) {
        duration++;
        delayuS(1);
        if (duration > timeout) {
            printf("Timeout occurred, duration: %ld\r\n", duration);
            return 0; // Timeout
        }
    }

    /* Measure the duration of the HIGH signal */
    duration = 0;
    while ((GPIOA->IDR & GPIO_IDR_1)) {
        duration++;
        delayuS(1);
        if (duration > timeout) {
            printf("2nd timeout occurred, duration: %ld\r\n", duration);
            return 0; // Timeout
        }
    }

    printf("Duration: %ld\r\n", duration);
    return duration; // Return the pulse duration
}

/**
 * @brief  Sends a trigger pulse to initiate distance measurement.
 *
 * @details
 * - Generates a 10-microsecond pulse on the trigger pin.
 * - Calls read_echo() to measure the duration of the echo signal.
 * - Calculates the distance based on the echo duration.
 */
void trig_func() {
    printf("Calling trig_func\r\n");

    Trig_low;                     // Turn off the trigger
    delayuS(10);                  // Wait for 10 microseconds
    Trig_high;                    // Turn on the trigger
    delayuS(10);                  // Wait for 10 microseconds
    Trig_low;                     // Turn off the trigger

    /* Measure the time of the echo signal */
    duration = read_echo(400000);

    /* Calculate the distance: duration / 2 * speed_of_sound (in cm/uS) */
    distance = duration / 58;

    delayuS(1000000); // Delay for stability

    printf("Trig function end, distance: %ld\r\n", distance);
}
