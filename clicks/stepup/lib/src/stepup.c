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

#include "stepup.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define STEPUP_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void stepup_spi_set ( stepup_t *ctx, uint16_t command );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stepup_cfg_setup ( stepup_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mod = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->config_word_cfg = STEPUP_DACA | STEPUP_BUFFERED | STEPUP_GAIN_1X | STEPUP_POWER_UP;
}

STEPUP_RETVAL stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = STEPUP_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return STEPUP_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, STEPUP_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->mod, cfg->mod );
    digital_out_init( &ctx->en, cfg->en );

    spi_master_deselect_device( ctx->chip_select ); 
    digital_out_high( &ctx->mod );
    digital_out_high( &ctx->en );

    return STEPUP_OK;

}

void stepup_default_cfg ( stepup_t *ctx, uint16_t out_value )
{
    // Click default configuration 
    digital_out_low( &ctx->mod );
    digital_out_high( &ctx->en );

    stepup_set_out( ctx, out_value );
}

void stepup_generic_transfer 
( 
    stepup_t *ctx, 
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

void stepup_mod_set ( stepup_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->mod, pin_state );
}

void stepup_en_set ( stepup_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->en, pin_state );
}

uint8_t stepup_set_config ( stepup_t *ctx, uint16_t config )
{
    if ( ( config & 0x0FFF ) != 0 ) 
    {
        return 1;
    }

    ctx->config_word = config;
    
    return 0;
}

uint8_t stepup_set_out ( stepup_t *ctx, uint16_t out_value )
{
    uint16_t aux_value;
    
    if ( out_value > 4095 )
    {
        return 1;
    }

    aux_value = ctx->config_word;
    aux_value |= out_value;
    stepup_spi_set( ctx, aux_value );
    
    return 0;
}

float stepup_get_percent ( uint16_t out_value )
{
    float aux_out;
    
    aux_out  = ( float )( out_value ) / 4095;
    aux_out *= 100;
    aux_out  = ( float )( 100 - aux_out );
    
    return aux_out;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void stepup_spi_set ( stepup_t *ctx, uint16_t command )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = command >> 8 ;
    aux_buffer[ 1 ] = command & 0x00FF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &aux_buffer[ 0 ], 1 );
    spi_master_write( &ctx->spi, &aux_buffer[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

// ------------------------------------------------------------------------- END

