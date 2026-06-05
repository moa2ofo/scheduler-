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
 * @brief Scheduler
 * 
 * Tasks:
 * - @ref Sched_Main
 * - @ref CountTime
 * - @ref DeltaTime_u32
 * - @ref Sched_GetRefTime_u32
 * - @ref Sched_EntrySequence
 * - @ref Sched_Task0
 * - @ref Sched_Task1
 * - @ref Sched_Task2
 * - @ref Sched_Task3
 * - @ref Sched_Task4
 * - @ref SCHED_TASK0_PERIOD
 *
 * | Name                 | Input | Output | Type                     | Factor | Offset | Size | Range         | Unit | Init value | Special Values | Link          |
 * |----------------------|-------|--------|--------------------------|--------|--------|------|---------------|------|------------|----------------|---------------|
 * | Sched_Main           | No    | Yes    | int32_t Sched_Main(void) | N/A    | N/A    | 1    | N/A           | N/A  | N/A        | Return status  | SW_INTF-P0006 |
 * | Sched_GetRefTime_u32 | Yes   | No     | uint32                   | N/A    | N/A    | 1    | [0,UINT32_MAX]| ms   | N/A        | Return status  | SW_ARCH-C0005 |
 * | Sched_EntrySequence  | No    | Yes    | void (void)              | N/A    | N/A    | N/A  | N/A           | N/A  | N/A        | N/A            | SW_ARCH-C0004 |
 * | SCHED_TASK0_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [5,5]         | ms   | 5          | N/A            | SW_ARCH-C0003 |
 * | SCHED_TASK1_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [10,10]       | ms   | 10         | N/A            | SW_ARCH-C0003 |
 * | SCHED_TASK2_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [20,20]       | ms   | 20         | N/A            | SW_ARCH-C0003 |
 * | SCHED_TASK3_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [100,100]     | ms   | 100        | N/A            | SW_ARCH-C0003 |
 *
 * ## High-level interaction
* @startuml
 * External -> Sched_Main
 * External -> Sched_EntrySequence
 * External -> Sched_GetRefTime_u32
 *
 * Sched_Main -> CountTime
 * Sched_Main -> ExecutePendingTasks
 *
 * ExecutePendingTasks -> Sched_Task0
 * ExecutePendingTasks -> Sched_Task1
 * ExecutePendingTasks -> Sched_Task2
 * ExecutePendingTasks -> Sched_Task3
 * ExecutePendingTasks -> Sched_Task4
 * @enduml
 */

/**
 * @brief Main scheduler function.
 * @ingroup Sched
 * @return Execution status.
 */
int32_t Sched_Main(void);

#endif
