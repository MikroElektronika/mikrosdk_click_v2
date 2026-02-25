/*! \file icu.h
 *
 * \brief Internal definitions for TDK/Chirp ICU ultrasonic sensors.
 *
 * This file contains various hardware-defined values for ICU series sensors,
 * including ICU-20201.

 * You should not need to edit this file or call the driver functions directly.  Doing so
 * will reduce your ability to benefit from future enhancements and releases from Chirp.
 *
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef ICU_H_
#define ICU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <invn/soniclib/details/ch_asic_shasta.h>

#define ICU_DATA_MEM_SIZE SHASTA_DATA_MEM_SIZE
#define ICU_DATA_MEM_ADDR SHASTA_DATA_MEM_ADDR
#define ICU_PROG_MEM_SIZE SHASTA_PROG_MEM_SIZE
#define ICU_PROG_MEM_ADDR SHASTA_PROG_MEM_ADDR
#define ICU_FW_SIZE       ICU_PROG_MEM_SIZE

#define ICU_CPU_ID SHASTA_CPU_ID_HI_VALUE /*!< Value in sensor ID reg */

#define ICU_BANDWIDTH_INDEX_1 10 /*!< Index of first sample for bandwidth calc */
#define ICU_BANDWIDTH_INDEX_2 11 /*!< Index of second sample for bandwidth calc */
#define ICU_SCALEFACTOR_INDEX 6  /*!< Index for calculating scale factor. */
#define ICU_FREQ_TRIM_LOW     (0)
#define ICU_FREQ_SEARCH_LOW   (-2)
#define ICU_FREQ_SEARCH_HIGH  (3)
#define ICU_MAX_TICK_INTERVAL 256

#define ICU_COMMON_READY_FREQ_LOCKED (0)    // TODO not needed - should be removed
#define ICU_COMMON_FREQCOUNTERCYCLES (128)  // TODO not needed - should be removed

#ifdef __cplusplus
}
#endif

#endif  // ICU_H_
