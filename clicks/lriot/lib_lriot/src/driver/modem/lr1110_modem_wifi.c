/*!
 * @file      lr1110_modem_wifi.c
 *
 * @brief     Wi-Fi passive scan driver implementation for LR1110 modem
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

#include "modem/lr1110_modem_wifi.h"
#include "modem/lr1110_modem_hal.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

#define LR1110_WIFI_BASIC_COMPLETE_RESULT_SIZE ( 22 )
#define LR1110_WIFI_EXTENDED_FULL_RESULT_SIZE ( 79 )
#define LR1110_WIFI_BASIC_MAC_TYPE_CHANNEL_RESULT_SIZE ( 9 )

#define LR1110_WIFI_RESET_CUMUL_TIMING_CMD_LENGTH ( 2 )
#define LR1110_WIFI_READ_CUMUL_TIMING_CMD_LENGTH ( 2 )
#define LR1110_WIFI_CONFIG_TIMESTAMP_AP_PHONE_CMD_LENGTH ( 2 + 4 )
#define LR1110_WIFI_GET_VERSION_CMD_LENGTH ( 2 )
#define LR1110_WIFI_PASSIVE_SCAN_CMD_LENGTH ( 2 + 10 )
#define LR1110_WIFI_PASSIVE_SCAN_TIME_LIMIT_CMD_LENGTH ( 2 + 10 )
#define LR1110_WIFI_SEARCH_COUNTRY_CODE_CMD_LENGTH ( 2 + 7 )
#define LR1110_WIFI_SEARCH_COUNTRY_CODE_TIME_LIMIT_CMD_LENGTH ( 2 + 7 )

#define LR1110_WIFI_ALL_CUMULATIVE_TIMING_SIZE ( 16 )
#define LR1110_WIFI_VERSION_SIZE ( 2 )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */
typedef enum
{
    LR1110_MODEM_WIFI_RESET_CUMUL_TIMING_PHASE_CMD       = 0x07,
    LR1110_MODEM_WIFI_READ_CUMUL_TIMING_PHASE_CMD        = 0x08,
    LR1110_MODEM_WIFI_CONFIG_TIMESTAMP_AP_PHONE_CMD      = 0x0B,
    LR1110_MODEM_WIFI_GET_FIRMWARE_WIFI_VERSION_CMD      = 0x20,
    LR1110_MODEM_WIFI_PASSIVE_SCAN_CMD                   = 0x30,
    LR1110_MODEM_WIFI_PASSIVE_SCAN_TIME_LIMIT_CMD        = 0x31,
    LR1110_MODEM_WIFI_SEARCH_COUNTRY_CODE_CMD            = 0x32,
    LR1110_MODEM_WIFI_SEARCH_COUNTRY_CODE_TIME_LIMIT_CMD = 0x33,
} lr1110_modem_api_command_wifi_t;

/*!
 * @brief Wi-Fi result interface structure
 */
typedef union
{
    lr1110_modem_wifi_basic_complete_result_t*         basic_complete;
    lr1110_modem_wifi_basic_mac_type_channel_result_t* basic_mac_type_channel;
} lr1110_modem_wifi_result_interface_t;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*!
 * @brief Return a uint16 value by reading a buffer of uint8 from index.
 *
 * This function interpret the array MSB first. It is equivalent to:
 * return array[index] * 256 + array[index+1]
 *
 */
static uint16_t uint16_from_array( uint8_t* array, uint16_t index );

/*!
 * @brief Return a uint32 value by reading a buffer of uint8 from index.
 *
 * This function interpret the array MSB first.
 *
 */
static uint32_t uint32_from_array( uint8_t* array, uint16_t index );

static void interpret_basic_complete_result_from_buffer( uint8_t nb_results, uint8_t* buffer,
                                                         lr1110_modem_wifi_basic_complete_result_t* result );

static void interpret_basic_mac_type_channel_result_from_buffer( uint8_t nb_results, uint8_t* buffer, 
                                                                 lr1110_modem_wifi_basic_mac_type_channel_result_t* result );

static void interpret_extended_full_result_from_buffer( uint8_t nb_results, uint8_t* buffer,
                                                        lr1110_modem_wifi_extended_full_result_t* result );

static void lr1110_wifi_read_mac_address_from_buffer( uint8_t* buffer, uint16_t index_in_buffer,
                                                      lr1110_modem_wifi_mac_address_t mac_address );

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

err_t lr1110_modem_wifi_reset_cumulative_timing( lriot_t *ctx )
{
    uint8_t cbuffer[LR1110_WIFI_RESET_CUMUL_TIMING_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_WIFI;
    cbuffer[1] = LR1110_MODEM_WIFI_RESET_CUMUL_TIMING_PHASE_CMD;

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_RESET_CUMUL_TIMING_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_wifi_read_cumulative_timing( lriot_t *ctx, lr1110_modem_wifi_cumulative_timings_t* timing )
{
    uint8_t cbuffer[LR1110_WIFI_READ_CUMUL_TIMING_CMD_LENGTH];
    uint8_t buffer_out[LR1110_WIFI_ALL_CUMULATIVE_TIMING_SIZE] = { 0 };
    err_t rc;

    cbuffer[0] = LR1110_MODEM_GROUP_ID_WIFI;
    cbuffer[1] = LR1110_MODEM_WIFI_READ_CUMUL_TIMING_PHASE_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_WIFI_READ_CUMUL_TIMING_CMD_LENGTH, buffer_out,
                                LR1110_WIFI_ALL_CUMULATIVE_TIMING_SIZE );

    timing->rx_detection_us = ( ( uint32_t ) buffer_out[0] << 24 ) + ( ( uint32_t ) buffer_out[1] << 16 ) + 
                              ( ( uint16_t ) buffer_out[2] << 8 ) + buffer_out[3];
    timing->rx_correlation_us = ( ( uint32_t ) buffer_out[4] << 24 ) + ( ( uint32_t ) buffer_out[5] << 16 ) + 
                                ( ( uint16_t ) buffer_out[6] << 8 ) + buffer_out[7];
    timing->rx_capture_us = ( ( uint32_t ) buffer_out[8] << 24 ) + ( ( uint32_t ) buffer_out[9] << 16 ) + 
                            ( ( uint16_t ) buffer_out[10] << 8 ) + buffer_out[11];
    timing->demodulation_us = ( ( uint32_t ) buffer_out[12] << 24 ) + ( ( uint32_t ) buffer_out[13] << 16 ) + 
                              ( ( uint16_t ) buffer_out[14] << 8 ) + buffer_out[15];

    return rc;
}

err_t lr1110_modem_wifi_cfg_timestamp_ap_phone( lriot_t *ctx, uint32_t timestamp_in_s )
{
    uint8_t cbuffer[LR1110_WIFI_CONFIG_TIMESTAMP_AP_PHONE_CMD_LENGTH];

    cbuffer[0] = LR1110_MODEM_GROUP_ID_WIFI;
    cbuffer[1] = LR1110_MODEM_WIFI_CONFIG_TIMESTAMP_AP_PHONE_CMD;

    cbuffer[2] = ( uint8_t )( timestamp_in_s >> 24 );
    cbuffer[3] = ( uint8_t )( timestamp_in_s >> 16 );
    cbuffer[4] = ( uint8_t )( timestamp_in_s >> 8 );
    cbuffer[5] = ( uint8_t )( timestamp_in_s >> 0 );

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_CONFIG_TIMESTAMP_AP_PHONE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_wifi_read_version( lriot_t *ctx, lr1110_modem_wifi_version_t* wifi_version )
{
    uint8_t cbuffer[LR1110_WIFI_GET_VERSION_CMD_LENGTH];
    uint8_t rbuffer[LR1110_WIFI_VERSION_SIZE] = { 0 };
    err_t rc;

    cbuffer[0] = LR1110_MODEM_GROUP_ID_WIFI;
    cbuffer[1] = LR1110_MODEM_WIFI_GET_FIRMWARE_WIFI_VERSION_CMD;

    rc = lr1110_modem_hal_read( ctx, cbuffer, LR1110_WIFI_GET_VERSION_CMD_LENGTH, rbuffer, LR1110_WIFI_VERSION_SIZE );

    wifi_version->major = rbuffer[0];
    wifi_version->minor = rbuffer[1];

    return rc;
}

err_t lr1110_modem_wifi_passive_scan( lriot_t *ctx, lr1110_modem_wifi_signal_type_scan_t signal_type,
                                      lr1110_modem_wifi_channel_mask_t channels, lr1110_modem_wifi_mode_t scan_mode,
                                      uint8_t max_results, uint8_t nb_scan_per_channel, uint16_t timeout_in_ms, 
                                      bool abort_on_timeout, lr1110_modem_wifi_result_format_t result_format )
{
    uint8_t cbuffer[LR1110_WIFI_PASSIVE_SCAN_CMD_LENGTH] = {
        ( uint8_t ) LR1110_MODEM_GROUP_ID_WIFI,
        ( uint8_t ) LR1110_MODEM_WIFI_PASSIVE_SCAN_CMD,
        ( uint8_t ) signal_type,
        ( uint8_t )( channels >> 8 ),
        ( uint8_t ) channels,
        ( uint8_t ) scan_mode,
        ( uint8_t ) max_results,
        ( uint8_t ) nb_scan_per_channel,
        ( uint8_t )( timeout_in_ms >> 8 ),
        ( uint8_t ) timeout_in_ms,
        ( uint8_t ) abort_on_timeout,
        ( uint8_t ) result_format,
    };

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_PASSIVE_SCAN_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_wifi_passive_scan_time_limit( lriot_t *ctx, lr1110_modem_wifi_signal_type_scan_t signal_type,
                                                 lr1110_modem_wifi_channel_mask_t channels, lr1110_modem_wifi_mode_t scan_mode,
                                                 uint8_t max_results, uint16_t timeout_per_channel_ms, uint16_t timeout_per_scan_ms,
                                                 lr1110_modem_wifi_result_format_t result_format )
{
    uint8_t cbuffer[LR1110_WIFI_PASSIVE_SCAN_TIME_LIMIT_CMD_LENGTH] = {
        ( uint8_t ) LR1110_MODEM_GROUP_ID_WIFI,
        ( uint8_t ) LR1110_MODEM_WIFI_PASSIVE_SCAN_TIME_LIMIT_CMD,
        ( uint8_t ) signal_type,
        ( uint8_t )( channels >> 8 ),
        ( uint8_t ) channels,
        ( uint8_t ) scan_mode,
        ( uint8_t ) max_results,
        ( uint8_t )( timeout_per_channel_ms >> 8 ),
        ( uint8_t ) timeout_per_channel_ms,
        ( uint8_t )( timeout_per_scan_ms >> 8 ),
        ( uint8_t ) timeout_per_scan_ms,
        ( uint8_t ) result_format,
    };

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_PASSIVE_SCAN_TIME_LIMIT_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_wifi_search_country_code( lriot_t *ctx, lr1110_modem_wifi_channel_mask_t channels_mask, uint8_t nb_max_results,
                                             uint8_t nb_scan_per_channel, uint16_t timeout_in_ms, bool abort_on_timeout )
{
    uint8_t cbuffer[LR1110_WIFI_SEARCH_COUNTRY_CODE_CMD_LENGTH] = {
        ( uint8_t ) LR1110_MODEM_GROUP_ID_WIFI,
        ( uint8_t ) LR1110_MODEM_WIFI_SEARCH_COUNTRY_CODE_CMD,
        ( uint8_t )( channels_mask >> 8 ),
        ( uint8_t ) channels_mask,
        nb_max_results,
        nb_scan_per_channel,
        ( uint8_t )( timeout_in_ms >> 8 ),
        ( uint8_t ) timeout_in_ms,
        ( uint8_t )( abort_on_timeout ? 1 : 0 )
    };

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_SEARCH_COUNTRY_CODE_CMD_LENGTH, 0, 0 );
}

err_t lr1110_modem_wifi_search_country_code_time_limit( lriot_t *ctx, lr1110_modem_wifi_channel_mask_t channels_mask,
                                                        uint8_t nb_max_results, uint16_t timeout_per_channel_ms, 
                                                        uint16_t timeout_per_scan_ms )
{
    uint8_t cbuffer[LR1110_WIFI_SEARCH_COUNTRY_CODE_TIME_LIMIT_CMD_LENGTH] = {
        ( uint8_t ) LR1110_MODEM_GROUP_ID_WIFI,
        ( uint8_t ) LR1110_MODEM_WIFI_SEARCH_COUNTRY_CODE_TIME_LIMIT_CMD,
        ( uint8_t )( channels_mask >> 8 ),
        ( uint8_t ) channels_mask,
        nb_max_results,
        ( uint8_t )( timeout_per_channel_ms >> 8 ),
        ( uint8_t ) timeout_per_channel_ms,
        ( uint8_t )( timeout_per_scan_ms >> 8 ),
        ( uint8_t ) timeout_per_scan_ms,
    };

    return lr1110_modem_hal_write( ctx, cbuffer, LR1110_WIFI_SEARCH_COUNTRY_CODE_TIME_LIMIT_CMD_LENGTH, 0, 0 );
}

void lr1110_modem_wifi_read_basic_mac_type_channel_results( uint8_t* buffer, uint16_t buffer_len,
                                                            lr1110_modem_wifi_basic_mac_type_channel_result_t* results,
                                                            uint8_t* nb_results )
{
    *nb_results = buffer_len / LR1110_WIFI_BASIC_MAC_TYPE_CHANNEL_RESULT_SIZE;
    interpret_basic_mac_type_channel_result_from_buffer( *nb_results, buffer, results );
}

void lr1110_modem_wifi_read_basic_complete_results( uint8_t* buffer, uint16_t buffer_len,
                                                    lr1110_modem_wifi_basic_complete_result_t* results,
                                                    uint8_t* nb_results )
{
    *nb_results = buffer_len / LR1110_WIFI_BASIC_COMPLETE_RESULT_SIZE;
    interpret_basic_complete_result_from_buffer( *nb_results, buffer, results );
}

void lr1110_modem_wifi_read_extended_full_results( uint8_t* buffer, uint16_t buffer_len,
                                                   lr1110_modem_wifi_extended_full_result_t* results,
                                                   uint8_t* nb_results )
{
    *nb_results = buffer_len / LR1110_WIFI_EXTENDED_FULL_RESULT_SIZE;
    interpret_extended_full_result_from_buffer( *nb_results, buffer, results );
}

err_t lr1110_modem_extract_channel_from_info_byte( lr1110_modem_wifi_channel_info_byte_t info_byte )
{
    return ( info_byte & 0x0F );
}

err_t lr1110_modem_extract_signal_type_from_data_rate_info( lr1110_modem_wifi_datarate_info_byte_t data_rate_info )
{
    return ( data_rate_info & 0x03 );
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

static uint16_t uint16_from_array( uint8_t* array, uint16_t index )
{
    return ( uint16_t )( array[index] << 8 ) + ( ( uint16_t )( array[index + 1] ) );
}

static uint32_t uint32_from_array( uint8_t* array, uint16_t index )
{
    return ( ( uint32_t )( array[index] ) << 24 ) + ( ( uint32_t )( array[index + 1] ) << 16 ) +
           ( ( uint32_t )( array[index + 2] ) << 8 ) + ( uint32_t )( array[index + 3] );
}

static void lr1110_wifi_read_mac_address_from_buffer( uint8_t* buffer, uint16_t index_in_buffer,
                                                      lr1110_modem_wifi_mac_address_t mac_address )
{
    for( uint8_t field_mac_index = 0; field_mac_index < LR1110_MODEM_WIFI_MAC_ADDRESS_LENGTH; field_mac_index++ )
    {
        mac_address[field_mac_index] = buffer[index_in_buffer + field_mac_index];
    }
}

static void interpret_basic_complete_result_from_buffer( uint8_t nb_results, uint8_t* buffer,
                                                         lr1110_modem_wifi_basic_complete_result_t* result )
{
    for( uint8_t result_index = 0; nb_results > result_index; result_index++ )
    {
        uint16_t local_index_start = LR1110_WIFI_BASIC_COMPLETE_RESULT_SIZE * result_index;
        result[result_index].data_rate_info_byte  = buffer[local_index_start + 0];
        result[result_index].channel_info_byte    = buffer[local_index_start + 1];
        result[result_index].rssi                 = buffer[local_index_start + 2];
        result[result_index].frame_type_info_byte = buffer[local_index_start + 3];
        lr1110_wifi_read_mac_address_from_buffer( buffer, local_index_start + 4, result[result_index].mac_address );
        result[result_index].phi_offset       = uint16_from_array( buffer, local_index_start + 10 );
        result[result_index].timestamp_us_high = uint32_from_array( buffer, local_index_start + 12 );
        result[result_index].timestamp_us_low  = uint32_from_array( buffer, local_index_start + 16 );
        result[result_index].beacon_period_tu = uint16_from_array( buffer, local_index_start + 20 );
    }
}

static void interpret_basic_mac_type_channel_result_from_buffer( uint8_t nb_results, uint8_t* buffer, 
                                                                 lr1110_modem_wifi_basic_mac_type_channel_result_t* result )
{
    for( uint8_t result_index = 0; nb_results > result_index; result_index++ )
    {
        uint16_t local_index_start = LR1110_WIFI_BASIC_MAC_TYPE_CHANNEL_RESULT_SIZE * result_index;
        result[result_index].data_rate_info_byte = buffer[local_index_start + 0];
        result[result_index].channel_info_byte   = buffer[local_index_start + 1];
        result[result_index].rssi                = buffer[local_index_start + 2];
        lr1110_wifi_read_mac_address_from_buffer( buffer, local_index_start + 3, result[result_index].mac_address );
    }
}

static void interpret_extended_full_result_from_buffer( uint8_t nb_results, uint8_t* buffer,
                                                        lr1110_modem_wifi_extended_full_result_t* result )
{
    for( uint8_t result_index = 0; result_index < nb_results; result_index++ )
    {
        uint16_t local_index_start = LR1110_WIFI_EXTENDED_FULL_RESULT_SIZE * result_index;
        lr1110_modem_wifi_extended_full_result_t* local_wifi_result = &result[result_index];

        local_wifi_result->data_rate_info_byte = buffer[local_index_start + 0];
        local_wifi_result->channel_info_byte   = buffer[local_index_start + 1];
        local_wifi_result->rssi                = buffer[local_index_start + 2];
        local_wifi_result->rate                = buffer[local_index_start + 3];
        local_wifi_result->service             = uint16_from_array( buffer, local_index_start + 4 );
        local_wifi_result->length              = uint16_from_array( buffer, local_index_start + 6 );
        local_wifi_result->frame_control       = uint16_from_array( buffer, local_index_start + 8 );
        lr1110_wifi_read_mac_address_from_buffer( buffer, local_index_start + 10, local_wifi_result->mac_address_1 );
        lr1110_wifi_read_mac_address_from_buffer( buffer, local_index_start + 16, local_wifi_result->mac_address_2 );
        lr1110_wifi_read_mac_address_from_buffer( buffer, local_index_start + 22, local_wifi_result->mac_address_3 );
        local_wifi_result->timestamp_us_high = uint32_from_array( buffer, local_index_start + 28 );
        local_wifi_result->timestamp_us_low  = uint32_from_array( buffer, local_index_start + 32 );
        local_wifi_result->beacon_period_tu = uint16_from_array( buffer, local_index_start + 36 );
        local_wifi_result->seq_control      = uint16_from_array( buffer, local_index_start + 38 );
        for( uint8_t ssid_index = 0; ssid_index < LR1110_MODEM_WIFI_RESULT_SSID_LENGTH; ssid_index++ )
        {
            local_wifi_result->ssid_bytes[ssid_index] = buffer[local_index_start + ssid_index + 40];
        }
        local_wifi_result->current_channel = buffer[local_index_start + 72];
        local_wifi_result->country_code    = uint16_from_array( buffer, local_index_start + 73 );
        local_wifi_result->io_regulation   = buffer[local_index_start + 75];
        local_wifi_result->fcs_check_byte.is_fcs_checked = ( ( buffer[local_index_start + 76] & 0x01 ) == 0x01 );
        local_wifi_result->fcs_check_byte.is_fcs_ok      = ( ( buffer[local_index_start + 76] & 0x02 ) == 0x02 );
        local_wifi_result->phi_offset                    = uint16_from_array( buffer, local_index_start + 77 );
    }
}

/* --- EOF ------------------------------------------------------------------ */
