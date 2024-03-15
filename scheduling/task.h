#include <stdbool.h>

struct Task;
typedef struct Task
{
        char* task_id;
        char* task_name;
        unsigned int duration;
        bool is_completed;
} Task;
