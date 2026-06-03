#include "DeltaTime_u32_help.h"

/* FUNCTION TO TEST */
uint32_t DeltaTime_u32(void)
{
  static uint32_t l_PrevTimestamp_u32 = 0u;
  uint32_t l_currTimeStamp_u32 = Sched_GetRefTime_u32();
  uint32_t l_deltaTime_u32;

  /* Time has increased, normal scenario */
  if (l_currTimeStamp_u32 > l_PrevTimestamp_u32)
  {
    l_deltaTime_u32 = l_currTimeStamp_u32 - l_PrevTimestamp_u32;
  }
  /* Time has decreased, overflow of the reference time occurred */
  else if (l_currTimeStamp_u32 < l_PrevTimestamp_u32)
  {
    l_deltaTime_u32 = (SCHED_MAX_REF_TIME - l_PrevTimestamp_u32) + l_currTimeStamp_u32 + 1u;
  }
  /* Time is unchanged, not enough time elapsed, do nothing */
  else
  {
    l_deltaTime_u32 = 0u;
  }

  l_PrevTimestamp_u32 = l_currTimeStamp_u32;

  return l_deltaTime_u32;
}