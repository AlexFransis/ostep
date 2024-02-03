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

void queue(Task* t, TaskQueue* tq);
Task* dequeue(TaskQueue* tq);
bool is_empty(TaskQueue* tq);
bool is_full(TaskQueue* tq);
void init_empty_queue(TaskQueue* tq, unsigned int max_size);
Task* head(TaskQueue* tq);
Task* tail(TaskQueue* tq);

#endif
