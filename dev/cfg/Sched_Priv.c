#include "Sched_Priv.h"
#include "Mcu.h"

void Sched_Task0(void)
{
  /* Task code for 5ms period */
}

void Sched_Task1(void)
{
  /* Task code for 10ms period */
}

void Sched_Task2(void)
{
  /* Task code for 20ms period */
  Mcu_ServiceWatchdog();
}

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
