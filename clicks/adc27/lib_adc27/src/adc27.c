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
 * @file adc27.c
 * @brief ADC 27 Click Driver.
 */

#include "adc27.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc27_cfg_setup ( adc27_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc27_init ( adc27_t *ctx, adc27_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t adc27_default_cfg ( adc27_t *ctx ) 
{
    err_t error_flag = ADC27_OK;
    memset ( ctx->config, 0, sizeof ( ctx->config ) );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_SGL_0 | ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_2_POS );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_SGL_1 | ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_POS );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_SGL_2 | ADC27_CONFIG_RANGE_SGL_VREF_4_NEG_TO_VREF_4_POS );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_SGL_3 | ADC27_CONFIG_RANGE_SGL_VREF_2_NEG_TO_VREF_2_POS );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_DIF_45 | ADC27_CONFIG_RANGE_DIF_VREF_NEG_TO_VREF_POS );
    error_flag |= adc27_set_config ( ctx, ADC27_CONFIG_CH_DIF_67 | ADC27_CONFIG_RANGE_DIF_2_VREF_NEG_TO_2_VREF_POS );
    error_flag |= adc27_set_mode ( ctx, ADC27_MODE_EXT_CLOCK );
    return error_flag;
}

err_t adc27_set_config ( adc27_t *ctx, uint8_t config ) 
{
    err_t error_flag = ADC27_OK;
    uint8_t input_byte = config | ADC27_START_BIT;
    if ( ( config & ADC27_CONFIG_RANGE_MASK ) > ADC27_CONFIG_RANGE_DIF_NO_CHANGE )
    {
        if ( ( ADC27_CONFIG_CH_DIF_01 != ( config & ADC27_CONFIG_CH_MASK ) ) &&
             ( ADC27_CONFIG_CH_DIF_23 != ( config & ADC27_CONFIG_CH_MASK ) ) &&
             ( ADC27_CONFIG_CH_DIF_45 != ( config & ADC27_CONFIG_CH_MASK ) ) &&
             ( ADC27_CONFIG_CH_DIF_67 != ( config & ADC27_CONFIG_CH_MASK ) ) )
        {
            return ADC27_ERROR;
        }
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &input_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->config[ ( config & ADC27_CONFIG_CH_MASK ) >> 4 ] = input_byte;
    return error_flag;
}

err_t adc27_set_mode ( adc27_t *ctx, uint8_t mode ) 
{
    err_t error_flag = ADC27_OK;
    uint8_t input_byte = mode | ADC27_START_BIT;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &input_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->mode = input_byte;
    return error_flag;
}

err_t adc27_read_raw_data ( adc27_t *ctx, uint8_t channel, uint16_t *data_out ) 
{
    err_t error_flag = ADC27_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t timeout_cnt = 0;
    if ( NULL == data_out )
    {
        return ADC27_ERROR;
    }
    data_buf[ 0 ] = channel | ADC27_START_BIT;
    if ( ADC27_MODE_EXT_CLOCK == ( ctx->mode & ADC27_MODE_MASK ) )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else if ( ADC27_MODE_EXT_ACQUISITION == ( ctx->mode & ADC27_MODE_MASK ) )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
        while ( !adc27_get_int_pin ( ctx ) )
        {
            if ( ++timeout_cnt > ADC27_TIMEOUT )
            {
                return ADC27_ERROR;
            }
            Delay_1ms ( );
        }
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        error_flag |= ADC27_ERROR;
    }

    if ( ADC27_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t adc27_read_voltage ( adc27_t *ctx, uint8_t channel, float *voltage ) 
{
    err_t error_flag = ADC27_OK;
    uint16_t raw_data = 0;
    uint8_t range = ctx->config[ ( channel & ADC27_CONFIG_CH_MASK ) >> 4 ] & ADC27_CONFIG_RANGE_MASK;
    if ( NULL == voltage )
    {
        return ADC27_ERROR;
    }
    error_flag |= adc27_read_raw_data ( ctx, channel, &raw_data );
    if ( ADC27_OK == error_flag )
    {
        switch ( range )
        {
            case ADC27_CONFIG_RANGE_SGL_VREF_4_NEG_TO_VREF_4_POS:
            {
                *voltage = ( ADC27_VREF / 4 ) * ( ( float ) raw_data - ADC27_DATA_RES_HALF ) / ADC27_DATA_RES_HALF;
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_VREF_2_NEG_TO_GND:
            {
                *voltage = ( ADC27_VREF / 2 ) * raw_data / ADC27_DATA_RES_FULL - ( ADC27_VREF / 2 );
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_2_POS:
            {
                *voltage = ( ADC27_VREF / 2 ) * raw_data / ADC27_DATA_RES_FULL;
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_VREF_2_NEG_TO_VREF_2_POS:
            case ADC27_CONFIG_RANGE_DIF_VREF_2_NEG_TO_VREF_2_POS:
            {
                *voltage = ( ADC27_VREF / 2 ) * ( ( float ) raw_data - ADC27_DATA_RES_HALF ) / ADC27_DATA_RES_HALF;
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_VREF_NEG_TO_GND:
            {
                *voltage = ADC27_VREF * raw_data / ADC27_DATA_RES_FULL - ADC27_VREF;
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_GND_TO_VREF_POS:
            {
                *voltage = ADC27_VREF * raw_data / ADC27_DATA_RES_FULL;
                break;
            }
            case ADC27_CONFIG_RANGE_SGL_VREF_NEG_TO_VREF_POS:
            case ADC27_CONFIG_RANGE_DIF_VREF_NEG_TO_VREF_POS:
            {
                *voltage = ADC27_VREF * ( ( float ) raw_data - ADC27_DATA_RES_HALF ) / ADC27_DATA_RES_HALF;
                break;
            }
            case ADC27_CONFIG_RANGE_DIF_2_VREF_NEG_TO_2_VREF_POS:
            {
                *voltage = ( 2 * ADC27_VREF ) * ( ( float ) raw_data - ADC27_DATA_RES_HALF ) / ADC27_DATA_RES_HALF;
                break;
            }
        }
    }
    return error_flag;
}

uint8_t adc27_get_int_pin ( adc27_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
