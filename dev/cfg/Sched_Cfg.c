#include "Mcu.h"
#include "Sched_Priv.h"

void Sched_EntrySequence(void) {
  /* Initialize MCU hardware modules*/
  Mcu_Initialize();
  /* Begin Short-Open-Window in case MCU initialization took too long */
  Mcu_ServiceWatchdogSow();
  /* Reset SysTick counter and reference timestamp */
  Mcu_ReloadSystick();
}

uint32_t Sched_GetRefTime_u32(void) {
  /* Return the current system time in ms */
  return Mcu_GetSystemTime_u32();
}