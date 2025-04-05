#include <stdlib.h>
#include "task.h"

void free_task(Task *t)
{
        free(t->task_id);
        free(t);
}
