#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue.h"
#include "task.h"
#include "quicksort.h"

#define QUANTUM 1


void start_fifo_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);
        Task* tasks = (Task*) malloc(task_count * sizeof(Task));

        if (tasks == NULL) {
                // handle error
        }

        // begin queuing tasks
        for (int i = 0; i < task_count; ++i) {
                // create task
                generate_task(&tasks[i]);
                enqueue(&tasks[i], tq);
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin fifo scheduling
        while (tq->size > 0) {
                Task* t = dequeue(tq);
                // print stats
                printf("  [ time %.2f ] JOB ID (%s) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
                       time, t->task_id, t->duration, time, time+t->duration, time);

                time += t->duration;
                response_sum += time;
                turnaround_sum += time;
                wait_sum += time;
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
        free(tasks);
}

void start_sjf_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

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
                enqueue(&tasks[i], tq);
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin sjf scheduling
        while (tq->size > 0) {
                Task* t = dequeue(tq);
                // print statistics
                printf("  [ time %.2f ] JOB ID (%s) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
                       time, t->task_id, t->duration, time, time+t->duration, time);

                time += t->duration;
                response_sum += time;
                turnaround_sum += time;
                wait_sum += time;
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
        free(tasks);
}

void start_rr_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

        // begin creating tasks and sorting them
        Task* tasks = (Task*) malloc(task_count * sizeof(Task));
        if (tasks == NULL) {
                // handle error
        }

        for (int i = 0; i < task_count; ++i) {
                generate_task(&tasks[i]);
                enqueue(&tasks[i], tq);
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin rr scheduling
        while (tq->size > 0) {
                Task* t = dequeue(tq);

                if (t->response == -1) {
                        t->response = time;
                }

                double current_wait = time - t->last_ran;
                double ran_for = 0;
                t->wait += current_wait;

                if (t->duration > QUANTUM) {
                        t->duration -= QUANTUM;
                        ran_for = QUANTUM;
                        printf("  [ time %.2f ] JOB ID (%s) -- run job for %.2f\n", time, t->task_id, ran_for);
                        enqueue(t, tq);
                } else {
                        ran_for = t->duration;
                        t->turnaround = time + ran_for;
                        printf("  [ time %.2f ] JOB ID (%s) -- run job for %.2f -- (DONE at %.2f)\n",
                               time, t->task_id, ran_for, t->turnaround);

                        // task is complete, add to final statistics
                        response_sum += t->response;
                        turnaround_sum += t->turnaround;
                        wait_sum += t->wait;
                }

                time += ran_for;
                t->last_ran = time;
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
        free(tasks);
}
