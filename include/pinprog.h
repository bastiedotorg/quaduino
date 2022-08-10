//
// Created by bastian on 07.07.21.
//

#ifndef QUADIUNO_PINPRO_H
#define QUADIUNO_PINPRO_H
#include "datatypes.h"

/**
 * defines the input (digital) pins for pinprog
 */
#define PIN_PROG_1 22
#define PIN_PROG_2 24
#define PIN_PROG_3 26

/**
 * digital pins to which the corresponding input pins are connected if they are setted to high
 */
#define PIN_PROG_PWR_1 23
#define PIN_PROG_PWR_2 25
#define PIN_PROG_PWR_3 27

void initPinProg();
SINT8 getModuleId();

#endif //QUADIUNO_PINPRO_H
