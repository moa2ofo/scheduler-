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
 *   <td>command</td>
 *   <td>External</td>
 *   <td>SW_INTF-P0006</td>
 *   <td>Main scheduler entry point called by the external platform.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref CountTime</td>
 *   <td rowspan="3">command</td>
 *   <td rowspan="6">Internal</td>
 *   <td>Derived from SW_ARCH-C0005</td>
 *   <td>Updates the internal scheduler timer.</td>
 * </tr>
 * <tr>
 *   <td>@ref DeltaTime_u32</td>
 *   <td>Derived from SW_ARCH-C0005</td>
 *   <td>Calculates elapsed time between two uint32_t time references.</td>
 * </tr>
 * <tr>
 *   <td>@ref ExecutePendingTasks</td>
 *   <td>Derived from SW_ARCH-C0003</td>
 *   <td>Executes all scheduler tasks that are pending according to the configured timing.</td>
 * </tr>
 * <tr>
 *   <td>@ref Timer_u32</td>
 *   <td rowspan="3">datum</td>
 *   <td>Derived from SW_ARCH-C0005</td>
 *   <td>Stores the current scheduler reference time.</td>
 * </tr>
 * <tr>
 *   <td>@ref NumOfTaskCalls_au32</td>
 *   <td>Derived from SW_ARCH-C0003</td>
 *   <td>Stores the number of calls executed for each configured scheduler task.</td>
 * </tr>
 * <tr>
 *   <td>@ref Task_ac</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Stores the configured scheduler task table.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref SCHED_TASK0_PERIOD</td>
 *   <td rowspan="8">parameter</td>
 *   <td rowspan="14">Configuration</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the execution period of Task0.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK1_PERIOD</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the execution period of Task1.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK2_PERIOD</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the execution period of Task2.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK3_PERIOD</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the execution period of Task3.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK0_SHIFT</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the phase shift of Task0.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK1_SHIFT</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the phase shift of Task1.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK2_SHIFT</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the phase shift of Task2.</td>
 * </tr>
 * <tr>
 *   <td>@ref SCHED_TASK3_SHIFT</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Defines the phase shift of Task3.</td>
 * </tr>
 *
 * <tr>
 *   <td>@ref Sched_EntrySequence</td>
 *   <td rowspan="6">command</td>
 *   <td>SW_ARCH-C0004</td>
 *   <td>Executes the scheduler entry sequence and initializes platform services.</td>
 * </tr>
 * <tr>
 *   <td>@ref Sched_GetRefTime_u32</td>
 *   <td>SW_ARCH-C0005<br>SW_INTF-P0006</td>
 *   <td>Provides the current scheduler reference time.</td>
 * </tr>
 * <tr>
 *   <td>@ref Sched_Task0</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Task executed according to the configured scheduler timing.</td>
 * </tr>
 * <tr>
 *   <td>@ref Sched_Task1</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Task executed according to the configured scheduler timing.</td>
 * </tr>
 * <tr>
 *   <td>@ref Sched_Task2</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Task executed according to the configured scheduler timing.</td>
 * </tr>
 * <tr>
 *   <td>@ref Sched_Task3</td>
 *   <td>SW_ARCH-C0003</td>
 *   <td>Task executed according to the configured scheduler timing.</td>
 * </tr>
 *
 * </table>
 *
 *
 *
 * ### Platform Data and Interface Specification
 * | Name                      | Category | Type             | Factor | Offset | Size               | Range              | Unit | Init value | Special Values |
 * |---------------------------|----------|------------------|--------|--------|--------------------|--------------------|------|------------|----------------|
 * | @ref Sched_Main           | C(I/O)   | int32_t (void)   | N/A    | N/A    | 1                  | N/A                | N/A  | N/A        | Return status  |
 * | @ref NumOfTaskCalls_au32  | D(I/O)   | uint32_t         | N/A    | N/A    | SCHED_NUM_OF_TASKS | N/A                | N/A  | 0          | Return status  |
 * | @ref Task_ac              | D(I/O)   | const Task_t     | N/A    | N/A    | SCHED_NUM_OF_TASKS | N/A                | N/A  | N/A        | Return status  |
 * | @ref Timer_u32            | D(I/O)   | uint32_t         | N/A    | N/A    | 1                  | 0..UINT32_MAX      | N/A  | 0          | N/A            |
 * ### Configuration Data and Interface Specification
 * | Name                      | Category | Type             | Factor | Offset | Size               | Range              | Unit | Init value | Special Values |
 * |---------------------------|----------|------------------|--------|--------|--------------------|--------------------|------|------------|----------------|
 * | @ref SCHED_MAX_REF_TIME   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | UINT32_MAX         | ms   | UINT32_MAX | N/A            |
 * | @ref SCHED_LOOP_PERIOD    | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 100                | ms   | 100        | N/A            |
 * | @ref SCHED_NUM_OF_TASKS   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 4                  | N/A  | 4          | N/A            |
 * | @ref SCHED_TASK0_PERIOD   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 5                  | ms   | 5          | N/A            |
 * | @ref SCHED_TASK1_PERIOD   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 10                 | ms   | 10         | N/A            |
 * | @ref SCHED_TASK2_PERIOD   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 20                 | ms   | 20         | N/A            |
 * | @ref SCHED_TASK3_PERIOD   | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 100                | ms   | 100        | N/A            |
 * | @ref SCHED_TASK0_SHIFT    | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 0                  | ms   | 0          | N/A            |
 * | @ref SCHED_TASK1_SHIFT    | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 2                  | ms   | 2          | N/A            |
 * | @ref SCHED_TASK2_SHIFT    | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 7                  | ms   | 7          | N/A            |
 * | @ref SCHED_TASK3_SHIFT    | P(I)     | uint32_t         | N/A    | N/A    | 1                  | 17                 | ms   | 17         | N/A            |
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
