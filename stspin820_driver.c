/*
 * stspin820_driver.c
 *
 *  Created on: 8 dic 2023
 *      Author: JUARELU1
 */

#include <drivers/stspin820/stspin820_driver.h>
#include <stdint.h>
#include <stdbool.h>
#include <tm4c_utils/pins.h>


void configStepMode(stspin820_driver_t* driver, step_mode_t step_mode){
    pinWrite(driver->m1, step_mode & 0b0001);
    pinWrite(driver->m2, (step_mode & 0b0010) >> 1);
    pinWrite(driver->m3, (step_mode & 0b0100) >> 2); 
}

void enableStepMotor(stspin820_driver_t* driver, uint8_t is_forward){
    pinWrite(driver->pin_en, 0);
    pinWrite(driver->pin_stby, 1);
    
    if(is_forward){
        pinWrite(driver->pin_dir, 1);
    }
    else{
        pinWrite(driver->pin_dir, 0);
    }
}

void disableStepMotor(stspin820_driver_t* driver){
    pinWrite(driver->pin_en, 1);
    pinWrite(driver->pin_stby, 0);
}

void setStandByStepMotor(stspin820_driver_t* driver){
    pinWrite(driver->pin_en, 0);
    pinWrite(driver->pin_stby, 1);
}



