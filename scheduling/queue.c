#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "task.h"


bool is_empty(TaskQueue *tq)
{
        return tq->size == 0;
}

bool is_full(TaskQueue *tq)
{
        return tq->size == tq->max_size;
}

TaskQueue* init_empty_queue(unsigned int max_size)
{
        TaskQueue* tq = malloc(sizeof(TaskQueue));
        if (tq == NULL) {
                return NULL;
        }

        tq->size = 0;
        tq->max_size = max_size;
        tq->task_list = malloc(sizeof(Task*) * max_size);

        if (tq->task_list == NULL) {
                free(tq);
                return NULL;
        }

        return tq;
}

bool enqueue(Task* t, TaskQueue* tq)
{
        if (!t || !tq || !tq->task_list) {
                return false;
        }

        if (is_full(tq)) {
                return false;
        }

        tq->task_list[tq->size] = t;
        tq->size += 1;

        return true;
}

Task* dequeue(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        Task* t = head(tq);
        // move all array elements forward by 1
        for (unsigned int i = 0; i < tq->size - 1; i++) {
                Task* next = tq->task_list[i+1];
                tq->task_list[i] = next;
        }

        tq->size -= 1;

        return t;
}

Task* head(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        return tq->task_list[0];
}

Task* tail(TaskQueue* tq)
{
        if (is_empty(tq)) {
                return NULL;
        }

        return tq->task_list[tq->size-1];
}

void free_queue(TaskQueue *tq)
{
        for (unsigned int i = 0; i < tq->size; ++i) {
                free(tq->task_list[i]->task_id);
        }

        free(tq->task_list);
        free(tq);
}
