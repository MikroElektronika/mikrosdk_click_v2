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

#include "bargraph3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BARGRAPH3_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bargraph3_cfg_setup ( bargraph3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->oe = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BARGRAPH3_RETVAL bargraph3_init ( bargraph3_t *ctx, bargraph3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BARGRAPH3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BARGRAPH3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BARGRAPH3_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->oe, cfg->oe );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );
    
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->pwm );

    // Input pins

    return BARGRAPH3_OK;
}

void bargraph3_generic_transfer ( bargraph3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void bargraph3_enable ( bargraph3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->oe, state );
}

void bargraph3_reset ( bargraph3_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms();
    digital_out_low( &ctx->rst );
    Delay_100ms();
    digital_out_high( &ctx->rst );
}

void bargraph3_set_pwm ( bargraph3_t *ctx, uint8_t state )
{
     digital_out_write( &ctx->pwm, state );
}

void bargraph3_display ( bargraph3_t *ctx, uint8_t ctrl, uint8_t dir, uint8_t counter)
{
    uint16_t convert = 0;
    uint8_t tmp[ 2 ];
    
    if ( ctrl == BARGRAPH3_INCREASE_LED )
    {
        if ( dir == BARGRAPH3_DIRECTION_TOP_TO_BOTTOM )
        {
            convert = ( 1 << counter ) - 1;
        }
        else
        {
            convert = ( uint8_t )( 0xFFE0 >> counter );
        }
    }
    else
    {
        if ( dir == BARGRAPH3_DIRECTION_TOP_TO_BOTTOM )
        {
            convert = ( 1 << counter );
        }
        else
        {
            convert = ( 0x20 >> counter );
        }
    }
    
    tmp[ 0 ] = 0x00;
    tmp[ 1 ] = convert ^ 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END

