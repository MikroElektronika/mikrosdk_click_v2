/*!
 * @file      lr1110_modem_common.h
 *
 * @brief     modem driver common definition for LR1110
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

#ifndef LR1110_MODEM_COMMON_H
#define LR1110_MODEM_COMMON_H

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
 * @brief Length of data buffer for reset event
 */
#define LR1110_MODEM_EVENT_RESET_COUNT_DATA_LENGTH ( 2 )

/*!
 * @brief Length of data buffer for TX done event
 */
#define LR1110_MODEM_EVENT_TX_DONE_STATUS_DATA_LENGTH ( 2 )

/*!
 * @brief Length of data buffer for downlink data event
 */
#define LR1110_MODEM_EVENT_DOWN_DATA_DATA_LENGTH ( 2 )

/*!
 * @brief Length of data buffer for file upload done event
 */
#define LR1110_MODEM_EVENT_UPLOAD_DONE_DATA_LENGTH ( 2 )

/*!
 * @brief Length of data buffer for setting configured by Device Management event
 */
#define LR1110_MODEM_EVENT_SET_CONF_DATA_LENGTH ( 2 )

/*!
 * @brief Length of data buffer for link ADR update event
 */
#define LR1110_MODEM_EVENT_LINK_STATUS_DATA_LENGTH ( 2 )

/*!
 * @brief Maximal length of event data buffer
 */
#define LR1110_MODEM_EVENT_MAX_LENGTH_BUFFER ( 1024 )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*!
 * @brief Command group identifier
 */
typedef enum
{
    LR1110_MODEM_GROUP_ID_SYSTEM = 0x01,  //!< Group ID for system commands
    LR1110_MODEM_GROUP_ID_WIFI   = 0x03,  //!< Group ID for Wi-Fi commands
    LR1110_MODEM_GROUP_ID_GNSS   = 0x04,  //!< Group ID for GNSS commands
    LR1110_MODEM_GROUP_ID_MODEM  = 0x06   //!< Group ID for modem commands
} lr1110_modem_api_group_id_t;

/*!
 * @brief Command return code (RC)
 */
typedef enum
{
    LR1110_MODEM_RESPONSE_CODE_OK                  = 0x00,  //!< Driver command executed successfully
    LR1110_MODEM_RESPONSE_CODE_UNKOWN              = 0x01,  //!< Command code unknown
    LR1110_MODEM_RESPONSE_CODE_NOT_INITIALIZED     = 0x03,  //!< Command not initialized
    LR1110_MODEM_RESPONSE_CODE_INVALID             = 0x04,  //!< Invalid command parameters
    LR1110_MODEM_RESPONSE_CODE_BUSY                = 0x05,  //!< Command cannot be executed now
    LR1110_MODEM_RESPONSE_CODE_FAIL                = 0x06,  //!< Command execution failed
    LR1110_MODEM_RESPONSE_CODE_BAD_FILE_UPLOAD_CRC = 0x08,  //!< File upload CRC check failed
    LR1110_MODEM_RESPONSE_CODE_BAD_SIZE            = 0x0A,  //!< Size check failed
    LR1110_MODEM_RESPONSE_CODE_BAD_FRAME           = 0x0F,  //!< SPI command checksum failed or CRC failed
    LR1110_MODEM_RESPONSE_CODE_NO_TIME             = 0x10   //!< GNSS time synchronisation lost
} lr1110_modem_response_code_t;

/*!
 * @brief Event type for modem operation
 */
typedef enum
{
    LR1110_MODEM_LORAWAN_EVENT_RESET          = 0x00,  //!< Modem has reset
    LR1110_MODEM_LORAWAN_EVENT_ALARM          = 0x01,  //!< Alarm time expired
    LR1110_MODEM_LORAWAN_EVENT_JOINED         = 0x02,  //!< Network successfully joined
    LR1110_MODEM_LORAWAN_EVENT_TX_DONE        = 0x03,  //!< Frame transmitted
    LR1110_MODEM_LORAWAN_EVENT_DOWN_DATA      = 0x04,  //!< Downlink data received
    LR1110_MODEM_LORAWAN_EVENT_UPLOAD_DONE    = 0x05,  //!< File upload completed
    LR1110_MODEM_LORAWAN_EVENT_SET_CONF       = 0x06,  //!< Configuration has been changed by Device Manager
    LR1110_MODEM_LORAWAN_EVENT_MUTE           = 0x07,  //!< Modem has been muted or un-muted by Device Manager
    LR1110_MODEM_LORAWAN_EVENT_STREAM_DONE    = 0x08,  //!< Last data stream fragment sent
    LR1110_MODEM_LORAWAN_EVENT_JOIN_FAIL      = 0x0A,  //!< Attempt to join network failed
    LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE = 0x0B,  //!< Wi-Fi passive scan done
    LR1110_MODEM_LORAWAN_EVENT_GNSS_SCAN_DONE = 0x0C,  //!< GNSS scan done or almanac update done
    LR1110_MODEM_LORAWAN_EVENT_TIME_UPDATED_ALC_SYNC =
        0x0D,  //!< Time updated by Application Layer Clock synchronization
    LR1110_MODEM_LORAWAN_EVENT_ADR_MOBILE_TO_STATIC =
        0x0E,  //!< Indicates to the host that the modem automatically switches Adaptative Data Rate configuration from
               //!< mobile to static when connection timeout occurs
    LR1110_MODEM_LORAWAN_EVENT_NEW_LINK_ADR = 0x0F,  //!< Modem received a LinkADR request
    LR1110_MODEM_LORAWAN_EVENT_NO_EVENT     = 0xFF   //!< No event: notify the host that no data have to be read
} lr1110_modem_lorawan_event_type_t;

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_COMMON_H

/* --- EOF ------------------------------------------------------------------ */
