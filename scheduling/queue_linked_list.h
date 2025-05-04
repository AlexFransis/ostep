#ifndef GUARD_queue_linked_list_h
#define GUARD_queue_linked_list_h

#include <stdbool.h>
#include "task.h"

typedef struct TaskNode {
        Task* task;
        struct TaskNode* next;
} TaskNode;

typedef struct {
        unsigned int size;
        unsigned int max_size;
        TaskNode* head;
        TaskNode* tail;
} TaskQueue;

typedef struct {
        unsigned size;
        unsigned queue_count;
        TaskQueue** queues;
} MLFQ;

bool enqueue(Task* t, TaskQueue* tq);
bool mlfq_enqueue(Task* t, MLFQ* mlfq, int queue_priority);
Task* dequeue(TaskQueue* tq);
Task* mlfq_dequeue(MLFQ* mlfq, int queue_priority);

TaskQueue* init_empty_queue(unsigned int max_size);
void free_queue(TaskQueue* tq);
MLFQ* init_empty_mlfq(unsigned queue_count, unsigned task_count);

#endif
