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

#include "ozone2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OZONE2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ozone2_cfg_setup ( ozone2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

OZONE2_RETVAL ozone2_init ( ozone2_t *ctx, ozone2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = OZONE2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return OZONE2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, OZONE2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return OZONE2_OK;

}

uint32_t ozone2_read ( ozone2_t *ctx )
{
    uint8_t rx_buff[ 3 ];
    uint32_t res;

    for( ; ; )
    {
        digital_out_low( &ctx->cs );
        Delay_10us();
        if ( digital_in_read( &ctx->cs ) == 0 )
        {
        break;
        }
        digital_out_high( &ctx->cs );
        Delay_1us();
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buff, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    res = rx_buff[ 0 ];
    res <<= 8;
    res |= rx_buff[ 1 ];
    res <<= 8;
    res |= rx_buff[ 2 ];
    
    if ( res < 2000000 )
    {
        return res;
    }
    else 
        return 0;

}
// ------------------------------------------------------------------------- END

