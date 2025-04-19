#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "scheduler.h"

typedef void (*scheduler_func)(int);
struct scheduler_entry
{
        const char *name;
        scheduler_func func;
};

struct scheduler_entry schedulers[] =
{
        {"fifo", start_fifo_scheduler},
        // add schedulers here

        {NULL, NULL} // sentinel
};

void print_usage()
{
        printf("Usage: ./main <scheduling_policy> <number_of_tasks>? <seed>?\n");
        printf("  scheduling_policy: Strategy to use (fifo)\n");
        printf("  seed: Random seed for reproducibility (default: current time)\n");
        printf("  number_of_tasks: Number of tasks to simulate (default: 10)\n");
};

int main(int argc, char** argv)
{
        if (argc < 2) {
                print_usage();

                return EXIT_FAILURE;
        }

        char* strategy = argv[1];

        int seed = (int) time(NULL);
        if (argc >= 3) {
                seed = atoi(argv[2]);
        }

        int task_count = 10;
        if (argc >= 4) {
                task_count = atoi(argv[3]);
                if (task_count <= 0) {
                        printf("Invalid number of tasks\n");
                        return EXIT_FAILURE;
                }

        }

        srand(seed);
        struct scheduler_entry *entry = schedulers;
        while (entry->name != NULL) {
                if (strcmp(strategy, entry->name) == 0) {
                        entry->func(task_count);
                        return EXIT_SUCCESS;
                }

                entry++;
        }

        printf("Unknown scheduling policy: %s\n", strategy);

        return EXIT_FAILURE;
}
