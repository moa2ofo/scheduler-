#ifndef SCHED_CFG_H
#define SCHED_CFG_H

#include <stdint.h>

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

/**
 * @ingroup Sched
 * @brief Get the current scheduler reference time.
 * @details
 * **Goal of the function**
 *
 * Provide the current system time in milliseconds used as
 * reference for task scheduling.
 *
 * @par Interface summary
 *
 * | Interface                  | In | Out | Type / Signature  | Description              |
 * |----------------------------|----|-----|-------------------|--------------------------|
 * | Mcu_GetSystemTime_u32      | X  |     | uint32_t(void)    | Get system time (ms)     |
 * | return val                 |    |  X  | uint32_t          | Current time reference   |
 *
 * @return uint32_t
 * Current system time in milliseconds.
 */
uint32_t Sched_GetRefTime_u32(void);

/**
 * @brief Maximum reference time value before wrap-around.
 */
#define SCHED_MAX_REF_TIME (UINT32_MAX)

/**
 * @brief Scheduler base loop period in milliseconds.
 * @details Must be a multiple of all configured task periods.
 */
#define SCHED_LOOP_PERIOD   (100u)


/**
 * @brief Number of scheduled tasks.
 */
#define SCHED_NUM_OF_TASKS (4u)

/**
 * @name Task Periods [ms]
 * @{
 */
#define SCHED_TASK0_PERIOD  (5u)
#define SCHED_TASK1_PERIOD  (10u)
#define SCHED_TASK2_PERIOD  (20u)
#define SCHED_TASK3_PERIOD  (100u)
/** @} */

/**
 * @name Task Phase Shifts [ms]
 * @{
 */


#define SCHED_TASK0_SHIFT   (0u)
#define SCHED_TASK1_SHIFT   (2u)
#define SCHED_TASK2_SHIFT   (7u)
#define SCHED_TASK3_SHIFT   (17u)

/** @} */

/** @} */

#endif // SCHED_CFG_H