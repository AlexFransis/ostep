#include <stddef.h>
#include <stdlib.h>
#include "queue.h"
#include "task.h"


TaskQueue init_empty_queue(unsigned int max_size)
{
        TaskQueue tq;
        tq.size = 0;
        tq.max_size = max_size;
        tq.task_list = malloc(sizeof(Task*) * max_size);

        return tq;
};

bool queue(Task* t, TaskQueue* tq)
{
        if (is_full(tq)) {
                return false;
        }

        Task** task_list = tq->task_list;
        task_list += tq->size; // move to last element
        *task_list = t;
        tq->size += 1;

        return true;
};

Task* dequeue(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        Task* t = head(tq);
        // move all array elements forward by 1
        for (int i = 0; i <= tq->size - 1; i++) {
                Task* next = tq->task_list[i+1];
                tq->task_list[i] = next;
        }
        tq->size -= 1;

        return t;
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

void free_queue(TaskQueue *tq)
{
        for (int i = 0; i < tq->size; ++i) {
                Task* task_to_free = *(tq->task_list + i);
                free_task(task_to_free);
        }

        free(tq);
}
