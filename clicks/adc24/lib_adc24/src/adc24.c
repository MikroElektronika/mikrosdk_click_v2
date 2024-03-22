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
 * @file adc24.c
 * @brief ADC 24 Click Driver.
 */

#include "adc24.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc24_cfg_setup ( adc24_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc24_init ( adc24_t *ctx, adc24_cfg_t *cfg ) 
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

err_t adc24_generic_write ( adc24_t *ctx, uint16_t control ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( control >> 8 );
    data_buf[ 1 ] = ( uint8_t ) control;

    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t adc24_generic_read ( adc24_t *ctx, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_t err_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t adc24_get_adc_data ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, uint16_t *adc_data ) 
{
    uint16_t control = DUMMY, data_buf = DUMMY;
    control = ADC24_CTRL_SET_WRITE; 
    control |= ( ( uint16_t ) ( ctrl.seq_shadow & ADC24_SEQ_SHADOW_ALTERED ) ) << 9;
    control |= ( ( uint16_t ) ( ctrl.ch_sel     & ADC24_CH_SEL_IN_15 ) ) << 6;
    control |= ( ( uint16_t ) ( ctrl.pm         & ADC24_PM_NORMAL ) ) << 4;
    control |= ( ( uint16_t ) ( ctrl.seq_shadow & ADC24_SEQ_SHADOW_PROGRAMMING ) ) << 3;
    control |= ( ( uint16_t ) ( ctrl.weak       & ADC24_WEAK_DOUT_WEAKLY_DRIVEN ) ) << 2;
    control |= ( ( uint16_t ) ( ctrl.range      & ADC24_RANGE_VREF_2V5 ) ) << 1;
    control |= ( uint16_t )   ( ctrl.coding     & ADC24_CODING_BIN );
    control <<= 4;

    err_t err_flag = adc24_generic_write( ctx, control );
    Delay_10us( );
    err_flag = adc24_generic_read( ctx, &data_buf );

    *in_pos = ( uint8_t ) ( ( data_buf >> 12 ) & ADC24_CH_SEL_IN_15 );
    *adc_data = data_buf & ADC24_ADC_RESOLUTION;
    return err_flag;
}

err_t adc24_get_voltage ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, float *voltage ) 
{
    uint16_t adc_data = DUMMY;
    err_t err_flag = adc24_get_adc_data( ctx, ctrl, in_pos, &adc_data );
    *voltage = ( float )  adc_data;
    *voltage /= ( float ) ADC24_ADC_RESOLUTION;
    if ( ADC24_RANGE_VREF_5V == ctrl.range )
    {
        *voltage *= ADC24_VREF_5V;
    }
    else 
    {
        *voltage *= ADC24_VREF_2V5;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
