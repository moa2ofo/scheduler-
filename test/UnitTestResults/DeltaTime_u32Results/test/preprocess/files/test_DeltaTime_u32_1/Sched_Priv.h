// CEEDLING NOTICE: This generated file only to be consumed by CMock

#ifndef _SCHED_PRIV_H_ // Ceedling-generated include guard
#define _SCHED_PRIV_H_

#include "Sched_Cfg.h"

typedef void (*const TaskHandler_t)(void);

typedef struct {
  TaskHandler_t handler_;
  const uint32_t period_cu32;
  const uint32_t shift_cu32;
} Task_t;

void CountTime(void);
void ExecutePendingTasks(void);
void Sched_Task0(void);

void Sched_Task1(void);

void Sched_Task2(void);

void Sched_Task3(void);

#endif // _SCHED_PRIV_H_
