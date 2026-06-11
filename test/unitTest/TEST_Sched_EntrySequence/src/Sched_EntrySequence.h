#ifndef TEST_SCHED_ENTRYSEQUENCE_H
#define TEST_SCHED_ENTRYSEQUENCE_H

#include "Sched_Cfg.h"
#include "Sched_Priv.h"

/**
 * @ingroup Sched
 * @brief Execute the scheduler entry initialization sequence.
 * @details
 * **Goal of the function**
 *
 * Initialize MCU hardware modules and ensure a consistent scheduler
 * start by resetting the system time base.
 *
 * The function performs:
 * - MCU initialization
 * - Watchdog service (Short-Open-Window)
 * - SysTick reload and reference time reset
 *
 * @par Interface summary
 *
 * | Interface                  | In | Out | Type / Signature | Description                     |
 * |----------------------------|----|-----|------------------|---------------------------------|
 * | Mcu_Initialize             | X  |     | void(void)       | HW initialization               |
 * | Mcu_ServiceWatchdogSow     | X  |     | void(void)       | Watchdog servicing              |
 * | Mcu_ReloadSystick          | X  |     | void(void)       | Reset system tick counter       |
 * | return val                 |    |     | void             | No return value                 |
 *
 * @par Activity diagram (PlantUML)
 * @startuml
 * start
 * :Mcu_Initialize();
 * :Mcu_ServiceWatchdogSow();
 * :Mcu_ReloadSystick();
 * stop
 * @enduml
 *
 * @return void
 */
void Sched_EntrySequence(void);

#endif /* TEST_SCHED_ENTRYSEQUENCE_H */
