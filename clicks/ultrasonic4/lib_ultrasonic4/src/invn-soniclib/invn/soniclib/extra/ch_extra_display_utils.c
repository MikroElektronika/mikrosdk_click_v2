/*! \file ch_extra_display_utils.c
 *
 * \brief Extra functions for debug purpose to print info about Chirp ultrasonic sensors.
 *
 * This file contains functions to print informations about sensors.
 *
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
#include <stdbool.h>
#include <invn/soniclib/ch_extra_display_utils.h>
#include <invn/soniclib/ch_log.h>

#if !IS_CH_LOG_USED
#error "Can't use functions of ch_extra_display_utils.c if log module not used"
#else

#define ODR_TO_FREQ_DIV(odr) (1 << (7 - odr))

#define SEG_TYPE_TO_STR(segment_type)                                                                                  \
	(segment_type == CH_MEAS_SEG_TYPE_COUNT)                                                                           \
			? "Count"                                                                                                  \
			: ((segment_type == CH_MEAS_SEG_TYPE_RX)                                                                   \
	                   ? "RX   "                                                                                       \
	                   : ((segment_type == CH_MEAS_SEG_TYPE_TX)                                                        \
	                              ? "TX   "                                                                            \
	                              : ((segment_type == CH_MEAS_SEG_TYPE_EOF) ? "EOF  " : "UNKNOWN")))

#define MODE_TO_STR(mode)                                                                                              \
	(mode == CH_MODE_FREERUN)                                                                                          \
			? "CH_MODE_FREERUN"                                                                                        \
			: ((mode == CH_MODE_TRIGGERED_TX_RX) ? "CH_MODE_TRIGGERED_TX_RX"                                           \
	                                             : ((mode == CH_MODE_TRIGGERED_RX_ONLY)                                \
	                                                        ? "CH_MODE_TRIGGERED_RX_ONLY"                              \
	                                                        : ((mode == CH_MODE_IDLE) ? "CH_MODE_IDLE" : "UNKNOWN")))

static bool is_part_number_icu(ch_dev_t *dev_ptr) {
	return ((ch_get_part_number(dev_ptr) == ICU10201_PART_NUMBER) ||
	        (ch_get_part_number(dev_ptr) == ICU20201_PART_NUMBER) ||
	        (ch_get_part_number(dev_ptr) == ICU30201_PART_NUMBER));
}

void ch_extra_display_init_info(ch_group_t *grp_ptr) {
	uint8_t num_ports             = ch_get_num_ports(grp_ptr);
	bool one_icu_sensor_connected = false;
	ch_dev_t *dev_ptr;

	ch_log_printf("Sensor  Type       Freq      RTC Cal     B/W    CPU Freq   Firmware\r\n");
	for (uint8_t dev_num = 0; dev_num < num_ports; dev_num++) {
		dev_ptr = ch_get_dev_ptr(grp_ptr, dev_num);
		bool is_icu_sensor;
		if (ch_sensor_is_connected(dev_ptr)) {

			is_icu_sensor             = is_part_number_icu(dev_ptr);
			one_icu_sensor_connected |= is_icu_sensor;

			ch_log_printf("  %u     %s%u  %lu Hz  %u@%ums  %uHz  %0.2fMHz  %s\r\n", dev_num,
			              (is_icu_sensor) ? "ICU-" : "    CH", ch_get_part_number(dev_ptr), ch_get_frequency(dev_ptr),
			              ch_get_rtc_cal_result(dev_ptr), ch_get_rtc_cal_pulselength(dev_ptr),
			              ch_get_bandwidth(dev_ptr), (ch_get_cpu_frequency(dev_ptr) / 1000000.0f),
			              ch_get_fw_version_string(dev_ptr));
		}
	}
	ch_log_printf("\n");

#ifdef INCLUDE_SHASTA_SUPPORT
	const char *sensor_id_str;
	ch_mfg_info_t manufacturing_info;

	if (!one_icu_sensor_connected)
		return;

	ch_log_printf("Sensor\tId\tYear\tWeek\tSite\tProduct\tPackage\tMEMS\tModule\r\n");
	for (uint8_t dev_num = 0; dev_num < num_ports; dev_num++) {
		dev_ptr = ch_get_dev_ptr(grp_ptr, dev_num);

		if (ch_sensor_is_connected(dev_ptr) && is_part_number_icu(dev_ptr)) {
			sensor_id_str = ch_get_sensor_id(dev_ptr);
			ch_get_mfg_info(dev_ptr, &manufacturing_info);
			ch_log_printf("%u\t%s\t%04u\tW%02u\t%u\t%03u\t%u\t%u\t%u\r\n", dev_num, sensor_id_str,
			              manufacturing_info.mfg_year, manufacturing_info.mfg_week, manufacturing_info.mfg_site,
			              manufacturing_info.product_code, manufacturing_info.package_code,
			              manufacturing_info.mems_code, manufacturing_info.module_code);
		}
	}
#endif  // INCLUDE_SHASTA_SUPPORT
}

uint8_t ch_extra_display_config_info(ch_dev_t *dev_ptr) {
	uint8_t ch_err  = 0;
	uint8_t dev_num = ch_get_dev_num(dev_ptr);

	if (!is_part_number_icu(dev_ptr)) {
		ch_config_t sensor_config;

		/* Read configuration values for the device into ch_config_t structure */
		ch_err = ch_get_config(dev_ptr, &sensor_config);
		if (!ch_err) {
			/* Display sensor number, mode and max range */
			ch_log_printf("Sensor %u:\tmax_range=%umm (%u samples)\tmode=%s  ", dev_num, sensor_config.max_range,
			              ch_get_num_samples(dev_ptr), MODE_TO_STR(sensor_config.mode));
		}
	} else {
#ifdef INCLUDE_SHASTA_SUPPORT
		/* Display measurement configuration */
		ch_meas_info_t meas_info;
		ch_meas_seg_info_t seg_info;

		for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
			ch_meas_get_info(dev_ptr, meas_num, &meas_info);

			if (meas_info.num_segments == 0)
				continue;

			ch_log_printf("Device %u: Measurement %u Configuration\r\n", dev_num, meas_num);

			ch_log_printf("  Total Samples = %u  (%u mm max range)\r\n", meas_info.num_rx_samples,
			              ch_meas_samples_to_mm(dev_ptr, meas_num, meas_info.num_rx_samples));

			uint8_t odr_freq_div = ODR_TO_FREQ_DIV(meas_info.odr);
			ch_log_printf("  Active Segments = %u\tRate = CH_ODR_FREQ_DIV_%u\r\n", meas_info.num_segments,
			              odr_freq_div);

			for (int seg_num = 0; seg_num <= meas_info.num_segments; seg_num++) { /* also display EOF */
				ch_meas_get_seg_info(dev_ptr, meas_num, seg_num, &seg_info);
				ch_log_printf("   Seg %u  %s ", seg_num, SEG_TYPE_TO_STR(seg_info.type));
				if (seg_info.type == CH_MEAS_SEG_TYPE_RX) {
					ch_log_printf("%3d sample%s  ", seg_info.num_rx_samples,
					              (seg_info.num_rx_samples == 1 ? " " : "s"));
				} else {
					ch_log_printf("             ");
				}
				ch_log_printf("%5d cycles  ", seg_info.num_cycles);
				if (seg_info.type == CH_MEAS_SEG_TYPE_TX) {
					ch_log_printf("Pulse width = %2u  Phase = %u  ", seg_info.tx_pulse_width, seg_info.tx_phase);
				} else if (seg_info.type == CH_MEAS_SEG_TYPE_RX) {
					ch_log_printf("Gain reduce = %2u  Atten = %u  ", seg_info.rx_gain, seg_info.rx_atten);
				}
				if (seg_info.rdy_int_en) {
					ch_log_printf("Rdy Int  ");
				}
				if (seg_info.done_int_en) {
					ch_log_printf("Done Int");
				}
				ch_log_printf("\r\n");
			} /* for (seg_num...) */
		}     /* for(meas_num...) */
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	ch_log_printf("\r\n");

	return ch_err;
}

#endif /* !IS_CH_LOG_USED */