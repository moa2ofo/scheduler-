#ifndef SCHED_CFG_H
#define SCHED_CFG_H

#include "Sched_Priv.h"
#include <stdint.h>

/**
 * @name Task Cfg Periods [ms]
 * @{
 */
#define SCHED_TASK1_SHIFT (2u)
#define SCHED_TASK2_SHIFT (7u)
#define SCHED_TASK3_SHIFT (17u)
#define SCHED_TASK1_PERIOD (10u)
#define SCHED_TASK2_PERIOD (20u)
#define SCHED_TASK3_PERIOD (100u)
/** @} */



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


/** @} */

/** @} */

#endif // SCHED_CFG_H