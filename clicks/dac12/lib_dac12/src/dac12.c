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
 * @file dac12.c
 * @brief DAC 12 Click Driver.
 */

#include "dac12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac12_cfg_setup ( dac12_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac12_init ( dac12_t *ctx, dac12_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t dac12_default_cfg ( dac12_t *ctx ) 
{
    err_t error_flag = DAC12_OK;
    
    error_flag |= dac12_soft_reset ( ctx );
    Delay_100ms ( );
    
    if ( DAC12_ERROR == dac12_check_communication ( ctx ) )
    {
        return DAC12_ERROR;
    }
    
    error_flag |= dac12_set_gain ( ctx, DAC12_SELECT_CHANNEL_NONE );
    
    return error_flag;
}

err_t dac12_write_register ( dac12_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( reg > DAC12_REG_DAC7 )
    {
        return DAC12_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac12_read_register ( dac12_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( reg > DAC12_REG_DAC7 )
    {
        return DAC12_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg | DAC12_SPI_READ;
    data_buf[ 1 ] = DUMMY;
    data_buf[ 2 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    if ( data_buf[ 0 ] != ( reg | DAC12_SPI_READ ) )
    {
        return DAC12_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    return error_flag;
}

err_t dac12_check_communication ( dac12_t *ctx )
{
    uint16_t device_id;
    if ( DAC12_OK == dac12_read_register ( ctx, DAC12_REG_DEVICE_ID, &device_id ) )
    {
        if ( DAC12_DEVICE_ID == ( device_id & DAC12_DEVICE_ID_MASK ) )
        {
            return DAC12_OK;
        }
    }
    return DAC12_ERROR;
}

err_t dac12_soft_reset ( dac12_t *ctx )
{
    return dac12_write_register ( ctx, DAC12_REG_TRIGGER, DAC12_SOFT_RESET );
}

err_t dac12_set_gain ( dac12_t *ctx, uint8_t channel )
{
    if ( channel > DAC12_SELECT_CHANNEL_ALL )
    {
        return DAC12_ERROR;
    }
    ctx->channel_gain = channel;
    return dac12_write_register ( ctx, DAC12_REG_GAIN, channel | DAC12_GAIN_REFDIV_EN );
}

err_t dac12_set_channel_value ( dac12_t *ctx, uint8_t channel, uint16_t dac_value )
{
    err_t error_flag = DAC12_OK;
    if ( dac_value > DAC12_MAX_DAC_VALUE )
    {
        return DAC12_ERROR;
    }
    dac_value <<= 4;
    if ( DAC12_SELECT_CHANNEL_ALL == channel )
    {
        return dac12_write_register ( ctx, DAC12_REG_BROADCAST, dac_value );
    }
    for ( uint8_t cnt = DAC12_REG_DAC0; cnt <= DAC12_REG_DAC7; cnt++ )
    {
        if ( channel & 0x01 )
        {
            error_flag |= dac12_write_register ( ctx, cnt, dac_value );
        }
        channel >>= 1;
    }
    return error_flag;
}

err_t dac12_set_channel_voltage ( dac12_t *ctx, uint8_t channel, float voltage )
{
    err_t error_flag = DAC12_OK;
    if ( voltage > DAC12_INTERNAL_VREF )
    {
        return DAC12_ERROR;
    }
    float int_vref = DAC12_INTERNAL_VREF / 2.0; // The reference voltage is internally divided by 2
    if ( voltage > int_vref )
    {
        // Set gain of 2 for selected channels
        if ( ( ctx->channel_gain & channel ) != channel )
        {
            error_flag |= dac12_set_gain ( ctx, ctx->channel_gain | channel );
        }
        int_vref *= 2.0; 
    }
    else
    {
        // Disable gain for selected channels
        if ( ctx->channel_gain & channel )
        {
            error_flag |= dac12_set_gain ( ctx, ctx->channel_gain & ~channel );
        }
    }
    error_flag |= dac12_set_channel_value ( ctx, channel, 
                                            ( uint16_t ) ( ( voltage / int_vref ) * DAC12_MAX_DAC_VALUE ) );
    return error_flag;
}

// ------------------------------------------------------------------------- END
