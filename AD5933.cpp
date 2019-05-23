// Library Code Section of AD5933

// Author: Mohammadmahdi Talebi 

#include "AD5933_Talebi.h"
//#include <WProgram.h>
#include <Arduino.h> // For the compatibility with Arduino Conventions.
//#include <WConstants.h>

//extern HardwareSerial Serial;
//AD5933_Class AD5933(100, Serial);
AD5933_Class AD5933;



int AD5933::getByte(byte address, byte *value) {
    // Request to read a byte using the address pointer register
    Wire.beginTransmission(AD5933_ADR);
    Wire.write(ADDR_PTR);
    Wire.write(address);

    // Ensure transmission worked
    if (byte res = Wire.endTransmission() != I2C_RESULT_SUCCESS) {
        *value = res;
        return false;
    }

    // Read the byte from the written address
    Wire.requestFrom(AD5933_ADR, 1);
    if (Wire.available()) {
        *value = Wire.read();
        return true;
    } else {
        *value = 0;
        return false;
    }
}

/**
 * Write a byte to a register on the AD5933.
 *
 * @param address The register address to write to
 * @param value The byte to write to the address
 * @return Success or failure of transmission
 */

bool AD5933::sendByte(byte address, byte value) {
    // Send byte to address
    Wire.beginTransmission(AD5933_ADDR);
    Wire.write(address);
    Wire.write(value);

    // Check that transmission completed successfully
    if (byte res = Wire.endTransmission() != I2C_RESULT_SUCCESS) {
        return false;
    } else {
        return true;
    }
}


/**
 * Set the control mode register, CTRL_REG1. This is the register where the
 * current command needs to be written to so this is used a lot.
 *
 * @param mode The control mode to set
 * @return Success or failure
 */
bool AD5933::setControlMode(byte mode) {
    // Get the current value of the control register
    byte val;
    if (!getByte(CTRL_REG1, &val))
        return false;

    // Wipe out the top 4 bits...mode bits are bits 5 through 8.
    val &= 0x0F;

    // Set the top 4 bits appropriately
    val |= mode;

    // Write back to the register
    return sendByte(CTRL_REG1, val);
}


/**
 * Reset the AD5933. This interrupts a sweep if one is running, but the start
 * frequency, number of increments, and frequency increment register contents
 * are not overwritten, but an initialize start frequency command is required
 * to restart a frequency sweep.
 *
 * @return Success or failure
 */
bool AD5933::reset() {
    // Get the current value of the control register
    byte val;
    if (!getByte(CTRL_REG2, &val))
        return false;

    // Set bit D4 for restart
    val |= CTRL_RESET;

    // Send byte back
    return sendByte(CTRL_REG2, val);
}
