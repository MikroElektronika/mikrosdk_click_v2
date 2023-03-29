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

#include "magneto2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MAGNETO2_DUMMY 0

#define MAGNETO2_ENABLE_FRAME_TRANSFER_START      0xAA
#define MAGNETO2_ENABLE_FRAME_TRANSFER_FOLLOWER   0xFF
#define MAGNETO2_MAX_16BIT_VALUE                  0xFFFF
#define MAGNETO2_ANGLE_COEFFICIENT                45.5

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto2_cfg_setup ( magneto2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MAGNETO2_RETVAL magneto2_init ( magneto2_t *ctx, magneto2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MAGNETO2_ENABLE_FRAME_TRANSFER_FOLLOWER;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MAGNETO2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MAGNETO2_ENABLE_FRAME_TRANSFER_FOLLOWER );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    return MAGNETO2_OK;

}

uint16_t magneto2_read_data ( magneto2_t *ctx )
{
    uint8_t check_value;
    uint16_t inverted_data_value;
    uint16_t data_value;

    uint8_t write_buffer_start[ 1 ];
    uint8_t write_buffer_follow[ 2 ];
    uint8_t data_value_buffer[ 2 ];
    uint8_t inverted_data_value_buffer[ 2 ];

    write_buffer_start[ 0 ] = MAGNETO2_ENABLE_FRAME_TRANSFER_START;
    write_buffer_follow[ 0 ] = MAGNETO2_ENABLE_FRAME_TRANSFER_FOLLOWER;
    write_buffer_follow[ 1 ] = MAGNETO2_ENABLE_FRAME_TRANSFER_FOLLOWER;

    spi_master_select_device( ctx->chip_select );
    Delay_5ms();
    spi_master_write( &ctx->spi, write_buffer_start, 1 );
    spi_master_write( &ctx->spi, write_buffer_follow, 1 );

    Delay_50us();
    spi_master_read( &ctx->spi, data_value_buffer, 2 );

    Delay_10us();

    spi_master_read( &ctx->spi, inverted_data_value_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
    data_value = data_value_buffer[ 1 ];
    data_value <<= 8;
    data_value |= data_value_buffer[ 0 ];

    check_value = data_value & 1;

    if ( check_value == 1 )
    {
        return -1;
    }
    
    inverted_data_value |= inverted_data_value_buffer[ 1 ];
    inverted_data_value <<= 8;
    inverted_data_value |= inverted_data_value_buffer[ 0 ];

    if ( data_value != inverted_data_value )
    {
        data_value >>= 2;
        return data_value;
    }
    else
    {
        return -1;
    }
}

float magneto2_read_angle ( magneto2_t* ctx )
{

    float angle;
    uint16_t data_value;

    data_value = magneto2_read_data( ctx );

    if ( data_value != MAGNETO2_MAX_16BIT_VALUE )
    {
        angle = (float)data_value;
        angle /= MAGNETO2_ANGLE_COEFFICIENT;

        return angle;
    }
    else
    {
        return -1;
    }
}

// ------------------------------------------------------------------------- END

