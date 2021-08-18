//
// Created by bastie on 10/21/20.
//
#include <Arduino.h>
#include "ostime.h"
unsigned long long GLOBAL_TIME;

void reset_time() {
    GLOBAL_TIME = millis();
}

unsigned long get_time() {
    return (millis() - GLOBAL_TIME)/CYCLE_TIME;
}
