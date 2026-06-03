#include "Sched_Task3_help.h"

/* FUNCTION TO TEST */
void Sched_Task3(void)
{
  /* Task code for 100ms period */

  /************* example code *************/
  static uint8_t counter = 0;

  counter++;

  if (counter >= 5)
  {
    counter = 0;
    toggle_led();
  }
  /****************************************/
}