#include "fifo.h"
#include "queue.h"


void schedule_task(Task *t, TaskQueue* tq)
{
        queue(t, tq);
}
