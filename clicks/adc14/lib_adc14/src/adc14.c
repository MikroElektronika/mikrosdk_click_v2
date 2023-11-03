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
 * @file adc14.c
 * @brief ADC 14 Click Driver.
 */

#include "adc14.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc14_cfg_setup ( adc14_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->shd  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->vref = ADC14_INT_VREF_2_048V;
}

err_t adc14_init ( adc14_t *ctx, adc14_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;
    
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

    digital_out_init( &ctx->shd, cfg->shd );
    
    adc14_device_power_up( ctx );

    return SPI_MASTER_SUCCESS;
}

void adc14_device_shutdown ( adc14_t *ctx ) 
{
    digital_out_low( &ctx->shd );
}

void adc14_device_power_up ( adc14_t *ctx ) 
{
    digital_out_high( &ctx->shd );
}

err_t adc14_read_conversion_data ( adc14_t *ctx, uint16_t *adc_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *adc_data = data_buf[ 0 ];
    *adc_data <<= 8;
    *adc_data |= data_buf[ 1 ];
    *adc_data >>= 2;
    *adc_data &= ADC14_RESOLUTION_12BIT;
    return err_flag;
}

err_t adc14_get_voltage ( adc14_t *ctx, float *voltage ) 
{
    err_t err_flag = ADC14_OK;
    uint16_t adc_data = DUMMY;
    for ( uint8_t n_cnt = 0; n_cnt < ADC14_MEASURE_NUM; n_cnt++ )
    {
        err_flag |= adc14_read_conversion_data( ctx, &adc_data );
        *voltage += ( float ) adc_data;
        Delay_1ms( );
    }
    *voltage /= ( float ) ADC14_MEASURE_NUM;
    *voltage *= ctx->vref;
    *voltage /= ADC14_RES_DIVIDER;
    *voltage *= ADC14_CONVERT_V_T_MV;
    return err_flag;
}

err_t adc14_set_vref ( adc14_t *ctx, float vref ) 
{
    err_t err_flag = ADC14_OK;
    if ( ( ADC14_EXT_VREF_3_3V < vref ) || ( ADC14_EXT_VREF_0V > vref ) )
    {
        err_flag = ADC14_ERROR;
    }
    else
    {
        err_flag = ADC14_OK;
        ctx->vref = vref;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
