#include "queue.h"
#include <stdio.h>

int main(int argc, char** argv)
{
        Task head_task = { "01", "head_task", 60 };
        Task tail_task = { "02", "tail_task", 60 };
        TaskQueue tq;
        init_empty_queue(&tq, 10);
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
