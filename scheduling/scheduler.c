#include <stdlib.h>
#include <string.h>
#include "scheduler.h"


void generate_uuid(char* uuid, int length)
{
        const char* alphanumeric = "0123456789abcdefghijklmnopqrstuvwxyz";

        for (int i = 0; i < length; ++i) {
                int random = rand() & strlen(alphanumeric);
                uuid[i] = alphanumeric[i];
        }

        uuid[length] = '\0';
};

Task* create_task(unsigned int duration)
{
        Task* t = malloc(sizeof(Task));
        t->duration = duration;
        t->task_id = rand();
};
