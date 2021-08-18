//
// Created by bastian on 07.07.21.
//

#include <Arduino.h>
#include "pinprog.h"

SINT8 moduleIdentifier = 0;

typedef struct {
    unsigned int num0 : 1;
    unsigned int num1 : 1;
    unsigned int num2 : 1;
    unsigned int num3 : 1;
    unsigned int num4 : 1;
    unsigned int num5 : 1;
    unsigned int num6 : 1;
    unsigned int num7 : 1;
} PIN_STATUS;

void initPinProg() {
    PIN_STATUS pinProg;

    pinMode(PIN_PROG_1, INPUT_PULLUP);
    pinMode(PIN_PROG_2, INPUT_PULLUP);
    pinMode(PIN_PROG_3, INPUT_PULLUP);

    pinMode(PIN_PROG_PWR_1, OUTPUT);
    pinMode(PIN_PROG_PWR_2, OUTPUT);
    pinMode(PIN_PROG_PWR_3, OUTPUT);

    digitalWrite(PIN_PROG_PWR_1, LOW);
    digitalWrite(PIN_PROG_PWR_2, LOW);
    digitalWrite(PIN_PROG_PWR_3, LOW);

    pinProg.num0 = !digitalRead(PIN_PROG_1);
    pinProg.num1 = !digitalRead(PIN_PROG_2);
    pinProg.num2 = !digitalRead(PIN_PROG_3);
    pinProg.num3 = 0;
    pinProg.num4 = 0;
    pinProg.num5 = 0;
    pinProg.num6 = 0;
    pinProg.num7 = 0;

    moduleIdentifier = *((SINT8*) &pinProg);
}

SINT8 getModuleId() {
    return moduleIdentifier;
}