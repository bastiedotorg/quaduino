#include <Arduino.h>
#include "database.h"
#include "scheduler.h"
#include "ostime.h"
#include "xsynchro.h"

#define NUM_JOBS 6
#define NUM_INIT_JOBS 6

T_JOB *activeJobTable;
long numJobs;

void led_high() {
    digitalWrite(7, HIGH); // sets the digital pin 13 on

}

void led_low() {
    digitalWrite(7, LOW); // sets the digital pin 13 on

}

void initSerial() {
    Serial.begin(9600);
    Serial.write("begin");

}

void initLed() {
    pinMode(7, OUTPUT);
}

T_JOB initJobTable[NUM_INIT_JOBS] = {
        {.start_time = 0, .stop_time = 0, .job_function = &initDB },
        {.start_time = 100, .stop_time = 0, .job_function = &initSerial },
        {.start_time = 200, .stop_time = 0, .job_function = &initLed },
        {.start_time = 300, .stop_time = 0, .job_function = &led_low },
        {.start_time = 400, .stop_time = 0, .job_function = &led_low },
        {.start_time = 500, .stop_time = 0, .job_function = &led_low },
};


T_JOB runJobTable[NUM_JOBS] = {
        {.start_time = 0, .stop_time = 0, .job_function = &job_xsynchro },
        {.start_time = 100, .stop_time = 0, .job_function = &reset_time },
        {.start_time = 200, .stop_time = 0, .job_function = &led_high },
        {.start_time = 300, .stop_time = 0, .job_function = &led_low },
        {.start_time = 400, .stop_time = 0, .job_function = &led_low },
        {.start_time = 500, .stop_time = 0, .job_function = &led_low },
};

void initDatabases() {
    initDB();
}
void setup() {

    activeJobTable = initJobTable;
    numJobs = NUM_INIT_JOBS;
    runScheduler(activeJobTable, numJobs);


    numJobs = NUM_JOBS;
    activeJobTable = runJobTable;


}

void loop() {
// write your code here
    runScheduler(activeJobTable, numJobs);
    Serial.write("loop");
}

