#ifndef TEST_EXECUTEPENDINGTASKS_H
#define TEST_EXECUTEPENDINGTASKS_H

#include "Sched_Cfg.h"
#include "Sched_Priv.h"

#include <stddef.h>
#include <string.h>

void ExecutePendingTasks(void);

uint32_t* get_NumOfTaskCalls_au32_ptr(void);
size_t get_NumOfTaskCalls_au32_size(void);
void set_NumOfTaskCalls_au32(const uint32_t* src, size_t n);
const Task_t* get_Task_ac_ptr(void);
size_t get_Task_ac_size(void);
void set_Task_ac(const const Task_t* src, size_t n);
uint32_t get_Timer_u32(void);
void set_Timer_u32(uint32_t val);

#endif /* TEST_EXECUTEPENDINGTASKS_H */
