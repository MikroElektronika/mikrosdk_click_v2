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

#include "c3dhall.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C3DHALL_DUMMY 0

void c3dhall_cfg_setup ( c3dhall_cfg_t *cfg )
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

C3DHALL_RETVAL c3dhall_init ( c3dhall_t *ctx, c3dhall_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C3DHALL_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C3DHALL_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C3DHALL_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return C3DHALL_OK;
}

void c3dhall_generic_transfer ( c3dhall_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms();
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    Delay_1ms();
    spi_master_deselect_device( ctx->chip_select );   
}

void c3dhall_read_all_data ( c3dhall_t *ctx, c3dhall_all_data_t *all_data )
{
    uint8_t write_buffer_start[ 8 ];
    uint8_t buffer_read[ 8 ];
    
    write_buffer_start[ 0 ] = C3DHALL_START_COMMUNICATION_BYTE;
   
    c3dhall_generic_transfer( ctx, write_buffer_start, 1, buffer_read, 8 ); 

    all_data->data_angle_a = buffer_read[ 2 ];
    all_data->data_angle_a <<= 8;
    all_data->data_angle_a |= buffer_read[ 1 ];

    all_data->data_angle_b = buffer_read[ 4 ];
    all_data->data_angle_b <<= 8;
    all_data->data_angle_b |= buffer_read[ 3 ];

    all_data->data_error = buffer_read[ 6 ];
    all_data->data_error <<= 8;
    all_data->data_error |= buffer_read[ 5 ];

    all_data->data_sum = buffer_read[ 7 ];
}

uint8_t c3dhall_calculate_angle ( c3dhall_t *ctx, uint16_t data_angle )
{
    uint32_t temp;
    uint8_t result;

    temp = ( uint32_t ) data_angle;
    temp *= 180;
    temp /= 65535;
    
    result = ( uint8_t ) temp;
    
    return result;
}
// ------------------------------------------------------------------------- END

