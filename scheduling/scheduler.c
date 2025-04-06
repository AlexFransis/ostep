#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scheduler.h"
#include "queue.h"
#include "cpu_core.h"
#include "task.h"


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
        const int uuid_size = 4;
        const int max_duration = 3; // in seconds
        char* uuid = (char*) malloc(uuid_size * sizeof(char));
        generate_uuid(uuid, uuid_size);
        t->duration = rand() % max_duration;
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
