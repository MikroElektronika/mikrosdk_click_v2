/*! \file ch_extra_display_utils.h
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
#ifndef CH_EXTRA_DISPLAY_UTILS_H_
#define CH_EXTRA_DISPLAY_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <invn/soniclib/soniclib.h>

/**
 * @brief      Display informations about sensor after firmware is loaded
 *
 * @param      grp_ptr  pointer to the ch_group_t descriptor for this group of sensors
 */
void ch_extra_display_init_info(ch_group_t *grp_ptr);

/**
 * @brief      Display informations about the configuration of measure of sensor
 *
 * @param      dev_ptr  pointer to the ch_dev_t descriptor structure
 *
 * @return     0 if configuration has been correctly displayed, 1 otherwise
 */
uint8_t ch_extra_display_config_info(ch_dev_t *dev_ptr);

#ifdef __cplusplus
}
#endif

#endif /* CH_EXTRA_DISPLAY_UTILS_H_ */
