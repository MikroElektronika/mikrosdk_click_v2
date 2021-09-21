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
 * @file dac11.c
 * @brief DAC 11 Click Driver.
 */

#include "dac11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac11_cfg_setup ( dac11_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac11_init ( dac11_t *ctx, dac11_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return SPI_MASTER_SUCCESS;
}

err_t dac11_default_cfg ( dac11_t *ctx ) 
{
    err_t error_flag = dac11_write_control_reg( ctx, DAC11_CMD_WRM, DUMMY );
    error_flag |= dac11_set_all_ch_value( ctx, DAC11_MIN_DAC_VALUE );
    error_flag |= dac11_write_control_reg( ctx, DAC11_CMD_PD_HIGH_Z, DAC11_SELECT_ALL_CHANNELS );
    
    return error_flag;
}

err_t dac11_generic_write ( dac11_t *ctx, uint16_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 256 ] = { 0 };

    if ( len > 128 )
    {
        return DAC11_ERROR;
    }
    
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt * 2 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
        tx_buf[ cnt * 2 + 1 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len * 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t dac11_write_control_reg( dac11_t *ctx, uint8_t cmd, uint16_t data_in )
{
    uint16_t control_data = 0;
    
    if ( cmd > 0x0F )
    {
        return DAC11_ERROR;
    }
    
    if ( data_in > DAC11_MAX_DAC_VALUE )
    {
        data_in = DAC11_MAX_DAC_VALUE;
    }
    
    control_data = ( ( uint16_t ) cmd << 12 ) | data_in;
    
    return dac11_generic_write( ctx, &control_data, 1 );
}

err_t dac11_set_all_ch_value( dac11_t *ctx, uint16_t dac_value )
{
    if ( dac_value > DAC11_MAX_DAC_VALUE )
    {
        dac_value = DAC11_MAX_DAC_VALUE;
    }
    
    return dac11_write_control_reg( ctx, DAC11_CMD_BROADCAST, dac_value );
}

err_t dac11_set_all_ch_voltage( dac11_t *ctx, float vref, float voltage )
{
    uint16_t dac_value = ( uint16_t ) ( ( voltage / vref ) * ( DAC11_MAX_DAC_VALUE + 1 ) );
    
    return dac11_set_all_ch_value( ctx, ( uint16_t ) ( ( voltage / vref ) * ( DAC11_MAX_DAC_VALUE + 1 ) ) );
}

err_t dac11_set_specific_ch_value( dac11_t *ctx, uint8_t channel, uint16_t dac_value )
{
    err_t error_flag = DAC11_OK;
    uint8_t tmp_ch = channel;
    
    if ( dac_value > DAC11_MAX_DAC_VALUE )
    {
        dac_value = DAC11_MAX_DAC_VALUE;
    }
    
    if ( DAC11_SELECT_ALL_CHANNELS == channel )
    {
        return dac11_set_all_ch_value( ctx, dac_value );
    }
    
    for ( uint8_t cnt = DAC11_CMD_CHANNEL_A; cnt <= DAC11_CMD_CHANNEL_H; cnt++ )
    {
        if ( tmp_ch & 0x01 )
        {
            error_flag |= dac11_write_control_reg( ctx, cnt, dac_value );
        }
        tmp_ch >>= 1;
    }
     
    error_flag |= dac11_write_control_reg( ctx, DAC11_CMD_UPDATE_SELECT, channel );
    
    return error_flag;
}

err_t dac11_set_specific_ch_voltage( dac11_t *ctx, uint8_t channel, float vref, float voltage )
{
    uint16_t dac_value = ( uint16_t ) ( ( voltage / vref ) * ( DAC11_MAX_DAC_VALUE + 1 ) );
    
    return dac11_set_specific_ch_value( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
