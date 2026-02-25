/*! \file ch101_gpr.h
 *
 * \brief Internal definitions for the Chirp CH101 GPR sensor firmware.
 *
 * This file contains register offsets and other values for use with the CH101 GPR
 * sensor firmware.  These values are subject to change without notice.
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

#ifndef CH101_GPR_H_
#define CH101_GPR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ch101.h"
#include <invn/soniclib/ch_rangefinder.h>
#include <invn/soniclib/soniclib.h>

/* GPR firmware registers */
#define CH101_GPR_REG_OPMODE          0x01
#define CH101_GPR_REG_TICK_INTERVAL   0x02
#define CH101_GPR_REG_IN_RINGDOWN_IDX 0x04
#define CH101_GPR_REG_PERIOD          0x05
#define CH101_GPR_REG_CAL_TRIG        0x06
#define CH101_GPR_REG_CAL_TRIG        0x06
#define CH101_GPR_REG_MAX_RANGE       0x07
#define CH101_GPR_REG_IN_RINGDOWN_THS 0x08
#define CH101_GPR_REG_REV_CYCLES      0x0C
#define CH101_GPR_REG_DCO_PERIOD      0x0E
#define CH101_GPR_REG_ST_RANGE        0x12
#define CH101_GPR_REG_READY           0x14
#define CH101_GPR_REG_IN_RINGDOWN     0x15
#define CH101_GPR_REG_TOF_SF          0x16
#define CH101_GPR_REG_TOF             0x18
#define CH101_GPR_REG_AMPLITUDE       0x1A
#define CH101_GPR_REG_CAL_RESULT      0x0A
#define CH101_GPR_REG_DATA            0x1C

#define CH101_GPR_MAX_SAMPLES (225)

extern const char *ch101_gpr_version;  // version string in fw .c file
extern const uint8_t ch101_gpr_fw_text[];
extern const uint8_t ch101_gpr_fw_vec[];
extern const uint16_t ch101_gpr_text_size;
extern const uint16_t ch101_gpr_vec_size;

uint16_t get_ch101_gpr_fw_ram_init_addr(void);
uint16_t get_ch101_gpr_fw_ram_init_size(void);

const unsigned char *get_ram_ch101_gpr_init_ptr(void);

uint8_t ch101_gpr_init(ch_dev_t *dev_ptr, fw_info_t **fw_info);

/*!
 * \brief Get the target "in ringdown" status.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return 0    if the target is absent or far away from the ringdown,
 *         1    when the range is less than about 130mm (default and programmable
 *              using in_ringdown_idx parameter) on CH101 and less than about 200mm on CH201
 *
 * For both sensors, when ch101_gpr_get_target_in_ringdown() goes from 0->1, it
 * will remain at 1 for at least 4 measurements, to prevent glitches.
 * When the target leaves the ringdown region there will be a 4 sample latency before
 * ch101_gpr_get_target_in_ringdown() returns 0.
 *
 */
uint8_t ch101_gpr_get_target_in_ringdown(ch_dev_t *dev_ptr);

/*!
 * \brief Get the amplitude threshold for "in ringdown" detection.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return          the threshold in LSB applied to the second peak of the ringdown
 *                  (sample 15) to recognize if a target is in the ringdown region
 *
 */
uint16_t ch101_gpr_get_in_ringdown_ths(ch_dev_t *dev_ptr);

/*!
 * \brief Set the amplitude threshold "in ringdown" status.
 *
 * \param dev_ptr           pointer to the ch_dev_t descriptor structure
 *        in_ringdown_ths   the threshold in LSB applied to the second peak of
 *                          the ringdown (sample 15) to recognize if a target is
 *                          in the ringdown region. Default value is 3000
 *
 */
void ch101_gpr_set_in_ringdown_ths(ch_dev_t *dev_ptr, uint16_t in_ringdown_ths);

/*!
 * \brief Get the sample index that defines the "in ringdown" region.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *
 * \return          the sample index that defines the "in ringdown" region.
 *                  If the range is under this value, the ch101_gpr_get_target_in_ringdown()
 *                  function will return 1, otherwise 0.
 *
 *
 * \note This is a beta function and might move or change name in a future release.
 */
uint8_t ch101_gpr_get_in_ringdown_idx(ch_dev_t *dev_ptr);

/*!
 * \brief Set the sample index for "in ringdown" status.
 *
 * \param dev_ptr 	pointer to the ch_dev_t descriptor structure
 *        in_ringdown_idx   the sample index that defines the "in ringdown" region.
 *                          Default value is 17 samples equals at about 130mm.
 *
 */
void ch101_gpr_set_in_ringdown_idx(ch_dev_t *dev_ptr, uint8_t in_ringdown_idx);

#ifdef __cplusplus
}
#endif

#endif
