/*
 * stspin820_driver.h
 *
 *  Created on: 8 dic 2023
 *      Author: JUARELU1
 */

#ifndef SRC_DRIVERS_STSPIN820_STSPIN820_DRIVER_H_
#define SRC_DRIVERS_STSPIN820_STSPIN820_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <tm4c_utils/pins.h>

/* Step mode pre-scaler selection*/
typedef enum {
    STEP_1_1   = 0b0000,
    STEP_1_2   = 0b0001,
    STEP_1_4   = 0b0010,
    STEP_1_8   = 0b0011,
    STEP_1_16  = 0b0100,
    STEP_1_32  = 0b0101,
    STEP_1_128 = 0b0110,
    STEP_1_256 = 0b0111,
}step_mode_t;

typedef enum {
    BACKWARD = 0U,
    FORWARD = 1U
}dir_mode_t;

/* Legacy functions to handle normal driver operations*/
typedef struct stspin820_legacy_functions stspin820_legacy_functions_t;

/* 
 * Library - driver base structure
 */
typedef struct{
    pin_t* pin_en;
    pin_t* pin_dir;
    pin_t* pin_step;
    pin_t* pin_stby;
    pin_t* m1;
    pin_t* m2;
    pin_t* m3;
    uint16_t step_mode;
    void (*runForward)(uint32_t);
    void (*runBackward)(uint32_t);
    stspin820_legacy_functions_t* legacy_functions;

}stspin820_driver_t;

struct stspin820_legacy_functions {
    void (*enable)(stspin820_driver_t*, dir_mode_t);
    void (*disable)(stspin820_driver_t*);
    void (*setStandBy)(stspin820_driver_t*);
};

void configStepMode(stspin820_driver_t* driver, step_mode_t step_mode);

/* Function to enable the step motor in the direction selected
 * @param is_forward set the @ref pin_dir in the selected configuration, 
 * use the @ref dir_mode_t to select backward or forward
 */
void enableStepMotor(stspin820_driver_t* driver, dir_mode_t is_forward);
void disableStepMotor(stspin820_driver_t* driver);
void setStandByStepMotor(stspin820_driver_t* driver);

#endif /* SRC_DRIVERS_STSPIN820_STSPIN820_DRIVER_H_ */
