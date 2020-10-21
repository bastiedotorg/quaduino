//
// Created by bastie on 10/21/20.
//

#ifndef QUADIUNO_SCHEDULER_H
#define QUADIUNO_SCHEDULER_H
typedef struct job {
    unsigned long start_time;
    unsigned long stop_time;
    void (* job_function)();
} T_JOB;

void runScheduler(const T_JOB* jobs, long num_jobs);
#endif //QUADIUNO_SCHEDULER_H
