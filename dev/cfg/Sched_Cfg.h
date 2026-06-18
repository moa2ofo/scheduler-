#ifndef SCHED_CFG_H
#define SCHED_CFG_H

#include "Sched_Priv.h"
#include <stdint.h>

/**
 * @brief Maximum reference time value before wrap-around.
 */
#define SCHED_MAX_REF_TIME (UINT32_MAX)

/**
 * @brief Scheduler base loop period in milliseconds.
 * @details Must be a multiple of all configured task periods.
 */
#define SCHED_LOOP_PERIOD (100u)

/**
 * @brief Number of scheduled tasks.
 */
#define SCHED_NUM_OF_TASKS (4u)

/**
 * @name Task Periods [ms]
 * @{
 */
#define SCHED_TASK0_PERIOD (5u)

/** @} */

/**
 * @name Task Phase Shifts [ms]
 * @{
 */

#define SCHED_TASK0_SHIFT (0u)

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
/** @} */

/** @} */

#endif // SCHED_CFG_H