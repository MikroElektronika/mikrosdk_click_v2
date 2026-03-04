/*! \file ch_rangefinder.h
 *
 * \brief Internal driver functions for operation with the Chirp ultrasonic sensor.
 *
 * This file contains range finding routines.
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
#ifndef CH_RANGEFINDER_H_
#define CH_RANGEFINDER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <invn/soniclib/soniclib.h>
#include <invn/soniclib/ch_rangefinder_types.h>

// total number of thresholds
#define CH101_COMMON_NUM_THRESHOLDS (6)
#define CHX01_COMMON_NUM_THRESHOLDS (6)

uint8_t ch_rangefinder_get_algo_config(const ch_dev_t *dev_ptr, ch_rangefinder_algo_config_t *config_ptr);

uint8_t ch_rangefinder_set_algo_config(ch_dev_t *dev_ptr, const ch_rangefinder_algo_config_t *config_ptr);

uint16_t ch_rangefinder_get_amplitude(ch_dev_t *dev_ptr);

uint8_t ch_rangefinder_set_static_range(ch_dev_t *dev_ptr, uint16_t samples);

uint8_t ch_rangefinder_set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresholds_ptr);
uint8_t ch_rangefinder_get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_buf_ptr);

uint8_t ch_rangefinder_set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t rx_holdoff);
uint16_t ch_rangefinder_get_rx_holdoff(ch_dev_t *dev_ptr);

uint32_t ch_rangefinder_get_range(ch_dev_t *dev_ptr, ch_range_t range_type);
uint32_t ch_rangefinder_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type);

/*!
 * \brief Get the measured time-of-flight from a sensor in microseconds
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * \return Time-of-flight in microseconds,
 *         or 0 if error
 *
 * This function reads the measurement result registers from the sensor and then computes the
 * time-of-flight in microseconds.  The time-of-flight is returned as a 32-bit integer.
 *
 * If the sensor did not successfully find the range of a target during the most recent measurement,
 * the returned value will be \a zero (0).  If an error occurs when getting or calculating the
 * range, zero (0) will be returned.
 *
 * \note This function only reports the results from the most recently completed measurement cycle.  It
 * does not actually trigger a measurement.  The time-of-flight that is reported is the total time
 * measured by the sensor between transmission and reception.  The value is always the full round-trip
 * time-of-flight.
 *
 */
uint32_t ch_get_tof_us(ch_dev_t *dev_ptr);

/*!
 * \brief Get static target rejection range setting.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * \return Static target rejection range setting, in samples, or 0 if not enabled
 *
 * This function returns the number of samples at the beginning of a measurement cycle over
 * which static target rejection filtering will be applied.
 *
 * To calculate the physical distance that corresponds to the number of samples, use the
 * \a ch_samples_to_mm() function.
 *
 * For ICU sensors, this function always returns the value for the default measurement
 * definition.  To specify which measurement to query, use the \a icu_gpt_get_static_filter()
 * function.
 *
 * See also \a ch_set_static_range().
 */
uint16_t ch_get_static_range(const ch_dev_t *dev_ptr);

/*!
 * \brief Configure static target rejection.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_samples 	number of sensor samples (at beginning of measurement cycle) over
 *                    	which static targets will be rejected
 *
 * \return 0 if successful, non-zero if error
 *
 * Static target rejection is a special processing mode in which the sensor will actively filter
 * out signals from close, non-moving objects, so that they do not continue to generate range
 * readings.  This allows detection and reporting of target objects that are farther away than the
 * static objects.  (Normally, the sensor reports the range value for the closest detected object.)
 *
 * Static target rejection is applied for a specified number of samples, starting at the beginning
 * of a measurement cycle* (i.e. for the closest objects).  The num_samples parameter specifies the
 * number of samples that will be filtered.  To calculate the appropriate value for \a num_samples
 * to filter over a certain physical distance, use the \a ch_mm_to_samples() function.
 *
 * For ICU sensors, this function always controls the default measurement definition.  To
 * specify which measurement to modify, use the \a icu_gpt_set_static_filter() function.
 *
 * See also \a ch_get_static_range().
 */
uint8_t ch_set_static_range(ch_dev_t *dev_ptr, uint16_t num_samples);

/*!
 * \brief Get the number of targets detected in last measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return number of targets detected in last measurement
 *
 * This function returns the number of valid targets that were detected in
 * the last measurement completed by the sensor.  Data for each of these targets
 * may then be read using \a ch_get_target_range() and \a ch_get_target_amplitude().
 *
 * See also \a ch_get_target_range(), \a ch_set_num_ranges().
 */
uint8_t ch_get_num_targets(ch_dev_t *dev_ptr);

/*!
 * \brief Get the range to a specific target detected in last measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param target_num	number of target to report
 * \param range_type 	the range type to be reported (e.g. one-way vs. round-trip)
 *
 * \return Range in millimeters times 32, or \a CH_NO_TARGET (0xFFFFFFFF) if no target was detected,
 *         or 0 if error
 *
 * This function reads the measurement data for a specific target and then computes the actual
 * range.  It should be called after the sensor has indicated that a measurement cycle is complete
 * by generating a signal on the INT line.  (Typically, this will be set up by an interrupt handler
 * associated with that input line.)
 *
 * \a target_num specifies the target whose range is to be calculated.  The \a ch_get_num_targets()
 * function may be used to determine the total number of valid targets detected by the measurement.
 *
 * The \a range_type parameter indicates whether the measurement is based on the one-way or round-trip
 * distance to/from a target, or the direct distance between two sensors operating in pitch-catch mode.
 * The possible values are:
 *   - \a CH_RANGE_ECHO_ONE_WAY -  gets full pulse/echo round-trip distance, then divides by 2
 *   - \a CH_RANGE_ECHO_ROUND_TRIP	- full pulse/echo round-trip distance
 *   - \a CH_RANGE_DIRECT - for receiving sensor in pitch-catch mode (one-way)
 *
 * See also \a ch_get_target_amplitude(), \a ch_get_range(), ch_get_num_targets().
 */
uint32_t ch_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type);

/*!
 * \brief Get the amplitude for a specific target detected in last measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param target_num	number of target to report
 *
 * \return amplitude value (LSBs)
 *
 * This function reads the measurement data for a specific target and returns the measured
 * amplitude value.  The amplitude is representative of the incoming sound pressure.  The value is expressed
 * in internal sensor counts (LSBs) and is not calibrated to any standard units.
 *
 * The amplitude value is not updated if a measurement cycle resulted in \a CH_NO_TARGET, as returned
 * by \a ch_get_target_range().
 *
 * See also \a ch_get_target_range(), \a ch_get_amplitude().
 */
uint16_t ch_get_target_amplitude(ch_dev_t *dev_ptr, uint8_t target_num);

/*!
 * \brief Get the measured time-of-flight for a specific target in microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param target_num	number of the detected target to be reported
 *
 * \return Time-of-flight in microseconds,
 *         or 0 if error
 *
 * This function reads the measurement result registers from the sensor and then computes the
 * time-of-flight in microseconds.  The time-of-flight is returned as a 32-bit integer.
 *
 * If the sensor did not successfully find the range of a target during the most recent measurement,
 * the returned value will be \a zero (0).  If an error occurs when getting or calculating the
 * range, zero (0) will be returned.
 *
 * \note This function only reports the results from the most recently completed measurement cycle.  It
 * does not actually trigger a measurement.  The time-of-flight that is reported is the total time
 * measured by the sensor between transmission and reception.  The value is always the full round-trip
 * time-of-flight.
 *
 */
uint32_t ch_get_target_tof_us(ch_dev_t *dev_ptr, uint8_t target_num);

/**
 * @brief      Return if a target is detected near sensor (in the ringdown)
 *
 * @param      dev_ptr  pointer to the ch_dev_t descriptor structure
 *
 * @return     1 if a target is detected, else 0
 */
uint8_t ch_is_target_in_ringdown(ch_dev_t *dev_ptr);

/*!
 * \brief Get the detection threshold.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param threshold_index 	index to the thresholds, starting from 0
 *
 * \return amplitude threshold value
 *
 * This function obtains the detection threshold value with the specified \a threshold_index
 * from the sensor and returns the corresponding threshold amplitude.
 *
 * See also \a ch_set_threshold().
 *
 * \note This function is only available when using special sensor firmware packages from Chirp.
 *
 * \note For ICU sensors and CH201 sensors with GPRMT firmware, multiple thresholds with programmable
 * sample ranges are supported - use \a ch_get_thresholds().
 */
uint16_t ch_get_threshold(ch_dev_t *dev_ptr, uint8_t threshold_index);

/*!
 * \brief Set the detection threshold.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param threshold_index 	index to the thresholds, starting from 0
 * \param amplitude 		amplitude threshold value
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the detection threshold value with the specified \a threshold_index value
 * for the sensor.  The detection threshold is the minimum amplitude required for a target detection
 * to be reported.  The \a amplitude value is the new required amplitude, expressed in the same
 * internal units used in \a ch_get_amplitude() and other functions.
 *
 * See also \a ch_get_threshold().
 *
 * \note This function is only available when using select sensor firmware packages from Chirp.
 *
 * \note For ICU sensors and CH201 sensors with GPRMT firmware, multiple thresholds with programmable
 * sample ranges are supported - use \a ch_set_thresholds().
 */
uint8_t ch_set_threshold(ch_dev_t *dev_ptr, uint8_t threshold_index, uint16_t amplitude);

/*!
 * \brief Get detection thresholds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param thresh_ptr 	pointer to ch_thresholds_t structure to receive threshold data
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains the current detection threshold values from the sensor and
 * returns them in a ch_thresholds_t structure specified by \a thresh_ptr.  The
 * ch_thresholds_t structure holds an array of ch_thresh_t structures, each of which
 * contains a starting sample number and amplitude threshold value.
 *
 * For ICU sensors, this function only reports the thresholds for the default measurement
 * (CH_DEFAULT_MEAS_NUM).  If both measurements are being used, the thresholds for each
 * may be obtained individually by using the \a icu_gpt_get_thresholds() function.
 *
 * See also \a ch_set_thresholds().
 *
 * \note This function is available for ICU sensors and when using most sensor firmware for
 * CH201 sensors.  If using other CH101/CH201 firmware with only a single detection treshold,
 * use \a ch_get_threshold().
 */
uint8_t ch_get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr);

/*!
 * \brief Set detection thresholds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param thresh_ptr 	pointer to ch_thresholds_t structure containing threshold data
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the detection threshold values for the sensor based on the
 * values in the \a ch_thresholds_t structure specified by \a thresh_ptr.  The
 * ch_thresholds_t structure holds an array of ch_thresh_t structures, each of which
 * contains a starting sample number and amplitude threshold value.
 *
 * To use this function, first initialize the ch_thresh_t sample/level pair of values for
 * each threshold.  The ICU sensor supports eight (8) separate thresholds, while the CH201 sensor
 * with GPRMT firmware supports six (6) thresholds.  Each threshold has a maximum
 * sample length of 255.
 *
 * It is not necessary to use the full set of thresholds, if the application and sensing
 * environment do not require that many different levels.  Unused thresholds should occupy
 * the last elements in the ch_thresholds_t structure and should have zero (0) for their
 * starting sample number.  These entries will be ignored, and the threshold specified
 * in the final valid entry will apply to the rest of the measurement.
 *
 * For ICU sensors, this function only sets the thresholds for the default measurement
 * (CH_DEFAULT_MEAS_NUM).  If both measurements are being used, the thresholds for each
 * may be set individually by using the \a icu_gpt_set_thresholds() function.
 *
 * See also \a ch_get_thresholds().
 *
 * \note This function supports ICU sensors and CH201 sensors with GPRMT firmware, with multiple
 * detection thresholds and programmable sample ranges.  If using other firmware with a
 * single detection treshold, use \a ch_set_threshold().
 */
uint8_t ch_set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresh_ptr);

/*!
 * \brief Get number of detection thresholds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return number of detection thresholds, or 0 if thresholds are not supported
 *
 * This function returns the number of independent detection threshold values that
 * are supported by the current sensor and sensor firmware.  For firmware supporting
 * multiple thresholds, the number of thresholds is the same as the number of threshold
 * fields in the \a ch_thresholds_t structure.
 *
 * See also \a ch_set_thresholds().
 */
uint8_t ch_get_num_thresholds(const ch_dev_t *dev_ptr);

uint8_t ch_rangefinder_display_config_info(ch_dev_t *dev_ptr);

#ifdef __cplusplus
}
#endif

#endif /* CH_RANGEFINDER_H_ */