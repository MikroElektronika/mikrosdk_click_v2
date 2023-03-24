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

#include "c420mar.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define c420MAR_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c420mar_cfg_setup ( c420mar_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->en = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

c420MAR_RETVAL c420mar_init ( c420mar_t *ctx, c420mar_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = c420MAR_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return c420MAR_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, c420MAR_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );
    digital_out_high( &ctx->cs );

    return c420MAR_OK;
}

void c420mar_generic_transfer ( c420mar_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

float c420mar_read_data ( c420mar_t *ctx )
{
    uint8_t tmp;
    uint16_t value;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, &tmp, 1 );
    value = tmp & 0x1F;
    value <<= 8;
    spi_master_read( &ctx->spi, &tmp, 1 );
    value |= tmp;
    value >>= 1;
    spi_master_deselect_device( ctx->chip_select );

    return ( float ) value / ( 20 * 10 );
}

// ------------------------------------------------------------------------- END

