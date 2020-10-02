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

#include "bargraph.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BARGRAPH_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bargraph_cfg_setup ( bargraph_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mr = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BARGRAPH_RETVAL bargraph_init ( bargraph_t *ctx, bargraph_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BARGRAPH_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
    {
        return BARGRAPH_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BARGRAPH_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->mr, cfg->mr );
    digital_out_init( &ctx->pwm, cfg->pwm );
    
    digital_out_high( &ctx->pwm);

    return BARGRAPH_OK;
}

void bargraph_generic_transfer ( bargraph_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void bargraph_driver_init ( bargraph_t *ctx )
{
    digital_out_high( &ctx->mr );
    spi_master_deselect_device( ctx->chip_select );   
    digital_out_high( &ctx->pwm );
}

void bargraph_reset ( bargraph_t *ctx )
{
    digital_out_low( &ctx->mr );
    Delay_1ms( );
    digital_out_high( &ctx->mr );
}

void bargraph_display( bargraph_t *ctx, uint8_t input )
{
    uint16_t convert;
    uint8_t tmp[ 2 ];
  
    convert  = ( uint16_t )( ( 1 << input ) - 1 );
    tmp[ 1 ] = ( convert & 0x00FF );
    tmp[ 0 ] = ( convert & 0xFF00 ) >> 8;
  
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 2 );
    spi_master_deselect_device( ctx->chip_select );  
}

void bargraph_enable ( bargraph_t *ctx, uint8_t input )
{
    digital_out_write( &ctx->pwm, input );
}

// ------------------------------------------------------------------------- END

