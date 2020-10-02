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

#include "digipot2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DIGIPOT2_DUMMY 0

void digipot2_cfg_setup ( digipot2_cfg_t *cfg )
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

DIGIPOT2_RETVAL digipot2_init ( digipot2_t *ctx, digipot2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DIGIPOT2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DIGIPOT2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DIGIPOT2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return DIGIPOT2_OK;
}

void digipot2_generic_transfer ( digipot2_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void digipot2_write_byte ( digipot2_t *ctx, uint8_t command, uint8_t write_data )
{
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = command;
    buffer[ 1 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );  
}

void digipot2_set_wiper_positions ( digipot2_t *ctx, uint8_t wiper_positions )
{
    uint8_t buffer[ 4 ];
    
    wiper_positions %= 256;

    buffer[ 0 ] = 0x00;
    buffer[ 1 ] = wiper_positions;
    buffer[ 2 ] = 0x20;
    buffer[ 3 ] = wiper_positions;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buffer, 4 );
    spi_master_deselect_device( ctx->chip_select );  
}


float digipot2_convert_output ( digipot2_t *ctx, uint16_t value_adc, float v_ref )
{
    float result;

    result = ( ( float ) value_adc * v_ref ) / 4096.0;
    
    return result;
}
// ------------------------------------------------------------------------- END

