/*! \file ch_api.c
 \brief Chirp SonicLib public API functions for using the Chirp ultrasonic sensor.

 The user should not need to edit this file. This file relies on hardware interface
 functions declared in ch_bsp.h and supplied in the board support package (BSP) for
 the specific hardware platform being used.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */
#include <stdbool.h>

#include <invn/soniclib/soniclib.h>
#include <invn/soniclib/details/ch_common.h>
#include <invn/soniclib/details/ch_driver.h>
#include <invn/soniclib/chirp_bsp.h>
#include <invn/soniclib/ch_log.h>
#include <invn/soniclib/details/ch_math_utils.h>

uint8_t ch_group_init(ch_group_t *grp_ptr, uint8_t num_devices, uint8_t num_buses, uint16_t rtc_cal_pulse_ms) {
	if (grp_ptr == NULL || num_devices == 0 || num_buses == 0) {
		return RET_ERR;
	}

	/* Init all fields of group to avoid potential "variables not initialized" issues */
	memset(grp_ptr, 0x00, sizeof(ch_group_t));

	grp_ptr->num_ports        = num_devices;
	grp_ptr->num_buses        = num_buses;
	grp_ptr->rtc_cal_pulse_ms = rtc_cal_pulse_ms;

	return RET_OK;
}

/*!
 * \brief Initialize a Chirp ultrasonic sensor descriptor structure
 *
 * \param dev_ptr 		a pointer to the ch_dev_t config structure for a sensor
 *
 * \return 0 (RET_OK) if successful, non-zero otherwise
 *
 */

uint8_t ch_init(ch_dev_t *dev_ptr, ch_group_t *grp_ptr, uint8_t dev_num, ch_fw_init_func_t fw_init_func) {
	uint8_t ret_val;

	if (dev_ptr == NULL || grp_ptr == NULL || (dev_num >= CHIRP_MAX_NUM_SENSORS) || fw_init_func == NULL) {
		return RET_ERR;
	}

	/* Init all fields of device to avoid potential "variables not initialized" issues */
	memset(dev_ptr, 0x00, sizeof(ch_dev_t));

	ret_val = ch_common_init(dev_ptr, grp_ptr, dev_num, fw_init_func);

	if (ret_val == RET_OK) {
		/* Set mode to idle */
		dev_ptr->mode = CH_MODE_IDLE;

#ifdef INCLUDE_SHASTA_SUPPORT
		/* Initialize sensor measurement queue */
		ret_val |= ch_common_meas_init_queue(dev_ptr);
#endif
	}

	return ret_val;
}

uint8_t ch_set_init_firmware(ch_dev_t *dev_ptr, ch_fw_init_func_t fw_init_func) {
	uint8_t ret_val = RET_ERR;

#ifdef INCLUDE_SHASTA_SUPPORT
	if (fw_init_func != NULL) {
		ret_val = ch_common_set_init_firmware(dev_ptr, fw_init_func);
	}
#else
	(void)dev_ptr;
	(void)fw_init_func;
#endif

	return ret_val;
}

uint8_t ch_get_config(ch_dev_t *dev_ptr, ch_config_t *config_ptr) {
	uint8_t ret_val = RET_OK;

	config_ptr->mode            = dev_ptr->mode;
	config_ptr->max_range       = dev_ptr->max_range;
	config_ptr->sample_interval = dev_ptr->freerun_intvl_us / 1000;

	return ret_val;
}

uint8_t ch_set_config(ch_dev_t *dev_ptr, ch_config_t *config_ptr) {
	uint8_t ret_val;

	ret_val = ch_set_max_range(dev_ptr, config_ptr->max_range);  // set max range

	if (!ret_val) {
		if (config_ptr->sample_interval != 0) {
			ret_val = ch_set_freerun_interval(dev_ptr,
			                                  config_ptr->sample_interval);  // set meas interval (free-run mode only)
			if (!ret_val) {
				dev_ptr->freerun_intvl_us = config_ptr->sample_interval * 1000;  // store  interval in usec
			}
		}
	}

	if (!ret_val) {
		if (dev_ptr->current_fw->api_funcs->set_target_interrupt != NULL) {  // if target interrupt mode supported
			ret_val = ch_set_target_interrupt(dev_ptr,
			                                  config_ptr->tgt_int_filter);  // enable/disable target detect interrupt
		}
	}

	if (!ret_val) {
		ret_val = ch_set_mode(dev_ptr, config_ptr->mode);  // set operating mode last
	}

	if (!ret_val) {
		dev_ptr->mode = config_ptr->mode;
	}

	return ret_val;
}

uint8_t ch_group_start(ch_group_t *grp_ptr) {

	return ch_common_group_start(grp_ptr);
}

uint8_t ch_restart(ch_dev_t *dev_ptr) {
	uint8_t ret_val = RET_ERR;

#ifdef INCLUDE_SHASTA_SUPPORT
	ret_val = chdrv_restart(dev_ptr);  // restart & program sensor

	if (!ret_val) {
		ret_val  = ch_meas_write_config(dev_ptr);                       // write meas config to sensor
		ret_val |= chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);  // apply trigger pin selection
	}
#else
	(void)dev_ptr;  // not supported for CH101/CH201, return error
#endif
	return ret_val;
}

uint8_t ch_group_restart(ch_group_t *grp_ptr) {
	uint8_t ret_val = RET_OK;

	for (int dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
		ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

		if (dev_ptr->sensor_connected) {
			ret_val |= ch_restart(dev_ptr);
		}
	}
	return ret_val;
}

void ch_trigger(ch_dev_t *dev_ptr) {

	if (dev_ptr->trig_type == CH_TRIGGER_TYPE_HW) {  // hardware trigger
		chdrv_hw_trigger(dev_ptr);
	} else {  // software trigger
		ch_trigger_soft(dev_ptr);
	}
}

void ch_trigger_soft(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
		chdrv_event_trigger(dev_ptr, EVENT_SW_TRIG);
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
		ch_trigger_soft_func_t func_ptr = dev_ptr->current_fw->api_funcs->trigger_soft;
		if (func_ptr != NULL) {  // CH101 and CH201 support depends on f/w type
			(*func_ptr)(dev_ptr);
		}
	}
#endif
}

void ch_set_trigger_type(ch_dev_t *dev_ptr, ch_trigger_type_t trig_type) {

	if ((dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) || (dev_ptr->current_fw->api_funcs->trigger_soft != NULL)) {
		dev_ptr->trig_type = trig_type;
	}
}

ch_trigger_type_t ch_get_trigger_type(ch_dev_t *dev_ptr) {
	return dev_ptr->trig_type;
}

void ch_group_trigger(ch_group_t *grp_ptr) {
	chdrv_group_hw_trigger(grp_ptr);  // group trigger is h/w only for now
}

void ch_reset(ch_dev_t *dev_ptr, ch_reset_t reset_type) {

#ifdef INCLUDE_SHASTA_SUPPORT
	(void)reset_type;
	chdrv_soft_reset(dev_ptr);  // Shasta doesn't have hard reset
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	if (reset_type == CH_RESET_HARD) {
		chdrv_group_hard_reset(dev_ptr->group);  // Whitney can only do group hard reset
	} else if (reset_type == CH_RESET_SOFT) {
		chdrv_soft_reset(dev_ptr);
	}
#endif
}

void ch_group_reset(ch_group_t *grp_ptr, ch_reset_t reset_type) {
	if (reset_type == CH_RESET_HARD) {
		chdrv_group_hard_reset(grp_ptr);
	} else {
		chdrv_group_soft_reset(grp_ptr);
	}
}

uint8_t ch_sensor_is_connected(ch_dev_t *dev_ptr) {

	return dev_ptr->sensor_connected;
}

uint16_t ch_get_part_number(ch_dev_t *dev_ptr) {

	return dev_ptr->part_number;
}

uint8_t ch_get_dev_num(ch_dev_t *dev_ptr) {

	return dev_ptr->io_index;
}

ch_dev_t *ch_get_dev_ptr(ch_group_t *grp_ptr, uint8_t dev_num) {

	if (dev_num >= grp_ptr->num_ports) {
		return NULL;
	}
	return grp_ptr->device[dev_num];
}

uint8_t ch_get_i2c_address(ch_dev_t *dev_ptr) {
	uint8_t i2c_address = 0;
#ifdef INCLUDE_WHITNEY_SUPPORT
	i2c_address = dev_ptr->i2c_address;
#else
	(void)dev_ptr;
#endif  // INCLUDE_WHITNEY_SUPPORT
	return i2c_address;
}

uint8_t ch_get_bus(ch_dev_t *dev_ptr) {

	return dev_ptr->bus_index;
}

uint8_t ch_get_num_ports(ch_group_t *grp_ptr) {

	return grp_ptr->num_ports;
}

void ch_get_version(ch_version_t *version_ptr) {
	if (version_ptr != NULL) {
		version_ptr->major = SONICLIB_VER_MAJOR;
		version_ptr->minor = SONICLIB_VER_MINOR;
		version_ptr->rev   = SONICLIB_VER_REV;
	}
}

const char *ch_get_fw_version_string(ch_dev_t *dev_ptr) {

	return dev_ptr->current_fw->fw_version_string;
}

uint8_t ch_log_init(ch_group_t *grp_ptr, ch_log_fmt_t format, ch_log_cfg_t *config_ptr) {
	static uint8_t log_id = 0;
	uint16_t num_samples_no_decim;
	uint8_t start_sample_no_decim;

	if (format == CH_LOG_FMT_REDSWALLOW) {
		ch_log_printf("# TDK InvenSense Embedded Redswallow Log\r\n");
		ch_log_printf("# sample rate: %0.2f S/s\r\n", 1000.0f / config_ptr->interval_ms);
		ch_log_printf("# Decimation factor: %u\r\n", config_ptr->decimation_factor);
		ch_log_printf("# Content: %s\r\n", config_ptr->output_type == CH_OUTPUT_IQ ? "iq" : "amp");

		for (uint8_t dev_num = 0; dev_num < ch_get_num_ports(grp_ptr); dev_num++) {
			ch_dev_t *dev_ptr = ch_get_dev_ptr(grp_ptr, dev_num);

			if (ch_sensor_is_connected(dev_ptr)) {
				if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
					num_samples_no_decim  = dev_ptr->num_rx_samples;
					start_sample_no_decim = config_ptr->start_sample;
				} else {
					/* on shasta samples returned are already decimated */
					num_samples_no_decim  = dev_ptr->num_rx_samples * config_ptr->decimation_factor;
					start_sample_no_decim = config_ptr->start_sample * config_ptr->decimation_factor;
				}
				ch_log_printf("# Sensors ID: %u\r\n", dev_num);
				ch_log_printf("# Sensors FOP: %lu Hz\r\n", dev_ptr->op_frequency);
				ch_log_printf("# Sensors NB Samples: %u\r\n", num_samples_no_decim);
				ch_log_printf("# Sensors NB First samples skipped: %u\r\n", start_sample_no_decim);
				ch_log_printf(
						"# header, log ID, time [s], tx_id, rx_id, range [cm], intensity [a.u.], target_detected, "
						"insertionAnnotation");

				for (int count  = start_sample_no_decim; count < num_samples_no_decim;
				     count     += config_ptr->decimation_factor) {
					float sample_cm = (float)dev_ptr->max_range * (count + 1) / (num_samples_no_decim * 10.0);
					ch_log_printf(", idata_%0.1f", sample_cm);
				}
				for (int count  = start_sample_no_decim; count < num_samples_no_decim;
				     count     += config_ptr->decimation_factor) {
					float sample_cm = (float)dev_ptr->max_range * (count + 1) / (num_samples_no_decim * 10.0);
					ch_log_printf(", qdata_%0.1f", sample_cm);
				}
				ch_log_printf("\r\n");
			}
		}
	}
	return ++log_id;
}

void ch_log_append(uint8_t log_id, ch_log_fmt_t format, uint64_t timestamp_usec, ch_log_data_t *log_data_ptr) {
	if (format == CH_LOG_FMT_REDSWALLOW) {
		int16_t q_data[MAX_NUM_SAMPLES];

		/* Avoid usage of __aeabi_ul2f which isn't available in all lib C implementations
		 * Source : https://github.com/adafruit/circuitpython/issues/342 and
		 * https://github.com/adafruit/circuitpython/pull/343/files
		 */
		float timestamp_sec  = ((float)(uint32_t)(timestamp_usec >> 32) * 4294967296.0f +
                               (float)(uint32_t)(timestamp_usec & 0xffffffff));
		timestamp_sec       /= 1000000.0f;
		ch_log_printf("chlog, %u, %0.6f, %u, %u, %0.1f, %u, %u, %u", log_id, timestamp_sec, log_data_ptr->tx_sensor_id,
		              log_data_ptr->rx_sensor_id, (float)log_data_ptr->range / (32.0f * 10.0f), log_data_ptr->amplitude,
		              log_data_ptr->range != CH_NO_TARGET, log_data_ptr->annotation);

		/* Print first all I data then all Q data
		 * If printing magnitude, print mag data in place of I data and 0 in place of Q data
		 * so sqrt(I^2+Q^2) is always possible whatever the input format used */
		for (int count = 0; count < log_data_ptr->num_samples; count++) {
			if (log_data_ptr->output_type == CH_OUTPUT_IQ) {
				/* print I data now */
				ch_log_printf(", %d", log_data_ptr->raw_data.iq_sample_ptr->i);
				/* save Q data to be print after */
				q_data[count] = log_data_ptr->raw_data.iq_sample_ptr->q;
				log_data_ptr->raw_data.iq_sample_ptr++;
			} else {
				ch_log_printf(", %u", *(log_data_ptr->raw_data.mag_data_ptr));
				q_data[count] = 0;
				log_data_ptr->raw_data.mag_data_ptr++;
			}
		}
		/* Q data */
		for (int count = 0; count < log_data_ptr->num_samples; count++) {
			ch_log_printf(", %d", q_data[count]);
		}
		ch_log_printf("\r\n");
	}
}

ch_mode_t ch_get_mode(ch_dev_t *dev_ptr) {

	return dev_ptr->mode;
}

uint8_t ch_set_mode(ch_dev_t *dev_ptr, ch_mode_t mode) {
	int ret_val = ch_common_set_mode(dev_ptr, mode);
	if (ret_val == RET_OK) {
		dev_ptr->mode = mode;
	}

	return ret_val;
}

uint16_t ch_get_sample_interval(ch_dev_t *dev_ptr) {
	/* Deprecated - use new equivalent function */
	return ch_get_freerun_interval(dev_ptr);
}

uint16_t ch_get_freerun_interval(ch_dev_t *dev_ptr) {
	uint16_t interval_ms = 0;

	if (dev_ptr->mode == CH_MODE_FREERUN) {
		interval_ms = (dev_ptr->freerun_intvl_us / 1000);
	}
	return interval_ms;
}

uint32_t ch_get_freerun_interval_us(ch_dev_t *dev_ptr) {
	uint32_t interval_us = 0;

	if (dev_ptr->mode == CH_MODE_FREERUN) {
		interval_us = dev_ptr->freerun_intvl_us;
	}
	return interval_us;
}

uint16_t ch_get_freerun_interval_ticks(ch_dev_t *dev_ptr) {
	uint16_t rtc_ticks = 0;

	if (dev_ptr->mode == CH_MODE_FREERUN) {
		rtc_ticks = ch_usec_to_ticks(dev_ptr, dev_ptr->freerun_intvl_us);
	}
	return rtc_ticks;
}

uint8_t ch_set_freerun_interval(ch_dev_t *dev_ptr, uint16_t sense_interval_ms) {

	return ch_common_set_freerun_interval(dev_ptr, sense_interval_ms);
}

uint8_t ch_set_freerun_interval_us(ch_dev_t *dev_ptr, uint32_t sense_interval_us) {

	return ch_common_set_freerun_interval_us(dev_ptr, sense_interval_us);
}

uint8_t ch_set_freerun_interval_ticks(ch_dev_t *dev_ptr, uint32_t sense_interval_ticks) {

	return ch_common_set_freerun_interval_ticks(dev_ptr, sense_interval_ticks);
}

uint8_t ch_set_sample_interval(ch_dev_t *dev_ptr, uint16_t sample_interval) {
	/* Deprecated - use new equivalent routine */
	return ch_set_freerun_interval(dev_ptr, sample_interval);
}

uint8_t ch_freerun_time_hop_enable(ch_dev_t *dev_ptr) {
	return ch_common_set_freerun_time_hop(dev_ptr, CH_DEFAULT_MEAS_NUM, true);
}

uint8_t ch_freerun_time_hop_disable(ch_dev_t *dev_ptr) {
	return ch_common_set_freerun_time_hop(dev_ptr, CH_DEFAULT_MEAS_NUM, false);
}

uint16_t ch_get_num_samples(ch_dev_t *dev_ptr) {

	return ch_common_get_num_samples(dev_ptr);
}

uint8_t ch_set_num_samples(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val                    = RET_ERR;
	ch_set_num_samples_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_num_samples;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, num_samples);
	}

	if (!ret_val) {
		dev_ptr->max_range = ch_samples_to_mm(dev_ptr, num_samples);  // store corresponding range in mm
	}
	return ret_val;
}

uint16_t ch_get_max_range(ch_dev_t *dev_ptr) {

	return dev_ptr->max_range;
}

uint8_t ch_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range) {
	return ch_common_set_max_range(dev_ptr, max_range);
}

uint16_t ch_get_max_samples(ch_dev_t *dev_ptr) {

	return dev_ptr->current_fw->max_samples;
}

uint8_t ch_get_sample_window(ch_dev_t *dev_ptr, uint16_t *start_sample_ptr, uint16_t *num_samples_ptr) {
	uint8_t ret_val = RET_ERR;

	if ((start_sample_ptr != NULL) && (num_samples_ptr != NULL)) {

		*start_sample_ptr = dev_ptr->win_start_sample;
		*num_samples_ptr  = dev_ptr->num_win_samples;
		ret_val           = RET_OK;
	}
	return ret_val;
}

uint8_t ch_set_sample_window(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t num_samples) {
	uint8_t ret_val                      = RET_ERR;
	ch_set_sample_window_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_sample_window;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, start_sample, num_samples);
	}

	return ret_val;
}

uint32_t ch_get_range(ch_dev_t *dev_ptr, ch_range_t range_type) {
	uint32_t range               = 0;
	ch_get_range_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_range;

	if (func_ptr != NULL) {
		range = (*func_ptr)(dev_ptr, range_type);
	}

	return range;
}

uint16_t ch_get_amplitude(ch_dev_t *dev_ptr) {
	int amplitude                    = 0;
	ch_get_amplitude_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_amplitude;

	if (func_ptr != NULL) {
		amplitude = (*func_ptr)(dev_ptr);
	}

	return amplitude;
}

uint16_t ch_get_amplitude_avg(ch_dev_t *dev_ptr) {
	uint16_t amplitude_avg               = 0;
	ch_get_amplitude_avg_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_amplitude_avg;

	if (func_ptr != NULL) {
		amplitude_avg = (*func_ptr)(dev_ptr);
	}

	return amplitude_avg;
}

uint8_t ch_get_amplitude_data(ch_dev_t *dev_ptr, uint16_t *amp_buf_ptr, uint16_t start_sample, uint16_t num_samples,
                              ch_io_mode_t mode) {
	uint16_t error                        = RET_ERR;
	ch_get_amplitude_data_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_amplitude_data;

	if (func_ptr != NULL) {
		error = (*func_ptr)(dev_ptr, amp_buf_ptr, start_sample, num_samples, mode);
	}

	return error;
}

uint8_t ch_get_amp_thresh_data(ch_dev_t *dev_ptr, ch_amp_thresh_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                               ch_io_mode_t mode) {

	return ch_common_get_amp_thresh_data(dev_ptr, buf_ptr, start_sample, num_samples, mode);
}

uint16_t ch_get_bandwidth(ch_dev_t *dev_ptr) {

	return dev_ptr->bandwidth;
}

uint8_t ch_set_frequency(ch_dev_t *dev_ptr, uint32_t request_op_freq_hz) {
	int ret_val                      = RET_ERR;
	ch_set_frequency_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_frequency;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, request_op_freq_hz);
#ifdef INCLUDE_SHASTA_SUPPORT
	} else {
		if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
			ret_val = ch_common_set_frequency(dev_ptr, request_op_freq_hz);
		}
#endif
	}

	return ret_val;
}

uint32_t ch_get_frequency(ch_dev_t *dev_ptr) {

	return dev_ptr->op_frequency;
}

uint8_t ch_group_set_frequency(ch_group_t *grp_ptr, uint32_t request_op_freq_hz) {

	return ch_common_group_set_frequency(grp_ptr, request_op_freq_hz);
}

uint32_t ch_group_get_frequency(ch_group_t *grp_ptr) {

	return grp_ptr->op_frequency;
}

uint16_t ch_get_rtc_cal_pulselength(ch_dev_t *dev_ptr) {

	return dev_ptr->group->rtc_cal_pulse_ms;
}

uint16_t ch_get_rtc_cal_result(ch_dev_t *dev_ptr) {

	return dev_ptr->rtc_cal_result;
}

uint16_t ch_get_scale_factor(ch_dev_t *dev_ptr) {

	return dev_ptr->amp_scale_factor;
}

uint8_t ch_get_iq_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                       ch_io_mode_t mode) {
	int ret_val                    = RET_ERR;
	ch_get_iq_data_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_iq_data;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, buf_ptr, start_sample, num_samples, mode);
	}

	return ret_val;
}

uint16_t ch_samples_to_mm(ch_dev_t *dev_ptr, uint16_t num_samples) {
	return ch_common_samples_to_mm(dev_ptr, num_samples);
}

uint16_t ch_mm_to_samples(ch_dev_t *dev_ptr, uint16_t num_mm) {
	int num_samples                  = 0;
	ch_mm_to_samples_func_t func_ptr = dev_ptr->current_fw->api_funcs->mm_to_samples;

	if (func_ptr != NULL) {
		num_samples = (*func_ptr)(dev_ptr, num_mm);
	}

	return num_samples;
}

uint16_t ch_iq_to_amplitude(ch_iq_sample_t *iq_sample) {
	uint32_t amplitude;
	uint32_t i_sq = ((int32_t)iq_sample->i * (int32_t)iq_sample->i);
	uint32_t q_sq = ((int32_t)iq_sample->q * (int32_t)iq_sample->q);

	amplitude = sqrt_int32(i_sq + q_sq);

	return (uint16_t)amplitude;
}

/*!
 * \brief Start a non-blocking sensor readout
 *
 * \param grp_ptr 		pointer to the ch_group_t descriptor structure for a group of sensors
 *
 * This function starts a non-blocking I/O operation on the specified group of sensors.
 */
uint8_t ch_io_start_nb(ch_group_t *grp_ptr) {
	uint8_t ret_val = 1;

	// only start I/O if there is a callback function
	if (grp_ptr->io_complete_callback != NULL) {
		chdrv_group_start_nb(grp_ptr);
		ret_val = 0;
	}

	return ret_val;
}

uint8_t ch_minimal_int_handler(ch_group_t *grp_ptr, uint8_t dev_num) {

	return chdrv_int_notify(grp_ptr, dev_num);
}

/*!
 * \brief Notify SonicLib that a sensor interrupt occurred.
 *
 * This function is used from the board support package (BSP) handler routine
 * for the sensor interrupt to notify SonicLib that the interrupt has
 * occurred.  The SonicLib driver layer will handle further processing of
 * the interrupt, including a call to the application-supplied callback
 * function.
 */
void ch_interrupt(ch_group_t *grp_ptr, uint8_t dev_num) {

	chdrv_int_callback(grp_ptr, dev_num);
}

/*!
 * \brief Set callback function for Chirp sensor I/O interrupt
 *
 * \note
 */
void ch_io_int_callback_set(ch_group_t *grp_ptr, ch_io_int_callback_t callback_func_ptr) {

	grp_ptr->io_int_callback = callback_func_ptr;
}

/*!
 * \brief Set callback function for Chirp sensor I/O operation complete
 *
 * \note
 */
void ch_io_complete_callback_set(ch_group_t *grp_ptr, ch_io_complete_callback_t callback_func_ptr) {

	grp_ptr->io_complete_callback = callback_func_ptr;
}

/*!
 * \brief Continue a non-blocking readout
 *
 * \param grp_ptr 			pointer to the ch_group_t config structure for a group of sensors
 * \param i2c_bus_index		index value identifying I2C/SPI bus within group
 *
 * Call this function once from your I2C interrupt handler each time it completes an I/O operation.
 * It will call the function previously specified during \a ch_io_complete_callback_set() when all group
 * transactions are complete.
 */
void ch_io_notify(ch_group_t *grp_ptr, uint8_t i2c_bus_index) {

	chdrv_group_irq_handler(grp_ptr, i2c_bus_index);
}

uint8_t ch_set_target_interrupt(ch_dev_t *dev_ptr, ch_tgt_int_filter_t tgt_int_filter) {
	int ret_val                             = RET_ERR;
	ch_set_target_interrupt_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_target_interrupt;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, tgt_int_filter);
	}

	return ret_val;
}

ch_tgt_int_filter_t ch_get_target_interrupt(ch_dev_t *dev_ptr) {
	ch_tgt_int_filter_t tgt_int_mode        = CH_TGT_INT_FILTER_OFF;
	ch_get_target_interrupt_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_target_interrupt;

	if (func_ptr != NULL) {
		tgt_int_mode = (*func_ptr)(dev_ptr);
	}

	return tgt_int_mode;
}

uint8_t ch_set_target_int_counter(ch_dev_t *dev_ptr, uint8_t meas_hist, uint8_t thresh_count, uint8_t reset) {
	uint8_t ret_val                           = RET_ERR;
	ch_set_target_int_counter_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_target_int_counter;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, meas_hist, thresh_count, reset);
	}

	return ret_val;
}

uint8_t ch_get_target_int_counter(ch_dev_t *dev_ptr, uint8_t *meas_hist_ptr, uint8_t *thresh_count_ptr,
                                  uint8_t *reset_ptr) {
	uint8_t ret_val                           = RET_ERR;
	ch_get_target_int_counter_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_target_int_counter;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, meas_hist_ptr, thresh_count_ptr, reset_ptr);
	}

	return ret_val;
}

ch_meas_status_t ch_meas_get_status(ch_dev_t *dev_ptr, uint8_t meas_num) {
	ch_meas_status_t status            = CH_MEAS_STATUS_UNKNOWN;
	ch_meas_get_status_func_t func_ptr = dev_ptr->current_fw->api_funcs->meas_get_status;

	if (func_ptr != NULL) {
		status = (*func_ptr)(dev_ptr, meas_num);
	}
	return status;
}

#ifdef INCLUDE_SHASTA_SUPPORT
uint8_t ch_set_interrupt_mode(ch_dev_t *dev_ptr, ch_interrupt_mode_t mode) {

	return ch_common_set_interrupt_mode(dev_ptr, mode);
}

ch_interrupt_mode_t ch_get_interrupt_mode(ch_dev_t *dev_ptr) {

	return ch_common_get_interrupt_mode(dev_ptr);
}

uint8_t ch_set_interrupt_drive(ch_dev_t *dev_ptr, ch_interrupt_drive_t drive) {

	return ch_common_set_interrupt_drive(dev_ptr, drive);
}

ch_interrupt_drive_t ch_get_interrupt_drive(ch_dev_t *dev_ptr) {

	return ch_common_get_interrupt_drive(dev_ptr);
}

uint8_t ch_enable_data_validation(ch_dev_t *dev_ptr, int16_t seed, uint8_t enable) {
	if (enable) {
		dev_ptr->meas_queue.reserved |= READOUT_OPTIONS_DATA_VALIDATION_BM;
	} else {
		dev_ptr->meas_queue.reserved &= ~READOUT_OPTIONS_DATA_VALIDATION_BM;
	}
	dev_ptr->data_validation_counter = seed;
	return ch_common_write_data_validation_cfg(dev_ptr, dev_ptr->meas_queue.reserved, seed);
}

uint16_t ch_data_validation_check(ch_dev_t *dev_ptr, ch_iq_sample_t *data, uint16_t num_samples) {
	uint16_t err_cnt = 0;

	for (uint16_t i = 0; i < num_samples; i++) {
		if ((i == 0) && (dev_ptr->meas_queue.reserved & READOUT_OPTIONS_METADATA_IN_S0_BM)) {
			dev_ptr->data_validation_counter += 2;
			continue;
		}

		if (data[i].q != dev_ptr->data_validation_counter++) {
			err_cnt++;
		}
		if (data[i].i != dev_ptr->data_validation_counter++) {
			err_cnt++;
		}
	}
	return err_cnt;
}

uint8_t ch_enable_double_buffer(ch_dev_t *dev_ptr, uint8_t enable) {
	int ret_val = RET_OK;

	if (enable) {
		dev_ptr->meas_queue.reserved |= READOUT_OPTIONS_DOUBLE_BUFFER_BM;
	} else {
		dev_ptr->meas_queue.reserved &= ~READOUT_OPTIONS_DOUBLE_BUFFER_BM;
	}

	ret_val = ch_common_meas_write_config(dev_ptr);

	return ret_val;
}

uint8_t ch_enable_metadata_in_iq0(ch_dev_t *dev_ptr, uint8_t enable) {
	int ret_val = RET_OK;

	if (enable) {
		dev_ptr->meas_queue.reserved |= READOUT_OPTIONS_METADATA_IN_S0_BM;
	} else {
		dev_ptr->meas_queue.reserved &= ~READOUT_OPTIONS_METADATA_IN_S0_BM;
	}

	ret_val = ch_common_meas_write_config(dev_ptr);

	return ret_val;
}

uint8_t ch_update_metadata_from_iq0(ch_dev_t *dev_ptr, ch_iq_sample_t *iq_data) {
	uint16_t *buf_ptr             = (uint16_t *)iq_data;
	const uint16_t next_buf_addr  = *buf_ptr;
	buf_ptr                      += 1;                  // move to next word
	const uint8_t is_valid        = (*buf_ptr) >> 8;    // get MSByte
	const uint8_t last_meas_num   = (*buf_ptr) & 0xFF;  // get LSByte
	if (is_valid) {
		dev_ptr->last_measurement = last_meas_num;
		dev_ptr->buf_addr         = next_buf_addr;
	}
	// set the first IQ sample to 0 after extracting metadata since many downstream
	// tools expect the first IQ sample to be 0 (ASIC always writes 0 as first sample).
	iq_data[0].i = 0;
	iq_data[0].q = 0;
	return (is_valid) ? 0 : 1;
}

#endif

uint8_t ch_set_rx_low_gain(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val = RET_ERR;

	ch_set_rx_low_gain_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_rx_low_gain;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, num_samples);
	}

	return ret_val;
}

uint16_t ch_get_rx_low_gain(ch_dev_t *dev_ptr) {
	uint16_t num_samples = 0;

	ch_get_rx_low_gain_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_rx_low_gain;

	if (func_ptr != NULL) {
		num_samples = (*func_ptr)(dev_ptr);
	}

	return num_samples;
}

uint8_t ch_set_tx_length(ch_dev_t *dev_ptr, uint16_t tx_length) {
	int ret_val                      = RET_ERR;
	ch_set_tx_length_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_tx_length;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, tx_length);
	}

	return ret_val;
}

uint16_t ch_get_tx_length(ch_dev_t *dev_ptr) {
	uint16_t tx_length               = 0;
	ch_get_tx_length_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_tx_length;

	if (func_ptr != NULL) {
		tx_length = (*func_ptr)(dev_ptr);
	}

	return tx_length;
}

void ch_set_rx_pretrigger(ch_group_t *grp_ptr, uint8_t enable) {

	if (enable) {
		chdrv_pretrigger_delay_set(grp_ptr, CHDRV_PRETRIGGER_DELAY_US);
	} else {
		chdrv_pretrigger_delay_set(grp_ptr, 0);
	}
}

uint8_t ch_get_rx_pretrigger(ch_group_t *grp_ptr) {
	uint8_t enabled = (grp_ptr->pretrig_delay_us != 0);

	return enabled;
}

uint8_t ch_check_program(ch_dev_t *dev_ptr) {

	return ch_common_check_program(dev_ptr);
}

uint8_t ch_set_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr) {
	int ret_val                       = RET_ERR;
	ch_set_cal_result_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_cal_result;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, cal_ptr);
	}

	return ret_val;
}

uint8_t ch_get_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr) {
	int ret_val                       = RET_ERR;
	ch_get_cal_result_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_cal_result;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, cal_ptr);
	}

	return ret_val;
}

uint8_t ch_set_data_output(ch_dev_t *dev_ptr, ch_output_t *output_ptr) {
	int ret_val                        = RET_ERR;
	ch_set_data_output_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_data_output;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, output_ptr);
	}

	return ret_val;
}

uint8_t ch_set_data_ready_delay(ch_dev_t *dev_ptr, uint8_t delay_ms) {
	int ret_val                             = RET_ERR;
	ch_set_data_ready_delay_func_t func_ptr = dev_ptr->current_fw->api_funcs->set_data_ready_delay;

	if (func_ptr != NULL) {
		ret_val = (*func_ptr)(dev_ptr, delay_ms);
	}

	return ret_val;
}

uint8_t ch_get_data_ready_delay(ch_dev_t *dev_ptr) {
	uint8_t delay_ms                        = 0;
	ch_get_data_ready_delay_func_t func_ptr = dev_ptr->current_fw->api_funcs->get_data_ready_delay;

	if (func_ptr != NULL) {
		delay_ms = (*func_ptr)(dev_ptr);
	}

	return delay_ms;
}

#ifdef INCLUDE_SHASTA_SUPPORT
uint8_t ch_meas_init_queue(ch_dev_t *dev_ptr) {

	return ch_common_meas_init_queue(dev_ptr);
}

uint8_t ch_meas_reset(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_reset(dev_ptr, meas_num);
}

uint8_t ch_meas_init(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_config_t *meas_config_ptr,
                     const void *thresh_ptr) {

	/* GPT algo code has been took out of Soniclib base code
	 * To don't break existing API, keep existing GPT parameter
	 * but return an error if used
	 */
	if (thresh_ptr != NULL)
		return RET_ERR;

	return ch_common_meas_init(dev_ptr, meas_num, meas_config_ptr);
}

const char *ch_get_sensor_id(ch_dev_t *dev_ptr) {

	return &(dev_ptr->id_string[0]);
}

uint8_t ch_get_mfg_info(ch_dev_t *dev_ptr, ch_mfg_info_t *info_ptr) {

	return ch_common_get_mfg_info(dev_ptr, info_ptr);
}

uint8_t ch_meas_import(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr) {

	return ch_common_meas_import(dev_ptr, meas_queue_ptr, algo_cfg_ptr);
}

uint8_t ch_meas_add_segment(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_segment_t *seg_ptr) {

	return ch_common_meas_add_segment(dev_ptr, meas_num, seg_ptr);
}

uint8_t ch_meas_insert_segment(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *inst_ptr,
                               uint8_t index_to_insert) {
	return ch_common_meas_insert_instruction(dev_ptr, meas_num, inst_ptr, index_to_insert);
}

uint8_t ch_meas_insert_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *inst_ptr,
                                   uint8_t index_to_insert) {
	return ch_common_meas_insert_instruction(dev_ptr, meas_num, inst_ptr, index_to_insert);
}

uint8_t ch_meas_remove_segment(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t index_to_remove) {
	return ch_common_meas_remove_instruction(dev_ptr, meas_num, index_to_remove);
}

uint8_t ch_meas_remove_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t index_to_remove) {
	return ch_common_meas_remove_instruction(dev_ptr, meas_num, index_to_remove);
}

uint8_t ch_meas_add_segment_count(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t int_enable) {

	return ch_common_meas_add_segment_count(dev_ptr, meas_num, num_cycles, int_enable);
}

uint8_t ch_meas_add_segment_rx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t length, uint8_t gain, uint8_t atten,
                               uint8_t int_enable) {

	return ch_common_meas_add_segment_rx(dev_ptr, meas_num, length, gain, atten, int_enable);
}

uint8_t ch_meas_add_segment_tx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t pulse_width,
                               uint8_t phase, uint8_t int_enable) {

	return ch_common_meas_add_segment_tx(dev_ptr, meas_num, num_cycles, pulse_width, phase, int_enable);
}

void ch_meas_init_segment_count(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t int_enable) {

	ch_common_meas_init_segment_count(seg_ptr, num_cycles, int_enable);
}

void ch_meas_init_segment_rx(ch_meas_segment_t *seg_ptr, uint16_t num_samples, ch_odr_t odr, uint8_t gain,
                             uint8_t atten, uint8_t int_enable) {

	ch_common_meas_init_segment_rx(seg_ptr, num_samples, odr, gain, atten, int_enable);
}

void ch_meas_init_segment_tx(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t pulse_width, uint8_t phase,
                             uint8_t int_enable) {

	ch_common_meas_init_segment_tx(seg_ptr, num_cycles, pulse_width, phase, int_enable);
}

uint8_t ch_meas_optimize(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr) {
	uint8_t ret_val = RET_ERR;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {  // not supported for CH101/CH201
		ret_val = ch_common_meas_optimize(dev_ptr, meas_queue_ptr, algo_cfg_ptr);
	}
	return ret_val;
}

void ch_meas_activate(ch_dev_t *dev_ptr, uint8_t meas_num) {

	ch_common_meas_activate(dev_ptr, meas_num);
}

void ch_meas_standby(ch_dev_t *dev_ptr, uint8_t meas_num) {

	ch_common_meas_standby(dev_ptr, meas_num);
}

uint8_t ch_meas_switch(ch_dev_t *dev_ptr) {

	return ch_common_meas_switch(dev_ptr);
}

uint8_t ch_meas_get_last_num(ch_dev_t *dev_ptr) {

	return ch_common_meas_get_last_num(dev_ptr);
}

uint16_t ch_get_next_buf_addr(ch_dev_t *dev_ptr) {
	return dev_ptr->buf_addr;
}

uint8_t ch_meas_write_config(ch_dev_t *dev_ptr) {

	return ch_common_meas_write_config(dev_ptr);
}

uint8_t ch_meas_get_queue(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr) {
	uint8_t ret_val = RET_ERR;

	if (meas_queue_ptr != NULL) {
		/* Copy internal queue definition */
		memcpy((void *)meas_queue_ptr, (void *)&(dev_ptr->meas_queue), sizeof(measurement_queue_t));
		ret_val = RET_OK;
	}
	return ret_val;
}

void ch_meas_get_info(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_info_t *info_ptr) {

	ch_common_meas_get_info(dev_ptr, meas_num, info_ptr);
}

void ch_meas_get_queue_info(ch_dev_t *dev_ptr, ch_meas_queue_info_t *info_ptr) {

	ch_common_meas_get_queue_info(dev_ptr, info_ptr);
}

void ch_inst_get_seg_info(pmut_transceiver_inst_t *inst_ptr, uint8_t odr, ch_meas_seg_info_t *info_ptr) {

	ch_common_inst_get_seg_info(inst_ptr, odr, info_ptr);
}

void ch_meas_get_seg_info(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t seg_num, ch_meas_seg_info_t *info_ptr) {

	ch_common_meas_get_seg_info(dev_ptr, meas_num, seg_num, info_ptr);
}

uint8_t ch_meas_set_interval(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t interval_ms) {

	return ch_common_meas_set_interval(dev_ptr, meas_num, interval_ms);
}

uint8_t ch_meas_set_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t interval_us) {

	return ch_common_meas_set_interval_us(dev_ptr, meas_num, interval_us);
}

uint8_t ch_meas_set_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t rtc_ticks) {

	return ch_common_meas_set_interval_ticks(dev_ptr, meas_num, rtc_ticks);
}

uint16_t ch_meas_get_interval(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_get_interval(dev_ptr, meas_num);
}

uint32_t ch_meas_get_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_get_interval_us(dev_ptr, meas_num);
}

uint32_t ch_meas_get_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_get_interval_ticks(dev_ptr, meas_num);
}

uint8_t ch_meas_time_hop_enable(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ch_common_set_freerun_time_hop(dev_ptr, meas_num, true);
}

uint8_t ch_meas_time_hop_disable(ch_dev_t *dev_ptr, uint8_t meas_num) {
	return ch_common_set_freerun_time_hop(dev_ptr, meas_num, false);
}

uint8_t ch_meas_set_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t odr) {

	return ch_common_meas_set_odr(dev_ptr, meas_num, odr);
}

ch_odr_t ch_meas_get_odr(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_get_odr(dev_ptr, meas_num);
}

uint8_t ch_meas_set_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {

	return ch_common_meas_set_num_samples(dev_ptr, meas_num, num_samples);
}

uint16_t ch_meas_get_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return ch_common_meas_get_num_samples(dev_ptr, meas_num);
}

uint8_t ch_meas_set_max_range(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t max_range_mm) {

	return ch_common_meas_set_max_range(dev_ptr, meas_num, max_range_mm);
}

uint16_t ch_meas_get_max_range(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return dev_ptr->meas_max_range_mm[meas_num];
}

uint16_t ch_meas_mm_to_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_mm) {

	return ch_common_meas_mm_to_samples(dev_ptr, meas_num, num_mm);
}

uint16_t ch_meas_samples_to_mm(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {

	return ch_common_meas_samples_to_mm(dev_ptr, meas_num, num_samples);
}

ch_output_type_t ch_meas_get_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num) {
	ch_meas_get_iq_output_func_t func_ptr = dev_ptr->current_fw->api_funcs->meas_get_iq_output;

	if (func_ptr != NULL) {
		return (*func_ptr)(dev_ptr, meas_num);
	} else {
		return CH_OUTPUT_IQ;  // standard I/Q by default
	}
}

uint8_t ch_meas_set_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num, ch_output_type_t output_format) {
	ch_meas_set_iq_output_func_t func_ptr = dev_ptr->current_fw->api_funcs->meas_set_iq_output;
	if (func_ptr != NULL) {
		return (*func_ptr)(dev_ptr, meas_num, output_format);
	} else {
		return RET_ERR;
	}
}

uint8_t ch_init_algo(ch_dev_t *dev_ptr) {

	return ch_common_init_algo(dev_ptr);
}

uint8_t ch_get_algo_info(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr) {

	return ch_common_get_algo_info(dev_ptr, algo_info_ptr);
}

uint8_t ch_get_algo_config(ch_dev_t *dev_ptr, void *algo_cfg_ptr) {

	return ch_common_get_algo_config(dev_ptr, algo_cfg_ptr);
}

uint8_t ch_set_algo_config(ch_dev_t *dev_ptr, const void *algo_cfg_ptr) {
	return ch_common_set_algo_config(dev_ptr, algo_cfg_ptr);
}

uint8_t ch_get_algo_output(ch_dev_t *dev_ptr, void *algo_out_ptr) {

	return ch_common_get_algo_output(dev_ptr, algo_out_ptr);
}

uint8_t ch_get_algo_state(ch_dev_t *dev_ptr, void *algo_state_ptr) {

	return ch_common_get_algo_state(dev_ptr, algo_state_ptr);
}

uint32_t ch_measure_pmut_frequency(ch_dev_t *dev_ptr) {
	return ch_common_measure_pmut_frequency(dev_ptr);
}

#endif  // INCLUDE_SHASTA_SUPPORT

uint32_t ch_get_cpu_frequency(ch_dev_t *dev_ptr) {

	return dev_ptr->cpu_frequency;
}

uint8_t ch_set_rtc(ch_dev_t *dev_ptr, ch_rtc_src_t rtc_source, uint16_t rtc_freq) {

	return ch_common_set_rtc(dev_ptr, rtc_source, rtc_freq);
}

uint16_t ch_get_rtc_frequency(ch_dev_t *dev_ptr) {

	return dev_ptr->rtc_frequency;
}

uint8_t ch_set_pmut_clock(ch_dev_t *dev_ptr, ch_pmut_clk_cfg_t clock_cfg) {

	return ch_common_set_pmut_clock(dev_ptr, clock_cfg);
}

ch_pmut_clk_cfg_t ch_get_pmut_clock(ch_dev_t *dev_ptr) {

	return dev_ptr->pmut_clk_cfg;
}

void ch_group_set_pmut_clock_freq(ch_group_t *grp_ptr, uint32_t pmut_clock_freq) {

	grp_ptr->pmut_clock_freq = pmut_clock_freq;
}

uint32_t ch_group_get_pmut_clock_freq(ch_group_t *grp_ptr) {

	return grp_ptr->pmut_clock_freq;
}

uint16_t ch_get_num_output_samples(ch_dev_t *dev_ptr) {

	return ch_common_get_num_output_samples(dev_ptr);
}

uint32_t ch_usec_to_cycles(ch_dev_t *dev_ptr, uint32_t num_usec) {

	return ch_common_usec_to_cycles(dev_ptr, num_usec);
}

uint32_t ch_cycles_to_usec(ch_dev_t *dev_ptr, uint32_t num_cycles) {

	return ch_common_cycles_to_usec(dev_ptr, num_cycles);
}

uint32_t ch_samples_to_cycles(uint16_t num_samples, ch_odr_t odr) {

	return ch_common_samples_to_cycles(num_samples, odr);
}

uint16_t ch_cycles_to_samples(uint32_t num_cycles, ch_odr_t odr) {

	return ch_common_cycles_to_samples(num_cycles, odr, false);
}

uint16_t ch_usec_to_ticks(ch_dev_t *dev_ptr, uint32_t num_usec) {

	return ch_common_usec_to_ticks(dev_ptr, num_usec);
}

uint32_t ch_ticks_to_usec(ch_dev_t *dev_ptr, uint16_t num_ticks) {

	return ch_common_ticks_to_usec(dev_ptr, num_ticks);
}

uint8_t ch_watchdog_enable(ch_dev_t *dev_ptr) {

	return ch_common_watchdog_enable(dev_ptr);
}

uint8_t ch_watchdog_disable(ch_dev_t *dev_ptr) {

	return ch_common_watchdog_disable(dev_ptr);
}

uint8_t ch_check_reset_state(ch_dev_t *dev_ptr, ch_sensor_reset_state_t *reset_state_ptr) {
	uint8_t rst_st;
	uint8_t ret_val = 0;

	ret_val = chdrv_check_reset_state(dev_ptr, &rst_st);

	if (rst_st == 1) {
		*reset_state_ptr = CH_RESET_STATE_ACTIVE;
	} else {
		*reset_state_ptr = CH_RESET_STATE_OK;
	}

	return ret_val;
}
