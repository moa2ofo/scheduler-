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
 * ### Tracebility module matrix
 * <table>
 * <tr>
 *   <th>Function / Data</th>
 *   <th>Requirement</th>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Main</td>
 *   <td>SW_INTF-P0006</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="2">@ref Sched_GetRefTime_u32</td>
 *   <td>SW_ARCH-C0005</td>
 * </tr>
 * <tr>
 *   <td>SW_INTF-P0006</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_EntrySequence</td>
 *   <td>SW_ARCH-C0004</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref SCHED_TASK0_PERIOD</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Task0</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Task1</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Task2</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Task3</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref Sched_Task4</td>
 *   <td>SW_ARCH-C0003</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref CountTime</td>
 *   <td>N/A</td>
 * </tr>
 *
 * <tr>
 *   <td rowspan="1">@ref DeltaTime_u32</td>
 *   <td>N/A</td>
 * </tr>
 *
 * </table>
 *
 * ### Module Data and Interface Specification
 * | Name                 | Input | Output | Type                     | Factor | Offset | Size | Range         | Unit | Init value | Special Values |
 * |----------------------|-------|--------|--------------------------|--------|--------|------|---------------|------|------------|----------------|
 * | Sched_Main           | No    | Yes    | int32_t (void)           | N/A    | N/A    | 1    | N/A           | N/A  | N/A        | Return status  |
 * | Sched_GetRefTime_u32 | Yes   | No     | uint32                   | N/A    | N/A    | 1    | [0,UINT32_MAX]| ms   | N/A        | Return status  |
 * | Sched_EntrySequence  | No    | Yes    | void (void)              | N/A    | N/A    | N/A  | N/A           | N/A  | N/A        | N/A            |
 * | SCHED_TASK0_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [5,5]         | ms   | 5          | N/A            |
 * | SCHED_TASK1_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [10,10]       | ms   | 10         | N/A            |
 * | SCHED_TASK2_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [20,20]       | ms   | 20         | N/A            |
 * | SCHED_TASK3_PERIOD   | Yes   | No     | const uint32             | 1      | 0      | 1    | [100,100]     | ms   | 100        | N/A            |
 *
 * ### High-level interaction
 * @startuml
 * title Scheduler
 *
 * actor External as External
 *
 * box "Public functions"
 *   participant "Sched_Main()" as Sched_Main
 *   participant "Sched_EntrySequence()" as Entry
 *   participant "Sched_GetRefTime_u32()" as GetRef
 * end box
 *
 * box "Internal functions"
 *   participant "CountTime()" as CountTime
 *   participant "ExecutePendingTasks()" as Exec
 *   participant "Sched_Task0()" as T0
 *   participant "Sched_Task1()" as T1
 *   participant "Sched_Task2()" as T2
 *   participant "Sched_Task3()" as T3
 *   participant "Sched_Task4()" as T4
 * end box
 *
 * == Entry point 1 ==
 * External -> Sched_Main : call Sched_Main()
 * Sched_Main -> CountTime : call CountTime()
 * CountTime --> Sched_Main : return
 *
 * Sched_Main -> Exec : call ExecutePendingTasks()
 * Exec -> T0 : call Sched_Task0()
 * T0 --> Exec : return
 * Exec -> T1 : call Sched_Task1()
 * T1 --> Exec : return
 * Exec -> T2 : call Sched_Task2()
 * T2 --> Exec : return
 * Exec -> T3 : call Sched_Task3()
 * T3 --> Exec : return
 * Exec -> T4 : call Sched_Task4()
 * T4 --> Exec : return
 *
 * Exec --> Sched_Main : return
 * Sched_Main --> External : return
 *
 * == Entry point 2 ==
 * External -> Entry : call Sched_EntrySequence()
 * Entry --> External : return
 *
 * == Entry point 3 ==
 * External -> GetRef : call Sched_GetRefTime_u32()
 * GetRef --> External : return
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
