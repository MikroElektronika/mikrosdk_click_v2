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

#include "digipot6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DIGIPOT6_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void digipot6_cfg_setup ( digipot6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

DIGIPOT6_RETVAL digipot6_init ( digipot6_t *ctx, digipot6_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data =DIGIPOT6_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DIGIPOT6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi,DIGIPOT6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return DIGIPOT6_OK;
}

void digipot6_default_cfg ( digipot6_t *ctx )
{
    digipot6_set_resistor( ctx, DIGIPOT6_CONNECT, DIGIPOT6_TCON_MASK_R0HW, DIGIPOT6_TCON_R0HW );
    digipot6_set_resistor( ctx, DIGIPOT6_CONNECT, DIGIPOT6_TCON_MASK_R0B, DIGIPOT6_TCON_R0B );
    digipot6_set_resistor( ctx, DIGIPOT6_CONNECT, DIGIPOT6_TCON_MASK_R0W, DIGIPOT6_TCON_R0W );
    digipot6_set_resistor( ctx, DIGIPOT6_CONNECT, DIGIPOT6_TCON_MASK_R0A, DIGIPOT6_TCON_R0A );
}

void digipot6_write_data ( digipot6_t *ctx, uint8_t reg, uint8_t w_data )
{
    uint8_t tmp;
    tmp = ( reg | DIGIPOT6_CMD_WRITE ) << 2;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_write( &ctx->spi, &w_data, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void digipot6_write_wiper_cmd ( digipot6_t *ctx, uint8_t cmd )
{
    uint8_t tmp;
    tmp = ( DIGIPOT6_VOLATILE_WIPER_0 | cmd ) << 2;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t digipot6_read_data ( digipot6_t *ctx, uint8_t reg ) 
{
    uint8_t w_buf[ 2 ];
    uint8_t r_buf[ 2 ];

    w_buf[ 0 ] = ( reg | DIGIPOT6_CMD_READ ) << 2;
    w_buf[ 1 ] = DIGIPOT6_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, w_buf, 2, r_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    return r_buf[ 0 ];
}

void digipot6_set_resistor ( digipot6_t *ctx, uint8_t state, uint8_t mask, uint8_t tcon )
{
    uint8_t tmp;

    tmp = digipot6_read_data( ctx, DIGIPOT6_TCON_REG );

    if ( state = DIGIPOT6_DISCONNECT )
    {
        tmp &= mask;
    }
    else if ( state == DIGIPOT6_CONNECT )
    {
        tmp |= tcon;
    }

    digipot6_write_data( ctx, DIGIPOT6_TCON_REG, tmp );
}

// ------------------------------------------------------------------------- END

