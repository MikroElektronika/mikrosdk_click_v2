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

#include "spiisolator.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SPIISOLATOR_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void spiisolator_cfg_setup ( spiisolator_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

SPIISOLATOR_RETVAL spiisolator_init ( spiisolator_t *ctx, spiisolator_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = SPIISOLATOR_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SPIISOLATOR_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, SPIISOLATOR_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    spi_master_deselect_device( ctx->chip_select ); 

    return SPIISOLATOR_OK;

}

void spiisolator_generic_transfer 
( 
    spiisolator_t *ctx, 
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

void spiisolator_write_cmd ( spiisolator_t *ctx, uint8_t cmd, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = cmd;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

 void spiisolator_write_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t write_data )
 {
     uint8_t w_buffer[ 2 ];
     w_buffer[ 0 ] = reg_address;
     w_buffer[ 0 ] &= write_cmd;
     w_buffer[ 1 ] = write_data;
     spi_master_select_device( ctx->chip_select );
     spi_master_write( &ctx->spi, &w_buffer[ 0 ], 1 );
     spi_master_write( &ctx->spi, &w_buffer[ 1 ], 1 );
     spi_master_deselect_device( ctx->chip_select );
 }
 uint8_t spiisolator_read_byte ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd )
 {
     uint8_t w_buffer[ 1 ];
     uint8_t r_buffer[ 1 ];
     w_buffer[ 0 ] = reg_address;
     w_buffer[ 0 ] |= read_cmd;
     spi_master_select_device( ctx->chip_select );
  
    spi_master_write( &ctx->spi, &w_buffer[ 0 ], 1 );
    spi_master_read( &ctx->spi, &r_buffer[ 0 ], 1 );
  
     spi_master_deselect_device( ctx->chip_select );
     return r_buffer[ 0 ];
 }

void spiisolator_write_data ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint16_t write_data )
{
    uint8_t w_buffer[ 3 ];

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] &= write_cmd;

    w_buffer[ 1 ] = ( uint8_t ) write_data;
    w_buffer[ 2 ] = ( uint8_t ) ( write_data >> 8 );

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &w_buffer[ 0 ], 1 );
    spi_master_write( &ctx->spi, &w_buffer[ 1 ], 1 );
    spi_master_write( &ctx->spi, &w_buffer[ 2 ], 1 );

    spi_master_deselect_device( ctx->chip_select );
}

uint16_t spiisolator_read_data ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 2 ];
    uint16_t result;

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= read_cmd;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &w_buffer[ 0 ], 1 );

    spi_master_read( &ctx->spi, &r_buffer[ 0 ], 1 );
    spi_master_read( &ctx->spi, &r_buffer[ 1 ], 1 );
    
    spi_master_deselect_device( ctx->chip_select );
    
    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];

    return result;
}

void spiisolator_write_bytes ( spiisolator_t *ctx, uint8_t reg_address, uint8_t write_cmd, uint8_t *write_data, uint16_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer;

    w_buffer = reg_address;
    w_buffer &= write_cmd;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &w_buffer, 1 );

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        spi_master_write( &ctx->spi, &write_data[ cnt ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );
}

void spiisolator_read_bytes ( spiisolator_t *ctx, uint8_t reg_address, uint8_t read_cmd, uint8_t *read_data, uint16_t n_bytes )
{
    uint8_t w_buffer[ 1 ];
    
    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= read_cmd;

    spiisolator_generic_transfer( ctx, &w_buffer[ 0 ], 1, read_data, n_bytes + 1 );
}

// ------------------------------------------------------------------------- END


