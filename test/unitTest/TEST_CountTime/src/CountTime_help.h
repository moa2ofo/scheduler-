#ifndef TEST_COUNTTIME_HELP_H
#define TEST_COUNTTIME_HELP_H

#include "CountTime.h"
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
static uint32_t Timer_u32 = 0u;
uint32_t get_Timer_u32(void) {
  return Timer_u32;
}
void set_Timer_u32(uint32_t val) {
  Timer_u32 = val;
}

#endif /* TEST_COUNTTIME_HELP_H */
