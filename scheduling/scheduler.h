#include "cpu_core.h"


Task* create_task(unsigned int duration);
Task* create_random_task();
void schedule_task(Task* t);
void run_task(Task* t, CPU_CORE* cpu_core);
void generate_uuid(char* );
