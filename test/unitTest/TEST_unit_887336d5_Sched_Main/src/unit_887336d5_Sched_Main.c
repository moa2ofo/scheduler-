#include "unit_887336d5_Sched_Main_help.h"

/* FUNCTION TO TEST */
int32_t Sched_Main(void) {
  Sched_EntrySequence();

  while(true) {
    CountTime();
    ExecutePendingTasks();
  }
}
