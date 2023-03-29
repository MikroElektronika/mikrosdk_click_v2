/**
 * @file      lr1110_modem_hal.c
 *
 * @brief     HAL implementation for LR1110 modem radio chip
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

#include "modem/lr1110_modem_hal.h"

/*!
 * @brief Return the computed CRC
 *
 * @param [in] crc_initial_value initial value of the CRC
 * @param [in] buffer Buffer used to compute the CRC
 * @param [out] crc CRC computed
 *
 * @returns CRC value
 */
static uint8_t lr1110_modem_compute_crc( uint8_t crc_initial_value, uint8_t* buffer, uint16_t length );

/*!
 * @brief Function to wait that the lr1110 modem-e busy line fall to low
 *
 * @param [in] ctx Chip implementation context
 * @param [in] timeout_ms timeout in millisec before leave the function
 *
 * @returns lr1110_hal_status_t
 */
static err_t lr1110_modem_hal_wait_on_busy( lriot_t *ctx, uint32_t timeout_ms );

/*!
 * @brief Function to wait the that lr1110 modem-e busy line raise to high
 *
 * @param [in] ctx Chip implementation context
 * @param [in] timeout_ms timeout in millisec before leave the function
 *
 * @returns lr1110_hal_status_t
 */
static err_t lr1110_modem_hal_wait_on_unbusy( lriot_t *ctx, uint32_t timeout_ms );

err_t lr1110_modem_hal_reset( lriot_t *ctx )
{
    lriot_set_rst_pin( ctx, 0 );
    Delay_1ms( );
    lriot_set_rst_pin( ctx, 1 );
    Delay_100ms( );
    return LR1110_MODEM_HAL_STATUS_OK;
}

err_t lr1110_modem_hal_wakeup( lriot_t *ctx )
{
    if( lr1110_modem_hal_wait_on_busy( ctx, 1000 ) == LR1110_MODEM_HAL_STATUS_OK )
    {
        // Wakeup radio
        spi_master_select_device( ctx->chip_select );
        spi_master_deselect_device( ctx->chip_select );
    }

    // Wait on busy pin for 100 ms
    return lr1110_modem_hal_wait_on_unbusy( ctx, 1000 );
}

err_t lr1110_modem_hal_read( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                           uint8_t* data_buf, uint16_t data_length )
{
    if( lr1110_modem_hal_wakeup( ctx ) == LR1110_MODEM_HAL_STATUS_OK )
    {
        uint8_t crc          = 0;
        uint8_t crc_received = 0;
        uint8_t status;

        // NSS low
        spi_master_select_device( ctx->chip_select );

        // Send CMD
        err_t error_flag = spi_master_write( &ctx->spi, command, command_length );

        // Compute and send CRC
        crc = lr1110_modem_compute_crc( 0xFF, command, command_length );

        error_flag |= spi_master_write( &ctx->spi, &crc, 1 );

        // NSS high
        spi_master_deselect_device( ctx->chip_select );

        // Wait on busy pin up to 1000 ms
        if( lr1110_modem_hal_wait_on_busy( ctx, 1000 ) != LR1110_MODEM_HAL_STATUS_OK )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }

        // Send dummy byte to retrieve RC & CRC

        // NSS low
        spi_master_select_device( ctx->chip_select );

        // read RC
        error_flag |= spi_master_read( &ctx->spi, &status, 1 );

        error_flag |= spi_master_read( &ctx->spi, data_buf, data_length );

        error_flag |= spi_master_read( &ctx->spi, &crc_received, 1 );

        // NSS high
        spi_master_deselect_device( ctx->chip_select );

        // Compute response crc
        crc = lr1110_modem_compute_crc( 0xFF, &status, 1 );
        crc = lr1110_modem_compute_crc( crc, data_buf, data_length );

        if( crc != crc_received )
        {
            // change the response code
            error_flag = LR1110_MODEM_HAL_STATUS_BAD_FRAME;
        }
        // Wait on busy pin up to 1000 ms
        if( lr1110_modem_hal_wait_on_unbusy( ctx, 1000 ) != LR1110_MODEM_HAL_STATUS_OK )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }

        // Wait on busy pin up to 1000 ms
        if( lr1110_modem_hal_wait_on_busy( ctx, 1000 ) != LR1110_MODEM_HAL_STATUS_OK )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }
        else
        {
            return error_flag;
        }
    }

    return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
}

err_t lr1110_modem_hal_write( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                            uint8_t* data_buf, uint16_t data_length )
{
    if( lr1110_modem_hal_wakeup( ctx ) == LR1110_MODEM_HAL_STATUS_OK )
    {
        err_t error_flag     = LRIOT_OK;
        uint8_t crc          = 0;
        uint8_t crc_received = 0;
        uint8_t status;

        // NSS low
        spi_master_select_device( ctx->chip_select );

        // Send CMD
        if ( command_length > 0 )
        {
            error_flag |= spi_master_write( &ctx->spi, command, command_length );
        }
        // Send Data
        
        if ( data_length > 0 )
        {
            error_flag |= spi_master_write( &ctx->spi, data_buf, data_length );
        }
        // Compute and send CRC
        crc = lr1110_modem_compute_crc( 0xFF, command, command_length );
        crc = lr1110_modem_compute_crc( crc, data_buf, data_length );

        error_flag |= spi_master_write( &ctx->spi, &crc, 1 );

        // NSS high
        spi_master_deselect_device( ctx->chip_select );

        // Wait on busy pin up to 1000 ms
        if( lr1110_modem_hal_wait_on_busy( ctx, 1000 ) != LR1110_MODEM_HAL_STATUS_OK )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }

        // Send dummy byte to retrieve RC & CRC

        // NSS low
        spi_master_select_device( ctx->chip_select );

        // read RC
        error_flag |= spi_master_read( &ctx->spi, &status, 1 );
        error_flag |= spi_master_read( &ctx->spi, &crc_received, 1 );

        // Compute response crc
        crc = lr1110_modem_compute_crc( 0xFF, &status, 1 );

        // NSS high
        spi_master_deselect_device( ctx->chip_select );

        if( crc != crc_received )
        {
            // change the response code
            error_flag = LR1110_MODEM_HAL_STATUS_BAD_FRAME;
        }

        // Don't wait on busy in these following cases
        // 0x0602 - LR1110_MODEM_GROUP_ID_MODEM / LR1110_MODEM_RESET_CMD
        // 0x0603 - LR1110_MODEM_GROUP_ID_MODEM / LR1110_MODEM_FACTORY_RESET_CMD

        if( ( ( ( command[ 0 ] << 8 ) | command[ 1 ] ) != 0x0602 ) && 
            ( ( ( command[ 0 ] << 8 ) | command[ 1 ] ) != 0x0603 ) )
        {
            // Wait on busy pin up to 1000 ms
            if( lr1110_modem_hal_wait_on_unbusy( ctx, 1000 ) != LR1110_MODEM_HAL_STATUS_OK )
            {
                return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
            }
            else
            {
                return error_flag;
            }
        }
        else
        {
            return error_flag;
        }
    }

    return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
}

err_t lr1110_modem_hal_write_without_rc( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                                       uint8_t* data_buf, uint16_t data_length )
{
    if( lr1110_modem_hal_wakeup( ctx ) == LR1110_MODEM_HAL_STATUS_OK )
    {
        uint8_t crc    = 0;

        /* NSS low */
        spi_master_select_device( ctx->chip_select );

        // Send CMD
        err_t error_flag = spi_master_write( &ctx->spi, command, command_length );

        // Send Data
        error_flag |= spi_master_write( &ctx->spi, data_buf, data_length );

        /* Compute and send CRC */
        crc = lr1110_modem_compute_crc( 0xFF, command, command_length );
        crc = lr1110_modem_compute_crc( crc, data_buf, data_length );

        error_flag |= spi_master_write( &ctx->spi, &crc, 1 );

        /* NSS high */
        spi_master_deselect_device( ctx->chip_select );

        return error_flag;
    }

    return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
}

err_t lr1110_modem_hal_write_read( lriot_t *ctx, uint8_t* command, uint8_t* data_buf, uint16_t data_length )
{
    while ( lriot_get_busy_pin ( ctx ) );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, command, 1, data_buf, data_length );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t lr1110_modem_hal_wait_on_busy( lriot_t *ctx, uint32_t timeout_ms )
{
    uint32_t start_time = 0;
    while( lriot_get_busy_pin ( ctx ) == 0 )
    {
        if( start_time > timeout_ms )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }
        start_time++;
        Delay_1ms ( );
    }
    return LR1110_MODEM_HAL_STATUS_OK;
}

static err_t lr1110_modem_hal_wait_on_unbusy( lriot_t *ctx, uint32_t timeout_ms )
{
    uint32_t start_time = 0;
    while( lriot_get_busy_pin ( ctx ) == 1 )
    {
        if( start_time > timeout_ms )
        {
            return LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT;
        }
        start_time++;
        Delay_1ms ( );
    }
    return LR1110_MODEM_HAL_STATUS_OK;
}

static uint8_t lr1110_modem_compute_crc( uint8_t crc_initial_value, uint8_t* buffer, uint16_t length )
{
    uint8_t crc = crc_initial_value;
    uint8_t extract;
    uint8_t sum;
    for ( int i = 0; i < length; i++ )
    {
        extract = *buffer;
        for ( uint8_t j = 8; j; j-- )
        {
            sum = ( crc ^ extract ) & 0x01;
            crc >>= 1;
            if ( sum )
            {
                crc ^= 0x65;
            }
            extract >>= 1;
        }
        buffer++;
    }
    return crc;
}
