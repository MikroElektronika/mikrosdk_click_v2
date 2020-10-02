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

#include <string.h>
#include "c7x10.h"
#include "c7x10_font.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C7X10_DUMMY 0

#define C7X10_FRAME_BUFFER_LEN 14
#define C7X10_MAX_ROW 7
#define C7X10_MAX_COL 10

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void latch( c7x10_t *ctx );
static void row_reset( c7x10_t *ctx );
static void row_clock( c7x10_t *ctx );
static void module_reset( c7x10_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c7x10_cfg_setup ( c7x10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rc = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rr = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

C7X10_RETVAL c7x10_init ( c7x10_t *ctx, c7x10_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C7X10_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C7X10_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C7X10_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rc, cfg->rc );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rr, cfg->rr );

    return C7X10_OK;
}

void c7x10_generic_write ( c7x10_t *ctx,  uint8_t data_in )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void c7x10_display_process ( c7x10_t *ctx, uint8_t *frame, uint16_t disp_delay )
{
    uint8_t cnt;
    uint8_t i;

    for ( cnt = 0; cnt < disp_delay; cnt++ )
    {
        module_reset( ctx );
        row_reset( ctx );

        for ( i = 0; i < C7X10_MAX_ROW; i++ )
        {
            c7x10_generic_write( ctx, frame[ i * 2 ] );
            c7x10_generic_write( ctx, frame[ ( i * 2 ) + 1 ] );
            latch( ctx );
            row_clock( ctx );
        }
        Delay_1ms();
    }
}

void c7x10_draw_pixel( c7x10_t *ctx, c7x10_pixel_t *pixel, uint8_t mode, uint8_t px_delay )
{
    static uint8_t frame[ C7X10_FRAME_BUFFER_LEN ];

    if ( ( pixel->cord_x > C7X10_MAX_ROW ) || ( pixel->cord_y > C7X10_MAX_COL ) ||
         ( pixel->cord_x == 0 ) || ( pixel->cord_y == 0 ) )
    {
        return;
    }

    if ( 6 > pixel->cord_y )
    {
        frame[ ( pixel->cord_x - 1 ) * 2 + 1 ] |= 0x01 << ( pixel->cord_y - 1 );
    }
    else
    {
        frame[ ( pixel->cord_x - 1 ) * 2 ] |= 0x01 << ( pixel->cord_y - 6 );
    }

    if ( mode == C7X10_DISPLAY_PIXEL_REFRESH )
    {
        c7x10_display_process(ctx, frame, px_delay);
        memset( frame, 0, C7X10_FRAME_BUFFER_LEN );
    }
}

void c7x10_draw_char ( c7x10_t *ctx, char ch, uint8_t mode, uint8_t ch_delay )
{
    const uint8_t *p_font = c7x10_font;
    uint8_t cnt;
    static uint8_t frame[ C7X10_FRAME_BUFFER_LEN ];

    p_font = &c7x10_font[ ch * 8 ];

    if ( ( mode & C7X10_DISPLAY_RIGHT ) == 1 )
    {
        for ( cnt = 0; cnt < C7X10_FRAME_BUFFER_LEN; cnt += 2 )
        {
            frame[ cnt ] = *( p_font++ );
        }
    }
    else
    {
        for ( cnt = 1; cnt <= C7X10_FRAME_BUFFER_LEN; cnt += 2 )
        {
            frame[ cnt ] = *( p_font++ );
        }
    }

    if ( ( mode & C7X10_DISPLAY_REFRESH ) != 0 )
    {
        c7x10_display_process( ctx, frame, ch_delay );
        memset( frame, 0, C7X10_FRAME_BUFFER_LEN );
    }
}


void c7x10_draw_number ( c7x10_t *ctx, uint8_t num, uint16_t num_delay)
{
    uint8_t const *p_font = c7x10_font;
    uint16_t cnt;
    uint8_t tmp_num;
    uint8_t frame[ C7X10_FRAME_BUFFER_LEN ];

    memset( frame, 0, C7X10_FRAME_BUFFER_LEN );

    if ( 99 < num )
    {
        return;
    }

    if ( 10 > num )
    {
        p_font = &c7x10_font[ ( num + 48 ) * 8 ];

        for ( cnt = 0; cnt < C7X10_FRAME_BUFFER_LEN; cnt += 2 )
        {
            frame[ cnt ] = *( p_font++ );
        }
    }
    else
    {
        tmp_num = num / 10;
        p_font = &c7x10_font[ ( tmp_num + 48 ) * 8 ];

        for ( cnt = 1; cnt <= C7X10_FRAME_BUFFER_LEN; cnt += 2 )
        {
            frame[ cnt ] = *( p_font++ );
        }

        tmp_num = num % 10;
        p_font = &c7x10_font[ ( tmp_num + 48 ) * 8 ];

        for ( cnt = 0; cnt < C7X10_FRAME_BUFFER_LEN; cnt += 2 )
        {
            frame[ cnt ] = *( p_font++ );
        }
    }

    c7x10_display_process( ctx, frame, num_delay );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void latch ( c7x10_t *ctx )
{
    // cs pin
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );
}

static void row_reset ( c7x10_t *ctx )
{
    // pwm pin
    digital_out_high( &ctx->rr );
    Delay_1us( );
    digital_out_low( &ctx->rr );
}

static void row_clock ( c7x10_t *ctx )
{
    // an pin
    digital_out_high( &ctx->rc );
    Delay_1us( );
    digital_out_low( &ctx->rc );
}

static void module_reset ( c7x10_t *ctx )
{
    // rst pin
    digital_out_low( &ctx->rst );
    Delay_1us( );
    digital_out_high( &ctx->rst );
}

// ------------------------------------------------------------------------- END

