/*! \file icu_gpt.c
 *
 * \brief Chirp Shasta General Purpose Rangefinding firmware interface
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
#define CH_LOG_MODULE_NAME "ICU_GPT"
#include <invn/soniclib/ch_log.h>

#include "icu_gpt.h"
#include <invn/soniclib/ch_rangefinder_types.h>
#include <invn/soniclib/details/ch_common.h>

#define ICU_DEVICES_NUM (3)
#define ODR_VALUES_NUM  (5)

static const ch_thresholds_t default_thresholds = {  // default thresholds for ICU-x0201
		.threshold = {
				{0, 800},  /* threshold 0 */
				{20, 400}, /* threshold 1 */
				{37, 200}, /* threshold 2 */
				{50, 100}, /* threshold 3 */
				{80, 70},  /* threshold 4 */
				{120, 50}, /* threshold 5 */
				{0, 0},    /* threshold 6 */
				{0, 0},    /* threshold 7 */
		}};

/* forward "declarations" for api_funcs */
static uint16_t get_amplitude(ch_dev_t *dev_ptr) {
	return icu_gpt_algo_get_target_amplitude(dev_ptr, CH_DEFAULT_TARGET_NUM);
}

static uint32_t get_tof_us(ch_dev_t *dev_ptr) {
	return icu_gpt_algo_get_target_tof_us(dev_ptr, CH_DEFAULT_TARGET_NUM);
}

static uint8_t set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *lib_thresh_buf_ptr) {
	if (!dev_ptr->sensor_connected || dev_ptr->asic_gen != CH_ASIC_GEN_2_SHASTA) {
		return RET_ERR;
	}

	return icu_gpt_set_thresholds(dev_ptr, CH_DEFAULT_MEAS_NUM, lib_thresh_buf_ptr);
}

static uint8_t get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *lib_thresh_buf_ptr) {
	if (!dev_ptr->sensor_connected || (lib_thresh_buf_ptr == NULL)) {
		return RET_ERR;
	}

	return icu_gpt_get_thresholds(dev_ptr, CH_DEFAULT_MEAS_NUM, lib_thresh_buf_ptr);
}

static uint8_t set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t num_samples) {
	return icu_gpt_set_rx_holdoff(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);
}

static uint16_t get_rx_holdoff(ch_dev_t *dev_ptr) {
	return icu_gpt_get_rx_holdoff(dev_ptr, CH_DEFAULT_MEAS_NUM);
}

static uint8_t set_static_range(ch_dev_t *dev_ptr, uint16_t num_samples) {
	if (!dev_ptr->sensor_connected || dev_ptr->asic_gen != CH_ASIC_GEN_2_SHASTA) {
		return RET_ERR;
	}

	return icu_gpt_set_static_filter(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);
}

static uint32_t get_range(ch_dev_t *dev_ptr, ch_range_t range_type) {
	return icu_gpt_algo_get_target_range(dev_ptr, CH_DEFAULT_TARGET_NUM, range_type);
}

static const ch_rangefinder_api_funcs_t algo_api_funcs = {
		.set_thresholds   = set_thresholds,
		.get_thresholds   = get_thresholds,
		.set_static_range = set_static_range,
		.set_rx_holdoff   = set_rx_holdoff,
		.get_rx_holdoff   = get_rx_holdoff,
		.get_tof_us       = get_tof_us,
};

static const ch_api_funcs_t api_funcs = {
		.set_num_samples      = ch_common_set_num_samples,
		.get_range            = get_range,
		.get_amplitude        = get_amplitude,
		.get_iq_data          = ch_common_get_iq_data,
		.get_amplitude_data   = ch_common_get_amplitude_data,
		.mm_to_samples        = ch_common_mm_to_samples,
		.set_data_output      = icu_gpt_algo_set_data_output,
		.set_target_interrupt = ch_common_set_target_interrupt,
		.get_target_interrupt = ch_common_get_target_interrupt,
		.set_sample_window    = ch_common_set_sample_window,
		.get_amplitude_avg    = ch_common_get_amplitude_avg,
		.set_tx_length        = ch_common_set_tx_length,
		.get_tx_length        = ch_common_get_tx_length,
		.meas_get_iq_output   = icu_gpt_algo_get_iq_output,
		.meas_set_iq_output   = icu_gpt_algo_set_iq_output,
		.algo_specific_api    = &algo_api_funcs,
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
		.freqCounterCycles           = ICU_COMMON_FREQCOUNTERCYCLES,
		.freqLockValue               = ICU_COMMON_READY_FREQ_LOCKED,
		.max_num_thresholds          = ICU_GPT_NUM_THRESHOLDS,
		.oversample                  = 0, /* This firmware does not use oversampling */
};

static void thresh_lib_to_sensor(const ch_dev_t *dev_ptr, const ch_thresholds_t *lib_thresh_ptr,
                                 thresholds_t *sens_thresh_ptr) {
	for (uint8_t thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {

		sens_thresh_ptr->threshold[thresh_num] = lib_thresh_ptr->threshold[thresh_num].level;

		if (thresh_num == (dev_ptr->current_fw->max_num_thresholds - 1)) {
			sens_thresh_ptr->stop_index[thresh_num] = dev_ptr->current_fw->max_samples;
		} else {
			sens_thresh_ptr->stop_index[thresh_num] = lib_thresh_ptr->threshold[thresh_num + 1].start_sample;
		}
	}
}

static uint8_t thresh_sensor_to_lib(const ch_dev_t *dev_ptr, const thresholds_t *sens_thresh_ptr,
                                    ch_thresholds_t *lib_thresh_ptr) {
	uint16_t start_sample;

	if (dev_ptr->current_fw->max_num_thresholds < 2)
		return RET_ERR;

	for (uint8_t thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {

		if (thresh_num == 0) {
			start_sample = 0;
		} else {
			start_sample = sens_thresh_ptr->stop_index[thresh_num - 1];
		}

		lib_thresh_ptr->threshold[thresh_num].start_sample = start_sample;

		lib_thresh_ptr->threshold[thresh_num].level = sens_thresh_ptr->threshold[thresh_num];
	}
	return RET_OK;
}

static uint8_t read_target_list(ch_dev_t *dev_ptr, InvnAlgoRangeFinderOutput *algo_out_ptr) {
	uint8_t err = 0;

	/* Get current sensor algo output (includes target list) */
	if ((err = chdrv_algo_out_read(dev_ptr, (void *)algo_out_ptr)))  // copy algo output to ch_dev_t
		goto handle_error;
	if ((err = ch_common_read_meas_config(dev_ptr)))
		goto handle_error;
handle_error:
	return err;
}

static uint8_t get_n_delay_cic(const ch_dev_t *dev_ptr, int8_t *n_delay_cic) {
	// table below obtained experimentally. tuned to minimize offset across
	// parts and cic_odr settings.
	static const int8_t num_delay_cic[ICU_DEVICES_NUM][ODR_VALUES_NUM] = {
			/* ODR : 2, 3, 4, 5, 6  */

			{4, 4, 5, 6, 6},  // Tahoe   ICU10201
			{3, 3, 4, 5, 6},  // Sierra  ICU20201
			{3, 3, 3, 4, 5}   // Trinity ICU30201

	};
	uint8_t odr_out = dev_ptr->odr_out;
	if ((odr_out < CH_ODR_FREQ_DIV_32) || (odr_out > CH_ODR_FREQ_DIV_2)) {
		return RET_ERR;  // Error: Invalid ODR.
	}
	uint8_t part_idx = 0;  // Part type index for num_delay_cic array.
	switch (dev_ptr->part_number) {
	case ICU10201_PART_NUMBER: {
		part_idx = 0;
		break;
	}
	case ICU20201_PART_NUMBER: {
		part_idx = 1;
		break;
	}
	case ICU30201_PART_NUMBER: {
		part_idx = 2;
		break;
	}
	default: {
		part_idx = 1;  // Assume ICU-20201
		break;
	}
	}

	CH_LOG_TRACE_MSG(" ODR = %d, PNum: %d, PIdx: %d, OIdx: %d, cic_delay: %d ", odr_out, dev_ptr->part_number, part_idx,
	                 odr_out - 2, (uint8_t)num_delay_cic[part_idx][odr_out - 2]);

	*n_delay_cic = num_delay_cic[part_idx][odr_out - CH_ODR_FREQ_DIV_32];
	return RET_OK;
}

static uint8_t get_tof_offset_lsb(const ch_dev_t *dev_ptr, int32_t *tof_offset_lsb) {
	int32_t pre_rx_ticks;
	*tof_offset_lsb = 0;

	uint8_t odr_out = dev_ptr->odr_out;
	// Compensate for offset error due to pre-rx transmit/count delay and CIC filter delay
	uint32_t pre_rx_cycles = dev_ptr->meas_pre_rx_cycles[dev_ptr->last_measurement];

	if (odr_out > CH_ODR_FREQ_DIV_8) {
		pre_rx_ticks = pre_rx_cycles << (odr_out - CH_ODR_FREQ_DIV_8);
	} else if (odr_out < CH_ODR_FREQ_DIV_8) {
		pre_rx_ticks = pre_rx_cycles >> (CH_ODR_FREQ_DIV_8 - odr_out);
	} else {
		pre_rx_ticks = pre_rx_cycles;
	}
	int8_t n_delay_cic;
	if (get_n_delay_cic(dev_ptr, &n_delay_cic) != RET_OK) {
		return RET_ERR;  // Indicates invalid ODR
	}
	*tof_offset_lsb = (n_delay_cic << 7) - pre_rx_ticks;
	return RET_OK;
}

uint8_t icu_gpt_init(ch_dev_t *dev_ptr, fw_info_t **fw_info) {
	(void)dev_ptr;

	/* Init firmware-specific function pointers */
	self.fw_text              = icu_gpt_fw_text;
	self.fw_text_size         = icu_gpt_text_size;
	self.fw_vec               = icu_gpt_fw_vec;
	self.fw_vec_size          = icu_gpt_vec_size;
	self.fw_version_string    = icu_gpt_version;
	self.ram_init             = get_ram_icu_gpt_init_ptr();
	self.get_fw_ram_init_size = get_icu_gpt_fw_ram_init_size;
	self.get_fw_ram_init_addr = get_icu_gpt_fw_ram_init_addr;

	*fw_info = &self;

	return 0;
}

uint8_t icu_gpt_algo_init(ch_dev_t *dev_ptr, InvnAlgoRangeFinderConfig *algo_cfg) {
	uint8_t ch_err = ch_init_algo(dev_ptr);
	/* Save pointer to algo config in user space, to be able to use it seemlessly in interface code */
	dev_ptr->algo_cfg_ptr = algo_cfg;

	return ch_err;
}

uint8_t icu_gpt_algo_configure(ch_dev_t *dev_ptr, uint8_t meas_num, const icu_gpt_algo_config_t *algo_config_ptr,
                               const ch_thresholds_t *lib_thresh_ptr) {
	InvnAlgoRangeFinderConfig *algo_cfg_ptr   = (InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr);
	InvnAlgoRangeFinderMeasConfig *config_ptr = &(algo_cfg_ptr->meas_cfg[meas_num]);

	config_ptr->ringdown_cancel_samples = algo_config_ptr->ringdown_cancel_samples;  // TODO use zero for default ??
	config_ptr->static_target_samples   = algo_config_ptr->static_filter_samples;
	config_ptr->num_ranges              = algo_config_ptr->num_ranges;
	config_ptr->iq_output_format        = (uint8_t)algo_config_ptr->iq_output_format;
	config_ptr->filter_update_modulo    = algo_config_ptr->filter_update_interval;

	if (lib_thresh_ptr == NULL) {
		lib_thresh_ptr = (ch_thresholds_t *)&default_thresholds;
	}

	thresh_lib_to_sensor(dev_ptr, lib_thresh_ptr,
	                     (thresholds_t *)&(config_ptr->thresholds));  // convert format and copy to meas config

	return RET_OK;
}

void icu_gpt_algo_reset(ch_dev_t *dev_ptr, uint8_t meas_num) {
	InvnAlgoRangeFinderConfig *algo_cfg_ptr = (InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr);

	if (algo_cfg_ptr == NULL)
		return;

	InvnAlgoRangeFinderMeasConfig *meas_cfg_ptr = &(algo_cfg_ptr->meas_cfg[meas_num]);

	// Init meas config
	meas_cfg_ptr->num_ranges              = 0;
	meas_cfg_ptr->ringdown_cancel_samples = 0;
	meas_cfg_ptr->static_target_samples   = 0;
	meas_cfg_ptr->iq_output_format        = 0;
	meas_cfg_ptr->filter_update_modulo    = 0;

	// Init thresholds
	for (int i = 0; i < LEN_THRESH; i++) {
		meas_cfg_ptr->thresholds.stop_index[i] = 0;
		meas_cfg_ptr->thresholds.threshold[i]  = 0;
	}
}

ch_output_type_t icu_gpt_algo_get_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num) {
	if (dev_ptr->algo_cfg_ptr == NULL) {
		/* Algo not configured, the default format of raw data is IQ */
		return CH_OUTPUT_IQ;
	}
	return ((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].iq_output_format;
}

uint8_t icu_gpt_algo_set_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num, ch_output_type_t output_format) {
	if (dev_ptr->algo_cfg_ptr == NULL) {
		/* Algo not configured, can't change raw data format */
		return RET_ERR;
	}

	((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].iq_output_format =
			(uint8_t)output_format;

	return ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
}

uint8_t icu_gpt_algo_get_num_targets(ch_dev_t *dev_ptr) {
	uint8_t num_valid_targets = 0; /* default value in case of read error */
	InvnAlgoRangeFinderOutput *sens_algo_out_addr =
			(InvnAlgoRangeFinderOutput *)(uintptr_t)dev_ptr->algo_info.algo_out_ptr;

	uint16_t num_targets_addr = (uint16_t)(uintptr_t) & (sens_algo_out_addr->tL.num_valid_targets);

	chdrv_read_byte(dev_ptr, num_targets_addr, &num_valid_targets);

	return num_valid_targets;
}

uint16_t icu_gpt_algo_get_target_amplitude(ch_dev_t *dev_ptr, uint8_t target_num) {
	uint16_t amplitude     = 0;
	uint16_t amplitude_reg = 0;
	InvnAlgoRangeFinderOutput *sens_algo_out_addr =
			(InvnAlgoRangeFinderOutput *)(uintptr_t)dev_ptr->algo_info.algo_out_ptr;

	if (!dev_ptr->sensor_connected || (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY)) {
		return 0;
	}

	amplitude_reg = (uint16_t)(uintptr_t) & (sens_algo_out_addr->tL.targets[target_num].amplitude);
	chdrv_read_word(dev_ptr, amplitude_reg, &amplitude);

	return amplitude;
}

uint32_t icu_gpt_algo_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type) {
	InvnAlgoRangeFinderOutput algo_out;
	const target_list_t *tgt_list_ptr = (target_list_t *)&(algo_out.tL);
	uint32_t range                    = CH_NO_TARGET;
	uint32_t time_of_flight           = 0;
	int err;

	if (!dev_ptr->sensor_connected) {
		return CH_NO_TARGET;
	}

	/* Get current target list from sensor */
	err = read_target_list(dev_ptr, &algo_out);
	if (tgt_list_ptr->num_valid_targets == 0) {
		/* No target detected */
		err = 1;
	}

	CH_LOG_DEBUG("meas_num=%d num_iq_bytes=%d", dev_ptr->last_measurement, dev_ptr->num_iq_bytes);

	if (!err) {
		/* Report specified target from list */
		time_of_flight = (uint32_t)tgt_list_ptr->targets[target_num].range;

		CH_LOG_DEBUG("target list:  num_valid_targets=%d  odr_out=%d  range[0]=%d  amp[0]=%d",
		             tgt_list_ptr->num_valid_targets, dev_ptr->odr_out, tgt_list_ptr->targets[0].range,
		             tgt_list_ptr->targets[0].amplitude);

		CH_LOG_TRACE_START("orig time_of_flight = %ld  ", time_of_flight);

		int32_t tof_offset_lsb;
		if (get_tof_offset_lsb(dev_ptr, &tof_offset_lsb) != RET_OK) {
			// error means bad ODR. better to make it fail obviously here than silently continue without
			// the compensation
			return CH_NO_TARGET;
		}

		time_of_flight -= tof_offset_lsb;

		CH_LOG_TRACE_MSG("adjusted time_of_flight = %lu", time_of_flight);
		CH_LOG_TRACE_END();

		range = ch_common_range_lsb_to_mm(dev_ptr, time_of_flight, range_type);
	}
	return range;
}

uint32_t icu_gpt_algo_get_target_tof_us(ch_dev_t *dev_ptr, uint8_t target_num) {
	int32_t tof_offset_lsb;
	uint8_t err = 0;
	InvnAlgoRangeFinderOutput algo_out;

	if (!dev_ptr->sensor_connected) {
		return 0;
	}

	/* Get current target list from sensor */  // TODO optimize reads vs. get_amplitude etc.
	err = read_target_list(dev_ptr, &algo_out);
	if (err) {
		return 0;
	}

	/* Report specified target from list */
	target_list_t *tgt_list_ptr = (target_list_t *)&(algo_out.tL);
	uint32_t tof_cycles         = (uint32_t)tgt_list_ptr->targets[target_num].range;
	if (get_tof_offset_lsb(dev_ptr, &tof_offset_lsb) != RET_OK) {
		// error means bad ODR. better to make it fail obviously here than silently continue without
		// the compensation
		return 0;
	}
	tof_cycles -= tof_offset_lsb;

	return ch_cycles_to_usec(dev_ptr, tof_cycles);
}

void icu_gpt_algo_update_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t new_odr) {
	InvnAlgoRangeFinderMeasConfig *meas_cfg_ptr =
			&((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num];

	const measurement_t *meas_ptr = (const measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	ch_odr_t old_odr              = (ch_odr_t)meas_ptr->odr;  // save previous ODR setting

	/* Adjust ringdown and static filter sample counts */
	if (new_odr < old_odr) {                                            // if lower ODR
		meas_cfg_ptr->ringdown_cancel_samples >>= (old_odr - new_odr);  //   fewer samples for same time/distance
		meas_cfg_ptr->static_target_samples   >>= (old_odr - new_odr);
	} else if (new_odr > old_odr) {                                     // if higher ODR
		meas_cfg_ptr->ringdown_cancel_samples <<= (new_odr - old_odr);  //   more samples
		meas_cfg_ptr->static_target_samples   <<= (new_odr - old_odr);
	}

	/* Adjust detection threshold sample counts */
	for (uint8_t thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {
		thresholds_t *thresh_ptr = (thresholds_t *)&(meas_cfg_ptr->thresholds);
		if (new_odr < old_odr) {                                         // if lower ODR
			thresh_ptr->stop_index[thresh_num] >>= (old_odr - new_odr);  //   fewer samples for same time/distance
		} else if (new_odr > old_odr) {                                  // if higher ODR
			thresh_ptr->stop_index[thresh_num] <<= (new_odr - old_odr);  //   more samples
		}
	}
}

uint8_t icu_gpt_algo_set_data_output(ch_dev_t *dev_ptr, const ch_output_t *output_ptr) {
	uint8_t ret_val = RET_OK;

	/* Change each measurement */
	for (uint8_t meas_num = 0; meas_num < CH_MEAS_MAX_MEAS; meas_num++) {
		ch_odr_t new_odr = CH_ODR_DEFAULT;

		/* Set data output type */
		ret_val = ch_meas_set_iq_output(dev_ptr, meas_num, output_ptr->output_type);
		if (ret_val != RET_OK) {
			/* exit loop */
			meas_num = CH_MEAS_MAX_MEAS;
			break;
		}

		/* Convert "decimation" to modified output data rate (ODR) */
		switch (output_ptr->decimation_factor) {
		case CH_DECIMATION_4:
			new_odr = CH_ODR_DEFAULT - 2;
			break;
		case CH_DECIMATION_2:
			new_odr = CH_ODR_DEFAULT - 1;
			break;
		case CH_DECIMATION_NONE:
			new_odr = CH_ODR_DEFAULT;
			break;
		case CH_DECIMATION_0_50:
			new_odr = CH_ODR_DEFAULT + 1;
			break;
		case CH_DECIMATION_0_25:
			new_odr = CH_ODR_DEFAULT + 2;
			break;
		default:
			/* note: CH_DECIMATION_3 is not supported */
			ret_val  = RET_ERR;
			meas_num = CH_MEAS_MAX_MEAS;
			break;
		}
		/* Set ODR */
		if (ret_val == RET_OK) {
			icu_gpt_algo_update_odr(dev_ptr, meas_num, new_odr);
			// TODO Update measure queue ??
			ret_val = ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
		}
	}

	return ret_val;
}

uint8_t icu_gpt_algo_is_target_in_ringdown(ch_dev_t *dev_ptr) {
	InvnAlgoRangeFinderOutput algo_out;

	if (!dev_ptr->sensor_connected)
		return 0;

	/* Get current target list from sensor */
	uint8_t err = read_target_list(dev_ptr, &algo_out);

	return !err && (algo_out.tL.reserved & 0x01);
}

#if IS_CH_LOG_USED
uint8_t icu_gpt_display_algo_thresholds(ch_dev_t *dev_ptr) {
	uint8_t ch_err = RET_OK;

	/* Get threshold values in structure */
	ch_thresholds_t detect_thresholds;

	ch_log_printf("Detection thresholds:\r\n");

	for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
		ch_log_printf("  Measurement %u\r\n", meas_num);
		ch_err = icu_gpt_get_thresholds(dev_ptr, meas_num, &detect_thresholds);
		if (ch_err) {
			/*error reading thresholds or thresholds not handled by fw */
			ch_log_printf("     KO\r\n");
			goto exit_print_cr;
		}

		for (int thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {
			uint16_t start_sample = detect_thresholds.threshold[thresh_num].start_sample;
			uint16_t start_mm     = ch_common_meas_samples_to_mm(dev_ptr, meas_num, start_sample);

			if ((thresh_num == 0) || (start_sample != 0)) { /* unused thresholds have start = 0 */
				ch_log_printf("     %u\tstart sample: %3u  = %4u mm\tlevel: %u", thresh_num, start_sample, start_mm,
				              detect_thresholds.threshold[thresh_num].level);
				if (detect_thresholds.threshold[thresh_num].level == CH_THRESH_LEVEL_HOLDOFF) {
					ch_log_printf(" (Rx Holdoff)");
				}
				ch_log_printf("\r\n");
			}
		}
	}

exit_print_cr:
	ch_log_printf("\r\n");

	return ch_err;
}
#endif

uint8_t icu_gpt_set_num_ranges(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t num_ranges) {
	((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].num_ranges = num_ranges;

	return ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
}

uint8_t icu_gpt_get_num_ranges(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].num_ranges;
}

uint8_t icu_gpt_set_thresholds(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_thresholds_t *lib_thresh_buf_ptr) {
	uint8_t ret_val = RET_ERR;
	InvnAlgoRangeFinderConfig *sens_algo_cfg_addr =
			(InvnAlgoRangeFinderConfig *)(uintptr_t)dev_ptr->algo_info.algo_cfg_ptr;
	InvnAlgoRangeFinderConfig *algo_cfg_ptr = (InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr);

	if (dev_ptr->sensor_connected && (lib_thresh_buf_ptr != NULL)) {
		/* Convert and write new threshold values to local copy of algo measurement config */
		/* Drop the volatile qualifier by casting because not running on MSP430 */
		thresholds_t *sens_thresh_ptr = (thresholds_t *)&(algo_cfg_ptr->meas_cfg[meas_num].thresholds);

		thresh_lib_to_sensor(dev_ptr, lib_thresh_buf_ptr, sens_thresh_ptr);

		/* Write to sensor */
		uint16_t thresholds_addr = (uint16_t)(uintptr_t) & ((sens_algo_cfg_addr)->meas_cfg[meas_num].thresholds);

		ret_val = chdrv_burst_write(dev_ptr, thresholds_addr, (uint8_t *)sens_thresh_ptr, sizeof(thresholds_t));
	}

	return ret_val;
}

uint8_t icu_gpt_get_thresholds(ch_dev_t *dev_ptr, uint8_t meas_num, ch_thresholds_t *lib_thresh_buf_ptr) {
	if (!dev_ptr->sensor_connected || (dev_ptr->current_fw->max_num_thresholds != ICU_GPT_NUM_THRESHOLDS) ||
	    (lib_thresh_buf_ptr == NULL)) {
		return RET_ERR;
	}

	InvnAlgoRangeFinderConfig *sens_algo_cfg_addr =
			(InvnAlgoRangeFinderConfig *)(uintptr_t)dev_ptr->algo_info.algo_cfg_ptr;
	thresholds_t sens_thresh;

	uint16_t thresh_start_addr = (uint16_t)(uintptr_t) & (sens_algo_cfg_addr->meas_cfg[meas_num].thresholds);
	uint8_t ret_val =
			(uint8_t)chdrv_burst_read(dev_ptr, thresh_start_addr, (uint8_t *)&sens_thresh, sizeof(thresholds_t));
	if (ret_val == RET_OK) {
		/* Copy fields to user buffer */
		ret_val = thresh_sensor_to_lib(dev_ptr, &sens_thresh, lib_thresh_buf_ptr);  // convert format and copy
	}

	return ret_val;
}

uint8_t icu_gpt_set_rx_holdoff(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {
	ch_thresholds_t thresholds = {0};
	uint8_t thresh_num;
	uint8_t ret_val = RET_OK;

	if (dev_ptr->current_fw->max_num_thresholds != ICU_GPT_NUM_THRESHOLDS)
		return RET_ERR;

	/* Get current threshold settings */
	ret_val = icu_gpt_get_thresholds(dev_ptr, meas_num, &thresholds);
	if (ret_val != RET_OK)
		return ret_val;

	if (num_samples < thresholds.threshold[1].start_sample) {  // if rx holdoff is shorter than first threshold
		/* Need to insert a new threshold[0] for holdoff */
		thresh_num = (dev_ptr->current_fw->max_num_thresholds - 2);  // start at next-to-last entry
		for (uint8_t i = 0; i < (dev_ptr->current_fw->max_num_thresholds - 1); i++) {
			// shuffle contents up one entry
			thresholds.threshold[thresh_num + 1].start_sample = thresholds.threshold[thresh_num].start_sample;
			thresholds.threshold[thresh_num + 1].level        = thresholds.threshold[thresh_num].level;
			thresh_num--;
		}

		thresholds.threshold[0].level        = CH_THRESH_LEVEL_HOLDOFF;  // first thresh get holdoff (max) value
		thresholds.threshold[1].start_sample = num_samples;              // second thresh starts after holdoff samples

	} else {
		/* Increase/extend first threshold(s) to prevent detection */
		uint16_t holdoff_samples_left = num_samples;

		thresh_num = 0;

		while ((holdoff_samples_left > 0) && (thresh_num < (dev_ptr->current_fw->max_num_thresholds - 1))) {
			uint16_t thresh_samples;

			if (thresholds.threshold[thresh_num + 1].start_sample <= num_samples) {
				/* this entire threshold is part of holdoff area */
				thresholds.threshold[thresh_num].level = CH_THRESH_LEVEL_HOLDOFF;

				thresh_samples = (thresholds.threshold[thresh_num + 1].start_sample -
				                  thresholds.threshold[thresh_num].start_sample);

				holdoff_samples_left -= thresh_samples;
			} else {
				/* end of holdoff is in this threshold - change start to extend previous holdoff thresh */
				thresholds.threshold[thresh_num].start_sample = num_samples;

				break;  // done now
			}

			thresh_num++;
		}

	}  // end if (num_samples < thresholds.threshold[1].start_sample)

	/* Write updated threshold values */
	ret_val = icu_gpt_set_thresholds(dev_ptr, meas_num, &thresholds);

	return ret_val;
}

uint16_t icu_gpt_get_rx_holdoff(ch_dev_t *dev_ptr, uint8_t meas_num) {
	ch_thresholds_t thresholds;
	uint8_t err;
	uint16_t rx_holdoff = 0;

	if (dev_ptr->current_fw->max_num_thresholds < 2)
		return RET_ERR;

	err = icu_gpt_get_thresholds(dev_ptr, meas_num, &thresholds);
	if ((err == RET_OK) && (thresholds.threshold[0].level == CH_THRESH_LEVEL_HOLDOFF)) {
		/* first threshold ends at start of the second thresh */
		rx_holdoff = thresholds.threshold[1].start_sample;
	}

	return rx_holdoff;
}

uint8_t icu_gpt_set_ringdown_cancel(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {
	((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].ringdown_cancel_samples = num_samples;

	return ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
}

uint16_t icu_gpt_get_ringdown_cancel(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].ringdown_cancel_samples;
}

uint8_t icu_gpt_set_static_filter(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {
	((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].static_target_samples = num_samples;

	return ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
}

uint16_t icu_gpt_get_static_filter(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].static_target_samples;
}

uint8_t icu_gpt_set_filter_update(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t update_interval) {
	((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].filter_update_modulo = update_interval;

	return ch_common_set_algo_config(dev_ptr, dev_ptr->algo_cfg_ptr);
}

uint8_t icu_gpt_get_filter_update(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ((InvnAlgoRangeFinderConfig *)(dev_ptr->algo_cfg_ptr))->meas_cfg[meas_num].filter_update_modulo;
}
