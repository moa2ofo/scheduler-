#ifndef TEST_EXECUTEPENDINGTASKS_H
#define TEST_EXECUTEPENDINGTASKS_H

#include "Sched_Cfg.h"
#include "Sched_Priv.h"

#include <stddef.h>

/**
 * @ingroup Sched
 * @brief Execute all tasks whose activation time has been reached.
 * @ingroup Sched
 * @details
 * **Goal of the function**
 *
 * Iterate over the configured task list and invoke each task whose
 * scheduled activation time has been reached according to the current
 * scheduler time base (`Timer_u32`).
 *
 * @par Interface summary
 *
 * | Interface                | In | Out | Type / Signature       | Param | Factor | Offset | Size | Range            | Unit |
 * |--------------------------|----|-----|-------------------------|-------|--------|--------|------|------------------|------|
 * | Timer_u32                | X  |     | uint32_t (global)       |       |   1    |   0    |   1  | 0..(wrap)        | [-]  |
 * | Task_ac                  | X  |     | const Task_t[]          |       |   1    |   0    |   N  | configured       | [-]  |
 * | NumOfTaskCalls_au32      | X  |  X  | uint32_t[] (global)     |       |   1    |   0    |   N  | 0..(wrap)        | [-]  |
 * | handler_                 | X  |     | void (*)(void)          |       |   1    |   0    |   1  | -                | [-]  |
 * | return val               |    |     | void                    |       |   1    |   0    |   1  | -                | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :l_idx_u32 = 0;
 * while (l_idx_u32 < SCHED_NUM_OF_TASKS) is (yes)
 *   :compute l_timeShift_s32;
 *   if (l_timeShift_s32 >= 0) then (yes)
 *     :call handler_();
 *     :NumOfTaskCalls_au32[idx]++;
 *   else (no)
 *   endif
 *   :l_idx_u32++;
 * endwhile
 * :return;
 * stop
 * @enduml
 *
 * @return void
 * No return value.
 */
void ExecutePendingTasks(void);

uint32_t* get_NumOfTaskCalls_au32_ptr(void);
size_t get_NumOfTaskCalls_au32_size(void);
const Task_t* get_Task_ac_ptr(void);
size_t get_Task_ac_size(void);
uint32_t get_Timer_u32(void);
void set_Timer_u32(uint32_t val);

#endif /* TEST_EXECUTEPENDINGTASKS_H */
