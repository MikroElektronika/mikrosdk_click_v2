/*! \file ch_rangefinder_types.h
 *
 * \brief Internal driver types for operation with the Chirp ultrasonic sensor.
 *
 * This file contains range finding types shared whith firmware doing range finding.
 *
 * You should not need to edit this file or call the driver functions directly.  Doing so
 * will reduce your ability to benefit from future enhancements and releases from Chirp.
 *
 */

/*
 Copyright 2016-2024, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */
#ifndef CH_RANGEFINDER_TYPES_H_
#define CH_RANGEFINDER_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <invn/soniclib/soniclib.h>

// total number of thresholds
#define CH101_COMMON_NUM_THRESHOLDS (6)
#define CHX01_COMMON_NUM_THRESHOLDS (6)

#ifdef INCLUDE_SHASTA_SUPPORT
#define CH_NUM_THRESHOLDS (LEN_THRESH) /*!< Number of internal detection thresholds (Shasta). */
#elif defined(INCLUDE_WHITNEY_SUPPORT)
#define CH_NUM_THRESHOLDS (6) /*!< Number of internal detection thresholds (CH201 only). */
#endif

//! Multiple detection threshold structure.
typedef struct {
	ch_thresh_t threshold[CH_NUM_THRESHOLDS];
} ch_thresholds_t;

typedef uint8_t (*ch_set_threshold_func_t)(ch_dev_t *dev_ptr, uint8_t threshold_index, uint16_t amplitude);
typedef uint16_t (*ch_get_threshold_func_t)(ch_dev_t *dev_ptr, uint8_t threshold_index);
typedef uint8_t (*ch_set_thresholds_func_t)(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr);
typedef uint8_t (*ch_get_thresholds_func_t)(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr);
typedef uint8_t (*ch_set_static_range_func_t)(ch_dev_t *dev_ptr, uint16_t static_range);
typedef uint8_t (*ch_set_rx_holdoff_func_t)(ch_dev_t *dev_ptr, uint16_t rx_holdoff);
typedef uint16_t (*ch_get_rx_holdoff_func_t)(ch_dev_t *dev_ptr);
typedef uint32_t (*ch_get_tof_us_func_t)(ch_dev_t *dev_ptr);

typedef struct {
	ch_set_threshold_func_t set_threshold;
	ch_get_threshold_func_t get_threshold;
	ch_set_thresholds_func_t set_thresholds;
	ch_get_thresholds_func_t get_thresholds;
	ch_set_static_range_func_t set_static_range;
	ch_set_rx_holdoff_func_t set_rx_holdoff;
	ch_get_rx_holdoff_func_t get_rx_holdoff;
	ch_get_tof_us_func_t get_tof_us;
} ch_rangefinder_api_funcs_t;

//! Algorithm configuration
typedef struct {
	uint16_t static_range; /*!< static target rejection range, in mm (0 if unused) */
	ch_thresholds_t
			*thresh_ptr; /*!< ptr to detection thresholds structure (if supported), should be NULL (0) for CH101 */
} ch_rangefinder_algo_config_t;

#ifdef __cplusplus
}
#endif

#endif /* CH_RANGEFINDER_TYPES_H_ */