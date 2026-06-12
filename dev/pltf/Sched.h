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
 *
/**
 * ### Static design and traceability matrix
 * <table>
 * <tr>
 *   <th>Software element</th>
 *   <th>Category</th>
 *   <th>Visibility</th>
 *   <th>Requirement</th>
 *   <th>Description</th>
 * </tr>
 *
 * <tr>
 *   <td>@ref Sched_Main</td>
 *   <td>Public interface / Command</td>
 *   <td>External</td>
 *   <td>SW_INTF-P0006</td>
 *   <td>Main scheduler entry point called by the external platform.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref Sched_GetRefTime_u32</td>
 *   <td>Public interface / Data access</td>
 *   <td>External</td>
 *   <td>SW_ARCH-C0005<br>SW_INTF-P0006</td>
 *   <td>Provides the current scheduler reference time.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref Sched_EntrySequence</td>
 *   <td>Internal unit</td>
 *   <td>Internal</td>
 *   <td>SW_ARCH-C0004</td>
 *   <td>Executes the scheduler entry sequence and initializes platform services.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref CountTime</td>
 *   <td>Internal unit</td>
 *   <td>Internal</td>
 *   <td>Derived from SW_ARCH-C0005</td>
 *   <td>Updates the internal scheduler timer.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref DeltaTime_u32</td>
 *   <td>Internal utility unit</td>
 *   <td>Internal</td>
 *   <td>Derived from SW_ARCH-C0005</td>
 *   <td>Calculates elapsed time between two uint32_t time references.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref SCHED_TASK0_PERIOD</td>
 *   <td>Configuration parameter</td>
 *   <td>Configuration</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the execution period of Task0.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref Sched_Task0</td>
 *   <td>Configured runnable</td>
 *   <td>Configuration</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Task executed according to the configured scheduler timing.</td>
 * </tr>
 *
 * </table>
 *
 *
 * ### Module Data and Interface Specification
 * | Name                 | Paramter | Datum | Command | Type             | Factor | Offset | Size               | Range              | Unit | Init value | Special Values |
 * |----------------------|----------|-------|---------|------------------|--------|--------|--------------------|--------------------|------|------------|----------------|
 * | Sched_Main           |          |       |    x    | int32_t (void)   | N/A    | N/A    | 1                  | N/A                | N/A  | N/A        | Return status  |
 * | NumOfTaskCalls_au32  |          |   x   |         | uint32_t         | N/A    | N/A    | SCHED_NUM_OF_TASKS | N/A                | N/A  | 0          | Return status  |
 * | Task_ac              |          |   x   |         | const Task_t     | N/A    | N/A    | SCHED_NUM_OF_TASKS | N/A                | N/A  | N/A        | Return status  |
 * | Timer_u32            |          |   x   |         | uint32_t         | N/A    | N/A    | 1                  | 0..UINT32_MAX      | ms   | 0          | N/A            |
 * | SCHED_MAX_REF_TIME   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | UINT32_MAX         | ms   | UINT32_MAX | N/A            |
 * | SCHED_LOOP_PERIOD    |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 100                | ms   | 100        | N/A            |
 * | SCHED_NUM_OF_TASKS   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 4                  | N/A  | 4          | N/A            |
 * | SCHED_TASK0_PERIOD   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 5                  | ms   | 5          | N/A            |
 * | SCHED_TASK1_PERIOD   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 10                 | ms   | 10         | N/A            |
 * | SCHED_TASK2_PERIOD   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 20                 | ms   | 20         | N/A            |
 * | SCHED_TASK3_PERIOD   |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 100                | ms   | 100        | N/A            |
 * | SCHED_TASK0_SHIFT    |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 0                  | ms   | 0          | N/A            |
 * | SCHED_TASK1_SHIFT    |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 2                  | ms   | 2          | N/A            |
 * | SCHED_TASK2_SHIFT    |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 7                  | ms   | 7          | N/A            |
 * | SCHED_TASK3_SHIFT    |    x     |       |         | uint32_t         | N/A    | N/A    | 1                  | 17                 | ms   | 17         | N/A            |
 *
 * ### High-level interaction
 * @startuml
 * title Scheduler Module
 * actor External as External
 * box "Platform interfaces"
 *     participant "Sched_Main()" as Main
 * end box
 * box "Platform internal"
 *     participant "CountTime()" as CountTime
 *     participant "ExecutePendingTasks()" as ExecuteTasks
 *     participant "DeltaTime_u32()" as DeltaTime    
 * end box
 * box "Configuration"
 *     participant "Sched_EntrySequence()" as EntrySeq
 *     participant "Sched_Task0()" as Task0
 *     participant "Sched_Task1()" as Task1
 *     participant "Sched_Task2()" as Task2
 *     participant "Sched_Task3()" as Task3
 * end box
 * 
 * 
 * actor "Mcu" as Mcu
 * 
 * == Entry point ==
 * External -> Main : call Sched_Main()
 * Main -> EntrySeq : call Sched_EntrySequence()
 * EntrySeq -> Mcu : call Mcu_Initialize()
 * EntrySeq -> Mcu : call Mcu_ServiceWatchdogSow()
 * EntrySeq -> Mcu : call Mcu_ReloadSystick()
 * Main -> CountTime : call CountTime()
 * CountTime -> DeltaTime : call DeltaTime_u32()
 * Main -> ExecuteTasks : call ExecutePendingTasks()
 * ExecuteTasks -> Task0 : call Sched_Task0() [5ms]
 * ExecuteTasks -> Task1 : call Sched_Task1() [10ms]
 * ExecuteTasks -> Task2 : call Sched_Task2() [20ms]
 * Task2 -> Mcu : call Mcu_ServiceWatchdog()
 * ExecuteTasks -> Task3 : call Sched_Task3() [100ms]
 * 
 * @enduml
 */

/**
 * @brief Main scheduler function.
 * @ingroup Sched
 * @return Execution status.
 */
int32_t Sched_Main(void);

#endif
