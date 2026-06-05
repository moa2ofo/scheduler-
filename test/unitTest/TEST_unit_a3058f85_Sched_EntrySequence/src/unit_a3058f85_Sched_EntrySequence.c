#include "unit_a3058f85_Sched_EntrySequence_help.h"

/* FUNCTION TO TEST */
void Sched_EntrySequence(void) {
  /* Initialize MCU hardware modules*/
  Mcu_Initialize();
  /* Begin Short-Open-Window in case MCU initialization took too long */
  Mcu_ServiceWatchdogSow();
  /* Reset SysTick counter and reference timestamp */
  Mcu_ReloadSystick();
}
