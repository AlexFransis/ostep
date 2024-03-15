#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "fifo.h"

int main(int argc, char** argv)
{
        if (argc != 2) {
                printf("Usage: ./main <scheduling_strategy>\n");
                return 0;
        }

        char* strategy = argv[1];

        if (strcmp(strategy, "fifo") == 0) {
                TaskQueue tq = init_fifo_scheduler();
        }

        Task head_task = { "01", "head_task", 60 };
        Task tail_task = { "02", "tail_task", 60 };
        TaskQueue tq = init_empty_queue(10);
        printf("Queue size: %d\n", tq.size);
        printf("Queue max size: %d\n", tq.max_size);

        printf("Queueing task\n");
        queue(&head_task, &tq);
        printf("Queue size: %d\n", tq.size);
        printf("Queue max size: %d\n", tq.max_size);

        printf("Queueing task\n");
        queue(&tail_task, &tq);
        printf("Queue size: %d\n", tq.size);
        printf("Queue max size: %d\n", tq.max_size);

        printf("Head task: %s\n", head(&tq)->task_name);
        printf("Tail task: %s\n", tail(&tq)->task_name);

        printf("Dequeueing task\n");
        dequeue(&tq);
        printf("Head task: %s\n", head(&tq)->task_name);
        printf("Tail task: %s\n", tail(&tq)->task_name);

        return 0;

}
