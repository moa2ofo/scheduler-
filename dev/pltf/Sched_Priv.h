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
static void CountTime(void);

/**
 * @brief Execute pending tasks.
 * @ingroup Sched
 */
static void ExecutePendingTasks(void);

/**
 * @brief Compute elapsed time since last call.
 * @return Delta time.
 * @ingroup Sched
 */
static uint32_t DeltaTime_u32(void);

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
