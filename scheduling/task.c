#include <stdlib.h>
#include <string.h>
#include "task.h"

#define UUID_MAX_LENGTH 4
#define TASK_MAX_DURATION 4 // in seconds

void free_task(Task* t)
{
        if (t) {
                free(t->task_id);
                free(t);
        }
}

void free_task_list(Task* t, unsigned len)
{
        for (unsigned i = 0; i < len; ++i) {
                free((t+i)->task_id);
        }

        free(t);
}

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
        t->task_id = malloc((UUID_MAX_LENGTH + 1) * sizeof(char));
        if (t->task_id == NULL) {
                exit(EXIT_FAILURE);
                /* add error handling */
        }

        generate_uuid(t->task_id, UUID_MAX_LENGTH);
        t->duration = rand() % TASK_MAX_DURATION + 1;
        t->last_ran = 0;
        t->turnaround = 0;
        t->wait = 0;
        t->response = -1;
};
