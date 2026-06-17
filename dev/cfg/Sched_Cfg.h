#ifndef SCHED_CFG_H
#define SCHED_CFG_H

#include <stdint.h>
#include "Sched_Priv.h"



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


/** @} */

/** @} */

#endif // SCHED_CFG_H