/**
 ****************************************************************************
 * @file           : i2c.h
 * @author         : Nidhi Gupta
 * @brief          : Header file for I2C initialization and data transfer functions
 * @date           : December 7, 2024
 * @details        : This file contains function prototypes and includes required for
 *                   I2C communication setup and data transfer.
 ****************************************************************************
 */

#include <stdio.h>         /* For using printf in debug mode */
#include <stm32f091xc.h>   /* STM32 board-specific definitions */
#include "stm32f0xx.h"     /* STM32 HAL headers */
#include "utilities.h"     /* For utility macros and definitions */
#include <stdbool.h>       /* For using boolean data type */
#include <stdint.h>        /* For fixed-width integer types */
#include <math.h>          /* For mathematical functions */

#ifndef I2C_H_
#define I2C_H_

/**
 * @brief Initializes the I2C peripheral.
 *
 * Configures GPIO pins for I2C communication, sets timing for the desired I2C speed,
 * and enables the I2C peripheral.
 */
void init_i2c();

/**
 * @brief Writes a single byte of data to the specified I2C address.
 *
 * @param addr The 7-bit I2C address of the target device.
 * @param data The byte of data to be transmitted.
 */
void I2C_Write(uint8_t addr, uint8_t data);

/**
 * @brief Writes multiple bytes of data to the specified I2C address.
 *
 * @param addr The 7-bit I2C address of the target device.
 * @param data Pointer to the array of bytes to be transmitted.
 * @param size Number of bytes in the data array.
 */
void I2C_Write_Multi(uint8_t addr, uint8_t *data, uint8_t size);

#endif /* I2C_H_ */
