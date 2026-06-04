#ifndef TEST_EXECUTEPENDINGTASKS_HELP_H
#define TEST_EXECUTEPENDINGTASKS_HELP_H

#include "ExecutePendingTasks.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static uint32_t NumOfTaskCalls_au32[SCHED_NUM_OF_TASKS] = {0u};
uint32_t *get_NumOfTaskCalls_au32_ptr(void) {
  return NumOfTaskCalls_au32;
}
size_t get_NumOfTaskCalls_au32_size(void) {
  return (size_t)4;
}
void set_NumOfTaskCalls_au32(const uint32_t *src, size_t n) {
  size_t m = (n < (size_t)4) ? n : (size_t)4;
  memcpy(NumOfTaskCalls_au32, src, m * sizeof(uint32_t));
}
static const Task_t Task_ac[SCHED_NUM_OF_TASKS] = {
    {.handler_ = &Sched_Task0, .period_cu32 = SCHED_TASK0_PERIOD, .shift_cu32 = SCHED_TASK0_SHIFT},
#if(SCHED_NUM_OF_TASKS > 1u)
    {.handler_ = &Sched_Task1, .period_cu32 = SCHED_TASK1_PERIOD, .shift_cu32 = SCHED_TASK1_SHIFT},
#endif
#if(SCHED_NUM_OF_TASKS > 2u)
    {.handler_ = &Sched_Task2, .period_cu32 = SCHED_TASK2_PERIOD, .shift_cu32 = SCHED_TASK2_SHIFT},
#endif
#if(SCHED_NUM_OF_TASKS > 3u)
    {.handler_ = &Sched_Task3, .period_cu32 = SCHED_TASK3_PERIOD, .shift_cu32 = SCHED_TASK3_SHIFT},
#endif
#if(SCHED_NUM_OF_TASKS > 4u)
    {.handler_ = &Sched_Task4, .period_cu32 = SCHED_TASK4_PERIOD, .shift_cu32 = SCHED_TASK4_SHIFT},
#endif
#if(SCHED_NUM_OF_TASKS > 5u)
#error "Number of tasks exceeds the maximum supported by the implementation."
#endif
};
const Task_t *get_Task_ac_ptr(void) {
  return Task_ac;
}
size_t get_Task_ac_size(void) {
  return (size_t)4;
}
void set_Task_ac(const const Task_t *src, size_t n) {
  size_t m = (n < (size_t)4) ? n : (size_t)4;
  memcpy(Task_ac, src, m * sizeof(const Task_t));
}
static uint32_t Timer_u32 = 0u;
uint32_t get_Timer_u32(void) {
  return Timer_u32;
}
void set_Timer_u32(uint32_t val) {
  Timer_u32 = val;
}

#endif /* TEST_EXECUTEPENDINGTASKS_HELP_H */
