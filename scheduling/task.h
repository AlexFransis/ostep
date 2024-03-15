enum TaskStatus {
        READY,
        QUEUED,
        IN_PROGRESS,
        COMPLETED,
};

struct Task;
typedef struct Task
{
        char* task_id;
        char* task_name;
        unsigned int duration;
        enum TaskStatus status;
} Task;
