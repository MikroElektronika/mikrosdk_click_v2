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

#include "dac6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DAC6_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac6_cfg_setup ( dac6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

DAC6_RETVAL dac6_init ( dac6_t *ctx, dac6_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DAC6_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DAC6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DAC6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return DAC6_OK;
}

void dac6_generic_transfer ( dac6_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

// Generic write function

void dac6_write_data ( dac6_t *ctx, uint16_t wr_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t ) ( wr_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) wr_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi,tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );  
}

// Set DAC output function

float dac6_set_output ( dac6_t *ctx )
{
    uint16_t temp;
    float v_out;
  
    temp = ( ctx->chan << 14 );
    temp |= ( ctx->op_mod << 12 );
    temp |= ( 0x0FFF & ctx->set_out );

    dac6_write_data( ctx, temp );
    
    v_out = ( float ) ctx->v_ref;
    v_out *= ( float ) ctx->set_out;
    v_out /= 4095.0;
    
    return v_out;
}

// ------------------------------------------------------------------------- END

