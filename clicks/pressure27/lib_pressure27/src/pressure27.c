/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file pressure27.c
 * @brief Pressure 27 Click Driver.
 */

#include "pressure27.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void pressure27_cfg_setup ( pressure27_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->eoc  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t pressure27_init ( pressure27_t *ctx, pressure27_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->eoc, cfg->eoc );

    /* Perform a hardware reset */
    pressure27_hw_reset( ctx );
    
    return SPI_MASTER_SUCCESS;
}

void pressure27_hw_reset ( pressure27_t *ctx )
{
    /* After reset the sensor needs up to 2.5 ms before accepting commands. */
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

uint8_t pressure27_get_eoc ( pressure27_t *ctx )
{
    return digital_in_read( &ctx->eoc );
}

err_t pressure27_get_pressure ( pressure27_t *ctx, float *pressure )
{
    err_t    error_flag  = PRESSURE27_OK;
    uint8_t  cmd_buf[ 3 ] = { 0 };
    uint8_t  rx_buf[ 4 ]  = { 0 };
    uint8_t  status;
    uint32_t raw_counts;
    uint16_t timeout_ms;

    /* Create Output Measurement Command {0xAA, 0x00, 0x00}. 
     * Any data received on MISO during this transfer is from the previous
     * command and should be discarded. */ 
    cmd_buf[ 0 ] = PRESSURE27_CMD_MEASURE;
    cmd_buf[ 1 ] = DUMMY;
    cmd_buf[ 2 ] = DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, cmd_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    if ( PRESSURE27_OK != error_flag )
    {
        return PRESSURE27_ERROR;
    }

    /* Wait for End-of-Conversion by polling EOC pin 
     * which goes HIGH when the measurement is complete. */ 
    timeout_ms = PRESSURE27_CONVERSION_TIMEOUT_MS;
    while ( !pressure27_get_eoc( ctx ) && ( timeout_ms > 0 ) )
    {
        Delay_1ms( );
        timeout_ms--;
    }

    if ( 0 == timeout_ms )
    {
        return PRESSURE27_ERROR;
    }

    /* Read result using NOP command {0xF0, 0x00, 0x00, 0x00}.
     * The sensor outputs 4 bytes on MISO:
     *     Byte 0: Status byte
     *     Byte 1: Data[23:16]
     *     Byte 2: Data[15:8]
     *     Byte 3: Data[7:0] */ 
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, PRESSURE27_CMD_NOP );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &rx_buf[ 1 ], 3 );
    spi_master_deselect_device( ctx->chip_select );

    if ( PRESSURE27_OK != error_flag )
    {
        return PRESSURE27_ERROR;
    }

    /* Validate status byte. */
    status = rx_buf[ 0 ];

    if ( !( status & PRESSURE27_STATUS_POWER_BIT ) )
    {
        /* Sensor is not powered. */
        return PRESSURE27_ERROR;
    }

    if ( status & PRESSURE27_STATUS_BUSY_BIT )
    {
        /* Data not ready despite EOC. */
        return PRESSURE27_ERROR;
    }

    if ( ( status & PRESSURE27_STATUS_MEM_ERR_BIT ) ||
         ( status & PRESSURE27_STATUS_MATH_SAT_BIT ) )
    {
        /* Memory integrity failure or internal math saturation. */
        return PRESSURE27_ERROR;
    }

    /* Assemble 24-bit raw pressure counts from bytes 1?3. */
    raw_counts = ( ( uint32_t ) rx_buf[ 1 ] << 16 ) |
                 ( ( uint32_t ) rx_buf[ 2 ] << 8 ) |
                 ( ( uint32_t ) rx_buf[ 3 ] );

    /* Convert raw counts to pressure in kPa:
     * Pressure = ((Output - Outputmin) * (Pmax - Pmin))
     *            / (Outputmax - Outputmin) + Pmin    */
    *pressure = ( ( ( float ) raw_counts - PRESSURE27_OUTPUT_MIN ) *
                  ( PRESSURE27_PMAX_KPA - PRESSURE27_PMIN_KPA ) ) /
                  ( PRESSURE27_OUTPUT_MAX - PRESSURE27_OUTPUT_MIN ) +
                    PRESSURE27_PMIN_KPA;

    return PRESSURE27_OK;
}

// ------------------------------------------------------------------------- END
