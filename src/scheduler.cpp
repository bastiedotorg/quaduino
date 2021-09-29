//
// Created by bastie on 10/21/20.
//
#include <Arduino.h>
#include "ostime.h"
#include "scheduler.h"

/**
 *
 *
 * @param jobs
 * @param num_jobs
 */
void runScheduler(const T_JOB* jobs, long num_jobs) {
    int service;
    for (service = 0; service < num_jobs; service++) {
        while (get_time() < jobs[service].start_time) {
            delay(1);
        }
        jobs[service].job_function();
        while (get_time() < jobs[service].stop_time) {
            delay(1);
        }
    }
}