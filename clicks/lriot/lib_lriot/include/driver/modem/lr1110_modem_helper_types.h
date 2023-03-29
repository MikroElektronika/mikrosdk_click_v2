/*!
 * @file      lr1110_modem_helper_types.h
 *
 * @brief     helper functions types definition for LR1110 modem
 *
 * Revised BSD License
 * Copyright Semtech Corporation 2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LR1110_MODEM_HELPER_TYPES_H
#define LR1110_MODEM_HELPER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdint.h>

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*!
 * @brief Initial GNSS date in second, 6 January 1980
 */
#define LR1110_MODEM_HELPER_INITAL_GNSS_DATE_SECONDS 315964800

/*!
 * @brief GNSS leap seconds offset in second
 */
#define LR1110_MODEM_HELPER_GNSS_LEAP_SECONDS_OFFSET 18

/*!
 * @brief GPS week number rollover
 */
#define LR1110_MODEM_HELPER_NB_WEEK_PER_WRAP 1024

/*!
 * @brief Number of seconds in per hour
 */
#define LR1110_MODEM_HELPER_NB_SEC_PER_HOUR 3600

/*!
 * @brief Number of hours per day
 */
#define LR1110_MODEM_HELPER_NB_HOUR_PER_DAY 24

/*!
 * @brief Number of days per week
 */
#define LR1110_MODEM_HELPER_NB_DAY_PER_WEEK 7

/**
 * @brief Maximum payload size in byte of a downlink
 */
#define LR1110_MODEM_HELPER_MAX_DOWNLINK_LENGTH 242

/*!
 * @brief Maximum payload size in byte of a nav message
 */
#define LR1110_MODEM_HELPER_GNSS_MAX_NAV_LENGTH 255

/*!
 * @brief Maximum payload size in byte of a Wi-Fi result
 */
#define LR1110_MODEM_HELPER_WIFI_MAX_BUFFER_LENGTH 948  // 12 results * LR1110_WIFI_EXTENDED_FULL_RESULT_SIZE

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/**
 * @brief LR1110 Modem helper status
 */
typedef enum
{
    LR1110_MODEM_HELPER_STATUS_OK    = 0,
    LR1110_MODEM_HELPER_STATUS_ERROR = 3
} lr1110_modem_helper_status_t;

/**
 * @brief Structure holding event-related data
 */
typedef struct
{
    uint8_t event_type;
    uint8_t missed_events;  //!< Number of event_type events missed before the current one
    union
    {
        struct
        {
            uint16_t count;
        } reset;
        struct
        {
            uint8_t status;
        } txdone;
        struct
        {
            int8_t  rssi;  //!< Signed value in dBm + 64
            int8_t  snr;   //!< Signed value in dB given in 0.25dB step
            uint8_t flag;
            uint8_t fport;
            uint8_t data_buf[LR1110_MODEM_HELPER_MAX_DOWNLINK_LENGTH];
            uint8_t length;
        } downdata;
        struct
        {
            uint8_t status;
        } upload;
        struct
        {
            uint8_t tag;
        } setconf;
        struct
        {
            uint8_t status;
        } mute;
         struct
        {
            uint16_t len;
            uint8_t buffer[LR1110_MODEM_HELPER_WIFI_MAX_BUFFER_LENGTH];
        } wifi;
         struct
        {
            uint16_t len;
            uint8_t nav_message[LR1110_MODEM_HELPER_GNSS_MAX_NAV_LENGTH];
        } gnss;
        struct
        {
            uint8_t status;
        } time;
    } event_data;
} lr1110_modem_event_t;

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_HELPER_TYPES_H
