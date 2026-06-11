#include <stdint.h>


  void Mcu_Initialize();

  void Mcu_ServiceWatchdogSow();

  void Mcu_ReloadSystick();

  uint32_t Mcu_GetSystemTime_u32();