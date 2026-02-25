/*! \file ch_common.c
 *
 * \brief Chirp SonicLib API function common implementations
 *
 * This file contains standard implementations of functions required to support the
 * SonicLib API.  The sensor firmware, in it's init routine, specifies which of these
 * common implementations should be used by initializing a set of function pointers.
 * These pointers, contained in the ch_api_funcs_t structure within the device descriptor,
 * can either direct the API calls to the functions in this file or to firmware-specific
 * equivalents that are supplied as part of the sensor firmware release.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#define CH_LOG_MODULE_NAME "CH_COMMON"
#include <invn/soniclib/ch_log.h>

#include <invn/soniclib/soniclib.h>
#include <invn/soniclib/chirp_bsp.h>
#include <invn/soniclib/details/ch_common.h>
#include <invn/soniclib/details/ch_helper.h>
#include <invn/soniclib/details/ch_math_utils.h>

#ifdef INCLUDE_SHASTA_SUPPORT
#include <invn/icu_interface/shasta_pmut_cmds.h>
#include <invn/soniclib/details/ch_asic_shasta.h>
#endif

#ifdef INCLUDE_WHITNEY_SUPPORT
#include <invn/soniclib/details/ch_asic_whitney.h>
#endif

/* Local definitions */
#define CH_IQ_SAMPLES_PER_READ 64   // number of I/Q samples to read at a time
#define REF_PRE_RX_CYCLES      800  // reference number of pre-receive cycles, to adjust ToF
#define RTC_CAL_BUS_NBYTES     255  // size of dummy transfer if using I/O bus clock for RTC cal

#ifdef INCLUDE_WHITNEY_SUPPORT
// Check that CH101 and CH201 prog mem are the same (assumed by ch_common_check_program())
#if ((CH101_PROG_MEM_ADDR != CH201_PROG_MEM_ADDR) || (CH101_PROG_MEM_SIZE != CH201_PROG_MEM_SIZE))
#error Mismatch in CH101 and CH201 program address or size
#endif
#endif

static inline bool is_time_hopping_enabled(uint16_t meas_period);
static uint16_t get_rtc_measure_period(uint16_t raw_meas_period);
static uint16_t update_rtc_measure_period(uint16_t prev_meas_period, uint16_t new_meas_period);
static uint8_t set_interval_ticks(ch_dev_t *dev_ptr, uint32_t rtc_ticks, uint8_t meas_num);
static uint8_t get_sample_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                               ch_io_mode_t mode, uint8_t sample_size_in_byte);
#ifdef INCLUDE_WHITNEY_SUPPORT
static inline uint8_t get_tof_sf_reg_addr(const ch_dev_t *dev_ptr);
#endif

/* Functions */

uint8_t ch_common_init(ch_dev_t *dev_ptr, ch_group_t *grp_ptr, uint8_t dev_num, ch_fw_init_func_t fw_init_func) {
	uint8_t ret_val;

	if (!dev_ptr || !grp_ptr || (dev_num >= CHIRP_MAX_NUM_SENSORS) || !fw_init_func) {
		return RET_ERR;
	}

#ifdef INCLUDE_WHITNEY_SUPPORT
	ch_i2c_info_t i2c_info;
	/* Get I2C parameters from BSP */
	ret_val = chbsp_i2c_get_info(grp_ptr, dev_num, &i2c_info);
	if (ret_val == RET_OK) {
		/* Save special handling flags for Chirp driver */
		grp_ptr->i2c_drv_flags = i2c_info.drv_flags;
		/* Call asic f/w init function passed in as parameter */
		ret_val = (*fw_init_func)(dev_ptr, &dev_ptr->main_fw_info);
	}
#else
	dev_ptr->main_fw_init_done   = 0;
	dev_ptr->mq_sanitize_enabled = 1;
	/* Call asic f/w init function passed in as parameter */
	ret_val = (*fw_init_func)(dev_ptr, &dev_ptr->main_fw_info);
#endif

	if (ret_val == RET_OK) {
		/* Init device and group descriptor linkage */
		dev_ptr->io_index        = dev_num;
		dev_ptr->group           = grp_ptr;  // set parent group pointer
		grp_ptr->device[dev_num] = dev_ptr;  // add device to parent group
#ifdef INCLUDE_WHITNEY_SUPPORT
		dev_ptr->app_i2c_address = i2c_info.address;
		dev_ptr->bus_index       = i2c_info.bus_num;
#endif
		if (dev_ptr->main_fw_info->fw_includes_sensor_init) {
			dev_ptr->current_fw = dev_ptr->main_fw_info;
		} else {
			dev_ptr->current_fw = NULL;
		}
#ifdef INCLUDE_SHASTA_SUPPORT
		/* By default there is no dedicated init fw */
		dev_ptr->init_fw_info = NULL;
#endif

		/* Mark this group as pending initialization via ch_group_start() */
		grp_ptr->status = CH_GROUP_STAT_INIT_PENDING;
	}

	return ret_val;
}

#ifdef INCLUDE_SHASTA_SUPPORT
uint8_t ch_common_set_init_firmware(ch_dev_t *dev_ptr, ch_fw_init_func_t fw_init_func) {
	uint8_t ret_val = RET_ERR;

	ret_val = (fw_init_func)(dev_ptr, &dev_ptr->init_fw_info);
	if (ret_val == RET_ERR || !dev_ptr->init_fw_info->fw_includes_sensor_init) {
		/* Issue getting init firmware info or the firmware used for init doesn't handle sensor init */
		ret_val = RET_ERR;
	} else if (!dev_ptr->main_fw_info->fw_includes_sensor_init) {
		/* Set init firmware as current firmware only if main firmware doesn't handle init */
		dev_ptr->main_fw_init_done = 0;
		dev_ptr->current_fw        = dev_ptr->init_fw_info;
	}

	return ret_val;
}
#endif

uint8_t ch_common_group_start(ch_group_t *grp_ptr) {
	uint8_t err = 0;

	err = chdrv_group_start(grp_ptr);
	if (!err) {
#ifdef INCLUDE_SHASTA_SUPPORT
		for (int dev_num = 0; dev_num < grp_ptr->num_ports; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

			if (!dev_ptr->sensor_connected) {
				continue;
			}
			if (dev_ptr->main_fw_info->fw_includes_sensor_init) {
				dev_ptr->main_fw_init_done = 1;
				/* Check if restart is pending */
			} else if (!dev_ptr->main_fw_init_done) {
				/* Restart */
				if (!err) {
					dev_ptr->current_fw = dev_ptr->main_fw_info;
					err                 = chdrv_restart(dev_ptr);
				}
				if (!err) {
					dev_ptr->main_fw_init_done = 1;
				}
			}
		}
#endif
	}

	if (!err) {
		grp_ptr->status = CH_GROUP_STAT_INIT_OK;
	}

	return err;
}

uint8_t ch_common_set_mode(ch_dev_t *dev_ptr, ch_mode_t mode) {
	uint8_t ret_val = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	measurement_queue_t *meas_q_ptr = &(dev_ptr->meas_queue);

	if (dev_ptr->sensor_connected) {
		switch (mode) {
		case CH_MODE_IDLE:
			// disable trigger sources
			meas_q_ptr->trigsrc = 0;
			break;

		case CH_MODE_FREERUN:
			ch_common_set_freerun_interval_us(dev_ptr, dev_ptr->freerun_intvl_us);

			meas_q_ptr->trigsrc = TRIGSRC_RTC;  // enable timer-based trigger
			break;

		case CH_MODE_TRIGGERED_RX_ONLY:
		case CH_MODE_TRIGGERED_TX_RX:
			if (dev_ptr->group->sensor_trig_pin == 1) {
				meas_q_ptr->trigsrc = TRIGSRC_HWTRIGGER_INT1;
			} else if (dev_ptr->group->sensor_trig_pin == 2) {
				meas_q_ptr->trigsrc = TRIGSRC_HWTRIGGER_INT2;
			}
			break;
		case CH_MODE_CONTINUOUS_RX:
			meas_q_ptr->trigsrc = TRIGSRC_CONTINUOUS_RX;
			break;
		default:
			ret_val = RET_ERR;  // return non-zero to indicate error
			break;
		}

		if (ret_val == RET_OK) {
			ret_val = ch_meas_write_config(dev_ptr);
		}
		if (ret_val == RET_OK) {
			ret_val = chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);
		}
		if (ret_val == RET_OK && mode == CH_MODE_CONTINUOUS_RX) {
			// a single SW trigger is needed for continuous RX mode
			chdrv_event_trigger(dev_ptr, EVENT_SW_TRIG);
		}
	}

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t opmode_reg;
	uint8_t period_reg;
	uint8_t tick_interval_reg;
	uint16_t max_tick_interval;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		opmode_reg        = CH101_COMMON_REG_OPMODE;
		period_reg        = CH101_COMMON_REG_PERIOD;
		tick_interval_reg = CH101_COMMON_REG_TICK_INTERVAL;
		max_tick_interval = CH101_MAX_TICK_INTERVAL;
	} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
		opmode_reg        = CH201_COMMON_REG_OPMODE;
		period_reg        = CH201_COMMON_REG_PERIOD;
		tick_interval_reg = CH201_COMMON_REG_TICK_INTERVAL;
		max_tick_interval = CH201_MAX_TICK_INTERVAL;
	}

	if (dev_ptr->sensor_connected) {
		switch (mode) {
		case CH_MODE_IDLE:
			chdrv_write_byte(dev_ptr, period_reg, 0);
			chdrv_write_word(dev_ptr, tick_interval_reg, max_tick_interval);
			chdrv_write_byte(dev_ptr, opmode_reg, CH_MODE_IDLE);
			break;

		case CH_MODE_FREERUN:
			ch_common_set_freerun_interval_us(dev_ptr, dev_ptr->freerun_intvl_us);
			chdrv_write_byte(dev_ptr, opmode_reg, CH_MODE_FREERUN);
			break;

		case CH_MODE_TRIGGERED_TX_RX:
			chdrv_write_byte(dev_ptr, opmode_reg, CH_MODE_TRIGGERED_TX_RX);
			break;

		case CH_MODE_TRIGGERED_RX_ONLY:
			chdrv_write_byte(dev_ptr, opmode_reg, CH_MODE_TRIGGERED_RX_ONLY);
			break;

		default:
			ret_val = RET_ERR;  // return non-zero to indicate error
			break;
		}
	}

#endif  // INCLUDE_SHASTA_SUPPORT

	return ret_val;
}

uint8_t ch_common_fw_load(ch_dev_t *dev_ptr) {
	uint8_t ch_err         = 0;
	uint16_t prog_mem_addr = 0;                                        // current destination address in sensor mem
	uint8_t *src_addr      = (uint8_t *)dev_ptr->current_fw->fw_text;  // firmware image text to load
	uint16_t fw_size       = 0;
	uint16_t num_xfers;
	uint16_t xfer_num      = 0;
	uint16_t bytes_left    = 0;
	uint16_t max_xfer_size = 0;  // max number of bytes per write transfer to sensor

	fw_size = dev_ptr->current_fw->fw_text_size;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (fw_size == 0) {  // handle missing size (old init)
			fw_size = CHX01_FW_SIZE;
		}
		prog_mem_addr = CHX01_PROG_MEM_ADDR;
#else
		ch_err = 1;
#endif
	} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		prog_mem_addr = ICU_PROG_MEM_ADDR;
#else
		ch_err = 1;
#endif
	}

	max_xfer_size = fw_size;
#ifdef MAX_PROG_XFER_SIZE  // if user specified max xfer size in chirp_board_config.h
	if (fw_size > MAX_PROG_XFER_SIZE) {
		max_xfer_size = MAX_PROG_XFER_SIZE;
	}
#endif

	/* Write f/w to sensor */
	num_xfers  = (fw_size + (max_xfer_size - 1)) / max_xfer_size;  // total # of transfers req'd
	bytes_left = fw_size;

	while (!ch_err && (xfer_num < num_xfers)) {
		uint16_t xfer_nbytes;  // number of bytes in this transfer

		if (bytes_left >= max_xfer_size) {
			xfer_nbytes = max_xfer_size;
		} else {
			xfer_nbytes = bytes_left;
		}

		if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
			ch_err = chdrv_prog_mem_write(dev_ptr, prog_mem_addr, src_addr, xfer_nbytes);
#endif
		} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
			ch_err = chdrv_burst_write(dev_ptr, prog_mem_addr, src_addr, xfer_nbytes);
		}

		src_addr      += xfer_nbytes;  // adjust source and destination addrs
		prog_mem_addr += xfer_nbytes;

		bytes_left -= xfer_nbytes;  // adjust remaining byte count
		xfer_num++;
	}

	/* Write separate interrupt vectors (last bytes in prog mem) */
	if (!ch_err && (dev_ptr->current_fw->fw_vec != NULL) && (dev_ptr->current_fw->fw_vec_size != 0)) {
		src_addr             = (uint8_t *)dev_ptr->current_fw->fw_vec;  // firmware image vectors to load
		uint16_t xfer_nbytes = dev_ptr->current_fw->fw_vec_size;        // fit in single transfer

		if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
			prog_mem_addr = CHX01_PROG_MEM_ADDR + CHX01_PROG_MEM_SIZE - dev_ptr->current_fw->fw_vec_size;
			ch_err        = chdrv_prog_mem_write(dev_ptr, prog_mem_addr, src_addr, xfer_nbytes);
#endif
		} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
			prog_mem_addr = ICU_PROG_MEM_ADDR + ICU_PROG_MEM_SIZE - dev_ptr->current_fw->fw_vec_size;
			ch_err        = chdrv_burst_write(dev_ptr, prog_mem_addr, src_addr, xfer_nbytes);
#endif
		}
	}
	return ch_err;
}

uint8_t ch_common_set_sample_interval(ch_dev_t *dev_ptr, uint16_t interval_ms) {
	/* Deprecated - use new equivalent function */
	return ch_common_set_freerun_interval(dev_ptr, interval_ms);
}

uint8_t ch_common_set_freerun_interval(ch_dev_t *dev_ptr, uint16_t interval_ms) {
	uint8_t ret_val = 1;  // default = error

	if ((interval_ms != 0) && dev_ptr->sensor_connected) {
		uint32_t rtc_ticks = dev_ptr->rtc_cal_result * interval_ms / dev_ptr->group->rtc_cal_pulse_ms;

		ret_val = set_interval_ticks(dev_ptr, rtc_ticks, CH_DEFAULT_MEAS_NUM);
	}
	if (ret_val == 0) {
		dev_ptr->freerun_intvl_us = (interval_ms * 1000);
	}
	return ret_val;
}

uint8_t ch_common_set_freerun_interval_us(ch_dev_t *dev_ptr, uint32_t interval_us) {
	uint8_t ret_val = 1;  // default = error

	if ((interval_us != 0) && dev_ptr->sensor_connected) {
		uint32_t rtc_ticks = dev_ptr->rtc_cal_result * interval_us / (dev_ptr->group->rtc_cal_pulse_ms * 1000);

		ret_val = set_interval_ticks(dev_ptr, rtc_ticks, CH_DEFAULT_MEAS_NUM);
	}
	if (ret_val == 0) {
		dev_ptr->freerun_intvl_us = interval_us;
	}
	return ret_val;
}

uint8_t ch_common_set_freerun_interval_ticks(ch_dev_t *dev_ptr, uint32_t interval_ticks) {
	uint8_t ret_val = 1;  // default = error

	if ((interval_ticks != 0) && dev_ptr->sensor_connected) {
		ret_val = set_interval_ticks(dev_ptr, interval_ticks, CH_DEFAULT_MEAS_NUM);
	}
	if (ret_val == 0) {
		dev_ptr->freerun_intvl_us = ch_common_ticks_to_usec(dev_ptr, interval_ticks);
	}
	return ret_val;
}

uint8_t ch_common_set_freerun_time_hop(ch_dev_t *dev_ptr, uint8_t meas_num, bool enable) {
	uint8_t ret_val = 1; /* default = error */

	uint16_t time_hop_mask = enable ? 0x0000 : MEAS_PERIOD_TIME_HOP_MASK;
#ifdef INCLUDE_SHASTA_SUPPORT
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);

	meas_ptr->meas_period = get_rtc_measure_period(meas_ptr->meas_period) | time_hop_mask;
	ret_val               = ch_meas_write_config(dev_ptr);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	(void)meas_num;

	uint8_t tick_interval_reg;
	uint16_t tick_interval;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		tick_interval_reg = CH101_COMMON_REG_TICK_INTERVAL;
	} else {
		tick_interval_reg = CH201_COMMON_REG_TICK_INTERVAL;
	}
	ret_val = chdrv_read_word(dev_ptr, tick_interval_reg, &tick_interval);
	if (!ret_val) {
		tick_interval  = get_rtc_measure_period(tick_interval) | time_hop_mask;
		ret_val       |= chdrv_write_word(dev_ptr, tick_interval_reg, tick_interval);
	}
#endif

	return ret_val;
}

static inline bool is_time_hopping_enabled(uint16_t meas_period) {
	return ((meas_period & MEAS_PERIOD_TIME_HOP_MASK) != MEAS_PERIOD_TIME_HOP_MASK);
}

static uint16_t get_rtc_measure_period(uint16_t raw_meas_period) {
	uint16_t meas_period;

	if (!is_time_hopping_enabled(raw_meas_period)) {
		/* do not clear upper bits unless they are both set (time hopping disabled) */
		meas_period = raw_meas_period & ~MEAS_PERIOD_TIME_HOP_MASK;
	} else {
		meas_period = raw_meas_period;
	}
	return meas_period;
}

static uint16_t update_rtc_measure_period(uint16_t prev_meas_period, uint16_t new_meas_period) {
	uint16_t meas_period;

	if (!is_time_hopping_enabled(prev_meas_period)) {
		meas_period = new_meas_period | MEAS_PERIOD_TIME_HOP_MASK;
	} else {
		meas_period = new_meas_period;
	}
	return meas_period;
}

static uint8_t set_interval_ticks(ch_dev_t *dev_ptr, uint32_t rtc_ticks, uint8_t meas_num) {

	if (rtc_ticks == 0)
		return 1;

#ifdef INCLUDE_SHASTA_SUPPORT
	return ch_common_meas_set_interval_ticks(dev_ptr, meas_num, rtc_ticks);
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	(void)meas_num;

	uint32_t period;
	uint8_t period_reg;
	uint8_t tick_interval_reg;
	uint8_t ret_val;
	uint16_t max_tick_interval;
	uint16_t current_tick_interval;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		period_reg        = CH101_COMMON_REG_PERIOD;
		tick_interval_reg = CH101_COMMON_REG_TICK_INTERVAL;
		max_tick_interval = CH101_MAX_TICK_INTERVAL;
	} else {
		period_reg        = CH201_COMMON_REG_PERIOD;
		tick_interval_reg = CH201_COMMON_REG_TICK_INTERVAL;
		max_tick_interval = CH201_MAX_TICK_INTERVAL;
	}

	period = (rtc_ticks / 2048) + 1;  // TODO need define
	if (period <= UINT8_MAX) {        /* check if result fits in register */
		uint32_t tick_interval;

		if (period != 0) {
			tick_interval = rtc_ticks / period;

			while (tick_interval > max_tick_interval) {  // enforce max interval
				tick_interval >>= 1;
				period        <<= 1;
			}
		} else {
			tick_interval = max_tick_interval;
		}

		/* Read existing tick interval to get time hopping flag */
		ret_val = chdrv_read_word(dev_ptr, tick_interval_reg, &current_tick_interval);
		if (!ret_val) {
			tick_interval = update_rtc_measure_period(current_tick_interval, tick_interval);

			CH_LOG_INFO("Set period=%lu, tick_interval=%lu", period, tick_interval);

			ret_val  = chdrv_write_byte(dev_ptr, period_reg, (uint8_t)period);
			ret_val |= chdrv_write_word(dev_ptr, tick_interval_reg, (uint16_t)tick_interval);
		}
	} else {
		ret_val = 1;
	}
	return ret_val;
#endif  // INCLUDE_SHASTA_SUPPORT
}

// Note: uses actual num_samples, even for CH201
uint8_t ch_common_set_num_samples(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val = 1;  // default is error (not connected or num_samples too big)

#ifdef INCLUDE_SHASTA_SUPPORT
	ret_val = ch_common_meas_set_num_samples(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	if (!dev_ptr->sensor_connected || num_samples > dev_ptr->current_fw->max_samples) {
		return 1;
	}

	uint8_t max_range_reg;
	uint16_t num_rx_low_gain_samples = ch_get_rx_low_gain(dev_ptr);  // zero if unsupported

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		max_range_reg = CH101_COMMON_REG_MAX_RANGE;
	} else {
		max_range_reg            = CH201_COMMON_REG_MAX_RANGE;
		num_samples             /= 2;  // each internal count for CH201 represents 2 physical samples
		num_rx_low_gain_samples /= 2;
	}

	if (num_samples < (num_rx_low_gain_samples + 1)) {
		num_samples = (num_rx_low_gain_samples + 1);
	}

	if (num_samples <= UINT8_MAX) {
		ret_val = chdrv_write_byte(dev_ptr, max_range_reg, num_samples);
	}

	if (!ret_val) {
		if (dev_ptr->part_number == CH101_PART_NUMBER) {
			dev_ptr->num_rx_samples = num_samples;
		} else {
			dev_ptr->num_rx_samples = (num_samples * 2);  // store actual physical sample count
		}
	} else {
		dev_ptr->num_rx_samples = 0;
	}
#endif  // INCLUDE_SHASTA_SUPPORT

	return ret_val;
}

uint16_t ch_common_get_num_samples(ch_dev_t *dev_ptr) {
	uint16_t num_samples = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	/* Report configured number of samples in last completed measurement */
	uint8_t last_meas = ch_common_meas_get_last_num(dev_ptr);
	num_samples       = ch_common_meas_get_num_samples(dev_ptr, last_meas);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	num_samples = dev_ptr->num_rx_samples;
#endif
	return num_samples;
}

uint8_t ch_common_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range_mm) {
	uint8_t ret_val;

#ifdef INCLUDE_SHASTA_SUPPORT
	ret_val = ch_common_meas_set_max_range(dev_ptr, CH_DEFAULT_MEAS_NUM, max_range_mm);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint32_t num_samples;

	ret_val = (!dev_ptr->sensor_connected);

	if (!ret_val) {
		num_samples = ch_common_mm_to_samples(dev_ptr, max_range_mm);

		if (num_samples > dev_ptr->current_fw->max_samples) {
			num_samples        = dev_ptr->current_fw->max_samples;
			dev_ptr->max_range = ch_common_samples_to_mm(dev_ptr, num_samples);  // store reduced max range
		} else {
			dev_ptr->max_range = max_range_mm;  // store user-specified max range
		}

		CH_LOG_DEBUG("num_samples=%lu", num_samples);
	}

	if (!ret_val) {
		ret_val = ch_set_num_samples(dev_ptr, num_samples);
	}

	CH_LOG_INFO("Set samples: ret_val: %u  dev_ptr->num_rx_samples: %u", ret_val, dev_ptr->num_rx_samples);

#endif  // INCLUDE_SHASTA_SUPPORT
	return ret_val;
}

uint16_t ch_common_mm_to_samples(ch_dev_t *dev_ptr, uint16_t num_mm) {
	uint8_t err;
	uint32_t scale_factor;
	uint32_t num_samples = 0;
	uint8_t oversample   = 0;  // used for CHx01 ODR value
	uint32_t divisor1    = 1;
	uint32_t divisor2    = (dev_ptr->group->rtc_cal_pulse_ms * CH_SPEEDOFSOUND_MPS);
#ifdef INCLUDE_SHASTA_SUPPORT
	ch_odr_t odr = (ch_odr_t)dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].odr;
#else
	oversample = dev_ptr->current_fw->oversample;  // set during f/w init
#endif

	err = (!dev_ptr) || (!dev_ptr->sensor_connected);

	if (!err) {
		if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
			if (dev_ptr->part_number == CH101_PART_NUMBER) {
				divisor1 = 0x2000;  // (4*16*128)  TODO need define(s)
			} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
				divisor1 = 0x4000;  // (4*16*128*2)  TODO need define(s)
			}
		} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
			divisor1 = (CH_PMUT_TICKS_PER_CYCLE / 2 * dev_ptr->fcount_cycles) << (7 - odr);
			// 1/2 range_mm_per_sound_path_mm * 16 clock_cycles_per_op_freq_cycle * fcount_cycles * 2^(7-cic_odr)
#endif  // INCLUDE_SHASTA_SUPPORT
		}
#ifdef INCLUDE_SHASTA_SUPPORT
		scale_factor = (uint32_t)dev_ptr->pmut_clock_fcount;
#elif defined(INCLUDE_WHITNEY_SUPPORT)
		if (dev_ptr->tof_scale_factor == 0) {
			dev_ptr->current_fw->calib_funcs->store_scalefactor(dev_ptr);
		}
		scale_factor = (uint32_t)dev_ptr->tof_scale_factor;
#endif
	}

	if (!err) {
		// Two steps of division to avoid needing a type larger than 32 bits
		// Ceiling division to ensure result is at least enough samples to meet specified range
		// Oversample value is signed power of two for this firmware relative to standard f/8 sampling.

		num_samples = ((dev_ptr->rtc_cal_result * scale_factor) + (divisor1 - 1)) / divisor1;

		num_samples = (((num_samples * num_mm) << oversample) + (divisor2 - 1)) / divisor2;

		err = (num_samples > UINT16_MAX);
	}

	if (!err) {
		if (dev_ptr->part_number == CH201_PART_NUMBER) {
			num_samples *= 2;  // each internal count for CH201 represents 2 physical samples
		}
	}

	if (err) {
		num_samples = 0;  // return zero if error
	}

	return (uint16_t)num_samples;
}

uint16_t ch_common_samples_to_mm(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint32_t num_mm = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	num_mm = ch_common_meas_samples_to_mm(dev_ptr, CH_DEFAULT_MEAS_NUM, num_samples);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint32_t op_freq = dev_ptr->op_frequency;
	if (op_freq != 0) {
		num_mm = ((uint32_t)num_samples * CH_SPEEDOFSOUND_MPS * 8 * 1000) / (op_freq * 2);
	}

	/* Adjust for oversampling, if used */
	num_mm                >>= dev_ptr->current_fw->oversample;
#endif

	return (uint16_t)num_mm;
}

uint32_t ch_common_range_lsb_to_mm(const ch_dev_t *dev_ptr, uint32_t time_of_flight, ch_range_t range_type) {
	uint32_t range = CH_NO_TARGET;
#ifdef INCLUDE_SHASTA_SUPPORT
	// Calculate range
	uint32_t odr              = dev_ptr->odr_out;
	uint32_t rtc_cal_pulse_ms = (uint32_t)dev_ptr->group->rtc_cal_pulse_ms;

	uint32_t num = (CH_SPEEDOFSOUND_MPS * ((rtc_cal_pulse_ms * time_of_flight * (uint32_t)dev_ptr->fcount_cycles) >>
	                                       (2 + odr))  // bitshift down by 10 to handle overflow;
	);
	// this one can't overflow, bitshift down by 10 to match num
	uint32_t den = ((uint32_t)dev_ptr->rtc_cal_result * (uint32_t)dev_ptr->pmut_clock_fcount) >> 11;

	range = (num / den);

	// formula debug
	CH_LOG_DEBUG("num = (%u * ((%lu * %lu * %lu) >> (2 + %lu)))) = %lu", CH_SPEEDOFSOUND_MPS, rtc_cal_pulse_ms,
	             time_of_flight, (uint32_t)dev_ptr->fcount_cycles, odr, num);
	CH_LOG_DEBUG("den = ((%u * %u) >> 11) = %lu", dev_ptr->rtc_cal_result, dev_ptr->pmut_clock_fcount, den);
	CH_LOG_DEBUG("range = %lu   num = %lu   den = %lu", range, num, den);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint16_t scale_factor   = dev_ptr->tof_scale_factor;

	if (scale_factor != 0) {
		uint32_t num = (CH_SPEEDOFSOUND_MPS * dev_ptr->group->rtc_cal_pulse_ms * (uint32_t)time_of_flight);
		uint32_t den = ((uint32_t)dev_ptr->rtc_cal_result * (uint32_t)scale_factor) >> 11;  // TODO need define
		range        = (num / den);
		if (dev_ptr->part_number == CH201_PART_NUMBER) {
			range *= 2;
		}
		// Adjust for oversampling, if used
		range >>= dev_ptr->current_fw->oversample;
	}
#endif  // INCLUDE_SHASTA_SUPPORT

	// If rx-only node, adjust for pre-trigger time included in ToF
	if (dev_ptr->mode == CH_MODE_TRIGGERED_RX_ONLY) {
		uint32_t pretrig_adj = (CH_SPEEDOFSOUND_MPS * dev_ptr->group->pretrig_delay_us * 32) / 1000;

		// formula debug
		CH_LOG_DEBUG_START("pre-trig adjust = %lu:  range before = %lu  ", pretrig_adj, range);

		if (range > pretrig_adj) {
			// subtract adjustment from calculated range
			range -= pretrig_adj;
		} else {
			// underflow - range is very close to zero, use minimum value
			range = CH_MIN_RANGE_VAL;
		}

		// formula debug
		CH_LOG_DEBUG_MSG("after = %lu", range);
		CH_LOG_DEBUG_END();
	}

	if ((range_type == CH_RANGE_ECHO_ONE_WAY) && (range >= (CH_MIN_RANGE_VAL * 2))) {
		range /= 2;  // convert round-trip to one-way
	}
	return range;
}

uint16_t ch_common_get_num_output_samples(ch_dev_t *dev_ptr) {
	uint16_t num_samples = 0;

	if (dev_ptr->sensor_connected) {
		if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
			num_samples = dev_ptr->num_rx_samples;  // always return the max sample count

		} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
			uint16_t num_iq_bytes_addr     = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.num_iq_bytes);
			uint16_t num_iq_bytes          = 0;
			uint16_t iq_output_format_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.iq_output_format);
			uint16_t iq_output_format      = 0;

			uint8_t err = chdrv_read_word(dev_ptr, num_iq_bytes_addr, &num_iq_bytes);
			if (!err) {
				err = chdrv_read_word(dev_ptr, iq_output_format_addr, &iq_output_format);
			}
			if (!err) {
				// ASIC always reports number of IQ bytes available, even when
				// the output format is magnitude
				uint8_t sample_size = sizeof(ch_iq_sample_t);
				num_samples         = (num_iq_bytes / sample_size);
			}
#endif  // INCLUDE_SHASTA_SUPPORT
		}
	}

	return num_samples;
}

uint8_t ch_common_get_locked_state(ch_dev_t *dev_ptr) {
	uint8_t ret_val = 0;
#ifdef INCLUDE_WHITNEY_SUPPORT
	uint8_t ready_reg;
	uint8_t lock_mask = dev_ptr->current_fw->freqLockValue;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		ready_reg = CH101_COMMON_REG_READY;
	} else {
		ready_reg = CH201_COMMON_REG_READY;
	}

	if (dev_ptr->sensor_connected) {
		uint8_t ready_value = 0;
		chdrv_read_byte(dev_ptr, ready_reg, &ready_value);
		if (ready_value & lock_mask) {
			ret_val = 1;
		}
	}
#else
	(void)dev_ptr;
#endif
	return ret_val;
}

void ch_common_prepare_pulse_timer(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);

	chdrv_event_trigger(dev_ptr, EVENT_RTC_CAL);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t cal_trig_reg;
	uint8_t i;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
		cal_trig_reg = CH101_COMMON_REG_CAL_TRIG;
	} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
		cal_trig_reg = CH201_COMMON_REG_CAL_TRIG;
	}

	if (dev_ptr->rtc_status == CH_RTC_STATUS_CAL_BUS) {
		/* Clock cal uses I2C clock */
		uint8_t write_buf[RTC_CAL_BUS_NBYTES];

		write_buf[0] = CHX01_COMMON_CAL_TRIG_USE_BUS;  // put opcode for trig reg in first byte

		for (i = 1; i < RTC_CAL_BUS_NBYTES; i++)
			write_buf[i] = i - 1;

		chdrv_burst_write(dev_ptr, cal_trig_reg, write_buf, RTC_CAL_BUS_NBYTES);
		// long write to keep clock going during cal
		uint8_t dummy = 0;
		chbsp_i2c_read(dev_ptr, &dummy, 1);  // dummy read to activate tx int on sensor

	} else {
		/* Normal clock cal */
		chdrv_write_byte(dev_ptr, cal_trig_reg, 0);
	}
#endif  // INCLUDE_SHASTA_SUPPORT
}

void ch_common_store_pt_result(ch_dev_t *dev_ptr) {
	uint16_t pt_result_reg = 0;
	uint16_t rtc_cal_result;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (dev_ptr->part_number == CH101_PART_NUMBER) {
			pt_result_reg = CH101_COMMON_REG_CAL_RESULT;
		} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
			pt_result_reg = CH201_COMMON_REG_CAL_RESULT;
		}
#endif
	} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		pt_result_reg = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.rtc_cal_result);
#endif  // INCLUDE_SHASTA_SUPPORT
	}

	chdrv_read_word(dev_ptr, pt_result_reg, &rtc_cal_result);
	dev_ptr->rtc_cal_result = rtc_cal_result;

	if (dev_ptr->rtc_status == CH_RTC_STATUS_CAL_DONE) {
		dev_ptr->rtc_frequency = (rtc_cal_result * 1000) / dev_ptr->group->rtc_cal_pulse_ms;
	} else if (dev_ptr->rtc_status == CH_RTC_STATUS_CAL_BUS) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		dev_ptr->rtc_frequency = (dev_ptr->group->io_bus_speed_hz * CHX01_I2C_RTC_CYCLES) / rtc_cal_result;
#else
		dev_ptr->rtc_frequency = 0;
#endif
	}
}

#ifdef INCLUDE_SHASTA_SUPPORT
uint32_t ch_common_measure_pmut_frequency(ch_dev_t *dev_ptr) {

	clock_control_t *clock_ctrl_ptr    = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
	raw_output_data_t *output_data_ptr = (raw_output_data_t *)&((dev_ptr->sens_cfg_addr)->raw);
	uint16_t raw_pmut_count            = 0;
	uint32_t pmut_freq                 = 0;
	uint16_t reg_addr;
	uint8_t err = 0;

	/* setup frequency counter */
	reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->fcount_cycles);  // fcount cycles
	chdrv_write_word(dev_ptr, reg_addr, dev_ptr->fcount_cycles);
	err = chdrv_event_trigger_and_wait(dev_ptr, EVENT_MUT_FCOUNT);  // start PMUT freq count

	if (err) {
		CH_LOG_ERR("Error waiting for EVENT_MUT_FCOUNT");
	}

	if (!err) {
		/* read result */
		reg_addr = (uint16_t)(uintptr_t) & (output_data_ptr->pmut_clock_fcount);  // PMUT freq count
		err      = (uint8_t)chdrv_read_word(dev_ptr, reg_addr, &raw_pmut_count);
	}

	if (!err) {
		/* Calculate PMUT operating frequency */
		pmut_freq = ((dev_ptr->rtc_frequency * raw_pmut_count) / dev_ptr->fcount_cycles) / 16;
		if (pmut_freq == 0) {  // avoid divide by zero when calculating a period from the frequency
			pmut_freq      = PMUT_FREQUENCY_ERROR_CODE;
			raw_pmut_count = PMUT_FREQUENCY_ERROR_CODE;
		}
		/* Store values in device descriptor */
		dev_ptr->op_frequency      = pmut_freq;
		dev_ptr->pmut_clock_fcount = raw_pmut_count;
	}

	CH_LOG_INFO("raw_pmut_count = %u pmut_freq = %lu Hz", raw_pmut_count, pmut_freq);

	return pmut_freq;
}
#endif

void ch_common_store_op_freq(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_SHASTA_SUPPORT
	uint32_t pmut_freq;
	uint32_t cpu_freq;

	CH_LOG_DEBUG("dev_ptr->fcount_cycles = %u", dev_ptr->fcount_cycles);
	CH_LOG_DEBUG("dev_ptr->rtc_frequency = %u Hz", dev_ptr->rtc_frequency);

	/* Run BIST on sensor */
	chdrv_run_bist(dev_ptr);

	/* Calculate PMUT operating frequency */
	pmut_freq = ch_common_measure_pmut_frequency(dev_ptr);

	/* Adjust cpu frequency to avoid multiple of pmut freq */
	cpu_freq = chdrv_cpu_freq_adjust(dev_ptr, pmut_freq);

	/* Store values in device descriptor */
	dev_ptr->orig_pmut_freq = pmut_freq;
	dev_ptr->cpu_frequency  = cpu_freq;

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t tof_sf_reg;
	uint16_t raw_freq;  // aka ToF scale factor
	uint32_t freq_counter_cycles;
	uint32_t num;
	uint32_t den;
	uint32_t op_freq;

	tof_sf_reg          = get_tof_sf_reg_addr(dev_ptr);
	freq_counter_cycles = dev_ptr->current_fw->freqCounterCycles;

	chdrv_read_word(dev_ptr, tof_sf_reg, &raw_freq);

	num = (uint32_t)(((dev_ptr->rtc_cal_result) * 1000U) / (CH_PMUT_TICKS_PER_CYCLE * freq_counter_cycles)) *
	      (uint32_t)(raw_freq);
	den     = (uint32_t)(dev_ptr->group->rtc_cal_pulse_ms);
	op_freq = (num / den);

	dev_ptr->op_frequency     = op_freq;
	dev_ptr->cpu_frequency    = chdrv_cpu_freq_calculate(dev_ptr);

#endif
}

void ch_common_store_bandwidth(ch_dev_t *dev_ptr) {
	uint32_t bandwidth = 0;
	ch_iq_sample_t iq_buf[2];  // assumes two consecutive samples
	uint16_t bw_index_1;
	uint16_t bw_index_2;
	uint16_t odr_freq_div;

#ifdef INCLUDE_SHASTA_SUPPORT
	bw_index_1   = ICU_BANDWIDTH_INDEX_1;
	bw_index_2   = ICU_BANDWIDTH_INDEX_2;
	odr_freq_div = 2;  // BIST uses CH_ODR_FREQ_DIV_2	(odr = 6)
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	bw_index_1                = CHX01_BANDWIDTH_INDEX_1;
	bw_index_2                = CHX01_BANDWIDTH_INDEX_2;
	odr_freq_div              = 8;  // BIST uses CH_ODR_FREQ_DIV_8	(odr = 4)
#endif

	uint8_t err = ch_get_iq_data(dev_ptr, iq_buf, bw_index_1, 2, CH_IO_MODE_BLOCK);
	if (!err) {
		uint32_t mag1sq = (uint32_t)(((int32_t)iq_buf[0].i * (int32_t)iq_buf[0].i) +
		                             ((int32_t)iq_buf[0].q * (int32_t)iq_buf[0].q));
		uint32_t mag2sq = (uint32_t)(((int32_t)iq_buf[1].i * (int32_t)iq_buf[1].i) +
		                             ((int32_t)iq_buf[1].q * (int32_t)iq_buf[1].q));

		bandwidth = FIXEDMUL(FP_log(FP_sqrt(FIXEDDIV(mag1sq, mag2sq))),
		                     (FIXEDDIV(INT2FIXED((uint64_t)dev_ptr->op_frequency),
		                               (FIXED_PI * ((bw_index_2 - bw_index_1) * odr_freq_div)))));

		dev_ptr->bandwidth = (uint16_t)FIXED2INT(bandwidth);
	} else {
		dev_ptr->bandwidth = 0;

		CH_LOG_ERR("Error reading BIST IQ data : %u", err);
	}
}

void ch_common_store_scale_factor(ch_dev_t *dev_ptr) {
#ifdef INCLUDE_WHITNEY_SUPPORT
	uint8_t err;
	uint8_t tof_sf_reg;
	uint16_t tof_scale_factor;

	tof_sf_reg = get_tof_sf_reg_addr(dev_ptr);

	err = chdrv_read_word(dev_ptr, tof_sf_reg, &tof_scale_factor);
	if (!err) {
		dev_ptr->tof_scale_factor = tof_scale_factor;
	} else {
		dev_ptr->tof_scale_factor = 0;
	}
#else
	dev_ptr->tof_scale_factor = 0;
#endif
}

static uint8_t get_sample_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                               ch_io_mode_t mode, uint8_t sample_size_in_bytes) {

	uint16_t iq_data_addr;
	uint16_t num_bytes  = (num_samples * sample_size_in_bytes);
	ch_group_t *grp_ptr = dev_ptr->group;
	int err             = 0;

	if ((num_samples == 0) || ((start_sample + num_samples) > dev_ptr->current_fw->max_samples)) {
		return 1;
	}

#ifdef INCLUDE_SHASTA_SUPPORT
	iq_data_addr  = dev_ptr->buf_addr;
	iq_data_addr += (start_sample * sample_size_in_bytes);  // add sample offset

	if (mode == CH_IO_MODE_BLOCK) {
		/* blocking transfer */
		err = chdrv_burst_read(dev_ptr, iq_data_addr, (uint8_t *)buf_ptr, num_bytes);
	} else {
		/* non-blocking transfer */
		err = chdrv_group_queue(grp_ptr, dev_ptr, 1, CHDRV_NB_TRANS_TYPE_STD, iq_data_addr, num_bytes,
		                        (uint8_t *)buf_ptr);
	}

#elif defined(INCLUDE_WHITNEY_SUPPORT)
	uint8_t use_prog_read     = 0;                          // default = do not use low-level programming interface

#ifndef USE_STD_I2C_FOR_IQ
	if (grp_ptr->num_connected[dev_ptr->bus_index] == 1) {  // if only one device on this bus
		use_prog_read = 1;                                  //   use low-level interface
	}
#endif

	if (dev_ptr->current_fw->max_num_thresholds == 0) {
		iq_data_addr = CH101_COMMON_REG_DATA;
	} else {
		iq_data_addr = CHX01_GPRMT_REG_DATA;
	}

	iq_data_addr += (start_sample * sample_size_in_bytes);

	if (mode == CH_IO_MODE_BLOCK) {
		/* blocking transfer */

		if (use_prog_read) {
			/* use low-level programming interface for speed */

			int num_transfers = (num_bytes + (CH_PROG_XFER_SIZE - 1)) / CH_PROG_XFER_SIZE;
			int bytes_left    = num_bytes;  // remaining bytes to read

			/* Convert register offsets to full memory addresses */
			if (dev_ptr->part_number == CH101_PART_NUMBER) {
				iq_data_addr += CH101_DATA_MEM_ADDR + CH101_COMMON_I2CREGS_OFFSET;
			} else {
				iq_data_addr += CH201_DATA_MEM_ADDR + CH201_COMMON_I2CREGS_OFFSET;
			}

			chbsp_program_enable(dev_ptr);  // assert PROG pin

			for (int xfer = 0; xfer < num_transfers; xfer++) {
				int bytes_to_read;
				uint8_t message[] = {(0x80 | CH_PROG_REG_CTL), 0x09};  // read burst command

				if (bytes_left > CH_PROG_XFER_SIZE) {
					bytes_to_read = CH_PROG_XFER_SIZE;
				} else {
					bytes_to_read = bytes_left;
				}
				chdrv_prog_write(dev_ptr, CH_PROG_REG_ADDR, (iq_data_addr + (xfer * CH_PROG_XFER_SIZE)));
				chdrv_prog_write(dev_ptr, CH_PROG_REG_CNT, (bytes_to_read - 1));
				err  = chdrv_prog_i2c_write(dev_ptr, message, sizeof(message));
				err |= chdrv_prog_i2c_read(dev_ptr, ((uint8_t *)buf_ptr + (xfer * CH_PROG_XFER_SIZE)), bytes_to_read);

				bytes_left -= bytes_to_read;
			}
			chbsp_program_disable(dev_ptr);  // de-assert PROG pin

		} else { /* if (use_prog_read) */
			/* use standard I2C interface */

			err = chdrv_burst_read(dev_ptr, iq_data_addr, (uint8_t *)buf_ptr, num_bytes);
		}

	} else {
		/* non-blocking transfer - queue a read transaction (must be started using ch_io_start_nb() ) */

		if (use_prog_read && (grp_ptr->i2c_drv_flags & I2C_DRV_FLAG_USE_PROG_NB)) {
			/* Use low-level programming interface to read data */

			/* Convert register offsets to full memory addresses */
			if (dev_ptr->part_number == CH101_PART_NUMBER) {
				iq_data_addr += (CH101_DATA_MEM_ADDR + CH101_COMMON_I2CREGS_OFFSET);
			} else {
				iq_data_addr += (CH201_DATA_MEM_ADDR + CH201_COMMON_I2CREGS_OFFSET);
			}

			err = chdrv_group_queue(grp_ptr, dev_ptr, 1, CHDRV_NB_TRANS_TYPE_PROG, iq_data_addr, num_bytes,
			                        (uint8_t *)buf_ptr);
		} else {
			/* Use regular I2C register interface to read data */
			err = chdrv_group_queue(grp_ptr, dev_ptr, 1, CHDRV_NB_TRANS_TYPE_STD, iq_data_addr, num_bytes,
			                        (uint8_t *)buf_ptr);
		}
	}

#endif  // INCLUDE_WHITNEY_SUPPORT

	return err;
}

uint8_t ch_common_set_sample_window(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t num_samples) {
	uint8_t err          = 1;
	uint16_t max_samples = dev_ptr->num_rx_samples;

	if ((num_samples <= CH_WINDOW_MAX_SAMPLES) && ((start_sample + num_samples) < max_samples)) {
		dev_ptr->win_start_sample = start_sample;
		dev_ptr->num_win_samples  = num_samples;
		err                       = 0;
	}

	return err;
}

uint16_t ch_common_get_amplitude_avg(ch_dev_t *dev_ptr) {
	uint16_t start_sample = dev_ptr->win_start_sample;
	uint16_t num_samples  = dev_ptr->num_win_samples;
	uint32_t total_amp    = 0;
	uint32_t avg_amp      = 0;
	uint8_t err           = 0;

	if ((start_sample != 0) && (num_samples != 0)) {

#ifdef INCLUDE_SHASTA_SUPPORT
		uint16_t window_amp_buf[CH_WINDOW_MAX_SAMPLES];

		err = ch_get_amplitude_data(dev_ptr, window_amp_buf, start_sample, num_samples, CH_IO_MODE_BLOCK);
		if (!err) {
			for (uint16_t idx = 0; idx < num_samples; idx++) {
				total_amp += window_amp_buf[idx];  // add amplitude for this sample
			}
		}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
		ch_iq_sample_t window_iq_buf[CH_WINDOW_MAX_SAMPLES];

		err = ch_get_iq_data(dev_ptr, window_iq_buf, start_sample, num_samples, CH_IO_MODE_BLOCK);
		if (!err) {
			for (uint16_t idx = 0; idx < num_samples; idx++) {
				total_amp += ch_iq_to_amplitude(&(window_iq_buf[idx]));  // add calculated amplitude
			}
		}
#endif
		avg_amp = (total_amp / num_samples);
	}

	return (uint16_t)avg_amp;
}

uint8_t ch_common_get_iq_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                              ch_io_mode_t mode) {
	uint8_t error = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t last_meas = ch_common_meas_get_last_num(dev_ptr);

	if (ch_meas_get_iq_output(dev_ptr, last_meas) != CH_OUTPUT_IQ) {
		error = 1;  // sensor must be in I/Q output mode
	}
#endif  // INCLUDE_WHITNEY_SUPPORT

	if (!error) {
		error = get_sample_data(dev_ptr, buf_ptr, start_sample, num_samples, mode, sizeof(ch_iq_sample_t));
	}

	return error;
}

uint8_t ch_common_get_amplitude_data(ch_dev_t *dev_ptr, uint16_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                                     ch_io_mode_t mode) {
	uint8_t error = 0;

#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t last_meas = ch_common_meas_get_last_num(dev_ptr);

	if (ch_meas_get_iq_output(dev_ptr, last_meas) == CH_OUTPUT_AMP) {
		/* Get amplitude values directly from sensor */
		error = get_sample_data(dev_ptr, (ch_iq_sample_t *)buf_ptr, start_sample, num_samples, mode, sizeof(uint16_t));
	} else {
		error = 1;  // sensor must be in amp output mode
	}
#elif defined(INCLUDE_WHITNEY_SUPPORT)
	ch_iq_sample_t iq_buf[CH_IQ_SAMPLES_PER_READ];
	uint16_t samples_in_chunk = 0;
	uint16_t sample_num       = start_sample;
	uint16_t samples_left     = num_samples;
	uint8_t chunks_left       = (num_samples + CH_IQ_SAMPLES_PER_READ - 1) / CH_IQ_SAMPLES_PER_READ;

	/* Validate mode (only blocking mode is supported) and sample count/offset */
	if ((mode != CH_IO_MODE_BLOCK) || (start_sample + num_samples > dev_ptr->current_fw->max_samples)) {
		error = 1;
	}

	while (!error && (chunks_left-- > 0)) {

		/* Read I/Q data */
		if (samples_left > CH_IQ_SAMPLES_PER_READ) {
			samples_in_chunk = CH_IQ_SAMPLES_PER_READ;
		} else {
			samples_in_chunk = samples_left;
		}

		samples_left -= samples_in_chunk;  // adjust remaining sample count for next pass

		error = get_sample_data(dev_ptr, iq_buf, sample_num, samples_in_chunk, mode, sizeof(ch_iq_sample_t));
		if (error) {
			break;
		}

		/* Calculate amplitudes and store in user buffer */
		for (uint16_t idx = 0; idx < samples_in_chunk; idx++) {
			buf_ptr[sample_num++] = ch_iq_to_amplitude(&iq_buf[idx]);
		}
	}
#endif  // INCLUDE_SHASTA_SUPPORT

	return error;
}

uint8_t ch_common_get_amp_thresh_data(ch_dev_t *dev_ptr, ch_amp_thresh_t *buf_ptr, uint16_t start_sample,
                                      uint16_t num_samples, ch_io_mode_t mode) {

	uint8_t error = 1;  // default return is error
#ifdef INCLUDE_SHASTA_SUPPORT
	uint8_t last_meas = ch_common_meas_get_last_num(dev_ptr);

	if (ch_meas_get_iq_output(dev_ptr, last_meas) ==
	    CH_OUTPUT_AMP_THRESH) {  // sensor must be in amp+thresh output mode

		/* Get amplitude + threshold pairs from sensor */
		error = get_sample_data(dev_ptr, (ch_iq_sample_t *)buf_ptr, start_sample, num_samples, mode,
		                        sizeof(ch_amp_thresh_t));
	}
#else
	(void)dev_ptr;
	(void)buf_ptr;
	(void)start_sample;
	(void)num_samples;
	(void)mode;
#endif
	return error;
}

uint8_t ch_common_set_rx_low_gain(ch_dev_t *dev_ptr, uint16_t num_samples) {
	uint8_t ret_val = 1;

#ifdef INCLUDE_WHITNEY_SUPPORT
	if (dev_ptr->part_number == CH201_PART_NUMBER) {
		if (num_samples > dev_ptr->num_rx_samples - 1) {  // do not extend past end of active range
			num_samples = (dev_ptr->num_rx_samples - 1);
		}

		if (num_samples < CH201_COMMON_RX_LOW_GAIN_MIN) {  // enforce minimum
			num_samples = CH201_COMMON_RX_LOW_GAIN_MIN;
		}

		uint8_t rx_lowgain_reg = CH201_COMMON_REG_LOW_GAIN_RXLEN;
		uint8_t reg_value      = (num_samples / 2);  // CH201 value is 1/2 actual sample count
		ret_val                = chdrv_write_byte(dev_ptr, rx_lowgain_reg, reg_value);
	}
#else
	(void)dev_ptr;
	(void)num_samples;
#endif
	return ret_val;
}

uint16_t ch_common_get_rx_low_gain(ch_dev_t *dev_ptr) {
	uint16_t num_samples = 0;

	if (dev_ptr->part_number != CH201_PART_NUMBER) {
		num_samples = 0;  // error - only supported on CH201
	} else {
#ifdef INCLUDE_WHITNEY_SUPPORT
		uint8_t reg_value = 0;
		uint8_t ret_val   = chdrv_read_byte(dev_ptr, CH201_COMMON_REG_LOW_GAIN_RXLEN, &reg_value);

		if (ret_val == 0) {
			num_samples = reg_value * 2;  // actual sample count is 2x register value
		}
#else
		(void)dev_ptr;
#endif
	}

	return num_samples;
}

uint8_t ch_common_set_tx_length(ch_dev_t *dev_ptr, uint16_t num_cycles) {
	uint8_t ret_val = 0;

	CH_LOG_INFO("num_cycles=%d", num_cycles);

	if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (dev_ptr->part_number == CH101_PART_NUMBER) {
			ret_val = chdrv_write_byte(dev_ptr, CH101_COMMON_REG_TX_LENGTH, num_cycles);
		} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
			ret_val = chdrv_write_byte(dev_ptr, CH201_COMMON_REG_TX_LENGTH, num_cycles);
		}
#else
		ret_val = 1;
#endif
	} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		for (uint8_t seg_num = 0; seg_num < CH_MEAS_MAX_SEGMENTS; seg_num++) {
			pmut_transceiver_inst_t *inst_ptr =
					(pmut_transceiver_inst_t *)&(dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].trx_inst[seg_num]);
			ch_meas_seg_type_t seg_type;

			seg_type = (ch_meas_seg_type_t)((inst_ptr->cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);

			if (seg_type == CH_MEAS_SEG_TYPE_TX) {
				inst_ptr->length = num_cycles;

				break;  // only modify first tx found
			}
		}
		ret_val = ch_meas_write_config(dev_ptr);
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	return ret_val;
}

uint16_t ch_common_get_tx_length(ch_dev_t *dev_ptr) {
	uint16_t num_cycles = 0;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		uint8_t num_cycles_8 = 0;
		if (dev_ptr->part_number == CH101_PART_NUMBER) {
			chdrv_read_byte(dev_ptr, CH101_COMMON_REG_TX_LENGTH, &num_cycles_8);
		} else if (dev_ptr->part_number == CH201_PART_NUMBER) {
			chdrv_read_byte(dev_ptr, CH201_COMMON_REG_TX_LENGTH, &num_cycles_8);
		}
		num_cycles = num_cycles_8;
#endif
	} else if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		for (uint8_t seg_num = 0; seg_num < CH_MEAS_MAX_SEGMENTS; seg_num++) {
			ch_meas_seg_type_t seg_type;
			uint16_t cmd_config = dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].trx_inst[seg_num].cmd_config;
			uint16_t seg_length = dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].trx_inst[seg_num].length;

			seg_type = (ch_meas_seg_type_t)((cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);

			if (seg_type == CH_MEAS_SEG_TYPE_TX) {
				num_cycles += seg_length;
			} else if (seg_type == CH_MEAS_SEG_TYPE_EOF) {
				break;
			}
		}
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	return num_cycles;
}

uint8_t ch_common_set_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr) {
	uint8_t ret_val = RET_ERR;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (dev_ptr->sensor_connected && (cal_ptr != NULL)) {
			ret_val  = chdrv_write_word(dev_ptr, CH101_COMMON_REG_DCO_PERIOD, cal_ptr->dco_period);
			ret_val |= chdrv_write_word(dev_ptr, CH101_COMMON_REG_REV_CYCLES, cal_ptr->rev_cycles);
		}
#else
		(void)dev_ptr;
		(void)cal_ptr;
#endif
	}
	return ret_val;
}

uint8_t ch_common_set_rtc(ch_dev_t *dev_ptr, ch_rtc_src_t rtc_source, uint16_t rtc_freq) {
	uint8_t ret_val = RET_OK;

	if ((rtc_freq == 0) && (rtc_source == CH_RTC_SRC_EXTERNAL)) {
		ret_val = RET_ERR;  // freq is required if using external RTC source
	}
	if ((rtc_freq == 0) && (dev_ptr->asic_gen == CH_ASIC_GEN_1_WHITNEY)) {
		ret_val = RET_ERR;  // zero is invalid on CH101 & CH201 - no factory test data
	}

	if (ret_val == RET_OK) {
		dev_ptr->rtc_frequency = rtc_freq;  // if zero, will use factory test result (Shasta only)

		if (rtc_source == CH_RTC_SRC_INTERNAL) {
			if (rtc_freq == 0) {
				dev_ptr->group->rtc_cal_type = CH_RTC_CAL_MANUAL;
				dev_ptr->rtc_status          = CH_RTC_STATUS_CAL_FACTORY;
			} else if (rtc_freq == CH_RTC_USE_BUS_SPEED) {
				dev_ptr->group->rtc_cal_type = CH_RTC_CAL_BUS;
				dev_ptr->rtc_status          = CH_RTC_STATUS_CAL_BUS;
			} else {
				dev_ptr->group->rtc_cal_type = CH_RTC_CAL_MANUAL;
				dev_ptr->rtc_status          = CH_RTC_STATUS_CAL_ESTIMATED;
			}
		} else if (rtc_source == CH_RTC_SRC_EXTERNAL) {
			dev_ptr->group->rtc_cal_type = CH_RTC_CAL_MANUAL;
			dev_ptr->rtc_status          = CH_RTC_STATUS_EXTERNAL;
		}
	}
	return ret_val;
}

uint8_t ch_common_get_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr) {
	uint8_t ret_val = RET_ERR;

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		if (dev_ptr->sensor_connected && (cal_ptr != NULL)) {
			ret_val  = chdrv_read_word(dev_ptr, CH101_COMMON_REG_DCO_PERIOD, &(cal_ptr->dco_period));
			ret_val |= chdrv_read_word(dev_ptr, CH101_COMMON_REG_REV_CYCLES, &(cal_ptr->rev_cycles));
		}
#else
		(void)dev_ptr;
		(void)cal_ptr;
#endif
	}

	return ret_val;
}

uint8_t ch_common_check_program(ch_dev_t *dev_ptr) {
	uint16_t addr;
	uint16_t num_bytes;  // total bytes to read
	uint8_t num_transfers;
	uint16_t bytes_left;  // remaining bytes to read
	uint8_t rx_buf[CH_PROG_XFER_SIZE];
	uint8_t err = 0;

	num_bytes     = dev_ptr->current_fw->fw_text_size;
	num_transfers = (num_bytes + (CH_PROG_XFER_SIZE - 1)) / CH_PROG_XFER_SIZE;
	bytes_left    = num_bytes;

	for (uint8_t xfer_num = 0; !err && (xfer_num < num_transfers); xfer_num++) {
		uint16_t bytes_to_read;

		if (bytes_left > CH_PROG_XFER_SIZE) {
			bytes_to_read = CH_PROG_XFER_SIZE;
		} else {
			bytes_to_read = bytes_left;
		}

		/* Read bytes from program memory */
#ifdef INCLUDE_SHASTA_SUPPORT
		addr = ICU_PROG_MEM_ADDR;
		err  = chdrv_burst_read(dev_ptr, (addr + (xfer_num * CH_PROG_XFER_SIZE)), rx_buf, bytes_to_read);

#elif defined(INCLUDE_WHITNEY_SUPPORT)
		uint8_t message[] = {(0x80 | CH_PROG_REG_CTL), 0x09};  // read burst command

		addr = CHX01_PROG_MEM_ADDR;
		chbsp_program_enable(dev_ptr);  // assert PROG line
		chdrv_prog_write(dev_ptr, CH_PROG_REG_ADDR, (addr + (xfer_num * CH_PROG_XFER_SIZE)));
		chdrv_prog_write(dev_ptr, CH_PROG_REG_CNT, (CH_PROG_XFER_SIZE - 1));

		err  = chdrv_prog_i2c_write(dev_ptr, message, sizeof(message));
		err |= chdrv_prog_i2c_read(dev_ptr, rx_buf, bytes_to_read);
		chbsp_program_disable(dev_ptr);  // de-assert PROG line
#endif  // INCLUDE_SHASTA_SUPPORT

		bytes_left -= bytes_to_read;  // adjust remaining byte count

		/* Compare read bytes with original firmware image */
		if (!err) {
			for (uint16_t idx = 0; idx < bytes_to_read; idx++) {
				uint8_t *fw_ptr = ((uint8_t *)(dev_ptr->current_fw->fw_text) + (xfer_num * CH_PROG_XFER_SIZE));

				if (rx_buf[idx] != fw_ptr[idx]) {
					err = 1;
					break;
				}
			}
		}
	} /* end for (xfer_num < num_transfers) */

#ifdef INCLUDE_WHITNEY_SUPPORT
	if (dev_ptr->group->num_connected[dev_ptr->bus_index] > 1) {  // if more than one device on this I2C bus
		chbsp_delay_ms(10);                                       // delay to let PROG interface settle
	}
#endif  // INCLUDE_WHITNEY_SUPPORT

	return err;
}

#ifdef INCLUDE_WHITNEY_SUPPORT
/*!
 * \brief Set DCO code and measure op frequency on a CHx01 device.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \param dcocode 		new DCO code to write to the device
 *
 * \return PMUT operating frequency in Hz
 *
 * This static function must only be called after initialization (ie after calling ch_group_start()).
 */
/*!
 */
static uint32_t set_new_dco_code(ch_dev_t *dev_ptr, uint16_t dcocode) {
	ch_common_set_mode(dev_ptr, CH_MODE_IDLE);
	chdrv_write_word(dev_ptr, CH101_COMMON_REG_DCO_PERIOD, dcocode);
	chdrv_wait_for_lock(dev_ptr, CHDRV_FREQLOCK_TIMEOUT_MS);
	ch_common_set_mode(dev_ptr, CH_MODE_TRIGGERED_TX_RX);
	dev_ptr->current_fw->calib_funcs->store_op_freq(dev_ptr);

	if (dev_ptr->op_frequency == 0) {  // catch possible error where op_frequency is zero, causing divide by zero error
		dev_ptr->op_frequency = PMUT_FREQUENCY_ERROR_CODE;
	}
	return dev_ptr->op_frequency;
}

static inline uint8_t get_tof_sf_reg_addr(const ch_dev_t *dev_ptr) {
	if (dev_ptr->current_fw->max_num_thresholds == 0) {
		return CH101_COMMON_REG_TOF_SF;
	} else {
		return CHX01_GPRMT_REG_TOF_SF;
	}
}

#endif  // INCLUDE_WHITNEY_SUPPORT

#ifdef INCLUDE_SHASTA_SUPPORT

static uint16_t pmut_bias_trim_to_code(uint16_t freq_trim, uint8_t bias_trim) {
	return (freq_trim & SCM_PMUT_CLK_FREQ_TRIM_BM) +
	       ((bias_trim << SCM_PMUT_CLK_BIAS_TRIM_BS) & SCM_PMUT_CLK_BIAS_TRIM_BM);
}

/*!
 * \brief Set PMUT clock code and measure op frequency on an ICU device.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \param freq_trim 		new frequency trim (fine code) to write to the device
 *
 * \param bias_trim 		new bias trim (coarse code) to write to the device
 *
 * \return PMUT operating frequency in Hz
 *
 * This static function must only be called after initialization (ie after calling ch_group_start()).
 */
/*!
 */
static uint32_t set_new_pmut_code(ch_dev_t *dev_ptr, uint16_t freq_trim, uint8_t bias_trim) {
	uint16_t pmut_trim_addr = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->common.clock.pmut_trim);  // PMUT trim
	uint16_t pmut_trim_val  = pmut_bias_trim_to_code(freq_trim, bias_trim);
	chdrv_write_word(dev_ptr, pmut_trim_addr, pmut_trim_val);
	/* Save PMUT trim value in case it needs to be reloaded later*/
	dev_ptr->pmut_trim = pmut_trim_val;
	/* Trigger event to apply settings */
	chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);
	return ch_common_measure_pmut_frequency(dev_ptr);
}

/*!
 * \brief Interpolate to estimate a frequency trim code that matches the desired operating period.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \param target_period_ns 		target operating period (1/operating frequency) in nanoseconds
 *
 * \param freq_trim_out 		the value at this address will contain the estimated frequency trim code
 *
 * \param freq_trim_min 		low value of frequency trim for interpolation
 *
 * \param freq_trim_max 		high value of frequency trim for interpolation
 *
 * \param bias_trim 		new bias trim (coarse code) to write to the device
 *
 * \return PMUT operating frequency in Hz
 *
 * This static function must only be called after initialization (ie after calling ch_group_start()).
 */
/*!
 */
static uint32_t interpolate_dco_code(ch_dev_t *dev_ptr, uint32_t target_period_ns, uint16_t *freq_trim_out,
                                     uint16_t freq_trim_min, uint16_t freq_trim_max, uint8_t bias_trim) {
	uint32_t freq             = 0;
	uint32_t dco_period_ns[2] = {0, 0};
	int32_t freq_trim_est     = freq_trim_min;

	// freq should never actually be zero, due to output validation in measure_pmut_frequency()
	freq = set_new_pmut_code(dev_ptr, freq_trim_min, bias_trim);  // max frequency == min period [ns]
	if (freq != 0) {
		dco_period_ns[0] = NSEC_PER_SEC / freq;
	}
	freq = set_new_pmut_code(dev_ptr, freq_trim_max, bias_trim);  // min frequency == max period [ns]
	if (freq != 0) {
		dco_period_ns[1] = NSEC_PER_SEC / freq;
	}

	int32_t zero_check = (int32_t)(dco_period_ns[1] - dco_period_ns[0]);  // avoid div by zero
	if (zero_check != 0) {
		freq_trim_est = (int32_t)freq_trim_min +
		                ((int32_t)target_period_ns - (int32_t)dco_period_ns[0]) *
		                        (int32_t)(freq_trim_max - freq_trim_min) / zero_check +
		                1;
	}
	if (freq_trim_est < 0) {  // catch underflow
		freq_trim_est = 0;
	}
	if (freq_trim_est > SCM_PMUT_CLK_FREQ_TRIM_BM) {
		freq_trim_est = SCM_PMUT_CLK_FREQ_TRIM_BM;
	}
	freq = set_new_pmut_code(dev_ptr, (uint16_t)freq_trim_est, bias_trim);

	CH_LOG_INFO("# %u, est=%u, dco0=%lu, dco1=%lu, dtarg=%lu, freq=%lu, ftarg= %lu", dev_ptr->io_index,
	            (uint16_t)freq_trim_est, dco_period_ns[0], dco_period_ns[1], target_period_ns, freq,
	            NSEC_PER_SEC / target_period_ns);

	*freq_trim_out = (uint16_t)freq_trim_est;

	return freq;
}

/*!
 * \brief Search a contiguous set of frequency trim codes for the closest code to a target frequency.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \param freq_trim_guess 		center of frequency trim code search window
 *
 * \param target_freq_hz 		the desired operating frequency in Hertz
 *
 * \param bias_trim 		new bias trim (coarse code) to write to the device
 *
 * \return PMUT operating frequency in Hz
 *
 * This static function must only be called after initialization (ie after calling ch_group_start()).
 */
/*!
 */
static uint32_t find_closest_frequency(ch_dev_t *dev_ptr, uint16_t freq_trim_guess, uint32_t target_freq_hz,
                                       uint8_t bias_trim) {
	int16_t i;
	int16_t idx_min_error = 0;
	uint32_t freq;
	int32_t min_frequency_err_hz;
	if (freq_trim_guess < (-ICU_FREQ_SEARCH_LOW)) {
		freq_trim_guess = (-ICU_FREQ_SEARCH_LOW);
	}
	if (freq_trim_guess > (SCM_PMUT_CLK_FREQ_TRIM_BM + ICU_FREQ_SEARCH_LOW)) {
		freq_trim_guess = SCM_PMUT_CLK_FREQ_TRIM_BM + ICU_FREQ_SEARCH_LOW;
	}
	min_frequency_err_hz = INT32_MAX;
	// look at the frequencies of the codes below and above the guess frequency and find the one
	// with the least error to the target frequency
	for (i = ICU_FREQ_SEARCH_LOW; i < ICU_FREQ_SEARCH_HIGH; i++) {
		freq = set_new_pmut_code(dev_ptr, (uint16_t)((int16_t)freq_trim_guess + i), bias_trim);
		if (min_frequency_err_hz > abs((int32_t)freq - (int32_t)target_freq_hz)) {
			min_frequency_err_hz = abs((int32_t)freq - (int32_t)target_freq_hz);
			idx_min_error        = i;

			CH_LOG_DEBUG("# *");
		}
		CH_LOG_DEBUG("# dcoest=%u, freq=%lu", (uint16_t)((int16_t)freq_trim_guess + i), freq);
	}
	freq_trim_guess = (uint16_t)((int16_t)freq_trim_guess + idx_min_error);
	freq            = set_new_pmut_code(dev_ptr, freq_trim_guess, bias_trim);
	return freq;
}

#endif

/*!
 * \brief Set the closest available operating frequency to a desired operating frequency.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \param op_frequency_hz 		the desired operating frequency in Hertz
 *
 * \return PMUT operating frequency in Hz
 */
/*!
 */
uint8_t ch_common_set_frequency(ch_dev_t *dev_ptr, uint32_t request_op_freq_hz) {
	uint8_t ret_val = RET_ERR;

	if (request_op_freq_hz == 0 || !dev_ptr || !(dev_ptr->sensor_connected)) {
		return ret_val;
	}

	uint32_t freq                  = 0;
	uint32_t pmut_clk_period_ns[2] = {0, 0};
	uint32_t target_freq_hz        = request_op_freq_hz;             // desired frequency
	uint32_t target_period_ns      = NSEC_PER_SEC / target_freq_hz;  //[ns]

	if (dev_ptr->part_number == CH101_PART_NUMBER) {
#ifdef INCLUDE_WHITNEY_SUPPORT
		uint16_t dco_code_estimate;
		int32_t min_frequency_err_hz;
		// initially, find two points on the DCO curve, which should be linear in period
		// increasing DCO code ~= increasing DCO period
		// freq should never actually be zero, due to output validation in measure_pmut_frequency()
		freq = set_new_dco_code(dev_ptr, CH101_DCO_LOW);
		if (freq != 0) {
			pmut_clk_period_ns[0] = NSEC_PER_SEC / freq;
		}
		freq = set_new_dco_code(dev_ptr, CH101_DCO_HIGH);
		if (freq != 0) {
			pmut_clk_period_ns[1] = NSEC_PER_SEC / freq;
		}

		// Now interpolate to estimate the DCO code
		int32_t zero_check = (int32_t)(pmut_clk_period_ns[1] - pmut_clk_period_ns[0]);
		if (zero_check != 0) {
			dco_code_estimate = (int32_t)CH101_DCO_LOW + ((int32_t)target_period_ns - (int32_t)pmut_clk_period_ns[0]) *
			                                                     (int32_t)(CH101_DCO_HIGH - CH101_DCO_LOW) / zero_check;

			freq = set_new_dco_code(dev_ptr, dco_code_estimate);
		} else {
			return ret_val;
		}

		CH_LOG_DEBUG("# Port %u, dco0=%lu, dco1=%lu, dco_code_estimate=%u, freq=%lu, targ= %lu", dev_ptr->io_index,
		             pmut_clk_period_ns[0], pmut_clk_period_ns[1], dco_code_estimate, freq, target_freq_hz);

		min_frequency_err_hz   = abs((int32_t)freq - (int32_t)target_freq_hz);
		uint32_t idx_min_error = 0;
		// if the error is too high, search around the estimate for the best code
		if (min_frequency_err_hz > CH101_DCO_SEARCH_THRESHOLD) {

			CH_LOG_INFO("# Frequency error above %dHz, searching for better match to %luHz", CH101_DCO_SEARCH_THRESHOLD,
			            target_freq_hz);

			int i;
			for (i = -5; i < 6; i++) {  //+/-5 DCO codes should be about +/-1500Hz
				freq = set_new_dco_code(dev_ptr, dco_code_estimate + i);
				if (abs((int32_t)freq - (int32_t)target_freq_hz) < min_frequency_err_hz) {
					min_frequency_err_hz = abs((int32_t)freq - (int32_t)target_freq_hz);
					idx_min_error        = i;

					CH_LOG_DEBUG("# *");
				}
				CH_LOG_DEBUG("# dco_code_estimate=%u, freq=%lu", dco_code_estimate + i, freq);
			}
			dco_code_estimate = dco_code_estimate + idx_min_error;
			freq              = set_new_dco_code(dev_ptr, dco_code_estimate);

			CH_LOG_DEBUG("# Final setting dco=%u, freq=%lu", dco_code_estimate, freq);
		}
		ret_val = RET_OK;
#endif  // INCLUDE_WHITNEY_SUPPORT

	} else if (dev_ptr->part_number != CH201_PART_NUMBER) {  // if the part is a ICU-x0201,
#ifdef INCLUDE_SHASTA_SUPPORT
		// initially, find two points on the DCO curve, which should be linear in period
		// increasing DCO code ~= increasing DCO period
		uint16_t freq_trim_max = SCM_PMUT_CLK_FREQ_TRIM_BM;
		uint16_t freq_trim_min = ICU_FREQ_TRIM_LOW;
		uint16_t freq_trim_out;
		uint8_t bias_trim;

		if (target_freq_hz < PMUT_CLK_BIAS_0_MAX_FREQ) {  // magic numbers based on frequency range of bias trims
			bias_trim     = 0;
			freq_trim_max = PMUT_CLK_FREQ_TRIM_MAX_BIAS_0;  // prevent going to super low frequency
		} else if (target_freq_hz < PMUT_CLK_BIAS_1_MAX_FREQ) {
			bias_trim     = 1;
			freq_trim_max = PMUT_CLK_FREQ_TRIM_MAX_BIAS_1;  // prevent going to super low frequency
		} else if (target_freq_hz < PMUT_CLK_BIAS_2_MAX_FREQ) {
			bias_trim = 2;
		} else {
			bias_trim = 3;
		}
		freq = interpolate_dco_code(dev_ptr, target_period_ns, &freq_trim_out, freq_trim_min, freq_trim_max, bias_trim);
		// freq should never actually be zero, due to output validation in measure_pmut_frequency()
		if (freq != 0) {
			pmut_clk_period_ns[0] = NSEC_PER_SEC / freq;
		}
		if (pmut_clk_period_ns[0] > target_period_ns) {
			freq_trim_max = freq_trim_out;
			freq_trim_min = freq_trim_out - 20;
		} else {
			freq_trim_min = freq_trim_out;
			freq_trim_max = freq_trim_out + 20;
		}
		if (freq_trim_min > SCM_PMUT_CLK_FREQ_TRIM_BM) {  // catch underflow
			freq_trim_min = 0;
		}
		if (freq_trim_max > SCM_PMUT_CLK_FREQ_TRIM_BM) {
			freq_trim_max = SCM_PMUT_CLK_FREQ_TRIM_BM;
		}
		freq = interpolate_dco_code(dev_ptr, target_period_ns, &freq_trim_out, freq_trim_min, freq_trim_max, bias_trim);
		// freq should never actually be zero, due to output validation in measure_pmut_frequency()
		if (freq != 0) {
			pmut_clk_period_ns[1] = NSEC_PER_SEC / freq;
		}
		freq = find_closest_frequency(dev_ptr, freq_trim_out, target_freq_hz, bias_trim);

		/* Adjust cpu frequency to avoid multiple of pmut freq */
		uint32_t cpu_freq = chdrv_cpu_freq_adjust(dev_ptr, freq);

		/* Store values in device descriptor */
		dev_ptr->cpu_frequency = cpu_freq;

		CH_LOG_INFO("freq_trim=%u, bias=%u freq=%lu", freq_trim_out, bias_trim, freq);
		ret_val = RET_OK;
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	return ret_val;
}

uint8_t ch_common_group_set_frequency(ch_group_t *grp_ptr, uint32_t request_op_freq_hz) {
	uint8_t ret_val = RET_OK;

#ifdef INCLUDE_WHITNEY_SUPPORT
	/* Every connected CHx01 device must support ch_set_frequency() */
	for (uint8_t dev_num = 0; dev_num < CHIRP_MAX_NUM_SENSORS; dev_num++) {
		ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
		if ((dev_ptr != NULL) && dev_ptr->sensor_connected) {

			if (dev_ptr->current_fw->api_funcs->set_frequency == NULL) {  // if no API support
				ret_val = RET_ERR;
			}
		}
	}
#endif  // INCLUDE_WHITNEY_SUPPORT

	/* Use average natural frequency, if no specific value given */
	if ((ret_val == RET_OK) && (request_op_freq_hz == CH_OP_FREQ_USE_AVG)) {
		uint32_t freq_total = 0;
		uint8_t num_devices = 0;

		for (uint8_t dev_num = 0; dev_num < CHIRP_MAX_NUM_SENSORS; dev_num++) {
			ch_dev_t *dev_ptr = grp_ptr->device[dev_num];
			if ((dev_ptr != NULL) && dev_ptr->sensor_connected) {
				freq_total += ch_get_frequency(dev_ptr);
				num_devices++;
			}
		}
		if (num_devices != 0) {
			request_op_freq_hz = (freq_total / num_devices);  // calculate average
		} else {
			ret_val = RET_ERR;
		}
	}

	/* Apply frequency to all sensors in group */
	for (uint8_t dev_num = 0; (ret_val == RET_OK) && (dev_num < CHIRP_MAX_NUM_SENSORS); dev_num++) {
		ch_dev_t *dev_ptr = grp_ptr->device[dev_num];

		if ((dev_ptr != NULL) && dev_ptr->sensor_connected) {
			ret_val = ch_set_frequency(dev_ptr, request_op_freq_hz);  // set freq using API entry point
		}
	}
	if (ret_val == RET_OK) {
		grp_ptr->op_frequency = request_op_freq_hz;  // store in group descriptor
	}
	return ret_val;
}

uint8_t ch_common_set_pmut_clock(ch_dev_t *dev_ptr, ch_pmut_clk_cfg_t clock_cfg) {
	uint8_t ret_val = RET_ERR;

#ifdef INCLUDE_SHASTA_SUPPORT
	if (dev_ptr->sensor_connected) {
		clock_control_t *clock_ctrl_ptr = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
		uint16_t control_reg_addr       = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->control);
		uint8_t old_control;
		uint8_t new_control;
		uint16_t pmut_trim_reg_addr = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->pmut_trim);
		uint16_t old_pmut_trim;
		uint16_t new_pmut_trim;

		/* Sensor is already initialized, read and modify current settings */
		ret_val = chdrv_read_byte(dev_ptr, control_reg_addr, &old_control);
		if (ret_val == RET_OK) {
			ret_val = chdrv_read_word(dev_ptr, pmut_trim_reg_addr, &old_pmut_trim);
		}

		if (ret_val == RET_OK) {
			/* Clear clock pad control & external input bits - same as CH_PMUT_CLK_DEFAULT */
			new_control   = old_control & ~CLK_CONTROL_PMUT_ON;
			new_pmut_trim = old_pmut_trim & ~(SCM_PMUT_CLK_PAD_MODE_BM | SCM_PMUT_CLK_EXT_EN);

			if (clock_cfg == CH_PMUT_CLK_OUTPUT_ENABLE || clock_cfg == CH_PMUT_CLK_OUTPUT_AUTO) {
				/* Enabling PMUT clock output */
				if (clock_cfg == CH_PMUT_CLK_OUTPUT_ENABLE) {
					new_control |= CLK_CONTROL_PMUT_ON;
				}
				new_pmut_trim |= SCM_PMUT_CLK_PAD_MODE_PMUT;  // enable pmut clock output on pad

				dev_ptr->group->pmut_clock_freq = (dev_ptr->op_frequency * CH_PMUT_TICKS_PER_CYCLE);
				// store this sensor's clock rate as master
			} else if (clock_cfg == CH_PMUT_CLK_SRC_EXTERNAL) {
				/* Enabling PMUT clock input from external source */
				if (dev_ptr->group->pmut_clock_freq != 0) {  // check that clock source is present
					new_pmut_trim         |= (SCM_PMUT_CLK_PAD_MODE_INPUT | SCM_PMUT_CLK_EXT_EN);
					dev_ptr->op_frequency  = (dev_ptr->group->pmut_clock_freq / CH_PMUT_TICKS_PER_CYCLE);
					// now using group pmut frequency

					/* Adjust cpu frequency to avoid multiple of new pmut freq */
					dev_ptr->cpu_frequency = chdrv_cpu_freq_adjust(dev_ptr, dev_ptr->op_frequency);

				} else {
					ret_val = RET_ERR;  // no other sensor has enabled clock output
				}

			} else if (clock_cfg == CH_PMUT_CLK_DEFAULT) {
				/* Setting/restoring default clock config */
				if (old_pmut_trim & CLK_CONTROL_PMUT_ON) {  // if this sensor was supplying the PMUT clock
					dev_ptr->group->pmut_clock_freq = 0;    // clear master clock freq for group
				}
				dev_ptr->op_frequency = dev_ptr->orig_pmut_freq;  // use original measured freq for this sensor
			}

			ret_val = chdrv_write_byte(dev_ptr, control_reg_addr, new_control);
			if (ret_val == RET_OK) {
				ret_val = chdrv_write_word(dev_ptr, pmut_trim_reg_addr, new_pmut_trim);
			}
		}

		if (ret_val == RET_OK) {
			/* Trigger event to apply settings */
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);
		}
	}  // end if (dev_ptr->sensor_connected)

	if (ret_val == RET_OK) {
		CH_LOG_INFO("Setting dev_ptr->pmut_clk_cfg to %x\n", clock_cfg);
		dev_ptr->pmut_clk_cfg = clock_cfg;  // save clock config in descriptor
	}

#else
	(void)dev_ptr;                       // unused
	(void)clock_cfg;
#endif  // INCLUDE_SHASTA_SUPPORT

	return ret_val;
}

uint32_t ch_common_samples_to_cycles(uint16_t num_samples, ch_odr_t odr) {
	uint32_t num_cycles = 0;

	num_cycles = num_samples << (CH_ODR_DEFAULT + (7 - odr));

#ifdef INCLUDE_WHITNEY_SUPPORT
	num_cycles /= CH_PMUT_TICKS_PER_CYCLE;  // CH101 & CH201 use PMUT cycles, not ticks
#endif

	return num_cycles;
}

uint16_t ch_common_cycles_to_samples(uint32_t num_cycles, ch_odr_t odr, bool include_s0) {
#ifdef INCLUDE_WHITNEY_SUPPORT
	num_cycles *= CH_PMUT_TICKS_PER_CYCLE;  // CH101 & CH201 use PMUT cycles, not ticks
	return num_cycles >> (CH_ODR_DEFAULT + (7 - odr));
#endif

	if (include_s0) {
		// compensate for 2 leading SMCLK cycles before sample 0, and include sample 0 in count.
		if (num_cycles < 2) {
			return 0;
		}
		return ((num_cycles - 2) >> (CH_ODR_DEFAULT + (7 - odr))) + 1;
	} else {
		return num_cycles >> (CH_ODR_DEFAULT + (7 - odr));
	}
}

uint32_t ch_common_usec_to_cycles(ch_dev_t *dev_ptr, uint32_t num_usec) {
	uint32_t num_cycles = 0;
	uint32_t op_freq    = dev_ptr->op_frequency;
	uint32_t cycles_per_pmut;  // "cycle" units per PMUT cycle

	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
#ifdef INCLUDE_SHASTA_SUPPORT
		cycles_per_pmut = SHASTA_SMCLK_CYCLES_PER_PMUT;  // Shasta uses SMCLK cycles
#else
		cycles_per_pmut = 0;  // return an error
#endif
	} else {
		cycles_per_pmut = 1;  // Whitney uses PMUT transducer cycles
	}

	num_cycles = (cycles_per_pmut * num_usec * (op_freq / 64)) / (1000000 / 64);

	return num_cycles;
}

uint32_t ch_common_cycles_to_usec(ch_dev_t *dev_ptr, uint32_t num_cycles) {
	uint32_t num_usec = 0;
	uint32_t op_freq  = dev_ptr->op_frequency;

	num_usec = (num_cycles * (1000000 / 64)) / (op_freq / 64);  // calculate as if PMUT cycles

	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {  // Shasta uses SMCLK cycles
#ifdef INCLUDE_SHASTA_SUPPORT
		num_usec /= SHASTA_SMCLK_CYCLES_PER_PMUT;
#else
		num_usec        = 0;  // return an error
#endif
	}

	return num_usec;
}

uint16_t ch_common_usec_to_ticks(const ch_dev_t *dev_ptr, uint32_t num_usec) {
	uint16_t rtc_ticks = 0;

	rtc_ticks = (uint16_t)((uint64_t)num_usec * dev_ptr->rtc_cal_result / dev_ptr->group->rtc_cal_pulse_ms / 1000);

	return rtc_ticks;
}

uint32_t ch_common_ticks_to_usec(const ch_dev_t *dev_ptr, uint16_t num_rtc_ticks) {
	uint32_t num_usec = 0;

	num_usec =
			(uint32_t)(((float)(num_rtc_ticks * dev_ptr->group->rtc_cal_pulse_ms) / dev_ptr->rtc_cal_result) * 1000.0);

	return num_usec;
}

uint8_t ch_common_watchdog_enable(ch_dev_t *dev_ptr) {
	uint8_t ret_val = RET_ERR;

	if ((dev_ptr->sensor_connected) && (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA)) {
#ifdef INCLUDE_SHASTA_SUPPORT
		clock_control_t *clock_ctrl_ptr = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
		uint16_t reg_addr               = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->control);
		uint16_t reg_value;

		reg_value = (CLK_CONTROL_PW_VAL | CLK_CONTROL_WDT_ON);  // watchdog enable + password bits
		ret_val   = chdrv_write_word(dev_ptr, reg_addr, reg_value);

		if (ret_val == RET_OK) {
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);
		}
#endif  // INCLUDE_SHASTA_SUPPORT
	}
	return ret_val;
}

uint8_t ch_common_watchdog_disable(ch_dev_t *dev_ptr) {
	uint8_t ret_val = RET_ERR;

	if ((dev_ptr->sensor_connected) && (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA)) {
#ifdef INCLUDE_SHASTA_SUPPORT
		clock_control_t *clock_ctrl_ptr = (clock_control_t *)&((dev_ptr->sens_cfg_addr)->common.clock);
		uint16_t reg_addr               = (uint16_t)(uintptr_t) & (clock_ctrl_ptr->control);
		uint16_t reg_value;

		reg_value = CLK_CONTROL_PW_VAL;  // password bits only - wd enable bit NOT set
		ret_val   = chdrv_write_word(dev_ptr, reg_addr, reg_value);

		if (ret_val == RET_OK) {
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_CLOCKS);
		}
#endif  // INCLUDE_WHITNEY_SUPPORT
	}
	return ret_val;
}

#ifdef INCLUDE_SHASTA_SUPPORT

uint8_t ch_common_meas_init_queue(ch_dev_t *dev_ptr) {
	uint8_t err = RET_OK;

	if (!dev_ptr) {
		return RET_ERR;
	}

	dev_ptr->meas_queue.meas_start   = CH_DEFAULT_MEAS_NUM;
	dev_ptr->meas_queue.meas_stop    = CH_DEFAULT_MEAS_NUM;
	dev_ptr->meas_queue.current_meas = CH_DEFAULT_MEAS_NUM;

	dev_ptr->meas_queue.intconfig = 0;
	if (dev_ptr->group->sensor_int_pin == 2) {
		dev_ptr->meas_queue.intconfig |= INTCONFIG_DR_INT2;
	}
	if (dev_ptr->tgt_int_filter == CH_TGT_INT_FILTER_ANY) {
		dev_ptr->meas_queue.intconfig |= INTCONFIG_ON_TARGET;
	}

	dev_ptr->meas_queue.trigsrc = 0;
	if (dev_ptr->trig_type == CH_TRIGGER_TYPE_HW) {
		if (dev_ptr->group->sensor_trig_pin == 1) {
			dev_ptr->meas_queue.trigsrc |= TRIGSRC_HWTRIGGER_INT1;
		} else if (dev_ptr->group->sensor_trig_pin == 2) {
			dev_ptr->meas_queue.trigsrc |= TRIGSRC_HWTRIGGER_INT2;
		}
	}

	for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
		err |= ch_common_meas_reset(dev_ptr, meas_num);
		if (err) {
			break;
		}
	}

	return err;
}

uint8_t ch_common_meas_import(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr) {
	uint8_t err = RET_OK;  // default is error return

	if (meas_queue_ptr != NULL) {
		/* Copy queue definition */
		memcpy((void *)&(dev_ptr->meas_queue), (void *)meas_queue_ptr, sizeof(measurement_queue_t));

		/* Set counts in dev descriptor for each measurement in queue */
		for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
			measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);

			ch_common_meas_update_counts(dev_ptr, meas_num, meas_ptr);
		}

		/* Update interrupt and trigger pin settings */
		dev_ptr->tgt_int_filter =
				(meas_queue_ptr->intconfig & INTCONFIG_ON_TARGET ? CH_TGT_INT_FILTER_ANY : CH_TGT_INT_FILTER_OFF);
		dev_ptr->group->sensor_int_pin  = (meas_queue_ptr->intconfig & INTCONFIG_DR_INT2 ? 2 : 1);
		dev_ptr->group->sensor_trig_pin = (meas_queue_ptr->trigsrc == TRIGSRC_HWTRIGGER_INT2 ? 2 : 1);

		/* Update measurement interval for MRQ0.if self-timed (freerunning) */
		if (meas_queue_ptr->trigsrc == TRIGSRC_RTC) {
			/* filter RTC raw measure period out of time hopping mask */
			uint16_t meas_period = get_rtc_measure_period(meas_queue_ptr->meas[CH_DEFAULT_MEAS_NUM].meas_period);
			uint32_t interval_ms = (uint32_t)meas_period * dev_ptr->group->rtc_cal_pulse_ms / dev_ptr->rtc_cal_result;
			dev_ptr->freerun_intvl_us = interval_ms * 1000;
		}
		/* Update sensor */
		err = ch_common_meas_write_config(dev_ptr);
	}

	if (algo_cfg_ptr != NULL) {
		/* Write measurement algorithm configuration directly to sensor */
		err |= ch_common_set_algo_config(dev_ptr, algo_cfg_ptr);
	}

	return err;
}

uint8_t ch_common_meas_reset(ch_dev_t *dev_ptr, uint8_t meas_num) {
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint8_t ret_val         = 0;

	meas_ptr->meas_period = 0;
	meas_ptr->odr         = CH_ODR_DEFAULT;

	// Init transceiver instructions
	for (int i = 0; i < INST_BUF_LENGTH; i++) {
		meas_ptr->trx_inst[i].cmd_config = 0;
		meas_ptr->trx_inst[i].length     = 0;
	}

	meas_ptr->trx_inst[0].cmd_config = PMUT_CMD_EOF;

	// Init counters
	dev_ptr->meas_num_segments[meas_num]   = 0;
	dev_ptr->meas_num_rx_samples[meas_num] = 0;

	return ret_val;
}

uint8_t ch_common_meas_init(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_config_t *meas_config_ptr) {
	measurement_queue_t *meas_q_ptr = (measurement_queue_t *)&(dev_ptr->meas_queue);
	measurement_t *meas_ptr         = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);

	uint8_t other_meas_num = (meas_num == 0 ? 1 : 0);  // assumes only 2 meas possible

	if (meas_config_ptr->mode == CH_MEAS_MODE_STANDBY) {  // if this meas will begin in standby mode (inactive)
		meas_q_ptr->meas_start = other_meas_num;          //   other meas must be active
		meas_q_ptr->meas_stop  = other_meas_num;
	} else {                                      // if this measurement will begin as active
		if (meas_q_ptr->meas_start > meas_num) {  //   adjust start and stop to include it
			meas_q_ptr->meas_start = meas_num;
		}
		if (meas_q_ptr->meas_stop < meas_num) {
			meas_q_ptr->meas_stop = meas_num;
		}
	}

	meas_q_ptr->current_meas = meas_q_ptr->meas_start;  // reset current meas to start

	meas_ptr->meas_period = meas_config_ptr->meas_period;
	meas_ptr->odr         = (uint8_t)meas_config_ptr->odr;

	return RET_OK;
}

uint8_t ch_common_meas_add_segment(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_segment_t *seg_ptr) {
	volatile measurement_t *meas_ptr = &(dev_ptr->meas_queue.meas[meas_num]);
	uint8_t seg_num                  = dev_ptr->meas_num_segments[meas_num];
	uint8_t err                      = 1;

	if (seg_num < INST_BUF_LENGTH - 1) {
		// Copy transceiver instruction
		meas_ptr->trx_inst[seg_num].cmd_config = seg_ptr->inst.cmd_config;
		meas_ptr->trx_inst[seg_num].length     = seg_ptr->inst.length;

		if (IS_INSTRUCTION_CMD_RX(meas_ptr->trx_inst[seg_num].cmd_config)) {
			dev_ptr->meas_num_rx_samples[meas_num] +=
					ch_common_cycles_to_samples(seg_ptr->inst.length, meas_ptr->odr, false);
		}

		// Mark end of instruction sequence, if any remaining slots
		seg_num++;
		if (seg_num < INST_BUF_LENGTH) {
			meas_ptr->trx_inst[seg_num].cmd_config = PMUT_CMD_EOF;
		}

		dev_ptr->meas_num_segments[meas_num]++;  // count one more active segment in this meas
		err = 0;
	}

	return err;
}

uint8_t ch_common_meas_insert_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *const inst_ptr,
                                          uint8_t index_to_insert) {
	uint8_t error = 1;

	if (dev_ptr && inst_ptr && (meas_num < CH_MEAS_MAX_MEAS)) {
		volatile measurement_t *meas_ptr = &(dev_ptr->meas_queue.meas[meas_num]);
		uint8_t curr_max_inst_num        = dev_ptr->meas_num_segments[meas_num];

		if (meas_ptr && (index_to_insert + 1 < INST_BUF_LENGTH) && (curr_max_inst_num + 1 < INST_BUF_LENGTH)) {

			// copy instructions, from index_to_insert to the end, one index to the right
			for (int i = dev_ptr->meas_num_segments[meas_num] + 1; i >= index_to_insert; --i) {
				meas_ptr->trx_inst[i] = meas_ptr->trx_inst[i - 1];
			}

			meas_ptr->trx_inst[index_to_insert].cmd_config = inst_ptr->inst.cmd_config;
			meas_ptr->trx_inst[index_to_insert].length     = inst_ptr->inst.length;

			dev_ptr->meas_num_segments[meas_num]++;  // count one more active instruction in this meas

			if (IS_INSTRUCTION_CMD_RX(meas_ptr->trx_inst[index_to_insert].cmd_config)) {
				dev_ptr->meas_num_rx_samples[meas_num] +=
						ch_common_cycles_to_samples(inst_ptr->inst.length, meas_ptr->odr, false);
			}
			error = 0;
		}
	}

	return error;
}

uint8_t ch_common_meas_remove_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t index_to_remove) {
	uint8_t error = 1;

	if (dev_ptr && (meas_num < CH_MEAS_MAX_MEAS)) {
		volatile measurement_t *meas_ptr = &(dev_ptr->meas_queue.meas[meas_num]);

		if (meas_ptr && dev_ptr->meas_num_segments[meas_num] != 0 && (index_to_remove < INST_BUF_LENGTH)) {
			if (IS_INSTRUCTION_CMD_RX(meas_ptr->trx_inst[index_to_remove].cmd_config)) {
				dev_ptr->meas_num_rx_samples[meas_num] -=
						ch_common_cycles_to_samples(meas_ptr->trx_inst[index_to_remove].length, meas_ptr->odr, false);
			}

			// copy instructions, from index_to_remove to the end, one index to the left
			for (int i = index_to_remove; i < (INST_BUF_LENGTH - index_to_remove - 1); ++i) {
				if (IS_INSTRUCTION_CMD_EOF(meas_ptr->trx_inst[i].cmd_config)) {
					break;
				}
				meas_ptr->trx_inst[i]                = meas_ptr->trx_inst[i + 1];
				meas_ptr->trx_inst[i + 1].cmd_config = 0;
				meas_ptr->trx_inst[i + 1].length     = 0;
			}

			dev_ptr->meas_num_segments[meas_num]--;  // count one less active instruction in this meas

			error = 0;
		}
	}

	return error;
}

uint8_t ch_common_meas_add_segment_count(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t int_enable) {
	ch_meas_segment_t meas_segment;
	uint8_t err = 0;

	ch_common_meas_init_segment_count(&meas_segment, num_cycles, int_enable);
	err = ch_meas_add_segment(dev_ptr, meas_num, &meas_segment);

	return err;
}

uint8_t ch_common_meas_add_segment_rx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples, uint8_t gain,
                                      uint8_t atten, uint8_t int_enable) {
	ch_meas_segment_t meas_segment;
	ch_odr_t odr = (ch_odr_t)dev_ptr->meas_queue.meas[meas_num].odr;
	uint8_t err  = 0;

	ch_common_meas_init_segment_rx(&meas_segment, num_samples, odr, gain, atten, int_enable);
	err = ch_meas_add_segment(dev_ptr, meas_num, &meas_segment);

	return err;
}

uint8_t ch_common_meas_add_segment_tx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t pulse_width,
                                      uint8_t phase, uint8_t int_enable) {
	ch_meas_segment_t meas_segment;
	uint8_t err = 0;

	ch_common_meas_init_segment_tx(&meas_segment, num_cycles, pulse_width, phase, int_enable);
	err = ch_meas_add_segment(dev_ptr, meas_num, &meas_segment);

	return err;
}

void ch_common_meas_init_segment_count(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t int_enable) {
	uint16_t cmd_config = PMUT_CMD_COUNT;

	if (int_enable) {
		cmd_config |= PMUT_DONE_IEN_BITS;  // enable interrupt when done
	}

	seg_ptr->inst.cmd_config = cmd_config;
	seg_ptr->inst.length     = num_cycles;
}

void ch_common_meas_init_segment_rx(ch_meas_segment_t *seg_ptr, uint16_t num_samples, ch_odr_t odr, uint8_t gain,
                                    uint8_t atten, uint8_t int_enable) {

	uint16_t cmd_config = (PMUT_CMD_RX | PMUT_RX_BIAS_EN_BITS);
	uint32_t num_cycles = ch_common_samples_to_cycles(num_samples, odr);

	if (num_cycles > UINT16_MAX) {
		num_cycles = UINT16_MAX;
	}

	if (int_enable) {
		cmd_config |= PMUT_DONE_IEN_BITS;  // enable interrupt when done
	}

	cmd_config |= ((gain & PMUT_RXGAIN_BM) << PMUT_RXGAIN_RED_BITSHIFT);  // add gain bits
	cmd_config |= ((atten & PMUT_RXATTEN_BM) << PMUT_RXATTEN_BITSHIFT);   // add attenuation bits

	seg_ptr->inst.cmd_config = cmd_config;
	seg_ptr->inst.length     = (uint16_t)num_cycles;
}

void ch_common_meas_init_segment_tx(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t pulse_width, uint8_t phase,
                                    uint8_t int_enable) {

	uint16_t cmd_config = (PMUT_CMD_TX | PMUT_RX_BIAS_EN_BITS);

	if (int_enable) {
		cmd_config |= PMUT_DONE_IEN_BITS;  // enable interrupt when done
	}

	cmd_config |= ((pulse_width & PMUT_TX_PW_BM) << PMUT_TX_PW_BITSHIFT);  // add pulse_width bits
	cmd_config |= ((phase & PMUT_TX_PHASE_BM) << PMUT_TX_PHASE_BITSHIFT);  // add phase bits

	seg_ptr->inst.cmd_config = cmd_config;
	seg_ptr->inst.length     = num_cycles;
}

uint8_t ch_common_write_data_validation_cfg(ch_dev_t *dev_ptr, uint8_t en_reg_val, int16_t seed) {
	uint8_t err = 0;

	uint16_t seed_addr = (uint16_t)(uintptr_t)&dev_ptr->sens_cfg_addr->common.reg_map_format.rsvd1;
	uint8_t seed_buf[2];
	seed_buf[0]  = seed & 0x00FF;
	seed_buf[1]  = (seed & 0xFF00) >> 8;
	err         |= chdrv_burst_write(dev_ptr, seed_addr, seed_buf, sizeof(seed_buf));

	uint16_t meas_queue_flags_addr = (uint16_t)(uintptr_t)&dev_ptr->sens_cfg_addr->meas_queue.reserved;
	err |= chdrv_burst_write(dev_ptr, meas_queue_flags_addr, &en_reg_val, sizeof(en_reg_val));

	return err;
}

uint8_t ch_common_meas_write_config(ch_dev_t *dev_ptr) {
	uint8_t err = 0;

	/* Write measurement queue values */
	err = chdrv_meas_queue_write(dev_ptr, NULL);

	/* Send event to apply settings (especially ODR) immediately */
	if (!err) {
		chdrv_event_trigger(dev_ptr, EVENT_PREPARE_MEAS);
	}

	/* Update measurement counts */
	if (!err) {
		for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
			measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);

			err |= ch_common_meas_update_counts(dev_ptr, meas_num, meas_ptr);
		}
	}

	return err;
}

// cache leading count instructions. remove them from q and store them in p
static void cache_leading_count_instructions(measurement_queue_t *q, pmut_transceiver_inst_t p[][32]) {
	for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
		uint8_t num_count_instructions = 0;
		for (uint8_t i = 0; i < INST_BUF_LENGTH; i++) {
			pmut_transceiver_inst_t pmut_inst = q->meas[meas_num].trx_inst[i];

			uint16_t pmut_cmd = (uint16_t)((pmut_inst.cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);
			if (pmut_cmd == PMUT_CMD_COUNT) {
				p[meas_num][i] = pmut_inst;
				num_count_instructions++;
			} else {
				break;
			}
		}
		CH_LOG_INFO("meas_num: %u, num_count_instructions: %u", meas_num, num_count_instructions);
		for (uint8_t i = 0; i < INST_BUF_LENGTH; i++) {
			if (i + num_count_instructions < INST_BUF_LENGTH) {
				q->meas[meas_num].trx_inst[i] = q->meas[meas_num].trx_inst[i + num_count_instructions];
			} else {
				q->meas[meas_num].trx_inst[i] = (pmut_transceiver_inst_t){.cmd_config = 0, .length = 0};
			}
		}
	}
}

// restore leading count instructions from p into q
static void restore_leading_count_instructions(measurement_queue_t *q, pmut_transceiver_inst_t p[][32]) {
	for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
		uint8_t num_count_instructions = 0;
		for (uint8_t i = 0; i < INST_BUF_LENGTH; i++) {
			pmut_transceiver_inst_t pmut_inst = p[meas_num][i];

			uint16_t pmut_cmd = (uint16_t)((pmut_inst.cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);
			if (pmut_cmd == PMUT_CMD_COUNT && pmut_inst.length > 0) {
				num_count_instructions++;
			} else {
				break;
			}
		}
		CH_LOG_INFO("meas_num: %u, num_count_instructions: %u", meas_num, num_count_instructions);
		for (uint8_t i = INST_BUF_LENGTH; i-- > 0;) {
			if (i >= num_count_instructions) {
				q->meas[meas_num].trx_inst[i] = q->meas[meas_num].trx_inst[i - num_count_instructions];
			} else {
				q->meas[meas_num].trx_inst[i] = p[meas_num][i];
			}
		}
	}
}

uint8_t ch_common_meas_optimize(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr) {
	uint8_t ret_val = RET_ERR;

	// must have init f/w that can perform optimization
	if ((dev_ptr->init_fw_info == NULL) || !dev_ptr->init_fw_info->fw_includes_tx_optimization) {
		return RET_ERR;
	}

	measurement_queue_t tx_opt_queue;  // meas queue after optimization
	pmut_transceiver_inst_t count_instructions[MEAS_QUEUE_MAX_MEAS][32] = {0};
	ch_group_t *grp_ptr                                                 = dev_ptr->group;

	if (grp_ptr->status == CH_GROUP_STAT_INIT_OK) {

		/* Import new meas queue and/or algo config if specified */
		if ((meas_queue_ptr != NULL) || (algo_cfg_ptr != NULL)) {
			ret_val = ch_common_meas_import(dev_ptr, meas_queue_ptr, algo_cfg_ptr);
		} else {
			ret_val = RET_OK;
		}
		cache_leading_count_instructions(&dev_ptr->meas_queue, count_instructions);

		/* Load init f/w to perform optimization */
		if (ret_val == RET_OK) {
			grp_ptr->status     = CH_GROUP_STAT_INIT_PENDING;  // re-init now pending
			dev_ptr->current_fw = dev_ptr->init_fw_info;
		}

		if (ret_val == RET_OK) {
			ret_val = chdrv_restart(dev_ptr);
		}

		/* Write measurement queue values */
		if (ret_val == RET_OK) {
			ret_val = chdrv_meas_queue_write(dev_ptr, NULL);
		}

		/* Trigger Tx optimize event on sensor */
		if (ret_val == RET_OK) {
			ret_val = chdrv_event_trigger_and_wait(dev_ptr, EVENT_TX_OPTIMIZE);
		}

		/* Read modified message queue */
		if (ret_val == RET_OK) {
			ret_val = chdrv_meas_queue_read(dev_ptr, &tx_opt_queue);
		}

		/* Extract optimized tx instructions and combine with existing meas queue segments */
		if (ret_val == RET_OK) {
			for (uint8_t meas_num = 0; meas_num < MEAS_QUEUE_MAX_MEAS; meas_num++) {
				uint16_t num_opt_tx_inst = 0;  // number of tx instructions after optimization
				uint16_t num_added;            // number of tx instructions added by opt

				for (uint8_t i = 0; i < INST_BUF_LENGTH; i++) {
					pmut_transceiver_inst_t pmut_inst = tx_opt_queue.meas[meas_num].trx_inst[i];

					uint16_t pmut_cmd = (uint16_t)((pmut_inst.cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);
					if (pmut_cmd == PMUT_CMD_TX) {
						num_opt_tx_inst++;  // count this tx instruction
					} else if (pmut_cmd == PMUT_CMD_EOF) {
						break;
					}
				}

				num_added = num_opt_tx_inst - dev_ptr->meas_num_tx_segments[meas_num];

				/* Shuffle old non-tx entries in queue to insert new set of tx instructions */
				for (uint8_t idx = INST_BUF_LENGTH - 1; (idx - num_added) > 0; idx--) {
					pmut_transceiver_inst_t *inst_ptr =
							(pmut_transceiver_inst_t *)&(dev_ptr->meas_queue.meas[meas_num].trx_inst);

					inst_ptr[idx] = inst_ptr[idx - num_added];
				}

				/* Copy optimized tx instructions into meas queue */
				for (uint8_t idx = 0; idx < num_opt_tx_inst; idx++) {
					pmut_transceiver_inst_t *inst_ptr =
							(pmut_transceiver_inst_t *)&(dev_ptr->meas_queue.meas[meas_num].trx_inst);
					pmut_transceiver_inst_t *opt_inst_ptr =
							(pmut_transceiver_inst_t *)&(tx_opt_queue.meas[meas_num].trx_inst);

					inst_ptr[idx] = opt_inst_ptr[idx];
				}
			}
			restore_leading_count_instructions(&dev_ptr->meas_queue, count_instructions);
		}  // end for (meas_num < MEAS_QUEUE_MAX_MEAS)

		/* Reload measurement f/w */
		if (ret_val == RET_OK) {
			dev_ptr->current_fw = dev_ptr->main_fw_info;
			ret_val             = chdrv_restart(dev_ptr);
		}

		/* Write new meas queue definition */
		if (ret_val == RET_OK) {
			grp_ptr->status = CH_GROUP_STAT_INIT_OK;  // indicate sensor (re-)init'd

			/* Write meas queue to device */
			ret_val = ch_common_meas_write_config(dev_ptr);

			/* Apply trigger pin selection */
			ret_val |= chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);
		}

	}  // end if (grp_ptr->status == CH_GROUP_STAT_INIT_OK)

	return ret_val;
}

void ch_common_meas_activate(ch_dev_t *dev_ptr, uint8_t meas_num) {
	measurement_queue_t *meas_q_ptr = (measurement_queue_t *)&(dev_ptr->meas_queue);

	if (meas_q_ptr->meas_start > meas_num) {  //  adjust start and stop to include this
		meas_q_ptr->meas_start = meas_num;
	}
	if (meas_q_ptr->meas_stop < meas_num) {
		meas_q_ptr->meas_stop = meas_num;
	}

	meas_q_ptr->current_meas = meas_num;  // this will be the next meas to run

	ch_common_meas_write_config(dev_ptr);  // write meas queue to device
}

void ch_common_meas_standby(ch_dev_t *dev_ptr, uint8_t meas_num) {
	measurement_queue_t *meas_q_ptr = (measurement_queue_t *)&(dev_ptr->meas_queue);
	uint8_t other_meas_num          = (meas_num == 0 ? 1 : 0);  // assumes only 2 meas possible

	meas_q_ptr->meas_start   = other_meas_num;  //   make other meas active
	meas_q_ptr->meas_stop    = other_meas_num;
	meas_q_ptr->current_meas = other_meas_num;

	ch_common_meas_write_config(dev_ptr);  // write meas queue to device
}

uint8_t ch_common_meas_switch(ch_dev_t *dev_ptr) {
	measurement_queue_t *meas_q_ptr = (measurement_queue_t *)&(dev_ptr->meas_queue);
	uint8_t new_meas_num            = (meas_q_ptr->current_meas == 0 ? 1 : 0);  // assumes only 2 meas possible

	ch_common_meas_standby(dev_ptr, meas_q_ptr->current_meas);  // force current meas into standby

	return new_meas_num;
}

uint8_t ch_common_meas_get_last_num(ch_dev_t *dev_ptr) {

	return dev_ptr->last_measurement;
}

void ch_common_meas_get_info(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_info_t *info_ptr) {
	measurement_queue_t *meas_q_ptr = &(dev_ptr->meas_queue);
	measurement_t *meas_ptr         = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);

	memset((void *)info_ptr, 0, sizeof(ch_meas_info_t));  // init info struct

	if ((meas_num >= meas_q_ptr->meas_start) && (meas_num <= meas_q_ptr->meas_stop)) {
		info_ptr->mode = CH_MEAS_MODE_ACTIVE;
	} else {
		info_ptr->mode = CH_MEAS_MODE_STANDBY;
	}

	info_ptr->num_segments    = dev_ptr->meas_num_segments[meas_num];  // values maintained by SonicLib
	info_ptr->num_tx_segments = dev_ptr->meas_num_tx_segments[meas_num];
	info_ptr->num_rx_samples  = dev_ptr->meas_num_rx_samples[meas_num];
	info_ptr->num_cycles      = dev_ptr->meas_num_cycles[meas_num];

	info_ptr->meas_period = meas_ptr->meas_period;  // copies of values on sensor
	info_ptr->odr         = (ch_odr_t)meas_ptr->odr;
}

void ch_common_inst_get_seg_info(pmut_transceiver_inst_t *inst_ptr, uint8_t odr, ch_meas_seg_info_t *info_ptr) {
	uint16_t cmd_config = inst_ptr->cmd_config;
	ch_meas_seg_type_t seg_type;

	memset((void *)info_ptr, 0, sizeof(ch_meas_seg_info_t));  // init info struct

	seg_type = (ch_meas_seg_type_t)((cmd_config >> PMUT_CMD_BITSHIFT) &
	                                PMUT_CMD_BITS);  // same values as ch_meas_seg_type_t

	info_ptr->type       = seg_type;
	info_ptr->num_cycles = inst_ptr->length;

	info_ptr->rdy_int_en  = ((cmd_config & PMUT_RDY_IEN_BITS) != 0);
	info_ptr->done_int_en = ((cmd_config & PMUT_DONE_IEN_BITS) != 0);

	if (seg_type == CH_MEAS_SEG_TYPE_TX) {
		info_ptr->tx_phase       = ((cmd_config >> PMUT_TX_PHASE_BITSHIFT) & PMUT_TX_PHASE_BM);
		info_ptr->tx_pulse_width = ((cmd_config >> PMUT_TX_PW_BITSHIFT) & PMUT_TX_PW_BM);
	} else if (seg_type == CH_MEAS_SEG_TYPE_RX) {
		info_ptr->num_rx_samples = ch_common_cycles_to_samples(info_ptr->num_cycles, odr, false);
		info_ptr->rx_gain        = ((cmd_config >> PMUT_RXGAIN_RED_BITSHIFT) & PMUT_RXGAIN_BM);
		info_ptr->rx_atten       = ((cmd_config >> PMUT_RXATTEN_BITSHIFT) & PMUT_RXATTEN_BM);
	}
}

void ch_common_meas_get_seg_info(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t seg_num, ch_meas_seg_info_t *info_ptr) {
	pmut_transceiver_inst_t *inst_ptr =
			(pmut_transceiver_inst_t *)&(dev_ptr->meas_queue.meas[meas_num].trx_inst[seg_num]);
	ch_odr_t odr = (ch_odr_t)dev_ptr->meas_queue.meas[meas_num].odr;
	ch_common_inst_get_seg_info(inst_ptr, odr, info_ptr);
}

void ch_common_meas_get_queue_info(ch_dev_t *dev_ptr, ch_meas_queue_info_t *info_ptr) {
	measurement_queue_t *meas_q_ptr = &(dev_ptr->meas_queue);

	memset((void *)info_ptr, 0, sizeof(ch_meas_queue_info_t));  // init info struct

	info_ptr->int_config   = meas_q_ptr->intconfig;
	info_ptr->meas_start   = meas_q_ptr->meas_start;
	info_ptr->meas_stop    = meas_q_ptr->meas_stop;
	info_ptr->current_meas = meas_q_ptr->current_meas;
	info_ptr->trig_src     = meas_q_ptr->trigsrc;
	info_ptr->last_meas    = ch_common_meas_get_last_num(dev_ptr);
}

uint8_t ch_common_meas_update_counts(ch_dev_t *dev_ptr, uint8_t meas_num, measurement_t *meas_ptr) {
	pmut_transceiver_inst_t *trx_inst_ptr =
			(pmut_transceiver_inst_t *)&(meas_ptr->trx_inst[0]);  // first instruction in meas
	uint16_t total_cycles        = 0;
	uint16_t total_rx_samples    = 0;
	uint8_t total_segments       = 0;
	uint16_t pre_rx_cycles       = 0;
	uint16_t pre_rx_cycles_no_tx = 0;  // COUNT cycles when no TX
	uint8_t num_rx_segments      = 0;
	uint16_t max_range_mm        = 0;
	uint8_t err                  = 0;
	uint16_t total_tx_segments   = 0;  // # of tx instructions
	uint32_t total_rx_cycles     = 0;

	dev_ptr->meas_num_segments[meas_num]   = 0;
	dev_ptr->meas_num_rx_samples[meas_num] = 0;

	uint16_t num_inst = 0;  // # of instructions
	/* Examine instructions until EOF marker */
	while (trx_inst_ptr->cmd_config != PMUT_CMD_EOF) {
		ch_meas_seg_type_t seg_type =
				(ch_meas_seg_type_t)((trx_inst_ptr->cmd_config >> PMUT_CMD_BITSHIFT) & PMUT_CMD_BITS);
		// use instruction as segment type
		if (num_inst++ >= INST_BUF_LENGTH) {
			err = 1;  // error - no EOF marker before end of instructions
			break;
		}

		total_cycles += trx_inst_ptr->length;

		total_segments++;  // each instruction = 1 segment

		if (seg_type == CH_MEAS_SEG_TYPE_RX) {
			total_rx_cycles += trx_inst_ptr->length;
			num_rx_segments++;

			if (total_tx_segments == 0) {
				pre_rx_cycles = pre_rx_cycles_no_tx;
			}
		} else if (seg_type == CH_MEAS_SEG_TYPE_TX) {
			if (num_rx_segments == 0) {
				pre_rx_cycles       += trx_inst_ptr->length;
				pre_rx_cycles_no_tx  = 0;
			}
			total_tx_segments++;
		} else if (seg_type == CH_MEAS_SEG_TYPE_COUNT) {
			if (total_tx_segments > 0) {
				pre_rx_cycles += trx_inst_ptr->length;
			} else {
				pre_rx_cycles_no_tx += trx_inst_ptr->length;
			}
		}

		trx_inst_ptr++;  // next instruction

	}  // end while (trx_inst_ptr->cmd_config != PMUT_CMD_EOF)

	total_rx_samples = ch_common_cycles_to_samples(total_rx_cycles, meas_ptr->odr, true);

	if (!err) {
		dev_ptr->meas_num_cycles[meas_num]      = total_cycles;
		dev_ptr->meas_num_tx_segments[meas_num] = total_tx_segments;
		dev_ptr->meas_num_rx_samples[meas_num]  = total_rx_samples;
		dev_ptr->meas_num_segments[meas_num]    = total_segments;
		dev_ptr->meas_pre_rx_cycles[meas_num]   = pre_rx_cycles;

		max_range_mm                         = ch_common_meas_samples_to_mm(dev_ptr, meas_num, total_rx_samples);
		dev_ptr->meas_max_range_mm[meas_num] = max_range_mm;  // store corresponding range in mm

		/* Fill in ch_dev_t fields for compatibility with simple SonicLib v2 API calls (use default meas) */
		if (meas_num == CH_DEFAULT_MEAS_NUM) {
			dev_ptr->num_rx_samples = total_rx_samples;
			dev_ptr->max_range      = max_range_mm;
		}
	}

	return err;
}

uint8_t ch_common_meas_set_interval(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t interval_ms) {
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint32_t rtc_ticks;
	uint8_t ret_val = RET_ERR;

	rtc_ticks = ((uint32_t)interval_ms * dev_ptr->rtc_cal_result) / dev_ptr->group->rtc_cal_pulse_ms;

	meas_ptr->meas_period = update_rtc_measure_period(meas_ptr->meas_period, rtc_ticks);

	ret_val = ch_common_meas_write_config(dev_ptr);

	if ((ret_val == RET_OK) && (meas_num == CH_DEFAULT_MEAS_NUM)) {
		dev_ptr->freerun_intvl_us = (interval_ms * 1000);  // default measurement gets interval in dev descriptor
	}

	return ret_val;
}

uint8_t ch_common_meas_set_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t interval_us) {
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint32_t rtc_ticks;
	uint8_t ret_val = RET_ERR;

	rtc_ticks = (interval_us * dev_ptr->rtc_cal_result) / (dev_ptr->group->rtc_cal_pulse_ms * 1000);

	meas_ptr->meas_period = update_rtc_measure_period(meas_ptr->meas_period, rtc_ticks);

	ret_val = ch_common_meas_write_config(dev_ptr);

	if ((ret_val == RET_OK) && (meas_num == CH_DEFAULT_MEAS_NUM)) {
		dev_ptr->freerun_intvl_us = interval_us;  // default measurement gets interval in dev descriptor
	}

	return ret_val;
}

uint8_t ch_common_meas_set_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t rtc_ticks) {
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint8_t ret_val         = RET_ERR;

	meas_ptr->meas_period = update_rtc_measure_period(meas_ptr->meas_period, rtc_ticks);

	ret_val = ch_common_meas_write_config(dev_ptr);

	if ((ret_val == RET_OK) && (meas_num == CH_DEFAULT_MEAS_NUM)) {
		dev_ptr->freerun_intvl_us = ch_common_ticks_to_usec(dev_ptr, rtc_ticks);
		// default measurement gets interval in dev descriptor
	}

	return ret_val;
}

uint16_t ch_common_meas_get_interval(ch_dev_t *dev_ptr, uint8_t meas_num) {
	uint32_t rtc_ticks = (uint32_t)get_rtc_measure_period(dev_ptr->meas_queue.meas[meas_num].meas_period);
	uint16_t num_ms;

	num_ms = (uint16_t)((rtc_ticks * dev_ptr->group->rtc_cal_pulse_ms) / dev_ptr->rtc_cal_result);

	return num_ms;
}

uint32_t ch_common_meas_get_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num) {
	uint32_t rtc_ticks = (uint32_t)get_rtc_measure_period(dev_ptr->meas_queue.meas[meas_num].meas_period);

	return ch_common_ticks_to_usec(dev_ptr, rtc_ticks);
}

uint32_t ch_common_meas_get_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return (uint32_t)get_rtc_measure_period(dev_ptr->meas_queue.meas[meas_num].meas_period);
}

uint8_t ch_common_meas_set_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t odr) {
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint8_t err             = RET_ERR;

	meas_ptr->odr = (uint8_t)odr;  // set new ODR

	err = ch_common_meas_write_config(dev_ptr);  // write to sensor

	return err;
}

ch_odr_t ch_common_meas_get_odr(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return dev_ptr->meas_queue.meas[meas_num].odr;
}

uint8_t ch_common_meas_set_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {
	uint8_t ret_val         = 1;  // default is error (not connected or num_samples too big)
	measurement_t *meas_ptr = (measurement_t *)&(dev_ptr->meas_queue.meas[meas_num]);
	uint8_t last_seg_num    = (dev_ptr->meas_num_segments[meas_num] - 1);  // get index of last active segment
	ch_odr_t odr            = (ch_odr_t)meas_ptr->odr;
	uint16_t max_range_mm   = 0;

	if (!dev_ptr->sensor_connected || num_samples > dev_ptr->current_fw->max_samples) {
		return 1;
	}

	if (num_samples > dev_ptr->num_rx_samples) {
		/* New sample count is greater - extend last measurement segment */
		uint16_t added_samples = (num_samples - dev_ptr->num_rx_samples);
		uint16_t added_cycles  = ch_common_samples_to_cycles(added_samples, odr);

		meas_ptr->trx_inst[last_seg_num].length += added_cycles;

		dev_ptr->num_rx_samples                += added_samples;
		dev_ptr->meas_num_rx_samples[meas_num] += added_samples;

	} else if (num_samples < dev_ptr->meas_num_rx_samples[meas_num]) {
		/* New sample count is less - shorten or eliminate last measurement segment(s) */
		uint16_t deleted_samples     = (dev_ptr->meas_num_rx_samples[meas_num] - num_samples);
		uint16_t deleted_cycles      = ch_common_samples_to_cycles(deleted_samples, odr);
		uint16_t deleted_cycles_left = deleted_cycles;

		while (deleted_cycles_left > 0) {
			if (meas_ptr->trx_inst[last_seg_num].length > deleted_cycles_left) {
				/* new end will be in this segment */
				meas_ptr->trx_inst[last_seg_num].length -= deleted_cycles_left;
				deleted_cycles_left                      = 0;
			} else {
				/* need to delete last segment and move to previous */
				deleted_cycles_left -= meas_ptr->trx_inst[last_seg_num].length;

				meas_ptr->trx_inst[last_seg_num].cmd_config = PMUT_CMD_EOF;

				last_seg_num--;
				(dev_ptr->meas_num_segments[meas_num])--;  // one less active segment
			}
		}

		dev_ptr->meas_num_rx_samples[meas_num] -= deleted_samples;
	}

	max_range_mm                         = ch_common_meas_samples_to_mm(dev_ptr, meas_num, num_samples);
	dev_ptr->meas_max_range_mm[meas_num] = max_range_mm;

	if (meas_num == CH_DEFAULT_MEAS_NUM) {
		dev_ptr->num_rx_samples = num_samples;
		dev_ptr->max_range      = max_range_mm;
	}

	/* Write to sensor */
	ret_val = ch_meas_write_config(dev_ptr);

	return ret_val;
}

uint16_t ch_common_meas_get_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num) {

	return dev_ptr->meas_num_rx_samples[meas_num];
}

uint8_t ch_common_meas_set_max_range(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t max_range_mm) {
	uint8_t ret_val;
	uint32_t num_samples;

	ret_val = (!dev_ptr->sensor_connected);

	if (!ret_val) {
		num_samples = ch_common_meas_mm_to_samples(dev_ptr, meas_num, max_range_mm);

		if (num_samples > dev_ptr->current_fw->max_samples) {
			num_samples                          = dev_ptr->current_fw->max_samples;
			dev_ptr->meas_max_range_mm[meas_num] = ch_common_meas_samples_to_mm(dev_ptr, meas_num, num_samples);
			// store reduced max range
		} else {
			dev_ptr->meas_max_range_mm[meas_num] = max_range_mm;  // store user-specified max range
		}

		if (meas_num == CH_DEFAULT_MEAS_NUM) {
			dev_ptr->max_range = dev_ptr->meas_max_range_mm[meas_num];
		}

		CH_LOG_DEBUG("num_samples=%lu", num_samples);
	}

	if (!ret_val) {
		ret_val = ch_meas_set_num_samples(dev_ptr, meas_num, num_samples);
	}

	CH_LOG_INFO("ret_val: %u  meas_num: %u dev_ptr->meas_num_rx_samples: %u", ret_val, meas_num,
	            dev_ptr->meas_num_rx_samples[meas_num]);

	return ret_val;
}

uint16_t ch_common_meas_mm_to_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_mm) {
	uint8_t this_odr     = ch_common_meas_get_odr(dev_ptr, meas_num);             // this meas odr
	uint8_t default_odr  = ch_common_meas_get_odr(dev_ptr, CH_DEFAULT_MEAS_NUM);  // default meas odr
	uint16_t num_samples = 0;

	if (meas_num != CH_DEFAULT_MEAS_NUM) {
		/* ch_common_mm_to_samples() always uses the default measurement's ODR, so, we temporarily
		 * change the stored ODR value for the default measurement in ch_dev_t and restore when done.
		 * Do not use ch_common_meas_set_odr() due to side effects.
		 */
		dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].odr = this_odr;  // set to this meas ODR
	}

	num_samples = ch_common_mm_to_samples(dev_ptr, num_mm);  // call std function

	dev_ptr->meas_queue.meas[CH_DEFAULT_MEAS_NUM].odr = default_odr;  // always restore

	return num_samples;
}

uint16_t ch_common_meas_samples_to_mm(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples) {
	uint16_t num_mm  = 0;
	uint32_t op_freq = dev_ptr->op_frequency;
	ch_odr_t odr     = ch_common_meas_get_odr(dev_ptr, meas_num);

	if (op_freq != 0) {
		num_mm = (((uint32_t)num_samples * CH_SPEEDOFSOUND_MPS * 1000) << (7 - odr)) / (op_freq * 2);
	}

	return num_mm;
}

uint8_t ch_common_read_meas_config(ch_dev_t *dev_ptr) {
	uint8_t err = 0;

	uint8_t last_measurement      = 0;
	uint8_t odr_out               = 0;
	uint8_t iq_output_format      = 0;
	uint16_t num_iq_bytes         = 0;
	uint16_t last_measurement_reg = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.last_measurement);
	uint16_t odr_out_reg          = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.odr_out);
	uint16_t iq_output_format_reg = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.iq_output_format);
	uint16_t num_iq_bytes_reg     = (uint16_t)(uintptr_t) & ((dev_ptr->sens_cfg_addr)->raw.num_iq_bytes);

	err  = chdrv_read_byte(dev_ptr, last_measurement_reg, &last_measurement);
	err |= chdrv_read_byte(dev_ptr, odr_out_reg, &odr_out);
	err |= chdrv_read_byte(dev_ptr, iq_output_format_reg, &iq_output_format);
	err |= chdrv_read_word(dev_ptr, num_iq_bytes_reg, &num_iq_bytes);

	if (!err) {
		dev_ptr->last_measurement = last_measurement & ~LAST_MEASUREMENT_CONTINUOUS;
		dev_ptr->is_continuous    = (last_measurement & LAST_MEASUREMENT_CONTINUOUS) > 0;
		dev_ptr->odr_out          = odr_out;
		dev_ptr->iq_output_format = iq_output_format;
		dev_ptr->num_iq_bytes     = num_iq_bytes;
		err                       = chdrv_read_buf_addr(dev_ptr);
	}

	return err;
}

uint8_t ch_common_set_target_interrupt(ch_dev_t *dev_ptr, ch_tgt_int_filter_t tgt_filter_mode) {
	int ret_val = RET_OK;

	if (tgt_filter_mode == CH_TGT_INT_FILTER_ANY) {
		dev_ptr->meas_queue.intconfig |= INTCONFIG_ON_TARGET;
	} else if (tgt_filter_mode == CH_TGT_INT_FILTER_OFF) {
		dev_ptr->meas_queue.intconfig &= ~INTCONFIG_ON_TARGET;
	} else {
		ret_val = RET_ERR;  // no Shasta target int counter support yet
	}

	if (ret_val == RET_OK) {
		dev_ptr->tgt_int_filter = tgt_filter_mode;  // save tgt_int_mode state
		ret_val                 = ch_common_meas_write_config(dev_ptr);
	}

	return ret_val;
}

ch_tgt_int_filter_t ch_common_get_target_interrupt(ch_dev_t *dev_ptr) {

	return dev_ptr->tgt_int_filter;
}

uint8_t ch_common_set_interrupt_mode(ch_dev_t *dev_ptr, ch_interrupt_mode_t mode) {
	int ret_val = RET_ERR;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
		if (mode == CH_INTERRUPT_MODE_PULSE) {
			dev_ptr->meas_queue.intconfig |= INTCONFIG_PULSE_INT;
		} else {
			dev_ptr->meas_queue.intconfig &= ~INTCONFIG_PULSE_INT;
		}

		/* Write to sensor */
		ret_val = ch_common_meas_write_config(dev_ptr);
		if (ret_val == RET_OK) {
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);
		}
	} else {                                    // CH_ASIC_GEN_1_WHITNEY (CH101 & CH201)
		if (mode == CH_INTERRUPT_MODE_PULSE) {  // ok because always enabled
			ret_val = RET_OK;
		}
	}

	if (ret_val != RET_ERR) {
		dev_ptr->int_mode = mode;  // save mode state
	}

	return ret_val;
}

ch_interrupt_mode_t ch_common_get_interrupt_mode(ch_dev_t *dev_ptr) {

	return dev_ptr->int_mode;
}

uint8_t ch_common_set_interrupt_drive(ch_dev_t *dev_ptr, ch_interrupt_drive_t mode) {
	int ret_val = RET_ERR;

	if (dev_ptr->asic_gen == CH_ASIC_GEN_2_SHASTA) {
		if (mode == CH_INTERRUPT_DRIVE_PUSH_PULL) {
			dev_ptr->meas_queue.intconfig |= INTCONFIG_PUSH_PULL_INT;
		} else {
			dev_ptr->meas_queue.intconfig &= ~INTCONFIG_PUSH_PULL_INT;
		}

		/* Write to sensor */
		ret_val = ch_common_meas_write_config(dev_ptr);
		if (ret_val == RET_OK) {
			chdrv_event_trigger(dev_ptr, EVENT_CONFIG_TRIGGER);
		}
	} else {                                          // CH_ASIC_GEN_1_WHITNEY (CH101 & CH201)
		if (mode == CH_INTERRUPT_DRIVE_OPEN_DRAIN) {  // ok because always enabled
			ret_val = RET_OK;
		}
	}

	if (ret_val != RET_ERR) {
		dev_ptr->int_drive = mode;  // save drive state
	}

	return ret_val;
}

ch_interrupt_drive_t ch_common_get_interrupt_drive(ch_dev_t *dev_ptr) {

	return dev_ptr->int_drive;
}

uint8_t ch_common_init_algo(ch_dev_t *dev_ptr) {
	uint8_t ret_val = RET_ERR;

	ret_val = chdrv_algo_init(dev_ptr);

	return ret_val;
}

uint8_t ch_common_get_algo_info(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr) {
	uint8_t ret_val = RET_ERR;

	if (algo_info_ptr != NULL) {
		ret_val = chdrv_algo_info_read(dev_ptr, algo_info_ptr);
	}
	return ret_val;
}

uint8_t ch_common_get_algo_config(ch_dev_t *dev_ptr, void *algo_cfg_ptr) {
	uint8_t ret_val = RET_ERR;

	if (algo_cfg_ptr != NULL) {
		ret_val = chdrv_algo_cfg_read(dev_ptr, algo_cfg_ptr);
	}
	return ret_val;
}

uint8_t ch_common_set_algo_config(ch_dev_t *dev_ptr, const void *algo_cfg_ptr) {
	uint8_t ret_val = RET_ERR;

	if (algo_cfg_ptr != NULL) {
		ret_val = chdrv_algo_cfg_write(dev_ptr, algo_cfg_ptr);
	}
	return ret_val;
}

uint8_t ch_common_get_algo_output(ch_dev_t *dev_ptr, void *algo_out_ptr) {
	uint8_t ret_val = RET_ERR;

	if (algo_out_ptr != NULL) {
		ret_val = chdrv_algo_out_read(dev_ptr, algo_out_ptr);
	}
	return ret_val;
}

uint8_t ch_common_get_algo_state(ch_dev_t *dev_ptr, void *algo_state_ptr) {
	uint8_t ret_val = RET_ERR;

	if (algo_state_ptr != NULL) {
		ret_val = chdrv_algo_state_read(dev_ptr, algo_state_ptr);
	}
	return ret_val;
}

uint8_t ch_common_get_mfg_info(ch_dev_t *dev_ptr, ch_mfg_info_t *info_ptr) {
	otp_copy_t otp;
	uint8_t ret_val = RET_OK;

	ret_val = chdrv_otpmem_copy(dev_ptr, &otp);

	if (ret_val == RET_OK) {
		info_ptr->mfg_year = otp.serial.year_since_2000;
		if (info_ptr->mfg_year != 0) {
			info_ptr->mfg_year += 2000;
		}
		info_ptr->mfg_week = otp.serial.work_week;
		info_ptr->mfg_site = otp.serial.production_site;

		info_ptr->product_code = otp.product_variant;
		info_ptr->package_code = otp.package_variant;
		info_ptr->mems_code    = otp.mems_variant;
		info_ptr->module_code  = otp.module_variant;
	}

	return ret_val;
}

#endif
