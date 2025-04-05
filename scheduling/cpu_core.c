#include <stdio.h>
#include <unistd.h>
#include "cpu_core.h"


void do_work(Task *t)
{
        printf("Doing work - Task ID: %s - Duration: %d\n", t->task_id, t->duration);
        sleep(t->duration);
}
