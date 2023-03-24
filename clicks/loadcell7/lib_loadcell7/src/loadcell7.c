/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file loadcell7.c
 * @brief Load Cell 7 Click Driver.
 */

#include "loadcell7.h"

void loadcell7_cfg_setup ( loadcell7_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;
}

err_t loadcell7_init ( loadcell7_t *ctx, loadcell7_cfg_t *cfg ) 
{
    if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->miso, cfg->miso ) )
    {
        return LOADCELL7_ERROR;
    }
    
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
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

    digital_out_init ( &ctx->cs, cfg->cs );
    
    loadcell7_enable_device ( ctx );
    Delay_100ms ( );
    
    return SPI_MASTER_SUCCESS;
}

void loadcell7_enable_device ( loadcell7_t *ctx )
{
    digital_out_high ( &ctx->cs );
}

void loadcell7_disable_device ( loadcell7_t *ctx )
{
    digital_out_low ( &ctx->cs );
}

err_t loadcell7_read_raw_adc ( loadcell7_t *ctx, int32_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    while ( digital_in_read( &ctx->miso ) );
    err_t error_flag = spi_master_read( &ctx->spi, data_buf, 3 );
    *data_out = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    *data_out = ( ( int32_t ) ( *data_out << 12 ) ) >> 12;
    return error_flag;
}

err_t loadcell7_tare_scale ( loadcell7_t *ctx )
{
    err_t error_flag = LOADCELL7_OK;
    uint16_t num_conv = 0;
    ctx->tare_scale = 0;
    while ( num_conv < LOADCELL7_NUM_CONVERSIONS )
    {
        int32_t raw_adc;
        error_flag |= loadcell7_read_raw_adc ( ctx, &raw_adc );
        ctx->tare_scale += raw_adc;
        num_conv++;
    }
    ctx->tare_scale /= LOADCELL7_NUM_CONVERSIONS;
    return error_flag;
}

err_t loadcell7_calibrate_weight ( loadcell7_t *ctx, float cal_weight )
{
    err_t error_flag = LOADCELL7_OK;
    int32_t net_weight_adc = 0;
    int32_t average_adc = 0;
    uint16_t num_conv = 0;
    while ( num_conv < LOADCELL7_NUM_CONVERSIONS )
    {
        int32_t raw_adc;
        error_flag |= loadcell7_read_raw_adc ( ctx, &raw_adc );
        average_adc += raw_adc;
        num_conv++;
    }
    average_adc /= LOADCELL7_NUM_CONVERSIONS;
    net_weight_adc = average_adc - ctx->tare_scale;
    if ( net_weight_adc )
    { 
        ctx->weight_scale = cal_weight / net_weight_adc;
    }
    return error_flag;
}

err_t loadcell7_get_weight ( loadcell7_t *ctx, float *weight )
{
    err_t error_flag = LOADCELL7_OK;
    int32_t average_adc = 0;
    uint16_t num_conv = 0;
    while ( num_conv < LOADCELL7_NUM_CONVERSIONS )
    {
        int32_t raw_adc;
        error_flag |= loadcell7_read_raw_adc ( ctx, &raw_adc );
        average_adc += raw_adc;
        num_conv++;
    }
    average_adc /= LOADCELL7_NUM_CONVERSIONS;
    *weight = ( average_adc - ctx->tare_scale ) * ctx->weight_scale;
    return error_flag;
}

// ------------------------------------------------------------------------- END
