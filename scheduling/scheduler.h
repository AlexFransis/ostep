#ifndef GUARD_scheduler_h
#define GUARD_scheduler_h

#include "task.h"

void start_fifo_scheduler(int nb_of_tasks);
void generate_task(Task* t);
void generate_uuid(char*, unsigned int length);

#endif
