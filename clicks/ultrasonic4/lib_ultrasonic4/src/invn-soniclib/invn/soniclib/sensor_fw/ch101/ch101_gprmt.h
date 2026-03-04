/*! \file ch101_gprmt.h
 *
 * \brief Internal definitions for the Chirp CH101 GPR Multi-threshold sensor firmware.
 *
 * This file contains register offsets and other values for use with the CH101 GPR
 * Multi-threshold sensor firmware.  These values are subject to change without notice.
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

#ifndef CH101_GPRMT_H_
#define CH101_GPRMT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ch101.h"
#include <invn/soniclib/ch_rangefinder.h>
#include <invn/soniclib/soniclib.h>

/* GPR with multi thresholds firmware registers */
#define CH101_GPRMT_REG_OPMODE         0x01
#define CH101_GPRMT_REG_TICK_INTERVAL  0x02
#define CH101_GPRMT_REG_LOW_GAIN_RXLEN 0x04
#define CH101_GPRMT_REG_PERIOD         0x05
#define CH101_GPRMT_REG_CAL_TRIG       0x06
#define CH101_GPRMT_REG_MAX_RANGE      0x07
#define CH101_GPRMT_REG_THRESH_LEN_0   0x08
#define CH101_GPRMT_REG_THRESH_LEN_1   0x09
#define CH101_GPRMT_REG_CAL_RESULT     0x0A
#define CH101_GPRMT_REG_THRESH_LEN_2   0x0C
#define CH101_GPRMT_REG_THRESH_LEN_3   0x0D
#define CH101_GPRMT_REG_TX_LENGTH      0x10
#define CH101_GPRMT_REG_ST_RANGE       0x12
#define CH101_GPRMT_REG_READY          0x14
#define CH101_GPRMT_REG_THRESH_LEN_4   0x15
#define CH101_GPRMT_REG_THRESHOLDS     0x16  // start of array of six 2-byte threshold levels
#define CH101_GPRMT_REG_TOF_SF         0x22
#define CH101_GPRMT_REG_TOF            0x24
#define CH101_GPRMT_REG_AMPLITUDE      0x26
#define CH101_GPRMT_REG_DATA           0x28

#define CH101_GPRMT_MAX_SAMPLES    (225)  // max number of samples
#define CH101_GPRMT_NUM_THRESHOLDS (6)    // total number of thresholds

extern const char *ch101_gprmt_version;  // version string in fw .c file
extern const uint8_t ch101_gprmt_fw_text[];
extern const uint8_t ch101_gprmt_fw_vec[];
extern const uint16_t ch101_gprmt_text_size;
extern const uint16_t ch101_gprmt_vec_size;

uint16_t get_ch101_gprmt_fw_ram_init_addr(void);
uint16_t get_ch101_gprmt_fw_ram_init_size(void);

const unsigned char *get_ram_ch101_gprmt_init_ptr(void);

uint8_t ch101_gprmt_init(ch_dev_t *dev_ptr, fw_info_t **fw_info);

#ifdef __cplusplus
}
#endif

#endif
