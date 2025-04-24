#ifndef GUARD_scheduler_h
#define GUARD_scheduler_h

#include "task.h"

void start_fifo_scheduler(int task_count);
void start_sjf_scheduler(int task_count);
void generate_task(Task* t);
void generate_uuid(char*, unsigned int length);

#endif
