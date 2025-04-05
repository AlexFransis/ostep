#ifndef GUARD_scheduler_h
#define GUARD_scheduler_h

#include "task.h"

typedef enum SchedulingPolicy {
        FIFO,
} SchedulingPolicy;

void start_scheduler(SchedulingPolicy policy, int nb_of_tasks);
void generate_task(Task* t);
void generate_uuid(char*, unsigned int length);

#endif
