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
 * @file dac22.c
 * @brief DAC 22 Click Driver.
 */

#include "dac22.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac22_cfg_setup ( dac22_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->latch = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac22_init ( dac22_t *ctx, dac22_cfg_t *cfg ) 
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

    digital_out_init( &ctx->latch, cfg->latch );
    Delay_1ms ( );
    digital_out_high ( &ctx->latch );

    return SPI_MASTER_SUCCESS;
}

err_t dac22_default_cfg ( dac22_t *ctx ) 
{
    err_t error_flag = DAC22_OK;
    
    error_flag |= dac22_set_dac_value ( ctx, DAC22_CHANNEL_ALL, DAC22_DAC_VALUE_MIN );
    error_flag |= dac22_set_vref_control ( ctx, DAC22_CHANNEL_ALL, DAC22_VREF_BUFFERED );
    error_flag |= dac22_set_power_control ( ctx, DAC22_CHANNEL_ALL, DAC22_PWR_NORMAL_OPERATION );

    return error_flag;
}

err_t dac22_write_reg ( dac22_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC22_CMD_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac22_read_reg ( dac22_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = DAC22_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC22_CMD_READ;
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( DAC22_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

void dac22_set_latch_pin ( dac22_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->latch, state );
}

err_t dac22_set_vref_control ( dac22_t *ctx, uint8_t channel, uint8_t vref )
{
    uint16_t vref_ctrl = 0;
    if ( vref > DAC22_VREF_BUFFERED )
    {
        return DAC22_ERROR;
    }
    if ( channel & DAC22_CHANNEL_0 )
    {
        vref_ctrl |= ( ( uint16_t ) vref );
    }
    if ( channel & DAC22_CHANNEL_1 )
    {
        vref_ctrl |= ( ( uint16_t ) vref << 2 );
    }
    return dac22_write_reg ( ctx, DAC22_REG_VOLATILE_VREF, vref_ctrl );
}

err_t dac22_set_power_control ( dac22_t *ctx, uint8_t channel, uint8_t pwr )
{
    uint16_t pwr_ctrl = 0;
    if ( pwr > DAC22_PWR_PDOWN_HIZ )
    {
        return DAC22_ERROR;
    }
    if ( channel & DAC22_CHANNEL_0 )
    {
        pwr_ctrl |= ( ( uint16_t ) pwr );
    }
    if ( channel & DAC22_CHANNEL_1 )
    {
        pwr_ctrl |= ( ( uint16_t ) pwr << 2 );
    }
    return dac22_write_reg ( ctx, DAC22_REG_VOLATILE_POWER_DOWN, pwr_ctrl );
}

err_t dac22_set_dac_value ( dac22_t *ctx, uint8_t channel, uint16_t value )
{
    err_t error_flag = DAC22_OK;
    if ( value > DAC22_DAC_VALUE_MAX )
    {
        return DAC22_ERROR;
    }
    if ( channel & DAC22_CHANNEL_0 )
    {
        error_flag |= dac22_write_reg ( ctx, DAC22_REG_VOLATILE_DAC_WIPER_0, value );
    }
    if ( channel & DAC22_CHANNEL_1 )
    {
        error_flag |= dac22_write_reg ( ctx, DAC22_REG_VOLATILE_DAC_WIPER_1, value );
    }
    dac22_set_latch_pin ( ctx, 0 );
    Delay_10ms ( );
    dac22_set_latch_pin ( ctx, 1 );
    return error_flag;
}

err_t dac22_set_dac_voltage ( dac22_t *ctx, uint8_t channel, uint16_t voltage_mv )
{
    err_t error_flag = DAC22_OK;
    uint16_t dac_value = 0;
    if ( voltage_mv > DAC22_VREF_INT )
    {
        return DAC22_ERROR;
    }
    dac_value = ( uint16_t ) ( ( float ) voltage_mv / DAC22_VREF_INT * DAC22_DAC_VALUE_MAX );
    return dac22_set_dac_value ( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
