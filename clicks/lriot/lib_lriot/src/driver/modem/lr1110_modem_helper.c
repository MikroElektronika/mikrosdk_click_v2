/*!
 * @file      lr1110_modem_helper.c
 *
 * @brief     helper functions implementation for LR1110 modem
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

#include "modem/lr1110_modem_helper.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/*!
 * @brief Offset for constellation ID
 */
#define LR1110_MODEM_HELPER_GNSS_ALMANAC_SV_CONSTELLATION_ID_BUFFER_LOCATION ( 21 )

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

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

err_t lr1110_modem_helper_get_utc_time( lriot_t *ctx, uint32_t* time )
{
    err_t rc;
    uint32_t gps_time;

    *time = 0;

    rc = lr1110_modem_get_gps_time( ctx, &gps_time );

    if( ( rc == LR1110_MODEM_RESPONSE_CODE_OK ) && ( gps_time != 0 ) )
    {
        *time = gps_time + ( LR1110_MODEM_HELPER_INITAL_GNSS_DATE_SECONDS - LR1110_MODEM_HELPER_GNSS_LEAP_SECONDS_OFFSET );
    }

    return rc;
}

err_t lr1110_modem_helper_gnss_get_gnss_week_number_rollover( lriot_t *ctx, uint8_t* gnss_week_number_rollover )
{
    err_t rc;
    uint32_t gps_time;

    *gnss_week_number_rollover = 0;

    rc = lr1110_modem_get_gps_time( ctx, &gps_time );

    if( ( rc == LR1110_MODEM_RESPONSE_CODE_OK ) && ( gps_time != 0 ) )
    {
        *gnss_week_number_rollover = gps_time / LR1110_MODEM_HELPER_NB_SEC_PER_HOUR /
                                     LR1110_MODEM_HELPER_NB_HOUR_PER_DAY / LR1110_MODEM_HELPER_NB_DAY_PER_WEEK /
                                     LR1110_MODEM_HELPER_NB_WEEK_PER_WRAP;
    }

    return rc;
}

err_t lr1110_modem_helper_gnss_get_almanac_date_by_index( lriot_t *ctx, uint8_t sv_id,
                                                          uint32_t* date, uint8_t gnss_week_number_rollover )
{
    uint8_t rbuffer[LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE] = { 0 };
    err_t rc;

    *date = 0;

    rc = lr1110_modem_gnss_almanac_read_by_index( ctx, sv_id, 1, rbuffer,
                                                  LR1110_MODEM_GNSS_SINGLE_ALMANAC_READ_SIZE );

    if( rc == LR1110_MODEM_RESPONSE_CODE_OK )
    {

        if( ( LR1110_MODEM_GNSS_ALMANAC_CONSTELLATION_UNDEFINED != 
              rbuffer[LR1110_MODEM_HELPER_GNSS_ALMANAC_SV_CONSTELLATION_ID_BUFFER_LOCATION] ) &&
            ( gnss_week_number_rollover != 0 ) )
        {
            *date = ( ( ( uint32_t ) rbuffer[2] << 8 ) + ( uint32_t ) rbuffer[1] );
            // date =  Initial GPS date (6 jan 1980) + 24h * 3600s * ( 1024 weeks * gnss_week_number_rollover
            // * 7 days + almanac_date )
            *date = ( LR1110_MODEM_HELPER_INITAL_GNSS_DATE_SECONDS +
                      LR1110_MODEM_HELPER_NB_HOUR_PER_DAY * LR1110_MODEM_HELPER_NB_SEC_PER_HOUR *
                          ( gnss_week_number_rollover * LR1110_MODEM_HELPER_NB_WEEK_PER_WRAP *
                                LR1110_MODEM_HELPER_NB_DAY_PER_WEEK +
                            *date ) );
        }
    }

    return rc;
}

err_t lr1110_modem_helper_gnss_get_result_destination( uint8_t* result_buffer, uint16_t result_buffer_size, uint8_t* destination )
{
    err_t status = LR1110_MODEM_HELPER_STATUS_ERROR;

    if( result_buffer_size != 0 )
    {
        switch( result_buffer[LR1110_MODEM_GNSS_SCAN_RESULT_DESTINATION_INDEX] )
        {
            case LR1110_MODEM_GNSS_DESTINATION_HOST:
            {
                status       = LR1110_MODEM_HELPER_STATUS_OK;
                *destination = LR1110_MODEM_GNSS_DESTINATION_HOST;

                break;
            }
            case LR1110_MODEM_GNSS_DESTINATION_SOLVER:
            {
                status       = LR1110_MODEM_HELPER_STATUS_OK;
                *destination = LR1110_MODEM_GNSS_DESTINATION_SOLVER;

                break;
            }
        }
    }

    return status;
}

err_t lr1110_modem_helper_gnss_get_event_type( uint8_t* result_buffer,
                                               uint16_t result_buffer_size,
                                               lr1110_modem_gnss_scan_done_event_t* event_type )
{
    err_t status = LR1110_MODEM_HELPER_STATUS_ERROR;

    if( result_buffer_size != 0 )
    {
        if( result_buffer[LR1110_MODEM_GNSS_SCAN_RESULT_DESTINATION_INDEX] == LR1110_MODEM_GNSS_DESTINATION_HOST )
        {
            switch( result_buffer[LR1110_MODEM_GNSS_SCAN_RESULT_EVENT_TYPE_INDEX] )
            {
                case LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_CRC_ERROR:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_CRC_ERROR;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_FLASH_INTEGRITY_ERROR:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_UPDATE_FAILS_FLASH_INTEGRITY_ERROR;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_VERSION_NOT_SUPPORTED:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_VERSION_NOT_SUPPORTED;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_PROCESS_OK:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_PROCESS_OK;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_IQ_FAILS:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_IQ_FAILS;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_NO_TIME:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_NO_TIME;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_NO_SATELLITE_DETECTED:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_NO_SATELLITE_DETECTED;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_GLOBAL_ALMANAC_CRC_ERROR:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_GLOBAL_ALMANAC_CRC_ERROR;
                    break;
                case LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_TOO_OLD:
                    status      = LR1110_MODEM_HELPER_STATUS_OK;
                    *event_type = LR1110_MODEM_GNSS_SCAN_DONE_ALMANAC_TOO_OLD;
                    break;
            }
        }
    }

    return status;
}

err_t lr1110_modem_helper_get_event_data( lriot_t *ctx, lr1110_modem_event_t* modem_event )
{
    lr1110_modem_helper_status_t status = LR1110_MODEM_HELPER_STATUS_ERROR;
    lr1110_modem_event_fields_t event_fields;

    if ( LR1110_MODEM_RESPONSE_CODE_OK == lr1110_modem_get_event( ctx, &event_fields ) )
    {
        status                     = LR1110_MODEM_HELPER_STATUS_OK;
        modem_event->event_type    = event_fields.event_type;
        modem_event->missed_events = event_fields.missed_events_count;

        switch ( modem_event->event_type )
        {
            case LR1110_MODEM_LORAWAN_EVENT_RESET:
                modem_event->event_data.reset.count = ( ( uint16_t ) event_fields.buffer[0] << 8 ) + event_fields.buffer[1];
                break;
            case LR1110_MODEM_LORAWAN_EVENT_TX_DONE:
                modem_event->event_data.txdone.status = event_fields.buffer[0];
                break;
            case LR1110_MODEM_LORAWAN_EVENT_DOWN_DATA:
                modem_event->event_data.downdata.rssi  = ( ( int8_t ) event_fields.buffer[0] ) - 64;
                modem_event->event_data.downdata.snr   = ( ( ( int8_t ) event_fields.buffer[1] ) >> 2 );
                modem_event->event_data.downdata.flag  = event_fields.buffer[2];
                modem_event->event_data.downdata.fport = event_fields.buffer[3];
                modem_event->event_data.downdata.length = event_fields.buffer_len - 4;  // remove rssi/snr/flag and fport from buffer
                for ( uint8_t i = 0; i < modem_event->event_data.downdata.length; i++ )
                {
                    modem_event->event_data.downdata.data_buf[i] = event_fields.buffer[i + 4];
                }
                break;
            case LR1110_MODEM_LORAWAN_EVENT_UPLOAD_DONE:
                modem_event->event_data.upload.status = event_fields.buffer[0];
                break;
            case LR1110_MODEM_LORAWAN_EVENT_SET_CONF:
                modem_event->event_data.setconf.tag = event_fields.buffer[0];
                break;
            case LR1110_MODEM_LORAWAN_EVENT_MUTE:
                modem_event->event_data.mute.status = event_fields.buffer[0];
                break;
            case LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE:
                modem_event->event_data.wifi.len = event_fields.buffer_len;
                for ( uint16_t i = 0; i < event_fields.buffer_len; i++ )
                {
                    modem_event->event_data.wifi.buffer[i] = event_fields.buffer[i];
                }
                break;
            case LR1110_MODEM_LORAWAN_EVENT_GNSS_SCAN_DONE:
                modem_event->event_data.gnss.len = event_fields.buffer_len;
                for ( uint16_t i = 0; i < event_fields.buffer_len; i++ )
                {
                    modem_event->event_data.gnss.nav_message[i] = event_fields.buffer[i];
                }
                break;
            case LR1110_MODEM_LORAWAN_EVENT_TIME_UPDATED_ALC_SYNC:
                modem_event->event_data.time.status = event_fields.buffer[0];
                break;
            default:
                break;
        }
    }
    return status;
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
