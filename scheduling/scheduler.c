#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue_linked_list.h"
#include "task.h"
#include "quicksort.h"

#define QUANTUM 1


void start_fifo_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

        // begin queuing tasks
        for (int i = 0; i < task_count; ++i) {
                // create task
                Task t = create_task(i);
                enqueue(&t, tq);
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin fifo scheduling
        while (tq->size > 0) {
                Task t = dequeue(tq);
                // print stats
                printf("  [ time %.2f ] JOB ID (%d) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
                       time, t.task_id, t.duration, time, time+t.duration, time);

                time += t.duration;
                response_sum += time;
                turnaround_sum += time;
                wait_sum += time;
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
}

void start_sjf_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

        // create array to sort tasks
        Task* tasks = (Task*) malloc(task_count * sizeof(Task));
        if (tasks == NULL) {
                // handle error
        }

        for (int i = 0; i < task_count; ++i) {
                // create task
                tasks[i] = create_task(i);
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
                Task t = dequeue(tq);
                // print statistics
                printf("  [ time %.2f ] JOB ID (%d) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
                       time, t.task_id, t.duration, time, time+t.duration, time);

                time += t.duration;
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

        for (int i = 0; i < task_count; ++i) {
                Task t = create_task(i);
                enqueue(&t, tq);
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin rr scheduling
        while (tq->size > 0) {
                Task task = dequeue(tq);

                if (task.response == -1) {
                        task.response = time;
                }

                double current_wait = time - task.last_ran;
                double ran_for = 0;
                task.wait += current_wait;

                if (task.duration > QUANTUM) {
                        task.duration -= QUANTUM;
                        ran_for = QUANTUM;
                        printf("  [ time %.2f ] JOB ID (%d) -- run job for %.2f\n", time, task.task_id, ran_for);
                        enqueue(&task, tq);
                } else {
                        ran_for = task.duration;
                        task.turnaround = time + ran_for;
                        printf("  [ time %.2f ] JOB ID (%d) -- run job for %.2f -- (DONE at %.2f)\n",
                               time, task.task_id, ran_for, task.turnaround);

                        // task is complete, add to final statistics
                        response_sum += task.response;
                        turnaround_sum += task.turnaround;
                        wait_sum += task.wait;
                }

                time += ran_for;
                task.last_ran = time;
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
}
