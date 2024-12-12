/**
 ******************************************************************************
 * @file           : sensor.h
 * @author         : Nidhi Gupta
 * @brief          : Header file for controlling sensors and managing related FSM functions
 * @details        : This file contains function declarations and macro definitions for:
 *                     - Controlling GPIO pins for sensors
 *                     - Trigger and echo signal handling
 *                     - System tick time management
 *                     - Distance measurement functionality
 * @reference      : Referred code from Elecia White Github account
 ******************************************************************************
 */


#include <stdio.h>         /* For using printf in debug mode */
#include <stdint.h>

#ifndef _SENSOR_H_
#define _SENSOR_H_

/**
 * @brief Macro to set PA0 (Trig pin) to HIGH state.
 * @details Used to trigger an external peripheral by sending a HIGH signal.
 */
#define Trig_high        GPIOA->BSRR = GPIO_BSRR_BS_0  /* Turn on PA0 (Trig pin) */

/**
 * @brief Macro to set PA0 (Trig pin) to LOW state.
 * @details Used to stop the trigger signal by sending a LOW state.
 */
#define Trig_low         GPIOA->BSRR = GPIO_BSRR_BR_0  /* Turn off PA0 (Trig pin) */

/**
 * @brief Pull-up resistor value for GPIO configuration.
 */
#define GPIO_PULL_UP_VALUE 1

/**
 * @typedef ticktime_t
 * @brief Type definition for system tick time in sixteenths of a second.
 */
typedef uint32_t ticktime_t; // Time in sixteenths of a second

/**
 * @brief Initializes GPIO pins for sensor control.
 * @details Configures GPIO pins to be used for trigger and echo signal handling.
 */
void init_gpio();

/**
 * @brief Sends a trigger signal using PA0 (Trig pin).
 * @details Toggles the Trig pin to initiate a measurement or interaction with an external sensor.
 */
void trig_func();

/**
 * @brief Reads the echo signal and calculates the distance.
 * @param timeout Maximum time to wait for the echo signal.
 * @return Measured distance in units defined by implementation.
 */
uint32_t read_echo(uint32_t timeout);

/**
 * @brief External declaration for distance measurement variable.
 * @details Tracks the measured distance value.
 */
extern volatile uint32_t distance;

/**
 * @brief External declaration for system time variable.
 * @details Tracks the current system time in sixteenths of a second.
 */
extern volatile ticktime_t system_time;

#endif /* _SENSOR_H_ */
