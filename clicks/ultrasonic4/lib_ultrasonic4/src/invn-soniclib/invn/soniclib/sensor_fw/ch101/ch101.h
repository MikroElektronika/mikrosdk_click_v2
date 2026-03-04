/*! \file ch101.h
 *
 * \brief Internal definitions for the Chirp CH101 ultrasonic sensor.
 *
 * This file contains various hardware-defined values for the CH101 sensor.

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

#ifndef CH101_H_
#define CH101_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CH101_DATA_MEM_SIZE 0x800
#define CH101_DATA_MEM_ADDR 0x0200
#define CH101_PROG_MEM_SIZE 0x800
#define CH101_PROG_MEM_ADDR 0xF800
#define CH101_FW_SIZE       CH101_PROG_MEM_SIZE

#define CH101_BANDWIDTH_INDEX_1 6 /*!< Index of first sample to use for calculating bandwidth. */
#define CH101_BANDWIDTH_INDEX_2                                                                                        \
	(CH101_BANDWIDTH_INDEX_1 + 1) /*!< Index of second sample to use for calculating bandwidth. */
#define CH101_SCALEFACTOR_INDEX 4 /*!< Index for calculating scale factor. */

#define CH101_MAX_TICK_INTERVAL 128

#define CH101_DCO_LOW              (100)
#define CH101_DCO_HIGH             (250)
#define CH101_DCO_SEARCH_THRESHOLD (100)  // Hz, if error is above this, do a search
#define CH101_REVDRIVE_DEFAULT     (2)

#ifdef __cplusplus
}
#endif

#endif
