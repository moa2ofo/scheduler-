#ifndef SCHED_PRIV_H
#define SCHED_PRIV_H

#include "Sched_Cfg.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Task handler function type.
 * @ingroup Sched
 */
typedef void (*const TaskHandler_t)(void);

/**
 * @brief Task configuration structure.
 * @ingroup Sched
 */
typedef struct {
  TaskHandler_t handler_;     /**< Task function */
  const uint32_t period_cu32; /**< Task period */
  const uint32_t shift_cu32;  /**< Task phase shift */
} Task_t;

/**
 * @brief Update scheduler time base.
 * @ingroup Sched
 */
void CountTime(void);

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

/**
 * @brief Compute elapsed time since last call.
 * @return Delta time.
 * @ingroup Sched
 */
uint32_t DeltaTime_u32(void);

/**
 * @brief Task 0 entry point.
 * @ingroup Sched
 */
void Sched_Task0(void);

#if(SCHED_NUM_OF_TASKS > 1u)
/**
 * @brief Task 1 entry point.
 * @ingroup Sched
 */
void Sched_Task1(void);
#endif

#if(SCHED_NUM_OF_TASKS > 2u)
/**
 * @brief Task 2 entry point.
 * @ingroup Sched
 */
void Sched_Task2(void);
#endif

#if(SCHED_NUM_OF_TASKS > 3u)
/**
 * @brief Task 3 entry point.
 * @ingroup Sched
 */
void Sched_Task3(void);
#endif

#if(SCHED_NUM_OF_TASKS > 4u)
/**
 * @brief Task 4 entry point.
 * @ingroup Sched
 */
void Sched_Task4(void);
#endif

#endif
