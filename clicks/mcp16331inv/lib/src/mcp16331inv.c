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

#include "mcp16331inv.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MCP16331INV_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp16331inv_cfg_setup ( mcp16331inv_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MCP16331INV_RETVAL mcp16331inv_init ( mcp16331inv_t *ctx, mcp16331inv_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MCP16331INV_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MCP16331INV_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MCP16331INV_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
   
    // Input pins

    digital_in_init( &ctx->an, cfg->an );
  
    spi_master_deselect_device( ctx->chip_select ); 
    digital_out_high( &ctx->rst );

    return MCP16331INV_OK;

}

void mcp16331inv_generic_transfer 
( 
    mcp16331inv_t *ctx, 
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

void mcp16331inv_set_dac_vout ( mcp16331inv_t *ctx, uint16_t dac_value, uint8_t gain_value, uint8_t mode )
{
    uint8_t temp[ 2 ] = { 0 };
    
    if ( gain_value & 0xFE )
    {
        return;
    }
    if ( mode & 0xFE )
    {
        return;
    }
    
    gain_value <<= 5;
    mode <<= 4;
    
    temp[ 0 ] = ( dac_value >> 8 ) & 0x0F;
    temp[ 0 ] |= gain_value;
    temp[ 0 ] |= mode;
    temp[ 0 ] |= 0x40;
    temp[ 1 ] = dac_value;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp[ 0 ], 1 );
    spi_master_write( &ctx->spi, &temp[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void mcp16331inv_enable_vin ( mcp16331inv_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

// ------------------------------------------------------------------------- END

