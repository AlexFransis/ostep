#ifndef GUARD_task_h
#define GUARD_task_h

#include <stdbool.h>

struct Task;
typedef struct Task
{
        char* task_id;
        char* task_name;
        unsigned int duration;
        unsigned int arrival_time;
        bool is_completed;
} Task;

void free_task(Task* t);

#endif
