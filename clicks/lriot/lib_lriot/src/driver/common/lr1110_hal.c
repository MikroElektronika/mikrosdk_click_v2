/**
 * @file      lr1110_hal.c
 *
 * @brief     HAL implementation for LR1110 radio chip
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

#include "common/lr1110_hal.h"

/*!
 * @brief Return the computed CRC
 *
 * @param [in] initial_value initial value of the CRC
 * @param [in] buffer Buffer containing data used to compute the CRC
 * @param [in] length Length of buffer
 *
 * @returns CRC value
 */
static uint8_t lr1110_hal_compute_crc( uint8_t initial_value, uint8_t* buffer, uint16_t length );

err_t lr1110_hal_reset( lriot_t *ctx )
{
    lriot_set_rst_pin( ctx, 0 );
    Delay_1ms( );
    lriot_set_rst_pin( ctx, 1 );

    return LRIOT_OK;
}

err_t lr1110_hal_wakeup( lriot_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );

    return LRIOT_OK;
}

err_t lr1110_hal_read( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                     uint8_t* data_buf, uint16_t data_length )
{
    uint8_t  dummy_byte  = 0x00;

    while ( lriot_get_busy_pin ( ctx ) );

    /* 1st SPI transaction */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, command, command_length );
    spi_master_deselect_device( ctx->chip_select );

    while ( lriot_get_busy_pin ( ctx ) );

    /* 2nd SPI transaction */
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &dummy_byte, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, LR1110_NOP );
    error_flag |= spi_master_read( &ctx->spi, data_buf, data_length );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t lr1110_hal_write( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                      uint8_t* data_buf, uint16_t data_length )
{
    err_t error_flag = LRIOT_OK;
    while ( lriot_get_busy_pin ( ctx ) );

    spi_master_select_device( ctx->chip_select );
    if ( command_length > 0 )
    {
        error_flag |= spi_master_write( &ctx->spi, command, command_length );
    }
    if ( data_length > 0 )
    {
        error_flag |= spi_master_write( &ctx->spi, data_buf, data_length );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t lr1110_hal_direct_read( lriot_t *ctx, uint8_t* data_buf, uint16_t data_length )
{
    while ( lriot_get_busy_pin ( ctx ) );

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, LR1110_NOP );
    error_flag |= spi_master_read( &ctx->spi, data_buf, data_length );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static uint8_t lr1110_hal_compute_crc( uint8_t initial_value, uint8_t* buffer, uint16_t length )
{
    uint8_t crc = initial_value;

    for ( uint16_t i = 0; i < length; i++ )
    {
        uint8_t extract = buffer[i];
        uint8_t sum;

        for ( uint8_t j = 8; j > 0; j-- )
        {
            sum = ( crc ^ extract ) & 0x01;
            crc >>= 1;

            if ( sum != 0 )
            {
                crc ^= 0x65;
            }

            extract >>= 1;
        }
    }

    return crc;
}
