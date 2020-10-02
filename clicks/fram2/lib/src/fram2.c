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

#include "fram2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FRAM2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fram2_cfg_setup ( fram2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

FRAM2_RETVAL fram2_init ( fram2_t *ctx, fram2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FRAM2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FRAM2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FRAM2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_high( &ctx->hld );

    return FRAM2_OK;
}

void fram2_default_cfg ( fram2_t *ctx )
{
    fram2_write_enable( ctx ); 
}

void fram2_generic_transfer ( fram2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void fram2_set_hold_pin ( fram2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->hld, state );
}

void fram2_write_enable ( fram2_t *ctx ) 
{
    uint8_t temp[ 1 ];
    
    temp[ 0 ] = FRAM_WREN;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

void fram2_write_disable ( fram2_t *ctx )  
{
    uint8_t temp[ 1 ];

    temp[ 0 ] = FRAM_WRDI;
    fram2_write_enable(ctx);

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t fram2_read_status ( fram2_t *ctx ) 
{
    uint8_t temp[ 1 ];
    uint8_t receive_buf[ 1 ];

    temp[ 0 ] = FRAM_RDSR;
    
    fram2_generic_transfer(ctx, temp, 1, receive_buf, 1 );

    return receive_buf[ 0 ];
}

void fram2_write_status ( fram2_t *ctx, uint8_t value ) 
{
    uint8_t temp[ 2 ];

    temp[ 0 ] = FRAM_WRSR;
    temp[ 1 ] = value;

    fram2_write_enable( ctx );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void fram2_read( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t count ) 
{
    uint8_t temp[ 4 ];
    
    temp[ 0 ] = FRAM_READ;
    temp[ 1 ] = ( uint8_t )( address >> 16 );
    temp[ 2 ] = ( uint8_t )( address >> 8 );
    temp[ 3 ] = ( uint8_t )( address & 0x000000FF );

    fram2_generic_transfer( ctx, temp, 4, buffer, count );
}

void fram2_write ( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t counter ) 
{
    uint8_t temp[ 260 ];
    uint8_t i;

    temp[ 0 ] = FRAM_WRITE;
    temp[ 1 ] = ( uint8_t )( address >> 16 );
    temp[ 2 ] = ( uint8_t )( address >> 8 );
    temp[ 3 ] = ( uint8_t )( address & 0x000000FF );
                           
    for ( i = 4; i < counter + 4; i++ )
    {
        temp[ i ] = *buffer;
        buffer++;
    }

    fram2_write_enable(ctx);

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, counter + 4 );
    spi_master_deselect_device( ctx->chip_select ); 
}

// ------------------------------------------------------------------------- END

