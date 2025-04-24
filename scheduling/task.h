#ifndef GUARD_task_h
#define GUARD_task_h

#include <stdbool.h>

struct Task;
typedef struct Task
{
        char* task_id;
        unsigned int duration;
        bool is_completed;
} Task;

void free_task(Task* t);

#endif
