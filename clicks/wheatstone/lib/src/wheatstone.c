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

#include "wheatstone.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define WHEATSTONE_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static float drv_adc_vref = 2048.0;
static float drv_adc_res = 4095.0;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->an_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
}

WHEATSTONE_RETVAL wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    analog_in_config_t adc_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = WHEATSTONE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return WHEATSTONE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, WHEATSTONE_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return WHEATSTONE_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, 3.3 );
    analog_in_set_resolution( &ctx->adc, ANALOG_IN_RESOLUTION_10_BIT);
    
    spi_master_select_device( ctx->chip_select );

    return WHEATSTONE_OK;
}

void wheatstone_generic_transfer 
( 
    wheatstone_t *ctx, 
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

void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value )
{
    uint8_t buffer[ 4 ];

    buffer[ 0 ] = pot_value;
    
    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &buffer[ 0 ], 1 );

    spi_master_deselect_device( ctx->chip_select );
}

void wheatstone_set_adc_vref ( wheatstone_t *ctx, float vref )
{
    drv_adc_vref = vref;
}

void wheatstone_set_adc_resolution ( wheatstone_t *ctx, float res )
{
    drv_adc_res = res;
}

float wheatstone_get_voltage ( wheatstone_t *ctx, uint16_t adc_value )
{
    return ( float )( ( adc_value * drv_adc_vref ) / drv_adc_res );
}

uint16_t wheatstone_generic_read ( wheatstone_t *ctx )
{
    wheatstone_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

// ------------------------------------------------------------------------- END

