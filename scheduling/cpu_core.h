#include "task.h"

struct CPU_CORE;
typedef struct CPU_CORE {
        unsigned int time_slice;
} CPU_CORE;

void do_work(CPU_CORE* cpu, Task* t);
