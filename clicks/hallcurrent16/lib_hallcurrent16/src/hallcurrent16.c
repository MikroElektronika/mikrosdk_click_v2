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
 * @file hallcurrent16.c
 * @brief Hall Current 16 Click Driver.
 */

#include "hallcurrent16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY    0x00

void hallcurrent16_cfg_setup ( hallcurrent16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ocf  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->vref    = HALLCURRENT16_VREF_3V3;
    cfg->gain    = HALLCURRENT16_GAIN_0;
}

err_t hallcurrent16_init ( hallcurrent16_t *ctx, hallcurrent16_cfg_t *cfg ) 
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
    
    ctx->vref = cfg->vref;
    ctx->gain = cfg->gain;

    digital_in_init( &ctx->ocf, cfg->ocf );
    return SPI_MASTER_SUCCESS;
}

err_t hallcurrent16_default_cfg ( hallcurrent16_t *ctx ) 
{
    float current = 0.0;
    hallcurrent16_set_sens( ctx );
    return hallcurrent16_get_current( ctx, &current );
}

void hallcurrent16_set_adc_vref ( hallcurrent16_t *ctx, float vref )
{
    ctx->vref = vref;
}

void hallcurrent16_set_sens ( hallcurrent16_t *ctx )
{
   switch ( ctx->gain )
    {
        case HALLCURRENT16_GAIN_0:
        {
            ctx->sens = HALLCURRENT16_SENS_CALC_GAIN_0;
            break;
        }
        case HALLCURRENT16_GAIN_1:
        {
            ctx->sens = HALLCURRENT16_SENS_CALC_GAIN_1;
            break;
        }
        case HALLCURRENT16_GAIN_2:
        {
            ctx->sens = HALLCURRENT16_SENS_CALC_GAIN_2;
            break;
        }
        case HALLCURRENT16_GAIN_3:
        {
            ctx->sens = HALLCURRENT16_SENS_CALC_GAIN_3;
            break;
        }
        default: 
        {
            ctx->sens = HALLCURRENT16_SENS_CALC_GAIN_0;
            break;
        }
    }
}

err_t hallcurrent16_get_voltage ( hallcurrent16_t *ctx, float *voltage )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    raw_adc = data_buf[ 0 ];
    raw_adc <<= 8;
    raw_adc |= data_buf[ 1 ];
    raw_adc &= HALLCURRENT16_RESOLUTION_12BIT;
    *voltage = ( float ) raw_adc;
    *voltage /= HALLCURRENT16_RESOLUTION_12BIT; 
    *voltage *= ctx->vref;
    return err_flag;
}

err_t hallcurrent16_get_vout ( hallcurrent16_t *ctx, float *adc_vout )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, HALLCURRENT16_ADDR_IN_CH_SEL_1 );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    err_flag |= hallcurrent16_get_voltage ( ctx, adc_vout );
    return err_flag;
}

err_t hallcurrent16_get_vref ( hallcurrent16_t *ctx, float *adc_vref )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, HALLCURRENT16_ADDR_IN_CH_SEL_2 );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    err_flag |= hallcurrent16_get_voltage ( ctx, adc_vref );
    return err_flag;
}


err_t hallcurrent16_get_current ( hallcurrent16_t *ctx, float *current )
{
    float adc_vout = 0.0, adc_vref = 0.0, vtg_sum = 0.0;
    uint16_t cnt = 0;
    err_t err_flag = HALLCURRENT16_OK;
    while ( cnt < HALLCURRENT16_ADC_NUM_OF_MEASURE )
    {
        err_flag |= hallcurrent16_get_vout ( ctx, &adc_vout );
        err_flag |= hallcurrent16_get_vref ( ctx, &adc_vref );
        vtg_sum += ( adc_vout - adc_vref );
        cnt++;
    }
    *current = vtg_sum;
    *current *= HALLCURRENT16_CONV_TO_MILI;
    *current /= ( float ) HALLCURRENT16_ADC_NUM_OF_MEASURE;
    *current /= ctx->sens;
    return err_flag;
}

uint8_t hallcurrent16_get_ovc_fault ( hallcurrent16_t *ctx ) 
{
    return digital_in_read( &ctx->ocf );
}

// ------------------------------------------------------------------------- END
