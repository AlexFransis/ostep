#include <stddef.h>
#include <stdlib.h>
#include "queue.h"


TaskQueue init_empty_queue(unsigned int max_size)
{
        TaskQueue tq;
        tq.size = 0;
        tq.max_size = max_size;
        tq.task_list = malloc(sizeof(Task*) * max_size);

        return tq;
};

void queue(Task* t, TaskQueue* tq)
{
        if (!is_full(tq)) {
                Task** queue = tq->task_list;
                queue += tq->size;
                *queue = t;
                tq->size += 1;
        }
};

Task* dequeue(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        Task** task_list = tq->task_list;
        Task* head = *task_list;
        tq->size -= 1;

        // move all array elements forward by 1
        for (int i = 0; i < tq->size; i++) {
                *(task_list + i) = *(task_list + i + 1);
        }

        return head;
};

bool is_empty(TaskQueue *tq)
{
        return tq->size == 0;
};

bool is_full(TaskQueue *tq)
{
        return tq->size == tq->max_size;
};

Task* head(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        Task** queue = tq->task_list;
        return *queue;
};

Task* tail(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        Task** queue = tq->task_list;
        return *(queue + tq->size - 1);
};
