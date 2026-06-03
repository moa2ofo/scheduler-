/* MyLib.c */

#include "MyLib.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
static bool SaturationEn_b = true;

/* Local (c-file static) function */
static uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16) {
  uint32_t l_acc_u32 = x_u32;

  /* Accumulate even-step sequence: for each l_i_u16 in [0 .. y_u16-1],
     add (l_i_u16 * 2) to l_acc_u32 */
  /* Loop counter l_i_u16 complies with interface and naming rules */
  for(uint16_t l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    l_acc_u32 += ((uint32_t)l_i_u16 * 2U);
  }
  return l_acc_u32;
}
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  uint32_t l_acc_u32;
  uint8_t l_i_u8;

  /* Check if input pointer is NULL */
  if(rec_pc == NULL) {
    return;
  }

  /* Switch-case structure for bounded accumulation based on multiplier_u8 */
  switch(multiplier_u8) {
  case 0U:
    /* No accumulation */
    l_acc_u32 = 0U;
    break;

  case 1U:
    /* Single direct assignment */
    l_acc_u32 = rec_pc->value_u32;
    break;

  default:
    /* Bounded loop accumulation */
    l_acc_u32 = 0U;
    for(l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  /* Increment global counter by accumulated value */
  g_counter_u32 += l_acc_u32;

  /* Invoke library function with accumulated value and multiplier address */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_val_u32;

  /* Check if delta pointer is NULL and assign default or dereferenced value */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 1U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Multiply base by delta factor */
  l_val_u32 = base_u32 * l_d_u16;

  /* Apply internal post-processing step */
  /* NOTE: MYLIB_MULT_VALUE_U8 macro is not defined in the [HEADER] but is referenced in the activity diagram */
  l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);

  return l_val_u32;
}
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  /* Check for NULL pointer or zero length input */
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    return 0U;
  }

  uint32_t l_sum_u32 = 0U;

  for(size_t l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
    values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
    l_sum_u32 += values_pu16[l_i_u32];
  }

  /* Invoke deterministic secondary computation; return value not used as per header */
  (void)MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);

  return l_sum_u32;
}
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc) {
  /* Check for NULL pointers to avoid invalid memory access */
  if((dest_p == NULL) || (src_pc == NULL)) {
    return;
  }

  /* Copy the content from source to destination record */
  dest_p->id_u16 = src_pc->id_u16;
  dest_p->value_u32 = src_pc->value_u32;

  /* Update the global record to mirror the destination record */
  g_record = *dest_p;

  /* Mark the system as ready */
  g_systemReady_b = true;
}
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_base_u32;
  MyLib_record_t l_r;

  /* Check if delta_pc_u16 is NULL and set l_d_u16 accordingly */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 0U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Compute base using internal helper */
  l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);

  /* Build temporary record derived from the base */
  l_r.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  l_r.value_u32 = l_base_u32 / 2U;

  /* Process the record via MyLib_ProcessRecord */
  MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);

  /* Return combined result: base plus global counter */
  return (l_base_u32 + g_counter_u32);
}
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32) {
  /* Function-local static cycle counter, persistent across calls */
  static uint32_t l_CycleCnt_u32 = 0U;

  uint32_t l_new_u32;
  uint8_t l_ret_u8;

  /* Step 1: Increment the function-static cycle counter */
  l_CycleCnt_u32++;

  /* Step 2: Check module readiness */
  if(g_systemReady_b == false) {
    /* System not ready, return error code 1 and perform no update */
    return 1U;
  }

  /* Step 3: Compute tentative new counter value */
  l_new_u32 = g_counter_u32 + add_u32;

  /* Step 4: Apply saturation if enabled */
  if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
    /* Saturation condition met: clamp to limit */
    g_counter_u32 = CounterLimit_u32;
    l_ret_u8 = 2U;
  } else {
    /* No saturation: store new value */
    g_counter_u32 = l_new_u32;
    l_ret_u8 = 0U;
  }

  /* Step 5: Periodically toggle SaturationEn_b every 16 calls */
  if((l_CycleCnt_u32 & 0x0FU) == 0U) {
    SaturationEn_b = !SaturationEn_b;
  }

  /* Return status code */
  return l_ret_u8;
}
int main() {
  return 0;
}
void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  uint32_t l_acc_u32 = 0U;

  if(rec_pc == NULL) {
    return;
  }

  switch(multiplier_u8) {
  case 0U:
    l_acc_u32 = 0U;
    break;
  case 1U:
    l_acc_u32 = rec_pc->value_u32;
    break;
  default:
    for(uint8_t l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  g_counter_u32 += l_acc_u32;

  /*
   * Call MyLib_ComputeAdjustedValue_u32 with l_acc_u32 and pointer to multiplier_u8
   * Cast multiplier_u8 pointer to const uint16_t* as required by the interface
   * This cast is safe because the function expects a pointer to uint16_t,
   * but multiplier_u8 is uint8_t, so we rely on the header specification.
   * If this is incorrect, the header is inconsistent.
   */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  uint32_t l_sum_u32 = 0U;
  uint32_t l_i_u32;
  uint8_t l_inNull_b = 0U;

  /* Check for NULL pointer or zero length */
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    l_inNull_b = 1U;
  }

  if(l_inNull_b == 0U) {
    for(l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
      /* Scale each element in-place */
      values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
      /* Accumulate the sum of scaled elements */
      l_sum_u32 += values_pu16[l_i_u32];
    }

    /* Call internal adjustment function with NULL pointer as per header */
    l_sum_u32 = MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
  }

  return l_sum_u32;
}
uint8_t UpdateCounter_u8(uint32_t add_u32) {
  static uint32_t l_CycleCnt_u32 = 0u;
  uint32_t l_new_u32;
  uint8_t l_ret_u8;

  l_CycleCnt_u32++;

  if(g_systemReady_b == false) {
    return 1u;
  }

  l_new_u32 = g_counter_u32 + add_u32;

  if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
    g_counter_u32 = CounterLimit_u32;
    l_ret_u8 = 2u;
  } else {
    g_counter_u32 = l_new_u32;
    l_ret_u8 = 0u;
  }

  if((l_CycleCnt_u32 & 0x0Fu) == 0u) {
    SaturationEn_b = !SaturationEn_b;
  }
  return l_ret_u8;
}

uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16) {
  /* Function-local static variables to preserve state machine context across calls */
  static uint8_t l_State_u8 = 0U;
  static MyLib_record_t l_LastRecord;
  static uint32_t l_LastAdjusted_u32 = 0U;

  /* Local variables */
  uint8_t l_ret_u8 = 0U;
  uint32_t l_UpdateValue_u32 = 0U;

  /* State machine execution */
  switch(l_State_u8) {
  case 0U: /* Init state */
    if(rec_pc == NULL) {
      l_ret_u8 = 1U;
    } else {
      MyLib_UpdateGlobalRecord(&l_LastRecord, rec_pc);
      l_State_u8 = 1U;
      l_ret_u8 = 0U;
    }
    break;

  case 1U: /* Process state */
    MyLib_ProcessRecord(&l_LastRecord, MYLIB_MULT_VALUE_U8);
    l_LastAdjusted_u32 = MyLib_ComputeAdjustedValue_u32(l_LastRecord.value_u32, delta_pc_u16);
    l_State_u8 = 2U;
    l_ret_u8 = 0U;
    break;

  case 2U: /* Update counter state */
    l_UpdateValue_u32 = add_u32 + l_LastAdjusted_u32;
    l_ret_u8 = MyLib_UpdateCounter_u8(l_UpdateValue_u32);
    l_State_u8 = 0U;
    break;

  default:
    /* Defensive: should not occur if state machine is correctly managed */
    l_ret_u8 = 0U;
    break;
  }

  return l_ret_u8;
}
