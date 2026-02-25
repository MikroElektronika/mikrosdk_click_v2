/*! \file ch101_gpr.c
 *
 * \brief Chirp CH101 General Purpose Rangefinding firmware interface
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

#include "ch101_gpr.h"
#include <invn/soniclib/details/ch_common.h>

static const ch_rangefinder_api_funcs_t algo_api_funcs = {
		.set_threshold    = NULL,
		.get_threshold    = NULL,
		.set_thresholds   = NULL,
		.get_thresholds   = NULL,
		.set_static_range = ch_rangefinder_set_static_range,
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
		.set_cal_result     = ch_common_set_cal_result,
		.get_cal_result     = ch_common_get_cal_result,
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
		.freqCounterCycles           = CH101_COMMON_FREQCOUNTERCYCLES,
		.freqLockValue               = CH101_COMMON_READY_FREQ_LOCKED,
		.oversample                  = 0, /* This firmware does not use oversampling */
		.max_samples                 = CH101_GPR_MAX_SAMPLES,
};

uint8_t ch101_gpr_init(ch_dev_t *dev_ptr, fw_info_t **fw_info) {

	dev_ptr->part_number = CH101_PART_NUMBER;

	/* Init firmware-specific function pointers */
	self.fw_text              = ch101_gpr_fw_text;
	self.fw_text_size         = ch101_gpr_text_size;
	self.fw_vec               = ch101_gpr_fw_vec;
	self.fw_vec_size          = ch101_gpr_vec_size;
	self.fw_version_string    = ch101_gpr_version;
	self.ram_init             = get_ram_ch101_gpr_init_ptr();
	self.get_fw_ram_init_size = get_ch101_gpr_fw_ram_init_size;
	self.get_fw_ram_init_addr = get_ch101_gpr_fw_ram_init_addr;

	*fw_info = &self;

	return 0;
}

uint8_t ch101_gpr_get_target_in_ringdown(ch_dev_t *dev_ptr) {
	uint8_t in_ringdown = 0;

	chdrv_read_byte(dev_ptr, CH101_GPR_REG_IN_RINGDOWN, &in_ringdown);

	return in_ringdown;
}

uint16_t ch101_gpr_get_in_ringdown_ths(ch_dev_t *dev_ptr) {
	uint16_t in_ringdown_ths = 0;

	chdrv_read_word(dev_ptr, CH101_GPR_REG_IN_RINGDOWN_THS, &in_ringdown_ths);

	return in_ringdown_ths;
}

void ch101_gpr_set_in_ringdown_ths(ch_dev_t *dev_ptr, uint16_t in_ringdown_ths) {
	chdrv_write_word(dev_ptr, CH101_GPR_REG_IN_RINGDOWN_THS, in_ringdown_ths);
}

uint8_t ch101_gpr_get_in_ringdown_idx(ch_dev_t *dev_ptr) {
	uint8_t in_ringdown_idx = 0;

	chdrv_read_byte(dev_ptr, CH101_GPR_REG_IN_RINGDOWN_IDX, &in_ringdown_idx);

	return in_ringdown_idx;
}

void ch101_gpr_set_in_ringdown_idx(ch_dev_t *dev_ptr, uint8_t in_ringdown_idx) {
	chdrv_write_byte(dev_ptr, CH101_GPR_REG_IN_RINGDOWN_IDX, in_ringdown_idx);
}