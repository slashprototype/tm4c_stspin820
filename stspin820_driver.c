/*
 * stspin820_driver.c
 *
 *  Created on: 8 dic 2023
 *      Author: JUARELU1
 */

#include "drivers/tm4c_stspin820/stspin820_driver.h"
#include <stdbool.h>
#include <stdint.h>
#include <tm4c_utils/pins.h>
#include "tm4c_utils/timers.h"

static void configureSpeed(stspin820_driver_t* driver, uint32_t frequency_hz) {
    uint32_t some_speed_relational = frequency_hz;
    driver->speed_ml_min = some_speed_relational;
    driver->timer->configureFrequency(driver->timer, driver->speed_ml_min);
}

static void runForward(stspin820_driver_t* driver, uint32_t frequency_hz) {
    driver->enable(driver);
    driver->configureSpeed(driver, frequency_hz);
    driver->timer->enable(driver->timer);
    pinWrite(driver->pin_dir, FORWARD);
}

static void runBackward(stspin820_driver_t* driver, uint32_t frequency_hz) {
    driver->enable(driver);
    driver->configureSpeed(driver, frequency_hz);
    driver->timer->enable(driver->timer);
    pinWrite(driver->pin_dir, BACKWARD);
}

static void enable(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 1);
    pinWrite(driver->pin_stby, 1);
}

static void disable(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 1);
    pinWrite(driver->pin_stby, 0);
    driver->timer->disable(driver->timer);
}

static void standBy(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 0);
    pinWrite(driver->pin_stby, 1);
    driver->timer->disable(driver->timer);
}

static void configStepMode(stspin820_driver_t* driver, step_mode_t step_mode) {
    pinWrite(driver->m1, step_mode & 0b0001);
    pinWrite(driver->m2, (step_mode & 0b0010) >> 1);
    pinWrite(driver->m3, (step_mode & 0b0100) >> 2);
}

void setupStepMotor(stspin820_driver_t* driver, step_mode_t step_mode) {
    driver->runForward = &runForward;
    driver->runBackward = &runBackward;
    driver->enable = &enable;
    driver->disable = &disable;
    driver->standBy = &standBy;
    driver->configStepMode = &configStepMode;
    driver->configureSpeed = &configureSpeed;

    driver->configStepMode(driver, step_mode);
}
