#include "Sched_GetRefTime_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Sched_GetRefTime_u32(void) {
  /* Return the current system time in ms */
  return Mcu_GetSystemTime_u32();
}