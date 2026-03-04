/*! \file ch_common.h
 *
 * \brief Internal driver functions for operation with the Chirp ultrasonic sensor.
 *
 * This file contains common implementations of sensor support routines.  These are
 * suitable for use with most standard sensor firmware images.  The firmware-specific
 * init function will set up various function pointers to either the common implementations
 * in this file, or corresponding firmware-specific implementations.
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

#ifndef CH_COMMON_H_
#define CH_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <invn/soniclib/soniclib.h>
#ifdef INCLUDE_WHITNEY_SUPPORT
#include <invn/soniclib/sensor_fw/ch101/ch101.h>
#include <invn/soniclib/sensor_fw/ch201/ch201.h>
#endif

/* All sensor common definitions */
#define CH_COMMON_RTC_CAL_PULSE_MS 100  // typical (default) rtc calibration pulse, in ms

#ifdef INCLUDE_WHITNEY_SUPPORT

/* CH-x01 common definitions */
#define CHX01_SCALEFACTOR_INDEX 4  // sample of BIST data for scale factor calc
#define CHX01_BANDWIDTH_INDEX_1 6  // first sample of BIST data for b/w calc
#define CHX01_BANDWIDTH_INDEX_2 7  // second sample of BIST data for b/w calc

#if (CH101_DATA_MEM_SIZE == CH201_DATA_MEM_SIZE)  // make sure CH101 and CH201 are the same
#define CHX01_DATA_MEM_SIZE CH101_DATA_MEM_SIZE   // data memory size
#endif
#if (CH101_DATA_MEM_ADDR == CH201_DATA_MEM_ADDR)
#define CHX01_DATA_MEM_ADDR CH101_DATA_MEM_ADDR  // data memory address
#endif
#if (CH101_PROG_MEM_SIZE == CH201_PROG_MEM_SIZE)
#define CHX01_PROG_MEM_SIZE CH101_PROG_MEM_SIZE  // program memory size
#endif
#if (CH101_PROG_MEM_ADDR == CH201_PROG_MEM_ADDR)
#define CHX01_PROG_MEM_ADDR CH101_PROG_MEM_ADDR  // program memory address
#endif
#if (CH101_FW_SIZE == CH201_FW_SIZE)
#define CHX01_FW_SIZE CH101_FW_SIZE  // sensor f/w size
#endif

#define CHX01_COMMON_CAL_TRIG_USE_BUS (0x80)  // calibration trigger cmd to use bus speed
#define CHX01_I2C_RTC_CYCLES          (128)   // RTC counter duration when using bus calibration

/* CH-101 common definitions */

#define CH101_COMMON_REG_OPMODE        0x01
#define CH101_COMMON_REG_TICK_INTERVAL 0x02
#define CH101_COMMON_REG_PERIOD        0x05
#define CH101_COMMON_REG_CAL_TRIG      0x06
#define CH101_COMMON_REG_MAX_RANGE     0x07
#define CH101_COMMON_REG_TIME_PLAN     0x09
#define CH101_COMMON_REG_TX_LENGTH     0x10
#define CH101_COMMON_REG_CAL_RESULT    0x0A
#define CH101_COMMON_REG_REV_CYCLES    0x0C
#define CH101_COMMON_REG_DCO_PERIOD    0x0E
#define CH101_COMMON_REG_RX_HOLDOFF    0x11
#define CH101_COMMON_REG_STAT_RANGE    0x12
#define CH101_COMMON_REG_STAT_COEFF    0x13
#define CH101_COMMON_REG_READY         0x14
#define CH101_COMMON_REG_TOF_SF        0x16
#define CH101_COMMON_REG_TOF           0x18
#define CH101_COMMON_REG_AMPLITUDE     0x1A
#define CH101_COMMON_REG_DATA          0x1C

#define CH101_COMMON_I2CREGS_OFFSET 0

#define CH101_COMMON_READY_FREQ_LOCKED (0x02)

#define CH101_COMMON_FREQCOUNTERCYCLES (128)

#define CH101_COMMON_STAT_COEFF_DEFAULT (6)  // default value for stationary target coefficient

/* CH-201 common definitions */

#define CH201_COMMON_REG_OPMODE         0x01
#define CH201_COMMON_REG_TICK_INTERVAL  0x02
#define CH201_COMMON_REG_LOW_GAIN_RXLEN 0x04
#define CH201_COMMON_REG_PERIOD         0x05
#define CH201_COMMON_REG_CAL_TRIG       0x06
#define CH201_COMMON_REG_MAX_RANGE      0x07
#define CH201_COMMON_REG_THRESH_LEN_0   0x08
#define CH201_COMMON_REG_THRESH_LEN_1   0x09
#define CH201_COMMON_REG_CAL_RESULT     0x0A
#define CH201_COMMON_REG_THRESH_LEN_2   0x0C
#define CH201_COMMON_REG_THRESH_LEN_3   0x0D
#define CH201_COMMON_REG_TX_LENGTH      0x10
#define CH201_COMMON_REG_RX_HOLDOFF     0x11
#define CH201_COMMON_REG_ST_RANGE       0x12
#define CH201_COMMON_REG_READY          0x14
#define CH201_COMMON_REG_THRESH_LEN_4   0x15
#define CH201_COMMON_REG_THRESHOLDS     0x16  // start of array of six 2-byte threshold levels
#define CH201_COMMON_REG_TOF_SF         0x22
#define CH201_COMMON_REG_TOF            0x24
#define CH201_COMMON_REG_AMPLITUDE      0x26
#define CH201_COMMON_REG_DATA           0x28

#define CH201_COMMON_I2CREGS_OFFSET 0

#define CH201_COMMON_READY_FREQ_LOCKED (0x02)

#define CH201_COMMON_FREQCOUNTERCYCLES (128)
#define CH201_COMMON_RX_LOW_GAIN_MIN   (8)  // minimum low-gain sample count

#define CHX01_GPRMT_REG_OPMODE         0x01
#define CHX01_GPRMT_REG_TICK_INTERVAL  0x02
#define CHX01_GPRMT_REG_LOW_GAIN_RXLEN 0x04
#define CHX01_GPRMT_REG_PERIOD         0x05
#define CHX01_GPRMT_REG_CAL_TRIG       0x06
#define CHX01_GPRMT_REG_MAX_RANGE      0x07
#define CHX01_GPRMT_REG_THRESH_LEN_0   0x08
#define CHX01_GPRMT_REG_THRESH_LEN_1   0x09
#define CHX01_GPRMT_REG_CAL_RESULT     0x0A
#define CHX01_GPRMT_REG_THRESH_LEN_2   0x0C
#define CHX01_GPRMT_REG_THRESH_LEN_3   0x0D
#define CHX01_GPRMT_REG_TX_LENGTH      0x10
#define CHX01_GPRMT_REG_RX_HOLDOFF     0x11
#define CHX01_GPRMT_REG_ST_RANGE       0x12
#define CHX01_GPRMT_REG_READY          0x14
#define CHX01_GPRMT_REG_THRESH_LEN_4   0x15
#define CHX01_GPRMT_REG_THRESHOLDS     0x16  // start of array of six 2-byte threshold levels
#define CHX01_GPRMT_REG_TOF_SF         0x22
#define CHX01_GPRMT_REG_TOF            0x24
#define CHX01_GPRMT_REG_AMPLITUDE      0x26
#define CHX01_GPRMT_REG_DATA           0x28

#endif /* INCLUDE_WHITNEY_SUPPORT */

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC (1000000000U)
#endif
#define PMUT_FREQUENCY_ERROR_CODE (1)  // this indicates some error in the frequency measurement

/* Function prototypes */
uint8_t ch_common_init(ch_dev_t *dev_ptr, ch_group_t *grp_ptr, uint8_t dev_num, ch_fw_init_func_t fw_init_func);

uint8_t ch_common_set_init_firmware(ch_dev_t *dev_ptr, ch_fw_init_func_t fw_init_func);

uint8_t ch_common_group_start(ch_group_t *grp_ptr);

uint8_t ch_common_set_mode(ch_dev_t *dev_ptr, ch_mode_t mode);

uint8_t ch_common_fw_load(ch_dev_t *dev_ptr);

uint8_t ch_common_set_rtc(ch_dev_t *dev_ptr, ch_rtc_src_t rtc_source, uint16_t rtc_freq);

uint8_t ch_common_set_sample_interval(ch_dev_t *dev_ptr, uint16_t interval_ms);  // deprecated
uint8_t ch_common_set_freerun_interval(ch_dev_t *dev_ptr, uint16_t interval_ms);

uint8_t ch_common_set_freerun_interval_us(ch_dev_t *dev_ptr, uint32_t interval_us);

uint8_t ch_common_set_freerun_interval_ticks(ch_dev_t *dev_ptr, uint32_t interval_periods);

uint8_t ch_common_set_freerun_time_hop(ch_dev_t *dev_ptr, uint8_t meas_num, bool enable);

uint8_t ch_common_set_num_samples(ch_dev_t *dev_ptr, uint16_t num_samples);

uint16_t ch_common_get_num_samples(ch_dev_t *dev_ptr);

uint8_t ch_common_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range_mm);

uint8_t ch_common_get_locked_state(ch_dev_t *dev_ptr);

uint32_t ch_common_get_op_freq(ch_dev_t *dev_ptr);

void ch_common_prepare_pulse_timer(ch_dev_t *dev_ptr);

void ch_common_store_pt_result(ch_dev_t *dev_ptr);

void ch_common_store_op_freq(ch_dev_t *dev_ptr);

void ch_common_store_bandwidth(ch_dev_t *dev_ptr);

void ch_common_store_scale_factor(ch_dev_t *dev_ptr);

uint16_t ch_common_mm_to_samples(ch_dev_t *dev_ptr, uint16_t num_mm);

uint16_t ch_common_samples_to_mm(ch_dev_t *dev_ptr, uint16_t num_samples);

uint8_t ch_common_get_iq_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                              ch_io_mode_t nonblock);

uint8_t ch_common_set_sample_window(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t end_sample);

uint16_t ch_common_get_amplitude_avg(ch_dev_t *dev_ptr);

uint8_t ch_common_get_amplitude_data(ch_dev_t *dev_ptr, uint16_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                                     ch_io_mode_t mode);
uint8_t ch_common_get_amp_thresh_data(ch_dev_t *dev_ptr, ch_amp_thresh_t *buf_ptr, uint16_t start_sample,
                                      uint16_t num_samples, ch_io_mode_t mode);

uint8_t ch_common_set_rx_low_gain(ch_dev_t *dev_ptr, uint16_t num_samples);
uint16_t ch_common_get_rx_low_gain(ch_dev_t *dev_ptr);

uint8_t ch_common_set_tx_length(ch_dev_t *dev_ptr, uint16_t num_cycles);
uint16_t ch_common_get_tx_length(ch_dev_t *dev_ptr);

uint8_t ch_common_set_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);
uint8_t ch_common_get_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);

uint8_t ch_common_check_program(ch_dev_t *dev_ptr);
uint8_t ch_common_set_frequency(ch_dev_t *dev_ptr, uint32_t target_freq_hz);
uint8_t ch_common_group_set_frequency(ch_group_t *grp_ptr, uint32_t frequency);
uint8_t ch_common_set_pmut_clock(ch_dev_t *dev_ptr, ch_pmut_clk_cfg_t clock_cfg);
uint8_t ch_common_watchdog_enable(ch_dev_t *dev_ptr);
uint8_t ch_common_watchdog_disable(ch_dev_t *dev_ptr);

#ifdef INCLUDE_SHASTA_SUPPORT
uint8_t ch_common_meas_init_queue(ch_dev_t *dev_ptr);
uint8_t ch_common_meas_reset(ch_dev_t *dev_ptr, uint8_t meas_num);
uint8_t ch_common_meas_init(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_config_t *meas_config_ptr);

uint8_t ch_common_write_data_validation_cfg(ch_dev_t *dev_ptr, uint8_t en, int16_t seed);

uint8_t ch_common_get_mfg_info(ch_dev_t *dev_ptr, ch_mfg_info_t *info_ptr);

uint8_t ch_common_meas_import(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr);
uint8_t ch_common_meas_add_segment(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_segment_t *seg_ptr);
uint8_t ch_common_meas_insert_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *const inst_ptr,
                                          uint8_t inst_num_to_insert);
uint8_t ch_common_meas_remove_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t inst_num_to_remove);
uint8_t ch_common_meas_add_segment_count(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t int_enable);
uint8_t ch_common_meas_add_segment_rx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples, uint8_t gain,
                                      uint8_t atten, uint8_t int_enable);
uint8_t ch_common_meas_add_segment_tx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t pulse_width,
                                      uint8_t phase, uint8_t int_enable);
void ch_common_meas_init_segment_count(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t int_enable);
void ch_common_meas_init_segment_rx(ch_meas_segment_t *seg_ptr, uint16_t num_samples, ch_odr_t odr, uint8_t gain,
                                    uint8_t atten, uint8_t int_enable);
void ch_common_meas_init_segment_tx(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t pulse_width, uint8_t phase,
                                    uint8_t int_enable);
uint8_t ch_common_meas_optimize(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr);
uint8_t ch_common_meas_write_config(ch_dev_t *dev_ptr);
uint8_t ch_common_meas_update_counts(ch_dev_t *dev_ptr, uint8_t meas_num, measurement_t *meas_ptr);
void ch_common_meas_activate(ch_dev_t *dev_ptr, uint8_t meas_num);
void ch_common_meas_standby(ch_dev_t *dev_ptr, uint8_t meas_num);
uint8_t ch_common_meas_switch(ch_dev_t *dev_ptr);
uint8_t ch_common_meas_get_last_num(ch_dev_t *dev_ptr);
void ch_common_meas_get_info(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_info_t *info_ptr);
void ch_common_meas_get_queue_info(ch_dev_t *dev_ptr, ch_meas_queue_info_t *info_ptr);
void ch_common_inst_get_seg_info(pmut_transceiver_inst_t *inst_ptr, uint8_t odr, ch_meas_seg_info_t *info_ptr);
void ch_common_meas_get_seg_info(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t seg_num, ch_meas_seg_info_t *info_ptr);
uint8_t ch_common_meas_set_interval(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t interval_ms);
uint8_t ch_common_meas_set_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t interval_us);
uint8_t ch_common_meas_set_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t rtc_periods);
uint16_t ch_common_meas_get_interval(ch_dev_t *dev_ptr, uint8_t meas_num);
uint32_t ch_common_meas_get_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num);
uint32_t ch_common_meas_get_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num);
uint8_t ch_common_meas_set_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);
uint16_t ch_common_meas_get_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num);
uint8_t ch_common_meas_set_max_range(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t max_range_mm);
uint8_t ch_common_meas_set_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t odr);
ch_odr_t ch_common_meas_get_odr(ch_dev_t *dev_ptr, uint8_t meas_num);
uint16_t ch_common_meas_mm_to_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_mm);
uint16_t ch_common_meas_samples_to_mm(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/**
 * \brief Read configuration settings associated with the last measurement.
 *
 * This function may be called to read measurement config from the sensor.
 * It reads the ODR, IQ format, number of IQ bytes, and the last measurement
 * config index from the sensor and sets it into the corresponding fields of
 * dev_ptr.
 *
 * This function is already called from ch_rangefinder_get_target_range, which
 * requires the ODR to convert the range from raw counts to millimeters. You
 * may need to manually call this function when implementing your own methods
 * that fetch and post-process data from the sensor.
 *
 * \param dev_ptr The device pointer. Will be modifed with measurement config
 *                read from sensor.
 *
 * \return Zero for success; non-zero for error.
 */
uint8_t ch_common_read_meas_config(ch_dev_t *dev_ptr);

uint8_t ch_common_init_algo(ch_dev_t *dev_ptr);
uint8_t ch_common_get_algo_info(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr);
uint8_t ch_common_get_algo_config(ch_dev_t *dev_ptr, void *algo_cfg_ptr);
uint8_t ch_common_set_algo_config(ch_dev_t *dev_ptr, const void *algo_cfg_ptr);
uint8_t ch_common_get_algo_output(ch_dev_t *dev_ptr, void *algo_out_ptr);
uint8_t ch_common_get_algo_state(ch_dev_t *dev_ptr, void *algo_state_ptr);

uint8_t ch_common_set_interrupt_mode(ch_dev_t *dev_ptr, ch_interrupt_mode_t mode);
ch_interrupt_mode_t ch_common_get_interrupt_mode(ch_dev_t *dev_ptr);

uint8_t ch_common_set_interrupt_drive(ch_dev_t *dev_ptr, ch_interrupt_drive_t drive);
ch_interrupt_drive_t ch_common_get_interrupt_drive(ch_dev_t *dev_ptr);

#endif  // INCLUDE_SHASTA_SUPPORT

uint8_t ch_common_set_target_interrupt(ch_dev_t *dev_ptr, ch_tgt_int_filter_t tgt_filter_mode);
ch_tgt_int_filter_t ch_common_get_target_interrupt(ch_dev_t *dev_ptr);

/**
 * \brief Convert the raw range from the sensor to millimeters.
 *
 * The sensor provides a raw reading of the range in LSBs. Use this function
 * to convert this to a result in millimeters. The output is in fixed point
 * with 5 decimal digits.
 *
 * \param dev_ptr The device pointer
 * \param time_of_flight The raw range (AKA raw time of flight)
 * \param range_type One of CH_RANGE_ECHO_ONE_WAY, for the distance between
 *                   a pulse echo sensor and a target; CH_RANGE_ROUND_TRIP
 *                   for the round-trip distance between sensor and target;
 *                   or CH_RANGE_DIRECT for pitch-catch operating mode.
 *
 * \return The range in mm in UQ27.5 format (an unsigned integer with 5 decimal
 *         bits).
 */
uint32_t ch_common_range_lsb_to_mm(const ch_dev_t *dev_ptr, uint32_t time_of_flight, ch_range_t range_type);

uint32_t ch_common_samples_to_cycles(uint16_t num_samples, ch_odr_t odr);
uint16_t ch_common_cycles_to_samples(uint32_t num_cycles, ch_odr_t odr, bool include_s0);
uint32_t ch_common_usec_to_cycles(ch_dev_t *dev_ptr, uint32_t num_usec);
uint32_t ch_common_cycles_to_usec(ch_dev_t *dev_ptr, uint32_t num_cycles);
uint16_t ch_common_usec_to_ticks(const ch_dev_t *dev_ptr, uint32_t num_usec);
uint32_t ch_common_ticks_to_usec(const ch_dev_t *dev_ptr, uint16_t num_rtc_periods);

uint16_t ch_common_get_num_output_samples(ch_dev_t *dev_ptr);

/*!
 * \brief Measure PMUT frequency on an ICU device.
 *
 * \param dev_ptr 		pointer to the ch_dev_t config structure for a sensor
 *
 * \return PMUT operating frequency in Hz
 *
 * This function must only be called after initialization (ie after calling ch_group_start()).
 */
/*!
 */
uint32_t ch_common_measure_pmut_frequency(ch_dev_t *dev_ptr);

#ifdef __cplusplus
}
#endif

#endif /* CH_COMMON_H_ */
