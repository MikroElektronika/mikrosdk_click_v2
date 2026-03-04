/*! \file ch201_gprmt.c
 *
 * \brief Chirp CH201 General Purpose Rangefinding Multi-Threshold firmware interface
 *
 * This file contains function definitions to interface a specific sensor firmware
 * package to SonicLib, including the main initialization routine for the firmware.
 * That routine initializes various fields within the \a ch_dev_t device descriptor
 * and specifies the proper functions to implement SonicLib API calls.  Those may
 * either be common implementations or firmware-specific routines located in this file.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#include "ch201_gprmt.h"
#include <invn/soniclib/details/ch_common.h>

static const ch_rangefinder_api_funcs_t algo_api_funcs = {
		.set_threshold    = NULL,
		.get_threshold    = NULL,
		.set_thresholds   = ch_rangefinder_set_thresholds,
		.get_thresholds   = ch_rangefinder_get_thresholds,
		.set_static_range = NULL,
		.set_rx_holdoff   = ch_rangefinder_set_rx_holdoff,
		.get_rx_holdoff   = ch_rangefinder_get_rx_holdoff,
		.get_tof_us       = NULL,
};

static const ch_api_funcs_t api_funcs = {
		.set_num_samples    = ch_common_set_num_samples,
		.get_range          = ch_rangefinder_get_range,
		.get_amplitude      = ch_rangefinder_get_amplitude,
		.get_iq_data        = ch_common_get_iq_data,
		.get_amplitude_data = ch_common_get_amplitude_data,
		.mm_to_samples      = ch_common_mm_to_samples,
		.set_sample_window  = ch_common_set_sample_window,
		.get_amplitude_avg  = ch_common_get_amplitude_avg,
		.set_rx_low_gain    = ch_common_set_rx_low_gain,
		.get_rx_low_gain    = ch_common_get_rx_low_gain,
		.set_tx_length      = NULL,  // not supported
		.get_tx_length      = ch_common_get_tx_length,
		.algo_specific_api  = &algo_api_funcs,
};

static const ch_calib_funcs_t calib_funcs = {
		.prepare_pulse_timer = ch_common_prepare_pulse_timer,
		.store_pt_result     = ch_common_store_pt_result,
		.store_op_freq       = ch_common_store_op_freq,
		.store_bandwidth     = ch_common_store_bandwidth,
		.store_scalefactor   = ch_common_store_scale_factor,
		.get_locked_state    = ch_common_get_locked_state,
};

static fw_info_t self = {
		.api_funcs                   = &api_funcs,
		.calib_funcs                 = &calib_funcs,
		.fw_includes_sensor_init     = 1,
		.fw_includes_tx_optimization = 0,
		.freqCounterCycles           = CH201_COMMON_FREQCOUNTERCYCLES,
		.freqLockValue               = CH201_COMMON_READY_FREQ_LOCKED,
		.max_samples                 = CH201_GPRMT_MAX_SAMPLES,     /* Init max sample count */
		.max_num_thresholds          = CHX01_COMMON_NUM_THRESHOLDS, /* Set max number of thresholds */
		.oversample                  = 0,                           /* This firmware does not use oversampling */
};

uint8_t ch201_gprmt_init(ch_dev_t *dev_ptr, fw_info_t **fw_info) {
	dev_ptr->part_number = CH201_PART_NUMBER;

	/* Init firmware-specific function pointers */
	self.fw_text              = ch201_gprmt_fw_text;
	self.fw_text_size         = ch201_gprmt_text_size;
	self.fw_vec               = ch201_gprmt_fw_vec;
	self.fw_vec_size          = ch201_gprmt_vec_size;
	self.fw_version_string    = ch201_gprmt_version;
	self.ram_init             = get_ram_ch201_gprmt_init_ptr();
	self.get_fw_ram_init_size = get_ch201_gprmt_fw_ram_init_size;
	self.get_fw_ram_init_addr = get_ch201_gprmt_fw_ram_init_addr;

	*fw_info = &self;

	return 0;
}
