/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "boost.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define BOOST_DUMMY               0x00

#define BOOST_ADC_VREF_VAL        2.048
#define BOOST_ADC_SPI_RESOLUTION  2097152
#define BOOST_R7                  15000
#define BOOST_R8                  470

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void boost_select_cs ( boost_t *ctx, pin_name_t cs );

static void boost_deselect_cs ( boost_t *ctx, pin_name_t cs );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void boost_cfg_setup ( boost_cfg_t *cfg )
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs1  = HAL_PIN_NC;
    cfg->cs2  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->spi_mode     = SPI_MASTER_MODE_3;
    cfg->cs1_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->cs2_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed    = 100000;

    cfg->dac.buf  = BOOST_CFG_VREF_BUFFERED;
    cfg->dac.ga   = BOOST_CFG_GAIN_1X;
    cfg->dac.shdn = BOOST_CFG_POWER_OUT_ON;
}

err_t boost_init ( boost_t *ctx, boost_cfg_t *cfg )
{
    digital_in_init( &ctx->miso, cfg->miso );

    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select1 = cfg->cs1;
    ctx->chip_select2 = cfg->cs2;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BOOST_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BOOST_DUMMY );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );

    ctx->cs1_polarity = cfg->cs1_polarity;
    ctx->cs2_polarity = cfg->cs2_polarity;

    digital_out_init( &ctx->cs1, ctx->chip_select1 );
    digital_out_init( &ctx->cs2, ctx->chip_select2 );

    boost_deselect_cs( ctx, ctx->chip_select1 );
    boost_deselect_cs( ctx, ctx->chip_select2 );

    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );

    ctx->dac.buf  = cfg->dac.buf;
    ctx->dac.ga   = cfg->dac.ga;
    ctx->dac.shdn = cfg->dac.shdn;

    return BOOST_OK;
}

void boost_device_enable ( boost_t *ctx )
{
    digital_out_high( &ctx->en );
}

void boost_device_disable ( boost_t *ctx )
{
    digital_out_low( &ctx->en );
}

void boost_dac_setup ( boost_t *ctx, boost_dac_cfg_t *cfg )
{
    ctx->dac.buf  = cfg->buf;
    ctx->dac.ga   = cfg->ga;
    ctx->dac.shdn = cfg->shdn;
}

err_t boost_dac_write ( boost_t *ctx, uint16_t dac_val )
{
    if ( dac_val > 4095 )
    {
        return BOOST_ERROR;
    }

    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = dac_val >> 8;
    write_buf[ 1 ] = dac_val;

    write_buf[ 0 ] |= ( ctx->dac.buf & 1 ) << 6;
    write_buf[ 0 ] |= ( ctx->dac.ga & 1 ) << 5;
    write_buf[ 0 ] |= ( ctx->dac.shdn & 1 ) << 4;

    boost_select_cs( ctx, ctx->chip_select1 );
    spi_master_write( &ctx->spi, write_buf, 2 );
    boost_deselect_cs( ctx, ctx->chip_select1 );

    return BOOST_OK;
}

float boost_vout_read ( boost_t *ctx )
{
    uint8_t rx_buf[ 3 ];

    boost_select_cs( ctx, ctx->chip_select2 );
    Delay_10us( );
    while ( digital_in_read( &ctx->miso ) );
    spi_master_read( &ctx->spi, rx_buf, 3 );
    boost_deselect_cs( ctx, ctx->chip_select2 );
    Delay_10us( );

    int32_t adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 2 ];

    if ( ( adc_val >> 22 ) == 2 )
    {
        adc_val |= 0xFFC00000;
    }
    else if ( ( adc_val >> 22 ) == 0 )
    {
        if ( adc_val & 0x200000 )
        {
            adc_val |= 0xFFC00000;
        }
    }
    else if ( ( adc_val >> 22 ) == 1 )
    {
        adc_val &= 0x003FFFFF;
    }

    float res = adc_val;
    res /= BOOST_ADC_SPI_RESOLUTION;
    res *= BOOST_ADC_VREF_VAL;
    res *= BOOST_R7 + BOOST_R8;
    res /= BOOST_R8;

    return res;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void boost_select_cs ( boost_t *ctx, pin_name_t cs )
{
    if ( cs == ctx->chip_select1 )
    {
        if ( ctx->cs1_polarity == SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW )
        {
            digital_out_low( &ctx->cs1 );
        }
        else
        {
            digital_out_high( &ctx->cs1 );
        }
    }
    else if ( cs == ctx->chip_select2 )
    {
        if ( ctx->cs2_polarity == SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW )
        {
            digital_out_low( &ctx->cs2 );
        }
        else
        {
            digital_out_high( &ctx->cs2 );
        }
    }
}

static void boost_deselect_cs ( boost_t *ctx, pin_name_t cs )
{
    if ( cs == ctx->chip_select1 )
    {
        if ( ctx->cs1_polarity == SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW )
        {
            digital_out_high( &ctx->cs1 );
        }
        else
        {
            digital_out_low( &ctx->cs1 );
        }
    }
    else if ( cs == ctx->chip_select2 )
    {
        if ( ctx->cs2_polarity == SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW )
        {
            digital_out_high( &ctx->cs2 );
        }
        else
        {
            digital_out_low( &ctx->cs2 );
        }
    }
}

// ------------------------------------------------------------------------ END
