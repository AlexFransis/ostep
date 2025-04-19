#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue.h"
#include "cpu_core.h"
#include "task.h"

#define UUID_MAX_LENGTH 4
#define TASK_MAX_DURATION 3 // in seconds


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
        t->duration = rand() % TASK_MAX_DURATION;
        t->task_id = uuid;
};


void start_fifo_scheduler(int nb_of_tasks)
{
        // create queue
        TaskQueue tq = init_empty_queue(nb_of_tasks);

        // begin queuing tasks
        for (int i = 0; i < nb_of_tasks; ++i) {
                // create fake task
                Task* t = malloc(sizeof(Task));
                generate_task(t);
                queue(t, &tq);
        }

        // begin fifo scheduling
        while (tq.size > 0) {
                Task* t = dequeue(&tq);
                do_work(t);
                free_task(t);
        }
}
