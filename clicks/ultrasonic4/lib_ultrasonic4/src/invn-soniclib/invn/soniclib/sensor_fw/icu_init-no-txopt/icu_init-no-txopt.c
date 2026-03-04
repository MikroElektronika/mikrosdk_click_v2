/*! \file icu_init-no-rxopt.c
 *
 * \brief Chirp Shasta ICU Initialization firmware interface
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

#include <invn/soniclib/soniclib.h>
#include "icu_init-no-txopt.h"
#include <invn/soniclib/details/ch_common.h>

static const ch_api_funcs_t api_funcs = {
		.set_num_samples      = NULL,
		.get_range            = NULL,
		.get_amplitude        = NULL,
		.get_iq_data          = ch_common_get_iq_data,
		.get_amplitude_data   = NULL,
		.mm_to_samples        = ch_common_mm_to_samples,
		.set_data_output      = NULL,
		.set_target_interrupt = NULL,
		.get_target_interrupt = NULL,
		.set_sample_window    = NULL,
		.get_amplitude_avg    = NULL,
		.set_tx_length        = ch_common_set_tx_length,
		.get_tx_length        = ch_common_get_tx_length,
		.algo_specific_api    = NULL,
};

static const ch_calib_funcs_t calib_funcs = {
		.prepare_pulse_timer = ch_common_prepare_pulse_timer,
		.store_pt_result     = ch_common_store_pt_result,
		.store_op_freq       = ch_common_store_op_freq,
		.store_bandwidth     = ch_common_store_bandwidth,
		.store_scalefactor   = ch_common_store_scale_factor,
		.get_locked_state    = ch_common_get_locked_state,
};

static fw_info_t self = {.api_funcs                   = &api_funcs,
                         .calib_funcs                 = &calib_funcs,
                         .fw_includes_sensor_init     = 1,
                         .fw_includes_tx_optimization = 0,
                         .freqCounterCycles           = ICU_COMMON_FREQCOUNTERCYCLES,
                         .freqLockValue               = ICU_COMMON_READY_FREQ_LOCKED,
                         .oversample                  = 0, /* This firmware does not use oversampling */
                         .max_num_thresholds          = 0};

uint8_t icu_init_no_txopt_init(ch_dev_t *dev_ptr, fw_info_t **fw_info) {
	(void)dev_ptr;

	/* Init firmware-specific function pointers */
	self.fw_text              = icu_init_no_txopt_fw_text;
	self.fw_text_size         = icu_init_no_txopt_text_size;
	self.fw_vec               = icu_init_no_txopt_fw_vec;
	self.fw_vec_size          = icu_init_no_txopt_vec_size;
	self.fw_version_string    = icu_init_no_txopt_version;
	self.ram_init             = get_ram_icu_init_no_txopt_init_ptr();
	self.get_fw_ram_init_size = get_icu_init_no_txopt_fw_ram_init_size;
	self.get_fw_ram_init_addr = get_icu_init_no_txopt_fw_ram_init_addr;

	*fw_info = &self;

	return 0;
}
