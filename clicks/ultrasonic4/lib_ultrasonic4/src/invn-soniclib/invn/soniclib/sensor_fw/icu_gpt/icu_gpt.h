/*! \file icu_gpt.h
 *
 * \brief Internal definitions for the Chirp ICU General Purpose Transceiver (GPT) firmware.
 *
 * This file contains various definitions and values for use with the icu_gpt
 * sensor firmware.
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

#ifndef ICU_GPT_H_
#define ICU_GPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <invn/soniclib/details/icu.h>
#include <invn/icu_interface/ch-rangefinder/structs.h>
#include <invn/soniclib/ch_rangefinder_types.h>
#include <invn/soniclib/soniclib.h>

#define ICU_GPT_MAX_SAMPLES    (IQ_SAMPLES_MAX)
#define ICU_GPT_NUM_THRESHOLDS (LEN_THRESH)

#define CH_THRESH_LEVEL_HOLDOFF (40000)

//! Algorithm configuration
typedef struct {
	uint16_t ringdown_cancel_samples;
	uint16_t static_filter_samples;
	ch_output_type_t iq_output_format;  // normal (Q,I) pairs, threshold/amp pairs, or 16-bit amp
	uint8_t num_ranges;
	uint8_t filter_update_interval;  // update the ringdown and STR filters every N+1 samples (0=every time, 1=every
	                                 // 2nd...
} icu_gpt_algo_config_t;

extern const char *icu_gpt_version;  // version string in fw .c file
extern const uint8_t icu_gpt_fw_text[];
extern const uint8_t icu_gpt_fw_vec[];
extern const uint16_t icu_gpt_text_size;
extern const uint16_t icu_gpt_vec_size;

uint16_t get_icu_gpt_fw_ram_init_addr(void);
uint16_t get_icu_gpt_fw_ram_init_size(void);

const unsigned char *get_ram_icu_gpt_init_ptr(void);

/**
 * @brief      Initialize GPT FW
 *
 * This function shall not be directly called.
 * It shall be passed in parameter of \a ch_init
 */
uint8_t icu_gpt_init(ch_dev_t *dev_ptr, fw_info_t **fw_info);

/**
 * @brief      Initialize GPT Algorithm
 *
 * @param      dev_ptr   pointer to the ch_dev_t descriptor structure
 * @param      algo_cfg  Pointer to algorithm configuration instanciated in application
 *
 * \return 0 if success, 1 if error
 */
uint8_t icu_gpt_algo_init(ch_dev_t *dev_ptr, InvnAlgoRangeFinderConfig *algo_cfg);

/**
 * @brief      Configure GPT Algorithm
 *
 * @param      dev_ptr          pointer to the ch_dev_t descriptor structure
 * @param[in]  meas_num         The measurement number
 * @param[in]  algo_config_ptr  Pointer to the  configuration to apply to algorithm
 * @param[in]  lib_thresh_ptr   Pointer to detection threshold definitions
 *
 * This function initializes the measurement specified by \a meas_num with the specified
 * configuration and detection thresholds.
 * * - num_ranges - maximum number of separate target range values to report
 * - ringdown_cancel_samples - number of samples close to sensor to use ringdown cancellation filter
 * - static_filter_samples - number of samples close to sensor to have static target rejection (STR) filter
 * - iq_output_format - 0=normal (Q,I) pairs; 1=mag,threshold pairs, 2=mag,phase pairs
 * - filter_update_interval - how often to update the ringdown and STR filters
 *
 *  \a thresh_ptr is a pointer to a structure containing the definitions of the detection thresholds
 * that will be used to detect a target.  (This same type of structure is used by \a ch_set_thresholds().)
 *
 * \return 0 if success, 1 if error
 */
uint8_t icu_gpt_algo_configure(ch_dev_t *dev_ptr, uint8_t meas_num, const icu_gpt_algo_config_t *algo_config_ptr,
                               const ch_thresholds_t *lib_thresh_ptr);

/**
 * @brief      Reset GPT Algorithm configuration
 *
 * @param      dev_ptr   pointer to the ch_dev_t descriptor structure
 * @param[in]  meas_num  The measurement number
 */
void icu_gpt_algo_reset(ch_dev_t *dev_ptr, uint8_t meas_num);

/**
 * @brief      Get the I/Q data output format of GPT Algorithm
 *
 * @param      dev_ptr   pointer to the ch_dev_t descriptor structure
 * @param[in]  meas_num  The measurement number
 *
 * @return I/Q data output format
 *
 * This function returns the measurement I/Q data output format, as follows:
 *  - CH_OUTPUT_IQ (0) - Standard pairs of {Q,I} int16_t values
 *  - CH_OUTPUT_AMP_THRESH (1) - Output amplitude + threshold uint16_t pair values
 *  - CH_OUTPUT_AMP	(2) - Output uint16_t amplitude values only
 */
ch_output_type_t icu_gpt_algo_get_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the I/Q data output format of GPT Algorithm.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param output_format	I/Q output format 0=normal (Q,I) pairs; 1=amplitude,threshold pairs, 2=amplitude array
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the measurement I/Q data output format.  The data may be output in
 * three different formats, based on the value of \a output_format:
 *  - CH_OUTPUT_IQ - Standard pairs of {Q,I} int16_t values
 *  - CH_OUTPUT_AMP_THRESH - Output amplitude + threshold uint16_t pair values
 *  - CH_OUTPUT_AMP	- Output uint16_t amplitude values only
 *
 */
uint8_t icu_gpt_algo_set_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num, ch_output_type_t output_format);

/**
 * @brief      Update algo ODR
 *
 * @param      dev_ptr   pointer to the ch_dev_t descriptor structure
 * @param[in]  meas_num  The measurement number
 * @param[in]  new_odr   The new odr
 *
 * Shall be called before ch_meas_set_odr because it relies on current ODR to update algorithm configuration
 */
void icu_gpt_algo_update_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t new_odr);

/*!
 * \brief Get the number of targets detected in last measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return number of targets detected in last measurement
 *
 * This function returns the number of valid targets that were detected in
 * the last measurement completed by the sensor. Data for each of these targets
 * may then be read using \a ch_get_target_range() and \a ch_get_target_amplitude().
 *
 * See also \a ch_get_target_range(), \a ch_set_num_ranges().
 */
uint8_t icu_gpt_algo_get_num_targets(ch_dev_t *dev_ptr);

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
uint16_t icu_gpt_algo_get_target_amplitude(ch_dev_t *dev_ptr, uint8_t target_num);

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
uint32_t icu_gpt_algo_get_target_tof_us(ch_dev_t *dev_ptr, uint8_t target_num);

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
uint32_t icu_gpt_algo_get_target_range(ch_dev_t *dev_ptr, uint8_t target_num, ch_range_t range_type);

/*!
 * \brief Set data output format and rate.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param output_ptr 	pointer to the data output type, including format and decimation factor
 *
 * This function sets both the data output format type and rate for sample data within a measurement.
 * The values are passed in a \a ch_output_t structure specified by \a output_ptr, which contains two
 * fields, \a output_type and \a decimation_factor.  The decimation factor is equivalent to the
 * sample output data rate (ODR) of the sensor, expressed differently.
 *
 * The possible values for output_type are:
 *  - CH_OUTPUT_IQ - Standard pairs of {Q,I} int16_t values (\a ch_iq_sample_t)
 *  - CH_OUTPUT_AMP_THRESH - Output amplitude + threshold uint16_t pair values (\a ch_amp_thresh_t)
 *  - CH_OUTPUT_AMP	- Output uint16_t amplitude values only
 *
 * The possible values for decimation_factor and the equivalent output
 * rate (ODR) values are as follows:
 *
 *  | Decimation Factor		|	ODR Value			| Sample Rate vs. Default
 *  | -----------------		|   ---------			| -----------------------
 *  | CH_DECIMATION_NONE	|	CH_ODR_FREQ_DIV_8 (CH_ODR_DEFAULT)	| default
 *  | CH_DECIMATION_0_25	|	CH_ODR_FREQ_DIV_2	| 4 x default
 *  | CH_DECIMATION_0_50	|	CH_ODR_FREQ_DIV_4	| 2 x default
 *  | CH_DECIMATION_2		|	CH_ODR_FREQ_DIV_16	| 1/2 default
 *  | CH_DECIMATION_3		|	\a no \a equivalent | 1/3 default - only in special CHx01 f/w
 *  | CH_DECIMATION_4		|	CH_ODR_FREQ_DIV_32  | 1/4 default
 *
 * Both measurements will be set to the specified output type.  To change
 * the output format for a single measurement, use \a ch_meas_set_iq_output().
 * To change the output data rate for a single measurement, use \a ch_meas_set_odr().
 */
uint8_t icu_gpt_algo_set_data_output(ch_dev_t *dev_ptr, const ch_output_t *output_ptr);

/**
 * @brief      Return if a target is detected near sensor (in the ringdown)
 *
 * @param      dev_ptr  pointer to the ch_dev_t descriptor structure
 *
 * @return     1 if a target is detected, else 0
 */
uint8_t icu_gpt_algo_is_target_in_ringdown(ch_dev_t *dev_ptr);

/**
 * @brief      Display GPT thresholds for debug purpose.
 *
 * @param      dev_ptr  pointer to the ch_dev_t descriptor structure
 *
 * @return     RET_OK if print of thresholds succeeded
 */
uint8_t icu_gpt_display_algo_thresholds(ch_dev_t *dev_ptr);

/*!
 * \brief Set the max number of reported target ranges for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_ranges	maximum number of target range values to report
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the maximum number of separate target range values that the
 * sensor will report in a single measurement.
 *
 * If \a num_ranges is set to 1, only a single target will be reported. Generally,
 * this will be the closest target whose signal exceeds the detection threshold value for
 * that part of the measurement.  Other targets will not be reported.
 *
 * If \a num_ranges is greater than 1, if multiple targets have ultrasound signals that
 * exceed the applicable threshold value, the sensor will report range (and amplitude)
 * values for each.
 *
 * See also \a ch_get_target_range(), \a ch_get_target_amplitude(), \a icu_gpt_get_num_ranges().
 */
uint8_t icu_gpt_set_num_ranges(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t num_ranges);

/*!
 * \brief Get the max number of reported target ranges for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return max number of target range values that will be reported
 *
 * This function returns the maximum number of separate target range values that the
 * sensor will report in a single measurement.
 */
uint8_t icu_gpt_get_num_ranges(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the number of ringdown cancellation samples for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_samples	number of samples (closest to sensor) to get ringdown cancellation
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the number of samples in the specified measurement that will receive "ringdown
 * cancellation" processing.  These samples are always the first in the measurement (corresponding
 * to targets closest to the sensor).
 *
 * Ringdown is the physical settling time of the ultrasound
 * transducer after generating a transmit pulse.  This settling causes a large false signal in
 * the first receive samples after the transmit segment ends.  Ringdown cancellation is a
 * filtering technique to remove these ringdown artifacts.  However, it can also
 * affect the sensing ability at close range.  The number of ringdown samples may be
 * tuned to obtain the best performance in a specific application.
 *
 * If the ringdown cancel sample count is too low, it will result in false detections at
 * very close indicated ranges.
 *
 * See also \a icu_gpt_get_ringdown_cancel()
 */
uint8_t icu_gpt_set_ringdown_cancel(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/*!
 * \brief Get the number of ringdown cancellation samples for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return number of ringdown cancellation samples
 *
 * This function returns the number of samples in the specified measurement that will receive "ringdown
 * cancellation" processing.  These samples are always the first in the measurement (corresponding
 * to targets closest to the sensor).
 *
 * See also \a icu_gpt_set_ringdown_cancel().
 */
uint16_t icu_gpt_get_ringdown_cancel(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set detection thresholds for a specific measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param thresh_ptr 	pointer to ch_thresholds_t structure containing threshold data
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the detection threshold values for the measurement specified
 * by \a meas_num, based on the values in the ch_thresholds_t structure specified by
 * \a thresh_ptr.  The ch_thresholds_t structure holds an array of ch_thresh_t
 * structures, each of which contains a starting sample number and amplitude threshold value.
 *
 * To use this function, first initialize the fields in the ch_thresh_t structure with
 * the sample/level pair of values for each threshold.  The ICU sensor supports eight (8)
 * separate thresholds.  Each threshold has a maximum sample length of 255.
 *
 * It is not necessary to use the full set of thresholds, if the appliction and sensing
 * environment do not require that many different levels.  Unused thresholds should occupy
 * the last ch_thresh_t elements in the ch_thresholds_t structure and should have zero (0)
 * for their starting sample number.  These entries will be ignored, and the threshold specified
 * in the final valid entry will apply to the rest of the measurement.
 *
 * The \a ch_set_thresholds() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_set_thresholds(), \a icu_gpt_get_thresholds().
 *
 * \note This function is only available for ICU sensors.
 */
uint8_t icu_gpt_set_thresholds(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_thresholds_t *lib_thresh_buf_ptr);

/*!
 * \brief Get detection thresholds for a specific measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param thresh_ptr 	pointer to ch_thresholds_t structure to receive threshold data
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains the current detection threshold values for one of the two
 * measurements, as specified by \a meas_num.
 *
 * The threshold values are returned in a ch_thresholds_t structure specified by
 * \a thresh_ptr.  The ch_thresholds_t structure holds an array of ch_thresh_t
 * structures, each of which contains a starting sample number and amplitude threshold
 * value.
 *
 * The \a ch_get_thresholds() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * \note This function is only available for ICU sensors.
 */
uint8_t icu_gpt_get_thresholds(ch_dev_t *dev_ptr, uint8_t meas_num, ch_thresholds_t *lib_thresh_buf_ptr);

/*!
 * \brief Set the number of static target filter samples for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_samples	number of samples (closest to sensor) to have STR filtering
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the number pf samples in the specified measurement that will have static
 * target rejection (STR) filtering.  STR filtering compares the active measurement with
 * previously observed values and will only report a target detection when there has been
 * noticeable change in the measured signal.
 *
 * The STR samples are always the first in the measurement (corresponding to targets closest to
 * the sensor).
 *
 * The \a ch_set_static_range() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a icu_gpt_get_static_filter()
 */
uint8_t icu_gpt_set_static_filter(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/*!
 * \brief Get the number of static target filter samples for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return number of samples to have STR filtering
 *
 * This function returns the number pf samples in the specified measurement that will have static
 * target rejection (STR) filtering.  STR filtering compares the active measurement with
 * previously observed values and will only report a target detection when there has been
 * noticeable change in the measured signal.
 *
 * The STR samples are always the first in the measurement (corresponding to targets closest to
 * the sensor).
 *
 * The \a ch_get_static_filter() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a icu_gpt_set_static_filter().
 */
uint16_t icu_gpt_get_static_filter(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the receive holdoff sample count for a specific measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_samples 	number of samples to be ignored at the beginning of each measurement
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the receive (rx) holdoff sample count for the specified measurement.
 * \a num_samples specifies a number of samples at the beginning of a measurement that will
 * be ignored for the purpose of detecting a target.  (These samples correspond to the closest
 * distances from the sensor.)
 *
 * To convert a physical distance into a sample count value to use here, use \a ch_meas_mm_to_samples().
 *
 * The \a ch_set_rx_holdoff() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a icu_gpt_get_rx_holdoff().
 */
uint8_t icu_gpt_set_rx_holdoff(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/*!
 * \brief Get the receive holdoff sample count for a specific measurement.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return number of samples that are ignored at the beginning of each measurement
 *
 * This function gets the receive (rx) holdoff sample count for the specified measurement.
 * The rx holdoff count is the number of samples at the beginning of a measurement that will
 * be ignored for the purpose of detecting a target, as previously set by \a icu_gpt_set_rx_holdoff().
 *
 * To convert the returned sample count to a physical distance, use \a ch_samples_to_mm().
 *
 * The \a ch_get_rx_holdoff() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a icu_gpt_set_rx_holdoff().
 */
uint16_t icu_gpt_get_rx_holdoff(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the filter update interval for a measurement.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param meas_num			measurement number
 * \param update_interval	how often to update, 0 = every sample
 *
 * \return 0 if success, 1 if error
 *
 * This function specifies how often the ringdown cancellation and static target
 * rejection (STR) filters are updated in the sensor.  A value of 0 will
 * update the filters during every measurement.  A value of 1 will update every
 * second measurement, a value of 2 will update every third measurement, etc.
 *
 * See also \a icu_gpt_get_filter_update().
 */
uint8_t icu_gpt_set_filter_update(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t update_interval);

/*!
 * \brief Get the filter update interval for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function returns the interval value for how often the ringdown cancellation
 * and static target rejection (STR) filters are updated in the sensor.  A value of
 * 0 will update the filters during every measurement.  A value of 1 will update every
 * second measurement, a value of 2 will update every third measurement, etc.
 *
 * See also \a icu_gpt_set_filter_update().
 */
uint8_t icu_gpt_get_filter_update(ch_dev_t *dev_ptr, uint8_t meas_num);

#ifdef __cplusplus
}
#endif

#endif /* ICU_GPT_H_ */
