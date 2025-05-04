#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "queue_linked_list.h"


MLFQ* init_empty_mlfq(unsigned queue_count, unsigned task_count)
{
        MLFQ* mlfq = malloc(sizeof(MLFQ));
        if (mlfq == NULL) {
                fprintf(stderr, "Failed to allocate memory for MLFQ");
                exit(EXIT_FAILURE);
        }

        mlfq->size = 0;
        mlfq->queue_count = queue_count;
        mlfq->queues = malloc(sizeof(TaskQueue*) * queue_count);
        if (mlfq->queues == NULL) {
                fprintf(stderr, "Failed to allocate memory for MLFQ");
                free(mlfq);
                exit(EXIT_FAILURE);
        }

        for (int i = 0; i < queue_count; ++i) {
                mlfq->queues[i] = init_empty_queue(task_count);
        }

        return mlfq;
}

TaskNode* init_empty_task_node()
{
        TaskNode* task_node = malloc(sizeof(TaskNode));
        if (task_node == NULL) {
                fprintf(stderr, "Failed to create empty task node");
                return NULL;
        }

        task_node->next = NULL;

        return task_node;
}

TaskQueue* init_empty_queue(unsigned int max_size)
{
        TaskQueue* tq = malloc(sizeof(TaskQueue));
        if (tq == NULL) {
                fprintf(stderr, "Failed to create task queue");
                exit(EXIT_FAILURE);
        }
        tq->head = NULL;
        tq->tail = NULL;
        tq->max_size = max_size;
        tq->size = 0;

        return tq;
}

bool enqueue(Task* t, TaskQueue* tq)
{
        if (tq->size >= tq->max_size) {
                return false;
        }

        TaskNode* node = init_empty_task_node();
        node->task = t;
        // first enqueue
        if (tq->tail == NULL || tq->head == NULL) {
                tq->head = node;
                tq->tail = node;
        } else {
                tq->tail->next = node;
                tq->tail = node;
        }

        tq->size += 1;

        return true;
}

Task* dequeue(TaskQueue* tq)
{
        if (tq->head == NULL) {
                return NULL;
        }
        TaskNode* old_head = tq->head;
        Task* task = old_head->task;
        tq->head = old_head->next;
        free(old_head);
        tq->size -= 1;

        return task;
}

Task* mlfq_dequeue(MLFQ* mlfq, int queue_priority)
{
        if (queue_priority > mlfq->queue_count) {
                return NULL;
        }
        Task* task = dequeue(mlfq->queues[queue_priority]);
        mlfq->size--;

        return task;
}

bool mlfq_enqueue(Task* task, MLFQ* mlfq, int queue_priority)
{
        if (queue_priority > mlfq->queue_count) {
                return false;
        }

        if (enqueue(task, mlfq->queues[queue_priority])) {
                mlfq->size++;

                return true;
        }

        return false;
}

void free_queue(TaskQueue* tq)
{
        TaskNode* current = tq->head;
        while (current != NULL) {
                TaskNode* next = current->next;
                free(current->task);
                free(current);
                current = next;
        }

        free(tq);
}

void free_mlfs(MLFQ* mlfq)
{
        for (int i = 0; i < mlfq->queue_count; i++) {
                free_queue(mlfq->queues[i]);
        }

        free(mlfq);
}
