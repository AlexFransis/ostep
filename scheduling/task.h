#ifndef GUARD_task_h
#define GUARD_task_h

#include <stdbool.h>

struct Task;
typedef struct Task
{
        int task_id;
        double duration;
        double last_ran;
        double turnaround;
        double wait;
        double response;
} Task;

Task create_task(int index);

#endif
