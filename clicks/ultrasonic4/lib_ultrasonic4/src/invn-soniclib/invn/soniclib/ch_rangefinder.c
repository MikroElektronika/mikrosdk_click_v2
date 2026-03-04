/*! \file ch_rangefinder.c
 *
 * \brief Chirp SonicLib API range finding function implementations
 */

/*
 Copyright 2016-2024, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */
#define CH_LOG_MODULE_NAME "CH_RANGEFINDER"
#include <invn/soniclib/ch_log.h>

#include <invn/soniclib/details/ch_common.h>
#if defined(INCLUDE_SHASTA_SUPPORT)
#include <invn/soniclib/sensor_fw/icu_gpt/icu_gpt.h>
#endif
#include <invn/soniclib/ch_rangefinder_types.h>
#include <invn/soniclib/ch_rangefinder.h>

#if defined(INCLUDE_WHITNEY_SUPPORT)
const uint8_t THRESH_LEN_REGS[CHX01_COMMON_NUM_THRESHOLDS] = {
		CHX01_GPRMT_REG_THRESH_LEN_0,
		CHX01_GPRMT_REG_THRESH_LEN_1,
		CHX01_GPRMT_REG_THRESH_LEN_2,
		CHX01_GPRMT_REG_THRESH_LEN_3,
		CHX01_GPRMT_REG_THRESH_LEN_4,
		0  // last threshold does not have length field - assumed to extend to end of data
};
#endif

uint8_t ch_rangefinder_set_static_range(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val = RET_ERR;  // default is error return

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (dev_ptr->sensor_connected) {
			ret_val = chdrv_write_byte(dev_ptr, CH101_COMMON_REG_STAT_RANGE, num_samples);

			if (!ret_val) {
				ret_val = chdrv_write_byte(dev_ptr, CH101_COMMON_REG_STAT_COEFF, CH101_COMMON_STAT_COEFF_DEFAULT);
			}

			if (!ret_val) {
				dev_ptr->static_range = num_samples;
			}
		}
#else
		(void)num_samples;
#endif
	} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		ret_val = icu_gpt_set_static_filter(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);
#else
		(void)num_samples;
#endif  // INCLUDE_SHASTA_SUPPORT
	}

	return ret_val;
}

uint32_t ch_rangefinder_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type) {

#ifdef INCLUDE_SHASTA_SUPPORT
	return icu_gpt_algo_get_target_range(dev_ptr, target_num, range_type);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	(void)target_num; /* parameter not used with whitney */

	uint32_t range          = CH_NO_TARGET;
	uint32_t time_of_flight = 0;
	int err;
	uint8_t tof_reg;

	if (!dev_ptr->sensor_connected) {
		return CH_NO_TARGET;
	}

	if (dev_ptr->current_fw->max_num_thresholds == CHX01_COMMON_NUM_THRESHOLDS) {
		tof_reg = CHX01_GPRMT_REG_TOF;
	} else {
		tof_reg = CH101_COMMON_REG_TOF;
	}

	uint16_t time_of_flight_16bit;
	err            = chdrv_read_word(dev_ptr, tof_reg, &time_of_flight_16bit);
	time_of_flight = (uint32_t)time_of_flight_16bit;

	if (!err && (time_of_flight != UINT16_MAX)) {  // If object detected

		if (dev_ptr->tof_scale_factor == 0) {
			dev_ptr->current_fw->calib_funcs->store_scalefactor(dev_ptr);
		}
		range = ch_common_range_lsb_to_mm(dev_ptr, time_of_flight, range_type);
	}
	return range;
#endif
}

uint32_t ch_rangefinder_get_range(ch_dev_t *dev_ptr, ch_range_t range_type) {
	return ch_rangefinder_get_target_range(dev_ptr, CH_DEFAULT_TARGET_NUM, range_type);
}

uint16_t ch_rangefinder_get_amplitude(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	return icu_gpt_algo_get_target_amplitude(dev_ptr, CH_DEFAULT_TARGET_NUM);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint16_t amplitude = 0;
	uint16_t amplitude_reg;

	if (!dev_ptr->sensor_connected || (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA)) {
		return 0;
	}

	if (dev_ptr->current_fw->max_num_thresholds == CHX01_COMMON_NUM_THRESHOLDS) {
		amplitude_reg = CHX01_GPRMT_REG_AMPLITUDE;
	} else {
		amplitude_reg = CH101_COMMON_REG_AMPLITUDE;
	}
	chdrv_read_word(dev_ptr, amplitude_reg, &amplitude);

	return amplitude;
#endif
}

uint8_t ch_rangefinder_set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *lib_thresh_buf_ptr) {
	if (!dev_ptr->sensor_connected) {
		return RET_ERR;
	}

#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->asic_gen != CH_ASIC_GEN_2_SHASTA) {
		return RET_ERR;
	}

	return icu_gpt_set_thresholds(dev_ptr, CH_DEFAULT_MEAS_NUM, lib_thresh_buf_ptr);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint16_t start_sample = 0;
	uint8_t ret_val       = RET_OK;

	if ((dev_ptr->asic_gen != CH_ASIC_GEN_1_WHITNEY) ||
	    (dev_ptr->current_fw->max_num_thresholds != CHX01_COMMON_NUM_THRESHOLDS)) {
		/* Not supported */
		return RET_ERR;
	}

	for (uint8_t thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {
		uint8_t thresh_len_reg = 0;  // offset of register for this threshold's length
		uint8_t thresh_len;
		uint16_t thresh_level;

		if (thresh_num < (dev_ptr->current_fw->max_num_thresholds - 1)) {
			uint16_t next_start_sample = lib_thresh_buf_ptr->threshold[thresh_num + 1].start_sample;

			thresh_len   = (next_start_sample - start_sample);
			start_sample = next_start_sample;
		} else {
			thresh_len = 0;
		}

		thresh_len_reg = THRESH_LEN_REGS[thresh_num];
		if (thresh_len_reg != 0) {
			ret_val = chdrv_write_byte(dev_ptr, thresh_len_reg,
			                           thresh_len);  // set length (if any) for this threshold
		}

		// write level to this threshold's entry in register array
		thresh_level = lib_thresh_buf_ptr->threshold[thresh_num].level;
		ret_val |=
				chdrv_write_word(dev_ptr, (CHX01_GPRMT_REG_THRESHOLDS + (thresh_num * sizeof(uint16_t))), thresh_level);

	}  // end 	for (thresh_num < max_num_thresholds)

	return ret_val;
#endif  // INCLUDE_SHASTA_SUPPORT
}

uint8_t ch_rangefinder_get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *lib_thresh_buf_ptr) {
	if (!dev_ptr->sensor_connected || (lib_thresh_buf_ptr == NULL)) {
		return RET_ERR;
	}

#ifdef INCLUDE_SHASTA_SUPPORT
	return icu_gpt_get_thresholds(dev_ptr, CH_DEFAULT_MEAS_NUM, lib_thresh_buf_ptr);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t thresh_len_reg = 0;  // offset of register for this threshold's length
	uint8_t thresh_len     = 0;  // number of samples described by each threshold
	uint16_t start_sample  = 0;  // calculated start sample for each threshold

	if (dev_ptr->current_fw->max_num_thresholds != CHX01_COMMON_NUM_THRESHOLDS) {
		return RET_ERR;
	}

	for (uint8_t thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {

		thresh_len_reg = THRESH_LEN_REGS[thresh_num];
		if (thresh_len_reg != 0) {
			// read the length field register for this threshold
			chdrv_read_byte(dev_ptr, thresh_len_reg, &thresh_len);
		} else {
			thresh_len = 0;
		}

		lib_thresh_buf_ptr->threshold[thresh_num].start_sample = start_sample;
		start_sample += thresh_len;  // increment start sample for next threshold

		// get level from this threshold's entry in register array
		chdrv_read_word(dev_ptr, (CHX01_GPRMT_REG_THRESHOLDS + (thresh_num * sizeof(uint16_t))),
		                &(lib_thresh_buf_ptr->threshold[thresh_num].level));
	}
	return RET_OK;
#endif  // INCLUDE_SHASTA_SUPPORT
}

uint8_t ch_rangefinder_set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t num_samples) {
#ifdef INCLUDE_SHASTA_SUPPORT
	return icu_gpt_set_rx_holdoff(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint16_t reg_value;
	uint8_t rx_holdoff_reg;

	if (!dev_ptr->sensor_connected) {
		return RET_ERR;
	}

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		rx_holdoff_reg = CH101_COMMON_REG_RX_HOLDOFF;
		reg_value      = num_samples;
	} else {
		rx_holdoff_reg = CH201_COMMON_REG_RX_HOLDOFF;
		reg_value      = (num_samples / 2);  // CH201 value is 1/2 actual sample count
	}

	return chdrv_write_byte(dev_ptr, rx_holdoff_reg, (uint8_t)reg_value);
#endif  // INCLUDE_SHASTA_SUPPORT
}

uint16_t ch_rangefinder_get_rx_holdoff(ch_dev_t *dev_ptr) {

#if defined(INCLUDE_SHASTA_SUPPORT)
	return icu_gpt_get_rx_holdoff(dev_ptr, CH_DEFAULT_MEAS_NUM);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint16_t rx_holdoff = 0;
	uint8_t rx_holdoff_reg;
	uint8_t reg_val = 0;

	if (!dev_ptr->sensor_connected) {
		return 0;
	}

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		rx_holdoff_reg = CH101_COMMON_REG_RX_HOLDOFF;
	} else {
		rx_holdoff_reg = CH201_COMMON_REG_RX_HOLDOFF;
	}
	chdrv_read_byte(dev_ptr, rx_holdoff_reg, &reg_val);
	rx_holdoff = (uint16_t)reg_val;

	if (dev_ptr->part_number == CH201_PART_NUMBER) {
		rx_holdoff *= 2; /* CH201 reports 1/2 actual sample count */
	}
	return rx_holdoff;
#endif /* INCLUDE_SHASTA_SUPPORT */
}

uint8_t ch_rangefinder_get_algo_config(const ch_dev_t *dev_ptr, ch_rangefinder_algo_config_t *config_ptr) {
	config_ptr->static_range = dev_ptr->static_range;
	config_ptr->thresh_ptr   = NULL;  // thresholds not returned here - use ch_get_thresholds()

	return RET_OK;
}

uint8_t ch_rangefinder_set_algo_config(ch_dev_t *dev_ptr, const ch_rangefinder_algo_config_t *config_ptr) {
	if (dev_ptr->current_fw->api_funcs->algo_specific_api == NULL) {
		return RET_ERR;
	}

	uint8_t ret_val                              = RET_OK;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;

	if (algo_funcs->set_thresholds != NULL) {
		// set multiple thresholds
		ret_val = ch_set_thresholds(dev_ptr, config_ptr->thresh_ptr);
	}

	// if STR supported
	if (!ret_val && algo_funcs->set_static_range != NULL) {
		// set static target rejection range
		ret_val = ch_set_static_range(dev_ptr, config_ptr->static_range);
		if (!ret_val) {
			dev_ptr->static_range = config_ptr->static_range;
		}
	}

	return ret_val;
}

uint16_t ch_get_static_range(const ch_dev_t *dev_ptr) {

	return dev_ptr->static_range;
}

uint8_t ch_set_static_range(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val                              = RET_OK;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_set_static_range_func_t func_ptr          = algo_funcs->set_static_range;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, num_samples);
	}

	return ret_val;
}

uint8_t ch_set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val                              = RET_ERR;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_set_rx_holdoff_func_t func_ptr            = algo_funcs->set_rx_holdoff;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, num_samples);
	}

	return ret_val;
}

uint16_t ch_get_rx_holdoff(ch_dev_t *dev_ptr) {
	uint16_t num_samples                         = 0;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_get_rx_holdoff_func_t func_ptr            = algo_funcs->get_rx_holdoff;

	if (func_ptr != NULL) {
		num_samples = (*func_ptr)(dev_ptr);
	}

	return num_samples;
}

uint32_t ch_get_tof_us(ch_dev_t *dev_ptr) {
	uint32_t tof_us                              = 0;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_get_tof_us_func_t func_ptr                = algo_funcs->get_tof_us;

	if (func_ptr != NULL) {
		tof_us = (*func_ptr)(dev_ptr);
	}

	return tof_us;
}

uint8_t ch_get_num_targets(ch_dev_t *dev_ptr) {

#ifdef INCLUDE_SHASTA_SUPPORT
	return icu_gpt_algo_get_num_targets(dev_ptr);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint32_t range = ch_rangefinder_get_range(dev_ptr, CH_RANGE_ECHO_ONE_WAY);
	// CHx01 only detects single target
	return (range == CH_NO_TARGET) ? 0 : 1;
#endif  // INCLUDE_SHASTA_SUPPORT
}

uint32_t ch_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type) {
	return ch_rangefinder_get_target_range(dev_ptr, target_num, range_type);
}

uint16_t ch_get_target_amplitude(ch_dev_t *dev_ptr, uint8_t target_num) {
#if defined(INCLUDE_SHASTA_SUPPORT)
	return icu_gpt_algo_get_target_amplitude(dev_ptr, target_num);
#else
	(void)dev_ptr;
	(void)target_num;
	return 0;
#endif
}

uint32_t ch_get_target_tof_us(ch_dev_t *dev_ptr, uint8_t target_num) {
#if defined(INCLUDE_SHASTA_SUPPORT)
	return icu_gpt_algo_get_target_tof_us(dev_ptr, target_num);
#else
	// TODO add whitney
	(void)dev_ptr;
	(void)target_num;
	return 0;
#endif
}

uint8_t ch_is_target_in_ringdown(ch_dev_t *dev_ptr) {
#if defined(INCLUDE_SHASTA_SUPPORT)
	return icu_gpt_algo_is_target_in_ringdown(dev_ptr);
#else
	(void)dev_ptr;
	return 0;
#endif
}

uint8_t ch_set_threshold(ch_dev_t *dev_ptr, uint8_t threshold_index, uint16_t amplitude) {
	uint8_t ret_val                              = RET_ERR;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_set_threshold_func_t func_ptr             = algo_funcs->set_threshold;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, threshold_index, amplitude);
	}

	return ret_val;
}

uint16_t ch_get_threshold(ch_dev_t *dev_ptr, uint8_t threshold_index) {
	uint16_t amplitude                           = 0;
	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_get_threshold_func_t func_ptr             = algo_funcs->get_threshold;

	if (func_ptr != NULL) {
		amplitude = (*func_ptr)(dev_ptr, threshold_index);
	}

	return amplitude;
}

uint8_t ch_set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr) {
	uint8_t ret_val = RET_ERR;

	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_set_thresholds_func_t func_ptr            = algo_funcs->set_thresholds;

	if ((func_ptr != NULL) && (thresh_ptr != NULL)) {
		ret_val = (*func_ptr)(dev_ptr, thresh_ptr);
	}

	return ret_val;
}

uint8_t ch_get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr) {
	uint8_t ret_val = RET_ERR;

	const ch_rangefinder_api_funcs_t *algo_funcs = dev_ptr->current_fw->api_funcs->algo_specific_api;
	ch_get_thresholds_func_t func_ptr            = algo_funcs->get_thresholds;

	if ((func_ptr != NULL) && (thresh_ptr != NULL)) {
		ret_val = (*func_ptr)(dev_ptr, thresh_ptr);
	}

	return ret_val;
}

uint8_t ch_get_num_thresholds(const ch_dev_t *dev_ptr) {
	uint8_t num_thresholds = 0;

	num_thresholds = dev_ptr->current_fw->max_num_thresholds;

	return num_thresholds;
}

uint8_t ch_rangefinder_display_config_info(ch_dev_t *dev_ptr) {
	uint8_t ch_err = RET_OK;

#ifdef INCLUDE_WHITNEY_SUPPORT
	ch_rangefinder_algo_config_t algo_config;
	ch_err = ch_rangefinder_get_algo_config(dev_ptr, &algo_config);
	/* Display static target rejection range, if used */
	if (algo_config.static_range != 0) {
		ch_log_printf("static_range=%u samples\r\n", algo_config.static_range);
	}
#endif

	if (dev_ptr->current_fw->max_num_thresholds == 0) {
		goto exit_print_cr;
	}

#ifdef INCLUDE_WHITNEY_SUPPORT
	/* Get threshold values in structure */
	ch_thresholds_t detect_thresholds;

	ch_err = ch_get_thresholds(dev_ptr, &detect_thresholds);
	if (ch_err) {
		/*error reading thresholds or thresholds not handled by fw */
		goto exit_print_cr;
	}

	ch_log_printf("Detection thresholds:\r\n");
	for (int thresh_num = 0; thresh_num < dev_ptr->current_fw->max_num_thresholds; thresh_num++) {
		uint16_t start_sample = detect_thresholds.threshold[thresh_num].start_sample;
		uint16_t start_mm     = ch_common_samples_to_mm(dev_ptr, start_sample);

		if ((thresh_num == 0) || (start_sample != 0)) { /* unused thresholds have start = 0 */
			ch_log_printf("     %u\tstart sample: %3u  = %4u mm\tlevel: %u", thresh_num, start_sample, start_mm,
			              detect_thresholds.threshold[thresh_num].level);
			ch_log_printf("\r\n");
		}
	}
#elif defined(INCLUDE_SHASTA_SUPPORT)
	icu_gpt_display_algo_thresholds(dev_ptr);
#endif

exit_print_cr:
	ch_log_printf("\r\n");

	return ch_err;
}
