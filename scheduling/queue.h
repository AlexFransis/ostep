#ifndef GUARD_queue_h
#define GUARD_queue_h

#include <stdbool.h>
#include "task.h"


struct TaskQueue;
typedef struct TaskQueue {
        unsigned int size;
        unsigned int max_size;
        Task** task_list;
} TaskQueue;

TaskQueue* init_empty_queue(unsigned int max_size);
bool enqueue(Task* t, TaskQueue* tq);
Task* dequeue(TaskQueue* tq);
Task* head(TaskQueue* tq);
Task* tail(TaskQueue* tq);

void free_queue(TaskQueue* tq);

#endif
