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

#include "llcspi.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LLCSPI_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void llcspi_cfg_setup ( llcspi_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_speed = SPI_MEDIUM; 
    cfg->spi_mode = SPI_MODE_0;

}

LLCSPI_RETVAL llcspi_init ( llcspi_t *ctx, llcspi_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.pins.sck    = cfg->sck;
    spi_cfg.pins.miso   = cfg->miso;
    spi_cfg.pins.mosi   = cfg->mosi;
    spi_cfg.chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_SUCCESS )
    {
        return LLCSPI_INIT_ERROR;
    }

    spi_master_set_dummy_data( &ctx->spi, LLCSPI_DUMMY );
    
    spi_master_start( &ctx->spi );

    return LLCSPI_OK;
}

void llcspi_generic_transfer ( llcspi_t *ctx, spi_master_transfer_data_t *block )
{
    spi_master_start( &ctx->spi );
    spi_master_transfer( &ctx->spi, block );
    spi_master_stop( &ctx->spi );    
}

void spillc_set_cs_pin ( llcspi_t *ctx, uint8_t state ) 
{
    if ( state == 0 )
    {
        spi_master_start( &ctx->spi );
    }
    else
    {
        spi_master_stop( &ctx->spi );
    }
}

void spillc_generic_write ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes )
{
    spi_master_transfer_data_t block;

    block.tx_buffer = p_buf;
    block.tx_length = n_bytes;
    block.rx_buffer = NULL;
    block.rx_length = NULL;

    llcspi_generic_transfer( ctx, &block );
}

void spillc_generic_read ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes )
{
    spi_master_transfer_data_t block;

    block.tx_buffer = NULL;
    block.tx_length = NULL;
    block.rx_buffer = p_buf;
    block.rx_length = n_bytes;

    llcspi_generic_transfer( ctx, &block );
}

// ------------------------------------------------------------------------- END

