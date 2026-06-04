#ifndef SCHED_CFG_H
#define SCHED_CFG_H

void Sched_EntrySequence(void);
uint32_t Sched_GetRefTime_u32(void);

/* Default time unit for all time-based variables is milliseconds */

#define SCHED_MAX_REF_TIME (UINT32_MAX)

#define SCHED_LOOP_PERIOD (100u) // Must be an integer multiple of all task periods

#define SCHED_NUM_OF_TASKS (4u)

#define SCHED_TASK0_PERIOD (5u)
#define SCHED_TASK1_PERIOD (10u)
#define SCHED_TASK2_PERIOD (20u)
#define SCHED_TASK3_PERIOD (100u)

#define SCHED_TASK0_SHIFT (0u)
#define SCHED_TASK1_SHIFT (2u)
#define SCHED_TASK2_SHIFT (7u)
#define SCHED_TASK3_SHIFT (17u)

#endif // SCHED_CFG_H