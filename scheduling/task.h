#ifndef GUARD_task_h
#define GUARD_task_h

#include <stdbool.h>

typedef struct
{
        int task_id;
        double duration;
        double last_ran;
        double turnaround;
        double wait;
        double response;
        double arrival_time;
        double preemption_limit;
} Task;

Task* create_task(int index);
double generate_exponential_time(double lambda);

#endif
