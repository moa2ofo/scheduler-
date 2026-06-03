/* MyLib.h */

#ifndef MYLIB_H
#define MYLIB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ========================= */
/*        MODULE GROUP       */
/* ========================= */

/**
 * @defgroup MyLib MyLib Module
 * @brief Deterministic record processing and counter management module
 *
 * The MyLib module provides a set of deterministic utilities for:
 * - Record processing with bounded accumulation
 * - Adjusted value computation with internal post-processing
 * - Global counter management with optional saturation
 * - Array scaling and analysis
 * - Record synchronization with global state
 * - High-level orchestration of operations
 * - Internal state machine execution
 *
 * ## Design constraints
 * - No dynamic allocation
 * - Fully deterministic execution
 * - Bounded loops only
 * - Explicit global state handling
 *
 * ## Global interactions
 * - g_counter_u32
 * - g_record
 * - g_systemReady_b
 *
 * ## High-level interaction
 * @startuml
 * External -> MyLib_RunStateMachine_u8
 * MyLib_RunStateMachine_u8 -> MyLib_ProcessRecord
 * MyLib_RunStateMachine_u8 -> MyLib_ComputeAdjustedValue_u32
 * MyLib_RunStateMachine_u8 -> MyLib_UpdateCounter_u8
 * @enduml
 *
 */

/* Numeric macros */
#define MYLIB_MAX_COUNT_U32 (100U)
#define MYLIB_MULT_VALUE_U8 (5U)

/* Typedef / struct */
typedef struct {
  uint16_t id_u16;
  uint32_t value_u32;
} MyLib_record_t;

/* Global variables */
extern uint32_t g_counter_u32;
extern MyLib_record_t g_record;
extern bool g_systemReady_b;

/**
 * @ingroup MyLib
 * @brief Process one record with a bounded accumulation and update module globals.
 *
 * @details
 * **Goal of the function**
 *
 * Consume an input record and apply a deterministic accumulation based on
 * `multiplier_u8`. The accumulation logic is implemented using a switch-case
 * structure to optimize specific scenarios while keeping execution bounded.
 *
 * Processing behavior:
 * - If `rec_pc == NULL`, the function returns immediately (no side effects).
 * - Otherwise, a local accumulator (`l_acc_u32`) is computed as follows:
 *   - `multiplier_u8 == 0U`
 *       → No accumulation (`l_acc_u32 = 0U`).
 *   - `multiplier_u8 == 1U`
 *       → Single direct assignment (`l_acc_u32 = rec_pc->value_u32`).
 *   - `default`
 *       → Bounded loop accumulation:
 *         `l_acc_u32 += rec_pc->value_u32` repeated `multiplier_u8` times.
 *
 * After accumulation:
 * - `g_counter_u32` is incremented by `l_acc_u32`.
 * - `MyLib_ComputeAdjustedValue_u32()` is invoked.
 *
 * Wrap-around on `uint32_t` is permitted by design.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | rec_pc                         | X  |     | const MyLib_record_t*                   |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | multiplier_u8                  | X  |     | uint8_t                                 |   X   |   1    |   0    |   1  | 0..255             | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_counter_u32                  |    |  X  | uint32_t (global)                       |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | return val                     |    |     | void                                    |       |   1    |   0    |   1  | -                  | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (rec_pc == NULL) then (yes)
 *   :return;
 * else (no)
 *   :switch(multiplier_u8);
 *     case (0U)
 *       :l_acc_u32 = 0U;
 *     case (1U)
 *       :l_acc_u32 = rec_pc->value_u32;
 *     case (default)
 *       :for l_i_u8 in [0..multiplier_u8-1];
 *         :l_acc_u32 += rec_pc->value_u32;
 *       :endfor;
 *   :endswitch;
 *   :g_counter_u32 += l_acc_u32;
 *   :call MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
 *   :return;
 * endif
 * stop
 * @enduml
 *
 * @param rec_pc
 * Pointer to the input record. If NULL, the function returns immediately.
 *
 * @param multiplier_u8
 * Accumulation selector:
 * - 0 → no accumulation
 * - 1 → single accumulation
 * - >1 → bounded loop accumulation
 *
 * @return void
 * No return value.
 */
void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);

/**
 * @ingroup MyLib
 * @brief Process one record with a bounded accumulation and update module globals.
 *
 * @details
 * **Goal of the function**
 *
 * Consume an input record and apply a deterministic accumulation based on
 * `multiplier_u8`. The accumulation logic is implemented using a switch-case
 * structure to optimize specific scenarios while keeping execution bounded.
 *
 * Processing behavior:
 * - If `rec_pc == NULL`, the function returns immediately (no side effects).
 * - Otherwise, a local accumulator (`l_acc_u32`) is computed as follows:
 *   - `multiplier_u8 == 0U`
 *       → No accumulation (`l_acc_u32 = 0U`).
 *   - `multiplier_u8 == 1U`
 *       → Single direct assignment (`l_acc_u32 = rec_pc->value_u32`).
 *   - `default`
 *       → Bounded loop accumulation:
 *         `l_acc_u32 += rec_pc->value_u32` repeated `multiplier_u8` times.
 *
 * After accumulation:
 * - `g_counter_u32` is incremented by `l_acc_u32`.
 * - `MyLib_ComputeAdjustedValue_u32()` is invoked.
 *
 * Wrap-around on `uint32_t` is permitted by design.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | rec_pc                         | X  |     | const MyLib_record_t*                   |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | multiplier_u8                  | X  |     | uint8_t                                 |   X   |   1    |   0    |   1  | 0..255             | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_counter_u32                  |    |  X  | uint32_t (global)                       |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | return val                     |    |     | void                                    |       |   1    |   0    |   1  | -                  | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (rec_pc == NULL) then (yes)
 *   :return;
 * else (no)
 *   :switch(multiplier_u8);
 *     case (0U)
 *       :l_acc_u32 = 0U;
 *     case (1U)
 *       :l_acc_u32 = rec_pc->value_u32;
 *     case (default)
 *       :for l_i_u8 in [0..multiplier_u8-1];
 *         :l_acc_u32 += rec_pc->value_u32;
 *       :endfor;
 *   :endswitch;
 *   :g_counter_u32 += l_acc_u32;
 *   :call MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
 *   :return;
 * endif
 * stop
 * @enduml
 *
 * @param rec_pc
 * Pointer to the input record. If NULL, the function returns immediately.
 *
 * @param multiplier_u8
 * Accumulation selector:
 * - 0 → no accumulation
 * - 1 → single accumulation
 * - >1 → bounded loop accumulation
 *
 * @return void
 * No return value.
 */
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);

/**
 * @ingroup MyLib
 * @brief Compute an adjusted value from a base value and an optional delta.
 *
 * @details
 * **Goal of the function**
 *
 * Multiply `base_u32` by a delta factor and apply a deterministic internal
 * post-processing step. If `delta_pc_u16` is NULL, a default delta of `1` is used.
 *
 * @par Interface summary
 *
 * | Interface           | In | Out | Type / Signature                 | Param | Factor | Offset | Size | Range              | Unit |
 * |---------------------|----|-----|----------------------------------|-------|--------|--------|------|--------------------|------|
 * | base_u32            | X  |     | uint32_t                         |   X   |   1    |   0    |   1  | 0..600             | [-]  |
 * | delta_pc_u16        | X  |     | const uint16_t*                  |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | InternalHelper_u32  | X  |  X  | uint32_t (uint32_t , uint16_t )  |       |   1    |   0    |   1  | -                  | [-]  |
 * | return val          |    |  X  | uint32_t                         |       |   1    |   0    |   1  | 0..500             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (delta_pc_u16 == NULL) then (yes)
 *   :l_d_u16 = 1;
 * else (no)
 *   :l_d_u16 = *delta_pc_u16;
 * endif
 * :l_val_u32 = base_u32 * l_d_u16;
 * :l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);
 * :return l_val_u32;
 * stop
 * @enduml
 *
 * @param base_u32
 * Base input value.
 *
 * @param delta_pc_u16
 * Optional pointer to delta factor. If NULL, delta defaults to 1.
 *
 * @return uint32_t
 * Adjusted value after applying delta and internal post-processing.
 */
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16);

/**
 * @ingroup MyLib
 * @brief Scale an array in-place and return the sum of scaled elements.
 *
 * @details
 * **Goal of the function**
 *
 * Iterate over `values_pu16` for `len_u32` elements, multiply each element by
 * `factor_u16`, store the result back into the array, and compute the sum.
 * If the pointer is NULL or the length is 0, return 0.
 *
 * The function also invokes `MyLib_ComputeAdjustedValue_u32()` to trigger a
 * secondary deterministic computation (its return value is not used).
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | values_pu16                    | X  |  X  | uint16_t*                               |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | len_u32                        | X  |     | size_t                                  |   X   |   1    |   0    |   1  | 0..600             | [-]  |
 * | factor_u16                     | X  |     | uint16_t                                |   X   |   1    |   0    |   1  | 0..65535           | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | return val                     |    |  X  | uint32_t                                |       |   1    |   0    |   1  | 0..500             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * : l_inNull_b = false;
 * 
 * if (values_pu16 == NULL or len_u32 == 0) then (yes)
 *   : l_inNull_b = true;
 * endif
 * :l_sum_u32 = 0;
 * 
 * if (l_inNull_b == false) then (process)
 *   :for l_i_u32 in [0 .. len_u32-1];
 *     :values_pu16[l_i_u32] = values_pu16[l_i_u32] * factor_u16;
 *     :l_sum_u32 += values_pu16[l_i_u32];
 *   :endfor;
 * 
 *   :call MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
 * endif
 * :return l_sum_u32;
 * 
 * stop
 * @enduml
 *
 * @param values_pu16
 * Pointer to the array to be scaled in-place. If NULL, the function returns 0.
 *
 * @param len_u32
 * Number of elements in the array. If 0, the function returns 0.
 *
 * @param factor_u16
 * Scaling factor applied to each element.
 *
 * @return uint32_t
 * Sum of the scaled array elements (wrap-around possible on overflow).
 */
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);

/**
 * @ingroup MyLib
 * @brief Scale an array in-place and return the sum of scaled elements.
 *
 * @details
 * **Goal of the function**
 *
 * It checks whether the input list is valid, then (if so) multiplies each item, 
 * sums them up, performs an internal adjustment, and finally returns the total.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | values_pu16                    | X  |  X  | uint16_t*                               |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | len_u32                        | X  |     | size_t                                  |   X   |   1    |   0    |   1  | 0..600             | [-]  |
 * | factor_u16                     | X  |     | uint16_t                                |   X   |   1    |   0    |   1  | 0..65535           | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | return val                     |    |  X  | uint32_t                                |       |   1    |   0    |   1  | 0..500             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * : l_inNull_b = false;
 * 
 * if (values_pu16 == NULL or len_u32 == 0) then (yes)
 *   : l_inNull_b = true;
 * endif
 * :l_sum_u32 = 0;
 * 
 * if (l_inNull_b == false) then (process)
 *   :for l_i_u32 in [0 .. len_u32-1];
 *     :values_pu16[l_i_u32] = values_pu16[l_i_u32] * factor_u16;
 *     :l_sum_u32 += values_pu16[l_i_u32];
 *   :endfor;
 * 
 *   :call MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
 * endif
 * :return l_sum_u32;
 * 
 * stop
 * @enduml
 *
 * @param values_pu16
 * Pointer to the array to be scaled in-place. If NULL, the function returns 0.
 *
 * @param len_u32
 * Number of elements in the array. If 0, the function returns 0.
 *
 * @param factor_u16
 * Scaling factor applied to each element.
 *
 * @return uint32_t
 * Sum of the scaled array elements (wrap-around possible on overflow).
 */
uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);

/**
 * @ingroup MyLib
 * @brief Copy a record into a destination and update module global state.
 *
 * @details
 * **Goal of the function**
 *
 * Copy the content of `src_pc` into `dest_p`. On success, mirror the copied
 * record to the module global record and mark the system as ready.
 * If any pointer is NULL, the function returns immediately without changes.
 *
 * @par Interface summary
 *
 * | Interface         | In | Out | Type / Signature       | Param | Factor | Offset | Size | Range              | Unit |
 * |-------------------|----|-----|------------------------|-------|--------|--------|------|--------------------|------|
 * | dest_p            | X  |  X  | MyLib_record_t*        |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | src_pc            | X  |     | const MyLib_record_t*  |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | g_record          |    |  X  | MyLib_record_t         |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_systemReady_b   |    |  X  | bool                   |       |   1    |   0    |   1  | false/true         | [-]  |
 * | return val        |    |     | void                   |       |   1    |   0    |   1  | -                  | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (dest_p == NULL or src_pc == NULL) then (yes)
 *   :return;
 * else (no)
 *   :dest_p->id_u16 = src_pc->id_u16;
 *   :dest_p->value_u32 = src_pc->value_u32;
 *   :g_record = *dest_p;
 *   :g_systemReady_b = true;
 *   :return;
 * endif
 * stop
 * @enduml
 *
 * @param dest_p
 * Destination record pointer. Updated if not NULL and `src_pc` is not NULL.
 *
 * @param src_pc
 * Source record pointer. Read-only. If NULL, nothing is updated.
 *
 * @return void
 * No return value.
 */
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc);

/**
 * @ingroup MyLib
 * @brief Run an orchestration sequence and return a combined result.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a deterministic sequence:
 * - Derive a delta (`l_d_u16`) from `delta_pc_u16` (default 0 if NULL)
 * - Compute a base using an internal helper
 * - Build a temporary record derived from the base
 * - Process the record via `MyLib_ProcessRecord()`
 * - Return `l_base_u32 + g_counter_u32`
 *
 * @par Interface summary
 *
 * | Interface              | In | Out | Type / Signature                         | Param | Factor | Offset | Size | Range              | Unit |
 * |------------------------|----|-----|------------------------------------------|-------|--------|--------|------|--------------------|------|
 * | start_u32              | X  |     | uint32_t                                 |   X   |   1    |   0    |   1  | 0..200             | [-]  |
 * | delta_pc_u16           | X  |     | const uint16_t*                          |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | InternalHelper_u32     |    |  X  | uint32_t (uint32_t x_u32, uint16_t y_u16)|       |   1    |   0    |   1  | -                  | [-]  |
 * | MyLib_ProcessRecord    |    |  X  | void (const MyLib_record_t *, uint8_t )  |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_counter_u32          |    |  X  | uint32_t (global)                        |       |   1    |   0    |   1  | 0..500             | [-]  |
 * | return val             |    |  X  | uint32_t                                 |       |   1    |   0    |   1  | 0..400             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (delta_pc_u16 == NULL) then (yes)
 *   :l_d_u16 = 0;
 * else (no)
 *   :l_d_u16 = *delta_pc_u16;
 * endif
 * :l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);
 * :l_r.id_u16 = (l_base_u32 & 0xFFFF);
 * :l_r.value_u32 = l_base_u32 / 2;
 * :call MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);
 * :return (l_base_u32 + g_counter_u32);
 * stop
 * @enduml
 *
 * @param start_u32
 * Input start value used to derive the orchestration base.
 *
 * @param delta_pc_u16
 * Optional pointer to delta. If NULL, delta defaults to 0.
 *
 * @return uint32_t
 * Combined result: computed base plus the current global counter.
 */
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16);

/**
 * @ingroup MyLib
 * @brief Compute a deterministic accumulated value based on an input seed and loop bound.
 *
 * @details
 * **Goal of the function**
 *
 * Provide a small, deterministic arithmetic helper that starts from `x_u32` and
 * accumulates an even-step sequence for `y_u16` iterations:
 * - Initialize `l_acc_u32` with `x_u32`
 * - For each `l_i_u16` in `[0 .. y_u16-1]`, add `(l_i_u16 * 2)` to `l_acc_u32`
 * - Return the final accumulated value
 *
 * This function is typically used as an internal building block to apply a
 * bounded and predictable post-processing step.
 *
 * @par Interface summary
 *
 * | Interface   | In | Out | Type / Signature | Param | Factor | Offset | Size | Range      | Unit |
 * |-------------|----|-----|------------------|-------|--------|--------|------|------------|------|
 * | x_u32       | X  |     | uint32_t         |   X   |   1    |   0    |   1  | 0..60535   | [-]  |
 * | y_u16       | X  |     | uint16_t         |   X   |   1    |   0    |   1  | 0..60535   | [-]  |
 * | return val  |    |  X  | uint32_t         |       |   1    |   0    |   1  | 0..700     | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :l_acc_u32 = x_u32;
 * :l_i_u16 = 0;
 * while (l_i_u16 < y_u16) is (yes)
 *   :l_acc_u32 += (l_i_u16 * 2);
 *   :l_i_u16++;
 * endwhile (no)
 * :return l_acc_u32;
 * stop
 * @enduml
 *
 * @param x_u32
 * Seed value used to initialize the accumulator.
 *
 * @param y_u16
 * Number of loop iterations. The accumulation adds `2*l_i_u16` for each
 * `l_i_u16` from 0 to `y_u16-1`.
 *
 * @return uint32_t
 * Final accumulated value (wrap-around possible on 32-bit overflow).
 */
static uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16);

/**
 * @ingroup MyLib
 * @brief Update the module global counter with optional saturation handling.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a deterministic sequence:
 * - Increment a function-static cycle counter (`l_CycleCnt_u32`)
 * - Check module readiness via `g_systemReady_b`
 *   - If not ready, return error code 1 and perform no update
 * - Compute a tentative new counter value (`l_new_u32 = g_counter_u32 + add_u32`)
 * - Apply saturation (if enabled):
 *   - If `SaturationEn_b == true` and `l_new_u32 > CounterLimit_u32`, clamp `g_counter_u32` and return code 2
 *   - Otherwise store `l_new_u32` into `g_counter_u32` and return code 0
 * - Periodically toggle `SaturationEn_b` every 16 calls (when `(l_CycleCnt_u32 & 0x0FU) == 0U`)
 *
 * @par Interface summary
 *
 * | Interface         | In | Out | Type / Signature           | Param | Factor | Offset | Size | Range              | Unit |
 * |-------------------|----|-----|----------------------------|-------|--------|--------|------|--------------------|------|
 * | add_u32           | X  |     | uint32_t                   |   X   |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | g_systemReady_b   |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | g_counter_u32     |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | CounterLimit_u32  |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | SaturationEn_b    |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | return val        |    |  X  | uint8_t                    |       |   1    |   0    |   1  | 0..2               | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :static l_CycleCnt_u32++;
 * if (g_systemReady_b == false) then (yes)
 *   :return 1;
 * else (no)
 *   :l_new_u32 = g_counter_u32 + add_u32;
 *   if ((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) then (yes)
 *     :g_counter_u32 = CounterLimit_u32;
 *     :l_ret_u8 = 2;
 *   else (no)
 *     :g_counter_u32 = l_new_u32;
 *     :l_ret_u8 = 0;
 *   endif
 *   if ((l_CycleCnt_u32 & 0x0F) == 0) then (yes)
 *     :SaturationEn_b = !SaturationEn_b;
 *   endif
 *   :return l_ret_u8;
 * endif
 * stop
 * @enduml
 *
 * @param add_u32
 * Unsigned increment added to `g_counter_u32` (wrap-around may occur before saturation check).
 *
 * @return uint8_t
 * Status code:
 * - 0: Update applied (no saturation clamp)
 * - 1: Rejected because `g_systemReady_b == false`
 * - 2: Saturation applied and `g_counter_u32` clamped to `CounterLimit_u32`
 */
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32);

/**
 * @ingroup MyLib
 * @brief Update the module global counter with optional saturation handling.
 *
 * @details
 * **Goal of the function**
 *
 * Executes a deterministic update: increments a static cycle counter, 
 * checks system readiness, computes a new counter with optional saturation, updates `g_counter_u32` accordingly, and returns a status code.
 * Toggles `SaturationEn_b` every 16 cycles and clamps the counter when enabled and limits are exceeded.
 *
 * @par Interface summary
 *
 * | Interface         | In | Out | Type / Signature           | Param | Factor | Offset | Size | Range              | Unit |
 * |-------------------|----|-----|----------------------------|-------|--------|--------|------|--------------------|------|
 * | add_u32           | X  |     | uint32_t                   |   X   |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | g_systemReady_b   |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | g_counter_u32     |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | CounterLimit_u32  |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | SaturationEn_b    |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | return val        |    |  X  | uint8_t                    |       |   1    |   0    |   1  | 0..2               | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :l_CycleCnt_u32++;
 * if (g_systemReady_b == false) then (yes)
 *   :return 1;
 * else (no)
 *   :l_new_u32 = g_counter_u32 + add_u32;
 *   if ((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) then (yes)
 *     :g_counter_u32 = CounterLimit_u32;
 *     :l_ret_u8 = 2;
 *   else (no)
 *     :g_counter_u32 = l_new_u32;
 *     :l_ret_u8 = 0;
 *   endif
 *   if ((l_CycleCnt_u32 & 0x0F) == 0) then (yes)
 *     :SaturationEn_b = !SaturationEn_b;
 *   endif
 *   :return l_ret_u8;
 * endif
 * stop
 * @enduml
 *
 * @param add_u32
 * Unsigned increment added to `g_counter_u32` (wrap-around may occur before saturation check).
 *
 * @return uint8_t
 * Status code:
 * - 0: Update applied (no saturation clamp)
 * - 1: Rejected because `g_systemReady_b == false`
 * - 2: Saturation applied and `g_counter_u32` clamped to `CounterLimit_u32`
 */
uint8_t UpdateCounter_u8(uint32_t add_u32);

/**
 * @ingroup MyLib
 * @brief Execute one step of an internal state machine operating on a record and updating the module counter.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a lightweight internal state machine that processes a record
 * across multiple calls and updates the module counter accordingly.
 * The function preserves context using static variables and orchestrates
 * record initialization, processing, and counter update by invoking
 * existing module services.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                                 | Param | Factor | Offset | Size | Range                | Unit |
 * |--------------------------------|----|-----|--------------------------------------------------|-------|--------|--------|------|----------------------|------|
 * | rec_pc                         | X  |     | const MyLib_record_t*                            |   X   |   1    |   0    |   1  | pointer / NULL       | [-]  |
 * | add_u32                        | X  |     | uint32_t                                         |   X   |   1    |   0    |   1  | 0..(wrap)            | [-]  |
 * | delta_pc_u16                   | X  |     | const uint16_t*                                  |   X   |   1    |   0    |   1  | pointer / NULL       | [-]  |
 * | MyLib_UpdateGlobalRecord       |    |  X  | void (MyLib_record_t*, const MyLib_record_t*)    |       |   1    |   0    |   1  | -                    | [-]  |
 * | MyLib_ProcessRecord            |    |  X  | void (MyLib_record_t*, uint8_t)                  |       |   1    |   0    |   1  | -                    | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 |    |  X  | uint32_t (uint32_t, const uint16_t*)             |       |   1    |   0    |   1  | 0..(wrap)            | [-]  |
 * | MyLib_UpdateCounter_u8         |    |  X  | uint8_t (uint32_t)                               |       |   1    |   0    |   1  | 0..2                 | [-]  |
 * | return val                     |    |  X  | uint8_t                                          |       |   1    |   0    |   1  | 0..3                 | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 *
 * :static uint8_t l_State_u8;
 * :static MyLib_record_t l_LastRecord;
 * :static uint32_t l_LastAdjusted_u32;
 * :uint8_t l_ret_u8 = 0;
 * :uint32_t l_UpdateValue_u32 = 0;
 *
 * switch (l_State_u8)
 *
 * case (0: Init)
 *   if (rec_pc == NULL) then (yes)
 *     :l_ret_u8 = 1;
 *   else (no)
 *     :MyLib_UpdateGlobalRecord(&l_LastRecord, rec_pc);
 *     :l_State_u8 = 1;
 *     :l_ret_u8 = 0;
 *   endif
 *   break
 *
 * case (1: Process)
 *   :MyLib_ProcessRecord(&l_LastRecord, MYLIB_MULT_VALUE_U8);
 *   :l_LastAdjusted_u32 =
 *   MyLib_ComputeAdjustedValue_u32(l_LastRecord.value_u32, delta_pc_u16);
 *   :l_State_u8 = 2;
 *   :l_ret_u8 = 0;
 *   break
 *
 * case (2: Update counter)
 *   :l_UpdateValue_u32 = add_u32 + l_LastAdjusted_u32;
 *   :l_ret_u8 = MyLib_UpdateCounter_u8(l_UpdateValue_u32);
 *   :l_State_u8 = 0;
 *   break
 *
 * endswitch
 *
 * :return l_ret_u8;
 * stop
 * @enduml
 *
 * @param rec_pc
 * Pointer to the input record used during the initialization state.
 * If NULL, the initialization step is rejected.
 *
 * @param add_u32
 * Increment applied to the module counter during the counter update state.
 *
 * @param delta_pc_u16
 * Optional pointer to a delta value used in the adjusted value computation.
 * If NULL, the adjustment routine applies its default behaviour.
 *
 * @return uint8_t
 * Status code:
 * - 0: Step executed successfully
 * - 1: Initialization rejected because `rec_pc == NULL`
 * - 2: Counter update routine reported saturation
 */
uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16);

#endif /* MYLIB_H */
