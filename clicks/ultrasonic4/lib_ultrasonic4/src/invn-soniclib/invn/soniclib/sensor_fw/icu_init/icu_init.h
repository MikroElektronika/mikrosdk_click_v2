/*! \file icu_init.h
 *
 * \brief Internal definitions for the Chirp ICU Initialization sensor firmware.
 *
 * This file contains various definitions and values for use with the ICU Init
 * sensor firmware.  These values are subject to change without notice.
 *
 * The ICU Init firmware only performs initialization of the sensor.  It does not
 * perform any measurements.  This firmware is used together with a different
 * firmware image that is loaded and run after the initialization completes.
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

#ifndef ICU_INIT_H_
#define ICU_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <invn/soniclib/details/icu.h>
#include <invn/soniclib/soniclib.h>
/* no algo selected - build minimal <invn/soniclib/sensor_fw/Init> config */
#include <invn/soniclib/sensor_fw/icu_init/icu_algo_format.h>
#include <invn/soniclib/sensor_fw/icu_init/icu_shasta_algo_structs.h>
#include <invn/soniclib/sensor_fw/icu_init/shasta_init_interface.h>

#define ICU_INIT_MAX_SAMPLES 680

extern const char *icu_init_version;  // version string in fw .c file
extern const uint8_t icu_init_fw_text[];
extern const uint8_t icu_init_fw_vec[];
extern const uint16_t icu_init_text_size;
extern const uint16_t icu_init_vec_size;

uint16_t get_icu_init_fw_ram_init_addr(void);
uint16_t get_icu_init_fw_ram_init_size(void);

const unsigned char *get_ram_icu_init_init_ptr(void);

uint8_t icu_init_init(ch_dev_t *dev_ptr, fw_info_t **fw_info);

#ifdef __cplusplus
}
#endif

#endif /* ICU_INIT_H_ */
