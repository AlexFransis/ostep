#include "fifo.h"
#include "queue.h"


TaskQueue init_fifo_scheduler()
{
        TaskQueue tq = init_empty_queue(10);

        return tq;
};
