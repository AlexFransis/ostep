#ifndef GUARD_scheduler_h
#define GUARD_scheduler_h


void start_fifo_scheduler(int task_count);
void start_sjf_scheduler(int task_count);
void start_rr_scheduler(int task_count);
void start_mlfq_scheduler(int task_count);
void set_scheduler_parameters(double quantum, double p_boost, double lambda);

static double s_quantum = 0.5;
static double s_priority_boost = 15;
static double s_lambda = 0.6;


#endif
