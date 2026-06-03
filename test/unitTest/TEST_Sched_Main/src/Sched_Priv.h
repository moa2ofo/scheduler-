#include <stdint.h>
#include <stdbool.h>
#include "Sched_Cfg.h"

void Sched_EntrySequence(void);
uint32_t Sched_GetRefTime_u32(void);

void CountTime(void);
void ExecutePendingTasks(void);
uint32_t DeltaTime_u32(void);

void Sched_Task0(void);
#if (SCHED_NUM_OF_TASKS > 1u)
void Sched_Task1(void);
#endif
#if (SCHED_NUM_OF_TASKS > 2u)
void Sched_Task2(void);
#endif
#if (SCHED_NUM_OF_TASKS > 3u)
void Sched_Task3(void);
#endif
#if (SCHED_NUM_OF_TASKS > 4u)
void Sched_Task4(void);
#endif
#if (SCHED_NUM_OF_TASKS > 5u)
#error "Number of tasks exceeds the maximum supported by the implementation."
#endif
