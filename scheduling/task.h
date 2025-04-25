#ifndef GUARD_task_h
#define GUARD_task_h

#include <stdbool.h>

struct Task;
typedef struct Task
{
        char* task_id;
        double duration;
        double last_ran;
        double turnaround;
        double wait;
        double response;
} Task;

void free_task(Task* t);
void free_task_list(Task* t, unsigned len);
void generate_task(Task *t);

#endif
