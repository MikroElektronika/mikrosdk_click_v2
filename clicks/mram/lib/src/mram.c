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

#include "mram.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MRAM_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mram_cfg_setup ( mram_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MRAM_RETVAL mram_init ( mram_t *ctx, mram_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MRAM_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MRAM_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MRAM_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );

    return MRAM_OK;

}

void mram_default_cfg ( mram_t *ctx )
{
    mram_enable_hold_mode ( ctx, MRAM_LOGIC_HIGH );
    mram_enable_write ( ctx );
    mram_enable_write_protect ( ctx, MRAM_LOGIC_HIGH );
    mram_write_status_reg ( ctx, MRAM_NONE_PROTECTED_MEMORY );
}

void mram_generic_transfer 
( 
    mram_t *ctx, 
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

uint8_t mram_read_status_reg ( mram_t *ctx )
{
    uint8_t data_buffer[ 1 ] = {0};
    
    data_buffer[0] = 0x05;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &data_buffer[ 0 ], 1, &data_buffer[ 0 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return data_buffer[0];
}

uint8_t mram_check_status_bit ( mram_t *ctx, uint8_t status_bit )
{
    uint8_t status_data = 0;
    
    status_data = mram_read_status_reg( ctx );
    
    switch ( status_bit )
    {
        case 0x02 : 
        if ( status_data & 0x02 )
        {
            return 0x01;
            break;
        }
        else
        {
            return 0x00;
            break;
        }
                    
        case 0x04 : 
        if ( status_data & 0x04 )
        {
            return 0x01;
            break;
        } 
        else
        {
            return 0x00;
            break;
        }
                    
        case 0x08 : 
        if ( status_data & 0x08 )
        {
            return 0x01;
            break;
        }
        else
        {
            return 0x00;
            break;
        }
                    
        case 0x80 : 
        if ( status_data & 0x80 )
        {
            return 0x01;
            break;
        }
        else
        {
            return 0x00;
            break;
        }
    }
}

uint8_t mram_enable_write ( mram_t *ctx )
{
    uint8_t data_buffer[ 1 ] = {0};

    data_buffer[ 0 ] = 0x06;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[ 0 ], 1);
    spi_master_deselect_device( ctx->chip_select );

    return mram_check_status_bit( ctx, MRAM_WRITE_ENABLE_BIT );
}

uint8_t mram_disable_write ( mram_t *ctx)
{
    uint8_t data_buffer[ 1 ] = { 0 };

    data_buffer[ 0 ] = 0x04;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[ 0 ], 1 );
    spi_master_deselect_device( ctx->chip_select );

    return mram_check_status_bit ( ctx, MRAM_WRITE_ENABLE_BIT);
}

void mram_write_status_reg ( mram_t *ctx, uint8_t transfer_data )
{
    uint8_t data_buffer[2] = {0};

    data_buffer[0] = 0x01;
    data_buffer[1] = transfer_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[ 0 ], 1);
    spi_master_write( &ctx->spi, &data_buffer[ 1 ], 1);
    spi_master_deselect_device( ctx->chip_select );
}

void mram_read_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes )
{
    uint8_t write_buffer[3] = {0};
    uint16_t cnt;

    write_buffer[0] = 0x03;
    write_buffer[1] = ((address >> 8) & 0x007F);
    write_buffer[2] = address;
    
    mram_generic_transfer ( ctx, write_buffer, 3, buffer, n_bytes );
}

void mram_write_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes )
{
    uint8_t number_bytes = 0;
    uint8_t data_buffer[100] = {0};
    uint16_t i = 0;
    uint16_t bytes_number = 0;
    uint16_t cnt;
    
    number_bytes = n_bytes + 3;
    bytes_number = n_bytes;

    data_buffer[0] = 0x02;
    data_buffer[1] = ((address >> 8) & 0x007F);
    data_buffer[2] = address;    
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_buffer, 3 );
    spi_master_write( &ctx->spi, buffer, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

void mram_enter_sleep_mode ( mram_t *ctx )
{
    uint8_t data_buffer[1] = {0};

    data_buffer[0] = 0xB9;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[0], 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void mram_wake_up_mode ( mram_t *ctx )
{
    uint8_t data_buffer[1] = {0};

    data_buffer[0] = 0xAB;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[0], 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void mram_enable_write_protect ( mram_t *ctx, uint8_t state )
{
    if ( state )
    {
       digital_out_high( &ctx->wp ); 
    }
    else
    {
        digital_out_low( &ctx->wp );
    }
}

void mram_enable_hold_mode ( mram_t *ctx, uint8_t state )
{
    if ( state )
    {
       digital_out_high( &ctx->hld ); 
    }
    else
    {
        digital_out_low( &ctx->hld );
    }
}
// ------------------------------------------------------------------------- END

