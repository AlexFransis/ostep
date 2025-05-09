#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scheduler.h"

typedef void (*scheduler_func)(int);
struct scheduler_entry
{
        const char* name;
        scheduler_func func;
};

struct scheduler_entry schedulers[] =
{
        {"fifo", start_fifo_scheduler},
        {"sjf", start_sjf_scheduler},
        {"rr", start_rr_scheduler},
        {"mlfq", start_mlfq_scheduler},
        // add schedulers here

        {NULL, NULL} // sentinel
};

void print_usage()
{
        printf("Usage: ./main <scheduling_policy> <number_of_tasks>? <seed>? <quantum>? <p_boost>? <lambda>?\n");
        printf("  scheduling_policy: Strategy to use fifo, sjf, rr\n");
        printf("  number_of_tasks: Number of tasks to simulate (default: 10)\n");
        printf("  seed: Random seed for reproducibility (default: current time)\n");
        printf("  quantum: duration slice for each task\n");
        printf("  p_boost: priority boost interval\n");
        printf("  lambda: used to simulate arrival times and task duration\n");
};

int main(int argc, char** argv)
{
        if (argc < 2) {
                print_usage();

                return EXIT_FAILURE;
        }

        char* strategy = argv[1];

        int task_count = 10;
        if (argc >= 3) {
                task_count = atoi(argv[2]);
                if (task_count <= 0) {
                        printf("Invalid number of tasks\n");
                        return EXIT_FAILURE;
                }

        }

        int seed = (int) time(NULL);
        if (argc >= 4) {
                seed = atoi(argv[3]);
        }

        if (argc >= 7) {
                char* endptr;
                set_scheduler_parameters(strtod(argv[4], &endptr), atoi(argv[5]), strtod(argv[6], &endptr));
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
