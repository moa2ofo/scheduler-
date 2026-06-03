// CEEDLING NOTICE: This generated file only to be consumed by CMock

#ifndef _SCHED_PRIV_H_ // Ceedling-generated include guard
#define _SCHED_PRIV_H_

#include "Sched_Cfg.h"

void Sched_EntrySequence(void);

void CountTime(void);
void ExecutePendingTasks(void);
uint32_t DeltaTime_u32(void);

void Sched_Task0(void);

void Sched_Task1(void);

void Sched_Task2(void);

void Sched_Task3(void);

#endif // _SCHED_PRIV_H_
