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

#include "noise.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define NOISE_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void noise_cfg_setup ( noise_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
}

err_t noise_init ( noise_t *ctx, noise_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, NOISE_DUMMY ) ) 
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return NOISE_OK;
}

void noise_default_cfg ( noise_t *ctx )
{
    noise_reset ( ctx );
    noise_set_cmd_reg ( ctx, NOISE_DEFAULT_COMMAND, NOISE_DEFAULT_THRESHOLD );
}

void noise_write_cmd_reg ( noise_t *ctx, uint16_t cmd_data )
{
    uint8_t aux_buffer[ 2 ] = { 0 };

    aux_buffer[ 0 ] = ( uint8_t ) ( ( cmd_data >> 8 ) & 0xFF );
    aux_buffer[ 1 ] = ( uint8_t ) ( cmd_data & 0xFF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write ( &ctx->spi, aux_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

err_t noise_set_cmd_reg ( noise_t *ctx, uint8_t configuration, uint16_t threshold )
{
    uint16_t cmd_data = 0;
    if ( threshold > 4095 )
    {
        return NOISE_ERROR;
    }
    cmd_data = configuration;
    cmd_data <<= 12;
    cmd_data |= threshold;
    noise_write_cmd_reg ( ctx, cmd_data );
    return NOISE_OK;
}

void noise_set_state ( noise_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void noise_reset ( noise_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
}

uint8_t noise_check_int_pin ( noise_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t noise_read_an_pin_value ( noise_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t noise_read_an_pin_voltage ( noise_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END

