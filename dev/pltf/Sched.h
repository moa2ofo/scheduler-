#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>

/**
 * @defgroup Sched Scheduler
 * @brief Scheduler module.
 *
 * The Module Data and Interface Specification define, in a clear, verifiable,
 * and consistent manner, all externally relevant aspects of a module,
 * including its interfaces and internal data. It covers function interfaces
 * as well as global and static variables, ensuring full transparency of how
 * the module exchanges and manages data in alignment with the software architecture.
 *
 * ## Module Interface Specification
 *
 * | Name        | Input | Output | Type                     | Factor | Offset | Size | Range  | Unit | Init value | Special Values |
 * |-------------|-------|--------|--------------------------|--------|--------|------|--------|------|------------|----------------|
 * | Sched_Main  | No    | Yes    | int32_t Sched_Main(void) | N/A    | N/A    | 1    | N/A    | N/A  | N/A        | Return status  |
 *
 * ## High-level interaction
 * @startuml
 * External -> Sched_Main
 * Sched_Main -> CountTime
 * Sched_Main -> ExecutePendingTasks
 * ExecutePendingTasks -> Sched_Task0
 * ExecutePendingTasks -> Sched_Task1
 * ExecutePendingTasks -> Sched_Task2
 * ExecutePendingTasks -> Sched_Task3
 * ExecutePendingTasks -> Sched_Task4
 * @enduml
 * @{
 */


/**
 * @brief Main scheduler function.
 * @return Execution status.
 */
int32_t Sched_Main(void);

/** @} */

#endif
