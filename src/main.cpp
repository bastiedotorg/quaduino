#include <Arduino.h>
#include "database.h"
#include "scheduler.h"
#include "ostime.h"
#include "xsynchro.h"
#include "spy.h"
#include "logging.h"

#include "rs485.h"
#include <SPI.h>
#include <Ethernet.h>
#include <pinprog.h>
#include <Servo.h>

#define NUM_JOBS 6
#define NUM_INIT_JOBS 8
Servo servo;
T_JOB *activeJobTable;
long numJobs;

/**
 * prints data on the Serial monitor
 *
 * @param data data with type char* to be printed
 */
void logData(char *data) {
}

/**
 * prints data on the Serial monitor
 *
 * @param data data with type int to be printed
 */
void logData(int data) {
}

/**
 * turns on an LED attached to digital Pin 45,47,49 if Z_SYN_NAVAIL of module 1-3 is false
 */
void led_high() {
    int ledState = 0;
    ledState = readDBindi(SENSOR_1);
    if (ledState > 50)
        digitalWrite(45, HIGH);
    if (ledState > 200)
        digitalWrite(47, HIGH);
    if (ledState > 500)
        digitalWrite(49, HIGH);

}

void led_low() {
    digitalWrite(45, LOW);
    digitalWrite(47, LOW);
    digitalWrite(49, LOW);
}

/**
 * initializes Serial communication on Serial port
 */
void initSerial() {
   // Serial.begin(9600);
    //Serial.write("standardSerial");

}

/**
 * analog read of analog pin A2 and prints the result to the Serial monitor
 */
void readPoti() {
    int val = 17;
    val = analogRead(A2);
    writeDBindi(SENSOR_1, val);
    servo.write(val / 2);
}

/**
 * defines digital Pins 7,45,47,49 as outputs (to connect them to a LED)
 */
void initLed() {
    pinMode(7, OUTPUT);
    pinMode(45, OUTPUT);
    pinMode(47, OUTPUT);
    pinMode(49, OUTPUT);
}

/**
 * defines analog Pin A2 as input (to connect a poti)
 */
void initPoti() {
    servo.attach(44);
    pinMode(A2, INPUT);
}

/**
 * callback function for sending test data via RS485
 */
void sendRs485() {
    sendMessageUint64(4711, XCONMA);
}

/**
 * callback function to recieve messages from to other modules
 */
void rcvRs485() {
    /*MESSAGE buf = getSamplingMessage(0, XCONMA);
    if(buf.payload.asUint == 4711) {
        led_high();
    }
    */
    MESSAGE buf1;
    MESSAGE buf2;
    receiveMessage(0, &buf1);
    receiveMessage(1, &buf2);
};

/**
 * Job Table for initialisation; to be run once
 */
T_JOB initJobTable[NUM_INIT_JOBS] = {
        {.start_time = 0, .stop_time = 0, .job_function = &initDB},
        {.start_time = 100, .stop_time = 0, .job_function = &initSerial},
        {.start_time = 100, .stop_time = 0, .job_function = &initPinProg},
        {.start_time = 200, .stop_time = 0, .job_function = &initLed},
        {.start_time = 300, .stop_time = 0, .job_function = &initPoti},
        {.start_time = 400, .stop_time = 0, .job_function = &init_spy},
        {.start_time = 500, .stop_time = 900, .job_function = &led_high},
        {.start_time = 900, .stop_time = 0, .job_function = &rs485Init},
};
const int scaler = 5;
T_JOB runJobTable[NUM_JOBS] = {
        {.start_time = 0, .stop_time = scaler * 1, .job_function = &sendRs485},
        {.start_time = 2 * scaler, .stop_time = 3 * scaler, .job_function = &rcvRs485},
        {.start_time = 4 * scaler, .stop_time = 8 * scaler, .job_function = &led_low},
        {.start_time = 8 * scaler, .stop_time = 12 * scaler, .job_function = &led_high},
        {.start_time = 12 * scaler, .stop_time = 16 * scaler, .job_function = &led_low},
        {.start_time = 16 * scaler, .stop_time = 18 * scaler, .job_function = &reset_time},
};


T_JOB runJobTable2[NUM_JOBS] = {
        {.start_time = 0, .stop_time = 1*scaler, .job_function = &job_xsynchro},
        {.start_time = 0 * scaler, .stop_time = 4 * scaler, .job_function = &reset_time},
        {.start_time = 4 * scaler, .stop_time = 6 * scaler, .job_function = &led_high},
        //{.start_time = 300, .stop_time = 0, .job_function = &led_low },
        {.start_time = 6 * scaler, .stop_time = 7 * scaler, .job_function = &readPoti},
        {.start_time = 7 * scaler, .stop_time = 11 * scaler, .job_function = &step_spy}, // with minimum data, this needs 60us
        {.start_time = 11 * scaler, .stop_time = 12 * scaler, .job_function = &led_low},
};


void setup() {
    activeJobTable = initJobTable;
    numJobs = NUM_INIT_JOBS;
    runScheduler(activeJobTable, numJobs);

    numJobs = NUM_JOBS;
    activeJobTable = runJobTable2;
}

long processCounter = 0;

void loop() {
// write your code here
    processCounter++;
    writeDBindi(X_XLANE, processCounter);
    runScheduler(activeJobTable, numJobs);

}

