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
 * @file hallcurrent17.c
 * @brief Hall Current 17 Click Driver.
 */

#include "hallcurrent17.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void hallcurrent17_cfg_setup ( hallcurrent17_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hallcurrent17_init ( hallcurrent17_t *ctx, hallcurrent17_cfg_t *cfg ) 
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

err_t hallcurrent17_default_cfg ( hallcurrent17_t *ctx ) 
{
    float current = DUMMY;
    hallcurrent17_set_adc_vref( ctx, HALLCURRENT17_VREF_3V3 );
    return hallcurrent17_get_current( ctx, &current );
}

void hallcurrent17_set_adc_vref ( hallcurrent17_t *ctx, float vref )
{
    ctx->vref = vref;
}

err_t hallcurrent17_get_voltage ( hallcurrent17_t *ctx, float *voltage )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    raw_adc = data_buf[ 0 ];
    raw_adc <<= 8;
    raw_adc |= data_buf[ 1 ];
    raw_adc &= HALLCURRENT17_RESOLUTION_12BIT;
    *voltage = ( float ) raw_adc;
    *voltage /= HALLCURRENT17_RESOLUTION_12BIT; 
    *voltage *= ctx->vref;
    *voltage *= ( HALLCURRENT17_RES_R5_R7_100_KOHM + HALLCURRENT17_RES_R6_R8_100_KOHM );
    *voltage /= HALLCURRENT17_RES_R6_R8_100_KOHM;
    return err_flag;
}

err_t hallcurrent17_get_vref ( hallcurrent17_t *ctx, float *adc_vref )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, HALLCURRENT17_ADDR_IN_CH_SEL_1 );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    err_flag |= hallcurrent17_get_voltage ( ctx, adc_vref );
    return err_flag;
}

err_t hallcurrent17_get_vout ( hallcurrent17_t *ctx, float *adc_vout )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = spi_master_set_default_write_data( &ctx->spi, HALLCURRENT17_ADDR_IN_CH_SEL_2 );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    err_flag |= hallcurrent17_get_voltage ( ctx, adc_vout );
    return err_flag;
}

err_t hallcurrent17_get_current ( hallcurrent17_t *ctx, float *current )
{
    float adc_vout = DUMMY, adc_vref = DUMMY, vtg_sum = DUMMY;
    uint16_t cnt = DUMMY;
    err_t err_flag = HALLCURRENT17_OK;
    while ( cnt < HALLCURRENT17_NUM_OF_MEASURE )
    {
        err_flag |= hallcurrent17_get_vout ( ctx, &adc_vout );
        err_flag |= hallcurrent17_get_vref ( ctx, &adc_vref );
        vtg_sum += ( adc_vout - adc_vref );
        cnt++;
    }
    *current = vtg_sum;
    *current *= HALLCURRENT17_CONV_V_TO_MV;
    *current /= ( float ) HALLCURRENT17_NUM_OF_MEASURE;
    *current /= HALLCURRENT17_SENSITIVITY_MV_A;
    return err_flag;
}

// ------------------------------------------------------------------------- END
