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
    
    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
}

NOISE_RETVAL noise_init ( noise_t *ctx, noise_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    analog_in_config_t adc_cfg; // dodato
    
    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = NOISE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return NOISE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, NOISE_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    // dodato

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return NOISE_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, 3.3 );
    analog_in_set_resolution( &ctx->adc, ANALOG_IN_RESOLUTION_10_BIT);

    return NOISE_OK;
}

void noise_default_cfg ( noise_t *ctx )
{
    noise_reset( ctx );
    noise_set_command_register( ctx, NOISE_DEFAULT_COMMAND, NOISE_DEFAULT_THRESHOLD );
}

void noise_generic_transfer 
( 
    noise_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void noise_write_command_register ( noise_t *ctx, uint16_t command_and_data_bits )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = (uint8_t)(command_and_data_bits >> 8);
    aux_buffer[ 1 ] = (uint8_t)(command_and_data_bits);

    noise_generic_transfer( ctx, aux_buffer, 2, 0, 0 );
}

uint8_t noise_set_command_register ( noise_t *ctx, uint8_t configuration,
                                     uint16_t threshold )
{
    uint16_t command_and_data_bits;
    
    if (threshold > 4095)
    {
        return 1;
    }
    else
    {
        command_and_data_bits = configuration;
        command_and_data_bits <<= 12;
        command_and_data_bits |= threshold;
        
        noise_write_command_register( ctx, command_and_data_bits );
        return 0;
    }
}

void noise_set_state ( noise_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void noise_reset ( noise_t *ctx )
{
    noise_set_state( ctx, 1 );
    Delay_100ms( );
    noise_set_state( ctx, 0 );
}

uint8_t noise_check_int_pin ( noise_t *ctx )
{
    uint8_t int_status;

    int_status = digital_in_read( &ctx->int_pin );

    if (int_status == 0)
    {
        return 0;
    }
    else if (int_status == 1)
    {
        return 1;
    }
}

uint16_t noise_generic_read ( noise_t *ctx )
{
    uint16_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

// ------------------------------------------------------------------------- END

