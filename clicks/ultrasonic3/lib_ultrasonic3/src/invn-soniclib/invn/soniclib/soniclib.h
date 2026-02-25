/*! \file soniclib.h
 *
 * \brief SonicLib public API and support functions for TDK/InvenSense ultrasonic
 * sensors (originally developed by Chirp Microsystems).
 *
 * SonicLib is a set of API functions and sensor driver routines designed to easily
 * control ultrasonic sensors from an embedded C application.  It allows an
 * application developer to obtain ultrasonic measurement data from one or more devices,
 * without needing to develop special low-level code to interact with the sensors directly.
 *
 * The SonicLib API functions provide a consistent interface for an application to use
 * ultrasonic sensors in various situations.  This is especially important, because
 * all TDK/InvenSense ultrasonic sensors are completely programmable, including the memory
 * map.  The SonicLib interfaces allow an application to use different sensor firmware images,
 * without requiring code changes.  Only a single initialization parameter must be modified
 * to use the new sensor firmware.
 *
 * SonicLib is used with all TDK/InvenSense ultrasonic sensors and firmware types and contains
 * all necessary functions to initialize and manage the devices.  It includes a complete set
 * of interfaces for typical rangefinding applications that measure distance using the
 * sensor(s).  Certain special sensor firmware may support unusual features, and additional
 * API interfaces for those special functions may be distributed separately.
 *
 * All function names in the SonicLib API begin with `ch_`.
 *
 * \note All operation of the sensor is controlled through the set of functions, data structures,
 * and symbolic values defined in this header file.  You should not need to modify this file
 * or the SonicLib functions, or use lower-level internal functions such as described in
 * the ch_driver.h file or other files in the `details` subdirectory.  Using any of these internal
 * definitions will reduce your ability to benefit from future enhancements and releases
 * from TDK/InvenSense.
 *
 *
 * #### Board Support Package
 * SonicLib also defines a set of board support package (BSP) functions that must be
 * provided by the developer, board vendor, or TDK/InvenSense.  The BSP functions are
 * NOT part of SonicLib - they are external interface routines that allow the SonicLib
 * functions to access the peripherals on the target board.  These functions, which all
 * begin with a "chbsp_" prefix, are described in the chirp_bsp.h header file.  See the
 * descriptions in that file for more detailed information on the BSP interfaces.
 *
 * Additionally, SonicLib requires the definition of a few static configuration
 * symbols. These are generally board dependent and are used to set the size of
 * static arrays, choose between hardware features that are unlikely to ever
 * change at runtime, etc.
 *
 * There are two ways to provide these symbols. The default behavior expects
 * a header called chirp_board_config.h to be directly on the include path.
 * A default implementation of this file is provided with the BSP, or can be
 * copied from <invn/soniclib/details/chirp_board_config.h>. Once copied and
 * placed in your project, you can edit it to meet your needs. Make sure that
 * your build places the directory containing chirp_board_config.h on the
 * include path (gcc -I option).
 *
 * The second method for providing the symbols is to use the build system
 * define flags. For example, you can use the -D option with gcc. To use this
 * method, you must first define the symbol INVN_SONICLIB_INTERNAL_BOARD_CONFIG.
 * This will cause soniclib to use the board config in <invn/soniclib/details>.
 * You should not edit this file directly. Instead, to change the value of the
 * symbols defined there, simply override them with -D flags during the build.
 *
 *
 * #### Basic Operating Sequence
 * At a high level, an application using SonicLib will do the following:
 *  -# Initialize the hardware on the board
 *  -# Initialize the Soniclib group structures, by calling \a ch_group_init()
 *  -# Initialize the SonicLib devices structures, by calling \a ch_init() for each sensor.
 *  -# Program and start the sensor(s), by calling \a ch_group_start().
 *  -# Set up a handler function to process interrupts from the sensor.
 *  -# Set up a triggering mechanism using a board timer, (unless the sensor will be used
 *  in free-running mode, in which no external trigger is needed).  A
 *  timer handler routine will typically trigger the sensor(s) using \a ch_group_trigger().
 *  -# Configure the sensor's operating range, detection thresholds, and other parameters.
 *  -# Set the sensor mode to enable sensing.
 *
 *  There are dedicated `ch_set_xxx()` functions for all configuration values.  Simple
 *  configurations may be able to use the \a ch_set_config() convenience function to
 *  configure the sensor and set the mode.
 *
 * At this point, the sensor will begin to perform measurements.  At the end of each
 * measurement cycle, the sensor will interrupt the host controller using its INT line.
 * The handler routine set up in step #4 above will be called, and it should cause the
 * application to read the measurement results from the sensor(s), using \a ch_get_range()
 * and optionally \a ch_get_amplitude() and/or \a ch_get_iq_data().
 *
 * Do not trigger a new measurement until the previous measurement has completed and all needed
 * data has been read from the device (including I/Q data, if \a ch_get_iq_data() is used).  If any
 * I/O operations are still active, the new measurement may be corrupted.
 *
 * #### Verbose Debug Output
 * To assist with debugging, verbose debug output from various internal SonicLib functions
 * may be enabled by defining `CH_LOG_MODULE_LEVEL=X` during the system build.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef __SONICLIB_H_
#define __SONICLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*==============  SonicLib Version Info ===================*/
/* SonicLib API/Driver version */
#define SONICLIB_VER_MAJOR  (4) /*!< SonicLib major version. */
#define SONICLIB_VER_MINOR  (7) /*!< SonicLib minor version. */
#define SONICLIB_VER_REV    (1) /*!< SonicLib revision. */
#define SONICLIB_VER_SUFFIX ""  /*!< SonicLib version suffix (contains pre-release info) */

/***** DO NOT MODIFY ANY VALUES BEYOND THIS POINT! *****/

#ifdef INVN_SONICLIB_INTERNAL_BOARD_CONFIG
#include <invn/soniclib/details/chirp_board_config.h> /* Header from board support package containing h/w params */
#else
// Support external board config by default. This was previously assumed to be
// directly on the include path.
#include "chirp_board_config.h"
#endif

/* Preliminary structure type definitions to resolve include order */
typedef struct ch_dev_t ch_dev_t;
typedef struct ch_group_t ch_group_t;
typedef struct fw_info_st fw_info_t;

/* ICU (second generation) Firmware  */
#ifdef INCLUDE_SHASTA_SUPPORT
#include <invn/icu_interface/shasta_external_regs.h> /* Shasta firmware interface */
#include <invn/soniclib/details/icu.h>
#include <invn/icu_interface/icu_algo_info.h> /* ICU sensor algorithm interface */
#endif

/* Miscellaneous header files */

#include <invn/soniclib/details/ch_driver.h>     /* Internal Chirp driver defines */
#include <invn/soniclib/details/ch_math_utils.h> /* math utility functions */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Chirp sensor part numbers */
#define CH101_PART_NUMBER       (101)   /*!< Integer sensor identifier for CH101. */
#define CH201_PART_NUMBER       (201)   /*!< Integer sensor identifier for CH201. */
#define ICU10201_PART_NUMBER    (10201) /*!< Integer sensor identifier for ICU-10201. */
#define ICU20201_PART_NUMBER    (20201) /*!< Integer sensor identifier for ICU-20201. */
#define ICU30201_PART_NUMBER    (30201) /*!< Integer sensor identifier for ICU-30201. */
#define ICU_UNKNOWN_PART_NUMBER (0)     /*!< Integer sensor identifier for unknown ICU sensors. */

/* Max expected number of samples per measurement (actual value depends on sensor f/w used) */
#ifdef INCLUDE_WHITNEY_SUPPORT

#define CH101_MAX_NUM_SAMPLES (225) /*!< Max expected samples per measurement for CH101. */
#define CH201_MAX_NUM_SAMPLES (450) /*!< Max expected samples per measurement for CH201. */
#define MAX_NUM_SAMPLES       CH201_MAX_NUM_SAMPLES

#endif
#ifdef INCLUDE_SHASTA_SUPPORT

#define ICU_MAX_NUM_SAMPLES (IQ_SAMPLES_MAX) /*!< Max for ICU sensors, from shasta_external_regs.h */
#define MAX_NUM_SAMPLES     ICU_MAX_NUM_SAMPLES

#endif

/* Misc definitions */
#define CH_NO_TARGET     (0xFFFFFFFF) /*!< Range value returned if no target was detected. */
#define CH_MIN_RANGE_VAL (0x0001)     /*!< Minimum range value returned for very short distances */

#define CH_DEFAULT_MEAS_NUM   (0) /*!< Measurement number to use for simple ch_mm_to_samples() etc. */
#define CH_DEFAULT_TARGET_NUM (0) /*!< Target number to report for simple ch_get_range() etc. */

#define CH_I2C_ADDR_PROG (0x45) /*!< I2C address of sensor programming interface. */
#define CH_SIG_BYTE_0    (0x0a) /*!< Signature byte in sensor (1 of 2). */
#define CH_SIG_BYTE_1    (0x02) /*!< Signature byte in sensor (2 of 2). */

#define CH_RTC_FREQ_TYPICAL     (29000) /*!< Typical sensor RTC frequency, in Hz, to use if none available. */
#define CH_PMUT_TICKS_PER_CYCLE (16)    /*!< Number of PMUT clock ticks per transducer cycle */

#define CH_OP_FREQ_USE_AVG (0) /*!< Special freq value to use average op freq for sensor group */

#ifdef MAXTARG
#define CH_MAX_NUM_TARGETS (MAXTARG) /*!< Maximum number of targets supported in sensor f/w */
#else
#define CH_MAX_NUM_TARGETS (1) /*!< Maximum number of targets supported in sensor f/w */
#endif

#define CH_SPEEDOFSOUND_MPS (343) /*!< Speed of sound, in meters per second. */

#define CH_WINDOW_MAX_SAMPLES (64) /*!< Maximum number of samples in a sample window */

//! Return value codes.
typedef enum { RET_OK = 0, RET_ERR = 1 } ch_retval;

//! Sensor product codes.
typedef enum {
	CH_PROD_CODE_ICU20201 = 1,    /*!< TDK ICU-20201 */
	CH_PROD_CODE_ICU10201 = 2,    /*!< TDK ICU-10201 */
	CH_PROD_CODE_ICU30201 = 3,    /*!< TDK ICU-30201 */
	CH_PROD_CODE_UNKNOWN  = 0xFF, /*!< Unknown product */
} ch_prod_code_t;

//! Sensor asic design generations.
typedef enum {
	CH_ASIC_GEN_1_WHITNEY = 1, /*!< Generation 1 sensors, including CH101 & CH201 */
	CH_ASIC_GEN_2_SHASTA  = 2, /*!< Generation 2 sensors, including ICU-x0201 models */
} ch_asic_gen_t;

//! Range data types.
typedef enum {
	CH_RANGE_ECHO_ONE_WAY    = 0, /*!< One way - gets full pulse/echo distance & divides by 2. */
	CH_RANGE_ECHO_ROUND_TRIP = 1, /*!< Round trip - full pulse/echo distance. */
	CH_RANGE_DIRECT          = 2, /*!< Direct - for receiving node in pitch-catch mode. */
} ch_range_t;

//! Sensor operating modes.
typedef enum {
	CH_MODE_IDLE    = 0x00,           /*!< Idle mode - low-power sleep, no sensing is enabled. */
	CH_MODE_FREERUN = 0x02,           /*!< Free-running mode - sensor uses internal clock to wake
	                                       and measure. */
	CH_MODE_TRIGGERED_TX_RX = 0x10,   /*!< Triggered transmit/receive mode - transmits and receives
	                                       when INT line triggered.*/
	CH_MODE_TRIGGERED_RX_ONLY = 0x20, /*!< Triggered receive-only mode - for pitch-catch operation
	                                      with another sensor. */
	//! Continuous receive mode
	/*! In this mode, the receiver runs continuously. There is no measurement
	 * frame-trigger. Data is double-buffered on the ASIC. The host reads one
	 * buffer while the ASIC writes the other.
	 */
	CH_MODE_CONTINUOUS_RX = 0x40
} ch_mode_t;

//! Sensor group status.
typedef enum ch_group_status {
	CH_GROUP_STAT_NOT_INIT     = 0, /*!< Group not initialized. */
	CH_GROUP_STAT_INIT_PENDING = 1, /*!< Group initialization pending. */
	CH_GROUP_STAT_INIT_OK      = 2  /*!< Group initialized. */
} ch_group_status_t;

//! Measurement status.
typedef enum {
	CH_MEAS_STATUS_UNKNOWN = 0, /*!< Measurement status unknown */
	CH_MEAS_STATUS_INIT    = 1, /*!< Measurement queue initialization pending */
	CH_MEAS_STATUS_TX_OPT  = 2, /*!< Transmit optimization pending. */
	CH_MEAS_STATUS_OK      = 3, /*!< Measurement queue configured. */
	CH_MEAS_STATUS_PENDING = 4, /*!< Measurement is pending. */
	CH_MEAS_STATUS_DONE    = 5, /*!< Measurement done. */
} ch_meas_status_t;

//! Measurement mode (active / standby)
typedef enum {
	CH_MEAS_MODE_ACTIVE  = 0, /*!< Measurement is active (will be performed) */
	CH_MEAS_MODE_STANDBY = 1  /*!< Measurement is in standby mode */
} ch_meas_mode_t;

//! Sensor reset types.
typedef enum {
	CH_RESET_HARD = 0, /*!< Hard reset. */
	CH_RESET_SOFT = 1  /*!< Soft reset. */
} ch_reset_t;

//! Sensor trigger types.
typedef enum {
	CH_TRIGGER_TYPE_HW = 0, /*!< Hardware triggered. */
	CH_TRIGGER_TYPE_SW = 1  /*!< Software triggered. */
} ch_trigger_type_t;

//! Sensor interrupt modes.
typedef enum {
	CH_INTERRUPT_MODE_PULSE = 0, /*!< Pulse mode. */
	CH_INTERRUPT_MODE_LATCH = 1  /*!< Latching mode. */
} ch_interrupt_mode_t;

//! Sensor interrupt drive type
typedef enum {
	CH_INTERRUPT_DRIVE_OPEN_DRAIN = 0, /*!< Open drain type. */
	CH_INTERRUPT_DRIVE_PUSH_PULL  = 1  /*!< Push pull type. */
} ch_interrupt_drive_t;

#ifdef INCLUDE_SHASTA_SUPPORT
//! Sensor interrupt types.
typedef enum {
	CH_INTERRUPT_TYPE_UNKNOWN     = INT_SRC_NONE,            /*!< 0x0000 - Unknown. */
	CH_INTERRUPT_TYPE_DATA_RDY    = INT_SRC_DATA_RDY,        /*!< 0x0001 - Data ready. */
	CH_INTERRUPT_TYPE_MUT_FCOUNT  = INT_SRC_MUT_FCOUNT_RDY,  /*!< 0x0002 - Transducer freq test done. */
	CH_INTERRUPT_TYPE_CPU_FCOUNT  = INT_SRC_CPU_FCOUNT_RDY,  /*!< 0x0004 - CPU freq test done. */
	CH_INTERRUPT_TYPE_BIST_RDY    = INT_SRC_BIST_RDY,        /*!< 0x0008 - Self test done. */
	CH_INTERRUPT_TYPE_TX_OPTIMIZE = INT_SRC_TX_OPTIMIZE,     /*!< 0x0010 - Transmit optimization done. */
	CH_INTERRUPT_TYPE_RTC_CAL_RDY = INT_SRC_RTC_CAL_RDY,     /*!< 0x0020 - RTC calibration done. */
	CH_INTERRUPT_TYPE_OTP_COPY    = INT_SRC_COPY_OTP_TO_RAM, /*!< 0x0080 - One-time-prog mem copied to ram. */
	CH_INTERRUPT_TYPE_OTP_WR_STEP = INT_SRC_OTP_WR_STEP,     /*!< 0x0100 - One-time-prog mem write step done. */
	CH_INTERRUPT_TYPE_WATCHDOG    = INT_SRC_WDT_EXPIRY,      /*!< 0x0400 - Watchdog timer expired. */
	CH_INTERRUPT_TYPE_PGM_LOADED  = INT_SRC_PGM_LOADED,      /*!< 0x0800 - Sensor f/w program loaded. */
	CH_INTERRUPT_TYPE_ALGO_ERROR  = INT_SRC_ALGO_ERROR,      /*!< 0x2000 - Measurement algorithm error. */
	CH_INTERRUPT_TYPE_DEBUG       = INT_SRC_DEBUG,           /*!< 0x4000 - Debug interrupt. */
	CH_INTERRUPT_TYPE_ERROR       = INT_SRC_ERROR            /*!< 0x8000 - Unspecified error. */
} ch_interrupt_type_t;

//! Output type.
typedef enum {
	CH_OUTPUT_IQ         = IQ_OUTPUT_NORMAL,     /*!< (0) - Output I/Q int16_t pair values */
	CH_OUTPUT_AMP_THRESH = IQ_OUTPUT_MAG_THRESH, /*!< (1) - Output amp + threshold uint16_t pair values */
	CH_OUTPUT_AMP        = IQ_OUTPUT_MAG         /*!< (2) - Output amplitude uint16_t values only */
} ch_output_type_t;
#else
//! Sensor interrupt types.(Whitney sensors only have one interrupt type)
typedef enum {
	CH_INTERRUPT_TYPE_UNKNOWN  = 0x0000,
	CH_INTERRUPT_TYPE_DATA_RDY = 0x0001,
} ch_interrupt_type_t;

//! Output type.
typedef enum {
	CH_OUTPUT_IQ  = 0, /*!< Output I/Q int16_t pair values */
	CH_OUTPUT_AMP = 2  /*!< Output amplitude uint16_t values only */
} ch_output_type_t;
#endif

//! Target interrupt filter modes.
typedef enum {
	CH_TGT_INT_FILTER_OFF     = 0, /*!< Target interrupt filter disabled - get int after each meas */
	CH_TGT_INT_FILTER_ANY     = 1, /*!< Interrupt if any target detected, no int if no target */
	CH_TGT_INT_FILTER_COUNTER = 4, /*!< Interrupt if num targets in meas history plus last meas is over threshold */
} ch_tgt_int_filter_t;

#define CH_TARGET_INT_HIST_MAX       (15) /*!< Maximum number of measurements included in target history */
#define CH_TARGET_INT_HIST_DEFAULT   (5)  /*!< Default number of measurements included in target history */
#define CH_TARGET_INT_THRESH_DEFAULT (3)  /*!< Default num targets in history required to interrupt */

//! Sensor output data rate (ODR).
typedef enum {
	CH_ODR_FREQ_DIV_32 = 2,                /*!< Sample output rate = sensor freq / 32 (lowest)  */
	CH_ODR_FREQ_DIV_16 = 3,                /*!< Sample output rate = sensor freq / 16           */
	CH_ODR_FREQ_DIV_8  = 4,                /*!< Sample output rate = sensor freq / 8  (default) */
	CH_ODR_FREQ_DIV_4  = 5,                /*!< Sample output rate = sensor freq / 4            */
	CH_ODR_FREQ_DIV_2  = 6,                /*!< Sample output rate = sensor freq / 2  (highest) */
	CH_ODR_DEFAULT     = CH_ODR_FREQ_DIV_8 /*!< Default sensor output rate */
} ch_odr_t;

//! Sensor real-time clock sources.
typedef enum {
	CH_RTC_SRC_INTERNAL = 0, /*!< Use sensor's internal RTC. */
	CH_RTC_SRC_EXTERNAL = 1  /*!< Use external RTC signal. */
} ch_rtc_src_t;

//! Sensor real-time clock status.
typedef enum {
	CH_RTC_STATUS_INIT          = 0, /*!< Internal RTC not calibrated. */
	CH_RTC_STATUS_CAL_DONE      = 1, /*!< Internal RTC calibrated locally. */
	CH_RTC_STATUS_CAL_FACTORY   = 2, /*!< Internal RTC uses factory calibration value */
	CH_RTC_STATUS_CAL_ESTIMATED = 3, /*!< Internal RTC uses estimate for frequency. */
	CH_RTC_STATUS_CAL_BUS       = 4, /*!< Internal RTC uses estimate based on bus clock rate */
	CH_RTC_STATUS_EXTERNAL      = 5, /*!< Uses external RTC signal as input. */
} ch_rtc_status_t;

#define CH_RTC_USE_BUS_SPEED (UINT16_MAX) /*!< Special value for RTC freq estimate, use I/O bus */

//! Sensor real-time clock status.
typedef enum {
	CH_RTC_CAL_STD    = 0, /*!< Standard RTC calibration using INT pulse. */
	CH_RTC_CAL_MANUAL = 1, /*!< Manual calibration using factory value or estimate. */
	CH_RTC_CAL_BUS    = 2, /*!< RTC calibration uses I/O bus clock. */
} ch_rtc_cal_t;

//! PMUT clock configuration (ICU sensors)
typedef enum {
	CH_PMUT_CLK_DEFAULT = 0, /*!< Standard PMUT clock config - MUTCLK pad disabled. */
	CH_PMUT_CLK_OUTPUT_ENABLE =
			1, /*!< Output PMUT clock signal on MUTCLK. This option forces MUTCLK on regardless of sensor state. */
	CH_PMUT_CLK_SRC_EXTERNAL = 2, /*!< Use external input as PMUT clock source */
	CH_PMUT_CLK_OUTPUT_AUTO =
			3, /*!< Output PMUT clock signal on MUTCLK but allow ICU device to control the power state */
} ch_pmut_clk_cfg_t;

//! I/O blocking mode flags.
typedef enum {
	CH_IO_MODE_BLOCK    = 0, /*!< Blocking mode. */
	CH_IO_MODE_NONBLOCK = 1  /*!< Non-blocking mode. */
} ch_io_mode_t;

//! Decimation factor.
typedef enum {
	CH_DECIMATION_0_25 = -2,
	CH_DECIMATION_0_50 = -1,
	CH_DECIMATION_NONE = 1,
	CH_DECIMATION_2    = 2,
	CH_DECIMATION_3    = 3,
	CH_DECIMATION_4    = 4
} ch_decimation_t;

//! Sensor reset state.
typedef enum { CH_RESET_STATE_OK = 0, CH_RESET_STATE_ACTIVE = 1 } ch_sensor_reset_state_t;

//! Log format.
typedef enum { CH_LOG_FMT_REDSWALLOW = 0 } ch_log_fmt_t;

//! SonicLib version structure.
typedef struct {
	uint8_t major; /*!< Major version */
	uint8_t minor; /*!< Minor version */
	uint8_t rev;   /*!< Revision */
} ch_version_t;

//! I2C info structure.
typedef struct {
	uint8_t address;    /*!< I2C device address */
	uint8_t bus_num;    /*!< I2C bus index */
	uint16_t drv_flags; /*!< flags for special handling by Chirp driver */
} ch_i2c_info_t;

/*!< Flags for special I2C handling by Chirp driver (drv_flags field in ch_i2c_info_t struct) */
#define I2C_DRV_FLAG_RESET_AFTER_NB (0x00000001) /*!< I2C interface needs reset after non-blocking transfer. */
#define I2C_DRV_FLAG_USE_PROG_NB    (0x00000002) /*!< Use programming interface for non-blocking transfer. */

//! Sensor I/Q data value.
typedef struct {
	int16_t q; /*!< Q component of sample */
	int16_t i; /*!< I component of sample */
} ch_iq_sample_t;

//! Sensor combined amplitude + detection threshold sample value.
typedef struct {
	uint16_t thresh; /*!< detection threshold for sample */
	uint16_t amp;    /*!< amplitude of sample */
} ch_amp_thresh_t;

//! Detection threshold value.
typedef struct {
	uint16_t start_sample;
	uint16_t level;
} ch_thresh_t;

//! Calibration result structure.
typedef struct {
	uint16_t dco_period;
	uint16_t rev_cycles;
} ch_cal_result_t;

//! Clock calibration values
typedef struct {
	uint16_t rtc_freq;    /*!< RTC frequency */
	uint16_t pmut_fcount; /*!< PMUT freq count */
	uint16_t pmut_trim;   /*!< PMUT trim code */
	uint8_t cpu_trim;     /*!< CPU trim code */
} ch_clock_cal_t;

//! Combined configuration structure.
typedef struct {
	ch_mode_t mode;                     /*!< operating mode */
	uint16_t max_range;                 /*!< maximum range, in mm */
	uint16_t sample_interval;           /*!< sensing interval, only used in free-running mode */
	ch_tgt_int_filter_t tgt_int_filter; /*!< target interrupt filtering mode */
} ch_config_t;

//! Data output structure.
typedef struct {
	ch_output_type_t output_type;      /*!< output type */
	ch_decimation_t decimation_factor; /*!< decimation factor */
} ch_output_t;

//! Log configuration structure.
typedef struct {
	uint16_t interval_ms;              /*!< interval between samples, in milliseconds */
	ch_output_type_t output_type;      /*!< output type */
	ch_decimation_t decimation_factor; /*!< decimation factor (resolution) of the data. */
	uint16_t start_sample;             /*!< starting sample number within measurement data */
} ch_log_cfg_t;

//! Log data structure.
typedef struct {
	uint8_t tx_sensor_id;         /*!< sensor which is transmitting the ultrasound pulse */
	uint8_t rx_sensor_id;         /*!< sensor which is receiving the ultrasound pulse */
	uint32_t range;               /*!< measured range as a 32-bit integer. From ch_get_range() */
	uint16_t amplitude;           /*!< amplitude value of the measured ultrasound signal. from ch_get_amplitude() */
	uint8_t annotation;           /*!< annotation data added by the users */
	ch_output_type_t output_type; /*!< output type */
	union {
		ch_iq_sample_t *iq_sample_ptr; /*!< pointer to ch_iq_data_t structure containing the I/Q data */
		uint16_t *mag_data_ptr;        /*!< pointer to mag data buffer containing amplitude data */
	} raw_data;
	uint16_t start_sample; /*!< starting sample number within measurement data */
	uint16_t num_samples;  /*!< number of samples to read from sensor */
} ch_log_data_t;

//! Measurement configuration - used during ch_meas_init()
typedef struct {
	ch_odr_t odr;
	uint16_t meas_period;
	ch_meas_mode_t mode;  // 1 if meas initially in standby mode (inactive), 0 if active
} ch_meas_config_t;

#ifdef INCLUDE_SHASTA_SUPPORT
/* Definitions for ICU-x0201 sensors (Shasta architecture) */

#define CH_MEAS_MAX_SEGMENTS (INST_BUF_LENGTH)     /*!< max number of segments in a measurement */
#define CH_MEAS_MAX_MEAS     (MEAS_QUEUE_MAX_MEAS) /*!< max number of measurements in meas queue */

#define CH_SENSOR_ID_LENGTH 8 /*!< length of sensor ID string in bytes: 3 byte lot + 4 byte serial num + null */

//! Measurement segment type
typedef enum {
	CH_MEAS_SEG_TYPE_COUNT = 0,  // must match PMUT cmd values
	CH_MEAS_SEG_TYPE_TX    = 1,
	CH_MEAS_SEG_TYPE_RX    = 2,
	CH_MEAS_SEG_TYPE_EOF   = 3
} ch_meas_seg_type_t;

//! Measurement segment
typedef struct {
	pmut_transceiver_inst_t inst;  // PMUT instruction

} ch_meas_segment_t;

//! Measurement info
typedef struct {
	uint32_t num_cycles;
	uint16_t num_tx_segments;
	uint16_t num_rx_samples;
	uint8_t num_segments; /*!< number of active segments (does not include EOF) */
	ch_odr_t odr;
	uint16_t meas_period; /*!< measurement interval in ticks */
	ch_meas_mode_t mode;  /*!< measurement mode (active or standby) */
} ch_meas_info_t;

//! Measurement segment info
typedef struct {
	ch_meas_seg_type_t type;
	uint16_t num_rx_samples;
	uint16_t num_cycles;
	uint8_t rdy_int_en;
	uint8_t done_int_en;
	uint8_t tx_phase;
	uint8_t tx_pulse_width;
	uint8_t rx_gain;
	uint8_t rx_atten;
} ch_meas_seg_info_t;

//! Measurement queue info
typedef struct {
	uint8_t int_config;    // interrupt pin selection
	uint8_t meas_start;    // which measurement do we start on
	uint8_t meas_stop;     // which measurement do we stop on
	uint8_t current_meas;  // which measurement do we do next
	uint8_t trig_src;      // trigger source: falling edge of INT1 or INT2, or internal timer
	uint8_t last_meas;     // last completed measurement
} ch_meas_queue_info_t;

//! Sensor manufacturing info
typedef struct {
	uint16_t mfg_year;
	uint8_t mfg_week;
	uint8_t mfg_site;
	uint8_t product_code;  // numeric value for product type (e.g. ICU-20201, ICU-10201, etc)
	uint8_t package_code;  // numeric value for package type (e.g. added microcap, changed bondwires)
	uint8_t mems_code;     // numeric value for mems transducer type (e.g. CH101/201/CypressZ1/A1)
	uint8_t module_code;   // numeric value for module type
} ch_mfg_info_t;

#endif  // INCLUDE_SHASTA_SUPPORT

//! API function pointer typedefs.
typedef uint8_t (*ch_get_config_func_t)(ch_dev_t *dev_ptr, ch_config_t *config_ptr);
typedef uint8_t (*ch_set_config_func_t)(ch_dev_t *dev_ptr, ch_config_t *config_ptr);
typedef uint8_t (*ch_set_num_samples_func_t)(ch_dev_t *dev_ptr, uint16_t num_samples);
typedef uint8_t (*ch_set_sample_window_func_t)(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t end_sample);
typedef uint32_t (*ch_get_range_func_t)(ch_dev_t *dev_ptr, ch_range_t range_type);
typedef uint16_t (*ch_get_amplitude_func_t)(ch_dev_t *dev_ptr);
typedef uint16_t (*ch_get_amplitude_avg_func_t)(ch_dev_t *dev_ptr);
typedef uint8_t (*ch_set_frequency_func_t)(ch_dev_t *dev_ptr, uint32_t target_freq_Hz);
typedef uint8_t (*ch_get_iq_data_func_t)(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample,
                                         uint16_t num_samples, ch_io_mode_t io_mode);
typedef uint8_t (*ch_get_amplitude_data_func_t)(ch_dev_t *dev_ptr, uint16_t *buf_ptr, uint16_t start_sample,
                                                uint16_t num_samples, ch_io_mode_t io_mode);
typedef uint16_t (*ch_mm_to_samples_func_t)(ch_dev_t *dev_ptr, uint16_t num_mm);
typedef uint8_t (*ch_set_target_interrupt_func_t)(ch_dev_t *dev_ptr, ch_tgt_int_filter_t tgt_int_filter);
typedef ch_tgt_int_filter_t (*ch_get_target_interrupt_func_t)(ch_dev_t *dev_ptr);
typedef uint8_t (*ch_set_target_int_counter_func_t)(ch_dev_t *dev_ptr, uint8_t meas_hist, uint8_t thresh_count,
                                                    uint8_t reset);
typedef uint8_t (*ch_get_target_int_counter_func_t)(ch_dev_t *dev_ptr, uint8_t *meas_hist_ptr,
                                                    uint8_t *thresh_count_ptr, uint8_t *reset_ptr);
typedef uint8_t (*ch_set_rx_low_gain_func_t)(ch_dev_t *dev_ptr, uint16_t num_samples);
typedef uint16_t (*ch_get_rx_low_gain_func_t)(ch_dev_t *dev_ptr);
typedef uint8_t (*ch_set_tx_length_func_t)(ch_dev_t *dev_ptr, uint16_t tx_length);
typedef uint16_t (*ch_get_tx_length_func_t)(ch_dev_t *dev_ptr);
typedef uint8_t (*ch_set_cal_result_func_t)(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);
typedef uint8_t (*ch_get_cal_result_func_t)(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);
typedef uint8_t (*ch_set_data_output_func_t)(ch_dev_t *dev_ptr, const ch_output_t *output);
typedef void (*ch_trigger_soft_func_t)(ch_dev_t *dev_ptr);
typedef uint8_t (*ch_set_data_ready_delay_func_t)(ch_dev_t *dev_ptr, uint8_t num_cycles);
typedef uint8_t (*ch_get_data_ready_delay_func_t)(ch_dev_t *dev_ptr);
typedef ch_meas_status_t (*ch_meas_get_status_func_t)(ch_dev_t *dev_ptr, uint8_t meas_num);

#ifdef INCLUDE_SHASTA_SUPPORT
typedef ch_output_type_t (*ch_meas_get_iq_output_func_t)(ch_dev_t *dev_ptr, uint8_t meas_num);
typedef uint8_t (*ch_meas_set_iq_output_func_t)(ch_dev_t *dev_ptr, uint8_t meas_num, ch_output_type_t output_format);
#endif

//! API function pointer structure (internal use).
typedef struct {
	ch_set_num_samples_func_t set_num_samples;
	ch_set_sample_window_func_t set_sample_window;
	ch_get_range_func_t get_range;
	ch_get_amplitude_func_t get_amplitude;
	ch_get_amplitude_avg_func_t get_amplitude_avg;
	ch_set_frequency_func_t set_frequency;
	ch_get_iq_data_func_t get_iq_data;
	ch_get_amplitude_data_func_t get_amplitude_data;
	ch_mm_to_samples_func_t mm_to_samples;
	ch_set_target_interrupt_func_t set_target_interrupt;
	ch_get_target_interrupt_func_t get_target_interrupt;
	ch_set_target_int_counter_func_t set_target_int_counter;
	ch_get_target_int_counter_func_t get_target_int_counter;
	ch_set_rx_low_gain_func_t set_rx_low_gain;
	ch_get_rx_low_gain_func_t get_rx_low_gain;
	ch_set_tx_length_func_t set_tx_length;
	ch_get_tx_length_func_t get_tx_length;
	ch_set_cal_result_func_t set_cal_result;
	ch_get_cal_result_func_t get_cal_result;
	ch_set_data_output_func_t set_data_output;
	ch_trigger_soft_func_t trigger_soft;
	ch_set_data_ready_delay_func_t set_data_ready_delay;
	ch_get_data_ready_delay_func_t get_data_ready_delay;
	ch_meas_get_status_func_t meas_get_status;
#ifdef INCLUDE_SHASTA_SUPPORT
	ch_meas_get_iq_output_func_t meas_get_iq_output;
	ch_meas_set_iq_output_func_t meas_set_iq_output;
#endif
	// Range finding specific
	const void *algo_specific_api;
} ch_api_funcs_t;

typedef struct {
	void (*prepare_pulse_timer)(ch_dev_t *dev_ptr); /*!< Pointer to function preparing sensor pulse
	                                                     timer to measure real-time clock (RTC)
	                                                     calibration pulse sent to device. */
	void (*store_pt_result)(ch_dev_t *dev_ptr);     /*!< Pointer to function to read RTC calibration
	                                                     pulse timer result from sensor and place value
	                                                     in the \a rtc_cal_result field. */
	void (*store_op_freq)(ch_dev_t *dev_ptr);       /*!< Pointer to function to read operating
	                                                     frequency and place value in the
	                                                     \a op_frequency field. */
	void (*store_bandwidth)(ch_dev_t *dev_ptr);     /*!< Pointer to function to read operating bandwidth
	                                                     and place value in the \a bandwidth field. */
	void (*store_scalefactor)(ch_dev_t *dev_ptr);   /*!< Pointer to function to calculate ToF scale factor
	                                                     and place value in the \a tof_scalefactor field. */
	uint8_t (*get_locked_state)(ch_dev_t *dev_ptr); /*!< Pointer to function returning locked state
	                                                     for sensor. */
} ch_calib_funcs_t;

struct fw_info_st {
	/* Sensor Firmware-specific Linkage Definitions */
	const char *fw_version_string;          /*!< Pointer to string identifying sensor firmware version. */
	const uint8_t *fw_text;                 /*!< Pointer to start of sensor firmware image text to be loaded */
	const uint8_t *fw_vec;                  /*!< Pointer to start of sensor firmware image vectors to be loaded */
	const uint8_t *ram_init;                /*!< Pointer to ram initialization data */
	uint16_t (*get_fw_ram_init_size)(void); /*!< Pointer to function returning ram init size
	                                             for sensor. */
	uint16_t (*get_fw_ram_init_addr)(void); /*!< Pointer to function returning start address of
	                                             ram initialization area in the sensor. */
	/* Functions used for sensor calibration */
	const ch_calib_funcs_t *const calib_funcs;
	/* API and callback functions */
	const ch_api_funcs_t *const api_funcs; /*!< Structure containing API function pointers. */
	uint16_t fw_text_size;                 /*!< Size of sensor firmware image text */
	uint16_t fw_vec_size;                  /*!< Size of sensor firmware interrupt vectors */

	uint16_t max_samples;             /*!< Maximum number of receiver samples for this sensor firmware */
	const uint16_t freqCounterCycles; /*!< Frequency counter cycles */
	const uint8_t freqLockValue;      /*!< Value set when sensor has locked */
	const int8_t oversample;          /*!< Oversampling factor (power of 2) */
	const uint8_t max_num_thresholds; /*!< Maximum number of detection thresholds for this sensor firmware */
	/* Sensor Firmware infos */
	const uint8_t fw_includes_sensor_init : 1;     /*!< If set, the firmware is able to initialize sensor hardware */
	const uint8_t fw_includes_tx_optimization : 1; /*!< If set, the firmware is able to run tx optimization */
	const uint8_t reserved : 6;
};

//! ASIC firmware init function pointer typedef.
typedef uint8_t (*ch_fw_init_func_t)(ch_dev_t *dev_ptr, fw_info_t **fw_info);

//! Sensor interrupt callback routine pointer.
typedef void (*ch_io_int_callback_t)(ch_group_t *grp_ptr, uint8_t io_index, ch_interrupt_type_t int_type);

//! Non-blocking I/O complete callback routine pointer.
typedef void (*ch_io_complete_callback_t)(ch_group_t *grp_ptr);

//! Periodic timer callback routine pointer.
typedef void (*ch_timer_callback_t)(void);

//!  Chirp sensor group descriptor structure.

/*! \note The \a CHIRP_MAX_NUM_SENSORS and \a CHIRP_NUM_BUSES symbols must be defined
 * by the user.  Normally this is done in the \b chirp_board_config.h header file that is
 * part of the board support package.
 */
struct ch_group_t {
	ch_group_status_t status;                       /*!< Group initialization status */
	uint8_t num_ports;                              /*!< Number of ports (max possible sensor connections) */
	uint8_t sensor_int_pin;                         /*!< Sensor interrupt pin (1 or 2) */
	uint8_t sensor_trig_pin;                        /*!< Sensor h/w trigger pin (1 or 2) */
	uint8_t num_buses;                              /*!< Number of SPI/I2C buses on this board */
	uint8_t sensor_count;                           /*!< Number of sensors detected */
	ch_rtc_cal_t rtc_cal_type;                      /*!< Type of RTC calibration used by sensors */
	uint32_t op_frequency;                          /*!< group nominal acoustic operating freq, if set */
	uint32_t pmut_clock_freq;                       /*!< group PMUT clock frequency, if used (16 x op freq) */
	uint32_t io_bus_speed_hz;                       /*!< I/O bus speed, in Hz */
	uint16_t i2c_drv_flags;                         /*!< Flags for special I2C handling by Chirp driver, from
	                                                     \a chbsp_get_i2c_info()*/
	uint16_t rtc_cal_pulse_ms;                      /*!< Real-time clock calibration pulse length (in ms) */
	uint16_t pretrig_delay_us;                      /*!< Pre-trigger delay for rx-only sensors (in us) */
	ch_io_int_callback_t io_int_callback;           /*!< Addr of routine to call when sensor interrupts */
	ch_io_complete_callback_t io_complete_callback; /*!< Addr of routine to call when non-blocking I/O
	                                                     completes */
	ch_dev_t *device[CHIRP_MAX_NUM_SENSORS];        /*!< Array of pointers to ch_dev_t structures for
	                                                     individual sensors */
#ifdef INCLUDE_WHITNEY_SUPPORT
	uint8_t num_connected[CHIRP_NUM_BUSES]; /*!< Array of counters for connected sensors per bus */
#endif
	chdrv_queue_t queue[CHIRP_NUM_BUSES]; /*!< Array of SPI/I2C non-blocking transaction
	                                                   queues (one per bus) */
};

//! Chirp sensor device descriptor structure.
struct ch_dev_t {
	ch_group_t *group; /*!< Pointer to parent group structure. */
#ifdef INCLUDE_SHASTA_SUPPORT
	char id_string[CH_SENSOR_ID_LENGTH]; /*! Sensor ID string: 3 byte lot + 4 byte serial num + null */
	shasta_config_t *sens_cfg_addr;      /*!< Address of sensor shared config mem */
#endif
	ch_asic_gen_t asic_gen;         /*!< Sensor asic design generation. */
	ch_mode_t mode;                 /*!< Sensor operating mode. */
	uint16_t max_range;             /*!< Maximum range, in mm */
	uint16_t static_range;          /*!< Static target rejection range, in samples (0 if unused) */
	uint32_t freerun_intvl_us;      /*!< Measurement interval (in microsec), if in free-running mode */
	ch_rtc_status_t rtc_status;     /*!< Sensor real-time clock status */
	uint16_t rtc_cal_result;        /*!< Real-time clock calibration result for the sensor. */
	ch_pmut_clk_cfg_t pmut_clk_cfg; /*!< PMUT clock input/output configuration */
	uint32_t orig_pmut_freq;        /*!< Starting PMUT frequency */
	uint32_t op_frequency;          /*!< Operating acoustic frequency for the sensor. */
	uint32_t cpu_frequency;         /*!< CPU frequency for the sensor. */
	uint16_t rtc_frequency;         /*!< Internal real-time-clock frequency for the sensor. */
#ifdef INCLUDE_SHASTA_SUPPORT
	uint16_t fcount_cycles;     /*!< freq count cycles */
	uint16_t pmut_clock_fcount; /*!< raw PMUT count from freq calculation */
	uint8_t cpu_trim;           /*!< CPU clock freq trim value */
	uint16_t pmut_trim;         /*!< PMUT freq trim value */
#endif
	uint16_t bandwidth;        /*!< Bandwidth for the sensor. */
	uint16_t amp_scale_factor; /*!< Amplitude scale factor. */
	uint16_t tof_scale_factor; /*!< Time-of-flight scale factor. */
#ifdef INCLUDE_WHITNEY_SUPPORT
	uint8_t i2c_address;     /*!< Current I2C addresses. */
	uint8_t app_i2c_address; /*!< Assigned application I2C address for device in normal operation*/
	uint16_t i2c_drv_flags;  /*!< Flags for special I2C handling by Chirp driver */
#endif
	uint8_t bus_index;         /*!< Index value identifying which SPI/I2C bus is used for this device. */
	uint16_t part_number;      /*!< Integer part number (e.g. 101 for a CH101 device). */
	uint8_t sensor_connected;  /*!< Sensor connection status:
	                                1 if discovered and successfully initialized, 0 otherwise. */
	uint8_t io_index;          /*!< Index value (device number) identifying device within group */
	uint16_t num_rx_samples;   /*!< Number of receiver samples for the current max range setting. */
	uint16_t win_start_sample; /*!< Starting sample of sample window, if supported */
	uint16_t num_win_samples;  /*!< Number of samples in sample window, if supported */

	ch_meas_status_t meas_status;       /*!< Sensor measurement status */
	ch_trigger_type_t trig_type;        /*!< Sensor triggering type (hardware or software) */
	ch_interrupt_mode_t int_mode;       /*!< Sensor interrupt mode (pulse or latching) */
	ch_interrupt_drive_t int_drive;     /*!< Sensor interrupt drive type (open drain or push pull) */
	ch_tgt_int_filter_t tgt_int_filter; /*!< Target interrupt filter mode */
	fw_info_t *main_fw_info;            /*!< Pointer to firmware infos for main/application firmware */
	fw_info_t *current_fw;              /*!< Pointer on firmware currently used by sensor */
#ifdef INCLUDE_SHASTA_SUPPORT
	fw_info_t *init_fw_info;       /*!< Pointer to firmware infos for initialization firmware (if necessary) */
	uint8_t main_fw_init_done;     /*!< Flag to indicate if main/application firmware have been initialized */
	uint8_t asic_ready;            /*!< Indicates ASIC is ready for commands */
	ch_clock_cal_t test_clock_cal; /*!< Clock calibration values from factory test */

	int16_t data_validation_counter; /*!< Counter value for data validation */
	int16_t mq_sanitize_enabled;     /* !< Perform mq sanitization step when non-zero */

	uint8_t reg_fmt_ver_major; /*!< SW defined register format major version */
	uint8_t reg_fmt_ver_minor; /*!< SW defined register format minor version */

	/* Sensor measurement queue */
	measurement_queue_t meas_queue; /*!< Sensor measurement queue (local copy) */

	uint8_t meas_num_segments[CH_MEAS_MAX_MEAS];      // number of active segments per measurement
	uint32_t meas_num_cycles[CH_MEAS_MAX_MEAS];       // total number of sensor cycles per measurement
	uint16_t meas_num_tx_segments[CH_MEAS_MAX_MEAS];  // total number of transmit segments per measurement
	uint16_t meas_pre_rx_cycles[CH_MEAS_MAX_MEAS];    // total number of sensor cycles in segments before first read
	uint16_t meas_num_rx_samples[CH_MEAS_MAX_MEAS];   // total number of receive samples per measurement
	uint16_t meas_max_range_mm[CH_MEAS_MAX_MEAS];     // max range setting based on num_rx_samples (millimeters)

	uint8_t last_measurement; /*!< Number of last completed measurement */
	uint8_t is_continuous;    /*!< 1 if last meas was continuous mode */
	uint8_t odr_out;          /*!< Output ODR used in last measurement */
	uint8_t iq_output_format; /*!< I/Q output format in last measurement */
	uint16_t num_iq_bytes;    /*!< Number of valid I/Q bytes in last measurement */
	uint16_t buf_addr;        /*!< Address of buffer containing the raw data */

	/* Sensor algorithm */
	ICU_ALGO_SHASTA_INFO *sens_algo_info_addr; /*!< Algorithm info addr on sensor */
	ICU_ALGO_SHASTA_INFO algo_info;            /*!< Sensor algorithm information (copy) */
	void *algo_cfg_ptr; /*!< Sensor algorithm config pointer (might be initialized by some fw interfaces) */

#endif  // INCLUDE_SHASTA_SUPPORT
};

/*==============  API function prototypes and documentation ===================*/

/*!
 * \brief Initialize the group descriptor for a group of sensors.
 *
 * \param grp_ptr 			pointer to the ch_group_t descriptor for sensor group to join
 * \param num_devices		number of the device within the sensor group
 * \param num_devices		number of the buses the sensors use
 * \param rtc_cal_pulse_ms	Length of the pulse used to calibrate the sensors RTC
 *
 * \return 0 if success, 1 if error
 *
 * This function is used to initialize few group structure field before initializing sensors
 *
 * Generally, an application will require only one ch_group_t structure to manage all Chirp sensors.
 *
 * \note This function only performs internal initialization of data structures, etc.  It does not
 * actually initialize the physical sensor device(s).  See \a ch_group_start(), \a ch_restart(),
 * and \a ch_group_restart().
 */
uint8_t ch_group_init(ch_group_t *grp_ptr, uint8_t num_devices, uint8_t num_buses, uint16_t rtc_cal_pulse_ms);

/*!
 * \brief Initialize the device descriptor for a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param grp_ptr 		pointer to the ch_group_t descriptor for sensor group to join
 * \param dev_num		number of the device within the sensor group (identifies which physical sensor)
 * \param fw_init_func 	pointer to the sensor firmware initialization function (determines sensor
 *                     	feature set)
 *
 * \return 0 if success, 1 if error
 *
 * This function is used to initialize various Chirp SonicLib structures before using a sensor.
 * The ch_dev_t device descriptor is the primary data structure used to manage a sensor, and its
 * address will subsequently be used as a handle to identify the sensor when calling most API functions.
 *
 * The \a dev_ptr parameter is the address of the ch_dev_t descriptor structure that will be initialized
 * and then used to identify and manage this sensor. The \a grp_ptr parameter is the address of a
 * ch_group_t structure describing the sensor group that will include the new sensor.  Both the ch_dev_t
 * structure and the ch_group_t structure must have already been allocated before this function is called.
 *
 * A separate ch_dev_t structure must be allocated for each sensor.
 *
 * \a dev_num is a simple index value that uniquely identifies a sensor within a group.  Each possible
 * sensor (i.e. each physical port on the board that could have a Chirp sensor attached) has a number,
 * starting with zero (0).  The device number is constant - it remains associated with a specific port
 * even if no sensor is actually attached.  Often, the \a dev_num value is used by both the
 * application and the board support package as an index into arrays containing per-sensor
 * information (e.g. data read from the sensors, pin assignments, etc.).
 *
 * The Chirp sensor is fully re-programmable, and the specific features and capabilities can be modified
 * by using different sensor firmware images.  The \a fw_init_func parameter is the address (name) of
 * the sensor firmware initialization routine that should be used to program the sensor and prepare it
 * for operation. The selection of this routine name is the only required change when switching from
 * one sensor firmware image to another.
 *
 * \note This function only performs internal initialization of data structures, etc.  It does not
 * actually initialize the physical sensor device(s).  See \a ch_group_start(), \a ch_restart(),
 * and \a ch_group_restart().
 */
uint8_t ch_init(ch_dev_t *dev_ptr, ch_group_t *grp_ptr, uint8_t dev_num, ch_fw_init_func_t fw_init_func);

/*!
 * \brief Initialize the init firmware to use for a sensor.
 *
 * \param dev_ptr      pointer to the ch_dev_t descriptor structure
 * \param fw_init_func pointer to the sensor init firmware initialization function
 *
 * \return 0 if success, 1 if error
 *
 * This function is used to define the init firmware for a sensor if the main firwmware (determined with ch_init)
 * doesn't have initialization features in it.
 * It can be necessary to set a specific initialization firmware (with tx optimization) if using measure optimization
 * API.
 *
 * \note This function only performs internal initialization of data structures, etc. It does not
 * actually initialize the physical sensor device(s).  See \a ch_group_start(), \a ch_restart(),
 * \a ch_group_restart() and \a ch_meas_optimize().
 */
uint8_t ch_set_init_firmware(ch_dev_t *dev_ptr, ch_fw_init_func_t fw_init_func);

/*!
 * \brief	Program and start a group of sensors.
 *
 * \param	grp_ptr pointer to the ch_group_t descriptor for sensor group to be started
 *
 * \return 0 if successful, 1 if error
 *
 * This function performs the actual discovery, programming, and initialization sequence for all sensors
 * within a sensor group.  Each sensor must have previously been added to the group by calling
 * \a ch_init().
 *
 * In brief, this function does the following for each sensor:
 * - Probe the possible sensor ports using SPI/I2C bus and each sensor's PROG line, to discover if sensor
 *   is connected.
 * - Reset sensor.
 * - Program sensor with firmware (version specified during \a ch_init()).
 * - For CH101/CH201 sensors only, assign unique I2C address to sensor (specified by board support package,
 *   see \a chbsp_i2c_get_info()).
 * - Start sensor execution.
 * - Wait for sensor to lock (complete initialization, including self-test).
 * - Send timed pulse on INT line to calibrate sensor Real-Time Clock (RTC).
 *
 * After this routine returns successfully, the sensor configuration may be set and ultrasonic
 * measurements may begin.
 *
 * See also \a ch_init(), \a ch_restart(), \a ch_group_restart().
 *
 * \note
 * When the sensor is programmed, the entire sensor firmware image is normally written in a
 * single, large SPI/I2C transfer.  To limit the size of this transfer for a specific hardware platform,
 * define the \b MAX_PROG_XFER_SIZE symbol in the \b chirp_board_config.h header file.  For more
 * information, see chirp_bsp.h.
 */
uint8_t ch_group_start(ch_group_t *grp_ptr);

/*!
 * \brief	Restart a sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if successful, 1 if error
 *
 * This function performs a re-start of a sensor that has previously been initialized
 * and started.  The sensor is reset, the sensor firmware is reloaded, and the configuration
 * settings are re-applied.  The sensor will not perform the normal calibration
 * steps (including clock calibration) - it will instead use the values saved during
 * a previous initialization.
 *
 * Normally, this function should not be needed.  It may be useful for special
 * error handling or other application-specific requirements.
 *
 * Different sensor firmware can be loaded, by calling \a ch_init() before this
 * function and specifying a new firmware init routine.  This is normally not recommended
 * for applications, but this mechanism is sometimes used internally by SonicLib.
 *
 * After this routine returns successfully, the sensor should be ready to resume
 * measurements.
 *
 * See also \a ch_group_restart(), \a ch_group_start().
 */
uint8_t ch_restart(ch_dev_t *dev_ptr);

/*!
 * \brief	Restart a group of sensors.
 *
 * \param	grp_ptr pointer to the ch_group_t descriptor for sensor group to be restarted
 *
 * \return 0 if successful, 1 if error
 *
 * This function performs a re-start of a group of sensors that have previously been initialized
 * and started.
 *
 * Each sensor will be reprogrammed with firmware (as specified in the most recent call to
 * \a ch_init()) and then will be started and configured.  The sensors will not perform
 * the normal calibration steps (including clock calibration) - they will instead use the
 * values saved by a previous initialization.
 *
 * After this routine returns successfully, the sensors should be ready to resume
 * measurements.
 *
 * See also \a ch_restart(), \a ch_group_start().
 */
uint8_t ch_group_restart(ch_group_t *grp_ptr);

/*!
 * \brief Get current configuration settings for a sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param	config_ptr	pointer to a ch_config_t structure to receive configuration values
 *
 * \return 0 if successful, 1 if error
 *
 * This function obtains the current configuration settings from the sensor and returns them
 * in a ch_config_t structure, whose address is specified by \a config_ptr.
 *
 * \note The individual configuration values returned in the ch_config_t structure may also be
 * obtained by using dedicated single-value functions.  See \a ch_get_mode(), \a ch_get_max_range(),
 * \a ch_get_freerun_interval(), \a ch_get_static_range(), and \a ch_get_thresholds().
 */
uint8_t ch_get_config(ch_dev_t *dev_ptr, ch_config_t *config_ptr);

/*!
 * \brief Set multiple configuration settings for a sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param	config_ptr	pointer to a ch_config_t structure containing new configuration values
 *
 * \return 0 if successful, 1 if error
 *
 * This function sets multiple configuration options within the sensor.  The configuration settings
 * are passed in a ch_config_t structure, whose address is specified by \a config_ptr.  The fields
 * in the ch_config_t structure must have been set with your new configuration values before this
 * function is called.
 *
 * \note The individual configuration values set by this function may also be set using dedicated
 * single-value functions. These two methods are completely equivalent and may be freely mixed.
 * See \a ch_set_mode(), \a ch_set_max_range(), \a ch_set_freerun_interval(), \a ch_set_static_range(),
 * \a ch_set_thresholds(), and \a ch_set_target_interrupt().
 */
uint8_t ch_set_config(ch_dev_t *dev_ptr, ch_config_t *config_ptr);

/*!
 * \brief Trigger a measurement on one sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * This function generates a pulse on the INT line for a single sensor.  If the sensor is in either
 * \a CH_MODE_TRIGGERED_TX_RX or \a CH_MODE_TRIGGERED_RX_ONLY mode, this pulse will begin a measurement
 * cycle.
 *
 * To simultaneously trigger all sensors in a group, use \a ch_group_trigger().
 *
 * \note Do not trigger a new measurement until the previous measurement has completed and all needed
 * data has been read from the device (including I/Q data, if \a ch_get_iq_data() is used).  If any
 * I/O operations are still active, the new measurement may be corrupted.
 */
void ch_trigger(ch_dev_t *dev_ptr);

/*!
 * \brief Trigger a measurement on a group of sensors.
 *
 * \param	grp_ptr 	pointer to the ch_group_t descriptor for this group of sensors
 *
 * This function generates a pulse on the INT line for each sensor in the sensor group.  If a sensor is
 * in either \a CH_MODE_TRIGGERED_TX_RX or \a CH_MODE_TRIGGERED_RX_ONLY mode, this pulse will begin a
 * measurement cycle.
 *
 * If a two or more sensors are operating in pitch-catch mode (in which one transmits and the others
 * receive), this function must be used to start a measurement cycle, so that the devices are
 * synchronized.
 *
 * To trigger a single sensor, use \a ch_trigger().
 *
 * \note Do not trigger a new measurement until the previous measurement has completed and all needed
 * data has been read from the device (including I/Q data, if \a ch_get_iq_data() is used).  If any
 * I/O operations are still active, the new measurement may be corrupted.
 */
void ch_group_trigger(ch_group_t *grp_ptr);

/*!
 * \brief Reset a sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param	reset_type	type of reset (\a CH_RESET_HARD or \a CH_RESET_SOFT)
 *
 * This function resets a sensor.  The \a reset_type parameter indicates if a software reset or
 * full hardware reset is requested.
 */
void ch_reset(ch_dev_t *dev_ptr, ch_reset_t reset_type);

/*!
 * \brief Reset a group of sensors.
 *
 * \param	grp_ptr 	pointer to the ch_group_t descriptor for this group of sensors
 * \param	reset_type	type of reset (\a CH_RESET_HARD or \a CH_RESET_SOFT)
 *
 * This function resets all sensors in a sensor group.  The \a reset_type parameter indicates if a
 * software reset or full hardware reset is requested.
 */
void ch_group_reset(ch_group_t *grp_ptr, ch_reset_t reset_type);

/*!
 * \brief	Indicate if a sensor is connected.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 	1 if the sensor is connected, 0 otherwise
 */
uint8_t ch_sensor_is_connected(ch_dev_t *dev_ptr);

/*!
 * \brief	Get part number for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 	Integer part number
 *
 * This function returns the TDK/Chirp part number for the specified device.  The
 * part number is a simple integer value, for example 101 for a CH101 sensor,
 * or 20201 for an ICU20201 sensor.
 */
uint16_t ch_get_part_number(ch_dev_t *dev_ptr);

/*!
 * \brief	Get device number (I/O index values) for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 	Device number
 *
 * This function returns the device number (I/O index) of the sensor within its sensor group.
 * Normally, this also corresponds to the sensor's port number on the board, and is used for
 * indexing arrays of pin definitions etc. within the board support package routines.
 */
uint8_t ch_get_dev_num(ch_dev_t *dev_ptr);

/*!
 * \brief	Get device descriptor pointer for a sensor.
 *
 * \param	grp_ptr 	pointer to the ch_group_t descriptor for this group of sensors
 * \param	dev_num		device number within sensor group
 *
 * \return 	Pointer to ch_dev_t descriptor structure
 *
 * This function returns the address of the ch_dev_t device descriptor for a certain sensor in
 * a sensor group.  The sensor is identified within the group by the \a dev_num device number.
 */
ch_dev_t *ch_get_dev_ptr(ch_group_t *grp_ptr, uint8_t dev_num);

/*!
 * \brief	Get the total number of sensor ports (possible sensors) in a sensor group.
 *
 * \param	grp_ptr 	pointer to the ch_group_t descriptor for this group of sensors
 *
 * \return 	Total number of ports (possible sensors) in the sensor group
 *
 * This function returns the maximum number of possible sensors within a sensor group.  Typically,
 * the number of sensors is limited by the physical connections on the board being used, so the
 * number of sensor ports on the board is returned by this function.
 */
uint8_t ch_get_num_ports(ch_group_t *grp_ptr);

/*!
 * \brief	Get the active I2C address for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return	I2C address, or 0 if error
 *
 * This function returns the currently active I2C address for a CHx01 sensor device.  This function
 * may be used by board support package routines to determine the proper I2C address to use for
 * a specified sensor.
 *
 * Zero is returned if this function is called for ICU sensors, which use a SPI bus interface.
 */
uint8_t ch_get_i2c_address(ch_dev_t *dev_ptr);

/*!
 * \brief	Get the active SPI/I2C bus for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return	SPI/I2C bus index
 *
 * This function returns the SPI/I2C bus index for a sensor device.  This function
 * may be used by board support package routines to determine the proper SPI/I2C bus to use for
 * a specified sensor.
 */
uint8_t ch_get_bus(ch_dev_t *dev_ptr);

/*!
 * \brief	Get the SonicLib version number.
 *
 * \param 	version_ptr 	pointer to a ch_version_t structure to receive version
 *
 * This function fills the fields in the \a ch_version_t structure identified by
 * \a version_ptr with the SonicLib version number.
 *
 * The version number consists of three x.y.z fields: <major>.<minor>.<rev>
 *
 * - \a Major versions are infrequent architectural releases that may include
 * fundamental changes to interfaces and other compatiblity issues.
 * - \a Minor releases introduce new features and may include minor changes to
 * individual interfaces, but are generally backwards compatible.
 * - \a Revision releases include bug fixes and other changes that do not
 * affect public interfaces.
 */
void ch_get_version(ch_version_t *version_ptr);

/*!
 * \brief	Get the firmware version description string for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 	Pointer to character string describing sensor firmware version
 *
 * This function returns a pointer to a string that describes the sensor firmware being used
 * on the device.
 */
const char *ch_get_fw_version_string(ch_dev_t *dev_ptr);

/*!
 * \brief	Get the current operating mode for a sensor.
 *
 * \param	dev_ptr 	pointer to the ch_dev_t config structure
 *
 * \return	Sensor operating mode
 *
 * This function returns the current operating mode for the sensor, one of:
 *	- \a CH_MODE_IDLE - low power idle mode, no measurements take place
 *	- \a CH_MODE_FREERUN - free-running mode, sensor uses internal clock to wake and measure
 *	- \a CH_MODE_TRIGGERED_TX_RX - hardware-triggered, sensor both transmits and receives
 *	- \a CH_MODE_TRIGGERED_RX_ONLY - hardware triggered, sensor only receives
 */
ch_mode_t ch_get_mode(ch_dev_t *dev_ptr);

/*!
 * \brief Configure a sensor for the specified operating mode.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param mode 		the new operating mode for the sensor
 * \return 0 if successful.
 *
 * This function sets the sensor to operate in the specified mode, which
 * must be one of the following:
 *	- \a CH_MODE_IDLE - low power idle mode, no measurements take place
 *	- \a CH_MODE_FREERUN - free-running mode, sensor uses internal clock to wake and measure
 *	- \a CH_MODE_TRIGGERED_TX_RX - hardware-triggered, sensor both transmits and receives
 *	- \a CH_MODE_TRIGGERED_RX_ONLY - hardware triggered, sensor only receives
 *	- \a CH_MODE_CONTINUOUS_RX - (ICU parts only) In this mode, the sensor
 *	     receives continuously. There is no frame-based trigger. Receive samples
 *	     are double-buffered. While the host is reading one buffer, the sensor
 *	     is writing new samples into the other buffer.
 */
uint8_t ch_set_mode(ch_dev_t *dev_ptr, ch_mode_t mode);

/*!
 * \brief Get the internal sensing timing interval for a sensor (deprecated).
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 			Interval between samples (in ms), or 0 if device is not in free-running mode
 *
 * \note This function is DEPRECATED and is provided only for backwards compatiblity.  New
 * applications should use the equivalent \a ch_get_freerun_interval() function.
 *
 * This function returns the interval between measurements, in milliseconds, for
 * a sensor operating in free-running mode.  If the sensor is in a different operating
 * mode (e.g. a triggered mode), zero is returned.
 */
uint16_t ch_get_sample_interval(ch_dev_t *dev_ptr);

/*!
 * \brief Get the internal sensing timing interval for a sensor, in milliseconds.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 			Interval between samples (in ms), or 0 if device is not in free-running mode
 *
 * This function returns the interval between measurements, in milliseconds, for
 * a sensor operating in free-running mode.  If the sensor is in a different operating
 * mode (e.g. a triggered mode), zero is returned.
 *
 * See also \a ch_get_freerun_interval_us(), \a ch_get_freerun_interval_ticks().
 */
uint16_t ch_get_freerun_interval(ch_dev_t *dev_ptr);

/*!
 * \brief Get the internal sensing timing interval for a sensor, in microseconds.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 			Interval between samples (in ms), or 0 if device is not in free-running mode
 *
 * This function returns the interval between measurements, in milliseconds, for
 * a sensor operating in free-running mode.  If the sensor is in a different operating
 * mode (e.g. a triggered mode), zero is returned.
 *
 * See also \a ch_get_freerun_interval_us(), \a ch_get_freerun_interval_ticks().
 */
uint32_t ch_get_freerun_interval_us(ch_dev_t *dev_ptr);

/*!
 * \brief Get the internal sensing timing interval for a sensor, in RTC clock ticks.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \return 			Interval between measurements (in sensor RTC clock periods), or 0
 * 					if device is not in free-running mode
 *
 * This function returns the interval between measurements, in sensor RTC clock
 * periods, for a sensor operating in free-running mode.  If the sensor is in a
 * different operating mode (e.g. a triggered mode), zero is returned.
 *
 * See also \a ch_get_freerun_interval_us(), \a ch_get_freerun_interval_ticks().
 */
uint16_t ch_get_freerun_interval_ticks(ch_dev_t *dev_ptr);

/*!
 * \brief Set the internal sensing interval (deprecated).
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param interval_ms 	interval between samples, in milliseconds.
 * \return 0 if successful, 1 if arguments are invalid.
 *
 * \note This function is DEPRECATED and is provided for backwards compatibility
 * only.  New applications should use the equivalent \a ch_set_freerun_interval()
 * function.
 *
 * This function sets the sample interval for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal clock to wake and perform a
 * measurement every \a interval_ms milliseconds.  A value of zero for \a interval_ms
 * is not valid.
 */
uint8_t ch_set_sample_interval(ch_dev_t *dev_ptr, uint16_t interval_ms);

/*!
 * \brief Set the internal sensing interval for freerunning mode, in milliseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param interval_ms 	interval between samples, in milliseconds.
 * \return 0 if successful, 1 if arguments are invalid.
 *
 * This function sets the sample interval for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal clock to wake and perform a
 * measurement every \a interval_ms milliseconds.  A value of zero for \a interval_ms
 * is not valid.
 *
 * To set the sensing interval with greater precision, use \a ch_set_freerun_interval_us()
 * or \a ch_set_freerun_interval_ticks().
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes.
 * The sample interval for a triggered device is determined by the external trigger timing.
 *
 * See also \a ch_get_freerun_interval(), \a ch_set_freerun_interval_us(),
 * \a ch_set_sense_interval_cycles().
 */
uint8_t ch_set_freerun_interval(ch_dev_t *dev_ptr, uint16_t interval_ms);

/*!
 * \brief Set the internal sensing interval for freerunning mode, in microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param interval_us 	interval between samples, in microseconds.
 * \return 0 if successful, 1 if arguments are invalid.
 *
 * This function sets the sample interval for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal clock to wake and perform a
 * measurement every \a interval_us microseconds.  A value of zero for \a interval_us
 * is not valid.
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes.
 * The sample interval for a triggered device is determined by the external trigger timing.
 *
 * See also \a ch_get_freerun_interval_us(), \a ch_set_freerun_interval(),
 * \a ch_set_freerun_interval_ticks().
 */
uint8_t ch_set_freerun_interval_us(ch_dev_t *dev_ptr, uint32_t interval_us);

/*!
 * \brief Set the internal sensing interval for freerunning mode, in RTC clock ticks.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param interval_ticks 	interval between samples, in sensor RTC clock periods
 * \return 0 if successful, 1 if arguments are invalid.
 *
 * This function sets the sample interval for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal real-time clock (RTC) to wake
 * and perform a measurement every \a interval_ticks clock periods.  A value of zero
 * for \a interval_ticks is not valid.
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes.
 * The sample interval for a triggered device is determined by the external trigger timing.
 *
 * See also \a ch_get_freerun_interval_ticks(), \a ch_set_freerun_interval(),
 * \a ch_set_freerun_interval_us().
 */
uint8_t ch_set_freerun_interval_ticks(ch_dev_t *dev_ptr, uint32_t interval_ticks);

/*!
 * \brief Enable time-hopping on measure period freerunning mode.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \return 0 if successful.
 *
 * This function enables the time-hopping for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal real-time clock (RTC) to wake
 * and perform a measurement every \a measure interval plus a random delay to
 * avoid coexistence with other sensors. Mean measure period is however equals to
 * \a measure interval.
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes.
 *
 * See also \a ch_freerun_time_hop_disable(), \a ch_get_freerun_interval_ticks(),
 * \a ch_set_freerun_interval(), \a ch_set_freerun_interval_us(),
 * \a ch_set_freerun_interval_ticks().
 */
uint8_t ch_freerun_time_hop_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Disable time-hopping on measure period freerunning mode
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \return 0 if successful.
 *
 * This function disable the time-hopping for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes
 *
 * See also \a ch_freerun_time_hop_enable(), \a ch_get_freerun_interval_ticks(),
 * \a ch_set_freerun_interval(), \a ch_set_freerun_interval_us(),
 * \a ch_set_freerun_interval_ticks().
 */
uint8_t ch_freerun_time_hop_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Get the number of samples per measurement cycle.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor struct
 *
 * \return  Number of samples per measurement cycle
 *
 * This function returns the configured number of samples which the Chirp sensor will obtain
 * during each measurement cycle.  The number of samples directly corresponds to the
 * range at which the sensor can detect, so this value is determined by the current maximum
 * range setting for the sensor.
 *
 * For ICU sensors, this function always returns the configured value for the last completed
 * measurement.  To specify which measurement to indicate, use the \a ch_meas_get_num_samples()
 * function.
 *
 * ICU sensors can report the number of output samples directly.  To obtain the number of
 * samples in the last measurement as reported by the sensor itself, use
 * \a ch_get_num_output_samples().  Normally, this will be the same as the configured value
 * reported by this routine.
 *
 *  See also \a ch_set_num_samples, \a ch_meas_get_num_samples, \a ch_get_max_range().
 */
uint16_t ch_get_num_samples(ch_dev_t *dev_ptr);

/*!
 * \brief Set the sensor sample count directly.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor struct
 * \param num_samples 	number of samples during each measurement cycle
 *
 * \return 0 if successful
 *
 * This function directly sets the number of samples which the Chirp sensor will perform
 * during a single measurement cycle.  The number of samples directly corresponds to the
 * range at which the sensor can detect.
 *
 * For ICU sensors, note that this function changes the number of samples in an existing
 * measurement.  The existing measurement definition will be shortened or extended
 * to match the new sample count.  If the measurement is extended, the new samples
 * will use the same settings as in the final receive segment.
 * This function always controls the default measurement definition.  To
 * specify which measurement to modify, use the \a ch_meas_set_num_samples() function.
 *
 * \note Often, the sample is count is not set using this function, but is instead set
 * indirectly using \a ch_set_max_range(), which will automatically set the sample
 * count based on a specified range in millimeters.
 *
 * See also \a ch_set_max_range(), \a ch_get_num_samples().
 */
uint8_t ch_set_num_samples(ch_dev_t *dev_ptr, uint16_t num_samples);

/*!
 * \brief Get the maximum possible sample count per measurement.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor struct
 *
 * \return  Maximum sample count for this device and firmware
 *
 * This function returns the maximum number of samples that can be included in a measurement.
 * This maximum sample count will vary depending on the sensor device (CH201 devices will
 * have higher sample counts than CH101 devices) and by the specific sensor firmware
 * that is being used.
 *
 * To get the number of these possible samples that are currently active (based on the maximum
 * range setting), use \a ch_get_num_samples().
 *
 */
uint16_t ch_get_max_samples(ch_dev_t *dev_ptr);

/*!
 * \brief Get the maximum range setting in mm for a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return Maximum range setting, in millimeters
 *
 * This function returns the current maximum detection range setting for the sensor,
 * in millimeters.
 *
 * For ICU sensors, this function always returns the values for the default measurement
 * definition.  To specify which measurement to query, use the \a ch_meas_get_max_range()
 * function.
 *
 * See also \a ch_get_num_samples(), \a ch_get_config().
 */
uint16_t ch_get_max_range(ch_dev_t *dev_ptr);

/*!
 * \brief Set the maximum range for a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param max_range maximum range, in millimeters
 *
 * \return 0 if successful, non-zero if error
 *
 * This function sets the maximum detection range for the sensor, in millimeters.  The
 * detection range setting controls how long the sensor will listen (i.e. how many samples
 * it will capture) during each measurement cycle.  (The number of samples is automatically
 * calculated for the specified range.)
 *
 * For ICU sensors, this function always controls the default measurement definition.  To
 * specify which measurement to modify, use the \a ch_meas_set_max_range() function.
 *
 * See also \a ch_set_num_samples(), \a ch_get_max_range(), \a ch_set_config().
 */
uint8_t ch_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range);

/*!
 * \brief Get the sample window for amplitude averaging.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param start_sample_ptr 	pointer to variable to be updated with sample number of first sample
 * \param num_samples_ptr  	pointer to variable to be updated with number of samples
 *
 * \return 0 if successful, non-zero if error
 *
 * This function obtains the current range of samples that are included in the sample window used for
 * amplitude averaging.  \a start_sample_ptr is a pointer to a variable that will be updated with the
 * number of the first sample in the sample window.  \a num_samples_ptr is a pointer to a variable that
 * will be updated with the the total number of samples in the sample window.
 *
 * See also \a ch_get_amplitude_avg(), \a ch_set_sample_window().
 *
 * \note Internal sample window averaging is available when using special sensor firmware packages
 * from Chirp.  In General Purpose Rangefinding (GPR) firmware, a software only implementation
 * is used.
 *
 */
uint8_t ch_get_sample_window(ch_dev_t *dev_ptr, uint16_t *start_sample_ptr, uint16_t *num_samples_ptr);

/*!
 * \brief Set the sample window for amplitude averaging.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param start_sample 	sample number of first sample in window
 * \param num_samples  	number of samples to include in window
 *
 * \return 0 if successful, non-zero if error
 *
 * This function sets the sample range to be included in the sample window used for
 * amplitude averaging.  \a start_sample is the number of the first sample that will be
 * included in the averaging window.  \a num_samples is the total number of samples
 * that will be included.
 *
 * See also \a ch_get_amplitude_avg(), \a ch_get_sample_window().
 *
 * \note Internal sample window averaging is available when using special sensor firmware packages
 * from Chirp.  In General Purpose Rangefinding (GPR) firmware, a software only implementation
 * is used.
 */
uint8_t ch_set_sample_window(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t num_samples);

/*!
 * \brief Get the measured range from a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param range_type 	the range type to be reported (e.g. one-way vs. round-trip)
 *
 * \return Range in millimeters times 32, or \a CH_NO_TARGET (0xFFFFFFFF) if no target was detected,
 *         or 0 if error
 *
 * This function reads the measurement result registers from the sensor and then computes the actual
 * range.  It should be called after the sensor has indicated that a measurement cycle is complete
 * by generating a signal on the INT line.  (Typically, this will be set up by an interrupt handler
 * associated with that input line.)
 *
 * The \a range_type parameter indicates whether the measurement is based on the one-way or round-trip
 * distance to/from a target, or the direct distance between two sensors operating in pitch-catch mode.
 * The possible values are:
 *   - \a CH_RANGE_ECHO_ONE_WAY -  gets full pulse/echo round-trip distance, then divides by 2
 *   - \a CH_RANGE_ECHO_ROUND_TRIP	- full pulse/echo round-trip distance
 *   - \a CH_RANGE_DIRECT - for receiving sensor in pitch-catch mode (one-way)
 *
 * This function returns the measured range as a 32-bit integer.  For maximum precision, the range value
 * is returned in a fixed-point format with 5 fractional bits.  So, the return value is the number of
 * millimeters times 32. Divide the value by 32 (shift right 5 bits) to get whole mm, or use floating
 * point (i.e.  divide by 32.0f) to preserve the full sub-millimeter precision.
 *
 * If the sensor did not successfully find the range of a target during the most recent measurement,
 * the returned range value will be \a CH_NO_TARGET.  If an error occurs when getting or calculating the
 * range, zero (0) will be returned.
 *
 * \note This function only reports the results from the most recently completed measurement cycle.  It
 * does not actually trigger a measurement.
 *
 * \note The \a range_type parameter only controls how this function interprets the results from the
 * measurement cycle.  It does not change the sensor mode.
 *
 */
uint32_t ch_get_range(ch_dev_t *dev_ptr, ch_range_t range_type);

/*!
 * \brief Get the measured amplitude from a sensor.
 *
 * \param 	dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * \return Amplitude value for most recent successful range reading
 *
 * This function returns the amplitude value for the most recent successful range measurement by
 * the sensor. The amplitude is representative of the incoming sound pressure.  The value is expressed
 * in internal sensor counts and is not calibrated to any standard units.
 *
 * The amplitude value is not updated if a measurement cycle resulted in \a CH_NO_TARGET, as returned
 * by \a ch_get_range().
 */
uint16_t ch_get_amplitude(ch_dev_t *dev_ptr);

/*!
 * \brief Get the averaged measured amplitude over the sample window.
 *
 * \param 	dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * \return Average amplitude value for samples in current sample window
 *
 * This function returns the average amplitude value for the most recent measurement cycle across the
 * samples within the current sample window.  The sample window is a subset of the overall sensor data,
 * and is specified by the \a ch_set_sample_window() function.
 *
 * The amplitude is representative of the incoming sound pressure.  The value is expressed in internal
 * sensor counts and is not calibrated to any standard units.
 *
 * \note Sample window averaging is only available when using special sensor firmware packages
 * from Chirp.  It is generally not available in General Purpose Rangefinding (GPR) firmware.
 *
 */
uint16_t ch_get_amplitude_avg(ch_dev_t *dev_ptr);

/*!
 * \brief Get the bandwidth of a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * This function returns the operating frequency of the sensor.  This is the primary frequency of the
 * ultrasonic pulse that is emitted by the device when transmitting.
 *
 * \return Sensor bandwidth, in Hz, or 0 if error or bandwidth measurement is not available
 *
 * \note The bandwidth measurement is only available when using special sensor firmware packages
 * from Chirp.  It is generally not available in General Purpose Rangefinding (GPR) firmware.
 */
uint16_t ch_get_bandwidth(ch_dev_t *dev_ptr);

/*!
 * \brief Set the operating frequency of a sensor.
 *
 * \param dev_ptr 				pointer to the ch_dev_t descriptor structure
 * \param request_op_freq_hz  	requested operating frequency in Hz
 *
 * \return 0 if success, 1 if error
 *
 * This function requests a desired acoustic operating frequency for a sensor.  This is the
 * primary frequency of the ultrasonic pulse that is emitted by the device when transmitting.
 *
 * The \a request_op_freq_hz parameter specifies the frequency, in Hz, that is requested.
 * The operating frequency for the sensor will be set as close as possible to
 * this value.  The operating frequency cannot be set to a value that
 * is outside the typical operating frequency range for the sensor model.
 *
 * In general, the actual operating frequency will be slightly different than the requested value.
 * Use \a ch_get_frequency() to obtain the sensor's operating frequency after the adjustment.
 *
 * Often, a group of sensors will be set to a common acoustic operating frequency to optimize the
 * transmit/receive efficiency for sensors operating in paired pitch/catch operation.  Use
 * \a ch_group_set_frequency(), instead of this function, to set all sensors in a
 * group to a common value.  That function can automatically apply a calculated value
 * based on the sensors' natural frequencies.
 *
 * See also \a ch_get_frequency(), \a ch_group_set_frequency().
 *
 * \note For CH101 and CH201 sensors, this function is only available in
 * select sensor firmware versions.
 */
uint8_t ch_set_frequency(ch_dev_t *dev_ptr, uint32_t request_op_freq_hz);

/*!
 * \brief Get the operating frequency of a sensor.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * This function returns the acoustic operating frequency of the sensor.  This is the primary
 * frequency of the ultrasonic pulse that is emitted by the device when transmitting.
 *
 * Normally, the returned operating frequency value is the natural resonant frequency
 * for the sensor.  However, if the frequency has been changed by using \a ch_set_frequency()
 * or \a ch_group_set_frequency(), the returned value will be the adjusted operating
 * frequency.
 *
 * \return Acoustic operating frequency, in Hz
 */
uint32_t ch_get_frequency(ch_dev_t *dev_ptr);

/*!
 * \brief Set the operating frequency for a group of sensors.
 *
 * \param grp_ptr 				pointer to the ch_group_t descriptor for sensor group
 * \param request_op_freq_hz  	requested operating frequency in Hz, or zero to use group avg
 *
 * \return 0 if success, 1 if error
 *
 * This function requests a desired acoustic operating frequency for a group of sensors.
 * This is the primary frequency of the ultrasonic pulse that is emitted by each device
 * when transmitting.
 *
 * When a group of sensors are used in paired pitch/catch operation, it is often
 * helpful to set them to a common acoustic operating frequency.  A better frequency
 * match between the transmitting and receiving sensors improves the range and
 * reliability.
 *
 * All sensors in the group must be the same production model (part number).  It
 * is not possible to set the frequency to a value that is outside the
 * typical operating frequency range for the sensor model.
 *
 * If the \a request_op_freq_hz parameter is \a CH_OP_FREQ_USE_AVG (zero), all sensors
 * will be set to the average of the unadjusted operating frequencies for the group,
 * which generally gives the best performance.  After this call returns, you may use
 * \a ch_group_get_frequency() to determine the average frequency that was used.
 *
 * If \a request_op_freq_hz is non-zero, the specified frequency in Hz will be applied
 * to all sensors.  Use this option to request a certain operating frequency for all sensors,
 * regardless of their natural operating frequencies.
 *
 * In general, the actual operating frequency for each device will vary
 * slightly from the requested value or calculated average frequency.  The nominal
 * group operating frequency may be obtained by using \a ch_group_get_frequency().
 * To determine the actual operating frequency for each individual sensor, use
 * \a ch_get_frequency().
 *
 * See also \a ch_group_get_frequency(), \a ch_set_frequency().
 *
 * \note For CH101 and CH201 sensors, this function is only available in
 * select sensor firmware versions.
 */
uint8_t ch_group_set_frequency(ch_group_t *grp_ptr, uint32_t request_op_freq_hz);

/*!
 * \brief Get the operating frequency for a group of sensors.
 *
 * \param grp_ptr	pointer to the ch_group_t descriptor for sensor group
 *
 * This function returns the nominal acoustic operating frequency for a group of
 * sensors whose frequencies have been adjusted using \a ch_group_set_frequency().
 * A return value of zero indicates that no group frequency has been set.
 *
 * In general, the actual operating frequency for each device will vary slightly
 * from the nominal group value.  Use \a ch_get_frequency() to obtain the adjusted
 * operating frequency for an individual sensor.
 *
 * \return Group nominal frequency, in Hz, or zero if no group frequency has been set
 *
 * See also \a ch_group_set_frequency(), \a ch_get_frequency().
 *
 * \note For CH101 and CH201 sensors, this function is only available in
 * select sensor firmware versions.
 */
uint32_t ch_group_get_frequency(ch_group_t *grp_ptr);

/*!
 * \brief Get the real-time clock calibration value.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 *
 * \return 	RTC calibration value
 *
 * This function returns the real-time clock (RTC) calibration value read from the sensor during
 * \a ch_group_start().  The RTC calibration value is calculated by the sensor during the RTC
 * calibration pulse, and it is used internally in calculations that convert between time and distance.
 */
uint16_t ch_get_rtc_cal_result(ch_dev_t *dev_ptr);

/*!
 * \brief Get the real-time clock calibration pulse length.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return RTC pulse length, in ms
 *
 * This function returns the length (duration), in milliseconds, of the the real-time clock (RTC)
 * calibration pulse used for the sensor.  The pulse is applied to the sensor's INT line during
 * \a ch_group_start() to calibrate the sensor's internal clock.  The pulse length is specified by
 * the board support package during the \a ch_group_init() function.
 *
 * The RTC calibration pulse length is used internally in calculations that convert between time
 * and distance.
 */
uint16_t ch_get_rtc_cal_pulselength(ch_dev_t *dev_ptr);

/*!
 * \brief Get the amplitude scale factor of a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * This function returns the amplitude scale factor of the sensor.  The scale factor is an
 * internal value generated during the initialization of the device.
 *
 * \return Scale factor value, or 0 if error or not available
 *
 * \note The scale factor value is only available when using special sensor firmware packages
 * from Chirp.
 */
uint16_t ch_get_scale_factor(ch_dev_t *dev_ptr);

/*!
 * \brief Get the raw I/Q measurement data from a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param buf_ptr		pointer to data buffer where I/Q data will be written
 * \param start_sample  starting sample number within measurement data (0 = start of data)
 * \param num_samples	number of samples to read from sensor
 * \param mode			whether I/Q read should block (\a CH_IO_MODE_BLOCK (0) = blocking,
 * 												   	\a CH_IO_MODE_NONBLOCK (1) = non-blocking)
 *
 * \return 0 if successful, 1 if error
 *
 * This function reads the raw I/Q measurement data from the sensor.  The I/Q data set includes
 * a discrete pair of values for each of the samples that make up a full measurement cycle.   Each
 * individual sample is reported as a pair of values, I and Q, in a quadrature format.  The I/Q
 * values may be used to calculate the relative amplitude of the measured ultrasound signal.
 *
 * The contents of the I/Q trace are updated on every measurement cycle, even if no target was
 * detected (i.e. even if \a ch_get_range() returns \a CH_NO_TARGET).  (Note that this is different
 * than the regular amplitude value, as returned by \a ch_get_amplitude(), which is \a not updated
 * unless a target is detected.)
 *
 * Each sample I/Q pair consists of two signed 16-bit integers and is described by the
 * \a ch_iq_sample_t structure. To convert any given pair of I/Q values to the amplitude value for
 * that sample, square both I and Q, and take the square root of the sum:
 * 			\f[Amp_n = \sqrt{(I_n)^2 + (Q_n)^2}\f]
 * Amplitude values in the sensor are expressed only in internal ADC counts (least-significant bits,
 * or LSBs) and are not calibrated to any standard units.
 *
 * The number of samples used in each I/Q trace is determined by the maximum range setting for the
 * device.  If it is set to less than the maximum possible range, not all samples will contain valid
 * data.  To determine the number of active samples within the trace, use \a ch_get_num_samples().
 *
 *  - To read all valid I/Q data, set \a start_sample to zero (0), and set \a num_samples to the
 *  value returned by \a ch_get_num_samples().
 *
 * To determine what sample number corresponds to a physical distance, use \a ch_mm_to_samples().
 *
 * To allow more flexibility in your application, the I/Q data readout from the device may be done
 * in a non-blocking mode, by setting \a mode to \a CH_IO_MODE_NONBLOCK (1).  In non-blocking
 * mode, the I/O operation takes place using DMA access in the background.  This function will
 * return immediately, and a notification will later be issued when the I/Q has been read.  To
 * use the \a non_block option, the board support package (BSP) you are using must provide the
 * \a chbsp_i2c_read_nb() and \a chbsp_i2c_read_mem_nb() functions.  To use non-blocking reads
 * of the I/Q data, you must specify a callback routine that will be called when the I/Q read
 * completes.  See \a ch_io_complete_callback_set().
 *
 * Non-blocking reads are managed together for a group of sensors.  To perform a non-blocking read:
 *
 *  -# Register a callback function using \a ch_io_complete_callback_set().
 *  -# Define and initialize a handler for the DMA interrupts generated.
 *  -# Synchronize with all sensors whose I/Q data should be read by waiting for all to indicate
 *     data ready.
 *  -# Set up a non-blocking read on each sensor, using \a ch_get_iq_data() with \a mode =
 *     \a CH_IO_MODE_NONBLOCK (1).
 *  -# Start the non-blocking reads on all sensors in the group, using \a ch_io_start_nb().
 *  -# Your callback function (set in step #1 above) will be called as each individual sensor's
 *     read completes.  Your callback function should initiate any further processing of the I/Q
 *     data, possibly by setting a flag that will be checked from within the application's main
 *     execution loop.  The callback function will likely be called at interrupt level, so the
 *     amount of processing within it should be kept to a minimum.
 *
 * For a CH101 sensor, up to 150 samples are taken during each measurement cycle; for a CH201
 * sensor, up to 450 samples are taken.  So, a complete CH101 I/Q trace will contain up to 600
 * bytes of data (150 samples x 4 bytes per sample), and a CH201 I/Q trace may contain up to
 * 1800 bytes.  The buffer specified by \a buf_ptr must be large enough to hold this amount of data.
 *
 * When the I/Q data is read from the sensor, the additional time required to transfer the I/Q
 * data over the SPI/I2C bus must be taken into account when planning how often the sensor can be
 * read (sample interval).
 *
 * \note It is important that any data I/O operations to or from the sensor, including reading
 * the I/Q data, complete before a new measurement cycle is triggered, or the new measurement may
 * be affected.
 *
 * \note This function only obtains the data from the most recently completed measurement cycle.
 * It does not actually trigger a measurement.
 */
uint8_t ch_get_iq_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                       ch_io_mode_t mode);

/*!
 * \brief Get the raw amplitude measurement data from a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param buf_ptr		pointer to data buffer where amplitude data will be written
 * \param start_sample  starting sample number within measurement data (0 = start of data)
 * \param num_samples	number of samples to read from sensor
 * \param mode			whether read should block (\a CH_IO_MODE_BLOCK (0) = blocking,
 * 											   	\a CH_IO_MODE_NONBLOCK (1) = non-blocking)
 *
 * \return 0 if successful, 1 if error
 *
 * The raw amplitude data are updated on every measurement cycle, even if no target was
 * detected (i.e. even if \a ch_get_range() returns \a CH_NO_TARGET).  (Note that this is different
 * than the regular amplitude value, as returned by \a ch_get_amplitude(), which is \a not updated
 * unless a target is detected.)
 *
 * Each sample amplitude consists of one unsigned 16-bit integer value.
 *
 * Amplitude values in the sensor are expressed only in internal ADC counts (least-significant bits,
 * or LSBs) and are not calibrated to any standard units.
 *
 * The number of samples available in each amplitude trace is determined by the maximum range setting for the
 * device.  If it is set to less than the maximum possible range, not all samples will contain valid
 * data.  To determine the number of active samples within the trace, use \a ch_get_num_samples().
 *
 *  - To read all valid amplitude data, set \a start_sample to zero (0), and set \a num_samples to the
 *  value returned by \a ch_get_num_samples().
 *
 * To determine what sample number corresponds to a physical distance, use \a ch_mm_to_samples().
 *
 * To allow more flexibility in your application, the amplitude data readout from the device may be done
 * in a non-blocking mode, by setting \a mode to \a CH_IO_MODE_NONBLOCK (1).  In non-blocking
 * mode, the I/O operation takes place using DMA access in the background.  This function will
 * return immediately, and a notification will later be issued when the amplitude has been read.  To
 * use the \a non_block option, the board support package (BSP) you are using must provide the
 * \a chbsp_i2c_read_nb() and \a chbsp_i2c_read_mem_nb() functions.  To use non-blocking reads
 * of the amplitude data, you must specify a callback routine that will be called when the amplitude read
 * completes.  See \a ch_io_complete_callback_set().
 *
 * \note Non-blocking amplitude reads are only supported when using certain Chirp sensor firmware
 * types which support direct readout of the amplitude data.  Other firmware types read I/Q data
 * and calculate the amplitudes as part of this function, and will require use of blocking mode
 * (CH_IO_MODE_BLOCK).  If non-blocking mode is specified when using sensor f/w that does not
 * support it, this function will return an error.
 *
 * Non-blocking reads are managed together for a group of sensors.  To perform a non-blocking read:
 *
 *  -# Register a callback function using \a ch_io_complete_callback_set().
 *  -# Define and initialize a handler for the DMA interrupts generated.
 *  -# Synchronize with all sensors whose amplitude data should be read by waiting for all to indicate
 *     data ready.
 *  -# Set up a non-blocking read on each sensor, using \a ch_get_amplitude_data() with \a mode =
 *     \a CH_IO_MODE_NONBLOCK (1).
 *  -# Start the non-blocking reads on all sensors in the group, using \a ch_io_start_nb().
 *  -# Your callback function (set in step #1 above) will be called as each individual sensor's
 *     read completes.  Your callback function should initiate any further processing of the I/Q
 *     data, possibly by setting a flag that will be checked from within the application's main
 *     execution loop.  The callback function will likely be called at interrupt level, so the
 *     amount of processing within it should be kept to a minimum.
 *
 * For a CH101 sensor, up to 150 samples are taken during each measurement cycle; for a CH201
 * sensor, up to 450 samples are taken.  So, a complete CH101 amplitude trace will contain up to 300
 * bytes of data (150 samples x 2 bytes per sample), and a CH201 amplitude trace may contain up to
 * 900 bytes.  The buffer specified by \a buf_ptr must be large enough to hold this amount of data.
 *
 * When the amplitude data is read from the sensor, the additional time required to transfer the
 * amplitude data over the SPI/I2C bus must be taken into account when planning how often the sensor can be
 * read (sample interval).
 *
 * \note It is important that any data I/O operations to or from the sensor, including reading
 * the amplitude data, complete before a new measurement cycle is triggered, or the new measurement may
 * be affected.
 *
 * \note This function only obtains the data from the most recently completed measurement cycle.
 * It does not actually trigger a measurement.
 */
uint8_t ch_get_amplitude_data(ch_dev_t *dev_ptr, uint16_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                              ch_io_mode_t mode);

/*!
 * \brief Get the amplitude measurement and threshold data from a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param buf_ptr		pointer to data buffer where amplitude and threshold data will be written
 * \param start_sample  starting sample number within measurement data (0 = start of data)
 * \param num_samples	number of samples to read from sensor
 * \param mode			whether read should block (\a CH_IO_MODE_BLOCK (0) = blocking,
 * 											   	\a CH_IO_MODE_NONBLOCK (1) = non-blocking)
 *
 * \return 0 if successful, 1 if error
 *
 * This function obtains specially formatted sample data from the sensor, in which both
 * the amplitude and the detection threshold are reported for each sample in a measurement.
 *
 * This function is similar to \a ch_get_amplitude_data(), except that the data values each
 * contains a 16-bit unsigned threshold value in addition to the 16-bit unsigned sample amplitude.
 * The threshold value is the required amplitude at that sample offset to detect a target object,
 * as set by ch_set_thresholds().  This output format may be useful in tuning and debugging the
 * detection threshold values.
 *
 * Each output sample consists of a ch_amp_thresh_t structure, containing one unsigned 16-bit
 * integer value threshold value followed by one unsigned 16-bit amplitude value.
 *
 * See \a ch_get_amplitude_data() for more information on reading amplitude values.
 */
uint8_t ch_get_amp_thresh_data(ch_dev_t *dev_ptr, ch_amp_thresh_t *buf_ptr, uint16_t start_sample, uint16_t num_samples,
                               ch_io_mode_t mode);

/*!
 * \brief Convert sample count to millimeters for a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_samples  	sample count to be converted
 *
 * \return Number of millimeters
 *
 * This function converts the sample count specified in \a num_samples and converts it to the
 * corresponding physical distance in millimeters.  The conversion uses values set during device
 * initialization and calibration that describe the internal timing of the sensor.
 *
 * This function may be helpful when working with both physical distances (as reported by the
 * \a ch_get_range() function) and sample-oriented values, such as data obtained from
 * \a ch_get_iq_data() or parameters for static target rejection (see \a ch_set_static_range()).
 *
 * \note The number of samples corresponding to a certain distance is determined by the
 * ODR (output data rate) for the sensor, which is the rate at which the received ultrasound
 * is sampled within each measurement.  So, the ODR must be known to calculate this conversion.
 *
 * \note In ICU sensors, the ODR is configurable.  The default is one sample per 8 transceiver cycles
 * (CH_ODR_FREQ_DIV_8, also known as CH_ODR_DEFAULT).  If the default ODR will not be not used,
 * the new ODR must be specified before this function is called, either as a standard parameter during
 * \a ch_meas_init(), or by calling \a ch_meas_set_odr() using CH_DEFAULT_MEAS_NUM as the measurement number.
 *
 * \note For ICU sensors, this function always returns the conversion values for the default measurement.
 * If multiple measurements are being used with different ODR settings, use the \a ch_meas_samples_to_mm()
 * function to get the correct value for the specific measurement.
 *
 * See also \a ch_mm_to_samples(), \a ch_meas_set_odr().
 */
uint16_t ch_samples_to_mm(ch_dev_t *dev_ptr, uint16_t num_samples);

/*!
 * \brief Convert millimeters to sample count for a sensor.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \param num_mm  number of millimeters to be converted
 *
 * \return Number of samples
 *
 * This function converts the distance in millimeters specified by \a num_mm and converts it
 * to the corresponding number of sensor samples.  The conversion uses values set during device
 * initialization and calibration that describe the internal timing of the sensor, which
 * affects how many samples correspond to a given distance.
 *
 * This function may be helpful when working with both physical distances (as reported by the
 * \a ch_get_range() function) and sample-oriented values, such as data obtained from
 * \a ch_get_iq_data() or parameters for filtering such as static target rejection
 * (see \a ch_set_static_range()).
 *
 * \note The number of samples corresponding to a certain distance is determined by the
 * ODR (output data rate) for the sensor, which is the rate at which the received ultrasound
 * is sampled within each measurement.  So, the ODR must be known to calculate this conversion.
 * This function always uses the ODR value for the default measurement (CH_DEFAULT_MEAS_NUM).
 * To get the conversion for a specific measurement, use \a ch_meas_mm_to_samples().
 *
 * \note In ICU sensors, the ODR is configurable.  The default is one sample per 8 transceiver cycles
 * (CH_ODR_FREQ_DIV_8, also known as CH_ODR_DEFAULT).  If the default ODR will not be not used,
 * the new ODR must be applied before this function is called, either as a standard parameter during
 * \a ch_meas_init(), or by calling \a ch_meas_set_odr() using CH_DEFAULT_MEAS_NUM as the measurement number.
 *
 * \note For ICU sensors, this function always returns the conversion values for the default measurement.
 * If multiple measurements are being used with different ODR settings, use the \a ch_meas_mm_to_samples()
 * function to get the correct value for the specific measurement.
 *
 * See also \a ch_samples_to_mm(), \a ch_meas_set_odr().
 */
uint16_t ch_mm_to_samples(ch_dev_t *dev_ptr, uint16_t num_mm);

/*!
 * \brief Calculate amplitude from sample I/Q values.
 *
 * \param iq_sample_ptr  pointer to ch_iq_data_t structure containing the I/Q data
 *
 * \return Amplitude value
 *
 * This function converts the I and Q values from a single raw sensor sample to an amplitude
 * value according to the following formula:
 * 			\f[Amp = \sqrt{(I)^2 + (Q)^2}\f]
 *
 * Amplitude values in the sensor are expressed only in internal ADC counts (least-significant bits,
 * or LSBs) and are not calibrated to any standard units.
 *
 * See also \a ch_get_iq_data(), \a ch_get_amplitude_data().
 */
uint16_t ch_iq_to_amplitude(ch_iq_sample_t *iq_sample_ptr);

/*!
 * \brief Start non-blocking I/O operation(s) for a group of sensors.
 *
 * \param grp_ptr 	pointer to the ch_group_t descriptor for sensor group
 *
 * \return 0 if success, 1 if error
 *
 * This function starts one or more non-blocking I/O operations on a group of sensors.
 * Generally, the I/O operations are non-blocking I/Q data read requests individually
 * generated using \a ch_get_iq_data().
 *
 * This function will return immediately after the I/O operations are started.  When the I/O operations complete,
 * the callback function registered using \a ch_io_complete_callback_set() will be called.
 *
 * See \a ch_get_iq_data() for more information.
 */
uint8_t ch_io_start_nb(ch_group_t *grp_ptr);

/*!
 * \brief Notify SonicLib that a sensor interrupt was received
 *
 * \param grp_ptr 	pointer to the ch_group_t config structure for a group of sensors
 * \param dev_num	interrupting sensor's device number within group
 * \return 0 for success, non-zero otherwise.
 *
 * This function should be called from the board support package when
 * an interrupt from the sensor is received.  The \a dev_num parameter
 * indicates which sensor interrupted.
 *
 * Unlike \a ch_interrupt(), this function does not call the user supplied
 * callback. It is intended to be used when the user would like more control
 * of exactly what happens when an interrupt is received from the sensor.
 *
 * Other differences from \a ch_interrupt():
 *
 *   - This function does not disable interrupt handling. This must be done in
 *     user code if needed.
 *   - This function does not read any metadata from the sensor, with one exception.
 *     During sensor programming, this funciton performs one SPI read in order
 *     to cause the ASIC to release the interrupt line.
 *   - This function does not update state of the dev_ptr
 *
 * See also \a ch_interrupt().
 */
uint8_t ch_minimal_int_handler(ch_group_t *grp_ptr, uint8_t dev_num);

/*!
 * \brief Run SonicLib's full-featured interrupt handler
 *
 * \param grp_ptr 			pointer to the ch_group_t sensor group descriptor structure
 * \param dev_num 			device number within group for interrupting sensor
 *
 * This function is used from the board support package (BSP) handler routine
 * for the sensor interrupt to announce that the interrupt has
 * occurred.  \a dev_num identifies which sensor has interrupted.
 *
 * The SonicLib driver layer will handle further processing of
 * the interrupt, including disabling the interrupt processing (to allow
 * for next trigger), reading sensor metadata, and calling the application-supplied
 * callback function.
 *
 * Only one of ch_interrupt() and \a ch_minimal_int_handler() should be called.
 * The latter function is a simplified handler that gives the user more control
 * of exactly what happens during the interrupt handling.
 *
 * \note Upon return from this routine, the sensor interrupt is disabled.
 *
 * See also \a ch_io_int_callback_set() and \a ch_minimal_int_handler().
 */
void ch_interrupt(ch_group_t *grp_ptr, uint8_t dev_num);

/*!
 * \brief Register sensor interrupt callback routine for a group of sensors.
 *
 * \param grp_ptr 			pointer to the ch_group_t sensor group descriptor structure
 * \param callback_func_ptr	pointer to callback function to be called when sensor interrupts
 *
 * This function registers the routine specified by \a callback_func_ptr to be called whenever the
 * sensor interrupts.  Generally, such an interrupt indicates that a measurement cycle has completed
 * and the sensor has data ready to be read.  All sensors in a sensor group use the same callback function,
 * which receives the interrupting device's device number (port number) as an input parameter to identify
 * the specific interrupting device.  The callback function also receives the \a ch_interrupt_type_t
 * interrupt type parameter that identifies the type (reason) for the sensor interrupt).
 */
void ch_io_int_callback_set(ch_group_t *grp_ptr, ch_io_int_callback_t callback_func_ptr);

/*!
 * \brief Register non-blocking I/O complete callback routine for a group of sensors.
 *
 * \param grp_ptr 			pointer to the ch_group_t group descriptor structure
 * \param callback_func_ptr	pointer to callback function to be called when non-blocking I/O operations complete
 *
 * This function registers the routine specified by \a callback_func_ptr to be called when all outstanding
 * non-blocking I/O operations complete for a group of sensors.   The non-blocking I/O operations must have previously
 * been initiated using \a ch_io_start_nb().
 */
void ch_io_complete_callback_set(ch_group_t *grp_ptr, ch_io_complete_callback_t callback_func_ptr);

/*!
 * \brief Notify SonicLib that a non-blocking I/O operation has completed.
 *
 * \param grp_ptr 		pointer to the ch_group_t sensor group descriptor structure
 * \param bus_index identifier indicating on which SPI/I2C bus the I/O operation was completed
 *
 * This function should be called from your non-blocking I/O interrupt handler each time a non-blocking
 * I/O operation completes.  The \a bus_index parameter should indicate which SPI/I2C bus is being
 * reported.
 *
 * When all outstanding non-blocking I/O operations are complete, SonicLib will call the callback
 * function previously registered using \a ch_io_complete_callback_set().
 */
void ch_io_notify(ch_group_t *grp_ptr, uint8_t bus_index);

/*!
 * \brief Configure target interrupt filtering mode.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param tgt_int_filter	target interrupt filter mode
 *
 * \return 0 if success, 1 if error
 *
 * This function configures the filtering of data ready interrupts from the
 * sensor based on target detection.
 *
 * In normal operation (if target detection interrupt filtering is not enabled), the sensor
 * will assert the INT line at the end of each measurement even if no target is detected.
 * This is the default behavior if this function is not used, or if \a tgt_int_filter is
 * CH_TGT_INT_FILTER_OFF.
 *
 * When basic target interrupt filtering is enabled, the sensor will assert the INT
 * line at the end of each measurement only if a target object was detected.  If no target
 * is detected, the sensor will not interrupt, and there is no indication from the sensor
 * that the measurement has completed.
 *
 * To use basic target interrupt filtering, set \a tgt_int_filter to \a CH_TGT_INT_FILTER_ANY.
 *
 * Target counter mode provides another level of filtering, across multiple measurements.
 * When counter filtering is enabled, the sensor will only interrupt after multiple measurements
 * have detected a target within a certain total number of consecutive recent measurements.
 * A configurable history of previous measurements is recorded, and the results are compared against a
 * threshold number of target detections.  The sensor will generate an interrupt only when
 * the count of target detections within the set of recent measurements meets the threshold value,
 *
 * To use counter mode filtering, set \a tgt_int_filter to \a CH_TGT_INT_FILTER_COUNTER.
 * The measurement history and target detection threshold count used in the filter can be
 * set by using the \a ch_set_target_int_counter() function.
 *
 * If not otherwise specified, the default measurement history length is 5 measurements.
 * The current measurement is combined with the measurements from the history, so a total of 6
 * measurements are used.  The default interrupt threshold is 3 target detections.  So by
 * default, 3 of the 6 most recent measurements must detect a target to generate an interrupt.
 *
 * By default, the counter filter maintains its history and counter values after an interrupt
 * is generated, so the next measurement may again interrupt based on the threshold comparison
 * as usual.  The counter filter may instead be configured to reset after generating an interrupt
 * by using \a ch_set_target_int_counter().  In this case, the full \a thresh_count threshold
 * must be met based on new detections, so that minimum number of measurements must occur
 * before another interrupt will be generated.
 *
 *	See also \a ch_set_target_int_counter(), \a ch_get_target_interrupt().
 *
 * \note Target interrupt filtering is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_set_target_interrupt(ch_dev_t *dev_ptr, ch_tgt_int_filter_t tgt_int_filter);

/*!
 * \brief Get the target interrupt filtering mode setting.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return Target interrupt filter mode
 *
 * This function returns the current setting for target interrupt filtering mode.
 * The mode is one of:
 *  - CH_TGT_INT_FILTER_OFF - No filtering.  The sensor will interrupt after each measurement, even
 *  if no target is detected.
 *	- CH_TGT_INT_FILTER_ANY - Target filtering.  The sensor will interrupt after each measurement
 *	in which a target is successfully detected.  No interrupt is generated if no target is found.
 *	- CH_TGT_INT_FILTER_COUNTER - Target filtering with a threshold value.  The sensor will interrupt if
 *	a specified number of measurements detect a target within a certain number of consecutive results.
 *
 *	See also \a ch_set_target_interrupt(), \a ch_get_target_int_counter().
 *
 * \note Target detection interrupt mode is only available in select Chirp sensor firmware versions.
 */
ch_tgt_int_filter_t ch_get_target_interrupt(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the target interrupt counter filter.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param meas_hist	number of previous measurements to include in target count
 * \param thresh_count	number of target detections req'd to generate interrupt
 * \param reset 	if non-zero, counter filter resets when int is generated
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the counter filter used to control target interrupts.  The
 * counter filter is by enabled using the \a ch_set_target_interrupt() function and
 * specifying \a CH_TGT_INT_FILTER_COUNTER as the filter type.
 *
 * When the counter filter is used, a certain threshold number of positive target detections must
 * be observed within a specified number of measurements in order for an interrupt to
 * be generated by the sensor.
 *
 * \a meas_hist specifies the number of previous measurements that will be included
 * in the history buffer for filtering.  The current measurement is combined with these
 * previous measurements, so a total of \a meas_hist + 1 measurements are used.
 *
 * \a thresh_count is the number of those measurements that must positively detect a
 * target for an interrupt to be generated.
 *
 * At the end of each measurement, the total number of measurements with target detection
 * within all the history and the new measurement is compared against the threshold value.
 * If it meets the threshold, the sensor will interrupt.
 * For example, if \a meas_hist is 5 and \a thresh_count is 3, an interrupt will be generated
 * if 3 of the most recent 6 measurements (the 5 in the history plus the new result) detected
 * a target.
 *
 * If \a reset is non-zero, the counter filter counts are reset when an interrupt is
 * generated.  The sensor will not interrupt again until \a thresh_count new measurements
 * detect a target, using the same threshold conditions as before.  If \a reset is zero,
 * the sensor will maintain its history and will continue to interrupt after each measurement
 * if the threshold number of detections within recent results is met.  Counter filter
 * resetting is disabled by default.
 *
 * The maximum value for both \a meas_hist and \a thresh_count is 15.
 *
 * See also \a ch_get_target_int_counter(), \a ch_set_target_interrupt().
 *
 * \note Target counter filtering is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_set_target_int_counter(ch_dev_t *dev_ptr, uint8_t meas_hist, uint8_t thresh_count, uint8_t reset);

/*!
 * \brief Get the target interrupt counter filter settings.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param meas_hist_ptr	pointer to location to receive count of measurements in filter history
 * \param thresh_count_ptr	pointer to location to receive number of target detections req'd
 * \param reset_ptr	pointer to location to receive target counter reset setting
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains the current target counter filter settings used to control sensor interrupts.
 * This filter is enabled by calling the \a ch_set_target_interrupt() (or \a ch_set_config()) function
 * and specifying \a CH_TGT_INT_FILTER_COUNTER as the filter type.
 *
 * The location specified by \a meas_hist_ptr will be set to the number of previous measurements
 * that are included in the history for filtering.  The current measurement is combined with
 * these previous measurements, so a total of \a meas_hist + 1 measurements are used.
 * The location specified by \a thresh_count_ptr will be set to the threshold number of those measurements
 * that must positively detect a target for an interrupt to be generated.
 * The location specified by \a reset_ptr will be set to 1 if the sensor resets the counter filter
 * after an interrupt is generated, 0 otherwise (default).
 *
 * The maximum value for both \a meas_hist and \a thresh_count is 15.
 *
 * See also \a ch_set_target_int_counter(), \a ch_set_target_interrupt().
 *
 * \note Target counter filtering is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_get_target_int_counter(ch_dev_t *dev_ptr, uint8_t *meas_hist_ptr, uint8_t *thresh_count_ptr,
                                  uint8_t *reset_ptr);

/*!
 * \brief Set interrupt mode (pulsed or latching)
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param mode  	CH_INTERRUPT_MODE_PULSE for pulse interrupt mode, CH_INTERRUPT_MODE_LATCH for latching mode
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the sensor interrupt to use a pulsed or latching level change.  In pulse mode,
 * the sensor will briefly change the INT line level and then restore it to the original state.  In
 * latching mode, the sensor will change the INT line level, and it will stay at that level until
 * reset by the interrupt handler in the board support package.  By default, ICU sensors use latching
 * interrupt mode (CH_INTERRUPT_MODE_LATCH).
 *
 * To use this function, set \a mode to CH_INTERRUPT_MODE_PULSE to enable pulsed interrupt mode.  Set
 * \a mode to CH_INTERRUPT_MODE_LATCH to disable the pulse interrupt mode and use latching behavior.
 *
 * \note This option is only available for ICU sensors.  CH101 and CH201 sensors
 * always use pulse interrupt mode for normal sensor interrupts.  Attempting to set \a mode to
 * CH_INTERRUPT_MODE_LATCH on a CH101 or CH201 will return an error.
 */
uint8_t ch_set_interrupt_mode(ch_dev_t *dev_ptr, ch_interrupt_mode_t mode);

/*!
 * \brief Get the pulse interrupt mode setting.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return CH_INTERRUPT_MODE_PULSE if interrupt uses pulse mode, CH_INTERRUPT_MODE_LATCH if latching mode
 *
 * This function returns the current setting for interrupt mode (pulsed or latching).
 *
 * \note CH101 and CH201 sensors always use pulse interrupt mode for normal
 * sensor interrupts, so this routine will always return CH_INTERRUPT_MODE_PULSE.
 */
ch_interrupt_mode_t ch_get_interrupt_mode(ch_dev_t *dev_ptr);

/*!
 * \brief Set interrupt drive (open drain or push pull)
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param drive  	CH_INTERRUPT_DRIVE_OPEN_DRAIN for open drain interrupt drive, CH_INTERRUPT_DRIVE_PUSH_PULL for push
 * pull drive
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the sensor interrupt to use an open-drain or push-pull
 * drive.  In open drain, the sensor will actively drive the line low and use a
 * pull-up resistor for the hight level.  In push-pull drive, the sensor will
 * actively drive the line both low and high.  Additionally, the pull-up
 * resistor on the interrupt pin used for hardware trigger is disabled.  By
 * default, ICU sensors use open drain interrupt drive
 * (CH_INTERRUPT_DRIVE_OPEN_DRAIN).
 *
 * To use this function, set \a drive to CH_INTERRUPT_DRIVE_OPEN_DRAIN to enable
 * open drain drive.  Set \a drive to CH_INTERRUPT_DRIVE_PUSH_PULL to use
 * push-pull drive.
 *
 * \note This option is only available for ICU sensors.  CH101 and CH201 sensors
 * always use active-high, pull low interrupts.  Attempting to set \a drive to
 * CH_INTERRUPT_MODE_PUSH_PULL on a CH101 or CH201 will return an error.
 */
uint8_t ch_set_interrupt_drive(ch_dev_t *dev_ptr, ch_interrupt_drive_t drive);

/*!  \brief Get the pulse interrupt drive setting.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return CH_INTERRUPT_DRIVE_OPEN_DRAIN if interrupt uses open drain drive,
 * CH_INTERRUPT_DRIVE_PUSH_PULL if push pull drive
 *
 * This function returns the current setting for interrupt drive (open drain or
 * push pull).
 *
 * \note CH101 and CH201 sensors always use active-high, pull low interrupt
 * drive for normal sensor interrupts, so this routine will always return
 * CH_INTERRUPT_DRIVE_OPEN_DRAIN.
 */
ch_interrupt_drive_t ch_get_interrupt_drive(ch_dev_t *dev_ptr);

/*!  \brief Enable data validation mode.  In this mode, ICU-x0201 sensors will overwrite the IQ
 *  data at the end of a measurement and after running the algorithm, with a known sequence to
 *  allow validating data transfer integrity while making minimal changes to the system otherwise.
 *  Currently, this is limited to a 16-bit counter that increments for each I and Q sample
 *  and is continuous across measurements.
 *
 *  This feature is currently only supported by icu_init_fw.  It is not recommended to use it if the
 *  application uses continuous receive, or has non-contiguous RX segments in its measurement
 *  queue.  Enabling data validation adds approximately 0.8μs per IQ sample to the measurement time.
 *  Note that for each sample, the counter value is incremented in the order of Q then I.
 *  Data validation must be handled by the application using ch_data_validation_check().
 *
 * \param dev_ptr The device pointer
 * \param seed Initial value for data validation counter
 * \param enable Set to 1 to enable data validation mode, set to 0 to disable
 *
 * \return 0 for success and non-zero otherwise
 */
uint8_t ch_enable_data_validation(ch_dev_t *dev_ptr, int16_t seed, uint8_t enable);

/*!  \brief Check data in validation mode, which should be enabled before calling this. Should be
 *  run over all IQ data received by the sensor after mode is enabled to keep the counters in sync.
 *
 * Note that for some values of receive length, this will be unreliable - avoid using overall RX
 * lengths 1 to 5 cycles longer than integer multiples of the ODR ratio.
 *
 * \param dev_ptr The device pointer
 * \param data Pointer to IQ buffer containing data sequence read from the sensor
 * \param num_samples Number of IQ samples in buffer
 *
 * \return Number of samples that don't match expected counter value
 */
uint16_t ch_data_validation_check(ch_dev_t *dev_ptr, ch_iq_sample_t *data, uint16_t num_samples);

/**
 * \brief Enable or disable the double buffering mode
 *
 * IMPORTANT: This function is currently only supported with gpt and init firmware.
 *
 * The ICU-X0201 sensors can be put into a double buffering mode which does the
 * following:
 *
 *  - Splits the IQ buffer in two
 *  - Swaps which half of the buffer is written after every measurement
 *
 * This enables a measurement to be triggered before the readout of the previous
 * measurement is finished (or even started). The disadvantage is that the maximum
 * number of supported samples is reduced by a factor of 2.
 *
 * You must not exceed the maximum number of supported samples, which can be found
 * as ch_get_max_samples(...)/2. SonicLib will not check this!
 *
 * \param dev_ptr The device pointer
 * \param enable Set to 1 to enable the double buffer mode or 0 to disable it
 *
 * \return 0 for success and non-zero otherwise
 */
uint8_t ch_enable_double_buffer(ch_dev_t *dev_ptr, uint8_t enable);

/**
 * \brief Enable or disable placing metadata in the first IQ sample

 * IMPORTANT: This function is currently only supported with gpt and init firmware.
 *
 * The ICU-X0201 can be configured to place metadata in the first IQ sample,
 * which is otherwise always read out as 0. If enabled, this will place the IQ
 * buffer address as well as the last measurement index in the first IQ sample.
 *
 * \param dev_ptr The device pointer
 * \param enable Set to 1 to enable metadata in IQ sample 0 or 0 to disable.
 *
 * \return 0 for success and non-zero otherwise
 */
uint8_t ch_enable_metadata_in_iq0(ch_dev_t *dev_ptr, uint8_t enable);

/**
 * \brief Extract the metadata from the first IQ sample and update the device pointer
 *
 * The ICU-X0201 can be configured to place metadata in the first IQ sample,
 * which is otherwise always read out as 0. If enabled, this will place the IQ
 * buffer address as well as the last measurement index in the first IQ sample.
 * See \a ch_enable_metadata_in_iq0().
 *
 * This function is used to extract metadata from the read IQ data. The metadata
 * will be updated into \a dev_ptr. That is, after calling this function, the device
 * pointer will be updated with the correct buffer address and last measurement index.
 *
 * After running this function and getting a 0 exit status, the last measurement index
 * can be retrieved using ch_meas_get_last_num() and the next buffer address with
 * ch_get_next_buf_addr().
 *
 * \param dev_ptr The device pointer
 * \param iq_data Pointer to the read IQ data. The metadata is extracted from
 *                the first sample, then the first sample is set back to 0.
 *
 * \return 0 for success and non-zero otherwise. If this function returns non-zero,
 *         then the device pointer is not updated. This most likely means that
 *         data was read from the incorrect buffer in double buffer mode. The situation
 *         should resolve itself on the next read since the same buffer will be
 *         read again, and the ASIC will swap write buffers on each measurement.
 */
uint8_t ch_update_metadata_from_iq0(ch_dev_t *dev_ptr, ch_iq_sample_t *iq_data);

/*!
 * \brief Set the receive holdoff sample count.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_samples 	number of samples to be ignored at the beginning of each measurement
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the receive (rx) holdoff sample count.  \a num_samples specifies a number of
 * samples at the beginning of a measurement that will be ignored for the purpose of
 * detecting a target.  (These samples correspond to the closest distances from the sensor.)
 *
 * To convert a physical distance into a sample count value to use here, use \a ch_mm_to_samples().
 *
 * For ICU sensors, this function always controls the default measurement definition.  To
 * specify which measurement to modify, use the \a icu_gpt_set_rx_holdoff() function.
 *
 * See also \a ch_get_rx_holdoff().
 */
uint8_t ch_set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t num_samples);

/*!
 * \brief Get the receive holdoff sample count.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return number of samples that are ignored at the beginning of each measurement
 *
 * This function gets the receive (rx) holdoff sample count.  The rx holdoff count
 * is the number of samples at the beginning of a measurement that will be ignored for
 * the purpose of detecting a target, as previously set by \a ch_set_rx_holdoff().
 *
 * To convert the returned sample count to a physical distance, use \a ch_samples_to_mm().
 *
 * For ICU sensors, this function always returns the value for the default measurement
 * definition.  To specify which measurement to query, use the \a icu_gpt_get_rx_holdoff()
 * function.
 *
 * See also \a ch_set_rx_holdoff().
 */
uint16_t ch_get_rx_holdoff(ch_dev_t *dev_ptr);

/*!
 * \brief Set the receive low-gain sample count.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_samples 	number of samples that have low gain at beginning of measurement
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the receive (rx) low-gain range in the sensor.  The low-gain range consists
 * of samples at the beginning of a measurement that will have a lower gain applied during the
 * sensor receive operation.  (These samples correspond to the closest distances from the sensor.)
 *
 * The low-gain range must be less than the current maximum range setting.  If \a num_samples is
 * greater than or equal to the maximum range setting, it will automatically be reduced.
 *
 * See also \a ch_get_rx_low_gain(), \a ch_get_num_samples().
 *
 * \note This function is only available in CH201 sensor firmware.
 */
uint8_t ch_set_rx_low_gain(ch_dev_t *dev_ptr, uint16_t num_samples);

/*!
 * \brief Get the receive low-gain sample count.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 	number of samples that have low gain at beginning of measurement
 *
 * This function gets the receive (rx) low-gain range from the sensor.  The low-gain range is
 * a count of samples at the beginning of a measurement that will have lower gain applied
 * during the ultrasound receive operation.
 *
 * The returned low-gain range is either the default value for the sensor firmware, or
 * a value previously set by \a ch_set_rx_low_gain().
 *
 * To convert the returned sample count to a physical distance, use \a ch_samples_to_mm().
 *
 * See also \a ch_set_rx_low_gain().
 *
 * \note This function is only available in CH201 sensor firmware.
 */
uint16_t ch_get_rx_low_gain(ch_dev_t *dev_ptr);

/*!
 * \brief Set the ultrasound transmit pulse length.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_cycles 	transmit pulse length (number of cycles per transmission)
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the length (duration) of the ultrasonic pulse sent by the
 * sensor when it transmits. \a num_cycles specifies the length of the pulse.
 *
 * For ICU (Shasta architecture) sensors, \a num_cycles are in units of Measurement State
 * Machine Clock (SMCLK) cycles.
 *
 * For CH101 and CH201 (Whitney architecture) sensors, \a num_cycles are ultrasonic
 * transducer (PMUT) cycles, so are 1/16 the corresponding ICU sensor value.
 *
 * See also \a ch_get_tx_length().
 *
 * \note This feature is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_set_tx_length(ch_dev_t *dev_ptr, uint16_t num_cycles);

/*!
 * \brief Get the ultrasound transmit pulse length.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return transmit pulse length (number of cycles per transmission)
 *
 * This function gets the length of the ultrasonic pulse sent by the sensor when
 * it transmit.  The transmit length is expressed in \a cycles.
 *
 * For ICU (Shasta architecture) sensors, \a cycles are in units of Measurement State
 * Machine Clock (SMCLK) cycles.
 *
 * For CH101 and CH201 (Whitney architecture) sensors, \a cycles are ultrasonic
 * transducer (PMUT) cycles.
 *
 * See also \a ch_set_tx_length().
 *
 * \note This feature is only available in select Chirp sensor firmware versions.
 */
uint16_t ch_get_tx_length(ch_dev_t *dev_ptr);

/*!
 * \brief Enable/disable receive-only sensor pre-triggering.
 *
 * \param grp_ptr 	pointer to the ch_group_t group descriptor structure
 * \param enable  	1 to enable pre-triggering, 0 to disable
 *
 * This function enables or disables pre-triggering of the receive-only sensor during Pitch-Catch
 * operation.  When pre-triggering is enabled, sensors in CH_MODE_TRIGGERED_RX_ONLY mode will be
 * triggered slightly before sensors in CH_MODE_TRIGGERED_TX_RX mode when \a ch_group_trigger() is called.
 * This improves the ability of a receive-only sensor to detect the transmitted pulse at very short
 * distances.
 *
 * If enabled, pre-triggering is used for all receive-only sensors in the sensor group.
 *
 * To use this function, set \a enable to 1 to enable pre-triggering, or 0 to disable pre-triggering.
 *
 * See also \a ch_get_rx_pretrigger().
 *
 * \note  Enabling pre-triggering will reduce the maximum range of the receive-only sensor(s), relative to the
 * setting specified in \a ch_set_max_range(), by about 200mm.  You may want to increase the maximum range setting
 * accordingly.
 */
void ch_set_rx_pretrigger(ch_group_t *grp_ptr, uint8_t enable);

/*!
 * \brief Get receive-only sensor pre-triggering setting.
 *
 * \param grp_ptr 	pointer to the ch_group_t group descriptor structure
 *
 * This function returns the current state (enabled or disabled) of pre-triggering receive-only
 * sensors.
 *
 * See also \a ch_set_rx_pretrigger().
 *
 * \return 1 if receive pre-triggering is enabled, 0 if disabled
 */
uint8_t ch_get_rx_pretrigger(ch_group_t *grp_ptr);

/*!
 * \brief Check sensor firmware program.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * This function confirms that the contents of the sensor's program memory match
 * the firmware that was loaded into it, as specified during the \a ch_init()
 * call.  The memory contents are read back from the sensor and are compared with
 * the original byte values used to program the device.
 *
 * \return 0 if firmware matches the original program, or 1 if mismatch (error)
 */
uint8_t ch_check_program(ch_dev_t *dev_ptr);

/*!
 * \brief Set the calibration result.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param cal_ptr 		pointer to ch_cal_result_t structure to receive calibration data
 *
 * \return 0 if success, 1 if error
 *
 * WARNING: This function should not be used to set the calibration result to a fixed value,
 * even one individually calculated for each sensor, as this could change over the lifetime
 * of the sensor; rather, this function could be used to update the calibration result if the
 * calibration result calculated by CHx01 at startup (i.e. returned by ch_get_cal_result())
 * is sufficiently different than expected or sensor performance is not good.
 *
 * This function sets the calibration result with a ch_cal_result_t structure specified by \a cal_ptr
 * for the sensor. The ch_cal_result_t structure contains DCO period and reverse drive cycles.
 *
 * To use this function, first initialize the ch_cal_result_t DCO period/reverse drive cycles pair of values
 *
 * See also \a ch_get_cal_result().
 */
uint8_t ch_set_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);

/*!
 * \brief Get the calibration result.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param cal_ptr 		pointer to ch_cal_result_t structure to receive calibration data
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains the current calibration result from the sensor and
 * returns them in a ch_cal_result_t structure specified by \a cal_ptr.  The
 * ch_cal_result_t structure contains DCO period and reverse drive cycles.
 *
 * See also \a ch_set_cal_result().
 */
uint8_t ch_get_cal_result(ch_dev_t *dev_ptr, ch_cal_result_t *cal_ptr);

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
 * For ICU sensors, both measurements will be set to the specified output type.  To change
 * the output format for a single measurement, use \a ch_meas_set_iq_output().
 * To change the output data rate for a single measurement, use \a ch_meas_set_odr().
 *
 * \note For CH101 and CH201 sensors, this function is only available in
 * select sensor firmware versions.
 */
uint8_t ch_set_data_output(ch_dev_t *dev_ptr, ch_output_t *output_ptr);

/*!
 * \brief Convert microseconds to sensor cycles.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_usec		number of microseconds
 *
 * \return Number of sensor cycles.
 *
 * This function takes a period of time specified in microseconds and converts
 * it to the corresponding number of internal sensor cycles.
 *
 * For ICU (Shasta architecture) sensors, \a cycles are in units of PMUT State
 * Machine Clock (SMCLK) cycles. The PMUT clock rate is 16 times the ultrasonic transducer
 * acoustic operating frequency.  These are the same cycle units used to specify measurement
 * transmit and count segment lengths.
 *
 * For CH101 and CH201 (Whitney architecture) sensors, \a cycles are ultrasonic
 * transducer cycles, so are 1/16 the corresponding ICU sensor value.
 *
 * See also \a ch_cycles_to_usec().
 */
uint32_t ch_usec_to_cycles(ch_dev_t *dev_ptr, uint32_t num_usec);

/*!
 * \brief Convert sensor cycles to microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_cycles	number of cycles
 *
 * \return Number of microseconds.
 *
 * This function takes a number of internal sensor cycles and converts
 * it to the corresponding period of time specified in microseconds.
 *
 * For ICU (Shasta architecture) sensors, \a num_cycles are in units of PMUT State
 * Machine Clock (SMCLK) cycles. The SMCLK rate is 16 times the ultrasonic transducer
 * acoustic operating frequency.  These are the same units used to specify measurement
 * transmit and count segment lengths.
 *
 * For CH101 and CH201 (Whitney architecture) sensors, \a num_cycles are ultrasonic
 * transducer cycles, so are 1/16 the corresponding ICU sensor value.
 *
 * See also \a ch_usec_to_cycles().
 */
uint32_t ch_cycles_to_usec(ch_dev_t *dev_ptr, uint32_t num_cycles);

/*!
 * \brief Convert samples to sensor cycles.
 *
 * \param num_samples	number of samples
 * \param odr			output data rate
 *
 * \return Number of sensor cycles.
 *
 * This function takes a count of samples and converts it to the
 * corresponding number of internal sensor cycles.  The cycles
 * are the same units used to specify measurement segment lengths.
 *
 * The \a odr parameter is the current output data rate setting for the
 * sensor.  The ODR affects the timing between samples, and therefore the
 * number of internal cycles per sample.
 *
 * See also \a ch_cycles_to_samples, \a ch_meas_get_odr.
 */
uint32_t ch_samples_to_cycles(uint16_t num_samples, ch_odr_t odr);

/*!
 * \brief Convert sensor cycles to samples.
 *
 * \param num_cycles	number of cycles
 * \param odr			output data rate
 *
 * \return Number of sample periods.
 *
 * This function takes a count of internal sensor cycles and converts it to the
 * corresponding number of sample periods.  The cycles
 * are the same units used to specify measurement segment lengths.
 *
 * The \a odr parameter is the current output data rate setting for the
 * sensor.  The ODR affects the timing between samples, and therefore the
 * number of internal cycles per sample.
 *
 * See also \a ch_samples_to_cycles, \a ch_meas_get_odr.
 */
uint16_t ch_cycles_to_samples(uint32_t num_cycles, ch_odr_t odr);

/*!
 * \brief Convert microseconds to sensor RTC clock ticks.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param num_usec		number of microseconds
 *
 * \return Number of sensor RTC clock ticks.
 *
 * This function takes a time specified in microseconds and converts
 * it to the corresponding number of sensor RTC clock periods.
 *
 * See also \a ch_ticks_to_usec(), ch_set_rtc().
 */
uint16_t ch_usec_to_ticks(ch_dev_t *dev_ptr, uint32_t num_usec);

/*!
 * \brief Convert sensor RTC clock ticks to microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param rtc_ticks		number of sensor RTC clock periods
 *
 * \return Number of microseconds.
 *
 * This function takes a number of internal sensor RTC clock periods and converts
 * it to the corresponding time in microseconds.
 *
 * See also \a ch_usec_to_ticks(), \a ch_set_rtc().
 */
uint32_t ch_ticks_to_usec(ch_dev_t *dev_ptr, uint16_t num_ticks);

#ifdef INCLUDE_SHASTA_SUPPORT

/*!
 * \brief Initialize the sensor measurement queue.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function resets and re-initializes the sensor measurement queue.  All
 * configuration settings and all measurements are cleared.
 */
uint8_t ch_meas_init_queue(ch_dev_t *dev_ptr);

/*!
 * \brief Import an externally defined measurement configuration.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param meas_queue_ptr	pointer to a complete measurement queue structure, or NULL
 * \param algo_cfg_ptr		pointer to a buffer containing algorithm configuration, or NULL
 *
 * \return 0 if success, 1 if error
 *
 * This function allows a fully defined measurement queue structure (measurement_queue_t)
 * and algorithm-specific configuration to be imported as a unit.  Taken
 * together, these two structures fully define the measurement to be performed.
 *
 * Alternatively, it is possible to import either the measurement queue or the algorithm
 * configuration individually, by supplying a NULL pointer for the other structure.  In
 * this case, the current settings will continue to be used for the values specified in
 * the other structure.  An error is returned if both pointers are NULL.
 *
 * The format of the algorithm configuration data will vary depending on the
 * sensor firmware and algorithm that are being used.
 *
 * See also \a ch_meas_optimize(), which combines importing and optimizing a measurement
 * queue.
 */
uint8_t ch_meas_import(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr);

/*!
 * \brief Reset a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return 0 if success, 1 if error
 *
 * This function resets and re-initializes the measurement specified by \a meas_num.
 * All segments in the measurement are removed.
 *
 * After calling this function, transmit and receive segments may be added to
 * the measurement.  See \a ch_meas_add_segment().
 */
uint8_t ch_meas_reset(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Initialize a measurement.
 *
 * \param dev_ptr 			pointer to the ch_dev_t descriptor structure
 * \param meas_num			measurement number
 * \param meas_config_ptr	pointer to measurement configuration settings
 * \param thresh_ptr		deprecated. Parameter not used. Shall be set to NULL
 *
 * \return 0 if success, 1 if error
 *
 * This function initializes the measurement specified by \a meas_num with the specified
 * configuration.
 * \a meas_config_ptr is a pointer to a ch_meas_config_t structure which must have already
 * been initialized.  The fields in this structure specify various parameters for the measurement
 * including
 * - odr - output data rate for the sensor (time between samples within measurement)
 * - meas_period - repeat period for measurement, in ticks (optional, freerun interval may be set later)
 * - mode - if CH_MEAS_MODE_STANDBY, this measurement will initially be put in standby mode (not active),
 *   if CH_MEAS_MODE_ACTIVE (zero), this measurement will initially be active and will be performed
 *
 * \a thresh_ptr was used to initialize GPT thresholds. Now use icu_gpt_algo_configure() to configure algo.
 */
uint8_t ch_meas_init(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_config_t *meas_config_ptr,
                     const void *thresh_ptr);

/*!
 * \brief Write measurement configuration to sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function writes a complete measurement queue configuration to the sensor device.  The measurement
 * queue settings must have already been defined, by using the standard API functions (initializing one
 * or more measurements and adding a sequence of measurement segments).
 *
 * This function additionally sanitizes the measurement queue by performing several checks
 * to ensure it is compatible with the selected sensor mode. This function
 * potentially modifies the queue, so users should examine the passed queue
 * after loading it.
 */
uint8_t ch_meas_write_config(ch_dev_t *dev_ptr);

/*!
 * \brief Optimize ultrasound measurement sequences for a sensor.
 *
 * \param dev_ptr 		 pointer to the ch_dev_t descriptor structure
 * \param meas_queue_ptr pointer to measurement queue to optimize, or NULL
 * \param algo_cfg_ptr 	 pointer to a buffer containing algorithm configuration, or NULL
 *
 * \return 0 if success, 1 if error
 *
 * This function optimizes the transmit sequences during measurements for a sensor.  The
 * original transmit segments are replaced by a longer sequence that is tuned to the
 * specific sensor.  In particular, the "ringdown" in the sensor following a transmission
 * is actively reduced.  The sensor is able to receive the echo signal sooner, thus
 * permitting measurements at closer distances.
 *
 * Optimization is performed on a defined measurement, such as the result of combining
 * measurement segments using \a ch_meas_add_segment() etc.  These segments are part of the
 * "measurement queue" for the sensor.
 *
 * To optimize the current measurement settings and make no other changes to the configuration,
 * specify NULL for both \a meas_queue_ptr and \a algo_cfg_ptr.
 *
 * Alternatively, a new measurement queue may be imported, optimized, and applied using this function,
 * similar to the \a ch_meas_import() function (e.g. to use an exported measurement queue
 * definition from the SonicLink development kit).  In this case, set \a meas_queue_ptr to
 * the location containing the measurement queue to be optimized.  The new measurement
 * queue will be optimized, and the resulting settings will be written to the sensor.  The
 * input measurement queue definition specified by \a meas_queue_ptr will not be modified.
 *
 * The \a algo_cfg_ptr parameter specifies a new measurement algorithm configuration to be applied.
 * If \a algo_cfg_ptr is NULL, the current configuration will be left unchanged.
 *
 * When optimization occurs, the sensor will be briefly re-programmed with special initialization
 * firmware that analyzes the sensor's operation and determines the appropriate optimization.  The
 * results are read from the sensor and are combined with the original settings.  Finally, the
 * measurement firmware is again programmed into the sensor, and the new settings are applied.  This
 * entire sequence will typically take about 250 ms to complete.
 *
 * \note A single set of measurement queue values should only be optimized \b once, because
 * new transmit segments will be inserted each time.  If your application needs to
 * perform optimization periodically, it should maintain a copy of the original
 * measurement queue values (before optimization) and pass that in again during each call
 * to this function.  A copy of the internal \a measurement_queue_t structure can be obtained
 * using \a ch_meas_get_queue().
 *
 * \note This feature is only available for ICU sensors.
 *
 * See also \a ch_meas_import(), \a ch_meas_get_queue().
 */
uint8_t ch_meas_optimize(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr, void *algo_cfg_ptr);

/*!
 * \brief Activate a defined measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		number of measurement to activate
 *
 * This function sets a measurement to active mode.  The specified measurement definition
 * will be used when the sensor makes a measurement.  The measurement must have previously
 * been defined, either by using \a ch_meas_init() and related calls to specify the measurement
 * segments, or by importing a complete measurement definition.
 *
 * If the measurement specified by \a meas_num was previously in standby mode (inactive),
 * it is made active.  In all cases, this definition will be used during the the next
 * measurement performed by the sensor, even if the other measurement is also active.
 *
 * This function does not affect the active vs. standby status of the other measurement.
 * If both measurements are active after calling this function, they will alternate each
 * time the sensor performs a measurement.
 *
 * See also \a ch_meas_standby(), \a ch_meas_switch(), \a ch_meas_init(), \a ch_meas_import().
 *
 * \note This feature is only available for ICU sensors.
 */
void ch_meas_activate(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Put a measurement in standby mode.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		number of measurement to place in standby mode
 *
 * This function places the specified measurement in standby mode.  This
 * measurement's definition will not be used by the sensor - the other measurement
 * definition will be used to perform all readings.
 *
 * Because there must always be at least one active measurement, this function will
 * activate the other measurement if it was not already active.  It is not possible
 * to have both measurements in standby mode simultaneously.
 *
 * A measurement may be set to initially be in standby mode, see \a ch_meas_init().
 *
 * See also \a ch_meas_activate(), \a ch_meas_switch().
 *
 * \note This feature is only available for ICU sensors.
 */
void ch_meas_standby(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Switch active and standby measurement definitions.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		number of measurement to place in standby mode
 *
 * \return measurement number of newly active measurement
 *
 * This function switches the roles of the two measurement definitions between
 * active and standby.  The currently active measurement is put into standby mode, and
 * the standby measurement is made active.
 *
 * If this function is called when both measurements are active, the next measurement
 * due to operate (the current measurement) will be placed into standby mode, and the
 * other measurement will remain active.
 *
 * This routine returns the number of the new active measurement.  This will be the
 * next measurement performed by the sensor.
 *
 * See also \a ch_meas_activate(), \a ch_meas_standby(), \a ch_meas_get_info().
 *
 * \note This feature is only available for ICU sensors.
 */
uint8_t ch_meas_switch(ch_dev_t *dev_ptr);

/*!
 * \brief Get number of last completed measurement.
 *
 * \param dev_ptr 		 pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function returns the measurement number (0 or 1) for the last
 * measurement that completed.  It is useful if both measurements are
 * active and are being executed alternately.
 *
 * \note This feature is only available for ICU sensors.
 */
uint8_t ch_meas_get_last_num(ch_dev_t *dev_ptr);

/*!
 * \brief Get the address of the IQ buffer that will be written by the next measurement.
 *
 * \param dev_ptr 		 pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function returns the address of the buffer that will be written by the next
 * measurement. This is useful in the double buffer mode.
 *
 * See also ch_update_metadata_from_iq0().
 *
 * \note This feature is only available for ICU sensors.
 */
uint16_t ch_get_next_buf_addr(ch_dev_t *dev_ptr);

/*!
 * \brief Get measurement queue values for a sensor.
 *
 * \param dev_ptr 		 pointer to the ch_dev_t descriptor structure
 * \param meas_queue_ptr pointer to location to receive measurement queue values
 *
 * \return 0 if success, 1 if error
 *
 * This function copies the current measurement queue values for a sensor to
 * the \a measurement_queue_t structure specified by \a meas_queue_ptr.
 *
 * This function may be used to save the original measurement queue values before
 * calling \a ch_meas_import() or \a ch_meas_optimize().
 *
 * See also \a ch_meas_write_config().
 *
 * \note This feature is only available for ICU sensors.
 */
uint8_t ch_meas_get_queue(ch_dev_t *dev_ptr, measurement_queue_t *meas_queue_ptr);

/*!
 * \brief Add a segment to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param seg_ptr		pointer to measurement segment to be added
 *
 * \return 0 if success, 1 if error
 *
 * This function adds a measurement segment to the measurement specified by \a meas_num.
 * \a seg_ptr points to a segment descriptor, which must have already been initialized.
 *
 * See also \a ch_meas_add_segment_tx(),\a ch_meas_add_segment_rx(), \a ch_meas_init_segment_tx(),
 * \a ch_meas_init_segment_rx(),
 */
uint8_t ch_meas_add_segment(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_segment_t *seg_ptr);

/*!
 * \brief Insert an instruction(segment) to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param inst_ptr		pointer to measurement instruction(segment) to be inserted
 * \param index_to_insert		instruction(segment) number to be inserted
 *
 * \return 0 if success, 1 if error
 *
 * This function inserts a measurement instruction(segment) to the measurement specified by \a meas_num.
 * \a inst_ptr points to an instruction(segment) descriptor, which must have already been initialized.
 *
 * Will be deprecated by the new equivalent function ch_meas_insert_instruction.
 */
uint8_t ch_meas_insert_segment(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *inst_ptr,
                               uint8_t index_to_insert);

/*!
 * \brief Insert an instruction(segment) to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param inst_ptr		pointer to measurement instruction(segment) to be inserted
 * \param index_to_insert		instruction(segment) number to be remove
 *
 * \return 0 if success, 1 if error
 *
 * This function inserts a measurement instruction(segment) to the measurement specified by \a meas_num.
 * \a inst_ptr points to an instruction(segment) descriptor, which must have already been initialized.
 *
 */
uint8_t ch_meas_insert_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, const ch_meas_segment_t *inst_ptr,
                                   uint8_t index_to_insert);

/*!
 * \brief Remove an instruction(segment) in a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param index_to_remove		instruction(segment) number to be removed
 *
 * \return 0 if success, 1 if error
 *
 * This function removes a measurement instruction(segment) to the measurement specified by \a meas_num.
 * \a inst_ptr points to an instruction(segment) descriptor, which must have already been initialized.
 *
 * Will be deprecated by the new equivalent function ch_meas_remove_instruction.
 */
uint8_t ch_meas_remove_segment(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t index_to_remove);

/*!
 * \brief Remove an instruction(segment) in a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param index_to_remove		instruction(segment) number to be removed
 *
 * \return 0 if success, 1 if error
 *
 * This function removes a measurement instruction(segment) to the measurement specified by \a meas_num.
 * \a inst_ptr points to an instruction(segment) descriptor, which must have already been initialized.
 *
 */
uint8_t ch_meas_remove_instruction(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t index_to_remove);

/*!
 * \brief Add a count (delay) segment to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_cycles	length of the segment, in cycles
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * \return 0 if success, 1 if error
 *
 * This function adds a count (delay) segment to the measurement specified by \a meas_num.
 * Such a segment does not transmit a signal nor does it sample received
 * ultrasound.  So, no samples are associated with this portion of the measurement time.
 *
 * This function combines the operations of \a ch_meas_init_segment_count() and \a ch_meas_add_segment().
 *
 */
uint8_t ch_meas_add_segment_count(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t int_enable);

/*!
 * \brief Add a receive segment to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_samples	length of the segment, in sample periods
 * \param gain_reduce	gain reduction value,  0 = max gain
 * \param atten			attenuation level
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * \return 0 if success, 1 if error
 *
 * This function adds a receive segment to the measurement specified by \a meas_num.  It
 * combines the operations of \a ch_meas_init_segment_rx() and \a ch_meas_add_segment().
 *
 */
uint8_t ch_meas_add_segment_rx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples, uint8_t gain_reduce,
                               uint8_t atten, uint8_t int_enable);

/*!
 * \brief Add a transmit segment to a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_cycles	length of the segment, in cycles
 * \param pulse_width	transmit pulse width
 * \param phase			transmit phase
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * \return 0 if success, 1 if error
 *
 * This function adds a transmit segment to the measurement specified by \a meas_num.  It
 * combines the operations of \a ch_meas_init_segment_tx() and \a ch_meas_add_segment().
 *
 * The \a cycles parameter specifies the overall length of the transmit pulse that will be generated.
 * The units are internal sensor cycles.
 *
 * See also \a ch_meas)add_segment_rx(), \a ch_meas_add_segment_count(), \a ch_usec_to_cycles().
 */
uint8_t ch_meas_add_segment_tx(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_cycles, uint8_t pulse_width,
                               uint8_t phase, uint8_t int_enable);

/*!
 * \brief Initialize a count (delay) measurement segment.
 *
 * \param seg_ptr 		pointer to the ch_meas_segment_t descriptor structure to be initialized
 * \param num_cycles	length of the segment, in cycles
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * This function initializes the measurement segment descriptor specified by \a seg_ptr as
 * a count (delay) segment.  Such a segment does not transmit a signal nor does it sample received
 * ultrasound.  So, no samples are associated with this portion of the measurement time.
 *
 * The \a cycles parameter specifies the overall length of the delay.  The units are internal sensor cycles.
 * Use the \a ch_usec_to_cycles() function to calculate the number of cycles for a specific delay duration.
 *
 * \return 0 if success, 1 if error
 *
 */
void ch_meas_init_segment_count(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t int_enable);

/*!
 * \brief Initialize a receive measurement segment.
 *
 * \param seg_ptr 		pointer to the ch_meas_segment_t descriptor structure to be initialized
 * \param num_samples	length of the segment, in sample periods
 * \param odr			output data rate setting to be used (set during \a ch_meas_init())
 * \param gain_reduce	gain reduction value,  0 = max gain
 * \param atten			attenuation level
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * \return 0 if success, 1 if error
 *
 * This function initializes the measurement segment descriptor specified by \a seg_ptr as
 * a receive segment.
 * The number of samples of added to the segments is limited by the maximum number of rx samples
 * that firmware can read and by the number of cycles a segment can store.
 * The length of segment in samples is converted to a number of cycles.
 * A segment have a maximum length of 65535 cycles.
 * If the number of sample exceeds the limitation, define the segments manually and import them
 * to a measure queue using \a ch_meas_import()
 */
void ch_meas_init_segment_rx(ch_meas_segment_t *seg_ptr, uint16_t num_samples, ch_odr_t odr, uint8_t gain_reduce,
                             uint8_t atten, uint8_t int_enable);

/*!
 * \brief Initialize a transmit measurement segment.
 *
 * \param seg_ptr 		pointer to the ch_meas_segment_t descriptor structure to be initialized
 * \param num_cycles	length of the segment, in cycles
 * \param pulse_width	transmit pulse width
 * \param phase			transmit phase
 * \param int_enable	if non-zero, the sensor will interrupt at the completion of this segment
 *
 * \return 0 if success, 1 if error
 *
 * This function initializes the measurement segment descriptor specified by \a seg_ptr as
 * a transmit segment.
 *
 * The \a cycles parameter specifies the overall length of the transmit pulse that will be generated.
 * The units are internal sensor cycles.
 *
 * See also \a ch_meas_init_segment_rx(), \a ch_meas_init_segment_count(), \a ch_usec_to_cycles().
 */
void ch_meas_init_segment_tx(ch_meas_segment_t *seg_ptr, uint16_t num_cycles, uint8_t pulse_width, uint8_t phase,
                             uint8_t int_enable);

/*!
 * \brief Get configuration information for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param info_ptr		pointer to ch_meas_info_t structure to be updated
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains configuration information for the measurement specified by \a meas_num.
 * The ch_meas_info_t structure specified by \a info_ptr will be completed with the
 * settings for the measurement, including:
 * - mode - whether the measurement is active or in standby mode
 * - num_segments - number of active segments in measurement
 * - num_samples - total number of sample periods in all segments
 * - num_ranges - maximum number of separate target range values to report
 * - odr - output data rate for the sensor (time between samples within measurement)
 * - meas_period - repeat period for measurement (0 if not used)
 * - ringdown_cancel_samples - number of samples close to sensor to use ringdown cancellation filter
 * - static_filter_samples - number of samples close to sensor to have static target rejection (STR) filter
 * - iq_output_format - 0=normal (Q,I) pairs; 1=mag,threshold pairs, 2=mag,phase pairs
 * - filter_update_interval - how often to update the ringdown and STR filters
 */
void ch_meas_get_info(ch_dev_t *dev_ptr, uint8_t meas_num, ch_meas_info_t *info_ptr);

/*!
 * \brief Get configuration information for the sensor measurement queue.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param info_ptr		pointer to ch_meas_queue_info_t structure to be updated
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains configuration information for the sensor's measurement queue.
 * The measurement queue contains all defined measurements plus common configuration
 * settings.  The ch_meas_queue_info_t structure specified by \a info_ptr will be completed
 * with the settings for the measurement queue, including:
 * - int_config - interrupt pin selection
 * - meas_start - which measurement do we start on
 * - meas_stop - which measurement do we stop on
 * - current_meas - which measurement do we do next
 * - trig_src - trigger source: INT1, INT2, or internal timer
 */
void ch_meas_get_queue_info(ch_dev_t *dev_ptr, ch_meas_queue_info_t *info_ptr);

/*!
 * \brief Get configuration information for a measurement segment.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param seg_num		segment number
 * \param info_ptr		pointer to ch_meas_seg_info_t structure to be updated
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains configuration information for the measurement segment specified
 * by \a meas_num and \a seg_num.
 *
 * The ch_meas_seg_info_t structure specified by \a info_ptr will be completed with the
 * settings for the measurement segment, including:
 * - num_rx_samples - length in sample periods (determined by num_cycles and output data rate)
 * - num_cycles - length in cycles
 * - rdy_int_en - sensor will interrupt when ready
 * - done_int_en - sensor will interrupt when done with segment
 * - tx_phase - phase (transmit segments only)
 * - tx_pulse_width - pulse width (transmit segments only)
 * - rx_gain_reduce - gain reduction (receive segments only)
 * - rx_atten - attenuation (receive segments only)
 */
void ch_meas_get_seg_info(ch_dev_t *dev_ptr, uint8_t meas_num, uint8_t seg_num, ch_meas_seg_info_t *info_ptr);

/*!
 * \brief Get configuration information for a measurement segment.
 *
 * \param inst_ptr 		pointer to the pmut_transciever_t instruction
 * \param odr           measurement odr
 * \param info_ptr		pointer to ch_meas_seg_info_t structure to be updated
 *
 * \return 0 if success, 1 if error
 *
 * This function obtains configuration information for the measurement segment specified
 * by \a inst_ptr.
 *
 * The ch_meas_seg_info_t structure specified by \a info_ptr will be completed with the
 * settings for the measurement segment, including:
 * - num_rx_samples - length in sample periods (determined by num_cycles and output data rate)
 * - num_cycles - length in cycles
 * - rdy_int_en - sensor will interrupt when ready
 * - done_int_en - sensor will interrupt when done with segment
 * - tx_phase - phase (transmit segments only)
 * - tx_pulse_width - pulse width (transmit segments only)
 * - rx_gain_reduce - gain reduction (receive segments only)
 * - rx_atten - attenuation (receive segments only)
 */
void ch_inst_get_seg_info(pmut_transceiver_inst_t *inst_ptr, uint8_t odr, ch_meas_seg_info_t *info_ptr);

/*!
 * \brief Set the repeat interval for a measurement, in milliseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param interval_ms	measurement interval, in milliseconds
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the internal measurement interval in the sensor.  The sensor will
 * perform a measurement every \a interval_ms milliseconds.  No external trigger is
 * required.
 *
 * To set the sensing interval with greater precision, use \a ch_meas_set_interval_us()
 * or \a ch_meas_set_interval_ticks().
 *
 * See also \a ch_set_freerun_interval(), \a ch_meas_get_interval().
 */
uint8_t ch_meas_set_interval(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t interval_ms);

/*!
 * \brief Set the repeat interval for a measurement, in microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param interval_us	measurement interval, in microseconds
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the internal measurement interval in the sensor.  The sensor will
 * perform a measurement every \a interval_us microseconds.  No external trigger is
 * required.
 *
 * See also \a ch_meas_set_interval(), \a ch_meas_get_interval_ticks().
 */
uint8_t ch_meas_set_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t interval_us);

/*!
 * \brief Set the repeat interval for a measurement, in sensor RTC clock ticks.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param rtc_ticks		measurement interval, in sensor RTC clock periods
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the internal measurement interval in the sensor.  The sensor will
 * perform a measurement every \a rtc_ticks sensor RTC clock periods.  No external trigger is
 * required.
 *
 * See also \a ch_meas_set_interval(), \a ch_meas_get_interval_ticks().
 */
uint8_t ch_meas_set_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num, uint32_t rtc_ticks);

/*!
 * \brief Get the repeat interval for a measurement, in milliseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return sensor measurement interval
 *
 * This function returns the internal measurement interval in the sensor,
 * in milliseconds.
 *
 * See also \a ch_meas_set_interval(), \a ch_get_freerun_interval().
 */
uint16_t ch_meas_get_interval(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Get the repeat interval for a measurement, in microseconds.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return sensor measurement interval
 *
 * This function returns the internal measurement interval in the sensor,
 * in microseconds.
 *
 * See also \a ch_meas_set_interval_us().
 */
uint32_t ch_meas_get_interval_us(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Get the repeat interval for a measurement, in sensor RTC clock ticks.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return sensor measurement interval
 *
 * This function returns the internal measurement interval in the sensor,
 * in sensor RTC clock periods.
 *
 * See also \a ch_meas_set_interval_ticks().
 */
uint32_t ch_meas_get_interval_ticks(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Enable time-hopping on measure period freerunning mode.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \return 0 if successful.
 *
 * This function enables the time-hopping for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).  The sensor will use its internal real-time clock (RTC) to wake
 * and perform a measurement every \a measure interval plus a random delay to
 * avoid coexistence with other sensors. Mean measure period is however equals to
 * \a measure interval.
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes.
 *
 * See also \a ch_meas_time_hop_disable(), \a ch_meas_get_interval_ticks(),
 * \a ch_meas_set_interval(), \a ch_meas_set_interval_us(),
 * \a ch_meas_set_interval_ticks().
 */
uint8_t ch_meas_time_hop_enable(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Disable time-hopping on measure period freerunning mode
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \return 0 if successful.
 *
 * This function disable the time-hopping for a sensor operating in freerunning mode
 * (\a CH_MODE_FREERUN).
 *
 * \note This function has no effect for a sensor operating in one of the triggered modes
 *
 * See also \a ch_meas_time_hop_enable(), \a ch_meas_get_interval_ticks(),
 * \a ch_meas_set_interval(), \a ch_meas_set_interval_us(),
 * \a ch_meas_set_interval_ticks().
 */
uint8_t ch_meas_time_hop_disable(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the output data rate for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function sets the output data rate (ODR) for the sensor.  The ODR setting determines
 * the spacing in time (and therefore in measured distance) between the individual sample
 * points within a measurement.
 *
 * The standard ODR value is CH_ODR_FREQ_DIV_8 (also known as CH_ODR_DEFAULT), or one sample per
 * 8 transceiver cycles.  The ODR may be adjusted higher or lower - each higher or value will
 * increase or decrease the output rate (i.e. the time between samples) by a factor of 2.  The
 * maximum ODR is CH_ODR_FREQ_DIV_2 (one sample every 2 transceiver cycles); the minimum ODR
 * is CH_ODR_FREQ_DIV_32 (one sample every 32 transceiver cycles).
 *
 * See also \a ch_meas_init(), \a ch_meas_get_odr().
 */
uint8_t ch_meas_set_odr(ch_dev_t *dev_ptr, uint8_t meas_num, ch_odr_t odr);

/*!
 * \brief Get the output data rate for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return ODR setting
 *
 * This function returns the output data rate (ODR) for the sensor.  The ODR setting determines
 * the spacing in time (and therefore in measured distance) between the individual samples
 * within a measurement.
 *
 * See also \a ch_meas_set_odr().
 */
ch_odr_t ch_meas_get_odr(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the sensor sample count for a specific measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor struct
 * \param meas_num		measurement number
 * \param num_samples 	number of samples during each measurement cycle
 *
 * \return 0 if successful
 *
 * This function directly sets the number of samples which the Chirp sensor will obtain
 * during a specific measurement (0 or 1).  The number of samples directly corresponds to the
 * range at which the sensor can detect.
 *
 * Note that this function changes the number of samples in an existing
 * measurement.  The existing measurement definition will be shortened or extended
 * to match the new sample count.  If the measurement is extended, the new samples
 * will use the same settings as in the final receive segment.
 *
 * The \a ch_set_num_samples() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_meas_set_max_range(), \a ch_set_num_samples().
 *
 */
uint8_t ch_meas_set_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/*!
 * \brief Get the number of samples per measurement cycle for a specific measurement.
 *
 * \param dev_ptr	pointer to the ch_dev_t descriptor struct
 * \param meas_num	measurement number
 *
 * \return  Number of samples per measurement cycle
 *
 * This function returns the configured number of samples which the Chirp sensor will obtain
 * during each measurement cycle for the specified measurement.  The number of samples
 * directly corresponds to the range at which the sensor can detect, so this value is determined
 * by the current maximum range setting for the sensor.
 *
 * The \a ch_get_num_samples() function may be used to obtain the number of samples in
 * the most recently completed measurement.
 *
 * See also \a ch_meas_get_max_range(), \a ch_get_num_output_samples().
 */
uint16_t ch_meas_get_num_samples(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the maximum range in mm for a specific measurement.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param meas_num	measurement number
 * \param max_range maximum range, in millimeters
 *
 * \return 0 if successful, non-zero if error
 *
 * This function sets the maximum detection range for the specified measurement,
 * in millimeters.  The detection range setting controls how long the sensor will listen
 * (i.e. how many samples it will capture) during each measurement cycle.  (The number of
 * samples is automatically calculated for the specified range.)
 *
 * Note that this function changes the number of samples in an existing
 * measurement.  The existing measurement definition will be shortened or extended
 * to match the new sample count.  If the measurement is extended, the new samples
 * will use the same settings as in the final receive segment.
 *
 * The \a ch_set_max_range() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_meas_set_num_samples(), \a ch_meas_get_max_range().
 */
uint8_t ch_meas_set_max_range(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t max_range_mm);

/*!
 * \brief Get the maximum range setting in mm for a specific measurement.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param meas_num	measurement number
 *
 * \return Maximum range setting, in millimeters
 *
 * This function returns the current maximum detection range setting for the
 * specified measurement, in millimeters.
 *
 * The \a ch_get_max_range() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_meas_set_max_range(), \a ch_meas_get_num_samples().
 */
uint16_t ch_meas_get_max_range(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Convert millimeters to sample count for a specific measurement.
 *
 * \param dev_ptr pointer to the ch_dev_t descriptor structure
 * \param meas_num	measurement number
 * \param num_mm  number of millimeters to be converted
 *
 * \return Number of samples
 *
 * This function converts the distance in millimeters specified by \a num_mm and converts it
 * to the corresponding number of sensor samples for a specific measurement number.  The
 * conversion uses values set during device initialization and calibration that describe the
 * internal timing of the sensor, which affects how many samples correspond to a given distance.
 *
 * \note In ICU sensors, the ODR is configurable.  The default is one sample per 8 transceiver cycles
 * (CH_ODR_FREQ_DIV_8, also known as CH_ODR_DEFAULT).  If the default ODR will not be not used,
 * the new ODR must be set for the specified measurement before this function is called, either as a
 * standard parameter during \a ch_meas_init(), or by calling \a ch_meas_set_odr().
 *
 * The \a ch_mm_to_samples() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_samples_to_mm(), \a ch_meas_set_odr().
 */
uint16_t ch_meas_mm_to_samples(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_mm);

/*!
 * \brief Convert sample count to millimeters for a specific measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 * \param num_samples  	sample count to be converted
 *
 * \return Number of millimeters
 *
 * This function converts the sample count specified in \a num_samples and converts it to the
 * corresponding physical distance in millimeters for the specified measurement.  The conversion
 * uses values set during device initialization and calibration that describe the internal timing
 * of the sensor.
 *
 * This function may be helpful when working with both physical distances (as reported by the
 * \a ch_get_range() function) and sample-oriented values, such as data obtained from
 * \a ch_get_iq_data() or parameters for static target rejection (see \a ch_set_static_range()).
 *
 * \note The number of samples corresponding to a certain distance is determined by the
 * ODR (output data rate) for the sensor, which is the rate at which the received ultrasound
 * is sampled within each measurement.  So, the ODR must be known to calculate this conversion.
 *
 * \note In ICU sensors, the ODR is configurable.  The default is one sample per 8 transceiver cycles
 * (CH_ODR_FREQ_DIV_8, also known as CH_ODR_DEFAULT).  If the default ODR will not be not used,
 * the new ODR must be set for the specified measurement before this function is called, either as a
 * standard parameter during \a ch_meas_init(), or by calling \a ch_meas_set_odr().
 *
 * The \a ch_samples_to_mm() function performs the same operation for the default
 * measurement (same as setting \a meas_num to CH_DEFAULT_MEAS_NUM).
 *
 * See also \a ch_mm_to_samples(), \a ch_meas_set_odr().
 */
uint16_t ch_meas_samples_to_mm(ch_dev_t *dev_ptr, uint8_t meas_num, uint16_t num_samples);

/*!
 * \brief Get the I/Q data output format for a measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return I/Q data output format
 *
 * This function returns the measurement I/Q data output format, as follows:
 *  - CH_OUTPUT_IQ (0) - Standard pairs of {Q,I} int16_t values
 *  - CH_OUTPUT_AMP_THRESH (1) - Output amplitude + threshold uint16_t pair values
 *  - CH_OUTPUT_AMP	(2) - Output uint16_t amplitude values only
 *
 * See also \a ch_meas_set_iq_output().
 */
ch_output_type_t ch_meas_get_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Set the I/Q data output format for a measurement.
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
 * See also \a ch_meas_get_iq_output(), \a ch_set_data_output(), \a ch_meas_init().
 */
uint8_t ch_meas_set_iq_output(ch_dev_t *dev_ptr, uint8_t meas_num, ch_output_type_t output_format);

/*!
 * \brief	Initialize the measurement algorithm on a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_info_ptr	pointer to a ICU_ALGO_SHASTA_INFO structure to receive info
 *
 * \return 0 if success, 1 if error
 *
 * This function initializes a measurement algorithm that has been loaded into a
 * sensor and configured.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.  It is not used directly in a typical application.
 *
 * See also \a ch_meas_import(), ch_get_algo_state().
 */
uint8_t ch_init_algo(ch_dev_t *dev_ptr);

/*!
 * \brief	Get the measurement algorithm output data from a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_out_ptr	pointer to a buffer to receive output data
 *
 * \return 0 if success, 1 if error
 *
 * This function reads the output data from an algorithm running on the ICU sensor.
 * This interface is independent of the specific algorithm or output format.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.  It is not used directly in a typical application.
 *
 */
uint8_t ch_get_algo_output(ch_dev_t *dev_ptr, void *algo_out_ptr);

/*!
 * \brief	Get the measurement algorithm state data from a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_state_ptr	pointer to a buffer to receive state data
 *
 * \return 0 if success, 1 if error
 *
 * This function reads the state data from an algorithm running on the ICU sensor.
 * This interface is independent of the specific algorithm or state format.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.  It is not used directly in a typical application.
 *
 */
uint8_t ch_get_algo_state(ch_dev_t *dev_ptr, void *algo_state_ptr);

/*!
 * \brief	Get the measurement algorithm configuration data from a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_cfg_ptr	pointer to a buffer to receive configuration data
 *
 * \return 0 if success, 1 if error
 *
 * This function reads the configuration data from an algorithm running on the ICU sensor.
 * This interface is independent of the specific algorithm or configuration format.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.  It is not used directly in a typical application.
 *
 */
uint8_t ch_get_algo_config(ch_dev_t *dev_ptr, void *algo_cfg_ptr);

/*!
 * \brief	Set the measurement algorithm configuration data to a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_cfg_ptr	pointer to a buffer to send configuration data
 *
 * \return 0 if success, 1 if error
 *
 * This function writes the configuration data to an algorithm running on the ICU sensor.
 * This interface is independent of the specific algorithm or configuration format.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.
 *
 */
uint8_t ch_set_algo_config(ch_dev_t *dev_ptr, const void *algo_cfg_ptr);

/*!
 * \brief	Get the measurement algorithm information data from a sensor.
 *
 * \param 	dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param	algo_info_ptr	pointer to a ICU_ALGO_SHASTA_INFO structure to receive info
 *
 * \return 0 if success, 1 if error
 *
 * This function reads the information data from an algorithm running on the ICU sensor.
 * This interface is independent of the specific algorithm that is being used.
 *
 * Normally, this routine will only be used by special applications or libraries which
 * interact with specific sensor firmware.  It is not used directly in a typical application.
 *
 */
uint8_t ch_get_algo_info(ch_dev_t *dev_ptr, ICU_ALGO_SHASTA_INFO *algo_info_ptr);

/*!
 * \brief	Get the unique Sensor ID String for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 	Pointer to character string containing unique sensor ID
 *
 * This function returns a pointer to a string that contains a unique identifier
 * for the sensor device.  The ID string consists of 7 ascii alpha-numeric
 * characters, terminated by a null byte (so total size is 8 bytes).
 * \a CH_SENSOR_ID_LENGTH, is defined as the length of the string, including the
 * null terminator.
 *
 * The first three bytes in the ID string specify the Production Lot.  The remaining
 * four bytes specify the alphanumeric Serial Number within that production lot.
 *
 * See also \a ch_get_mfg_info(), \a ch_get_fw_version_string.
 */
const char *ch_get_sensor_id(ch_dev_t *dev_ptr);

/*!
 * \brief	Get manufacturing information for a sensor.
 *
 * \param 	dev_ptr 	pointer to the ch_dev_t descriptor structure
 * \param   info_ptr	pointer to ch_mfg_info_t structure to be updated
 *
 * \return 0 if success, 1 if error
 *
 * This function sets fields in a \a ch_mfg_info_t structure with manufacturing
 * information for the specific sensor device.  These fields include:
 *  - mfg_site - manufacturing location where sensor was made
 *  - mfg_year - year when sensor was made
 *  - mfg_week - work-week number within the year when sensor was made
 *  - product_code - numeric identifier for the sensor product type
 *  - package_code - numeric identifier for the sensor package type
 *  - module_code - numeric identifier for the sensor module type
 *  - mems_code - numeric identifier for the MEMS ultrasonic transducer type
 *
 * See also \a ch_get_sensor_id(), \a ch_get_part_number().
 */
uint8_t ch_get_mfg_info(ch_dev_t *dev_ptr, ch_mfg_info_t *info_ptr);

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
uint32_t ch_measure_pmut_frequency(ch_dev_t *dev_ptr);

#endif  // INCLUDE_SHASTA_SUPPORT

/*!
 * \brief Get the sensor CPU frequency, in Hz.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return sensor CPU frequency, in Hz
 *
 * This function returns the processor speed, in Hz, for the micro-controller in
 * the ultrasound sensor.
 */
uint32_t ch_get_cpu_frequency(ch_dev_t *dev_ptr);

/*!
 * \brief Configure the sensor real-time clock (RTC).
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param rtc_source	RTC source (internal or external)
 * \param rtc_freq 		RTC frequency in Hz, or CH_RTC_USE_BUS_SPEED,
 * 						or zero to use factory test result
 *
 * \return 0 if success, 1 if error
 *
 * This function changes the default real-time clock (RTC) configuration to
 * meet special requirements and system limitations.  In most applications,
 * this function is not needed and should not be called.
 *
 * Two options may be set.  For the internal RTC clock, this function can specify
 * alternatives to the standard clock calibration.  Or, this function can
 * indicate that an external clock source be used to drive the sensor's RTC
 * functions.
 *
 * An accurate measurement of the sensor's RTC clock is an important part of the
 * time-of-flight calculations performed by the ultrasonic sensor and SonicLib.
 * Any inaccuracy in the RTC frequency value will directly result in inaccuracy
 * in time-of-flight, and therefore range, measurements.
 *
 * ### Internal RTC Calibration
 * Normally, the sensor's internal RTC clock frequency is measured during sensor
 * initialization, using an external timed pulse (typically 100 ms) on the sensor
 * INT line.  This pulse takes place during \a ch_group_start().  Using a timed
 * calibration pulse is recommended, because it gives the best overall sensor accuracy.
 * In some situations, however, it may be impossible or inconvenient to apply a
 * sufficiently accurate timed pulse to calibrate the RTC.  This function provides
 * two alternative ways to set the frequency value, with some sacrifice in ultimate
 * sensor accuracy.
 *
 * This function can specify the frequency, in Hz, for the RTC using either the stored
 * factory test result or a custom value.  This function does not actually change the
 * sensor's internal RTC frequency, it simply sets the numeric value that will be used
 * in calculations where the RTC frequency is needed.
 *
 * #### Using the Factory RTC Calibration
 * ICU sensors contain factory test data that includes a measurement of the sensor's
 * internal RTC frequency.  This value provides a reasonable substitute for performing
 * full calibration using a calibration pulse.
 *
 * To use the factory RTC calibration data, specify \a CH_RTC_SRC_INTERNAL for
 * \a rtc_source and a value of zero for \a rtc_freq.
 *
 * Factory RTC calibration values are not available for CH101 or CH201 sensors.
 *
 * #### Using the I/O Bus Clock to Estimate RTC Frequency
 * In some cases, it is possible to use the I/O bus clock as a reference for calibrating
 * the RTC.  (This feature is only available in select sensor f/w variants.)
 *
 * To use the bus clock for calibration, specify \a CH_RTC_SRC_INTERNAL for
 * \a rtc_source, and set \a rtc_freq to \a CH_RTC_USE_BUS_SPEED.
 *
 * For CH101/CH201 sensor types that support this calibration mode, the I2C bus
 * clock (SCL) speed is assumed to be 400000 Hz by default.  If a different, more
 * accurate value for the bus clock speed is available, it can be specified
 * by defining \a CHIRP_I2C_BUS_SPEED_HZ in the \b chirp_board_config.h file in the
 * board support package, and setting the value to the correct bus speed.  Inaccuracies
 * in the bus clock rate value will affect frequency and range measurements by the sensor.
 *
 * #### Supplying an Estimated RTC Frequency
 * If \a rtc_freq is not zero or CH_RTC_USE_BUS_SPEED, the specified value will be
 * used in all calculations requiring the RTC frequency.  Normal calibration using a
 * pulse is not performed.  The \a rtc_freq value should be the best available
 * estimate of the RTC frequency for this device.
 *
 * To use an estimated RTC frequency, specify \a CH_RTC_SRC_INTERNAL for
 * \a rtc_source, and set \a rtc_freq to the approximate RTC frequency, in Hz.
 *
 * If no other estimate is available, \a rtc_freq may be specified as \a CH_RTC_FREQ_TYPICAL
 * (29000 Hz) for a rough approximation of a typical RTC frequency.
 *
 * This option is a last choice, due to the impact on measurement accuracy, but it will
 * allow measurements to be completed.
 *
 * ### Using an External RTC Clock
 * This function can also set the source of the sensor's real-time clock.  By default,
 * the sensor will use its internal oscillator as the RTC clock time base.  To use the
 * internal RTC, no special action is required, and this routine does not have to be called
 * unless you are changing the calibration values described above.
 *
 * For enhanced timing accuracy, an external clock source (e.g. crystal oscillator) may be
 * connected to the ICU sensor.  This may be used to maintain a more exact measurement interval
 * for sensors operating in free-running mode (CH_MODE_FREERUN).
 *
 * To enable an external clock source for the RTC, set \a rtc_source to \a CH_RTC_SRC_EXTERNAL,
 * and set \a rtc_freq to the frequency of the clock signal in Hz (e.g. 32768 for a
 * 32.768 kHz crystal).
 *
 * ### When to Call this Function
 * This function should be called after \a ch_init() but before \a ch_group_start().
 * This function must be called before \a ch_group_start(), because RTC calibration is
 * normally done then.  When this function is used, the sensor will not require or perform
 * automatic RTC calibration using a timed pulse.
 *
 * All sensors in a sensor group must use the same calibration method, automatic (default)
 * or manual (using this routine for each sensor in the group before \a ch_group_start()).
 *
 * \note This function may only be called during sensor initialization, after \a ch_init()
 * and before \a ch_group_start().  Use at any other time will result in undefined behavior.
 *
 * See also \a ch_get_rtc_frequency().
 */
uint8_t ch_set_rtc(ch_dev_t *dev_ptr, ch_rtc_src_t rtc_source, uint16_t rtc_freq);

/*!
 * \brief Get the sensor real-time clock (RTC) frequency, in Hz.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return sensor RTC frequency, in Hz
 *
 * This function returns the real-time clock (RTC) frequency, in Hz, for the
 * micro-controller in the ultrasound sensor.
 */
uint16_t ch_get_rtc_frequency(ch_dev_t *dev_ptr);

/*!
 * \brief Configure ultrasound transducer clock.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param clock_cfg 	clock configuration setting
 *
 * \return 0 if success, 1 if error
 *
 * This function configures the PMUT clock input and output settings to allow
 * the multiple sensors to share a common clock signal.  One sensor may be
 * set to output the signal from the PMUT clock, while others may be set
 * to use that signal as a clock input.  This permits very exact frequency
 * matching for critical applications.  Alternatively, all sensors may
 * be set to use an independent, external clock signal.
 *
 * This function may only be called after \a ch_group_start() has initialized
 * the sensors.  The original PMUT clock settings will be modified,
 * and the new settings will be applied immediately.  The PMUT clock settings
 * must be set separately for each sensor.
 *
 * - Normally, the PMUT clock is internal and the signal is not output on the
 * sensor MUTCLK pad.  This function is not needed in this case.  (This is the
 * default CH_PMUT_CLK_DEFAULT configuration.)
 *
 * - To enable output of the sensor's PMUT clock on the MUTCLK pad, set \a clock_cfg
 * to CH_PMUT_CLK_OUTPUT_AUTO or CH_PMUT_CLK_OUTPUT_ENABLE. The AUTO setting allows
 * the ICU part to control the power state of the clock. In this case, the clock
 * will only be available while the ICU part is actively performing a measurement.
 * This is a good option to use when multiple parts will be active simultaneously.
 * The ENABLE option will unconditionally force the clock on. This can be used
 * in situations where the clock should be available even if the part providing it
 * is inactive, such as during transmit optimization.
 *
 * - The output frequency of the signal on the pad will be 16 times the sensor's
 * acoustic operating frequency.
 *
 * - To use an input signal on the MUTCLK pad as the external PMUT clock source,
 * set \a clock_cfg to CH_PMUT_CLK_SRC_EXTERNAL.  In this configuration, the
 * sensor's PMUT will operate at 1/16 the input clock signal frequency.
 *
 * - To restore the default PMUT clock configuration (i.e. to un-do either operation),
 * set \a clock_cfg to CH_PMUT_CLK_DEFAULT.
 *
 * When one sensor supplies the clock for one or more other sensors, the sequence of
 * enabling and disabling the clock settings across the sensors is important.
 * The clock source must be present whenever a secondary sensor is
 * configured to use an external clock source.
 * - When enabling, the clock source sensor should be set to CH_PMUT_CLK_OUTPUT_AUTO or
 *   CH_PMUT_CLK_OUTPUT_ENABLE first, then the other sensor(s) should
 *   be set to CH_PMUT_CLK_SRC_EXTERNAL.
 * - When disabling, the secondary sensor(s) should be set to CH_PMUT_CLK_DEFAULT
 *   first, then the clock source sensor should be set to CH_PMUT_CLK_DEFAULT.
 *
 * If an independent clock source (not from a sensor) is used, that input signal
 * must be present and \a ch_group_set_pmut_clock_freq() must be called to specify the clock
 * frequency before the sensors are set to CH_PMU_CLK_SRC_EXTERNAL.
 *
 * The \a ch_get_frequency() function will report the current acoustic operating
 * frequency of the PMUT, regardless of the clock source.  So, if the sensor is using an
 * external clock source, the indicated frequency will match that of the sensor supplying
 * the clock signal, or 1/16 the input clock rate if an independent signal.
 *
 * Only one shared PMUT clock signal can be used within a sensor group.  Individual
 * sensors are not required to use the shared clock.
 *
 * See also \a ch_get_pmut_clock(), \a ch_group_set_pmut_clock_freq().
 *
 * \note This feature is not available on CH101 or CH201 sensors.
 */
uint8_t ch_set_pmut_clock(ch_dev_t *dev_ptr, ch_pmut_clk_cfg_t clock_cfg);

/*!
 * \brief Get ultrasound transducer clock configuration.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function returns the current configuration setting for the PMUT clock.
 *
 * See also \a ch_set_pmut_clock().
 *
 * \note On CH101 and CH201 sensors, this function always returns CH_PMUT_CLK_DEFAULT.
 */
ch_pmut_clk_cfg_t ch_get_pmut_clock(ch_dev_t *dev_ptr);

/*!
 * \brief Specify the transducer clock input frequency for a group of sensors
 *
 * \param grp_ptr 			pointer to the ch_group_t sensor group descriptor structure
 * \param pmut_clock_freq 	frequency of input clock signal, in Hz
 *
 * \return 0 if success, 1 if error
 *
 * This function is used only in unusual designs in which the ultrasonic
 * transducers (PMUTs) of multiple sensors share an independent, external
 * clock source.  This function is not needed if the sensors each use their
 * own clock (the default) or if one sensor supplies the PMUT clock signal
 * for others.  (See \a ch_set_pmut_clock().)
 *
 * This function specifies the frequency of the external clock signal, in Hz.
 * The sensors will operate at an acoustic frequency of 1/16 the input clock
 * rate.  For example, if the input clock rate is 800 kHz, the sensor will
 * operate at 50 kHz.
 *
 * The input clock rate must be appropriate for the specific sensor model
 * being used.  Radical shifts in operating frequency are not possible.
 *
 * The input clock signal must be present, and this function must be called to
 * specify the frequency before \a ch_set_pmut_clock() is used to enable the
 * external clock input for any sensors.
 *
 * Only one shared PMUT clock signal can be used within a sensor group.
 *
 * See also \a ch_group_get_pmut_clock_freq(), \a ch_set_pmut_clock().
 *
 * \note This feature is not available on CH101 or CH201 sensors.
 */
void ch_group_set_pmut_clock_freq(ch_group_t *grp_ptr, uint32_t pmut_clock_freq);

/*!
 * \brief Get the transducer clock input frequency for a group of sensors
 *
 * \param grp_ptr 			pointer to the ch_group_t sensor group descriptor structure
 *
 * \return		frequency of group transducer clock signal in Hz, or zero if no shared clock
 *
 * This function is used only in designs in which the ultrasonic
 * transducers (PMUTs) of multiple sensors in a group share a clock source.
 * The clock source may be output from one of the sensors, or it may be
 * from an independent signal source.  (See \a ch_set_pmut_clock().)
 *
 * This function returns the frequency of the group PMUT clock signal, in Hz,
 * regardless of its source.  The returned frequency will be zero if no sensor
 * is outputting a clock signal and no independent clock rate has been specified
 * using \a ch_set_pmut_clock_freq().
 *
 * The sensors operate at an acoustic frequency of 1/16 the PMUT clock
 * rate.  For example, if the reported clock rate is 800 kHz, the sensors are
 * operating at 50 kHz.
 *
 * See also \a ch_group_set_pmut_clock_freq(), \a ch_set_pmut_clock().
 *
 * \note This feature is not available on CH101 or CH201 sensors.
 */
uint32_t ch_group_get_pmut_clock_freq(ch_group_t *grp_ptr);

/*!
 * \brief Set data ready interrupt delay interval.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param delay_ms 		time, in milliseconds, for sensor to delay after measurement
 *
 * \return 0 if success, 1 if error
 *
 * This function sets a delay interval that will cause the sensor to wait slightly
 * after a measurement completes before issuing a data ready interrupt.  It is
 * used in special circumstances to handle unusual timing constraints.  Normally,
 * this function should not be used.
 *
 * \a delay_ms specifies the time, in milliseconds, that the sensor will delay
 * after the measurement completes before generating the interrupt signal.
 *
 * The granularity of this delay is limited by the period of the sensor's internal
 * wake cycle timer, so in some cases the \a delay_ms value will be increased to match
 * the next whole number of wake cycles.  (A granularity of about 4 ms is typical.)
 *
 * The \a ch_get_data_ready_delay() function may be used to determine the actual
 * delay period, after any adjustment to match the sensor wake cycles.
 *
 * \note This function is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_set_data_ready_delay(ch_dev_t *dev_ptr, uint8_t delay_ms);

/*!
 * \brief Get data ready interrupt delay interval.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return  			time, in milliseconds, that sensor will delay after measurement
 *
 * This function returns the time, in milliseconds, that the sensor will wait between
 * the completion of a measurement cycle and generating a data ready interrupt.  The
 * delay may be slightly greater than the value specified during \a ch_set_data_ready_delay(),
 * due to the granularity of the sensor's wake cycle timer.
 *
 * \note This function is only available in select Chirp sensor firmware versions.
 */
uint8_t ch_get_data_ready_delay(ch_dev_t *dev_ptr);

/*!
 * \brief Get the number of valid output samples in last measurement.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return number of output samples in last measurement
 *
 * This function returns the number of valid samples in the most recently completed measurement,
 * as reported by the sensor.  The sensor will be queried dynamically over the I/O bus interface.
 *
 * In general, this number will match the configured sample count for the last measurement, which
 * can be obtained using \a ch_get_num_samples().  That function is recommended for typical use,
 * because it requires no additional I/O to the sensor.
 *
 * \note For CH101 and CH201 sensors, this function will always return the configured sample
 * count, not a dynamic value from the sensor (i.e. it is identical to \a ch_get_num_samples()).
 *
 * See also \a ch_get_num_samples(), \a ch_meas_get_num_samples().
 */
uint16_t ch_get_num_output_samples(ch_dev_t *dev_ptr);

/*!
 * \brief Trigger a measurement using software (SPI) interface.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 * This function sends a special command to the sensor over the SPI bus to trigger a measurement.
 * The software interface is always used regardless of the trigger type that has been set using
 * \a ch_set_trigger_type().
 *
 * This may be used in place of a standard hardware trigger using a GPIO line, although there
 * will be more latency and less exact timing control.
 *
 * See also \a ch_trigger().
 */
void ch_trigger_soft(ch_dev_t *dev_ptr);

/*!
 * \brief Set the trigger type for a sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param trig_type 	trigger type to be used, CH_TRIGGER_TYPE_HW or CH_TRIGGER_TYPE_SW
 *
 * This function sets the trigger type to be used to initiate a measurement on a sensor
 * that is in triggered mode.  (Sensors in free-running mode are self-triggered based on
 * an internal timer.)
 *
 * By default (if this routine is not called), sensors are triggered using a hardware signal
 * on the INT line.  For ICU sensors, either there are two INT lines, INT1 and INT2.  The line
 * to be used for triggering is selected by the CHIRP_SENSOR_TRIG_PIN definition in the
 * chirp_board_config.h file.
 *
 * Alternatively, a measurement may be initiated via software, using a SPI command sent to the
 * sensor.  This may be used in place of a standard hardware trigger using a GPIO line, although there
 * will be more latency and less exact timing control.  To enable software triggering, set \a trig_type
 * to CH_TRIGGER_TYPE_SW.
 *
 * See also \a ch_trigger(), \a ch_trigger_soft(), \a ch_get_trigger_type().
 *
 * \note Software triggering is not available for CH101 and CH201 sensors, so hardware triggering is
 * always used.  Calling this routine will have no effect.
 */
void ch_set_trigger_type(ch_dev_t *dev_ptr, ch_trigger_type_t trig_type);

/*!
 * \brief Get the trigger type for a sensor.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return  		trigger type, either CH_TRIGGER_TYPE_HW or CH_TRIGGER_TYPE_SW
 *
 * This function gets the current trigger type to be used to initiate a measurement on a sensor
 * when in triggered mode.
 *
 * By default, sensors are triggered using a hardware signal on the INT line, and this
 * function will return CH_TRIGGER_TYPE_HW.
 *
 * Alternatively, software triggering may be used, using a special SPI command to the sensor.  In this
 * case, this function will return CH_TRIGGER_TYPE_SW.
 *
 * See also \a ch_set_trigger_type(), \a ch_trigger().
 */
ch_trigger_type_t ch_get_trigger_type(ch_dev_t *dev_ptr);

/*!
 * \brief Get measurement status.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 * \param meas_num		measurement number
 *
 * \return status
 *
 * This function returns the current measurement status in the sensor.  It may be used to
 * help determine if valid measurement I/Q data can be read from the sensor.
 *
 * A status value of CH_MEAS_STATUS_DONE indicates that complete measurement data is available
 * for reading.  A value of CH_MEAS_STATUS_PENDING indicates that a measurement is in progress,
 * and the current data values should not be used.
 *
 * Note that this routine only reports the status at the time it is called.
 *
 * See also \a ch_trigger(), \a ch_trigger_soft().
 *
 * \note For CH101 and CH201 sensors, \a meas_num should be set to CH_DEFAULT_MEAS_NUM.
 *
 * \note This function is only available in select Chirp sensor firmware versions.
 */
ch_meas_status_t ch_meas_get_status(ch_dev_t *dev_ptr, uint8_t meas_num);

/*!
 * \brief Initialize a log in the specified log format.
 *
 * \param grp_ptr 			pointer to the ch_group_t descriptor for this group of sensors
 * \param format 			format of the log. For example, CH_LOG_FMT_REDSWALLOW
 * \param config_ptr 		pointer to log config structure that contains the input values of the log
 *
 * \return a Log ID value to be used later when appending the log
 *
 * This function initializes a sensor data log in the specified log format.
 */
uint8_t ch_log_init(ch_group_t *grp_ptr, ch_log_fmt_t format, ch_log_cfg_t *config_ptr);

/*!
 * \brief Append received sensor data to log.
 *
 * \param log_id 			log ID to specify the log to use
 * \param format 			format of the log
 * \param timestamp 		current time in us
 * \param log_data_ptr 		pointer to log data structure that contains the log data
 *
 * This function appends received sensor data (including I/Q data) to the log in the specified log format.
 * The function takes a new Log ID returns by \a ch_log_init() function to specify the log to use.
 *
 * The function should be used when the previous measurement has completed and all needed
 * data has been read from the device (including I/Q data)
 */
void ch_log_append(uint8_t log_id, ch_log_fmt_t format, uint64_t timestamp, ch_log_data_t *log_data_ptr);

/*!
 * \brief Enable watchdog timer in sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 *  This function enables the watchdog timer function in the sensor.  When the watchdog timer
 *  is enabled, the sensor must complete a measurement within approximately one second or the
 *  timer will expire.  The timer is reset every time a measurement completes.
 *
 *  If the watchdog timer expires, the sensor will generate an interrupt and will specify
 *  CH_INTERRUPT_TYPE_WATCHDOG as the interrupt type.  This interrupt type is passed
 *  as a parameter to the application's sensor interrupt callback routine that was registered
 *  using \a ch_io_int_callback_set().  That callback routine should examine the interrupt
 *  type and take appropriate action if a watchdog timeout occurred.
 *
 *  \note This feature is only available on ICU sensors.  For CH101 and CH201 sensors, the watchdog
 *  timer is enabled by using a different sensor firmware image (these firmware types have "_wd" in
 *  their names).  Not all CH101 and CH201 firmware types have equivalent watchdog-enabled versions.
 *
 *  See also \a ch_watchdog_disable().
 */
uint8_t ch_watchdog_enable(ch_dev_t *dev_ptr);

/*!
 * \brief Disable watchdog timer in sensor.
 *
 * \param dev_ptr 		pointer to the ch_dev_t descriptor structure
 *
 * \return 0 if success, 1 if error
 *
 *  This function disables the watchdog timer function in the sensor.
 *
 *  \note This feature is only available on ICU sensors.  For CH101 and CH201 sensors, the watchdog
 *  timer is enabled or disabled by using a different sensor firmware image.
 *
 *  See also \a ch_watchdog_enable().
 */
uint8_t ch_watchdog_disable(ch_dev_t *dev_ptr);

/*!
 * \brief Check if sensor reset has occurred.
 *
 * \param dev_ptr       pointer to the ch_dev_t descriptor structure
 * \param reset_state_ptr   pointer to variable that will be updated with the ch_sensor_reset_state_t value.
 *  0 = No Reset, 1 = Reset has occurred.
 *
 *  \return 0 if successful, non-zero otherwise
 *
 * This function calls the driver function to check if the sensor has reset.
 *
 * This API can be called periodically in a measurement loop to check if the sensor was arbitrarily reset.
 * If this reset event is detected during normal sensor operation the sensor has to be
 * completely re-initialized similar to a power-on condition.
 *
 */
uint8_t ch_check_reset_state(ch_dev_t *dev_ptr, ch_sensor_reset_state_t *reset_state_ptr);

#ifdef __cplusplus
}
#endif

#endif /* __SONICLIB_H_ */
