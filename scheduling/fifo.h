#ifndef GUARD_fifo_h
#define GUARD_fifo_h

#include "queue.h"

TaskQueue init_fifo_scheduler();
void schedule_task(Task* t, TaskQueue* tq);


#endif
