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
 * \file uv.c
 *
 */

#include "uv.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define UV_DUMMY            0       /*!< Dummy data. */

#define UV_DATA_MSB_MASK    0x3F    /*!< ADC data MSB byte mask. */
#define UV_DATA_MSB_OFFSET  7       /*!< ADC data MSB bits offset. */
#define UV_DATA_LSB_OFFSET  1       /*!< ADC data LSB bits offset. */

#define UV_ADC_RES_VAL      4096    /*!< ADC resolution value. */
#define UV_ADC_VREF_VAL     3.3     /*!< ADC refernce voltage value. */

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uv_cfg_setup ( uv_cfg_t *cfg )
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref_input = ANALOG_IN_VREF_EXTERNAL;
    cfg->vref_value = 3.3;
}

err_t uv_init ( uv_t *ctx, uv_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    analog_in_config_t an_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck      = cfg->sck;
    spi_cfg.miso     = cfg->miso;
    spi_cfg.mosi     = cfg->mosi;
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, UV_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    analog_in_configure_default( &an_cfg );

    an_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->an, &an_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_resolution( &ctx->an, cfg->resolution );
    analog_in_set_vref_input( &ctx->an, cfg->vref_input );
    analog_in_set_vref_value( &ctx->an, cfg->vref_value );

    if ( digital_out_init( &ctx->en, cfg->en ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    ctx->handler = NULL;

    return SPI_MASTER_SUCCESS;
}

void uv_set_callback_handler ( uv_t *ctx, uv_callback_t handler )
{
    ctx->handler = handler;
}

err_t uv_read_adc_value ( uv_t *ctx, uint16_t *data_out )
{
    uint8_t adc_data[ 2 ] = { UV_DUMMY };
    err_t err_stat = SPI_MASTER_SUCCESS;

    spi_master_select_device( ctx->chip_select );
    err_stat = spi_master_read( &ctx->spi, adc_data, 2 );
    spi_master_deselect_device( ctx->chip_select );

    if ( err_stat == SPI_MASTER_ERROR )
    {
        return SPI_MASTER_ERROR;
    }

    *data_out = adc_data[ 0 ] & UV_DATA_MSB_MASK;
    *data_out <<= UV_DATA_MSB_OFFSET;
    *data_out |= adc_data[ 1 ] >> UV_DATA_LSB_OFFSET;

    return SPI_MASTER_SUCCESS;
}

err_t uv_read_adc_voltage ( uv_t *ctx, float *data_out )
{
    uint16_t adc_data = UV_DUMMY;
    err_t err_stat = SPI_MASTER_SUCCESS;

    err_stat = uv_read_adc_value( ctx, &adc_data );

    if ( err_stat == SPI_MASTER_ERROR )
    {
        return SPI_MASTER_ERROR;
    }

    *data_out = adc_data;
    *data_out /= UV_ADC_RES_VAL;
    *data_out *= UV_ADC_VREF_VAL;

    return SPI_MASTER_SUCCESS;
}

err_t uv_read_an_pin_value ( uv_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->an, data_out );
}

err_t uv_read_an_pin_voltage ( uv_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->an, data_out );
}

void uv_calc_index ( uv_t *ctx, float data_in, uint8_t *data_out )
{
    float tmp;

    tmp = 12.49 * data_in - 12.49;

    if ( tmp < 0 )
    {
        tmp = 0;
    }

    *data_out = tmp;

    if ( ctx->handler == NULL )
    {
        return;
    }

    if ( *data_out <= 2 )
    {
        ctx->handler( "Risk of harm - Low" );
    }
    else if ( *data_out <= 5 )
    {
        ctx->handler( "Risk of harm - Moderate" );
    }
    else if ( *data_out <= 7 )
    {
        ctx->handler( "Risk of harm - High" );
    }
    else if ( *data_out <= 10 )
    {
        ctx->handler( "Risk of harm - Very high" );
    }
    else
    {
        ctx->handler( "Risk of harm - Extreme" );
    }
}

void uv_device_enable ( uv_t *ctx )
{
    digital_out_high( &ctx->en );
}

void uv_device_disable ( uv_t *ctx )
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END
