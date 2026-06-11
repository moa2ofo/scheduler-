#include "Mcu.h"
#include "Sched_Priv.h"

const uint32_t SCHED_LOOP_PERIOD=100;
const uint32_t SCHED_TASK0_PERIOD=5;
const uint32_t SCHED_TASK1_PERIOD=10;
const uint32_t SCHED_TASK2_PERIOD=20;
const uint32_t SCHED_TASK3_PERIOD=100;
const uint32_t SCHED_TASK0_SHIFT=0; 
const uint32_t SCHED_TASK1_SHIFT=2; 
const uint32_t SCHED_TASK2_SHIFT=7; 
const uint32_t SCHED_TASK3_SHIFT=17; 



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