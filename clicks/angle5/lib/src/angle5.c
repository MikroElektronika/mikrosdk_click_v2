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

#include "angle5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ANGLE5_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void angle5_cfg_setup ( angle5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mgh = HAL_PIN_NC;
    cfg->mgl = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

ANGLE5_RETVAL angle5_init ( angle5_t *ctx, angle5_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ANGLE5_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ANGLE5_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ANGLE5_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Input pins

    digital_in_init( &ctx->mgh, cfg->mgh );
    digital_in_init( &ctx->mgl, cfg->mgl );

    return ANGLE5_OK;
}

void angle5_generic_transfer 
( 
    angle5_t *ctx, 
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

uint16_t angle5_read_raw_angle ( angle5_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t raw_angle;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );  

    raw_angle = rx_buf[ 0 ];
    raw_angle <<= 8;
    raw_angle |= rx_buf[ 1 ];

    return raw_angle;
}

float angle5_read_angle_deg ( angle5_t *ctx )
{
    float angle;
    uint16_t raw_angle;

    raw_angle = angle5_read_raw_angle( ctx );
    angle = ( raw_angle * 360.0 ) / 65536.0;

    return angle;
}

uint16_t angle5_read_register ( angle5_t *ctx, uint8_t reg_addr, uint8_t *rsp )
{
    uint8_t angle_rx_buf[ 2 ];
    uint8_t reg_rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t angle;

    tx_buf[ 0 ] = ANGLE5_CMD_READ | reg_addr;
    tx_buf[ 1 ] = ANGLE5_DUMMY;

    // send command and read angle
    angle5_generic_transfer( ctx, tx_buf, 2, angle_rx_buf, 2 );

    // Communication delay
    Delay_1us( );

    // read register
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, reg_rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    // Communication delay
    Delay_1us( );

    angle = angle_rx_buf[ 0 ];
    angle <<= 8;
    angle |= angle_rx_buf[ 1 ];
    angle >>= 4;

    *rsp = reg_rx_buf[ 0 ];

    return angle;
}

uint16_t angle5_write_register ( angle5_t *ctx, uint8_t reg_addr, uint8_t tx_data, uint8_t *status )
{
    uint8_t angle_rx_buf[ 2 ];
    uint8_t reg_rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t angle;

    tx_buf[ 0 ] = ANGLE5_CMD_WRITE | reg_addr;
    tx_buf[ 1 ] = tx_data;

    // send command and read angle
    angle5_generic_transfer( ctx, tx_buf, 2, angle_rx_buf, 2 );

    // Communication delay
    Delay_10ms();
    Delay_10ms();

    // read register
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, reg_rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    angle = angle_rx_buf[ 0 ];
    angle <<= 8;
    angle |= angle_rx_buf[ 1 ];
    angle >>= 4;

    if ( reg_rx_buf[ 0 ] == tx_data )
    {
        *status = 0;
    }
    else
    {
        *status = 1;
    }

    return angle;
}

float angle5_calc_rpm ( float old_angle, float new_angle )
{
    float angle;

    angle = old_angle - new_angle;
    if ( angle < 0 )
    {
        angle *= -1;
    }

    return ( angle * 0.16667 );
}

uint8_t angle5_get_mgh_pin_state( angle5_t *ctx )
{
    return digital_in_read( &ctx->mgh );
}

uint8_t angle5_get_mgl_pin_state( angle5_t *ctx )
{
    return digital_in_read( &ctx->mgl );
}

// ------------------------------------------------------------------------- END

