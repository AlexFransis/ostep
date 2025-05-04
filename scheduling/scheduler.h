#ifndef GUARD_scheduler_h
#define GUARD_scheduler_h

void start_fifo_scheduler(int task_count);
void start_sjf_scheduler(int task_count);
void start_rr_scheduler(int task_count);
void start_mlfq_scheduler(int task_count);

#endif
