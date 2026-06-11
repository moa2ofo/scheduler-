#ifndef TEST_SCHED_GETREFTIME_U32_H
#define TEST_SCHED_GETREFTIME_U32_H

#include "Sched_Cfg.h"
#include "Sched_Priv.h"

/**
 * @ingroup Sched
 * @brief Get the current scheduler reference time.
 * @details
 * **Goal of the function**
 *
 * Provide the current system time in milliseconds used as
 * reference for task scheduling.
 *
 * @par Interface summary
 *
 * | Interface                  | In | Out | Type / Signature  | Description              |
 * |----------------------------|----|-----|-------------------|--------------------------|
 * | Mcu_GetSystemTime_u32      | X  |     | uint32_t(void)    | Get system time (ms)     |
 * | return val                 |    |  X  | uint32_t          | Current time reference   |
 *
 * @return uint32_t
 * Current system time in milliseconds.
 */
uint32_t Sched_GetRefTime_u32(void);


#endif /* TEST_SCHED_GETREFTIME_U32_H */
