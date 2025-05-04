#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "task.h"

#define MEAN_DURATION 6.0


double generate_exponential_time(double lambda)
{
        double u = ((double) rand() / (RAND_MAX));
        return -log(1 - u) / lambda;
}

Task* create_task(int index)
{
        Task* t = malloc(sizeof(Task));
        if (t == NULL) {
                fprintf(stderr, "Failed to allocate memory for Task\n");
                exit(EXIT_FAILURE);
        }

        t->task_id = index;
        t->last_ran = 0.0;
        t->turnaround = 0.0;
        t->wait = 0.0;
        t->response = -1;
        t->arrival_time = -1;
        t->preemption_limit = 1;
        t->duration = generate_exponential_time(1.0 / MEAN_DURATION);

        return t;
}
