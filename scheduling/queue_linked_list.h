#ifndef GUARD_queue_linked_list_h
#define GUARD_queue_linked_list_h

#include <stdbool.h>
#include "task.h"

struct TaskNode;
typedef struct TaskNode {
        Task task;
        struct TaskNode* next;
} TaskNode;

struct TaskQueue;
typedef struct TaskQueue {
        unsigned int size;
        unsigned int max_size;
        TaskNode* head;
        TaskNode* tail;
} TaskQueue;

bool enqueue(Task* t, TaskQueue* tq);
Task dequeue(TaskQueue* tq);

TaskQueue* init_empty_queue(unsigned int max_size);
void free_queue(TaskQueue* tq);

#endif
