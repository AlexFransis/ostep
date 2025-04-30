#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "queue_linked_list.h"


TaskNode* init_empty_task_node()
{
        TaskNode* task_node = malloc(sizeof(TaskNode));
        if (task_node == NULL) {
                printf("Failed to create empty task node");
                return NULL;
        }

        task_node->next = NULL;

        return task_node;
}

TaskQueue* init_empty_queue(unsigned int max_size)
{
        TaskQueue* tq = malloc(sizeof(TaskQueue));
        if (tq == NULL) {
                printf("Failed to create task queue");
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
        node->task = *t;
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

Task dequeue(TaskQueue* tq)
{
        if (tq->head == NULL) {
                Task empty = {0};
                return empty;
        }
        TaskNode* old_head = tq->head;
        Task task = old_head->task;
        tq->head = old_head->next;
        free(old_head);
        tq->size -= 1;

        return task;
}

void free_queue(TaskQueue* tq)
{
        TaskNode* current = tq->head;
        while (current != NULL) {
                TaskNode* next = current->next;
                free(&(current->task));
                free(current);
                current = next;
        }

        free(tq);
}
