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
 * @file dac24.c
 * @brief DAC 24 Click Driver.
 */

#include "dac24.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac24_cfg_setup ( dac24_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac24_init ( dac24_t *ctx, dac24_cfg_t *cfg ) 
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

err_t dac24_write_reg ( dac24_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac24_set_power_down ( dac24_t *ctx, uint8_t pwr )
{
    err_t error_flag = DAC24_OK;
    switch ( pwr )
    {
        case DAC24_POWER_DOWN_HIZ:
        {
            error_flag = dac24_write_reg ( ctx, DAC24_REG_POWER_DOWN_HIZ, DAC24_DAC_VALUE_MIN );
            break;
        }
        case DAC24_POWER_DOWN_2_5K:
        {
            error_flag = dac24_write_reg ( ctx, DAC24_REG_POWER_DOWN_2_5K, DAC24_DAC_VALUE_MIN );
            break;
        }
        case DAC24_POWER_DOWN_100K:
        {
            error_flag = dac24_write_reg ( ctx, DAC24_REG_POWER_DOWN_100K, DAC24_DAC_VALUE_MIN );
            break;
        }
        default:
        {
            error_flag = DAC24_ERROR;
            break;
        }
    }
    return error_flag;
}

err_t dac24_set_dac_value ( dac24_t *ctx, uint8_t channel, uint8_t value )
{
    err_t error_flag = DAC24_OK;
    if ( channel > DAC24_CHANNEL_3 )
    {
        return DAC24_ERROR;
    }
    if ( DAC24_CHANNEL_ALL == channel )
    {
        error_flag |= dac24_write_reg ( ctx, DAC24_REG_ALL_CH_DATA_OUT, value );
    }
    else
    {
        error_flag |= dac24_write_reg ( ctx, channel, value );
    }
    return error_flag;
}

err_t dac24_set_dac_voltage ( dac24_t *ctx, uint8_t channel, uint16_t voltage_mv )
{
    err_t error_flag = DAC24_OK;
    uint16_t dac_value = 0;
    if ( voltage_mv > DAC24_VCC_LEVEL )
    {
        return DAC24_ERROR;
    }
    dac_value = ( uint16_t ) ( ( float ) voltage_mv / DAC24_VCC_LEVEL * DAC24_DAC_VALUE_MAX );
    return dac24_set_dac_value ( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
