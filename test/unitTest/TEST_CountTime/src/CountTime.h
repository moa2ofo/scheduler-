#ifndef TEST_COUNTTIME_H
#define TEST_COUNTTIME_H

#include "Sched_Cfg.h"
#include "Sched_Priv.h"

#include <stddef.h>

/**
 * @brief Update scheduler time base.
 * @ingroup Sched
 */
void CountTime(void);

uint32_t *get_NumOfTaskCalls_au32_ptr(void);
size_t get_NumOfTaskCalls_au32_size(void);
uint32_t get_Timer_u32(void);
void set_Timer_u32(uint32_t val);

#endif /* TEST_COUNTTIME_H */
