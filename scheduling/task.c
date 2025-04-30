#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"

#define UUID_MAX_LENGTH 4
#define TASK_MAX_DURATION 4 // in seconds


Task create_task(int index)
{
        Task t;
        t.task_id = index;
        t.last_ran = 0;
        t.turnaround = 0;
        t.wait = 0;
        t.response = -1;
        t.duration = rand() % TASK_MAX_DURATION + 1;

        return t;
}
