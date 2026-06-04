#ifndef SCHED_CFG_H
#define SCHED_CFG_H

void Sched_EntrySequence(void);
uint32_t Sched_GetRefTime_u32(void);

/* Default time unit for all time-based variables is milliseconds */

#define SCHED_MAX_REF_TIME (UINT32_MAX)

const uint32 SCHED_LOOP_PERIOD = (100u); // Must be an integer multiple of all task periods

const uint32 SCHED_NUM_OF_TASKS = (4u);

const uint32 SCHED_TASK0_PERIOD = (5u);
const uint32 SCHED_TASK1_PERIOD = (10u);
const uint32 SCHED_TASK2_PERIOD = (20u);
const uint32 SCHED_TASK3_PERIOD = (100u);

const uint32 SCHED_TASK0_SHIFT = (0u);
const uint32 SCHED_TASK1_SHIFT = (2u);
const uint32 SCHED_TASK2_SHIFT = (7u);
const uint32 SCHED_TASK3_SHIFT = (17u);

#endif // SCHED_CFG_H