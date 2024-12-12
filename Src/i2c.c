/**
 ******************************************************************************
 * @file           : i2c.c
 * @author         : Nidhi Gupta
 * @brief          : Source file for I2C initialization and operations
 * @details        : This file provides functions to initialize the I2C peripheral
 *                   and perform read/write operations.
 ******************************************************************************
 */

#include <i2c.h>

/**
 * @brief Initializes I2C1 peripheral.
 * @details Configures GPIO pins PB8 and PB9 for I2C alternate function,
 *          sets timing for standard mode (100 kHz), and enables the I2C1 peripheral.
 */
void init_i2c() {

    // Configure GPIOB pins PB8 (SCL) and PB9 (SDA) for alternate function
    GPIOB->MODER |= (2 << 16) | (2 << 18);  // Alternate Function mode for PB8, PB9

    // Set output type to open-drain for PB8 and PB9
    GPIOB->OTYPER |= (1 << 8) | (1 << 9);

    // Configure high-speed output for PB8 and PB9
    GPIOB->OSPEEDR |= ~((3 << 16) | (3 << 18));

    // Set alternate function AF4 for PB8 and PB9
    GPIOB->AFR[1] |= (1 << 0) | (1 << 4);

    // Reset and deassert reset for I2C1 peripheral
    RCC->APB1RSTR |= (1 << 21);  // Assert reset for I2C1
    RCC->APB1RSTR &= ~(1 << 21); // Deassert reset

    // Configure timing for I2C1 (100 kHz with 8 MHz PCLK)
    I2C1->TIMINGR = 0x10805E89;

    // Enable I2C1
    I2C1->CR1 |= I2C_CR1_PE;
}

/**
 * @brief Writes a single byte to a slave device.
 * @param addr Address of the slave device.
 * @param data Byte to write to the slave device.
 */
void I2C_Write(uint8_t addr, uint8_t wr_data) {
    // Wait until I2C is not busy
    while (I2C1->ISR & I2C_ISR_BUSY);

    // Configure the address and number of bytes to write
    I2C1->CR2 = (addr << 1) | (2 << I2C_CR2_NBYTES_Pos);
    I2C1->CR2 |= I2C_CR2_START;

    // Wait until TXIS flag is set (ready to transmit data)
    while (!(I2C1->ISR & I2C_ISR_TXIS));

    // Write data to the transmit data register
    I2C1->TXDR = wr_data;

    // Wait until transfer complete
    while (!(I2C1->ISR & I2C_ISR_TC));

    // Generate STOP condition
    I2C1->CR2 |= I2C_CR2_STOP;

    // Wait for STOP flag to be cleared
    while (!(I2C1->ISR & I2C_ISR_STOPF));

    // Clear STOP flag
    I2C1->ICR |= I2C_ICR_STOPCF;
}

/**
 * @brief Writes multiple bytes to a slave device.
 * @param addr Address of the slave device.
 * @param data Pointer to the array of data to write.
 * @param size Number of bytes to write.
 */
void I2C_Write_Multi(uint8_t address, uint8_t *wr_data, uint8_t size) {
    // Wait until I2C is not busy
    while (I2C1->ISR & I2C_ISR_BUSY);

    // Configure the address and number of bytes to write
    I2C1->CR2 = (address << 1) | (size << I2C_CR2_NBYTES_Pos);
    I2C1->CR2 |= I2C_CR2_START;

    // Transmit all bytes
    for (uint8_t i = 0; i < size; i++) {
        // Wait until TXIS flag is set (ready to transmit data)
        while (!(I2C1->ISR & I2C_ISR_TXIS));

        // Send data byte
        I2C1->TXDR = wr_data[i];
    }

    // Wait for transfer complete
    while (!(I2C1->ISR & I2C_ISR_TC));

    // Generate STOP condition
    I2C1->CR2 |= I2C_CR2_STOP;

    // Wait for STOP flag to be cleared
    while (!(I2C1->ISR & I2C_ISR_STOPF));

    // Clear STOP flag
    I2C1->ICR |= I2C_ICR_STOPCF;
}

/**
 * @brief Reads multiple bytes from a slave device.
 * @param addr Address of the slave device.
 * @param reg Register address to start reading from.
 * @param buffer Pointer to the buffer to store the received data.
 * @param size Number of bytes to read.
 */
void i2c_Readmulti(uint8_t address, uint8_t reg, uint8_t *buff, uint8_t size) {
    // Wait until I2C is not busy
    while (I2C1->ISR & I2C_ISR_BUSY);

    // Configure the slave address and send the register address to read from
    I2C1->CR2 = (address << 1) | (1 << I2C_CR2_NBYTES_Pos);
    I2C1->CR2 |= I2C_CR2_START;

    // Wait until TXIS flag is set
    while (!(I2C1->ISR & I2C_ISR_TXIS));

    // Send the register address
    I2C1->TXDR = reg;

    // Wait until transfer complete
    while (!(I2C1->ISR & I2C_ISR_TC));

    // Configure the slave address for read operation and number of bytes to read
    I2C1->CR2 = (address << 1) | I2C_CR2_RD_WRN | (size << I2C_CR2_NBYTES_Pos);
    I2C1->CR2 |= I2C_CR2_START | I2C_CR2_AUTOEND;

    // Receive all bytes
    for (uint8_t i = 0; i < size; i++) {
        // Wait until RXNE flag is set (ready to receive data)
        while (!(I2C1->ISR & I2C_ISR_RXNE));

        // Read data byte from receive data register
        buff[i] = I2C1->RXDR;
    }

    // Wait for STOP flag to be set
    while (!(I2C1->ISR & I2C_ISR_STOPF));

    // Clear STOP flag
    I2C1->ICR |= I2C_ICR_STOPCF;
}
