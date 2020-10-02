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

#include "thumbstick.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THUMBSTICK_DUMMY 0
#define THUMBSTICK_MARGIN 1365

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

THUMBSTICK_RETVAL thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = THUMBSTICK_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return THUMBSTICK_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, THUMBSTICK_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THUMBSTICK_OK;
}

void thumbstick_generic_transfer 
( 
    thumbstick_t *ctx, 
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

uint16_t thumbstick_read_data ( thumbstick_t *ctx, uint8_t channel )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];

    uint16_t result;

    result = 0x00;
    tx_buf[ 0 ] = 0x06;
    tx_buf[ 1 ] = channel;

    thumbstick_generic_transfer ( ctx, tx_buf, 2, rx_buf, 3 );

    result = rx_buf[ 1 ] & 0x0F;
    result <<= 8;
    result |= rx_buf[ 2 ];

    return result;
}

uint8_t thumbstick_get_position ( thumbstick_t *ctx )
{
    uint16_t ver;
    uint16_t hor;
    uint8_t pos;

    ver  = thumbstick_read_data( ctx, THUMBSTICK_CHANNEL_V );
    hor  = thumbstick_read_data( ctx, THUMBSTICK_CHANNEL_H );

    pos = THUMBSTICK_POSITION_START;

    if ( ( ver < THUMBSTICK_MARGIN ) && ( hor > THUMBSTICK_MARGIN ) && ( hor < ( 2 * THUMBSTICK_MARGIN) ) )
    {
        pos = THUMBSTICK_POSITION_TOP;
    }
    else if ( ( ver > ( 2 * THUMBSTICK_MARGIN ) ) && ( hor > THUMBSTICK_MARGIN ) && ( hor < ( 2 * THUMBSTICK_MARGIN ) ) )
    {
        pos = THUMBSTICK_CHANNEL_BOTTOM;
    }
    else if ( hor < THUMBSTICK_MARGIN )
    {
        pos = THUMBSTICK_CHANNEL_LEFT;
    }
    else if ( hor > ( 2 * THUMBSTICK_MARGIN ) )
    {
        pos = THUMBSTICK_POSITION_RIGHT;
    }
    return pos;
}

uint8_t thumbstick_button_state ( thumbstick_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

