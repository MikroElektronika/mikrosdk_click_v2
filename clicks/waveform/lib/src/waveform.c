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

#include "waveform.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define WAVEFORM_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void waveform_cfg_setup ( waveform_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

WAVEFORM_RETVAL waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = WAVEFORM_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return WAVEFORM_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, WAVEFORM_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );

    spi_master_deselect_device( ctx->chip_select );  
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->pwm );

    return WAVEFORM_OK;
}

void waveform_digipot_dec ( waveform_t *ctx ) 
{       
    uint8_t transfer;

    transfer = 0x07;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, &transfer, 1 );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select ); 
}

void waveform_digipot_inc ( waveform_t *ctx ) 
{    
    uint8_t transfer;
    
    transfer = 0x1F;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, &transfer, 1 );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select ); 
}

void waveform_write_reg ( waveform_t *ctx, uint16_t reg_setting )
{
    uint8_t temp[ 2 ];

    temp[ 0 ] = ( uint8_t ) ( reg_setting >> 8 );
    temp[ 1 ] = ( uint8_t ) ( reg_setting );

    digital_out_low( &ctx->rst );
    Delay_1ms( );
    spi_master_write( &ctx->spi, temp, 2 );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
}

void waveform_write_freqency ( waveform_t *ctx, uint32_t f )
{
    uint16_t fekreg_0 = 0;
    uint16_t fekreg_1 = 0;

    fekreg_0 = f & 0x7FFF;
    fekreg_1 = ( f >> 14 ) & 0x7FFF;
    
    waveform_write_reg( ctx, 0x0000 );
    waveform_write_reg( ctx, 0x8000 | fekreg_0 );
 
    waveform_write_reg( ctx, 0x1000 );
    waveform_write_reg( ctx, 0x4000 | fekreg_1 );
}

void waveform_sine_output ( waveform_t *ctx, uint32_t f )
{
    waveform_write_freqency( ctx, f );
    waveform_write_reg( ctx, 0x2100 );
    waveform_write_reg( ctx, 0x2000 );
}

void waveform_triangle_output ( waveform_t *ctx, uint32_t f )
{
    waveform_write_freqency( ctx, f );
    waveform_write_reg( ctx, WAVEFORM_CR_B28_BITMASK | WAVEFORM_CR_MODE_BITMASK );
}

void waveform_square_output ( waveform_t *ctx, uint32_t f )
{
    waveform_write_freqency( ctx, f );
    waveform_write_reg( ctx, WAVEFORM_CR_B28_BITMASK | 
                                WAVEFORM_CR_DIV2_BITMASK | 
                                WAVEFORM_CR_OPBITEN_BITMASK );
}

// ------------------------------------------------------------------------- END

