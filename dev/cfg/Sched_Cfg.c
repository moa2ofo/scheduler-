
#include "Sched_Cfg.h"
#include "Sched.h"


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

void Sched_Task0(void) {
  /* Task code for 5ms period */
}

void Sched_Task1(void) {
  /* Task code for 10ms period */
}

void Sched_Task2(void) {
  /* Task code for 20ms period */
}
void Sched_Task3(void) {
  /* Task code for 100ms period */
}

void Sched_Task4(void) {
  /* Task code for 100ms period */
}