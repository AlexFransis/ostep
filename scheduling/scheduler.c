#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue.h"
#include "task.h"
#include "quicksort.h"

#define UUID_MAX_LENGTH 4
#define TASK_MAX_DURATION 20 // in seconds


void generate_uuid(char* uuid, unsigned int length)
{
        const char* alphanumeric = "0123456789abcdefghijklmnopqrstuvwxyz";
        const long alphanumeric_len = strlen(alphanumeric);

        for (unsigned int i = 0; i < length; ++i) {
                int random = rand() % alphanumeric_len;
                uuid[i] = alphanumeric[random];
        }

        uuid[length] = '\0';
};

void generate_task(Task* t)
{
        char* uuid = (char*) malloc(UUID_MAX_LENGTH * sizeof(char));
        if (uuid == NULL) {
                /* add error handling */
        }

        generate_uuid(uuid, UUID_MAX_LENGTH);
        t->duration = rand() % TASK_MAX_DURATION + 1;
        t->task_id = uuid;
};


void start_fifo_scheduler(int task_count)
{
        // create queue
        TaskQueue tq = init_empty_queue(task_count);

        // begin queuing tasks
        for (int i = 0; i < task_count; ++i) {
                // create task
                Task* t = malloc(sizeof(Task));
                generate_task(t);
                queue(t, &tq);
        }

        // for statistics
        unsigned time = 0;
        unsigned turnaround_sum = 0;
        unsigned wait_sum = 0;
        unsigned response_sum = 0;

        // begin fifo scheduling
        while (tq.size > 0) {
                Task* t = dequeue(&tq);
                // print stats
                printf("JOB ID %s -- duration: %d", t->task_id, t->duration);
                printf("  response: %d secs -- turnaround: %d secs -- wait: %d secs\n", time, time+t->duration, time);

                time += t->duration;
                response_sum += time;
                turnaround_sum += time;
                wait_sum += time;

                free_task(t);
        }

        printf("AVERAGE RUN\n");
        printf("  response: %d -- turnaroud: %d -- wait: %d\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);
}

void start_sjf_scheduler(int task_count)
{

        // create queue
        TaskQueue tq = init_empty_queue(task_count);

        // begin creating tasks and sorting them
        Task* tasks = (Task*) malloc(task_count * sizeof(Task));
        if (tasks == NULL) {
                // handle error
        }

        for (int i = 0; i < task_count; ++i) {
                // create task
                generate_task(&tasks[i]);
        }

        // sort task by ascending order of task duration
        sort_tasks(tasks, task_count);

        // queue tasks
        for (int i = 0; i < task_count; ++i) {
                queue(&tasks[i], &tq);
        }

        // for statistics
        unsigned time = 0;
        unsigned turnaround_sum = 0;
        unsigned wait_sum = 0;
        unsigned response_sum = 0;

        // begin sjf scheduling
        while (tq.size > 0) {
                Task* t = dequeue(&tq);
                // print statistics
                printf("JOB ID %s -- duration: %d", t->task_id, t->duration);
                printf("  response: %d secs -- turnaround: %d secs -- wait: %d secs\n", time, time+t->duration, time);

                time += t->duration;
                response_sum += time;
                turnaround_sum += time;
                wait_sum += time;

                free(t->task_id);
        }

        printf("AVERAGE RUN\n");
        printf("  response: %d -- turnaroud: %d -- wait: %d\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free(tasks);
}
