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

#include "scanner.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void scanner_cfg_setup ( scanner_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
}

SCANNER_RETVAL scanner_init ( scanner_t *ctx, scanner_cfg_t *cfg )
{
    // Output pins 
    
    digital_out_init( &ctx->mosi, cfg->mosi );
    digital_out_init( &ctx->sck, cfg->sck );

    // Input pins

    digital_in_init( &ctx->miso, cfg->miso );

    digital_out_low( &ctx->mosi );
    digital_out_low( &ctx->sck );

    return SCANNER_OK;
}

void scanner_set_sdi ( scanner_t *ctx, uint8_t sdi_mode )
{
    digital_out_write( &ctx->mosi, sdi_mode );
}

uint8_t scanner_get_sdo ( scanner_t *ctx )
{
    return digital_in_read( &ctx->miso );
}

void scanner_clock ( scanner_t *ctx )
{
    Delay_1us( );
    digital_out_high( &ctx->sck );
    Delay_1us( );
    digital_out_low( &ctx->sck );
}

void scanner_serial_cmd ( scanner_t *ctx, uint8_t cmd )
{
    uint8_t clk_cnt;

    scanner_set_sdi( ctx, 0 );
    scanner_clock( ctx );

    for ( clk_cnt = 0; clk_cnt < 8; clk_cnt++ )
    {
        scanner_set_sdi( ctx, ( cmd >> clk_cnt ) & 0x01 );
        scanner_clock( ctx );
    }

    scanner_set_sdi( ctx, 1 );
    scanner_clock( ctx );

    for ( clk_cnt = 0; clk_cnt < 5; clk_cnt++ )
    {
        scanner_clock( ctx );
    }
}

uint8_t scanner_serial_read_reg ( scanner_t *ctx, uint8_t reg_adr )
{
    uint8_t clk_cnt;
    uint8_t temp_data = 0x00;
    uint8_t sdo_data;

    scanner_serial_cmd( ctx, SCANNER_CMD_REGREAD | reg_adr );
    
    switch ( reg_adr )
    {
        case SCANNER_REG_GAIN_CENTER:
        case SCANNER_REG_GAIN_LEFT:
        case SCANNER_REG_GAIN_RIGHT:
        {
            for ( clk_cnt = 0; clk_cnt < 5; clk_cnt++ )
            {
                scanner_clock( ctx );
                sdo_data = scanner_get_sdo( ctx );
                temp_data |= sdo_data << clk_cnt;
            }
            return temp_data;
        }
        case SCANNER_REG_OFFSET_CENTER:
        case SCANNER_REG_OFFSET_LEFT:
        case SCANNER_REG_OFFSET_RIGHT:
        case SCANNER_REG_MODE:
        {
            for ( clk_cnt = 0; clk_cnt < 8; clk_cnt++ )
            {
                scanner_clock( ctx );
                sdo_data = scanner_get_sdo( ctx );
                temp_data |= sdo_data << clk_cnt;
            }
            return temp_data;
        }
        default:
        {
            return 0x00;
        }
    }
}

void scanner_serial_write_reg ( scanner_t *ctx, uint8_t reg_adr, uint8_t write_data )
{
    uint8_t clk_cnt;

    scanner_serial_cmd( ctx, SCANNER_CMD_REGWRITE | reg_adr );
    
    switch ( reg_adr )
    {
        case SCANNER_REG_GAIN_CENTER:
        case SCANNER_REG_GAIN_LEFT:
        case SCANNER_REG_GAIN_RIGHT:
        {
            for ( clk_cnt = 0; clk_cnt < 5; clk_cnt++ )
            {
                scanner_set_sdi( ctx, ( write_data >> clk_cnt ) & 0x01 );
                scanner_clock( ctx );
            }
        }
        case SCANNER_REG_OFFSET_CENTER:
        case SCANNER_REG_OFFSET_LEFT:
        case SCANNER_REG_OFFSET_RIGHT:
        case SCANNER_REG_MODE:
        {
            for ( clk_cnt = 0; clk_cnt < 8; clk_cnt++ )
            {
                scanner_set_sdi( ctx, ( write_data >> clk_cnt ) & 0x01 );
                scanner_clock( ctx );
            }
        }
        default:
        {
            return;
        }
    }
}

void scanner_startup ( scanner_t *ctx )
{
    uint8_t clk_cnt;
    
    for ( clk_cnt = 0; clk_cnt < 10; clk_cnt++ )
    {
        scanner_clock( ctx );
    }

    scanner_serial_cmd( ctx, SCANNER_CMD_RESET );
    scanner_serial_cmd( ctx, SCANNER_CMD_RESET );
    scanner_serial_cmd( ctx, SCANNER_CMD_RESET );

    for ( clk_cnt = 0; clk_cnt < 30; clk_cnt++ )
    {
        scanner_clock( ctx );
    }
}

void scanner_read_pixel ( scanner_t *ctx, uint8_t *pixel_data )
{
    uint8_t clk_cnt;
    uint8_t clk_data;
    uint8_t temp_data;
    uint8_t sdo_data;

    scanner_serial_cmd( ctx, SCANNER_CMD_STARTINT );
    for ( clk_cnt = 0; clk_cnt < 22; clk_cnt++ )
    {
        scanner_clock( ctx );
    }
    
    scanner_serial_cmd( ctx, SCANNER_CMD_SAMPLEINT );
    scanner_serial_cmd( ctx, SCANNER_CMD_READPIXEL );
    
    for ( clk_cnt = 0; clk_cnt < 40; clk_cnt++ )
    {
        scanner_clock( ctx );
    }
    
    for ( clk_cnt = 0; clk_cnt < 102; clk_cnt++ )
    {
        temp_data = 0x00;
        for ( clk_data = 0; clk_data < 10; clk_data++ )
        {
            if ( ( clk_data != 0 ) || ( clk_data != 9 ) )
            {
                sdo_data = scanner_get_sdo( ctx );
                temp_data |= sdo_data << clk_data;
            }
            scanner_clock( ctx );
        }
        *pixel_data = temp_data;
        pixel_data++;
    }

    Delay_100ms( );
    scanner_serial_cmd( ctx, SCANNER_CMD_RESET );
}

// ------------------------------------------------------------------------- END

