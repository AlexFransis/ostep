#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "scheduler.h"
#include "queue_linked_list.h"
#include "task.h"
#include "quicksort.h"

#ifndef QUANTUM
#define QUANTUM 0.5
#endif

#ifndef PRIORITY_BOOST
#define PRIORITY_BOOST 10
#endif

#ifndef LAMBDA
#define LAMBDA 0.6
#endif

void start_fifo_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

        // begin queuing tasks
        for (int i = 0; i < task_count; ++i) {
                // create task
                Task* t = create_task(i);
                enqueue(t, tq);
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
                printf("  [ time %.2f ] JOB ID (%d) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
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
}

void start_sjf_scheduler(int task_count)
{
        // create queue
        TaskQueue* tq = init_empty_queue(task_count);

        // create array to sort tasks
        Task** tasks = malloc(task_count * sizeof(Task*));
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
                enqueue(tasks[i], tq);
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
                printf("  [ time %.2f ] JOB ID (%d) -- duration: %.2f -- response: %.2f secs -- turnaround: %.2f secs -- wait: %.2f secs\n",
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

        double* task_arrival_times = malloc(sizeof(double) * task_count);
        double next_arrival = 0.0;
        for (int i = 0; i < task_count; ++i) {
                double inter_arrival = generate_exponential_time(LAMBDA);
                next_arrival += inter_arrival;
                task_arrival_times[i] = next_arrival;
        }

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        // begin rr scheduling
        int i = 0;
        while (tq->size > 0 || i < task_count) {
                // simulate random arrival of tasks
                while (task_arrival_times[i] < time && i < task_count) {
                        Task* t = create_task(i);
                        t->arrival_time = time;
                        enqueue(t, tq);
                        ++i;
                        printf("  [ time %.2f ] NEW JOB QUEUED -- JOB ID (%d) -- duration: %.2f\n",
                                time, t->task_id, t->duration);
                }

                if (tq->size > 0) {

                        Task* task = dequeue(tq);

                        if (task->response == -1) {
                                task->response = time - task->arrival_time;
                        }

                        double current_wait = time - task->last_ran;
                        double ran_for = 0.0;
                        task->wait += current_wait;

                        if (task->duration > QUANTUM) {
                                task->duration -= QUANTUM;
                                ran_for = QUANTUM;
                                printf("  [ time %.2f ] JOB ID (%d) -- run job for %.2f -- remaining: %.2f\n",
                                       time, task->task_id, ran_for, task->duration);

                                // requeue
                                enqueue(task, tq);
                        } else {
                                ran_for = task->duration;
                                task->turnaround = (time + ran_for - task->arrival_time);
                                printf("  [ time %.2f ] JOB ID (%d) -- run job for %.2f -- (DONE at %.2f)\n",
                                       time, task->task_id, ran_for, time+ran_for);

                                // task is complete, add to final statistics and free
                                response_sum += task->response;
                                turnaround_sum += task->turnaround;
                                wait_sum += task->wait;

                                free(task);
                        }

                        time += ran_for;
                        task->last_ran = time;
                } else {
                        printf("  [ time %.2f ] WAITING FOR JOBS\n", time);
                        time += 1;
                }
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

        free_queue(tq);
}

void boost_tasks_priority(MLFQ* mlfq)
{
        for (int i = mlfq->queue_count - 1; i > 0; --i) {
                if (mlfq->size > 0) {
                        while (mlfq->queues[i]->size > 0) {
                                Task* t = mlfq_dequeue(mlfq, i);
                                t->preemption_limit = 1;
                                mlfq_enqueue(t, mlfq, 0);
                        }
                }
        }
}

void start_mlfq_scheduler(int task_count)
{
        // create 3 queue priority
        MLFQ* mlfq = init_empty_mlfq(3, task_count);

        // simulate task arrival times
        double* task_arrival_times = malloc(sizeof(double) * task_count);
        double next_arrival = 0.0;
        for (int i = 0; i < task_count; ++i) {
                double inter_arrival = generate_exponential_time(LAMBDA);
                next_arrival += inter_arrival;
                task_arrival_times[i] = next_arrival;
        }

        double quanta[] = {
                QUANTUM,
                QUANTUM * 5,
                QUANTUM * 10
        };

        // for statistics
        double time = 0.0;
        double turnaround_sum = 0.0;
        double wait_sum = 0.0;
        double response_sum = 0.0;

        int task_index = 0;
        int last_boost_time = 0;
        double ran_for = 0;
        while (task_index < task_count || mlfq->size > 0) {
                // start with top priority
                unsigned int i = 0;
                while (i < mlfq->queue_count) {
                        // generate random job that enters enters the queue
                        while (task_index < task_count && task_arrival_times[task_index] < time) {
                                Task* t = create_task(task_index);
                                t->arrival_time = time;
                                mlfq_enqueue(t, mlfq, 0);
                                task_index++;
                                printf("  [ time %.2f ] NEW JOB QUEUED -- JOB ID (%d) -- duration: %.2f\n",
                                       time, t->task_id, t->duration);

                                // set queue index to top priority
                                i = 0;
                        }

                        if (mlfq->queues[i]->size > 0) {
                                if (last_boost_time + PRIORITY_BOOST <= time) {
                                        printf("  [ time %.2f ] boosting priority of all jobs\n", time);
                                        boost_tasks_priority(mlfq);
                                        // reset to top priority queue
                                        i = 0;
                                        last_boost_time = time;
                                }

                                // if there are jobs in higher priority queues switch to that queue
                                if (i != 0) {
                                        for (unsigned int j = 0; j < i; ++j) {
                                                if (mlfq->queues[j]->size > 0) {
                                                        i = j;
                                                        break;
                                                }
                                        }
                                }

                                Task* task = mlfq_dequeue(mlfq, i);

                                if (task->response == -1) {
                                        task->response = time - task->arrival_time;
                                }

                                double current_wait = time - task->last_ran;
                                task->wait += current_wait;

                                double quantum = quanta[i];
                                if (task->duration > quantum) {
                                        task->duration -= quantum;
                                        ran_for = quantum;
                                        if (task->preemption_limit > 0) {
                                                task->preemption_limit--;
                                                printf("  [ time %.2f ] JOB ID (%d) -- PRIORITY (%d) -- run job for %.2f\n",
                                                       time, task->task_id, i, ran_for);
                                                mlfq_enqueue(task, mlfq, i);

                                        } else if (i == mlfq->queue_count - 1) {
                                                printf("  [ time %.2f ] JOB ID (%d) -- PRIORITY (%d) -- run job for %.2f\n",
                                                       time, task->task_id, i, ran_for);
                                                mlfq_enqueue(task, mlfq, i);
                                        } else {
                                                printf("  [ time %.2f ] JOB ID (%d) -- PRIORITY (%d) -- run job for %.2f -- reducing job priority\n",
                                                       time, task->task_id, i, ran_for);
                                                mlfq_enqueue(task, mlfq, i+1);
                                        }
                                } else {
                                        ran_for = task->duration;
                                        task->turnaround = (time + ran_for - task->arrival_time);
                                        printf("  [ time %.2f ] JOB ID (%d) -- PRIORITY (%d) -- run job for %.2f -- (DONE at %.2f)\n",
                                               time, task->task_id, i, ran_for, time+ran_for);

                                        // task is complete, add to final statistics and free
                                        response_sum += task->response;
                                        turnaround_sum += task->turnaround;
                                        wait_sum += task->wait;

                                        free(task);
                                }

                                time += ran_for;
                                task->last_ran = time;
                        }
                        ++i;
                }

                if (task_index < task_count && mlfq->size == 0) {
                        time++;
                }
        }

        printf("AVERAGE RUN -- TOTAL TASK: %d\n", task_count);
        printf(" avg response: %.2f -- avg turnaroud: %.2f -- avg wait: %.2f\n",
               response_sum/task_count, turnaround_sum/task_count, wait_sum/task_count);

}
