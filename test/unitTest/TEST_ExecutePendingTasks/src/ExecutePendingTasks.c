#include "ExecutePendingTasks_help.h"

/* FUNCTION TO TEST */
void ExecutePendingTasks(void) {
  uint32_t l_idx_u32;
  int32_t l_timeShift_s32;

  /* Parse through all tasks, with lower index tasks having higher priority */
  for(l_idx_u32 = 0u; l_idx_u32 < SCHED_NUM_OF_TASKS; l_idx_u32++) {
    /* Calculate current time relative to the next call of the task*/
    l_timeShift_s32 = (int32_t)(Timer_u32 - ((Task_ac[l_idx_u32].period_cu32 * NumOfTaskCalls_au32[l_idx_u32]) + Task_ac[l_idx_u32].shift_cu32));

    if(l_timeShift_s32 >= 0) {
      Task_ac[l_idx_u32].handler_();
      NumOfTaskCalls_au32[l_idx_u32]++;
    }
  }
}