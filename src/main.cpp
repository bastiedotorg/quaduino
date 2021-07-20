#include <Arduino.h>
#include "database.h"
#include "scheduler.h"
#include "ostime.h"
#include "xsynchro.h"
#include "spy.h"

#include "rs485.h"

#define NUM_JOBS 6
#define NUM_INIT_JOBS 7

T_JOB *activeJobTable;
long numJobs;

void led_high() {
    digitalWrite(45, HIGH); // sets the digital pin 13 on
    digitalWrite(47, HIGH);
    digitalWrite(49, HIGH);
}

void led_low() {
    digitalWrite(45, LOW);
    digitalWrite(47, LOW);
    digitalWrite(49, LOW);
}

void initSerial() {
    Serial.begin(9600);
    //Serial.write("standardSerial");

}

void readPoti() {
    int val = 17;
    val = analogRead(A2);
    Serial.print(val);
}


void initLed() {
    pinMode(7, OUTPUT);
    pinMode(45, OUTPUT);
    pinMode(47, OUTPUT);
    pinMode(49, OUTPUT);
}

void initPoti() {
    pinMode(A2, INPUT);
}

void sendRs485() {
    sendMessageUint64(4711, XCONMA);
}

void rcvRs485 (){
    /*MESSAGE buf = getSamplingMessage(0, XCONMA);
    if(buf.payload.asUint == 4711) {
        led_high();
    }
    */
    MESSAGE buf1;
    MESSAGE buf2;
    receiveMessage(0, &buf1);
    receiveMessage(1, &buf2);
    if(buf1.payload.asUint == 4711 || buf2.payload.asUint == 4711){
        led_high();
    }
};

T_JOB initJobTable[NUM_INIT_JOBS] = {
        {.start_time = 0, .stop_time = 0, .job_function = &initDB },
        {.start_time = 100, .stop_time = 0, .job_function = &initSerial },
        {.start_time = 200, .stop_time = 0, .job_function = &initLed },
        {.start_time = 300, .stop_time = 0, .job_function = &initPoti },
        {.start_time = 400, .stop_time = 0, .job_function = &init_spy },
        {.start_time = 500, .stop_time = 900, .job_function = &led_high },
        {.start_time = 900, .stop_time = 0, .job_function = &rs485Init },
};
T_JOB runJobTable[NUM_JOBS] = {
        {.start_time = 0, .stop_time = 50, .job_function = &sendRs485 },
        {.start_time = 100, .stop_time = 150, .job_function = &rcvRs485 },
        {.start_time = 200, .stop_time = 400, .job_function = &led_low },
        {.start_time = 400, .stop_time = 600, .job_function = &led_low },
        {.start_time = 600, .stop_time = 800, .job_function = &led_low },
        {.start_time = 800, .stop_time = 0, .job_function = &reset_time },
};


T_JOB runJobTable2[NUM_JOBS] = {
        {.start_time = 0, .stop_time = 0, .job_function = &job_xsynchro },
        {.start_time = 100, .stop_time = 0, .job_function = &reset_time },
        {.start_time = 200, .stop_time = 0, .job_function = &led_high },
        {.start_time = 300, .stop_time = 0, .job_function = &led_low },
        {.start_time = 400, .stop_time = 0, .job_function = &led_high },
        {.start_time = 500, .stop_time = 0, .job_function = &readPoti },
};



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
    //Serial.println("Looping\n");

}

