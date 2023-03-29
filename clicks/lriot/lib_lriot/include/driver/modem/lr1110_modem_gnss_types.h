/*!
 * @file      lr1110_modem_gnss_types.h
 *
 * @brief     GNSS scan driver types definition for LR1110 modem
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

#ifndef LR1110_MODEM_GNSS_TYPES_H
#define LR1110_MODEM_GNSS_TYPES_H

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
 * @brief Number of almanacs in full update payload
 */
#define LR1110_MODEM_GNSS_FULL_UPDATE_N_ALMANACS ( 128 )

/*!
 * @brief Size of the almanac of a single satellite when reading
 */
#define LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE ( 22 )

/*!
 * @brief Size of the almanac of a single satellite when writing
 */
#define LR1110_MODEM_GNSS_SINGLE_ALMANAC_WRITE_SIZE ( 20 )

/*!
 * @brief Size of the almanac for all satellites when writing
 */
#define LR1110_MODEM_GNSS_FULL_ALMANAC_WRITE_BUFFER_SIZE \
    ( ( LR1110_MODEM_GNSS_FULL_UPDATE_N_ALMANACS * LR1110_MODEM_GNSS_SINGLE_ALMANAC_WRITE_SIZE ) + 20 )

/*!
 * @brief Position of the destination ID in the scan result buffer
 */
#define LR1110_MODEM_GNSS_SCAN_RESULT_DESTINATION_INDEX ( 0 )

/*!
 * @brief Position of the scan done event type in the scan result buffer, \note a event type exists only if the
 * destination is LR1110_MODEM_GNSS_DESTINATION_HOST
 */
#define LR1110_MODEM_GNSS_SCAN_RESULT_EVENT_TYPE_INDEX ( 1 )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*!
 * @brief GNSS Event value for Host destinated message
 *
 * These values are the meaning of the second byte of a message destinated to host obtained when reading
 * LR1110_MODEM_LORAWAN_EVENT_GNSS_SCAN_DONE buffer
 */
typedef enum
{
    LR1110_MODEM_GNSS_SCAN_DONE_PROCESS_OK                                 = 0x00,
    LR1110_MODEM_GNSS_SCAN_DONE_IQ_FAILS                                   = 0x05,
    LR1110_MODEM_GNSS_SCAN_DONE_NO_TIME                                    = 0x06,
    LR1110_MODEM_GNSS_SCAN_DONE_NO_SATELLITE_DETECTED                      = 0x07,
    LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_TOO_OLD                            = 0x08,
    LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_CRC_ERROR             = 0x09,
    LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_FLASH_INTEGRITY_ERROR = 0x0A,
    LR1110_MODEM_GNSS_SCAN_DONE_GLOBAL_ALMANAC_CRC_ERROR                   = 0x0D,
    LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_VERSION_NOT_SUPPORTED              = 0x0E
} lr1110_modem_gnss_scan_done_event_t;

/*!
 * @brief GNSS response type indicates the destination: Host MCU or GNSS solver
 */
typedef enum
{
    LR1110_MODEM_GNSS_DESTINATION_HOST   = 0x00,  //!< Host MCU
    LR1110_MODEM_GNSS_DESTINATION_SOLVER = 0x01   //!< GNSS Solver
} lr1110_modem_gnss_destination_t;

/*!
 * @brief Search mode for GNSS scan
 */
typedef enum
{
    LR1110_MODEM_GNSS_OPTION_DEFAULT     = 0x00,  //!< Search all requested satellites or fail
    LR1110_MODEM_GNSS_OPTION_BEST_EFFORT = 0x01   //!< Add additional search if not all satellites are found
} lr1110_modem_gnss_search_mode_t;

/*!
 * @brief bit mask indicating which information is added in the output payload
 */
enum lr1110_modem_gnss_result_mask_e
{
    LR1110_MODEM_GNSS_PSEUDO_RANGE_MASK = ( 1 << 0 ),
    LR1110_MODEM_GNSS_DOPPLER_MASK      = ( 1 << 1 ),
    LR1110_MODEM_GNSS_BIT_CHANGE_MASK   = ( 1 << 2 )
};

/*!
 * @brief Constellation identifiers
 */
typedef enum
{
    LR1110_MODEM_GNSS_GPS_MASK    = 0x01,
    LR1110_MODEM_GNSS_BEIDOU_MASK = 0x02
} lr1110_modem_gnss_constellation_t;

/*!
 * @brief Almanac Constellation identifiers
 */
typedef enum
{
    LR1110_MODEM_GNSS_ALMANAC_CONSTELLATION_GPS       = 0x01,
    LR1110_MODEM_GNSS_ALMANAC_CONSTELLATION_BEIDOU    = 0x02,
    LR1110_MODEM_GNSS_ALMANAC_CONSTELLATION_UNDEFINED = 0x08
} lr1110_modem_gnss_almanac_constellation_id_t;

/*!
 * @brief Frequency search space around the Doppler frequency
 */
typedef enum
{
    LR1110_MODEM_GNSS_FREQUENCY_SEARCH_SPACE_250_HZ = 0x00,
    LR1110_MODEM_GNSS_FREQUENCY_SEARCH_SPACE_500_HZ = 0x01,
    LR1110_MODEM_GNSS_FREQUENCY_SEARCH_SPACE_1_KHZ  = 0x02,
    LR1110_MODEM_GNSS_FREQUENCY_SEARCH_SPACE_2_KHZ  = 0x03
} lr1110_modem_gnss_frequency_search_space_t;

/*!
 * @brief Context status error code
 */
typedef enum
{
    LR1110_MODEM_GNSS_CONTEXT_STATUS_NO_ERROR                         = 0x00,  //!< No error
    LR1110_MODEM_GNSS_CONTEXT_STATUS_ALMANAC_TOO_OLD                  = 0x01,  //!< Almanac too old
    LR1110_MODEM_GNSS_CONTEXT_STATUS_LAST_ALMANAC_UPDATE_CRC_MISMATCH = 0x02,  //!< Last almanac update CRC mismatch
    LR1110_MODEM_GNSS_CONTEXT_STATUS_FLASH_MEMORY_INTEGRITY_ERROR     = 0x03,  //!< Flash memory integrity error
    LR1110_MODEM_GNSS_CONTEXT_STATUS_LAST_ALMANAC_UPDATE_TOO_OLD =
        0x04   //!< Last almanac update time difference more than 1 month
} lr1110_modem_gnss_context_status_error_code_t;

/*!
 * @brief Satellite ID type
 */
typedef uint8_t lr1110_modem_gnss_satellite_id_t;

/*!
 * @brief Bit mask of constellation configurations
 *
 * @see lr1110_modem_gnss_constellation_t
 */
typedef uint8_t lr1110_modem_gnss_constellation_mask_t;

/*!
 * @brief Bit mask of frequency search space configurations
 *
 * @see lr1110_modem_gnss_frequency_search_space_t
 */
typedef uint8_t lr1110_modem_gnss_frequency_search_space_mask_t;

/*!
 * @brief Buffer that holds data for all almanacs full update
 */
typedef uint8_t lr1110_modem_gnss_almanac_full_update_bytestream_t[LR1110_MODEM_GNSS_FULL_ALMANAC_WRITE_BUFFER_SIZE];

/*!
 * @brief Buffer that hold one chunk of almanac for update
 */
typedef uint8_t lr1110_modem_gnss_almanac_one_chunk_bytestream_t[LR1110_MODEM_GNSS_SINGLE_ALMANAC_WRITE_SIZE];

/*!
 * @brief Assistance position.
 */
typedef struct
{
    float latitude;   //!< Latitude 12 bits (latitude in degree * 2048/90) with resolution 0.044°
    float longitude;  //!< Longitude 12 bits (longitude in degree * 2048/180) with resolution 0.088°
} lr1110_modem_gnss_solver_assistance_position_t;

/*!
 * @brief Detected satellite structure
 */
typedef struct
{
    lr1110_modem_gnss_satellite_id_t satellite_id;  //!< Satellite ID
    int8_t                           cnr;           //!< Carrier-to-noise ration (C/N) in dB
} lr1110_modem_gnss_detected_satellite_t;

/*!
 * @brief GNSS timings of the LR1110 modem
 */
typedef struct
{
    uint32_t radio_ms;        //!< Duration with radio on
    uint32_t computation_ms;  //!< Duration of computation
} lr1110_modem_gnss_timings_t;

/*!
 * @brief Version structure of the LR1110 GNSS firmware
 */
typedef struct
{
    uint8_t gnss_firmware;  //!< Version of the firmware
    uint8_t gnss_almanac;   //!< Version of the almanac format
} lr1110_modem_gnss_version_t;

/*!
 * @brief Status message struct in case of operation code = 0x18 (Status Message)
 */
typedef struct
{
    uint8_t  gnss_firmware_version;  //!< GNSS firmware version
    uint32_t global_almanac_crc;  //!< The global CRC is the 32 bit CRC computed on all the flash memory content, on all
                                  //!< 128 satellites. Per sv 21 bytes
    uint8_t  error_code;               //!< Error code
    uint8_t  almanac_update_bit_mask;  //!< Almanac update bit mask
    uint8_t  frequency_search_space;   //!< Frequency search space
} lr1110_modem_gnss_context_t;

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_GNSS_TYPES_H
