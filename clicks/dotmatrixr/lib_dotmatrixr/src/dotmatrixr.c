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

#include "dotmatrixr.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DOTMATRIXR_DUMMY 0

static const uint8_t dev_ascii_matrix[ 98 ][ 6 ] =
{
    { '0', 0x3E, 0x51, 0x49, 0x45, 0x3E },//0
    { '1', 0x00, 0x42, 0x7F, 0x40, 0x00 },//1
    { '2', 0x62, 0x51, 0x49, 0x49, 0x46 },//2
    { '3', 0x22, 0x41, 0x49, 0x49, 0x36 },//3
    { '4', 0x18, 0x14, 0x12, 0x7F, 0x10 },//4
    { '5', 0x27, 0x45, 0x45, 0x45, 0x39 },//5
    { '6', 0x3C, 0x4A, 0x49, 0x49, 0x30 },//6
    { '7', 0x01, 0x71, 0x09, 0x05, 0x03 },//7
    { '8', 0x36, 0x49, 0x49, 0x49, 0x36 },//8
    { '9', 0x06, 0x49, 0x49, 0x29, 0x1E },//9

    { 'A', 0x7E, 0x09, 0x09, 0x09, 0x7E },//A   //i=10
    { 'B', 0x7E, 0x49, 0x49, 0x49, 0x36 },//B
    { 'C', 0x3E, 0x41, 0x41, 0x41, 0x22 },//C
    { 'D', 0x7F, 0x41, 0x41, 0x41, 0x3E },//D
    { 'E', 0x7F, 0x49, 0x49, 0x49, 0x41 },//E
    { 'F', 0x7F, 0x09, 0x09, 0x09, 0x01 },//F
    { 'G', 0x3E, 0x41, 0x41, 0x51, 0x32 },//G
    { 'H', 0x7F, 0x08, 0x08, 0x08, 0x7F },//H
    { 'I', 0x00, 0x41, 0x7F, 0x41, 0x00 },//I
    { 'J', 0x20, 0x40, 0x40, 0x40, 0x3F },//J
    { 'K', 0x7F, 0x08, 0x14, 0x22, 0x41 },//K
    { 'L', 0x7F, 0x40, 0x40, 0x40, 0x40 },//L
    { 'M', 0x7F, 0x08, 0x0C, 0x02, 0x7F },//M
    { 'N', 0x7F, 0x04, 0x08, 0x10, 0x7F },//N
    { 'O', 0x3E, 0x41, 0x41, 0x41, 0x3E },//O
    { 'P', 0x7F, 0x09, 0x09, 0x09, 0x06 },//P
    { 'Q', 0x3E, 0x41, 0x51, 0x21, 0x5E },//Q
    { 'R', 0x7F, 0x09, 0x19, 0x29, 0x46 },//R
    { 'S', 0x26, 0x49, 0x49, 0x49, 0x32 },//S
    { 'T', 0x01, 0x01, 0x7F, 0x01, 0x01 },//T
    { 'U', 0x3F, 0x40, 0x40, 0x40, 0x3F },//U
    { 'V', 0x07, 0x18, 0x60, 0x18, 0x07 },//V
    { 'W', 0x7F, 0x20, 0x18, 0x20, 0x7F },//W
    { 'X', 0x63, 0x14, 0x08, 0x14, 0x63 },//X
    { 'Y', 0x03, 0x04, 0x78, 0x04, 0x03 },//Y
    { 'Z', 0x61, 0x51, 0x49, 0x45, 0x43 },//Z   //i=35

    { 'a', 0x38, 0x44, 0x44, 0x3C, 0x40 },//a   //i=36
    { 'b', 0x7F, 0x48, 0x44, 0x44, 0x38 },//b
    { 'c', 0x38, 0x44, 0x44, 0x44, 0x44 },//c
    { 'd', 0x38, 0x44, 0x44, 0x48, 0x7F },//d
    { 'e', 0x38, 0x54, 0x54, 0x54, 0x08 },//e
    { 'f', 0x08, 0x7e, 0x09, 0x02, 0x00 },//f
    { 'g', 0x08, 0x14, 0x54, 0x54, 0x3C },//g
    { 'h', 0x7F, 0x08, 0x04, 0x04, 0x78 },//h
    { 'i', 0x00, 0x44, 0x7D, 0x40, 0x00 },//i
    { 'j', 0x20, 0x40, 0x44, 0x3D, 0x00 },//j
    { 'k', 0x00, 0x7F, 0x10, 0x28, 0x44 },//k
    { 'l', 0x00, 0x41, 0x7F, 0x40, 0x00 },//l
    { 'm', 0x78, 0x04, 0x18, 0x04, 0x78 },//m
    { 'n', 0x7C, 0x08, 0x04, 0x04, 0x78 },//n
    { 'o', 0x38, 0x44, 0x44, 0x44, 0x38 },//o
    { 'p', 0x7C, 0x14, 0x24, 0x24, 0x18 },//p
    { 'q', 0x18, 0x24, 0x14, 0x7C, 0x40 },//q
    { 'r', 0x00, 0x7C, 0x08, 0x04, 0x04 },//r
    { 's', 0x48, 0x54, 0x54, 0x54, 0x20 },//s
    { 't', 0x04, 0x3E, 0x44, 0x20, 0x00 },//t
    { 'u', 0x3C, 0x40, 0x40, 0x20, 0x7C },//u
    { 'v', 0x1C, 0x20, 0x40, 0x20, 0x1C },//v
    { 'w', 0x3C, 0x40, 0x30, 0x40, 0x3C },//w
    { 'x', 0x44, 0x28, 0x10, 0x28, 0x44 },//x
    { 'y', 0x04, 0x48, 0x30, 0x08, 0x04 },//y
    { 'z', 0x44, 0x64, 0x54, 0x4C, 0x44 },//z   //i=61

    { ' ', 0x00, 0x00, 0x00, 0x00, 0x00 },
    { '!', 0x00, 0x5F, 0x00, 0x00, 0x00 },
    { '"', 0x00, 0x03, 0x00, 0x03, 0x00 },
    { '#', 0x14, 0x7F, 0x14, 0x7F, 0x14 },
    { '$', 0x24, 0x2A, 0x7F, 0x2A, 0x12 },
    { '%', 0x23, 0x13, 0x08, 0x64, 0x62 },
    { '&', 0x36, 0x49, 0x56, 0x20, 0x50 },
    { '\'', 0x00, 0x0B, 0x07, 0x00, 0x00},
    { '(', 0x00, 0x00, 0x3E, 0x41, 0x00 },
    { ')', 0x00, 0x41, 0x3E, 0x00, 0x00 },
    { '*', 0x08, 0x2A, 0x1C, 0x2A, 0x08 },
    { '+', 0x08, 0x08, 0x3E, 0x08, 0x08 },
    { ',', 0x00, 0x58, 0x38, 0x00, 0x00 },
    { '-', 0x08, 0x08, 0x08, 0x08, 0x08 },
    { '.', 0x00, 0x30, 0x30, 0x00, 0x00 },
    { '/', 0x20, 0x10, 0x08, 0x04, 0x02 },
    { ':', 0x00, 0x36, 0x36, 0x00, 0x00 },
    { ';', 0x00, 0x5B, 0x3B, 0x00, 0x00 },
    { '<', 0x00, 0x08, 0x14, 0x22, 0x41 },
    { '=', 0x14, 0x14, 0x14, 0x14, 0x14 },
    { '>', 0x41, 0x22, 0x14, 0x08, 0x00 },
    { '?', 0x02, 0x01, 0x51, 0x09, 0x06 },
    { '@', 0x3E, 0x41, 0x5D, 0x55, 0x1E },
    { '{', 0x00, 0x08, 0x36, 0x41, 0x00 },
    { '|', 0x00, 0x00, 0x77, 0x00, 0x00 },
    { '}', 0x00, 0x41, 0x36, 0x08, 0x00 },
    { '~', 0x08, 0x04, 0x08, 0x10, 0x08 },
    { '[', 0x00, 0x00, 0x7F, 0x41, 0x41 },
    { '\\',0x02, 0x04, 0x08, 0x10, 0x20 },
    { ']', 0x41, 0x41, 0x7F, 0x00, 0x00 },
    { '-', 0x04, 0x02, 0x7F, 0x02, 0x04 },
    { '_', 0x40, 0x40, 0x40, 0x40, 0x40 }
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dotmatrixr_cfg_setup ( dotmatrixr_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rs = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->bl = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

DOTMATRIXR_RETVAL dotmatrixr_init ( dotmatrixr_t *ctx, dotmatrixr_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DOTMATRIXR_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DOTMATRIXR_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DOTMATRIXR_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rs, cfg->rs );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->bl, cfg->bl );

    return DOTMATRIXR_OK;
}

void dotmatrixr_generic_transfer ( dotmatrixr_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select ); 
}

void dotmatrixr_set_bl_pin_state ( dotmatrixr_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->bl, state );
}

void dotmatrixr_set_rs_pin_state ( dotmatrixr_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rs, state );
}

void dotmatrixr_set_rst_pin_state ( dotmatrixr_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void dotmatrixr_restart ( dotmatrixr_t *ctx )
{
    dotmatrixr_set_rst_pin_state( ctx, 0 );
    Delay_100ms(  );
    dotmatrixr_set_rst_pin_state( ctx, 1 );
}

void dotmatrixr_ctrl_0 ( dotmatrixr_t *ctx, uint8_t ctrl_byte )
{
    dotmatrixr_set_rs_pin_state( ctx, 1 );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &ctrl_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    dotmatrixr_set_rs_pin_state( ctx, 0 );
}

void dotmatrixr_ctrl_1 ( dotmatrixr_t *ctx, uint8_t ctrl_byte )
{
    dotmatrixr_set_rs_pin_state( ctx, 1 );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &ctrl_byte, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    dotmatrixr_set_rs_pin_state( ctx, 0 );
}

void dotmatrixr_write_ascii ( dotmatrixr_t *ctx, char *ascii_data )
{
    uint8_t text_len;
    uint8_t write_text[ 20 ] = { 0x00 };
    uint16_t matrix_cnt = 0;
    uint8_t display_cnt = 0;
    uint8_t ascii_cnt = 0;
    uint8_t write_text_cnt = 0;
    uint8_t flag_found = 0;
    
    text_len = strlen( ascii_data );
    
    if ( text_len >= 4 )
    {
       text_len = 4;
    }
    
    for ( display_cnt = 0; display_cnt < text_len; display_cnt++ )
    {
        for ( matrix_cnt = 0; matrix_cnt < 98; matrix_cnt++ )
        {
            if ( dev_ascii_matrix[ matrix_cnt ][ 0 ] == ascii_data[ display_cnt ] )
            {
                flag_found = 1;
                break;
            }
        }
        if ( 0 == flag_found )
        {
            matrix_cnt = 62;
        }
        for ( ascii_cnt = 1; ascii_cnt < 6; ascii_cnt++ )
        {
            write_text[ write_text_cnt ] = dev_ascii_matrix[ matrix_cnt ][ ascii_cnt ];
            write_text_cnt++;
        }
        flag_found = 0;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_text, 20 );
    spi_master_deselect_device( ctx->chip_select );  
}

// ------------------------------------------------------------------------- END

