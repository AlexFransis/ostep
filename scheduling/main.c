#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "scheduler.h"

int main(int argc, char** argv)
{
        if (argc != 4) {
                printf("Usage: ./main <scheduling_policy> <number_of_tasks> <seed>\n");
                return 0;
        }

        char* strategy = argv[1];
        int nb_of_tasks = atoi(argv[2]);
        int seed = atoi(argv[3]);

        if (strcmp(strategy, "fifo") == 0) {
                srand(seed);
                start_scheduler(FIFO, nb_of_tasks);
        }


        return 0;

}
