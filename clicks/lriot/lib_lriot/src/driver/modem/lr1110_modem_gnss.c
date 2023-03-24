/*!
 * @file      lr1110_modem_gnss.c
 *
 * @brief     GNSS scan driver implementation for LR1110 modem
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

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "modem/lr1110_modem_gnss.h"
#include "modem/lr1110_modem_hal.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

#ifndef MIN
/*!
 * @brief Helper macro for min evaluation
 */
#define MIN( a, b ) ( ( a > b ) ? b : a )
#endif  // MIN

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/*!
 * @brief Command buffer length for command Set constellation
 */
#define LR1110_MODEM_GNSS_SET_CONSTALLATION_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Command buffer length for command Read constellation
 */
#define LR1110_MODEM_GNSS_READ_CONSTALLATION_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Set almanac update
 */
#define LR1110_MODEM_GNSS_SET_ALMANAC_UPDATE_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Command buffer length for command Read almanac update
 */
#define LR1110_MODEM_GNSS_READ_ALMANAC_UPDATE_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Read firmware version
 */
#define LR1110_MODEM_GNSS_READ_FW_VERSION_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Read supported constellation
 */
#define LR1110_MODEM_GNSS_READ_SUPPORTED_CONSTELLATION_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Almanac full update
 */
#define LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Set frequency search space
 */
#define LR1110_MODEM_GNSS_SET_FREQ_SEARCH_SPACE_CMD_LENGTH ( 2 + 1 )

/*!
 * @brief Command buffer length for command Read frequency search space
 */
#define LR1110_MODEM_GNSS_READ_FREQ_SEARCH_SPACE_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Set assistance position
 */
#define LR1110_MODEM_GNSS_SET_ASSISTANCE_POSITION_CMD_LENGTH ( 2 + 4 )

/*!
 * @brief Command buffer length for command Read assistance position
 */
#define LR1110_MODEM_GNSS_READ_ASSISTANCE_POSITION_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Set crystal error
 */
#define LR1110_MODEM_GNSS_SET_XTAL_ERROR_CMD_LENGTH ( 2 + 2 )

/*!
 * @brief Command buffer length for command Read crystal error
 */
#define LR1110_MODEM_GNSS_READ_XTAL_ERROR_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Push solver message
 */
#define LR1110_MODEM_GNSS_PUSH_SOLVER_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Get context status
 */
#define LR1110_MODEM_GNSS_GET_CONTEXT_STATUS_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Get number of satellites detected
 */
#define LR1110_MODEM_GNSS_GET_NB_SV_SATELLITES_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Get satellites detected
 */
#define LR1110_MODEM_GNSS_GET_SV_SATELLITES_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Get GNSS scan timings
 */
#define LR1110_MODEM_GNSS_GET_TIMINGS_CMD_LENGTH ( 2 )

/*!
 * @brief Command buffer length for command Read almanac by index
 */
#define LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_CMD_LENGTH ( 2 + 2 )

/*!
 * @brief Command buffer length for command Start autonomous scan
 */
#define LR1110_MODEM_GNSS_SCAN_AUTONOMOUS_CMD_LENGTH ( 2 + 3 )

/*!
 * @brief Command buffer length for command Start assisted scan
 */
#define LR1110_MODEM_GNSS_SCAN_ASSISTED_CMD_LENGTH ( 2 + 3 )

/*!
 * @brief Maximal payload size to send during full almanac update
 */
#define LR1110_MODEM_GNSS_FULL_ALMANAC_UPDATE_PACKET_LENGTH ( 260 )

/*!
 * @brief Response buffer size for command GNSS get timings
 */
#define LR1110_MODEM_GNSS_SCAN_GET_TIMINGS_RBUFFER_LENGTH ( 8 )

/*!
 * @brief Response buffer size for command GNSS get context
 */
#define LR1110_MODEM_GNSS_SCAN_GET_CONTEXT_RBUFFER_LENGTH ( 9 )

/*!
 * @brief Maximal number of detectable satellites
 */
#define LR1110_MODEM_GNSS_MAX_DETECTED_SV ( 32 )

/*!
 * @brief Size of satellite information reported in Get satellites detected commands per satellite (in byte)
 */
#define LR1110_MODEM_GNSS_DETECTED_SV_SINGLE_SIZE ( 2 )

/*!
 * @brief Maximal response buffer size for command Get satellites detected
 */
#define LR1110_MODEM_GNSS_MAX_DETECTED_SV_BUFFER_SIZE \
    ( LR1110_MODEM_GNSS_MAX_DETECTED_SV * LR1110_MODEM_GNSS_DETECTED_SV_SINGLE_SIZE )

/*!
 * @brief Response buffer size for command Read firwmare version
 */
#define LR1110_MODEM_GNSS_READ_FIRMWARE_VERSION_RBUFFER_LENGTH ( 2 )

/*!
 * @brief Response buffer size for command Read almanac by index
 */
#define LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_RBUFFER_LENGTH ( LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE * 11 )

/*!
 * @brief Scaling factor for latitude conversion
 */
#define LR1110_MODEM_GNSS_SCALING_LATITUDE ( 90 )

/*!
 * @brief Scaling factor for longitude conversion
 */
#define LR1110_MODEM_GNSS_SCALING_LONGITUDE ( 180 )

/*!
 * @brief Offset for SNR/CNR conversion
 */
#define LR1110_MODEM_GNSS_SNR_TO_CNR_OFFSET ( 31 )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*!
 * @brief Operation code for GNSS commands
 */
typedef enum
{
    LR1110_MODEM_GNSS_SET_CONSTELLATION_CMD            = 0x00,  //!< set the constellation to use
    LR1110_MODEM_GNSS_READ_CONSTELLATION_CMD           = 0x01,  //!< read the used consteallations
    LR1110_MODEM_GNSS_SET_ALMANAC_UPDATE_CMD           = 0x02,  //!< set almanac update configuration
    LR1110_MODEM_GNSS_READ_ALMANAC_UPDATE_CMD          = 0x03,  //!< read the almanac update configuration
    LR1110_MODEM_GNSS_SET_FREQ_SEARCH_SPACE_CMD        = 0x04,  //!< set the frequency search space
    LR1110_MODEM_GNSS_READ_FREQ_SEARCH_SPACE_CMD       = 0x05,  //!< read the frequency search space
    LR1110_MODEM_GNSS_READ_FW_VERSION_CMD              = 0x06,  //!< read the firmware version
    LR1110_MODEM_GNSS_READ_SUPPORTED_CONSTELLATION_CMD = 0x07,  //!< read the supported constellations
    LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD          = 0x0E,  //!< Almanac update
    LR1110_MODEM_GNSS_SET_ASSISTANCE_POSITION_CMD      = 0x10,  //!< set the assistance position
    LR1110_MODEM_GNSS_READ_ASSISTANCE_POSITION_CMD     = 0x11,  //!< read the assistance position
    LR1110_MODEM_GNSS_SET_XTAL_ERROR_CMD               = 0x12,  //!< set xtal accuracy
    LR1110_MODEM_GNSS_READ_XTAL_ERROR_CMD              = 0x13,  //!< read the xtal accuracy
    LR1110_MODEM_GNSS_PUSH_SOLVER_CMD                  = 0x14,  //!< set the informations from the solver to the chip
    LR1110_MODEM_GNSS_GET_CONTEXT_STATUS_CMD           = 0x16,  //!< read the GNSS context status
    LR1110_MODEM_GNSS_GET_NB_SV_DETECTED_CMD           = 0x17,  //!< read the number of detected satellites
    LR1110_MODEM_GNSS_GET_SV_DETECTED_CMD              = 0x18,  //!< read the informations of detected satellites
    LR1110_MODEM_GNSS_GET_TIMINGS_CMD                  = 0x19,  //!< read the meseaured timings during the scan
    LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_CMD        = 0x1A,  //!< read the almanac by index
    LR1110_MODEM_GNSS_SCAN_AUTONOMOUS_CMD              = 0x30,  //!< start the scan autonomous
    LR1110_MODEM_GNSS_SCAN_ASSISTED_CMD                = 0x31   //!< start the scan assisted
} lr1110_modem_api_command_gnss_t;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

err_t lr1110_modem_gnss_set_constellations_to_use(
    lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t constellation_to_use )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_SET_CONSTALLATION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SET_CONSTELLATION_CMD;

    cbuffer[2] = constellation_to_use;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SET_CONSTALLATION_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_read_used_constellations(
    lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* constellations_used )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_CONSTALLATION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_CONSTELLATION_CMD;

    return lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_CONSTALLATION_CMD_LENGTH, 
                                  constellations_used, sizeof( *constellations_used ) );
}

err_t lr1110_modem_gnss_set_almanac_update(
    lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t constellations_to_update )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_SET_ALMANAC_UPDATE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SET_ALMANAC_UPDATE_CMD;

    cbuffer[2] = constellations_to_update;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SET_ALMANAC_UPDATE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_read_almanac_update(
    lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* constellations_to_update )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_ALMANAC_UPDATE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_ALMANAC_UPDATE_CMD;

    return lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_ALMANAC_UPDATE_CMD_LENGTH, 
                                  constellations_to_update, sizeof( *constellations_to_update ) );
}

err_t lr1110_modem_gnss_set_frequency_search(
    lriot_t *ctx, lr1110_modem_gnss_frequency_search_space_mask_t frequency_search_space )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_SET_FREQ_SEARCH_SPACE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SET_FREQ_SEARCH_SPACE_CMD;

    cbuffer[2] = frequency_search_space;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SET_FREQ_SEARCH_SPACE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_read_frequency_search(
    lriot_t *ctx, lr1110_modem_gnss_frequency_search_space_mask_t* frequency_search_space )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_FREQ_SEARCH_SPACE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_FREQ_SEARCH_SPACE_CMD;

    return lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_FREQ_SEARCH_SPACE_CMD_LENGTH, 
                                  frequency_search_space, sizeof( *frequency_search_space ) );
}

err_t lr1110_modem_gnss_read_firmware_version( lriot_t *ctx, lr1110_modem_gnss_version_t* version )
{
    err_t rc;
    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_FW_VERSION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_FW_VERSION_CMD;

    uint8_t rbuffer[LR1110_MODEM_GNSS_READ_FIRMWARE_VERSION_RBUFFER_LENGTH] = { 0 };

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_FW_VERSION_CMD_LENGTH, rbuffer,
                                LR1110_MODEM_GNSS_READ_FIRMWARE_VERSION_RBUFFER_LENGTH );

    version->gnss_firmware = rbuffer[0];
    version->gnss_almanac  = rbuffer[1];

    return rc;
}

err_t lr1110_modem_gnss_read_supported_constellations(
    lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* supported_constellations )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_SUPPORTED_CONSTELLATION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_SUPPORTED_CONSTELLATION_CMD;

    return lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_SUPPORTED_CONSTELLATION_CMD_LENGTH, 
                                  supported_constellations, sizeof( *supported_constellations ) );
}

err_t lr1110_modem_gnss_almanac_full_update(
    lriot_t *ctx, lr1110_modem_gnss_almanac_full_update_bytestream_t almanac_bytestream )
{
    err_t rc = 0;

    uint8_t  cbuffer[LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD_LENGTH];
    uint16_t remaining_almanac_to_write = LR1110_MODEM_GNSS_FULL_ALMANAC_WRITE_BUFFER_SIZE;

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD;

    while( remaining_almanac_to_write > 0 )
    {
        uint16_t almanac_size_to_write =
            MIN( remaining_almanac_to_write, LR1110_MODEM_GNSS_FULL_ALMANAC_UPDATE_PACKET_LENGTH );

        rc = lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD_LENGTH,
                                     &almanac_bytestream[ LR1110_MODEM_GNSS_FULL_ALMANAC_WRITE_BUFFER_SIZE - remaining_almanac_to_write ], 
                                     almanac_size_to_write );

        remaining_almanac_to_write -= almanac_size_to_write;
    }

    return rc;
}

err_t lr1110_modem_gnss_one_chunk_almanac_update(
    lriot_t *ctx, lr1110_modem_gnss_almanac_one_chunk_bytestream_t almanac_one_chunk_bytestream )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_ALMANAC_FULL_UPDATE_CMD_LENGTH, 
                                   almanac_one_chunk_bytestream, LR1110_MODEM_GNSS_SINGLE_ALMANAC_WRITE_SIZE );
}

err_t lr1110_modem_gnss_set_assistance_position(
    lriot_t *ctx, lr1110_modem_gnss_solver_assistance_position_t* assistance_position )
{
    int16_t latitude, longitude;

    uint8_t cbuffer[LR1110_MODEM_GNSS_SET_ASSISTANCE_POSITION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SET_ASSISTANCE_POSITION_CMD;

    latitude   = ( ( assistance_position->latitude * 2048 ) / LR1110_MODEM_GNSS_SCALING_LATITUDE );
    cbuffer[2] = ( uint8_t )( latitude >> 8 );
    cbuffer[3] = ( uint8_t )( latitude );

    longitude  = ( ( assistance_position->longitude * 2048 ) / LR1110_MODEM_GNSS_SCALING_LONGITUDE );
    cbuffer[4] = ( uint8_t )( longitude >> 8 );
    cbuffer[5] = ( uint8_t )( longitude );

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SET_ASSISTANCE_POSITION_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_read_assistance_position(
    lriot_t *ctx, lr1110_modem_gnss_solver_assistance_position_t* assistance_position )
{
    uint8_t position_buffer[4] = { 0x00 };
    int16_t position_tmp;
    err_t rc;

    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_ASSISTANCE_POSITION_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_ASSISTANCE_POSITION_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_ASSISTANCE_POSITION_CMD_LENGTH,
                                position_buffer, sizeof( position_buffer ) );

    position_tmp                  = ( ( ( uint16_t ) position_buffer[0] << 8 ) + position_buffer[1] );
    assistance_position->latitude = ( ( float ) ( position_tmp ) *LR1110_MODEM_GNSS_SCALING_LATITUDE ) / 2048;

    position_tmp                   = ( ( ( uint16_t ) position_buffer[2] << 8 ) + position_buffer[3] );
    assistance_position->longitude = ( ( float ) ( position_tmp ) *LR1110_MODEM_GNSS_SCALING_LONGITUDE ) / 2048;

    return rc;
}

err_t lr1110_modem_gnss_set_xtal_error( lriot_t *ctx, float xtal_error_in_ppm )
{
    int16_t error;

    uint8_t cbuffer[LR1110_MODEM_GNSS_SET_XTAL_ERROR_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SET_XTAL_ERROR_CMD;

    error      = ( ( xtal_error_in_ppm * 32768 ) / 40 );
    cbuffer[2] = ( uint8_t )( error >> 8 );
    cbuffer[3] = ( uint8_t )( error );

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SET_XTAL_ERROR_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_read_xtal_error( lriot_t *ctx, float* xtal_error_in_ppm )
{
    uint8_t xtal_error_buffer[2] = { 0x00 };
    int16_t xtal_error_temp;
    err_t rc;

    uint8_t cbuffer[LR1110_MODEM_GNSS_READ_XTAL_ERROR_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_READ_XTAL_ERROR_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_READ_XTAL_ERROR_CMD_LENGTH,
                                xtal_error_buffer, sizeof( xtal_error_buffer ) );

    xtal_error_temp    = ( ( ( uint16_t ) xtal_error_buffer[0] << 8 ) + xtal_error_buffer[1] );
    *xtal_error_in_ppm = ( ( float ) ( xtal_error_temp ) * 40 ) / 32768;

    return rc;
}

err_t lr1110_modem_gnss_get_context( lriot_t *ctx, lr1110_modem_gnss_context_t* gnss_context )
{
    err_t rc;

    uint8_t cbuffer[LR1110_MODEM_GNSS_GET_CONTEXT_STATUS_CMD_LENGTH];
    uint8_t rbuffer[LR1110_MODEM_GNSS_SCAN_GET_CONTEXT_RBUFFER_LENGTH] = { 0 };

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_GET_CONTEXT_STATUS_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_GET_CONTEXT_STATUS_CMD_LENGTH, rbuffer,
                                LR1110_MODEM_GNSS_SCAN_GET_CONTEXT_RBUFFER_LENGTH );

    gnss_context->gnss_firmware_version = rbuffer[2];
    gnss_context->global_almanac_crc    = ( ( uint32_t ) rbuffer[6] << 24 ) + ( ( uint32_t ) rbuffer[5] << 16 ) +
                                          ( ( uint32_t ) rbuffer[4] << 8 ) + ( ( uint32_t ) rbuffer[3] << 0 );
    gnss_context->error_code              = ( rbuffer[7] >> 4 );
    gnss_context->almanac_update_bit_mask = ( rbuffer[7] >> 1 ) & 0x07;
    gnss_context->frequency_search_space = ( ( ( rbuffer[7] & 0x01 ) << 1 ) | ( rbuffer[8] >> 7 ) );

    return rc;
}

err_t lr1110_modem_gnss_get_nb_detected_satellites( lriot_t *ctx, uint8_t* nb_detected_satellites )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_GET_NB_SV_SATELLITES_CMD_LENGTH] = { 0 };

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_GET_NB_SV_DETECTED_CMD;

    return lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_GET_NB_SV_SATELLITES_CMD_LENGTH, nb_detected_satellites, 1 );
}

err_t lr1110_modem_gnss_get_detected_satellites( lriot_t *ctx, uint8_t nb_detected_satellites,
                                                 lr1110_modem_gnss_detected_satellite_t* detected_satellite_id_snr )
{
    uint8_t max_satellites_to_fetch = ( LR1110_MODEM_GNSS_MAX_DETECTED_SV > nb_detected_satellites ) ? 
                                        nb_detected_satellites : LR1110_MODEM_GNSS_MAX_DETECTED_SV;
    uint16_t read_size = max_satellites_to_fetch * LR1110_MODEM_GNSS_DETECTED_SV_SINGLE_SIZE;
    uint8_t  result_buffer[LR1110_MODEM_GNSS_MAX_DETECTED_SV_BUFFER_SIZE] = { 0 };
    err_t rc;

    uint8_t cbuffer[LR1110_MODEM_GNSS_GET_SV_SATELLITES_CMD_LENGTH] = { 0 };

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_GET_SV_DETECTED_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_GET_SV_SATELLITES_CMD_LENGTH, result_buffer, read_size );
    for( uint8_t index_satellite = 0; index_satellite < max_satellites_to_fetch; index_satellite++ )
    {
        uint16_t local_result_buffer_index = index_satellite * 2;
        lr1110_modem_gnss_detected_satellite_t* local_satellite_result    = &detected_satellite_id_snr[index_satellite];

        local_satellite_result->satellite_id = result_buffer[local_result_buffer_index];
        local_satellite_result->cnr =
            result_buffer[local_result_buffer_index + 1] + LR1110_MODEM_GNSS_SNR_TO_CNR_OFFSET;
    }

    return rc;
}

err_t lr1110_modem_gnss_get_timings( lriot_t *ctx, lr1110_modem_gnss_timings_t* timings )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_GET_TIMINGS_CMD_LENGTH];
    uint8_t rbuffer[LR1110_MODEM_GNSS_SCAN_GET_TIMINGS_RBUFFER_LENGTH] = { 0 };
    err_t rc;

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_GET_TIMINGS_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_GET_TIMINGS_CMD_LENGTH, rbuffer,
                                LR1110_MODEM_GNSS_SCAN_GET_TIMINGS_RBUFFER_LENGTH );

    timings->computation_ms = ( ( ( ( uint32_t ) rbuffer[0] ) << 24 ) + ( ( ( uint32_t ) rbuffer[1] ) << 16 ) +
                                ( ( ( uint32_t ) rbuffer[2] ) << 8 ) + ( ( ( uint32_t ) rbuffer[3] ) << 0 ) ) / 1000;
    timings->radio_ms = ( ( ( ( uint32_t ) rbuffer[4] ) << 24 ) + ( ( ( uint32_t ) rbuffer[5] ) << 16 ) +
                          ( ( ( uint32_t ) rbuffer[6] ) << 8 ) + ( ( ( uint32_t ) rbuffer[7] ) << 0 ) ) / 1000;

    return rc;
}

err_t lr1110_modem_gnss_almanac_read_by_index( lriot_t *ctx, uint8_t sv_id, uint8_t nb_sv,
                                               uint8_t* almanac_read, uint8_t buffer_len )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_CMD_LENGTH];
    uint8_t rbuffer[LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_RBUFFER_LENGTH] = { 0 };
    err_t rc;

    if( ( nb_sv <= 11 ) && ( buffer_len >= ( nb_sv * LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE ) ) )
    {
        cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
        cbuffer[1] = LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_CMD;

        cbuffer[2] = sv_id;
        cbuffer[3] = nb_sv;

        rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_MODEM_GNSS_ALMANAC_READ_BY_INDEX_CMD_LENGTH, rbuffer,
                                    nb_sv * LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE );

        if( rc == LR1110_MODEM_RESPONSE_CODE_OK )
        {
            for( uint8_t i = 0; i < nb_sv * LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE; i++ )
            {
                almanac_read[i] = rbuffer[i];
            }
        }
    }
    else
    {
        rc = LR1110_MODEM_RESPONSE_CODE_INVALID;
    }

    return rc;
}

err_t lr1110_modem_gnss_scan_autonomous( lriot_t *ctx, lr1110_modem_gnss_search_mode_t effort_mode,
                                         uint8_t gnss_result_mask, uint8_t nb_sat )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_SCAN_AUTONOMOUS_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SCAN_AUTONOMOUS_CMD;

    cbuffer[2] = ( uint8_t ) effort_mode;
    cbuffer[3] = gnss_result_mask;
    cbuffer[4] = nb_sat;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SCAN_AUTONOMOUS_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_scan_assisted( lriot_t *ctx, lr1110_modem_gnss_search_mode_t effort_mode,
                                       uint8_t gnss_result_mask, uint8_t nb_sat )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_SCAN_ASSISTED_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_SCAN_ASSISTED_CMD;

    cbuffer[2] = ( uint8_t ) effort_mode;
    cbuffer[3] = gnss_result_mask;
    cbuffer[4] = nb_sat;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_SCAN_ASSISTED_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_gnss_push_solver_msg( lriot_t *ctx, uint8_t* payload, uint16_t payload_size )
{
    uint8_t cbuffer[LR1110_MODEM_GNSS_PUSH_SOLVER_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_GNSS;
    cbuffer[1] = LR1110_MODEM_GNSS_PUSH_SOLVER_CMD;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_MODEM_GNSS_PUSH_SOLVER_CMD_LENGTH, payload, payload_size );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
