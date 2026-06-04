#ifndef SCHED_PRIV_H
#define SCHED_PRIV_H

#include "Sched_Cfg.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Task handler function type.
 */
typedef void (*const TaskHandler_t)(void);

/**
 * @brief Task configuration structure.
 */
typedef struct {
  TaskHandler_t handler_;     /**< Task function */
  const uint32_t period_cu32; /**< Task period */
  const uint32_t shift_cu32;  /**< Task phase shift */
} Task_t;

/* Internal functions */
static void CountTime(void);
static void ExecutePendingTasks(void);
static uint32_t DeltaTime_u32(void);

/* Task entry points */
void Sched_Task0(void);
#if(SCHED_NUM_OF_TASKS > 1u)
void Sched_Task1(void);
#endif
#if(SCHED_NUM_OF_TASKS > 2u)
void Sched_Task2(void);
#endif
#if(SCHED_NUM_OF_TASKS > 3u)
void Sched_Task3(void);
#endif
#if(SCHED_NUM_OF_TASKS > 4u)
void Sched_Task4(void);
#endif

#endif