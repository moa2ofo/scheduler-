#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_Sched_Cfg.h"


static struct mock_Sched_CfgInstance
{
  unsigned char placeHolder;
} Mock;

extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_Sched_Cfg_Verify(void)
{
}

void mock_Sched_Cfg_Init(void)
{
  mock_Sched_Cfg_Destroy();
}

void mock_Sched_Cfg_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

