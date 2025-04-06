#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "scheduler.h"

int main(int argc, char** argv)
{
        if (argc < 2) {
                printf("Usage: ./main <scheduling_policy> <number_of_tasks>? <seed>?\n");
                return 0;
        }

        char* strategy = argv[1];
        int nb_of_tasks = 10;
        int seed = 1;
        if (argc >= 3) {
                nb_of_tasks = atoi(argv[2]);
        }
        if (argc >= 4) {
                seed = atoi(argv[3]);
        }

        srand(seed);
        if (strcmp(strategy, "fifo") == 0) {
                start_fifo_scheduler(nb_of_tasks);
        }


        return 0;

}
