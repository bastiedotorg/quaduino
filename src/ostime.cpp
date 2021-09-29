//
// Created by bastie on 10/21/20.
//
#include <Arduino.h>
#include "ostime.h"
unsigned long long GLOBAL_TIME;

/**
 * sets GLOBAL_TIME to current time of the device since startup
 */
void reset_time() {
    GLOBAL_TIME = millis();
}

/**
 * calculates the elapsed time since the last time the function reset_time has been called
 *
 * @return elapsed time since last call of reset_time
 */
unsigned long get_time() {
    return (millis() - GLOBAL_TIME)/CYCLE_TIME;
}
