#include "CountTime_help.h"

/* FUNCTION TO TEST */
void CountTime(void)
{
  Timer_u32 += DeltaTime_u32();
  
  if (Timer_u32 >= SCHED_LOOP_PERIOD)
  {
    Timer_u32 -= SCHED_LOOP_PERIOD;
    memset(NumOfTaskCalls_au32, 0u, sizeof(NumOfTaskCalls_au32));
  }
}