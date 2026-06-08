#include "Sched_Priv.h"
#include <string.h>

static uint32_t Timer_u32 = 0u;

static uint32_t NumOfTaskCalls_au32[SCHED_NUM_OF_TASKS] = {0u};
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

int32_t Sched_Main(void) {
  Sched_EntrySequence();

  while(true) {
    CountTime();
    ExecutePendingTasks();
  }
}

static void CountTime(void) {
  Timer_u32 += DeltaTime_u32();

  if(Timer_u32 >= SCHED_LOOP_PERIOD) {
    Timer_u32 -= SCHED_LOOP_PERIOD;
    memset(NumOfTaskCalls_au32, 0u, sizeof(NumOfTaskCalls_au32));
  }
}

static uint32_t DeltaTime_u32(void) {
  static uint32_t l_PrevTimestamp_u32 = 0u;
  uint32_t l_currTimeStamp_u32 = Sched_GetRefTime_u32();
  uint32_t l_deltaTime_u32;

  /* Time has increased, normal scenario */
  if(l_currTimeStamp_u32 > l_PrevTimestamp_u32) {
    l_deltaTime_u32 = l_currTimeStamp_u32 - l_PrevTimestamp_u32;
  }
  /* Time has decreased, overflow of the reference time occurred */
  else if(l_currTimeStamp_u32 < l_PrevTimestamp_u32) {
    l_deltaTime_u32 = (SCHED_MAX_REF_TIME - l_PrevTimestamp_u32) + l_currTimeStamp_u32 + 1u;
  }
  /* Time is unchanged, not enough time elapsed, do nothing */
  else {
    l_deltaTime_u32 = 0u;
  }
  l_PrevTimestamp_u32 = l_currTimeStamp_u32;

  return l_deltaTime_u32;
}

static void ExecutePendingTasks(void) {
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
