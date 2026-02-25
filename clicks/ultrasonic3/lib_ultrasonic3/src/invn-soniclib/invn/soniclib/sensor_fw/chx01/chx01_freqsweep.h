/*!
 * \file chx01_freqsweep.h
 *
 * \brief Internal definitions for the Chirp CHX01 Frequency Sweep sensor firmware.
 *
 * This file contains function definitions, register offsets and other interfaces
 * for use with the CHX01 Frequency Sweep sensor firmware.  Many of these are designed for
 * compatibility with the Chirp Frequency Sweep production test system.
 * These values are subject to change without notice.
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

#ifndef CHX01_FREQSWEEP_H_
#define CHX01_FREQSWEEP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <invn/soniclib/soniclib.h>
#include <invn/soniclib/ch_rangefinder.h>

#define CHX01_FREQSWEEP_REG_REGMAPFMT     0x00
#define CHX01_FREQSWEEP_REG_OPMODE        0x01
#define CHX01_FREQSWEEP_REG_TICK_INTERVAL 0x02
#define CHX01_FREQSWEEP_REG_WBCFG         0x04
#define CHX01_FREQSWEEP_REG_PERIOD        0x05
#define CHX01_FREQSWEEP_REG_CAL_TRIG      0x06
#define CHX01_FREQSWEEP_REG_MAX_RANGE     0x07
#define CHX01_FREQSWEEP_REG_DCOSTART      0x08
#define CHX01_FREQSWEEP_REG_CAL_RESULT    0x0A
#define CHX01_FREQSWEEP_REG_DCOSTOP       0x0C
#define CHX01_FREQSWEEP_REG_TXLENGTH      0x0E
#define CHX01_FREQSWEEP_REG_READY         0x0F
#define CHX01_FREQSWEEP_REG_DCOSTEP       0x10
#define CHX01_FREQSWEEP_REG_HOLDOFF       0x11
#define CHX01_FREQSWEEP_REG_THRESHOLD     0x12
#define CHX01_FREQSWEEP_REG_PULSE_WIDTH   0x14
#define CHX01_FREQSWEEP_REG_DCODIVIDER    0x15
#define CHX01_FREQSWEEP_REG_RXQUEUE       0x16
#define CHX01_FREQSWEEP_REG_TOF_SF        0x24
#define CHX01_FREQSWEEP_REG_TOF           0x26
#define CHX01_FREQSWEEP_REG_AMPLITUDE     0x28
#define CHX01_FREQSWEEP_REG_DCOCODE       0x2A
#define CHX01_FREQSWEEP_REG_DATA          0x2C

// Maximum number of samples that can be stored; max value of MAX_RANGE
#define CHX01_FREQSWEEP_MAX_SAMPLES 150

// Number of RXQUEUE 16-bit entries
#define CHX01_FREQSWEEP_RXQUEUE_ITEMS 7

// Bit width of each field in RXQUEUE items
#define CHX01_FREQSWEEP_RXQUEUE_BITS_SAMPLES 7
#define CHX01_FREQSWEEP_RXQUEUE_BITS_ATTEN   2
#define CHX01_FREQSWEEP_RXQUEUE_BITS_GAIN    3

// Position of lowest bit in each field of RXQUEUE items
#define CHX01_FREQSWEEP_RXQUEUE_BITPOS_SAMPLES 3
#define CHX01_FREQSWEEP_RXQUEUE_BITPOS_ATTEN                                                                           \
	(CHX01_FREQSWEEP_RXQUEUE_BITPOS_SAMPLES + CHX01_FREQSWEEP_RXQUEUE_BITS_SAMPLES)
#define CHX01_FREQSWEEP_RXQUEUE_BITPOS_GAIN (CHX01_FREQSWEEP_RXQUEUE_BITPOS_ATTEN + CHX01_FREQSWEEP_RXQUEUE_BITS_ATTEN)

// Enumerated values for various registers
#define CHX01_FREQSWEEP_OPMODE_IDLE      0x00
#define CHX01_FREQSWEEP_OPMODE_FREERUN   0x02
#define CHX01_FREQSWEEP_OPMODE_TRIGGERED 0x10
#define CHX01_FREQSWEEP_OPMODE_RX_ONLY   0x20

#define CHX01_FREQSWEEP_PERIOD_IDLE        0
#define CHX01_FREQSWEEP_TICK_INTERVAL_IDLE 2048

#define CHX01_FREQSWEEP_READY_NOTLOCKED 0x00
#define CHX01_FREQSWEEP_READY_NOTREADY  0x01

// ASIC firmware linkage
extern const char *chx01_freqsweep_version;  // version string in fw .c file
extern const uint8_t chx01_freqsweep_fw_text[];
extern const uint8_t chx01_freqsweep_fw_vec[];
extern const uint16_t chx01_freqsweep_text_size;
extern const uint16_t chx01_freqsweep_vec_size;

const unsigned char *get_ram_chx01_freqsweep_init_ptr(void);
uint16_t get_chx01_freqsweep_fw_ram_init_addr(void);
uint16_t get_chx01_freqsweep_fw_ram_init_size(void);

uint8_t chx01_freqsweep_init(ch_dev_t *dev_ptr, fw_info_t **fw_info);

/*!
 * \brief Set the MAX_RANGE register directly.
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 * \param samples Value to write to MAX_RANGE register, determining length of data used in target detection
 *
 * \return 0 if successful
 */
uint8_t chx01_freqsweep_set_samples(ch_dev_t *dev_ptr, uint8_t samples);

uint8_t chx01_freqsweep_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range_mm);

/*!
 * \brief Configure threshold of detection.
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 * \param threshold minimum received echo intensity for detecting a target
 *
 * \return 0 if successful.
 */
uint8_t chx01_freqsweep_set_threshold(ch_dev_t *dev_ptr, uint16_t threshold);

/*!
 * \brief Configure target detection holdoff.
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 * \param holdoff number of samples to discard before starting target detection
 *
 * \return 0 if successful.
 */
uint8_t chx01_freqsweep_set_holdoff(ch_dev_t *dev_ptr, uint8_t holdoff);

/*!
 * \brief Gets measured intensity from the sensor.
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 *
 * This function reads back the amplitude from the sensor. The intensity is representative of the incoming sound
 * pressure.
 *
 * \return Amplitude (arbitrary units).
 */
uint16_t chx01_freqsweep_get_amplitude(ch_dev_t *dev_ptr);

/*!
 * \brief Reads IQ data from sensor and places it into specified buffer.
 * \param dev_ptr Pointer to the ch_dev_t device descriptor
 * \param buf_ptr Buffer to which to store IQ data
 * \param start_sample  starting sample of requested I/Q data
 * \param num_samples  number of samples to return I/Q for
 * \param mode  I/O mode - must be CH_IO_MODE_BLOCK
 * \return 0 on success, nonzero on failure
 */
uint8_t chx01_freqsweep_get_iq_data(ch_dev_t *dev_ptr, uint8_t /*ch_iq_sample_t*/ *buf_ptr, uint16_t start_sample,
                                    uint16_t num_samples, uint8_t /*ch_io_mode_t*/ mode);

/*!
 * \brief Write an entry into the receive settings queue
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 * \param queue_index which position in the queue to write this item
 * \param samples sample count for which these settings will be in effect, Range of values 1-127
 * \param attenuation Range of values 0-3
 * \param gain Range of values 0-4
 */
uint8_t chx01_freqsweep_set_rxqueue_item(ch_dev_t *dev_ptr, uint8_t queue_index, uint8_t samples, uint8_t attenuation,
                                         uint8_t gain);

/*!
 * \brief Check if the sensor has completed its start-up calibration (locking) procedure.
 *
 * \param dev_ptr a pointer to the ch_dev_t device descriptor
 *
 * \return 1 if the sensor is locked, 0 otherwise.
 */
uint8_t chx01_freqsweep_get_locked_state(ch_dev_t *dev_ptr);

void chx01_freqsweep_prepare_pulse_timer(ch_dev_t *dev_ptr);

void chx01_freqsweep_store_pt_result(ch_dev_t *dev_ptr);

void chx01_freqsweep_store_op_freq(ch_dev_t *dev_ptr);

void chx01_freqsweep_store_bandwidth(ch_dev_t *dev_ptr);

void chx01_freqsweep_store_scale_factor(ch_dev_t *dev_ptr);

int chx01_freqsweep_set_pulse_width(ch_dev_t *dev_ptr, uint8_t pulse_width);

int chx01_freqsweep_set_tx_length(ch_dev_t *dev_ptr, uint8_t tx_length);

uint32_t chx01_freqsweep_get_op_freq(ch_dev_t *dev_ptr);

int chx01_freqsweep_set_dco_divider(ch_dev_t *dev_ptr, uint8_t dco_divider);

uint16_t chx01_freqsweep_get_dco_code(ch_dev_t *dev_ptr);

int chx01_freqsweep_set_dco_start(ch_dev_t *dev_ptr, uint16_t dco_start);

int chx01_freqsweep_set_dco_stop(ch_dev_t *dev_ptr, uint16_t dco_stop);

#ifdef __cplusplus
}
#endif

#endif /* CHX01_FREQSWEEP_H_ */
