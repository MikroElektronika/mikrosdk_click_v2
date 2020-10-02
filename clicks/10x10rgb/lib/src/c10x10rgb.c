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

#include "c10x10rgb.h"
#include "c10x10rgb_ascii_matrix.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void drv_show_screen ( c10x10rgb_t *ctx, uint32_t *screen_matrix );

static void drv_memset ( void * p1, char character, int n );

static void drv_matrix_add_scroll_buf
( 
    drv_scroll_buf_t *scroll_buf_obj, 
    c10x10rgb_byte_t *data_array,
    uint8_t demo_array_len 
);

static void drv_matrix_image_update ( uint32_t *matrix, drv_update_line_t *data_obj );

static void drv_show_delay ( uint16_t wait_ms );

static uint32_t drv_color_wheel ( uint8_t wheel_pos, uint8_t brightness );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c10x10rgb_cfg_setup ( c10x10rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one )
{
    // Additional gpio pins

    cfg->di_pin = HAL_PIN_NC;
    cfg->do_pin = HAL_PIN_NC;

    cfg->logic_zero = logic_zero;
    cfg->logic_one = logic_one;
}

c10X10RGB_RETVAL c10x10rgb_init ( c10x10rgb_t *ctx, c10x10rgb_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->di_pin, cfg->di_pin );

    // Input pins

    digital_in_init( &ctx->do_pin, cfg->do_pin );

    // Function pointers 

    ctx->logic_zero = cfg->logic_zero;
    ctx->logic_one = cfg->logic_one;

    digital_out_low( &ctx->di_pin );

    return c10X10RGB_OK;
}

void c10x10rgb_write_data ( c10x10rgb_t *ctx, uint32_t w_data ) 
{
    int8_t cnt;
    uint32_t tmp = LOGIC_ONE;

    for ( cnt = NUM_DATA_BITS; cnt >= 0; cnt-- )
    {
        if ( ( ( w_data ) & ( tmp << cnt ) ) == 0 )
        {
            ctx->logic_zero( );
        }
        else
        {
            ctx->logic_one( );
        }
    }
}

void c10x10rgb_fill_screen ( c10x10rgb_t *ctx, uint32_t screen_color ) 
{
    uint8_t cnt;

    for ( cnt = 0; cnt < NUM_MATRIX_BYTE; cnt++ )
    {
        c10x10rgb_write_data( ctx, screen_color );
    }
}

uint32_t c10x10rgb_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness ) 
{
    uint32_t color;

    if ( brightness != 0 )
    {
         color = ( green * brightness ) >> 8;
         color <<= 8;
         color |= ( red * brightness ) >> 8;
         color <<= 8;
         color |= ( blue * brightness ) >> 8;
    }
    else
    {
        color = green;
        color <<= 8;
        color |= red;
        color <<= 8;
        color |= blue;
    }

    return color;
}

void c10x10rgb_display_image ( c10x10rgb_t *ctx, uint32_t *demo_image ) 
{
    drv_show_screen( ctx, demo_image );
}

void c10x10rgb_display_byte ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj ) 
{
    uint8_t cnt;
    uint8_t cnt_bit;
    uint8_t tmp_data;
    uint32_t matrix[ NUM_MATRIX_BYTE ] = { 0 };

    drv_memset( matrix, 0, NUM_MATRIX_BYTE );

    for( cnt = 0; cnt < 10; cnt++ )
    {
        tmp_data = ascii_matrix[ data_obj->data_byte - 32 ][ SELECT_INV_BYTE_POS(
                 data_obj->rotate, cnt ) ];
        for ( cnt_bit = 0; cnt_bit < 8; cnt_bit++ )
        {
            if ( ( tmp_data >> SELECT_INVERT( ( data_obj->rotate & 0x01 ),
                 cnt_bit ) ) & 0x01 != 0 )
            {
                matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ),
                     cnt, cnt_bit ) ] = data_obj->color;
            }
            else
            {
                matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ),
                     cnt, cnt_bit ) ] = data_obj->bg_color;
                matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ),
                     cnt, 8 ) ] = data_obj->bg_color;
                matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ),
                     cnt, 9 ) ] = data_obj->bg_color;
            }
        }
    }

    drv_show_screen( ctx, matrix );
}

void c10x10rgb_display_string ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj, 
    uint8_t len, uint16_t speed_ms ) 
{
    uint16_t cnt_byte;
    uint8_t cnt;
    uint32_t matrix[ NUM_MATRIX_BYTE ] = { 0 };
    
    drv_update_line_t line_data_obj;
    drv_scroll_buf_t  scroll_buf_obj;

    drv_memset( scroll_buf_obj.buffer, 0, NUX_MAX_CHAR * 10 );
    drv_matrix_add_scroll_buf( &scroll_buf_obj, data_obj, len );

    for ( cnt_byte = 0; cnt_byte < scroll_buf_obj.len; cnt_byte++ )
    {
        drv_memset( matrix, 0, NUM_MATRIX_BYTE );
        for( cnt = 0; cnt < 10; cnt++ )
        {
            line_data_obj.new_data = scroll_buf_obj.buffer[ cnt_byte + cnt ].data_byte;
            line_data_obj.rotate = scroll_buf_obj.buffer[ cnt_byte + cnt ].rotate;
            line_data_obj.line_pos = cnt;
            line_data_obj.color = scroll_buf_obj.buffer[ cnt_byte + cnt ].color;
            line_data_obj.bg_color = scroll_buf_obj.buffer[ cnt_byte + cnt ].bg_color;

            drv_matrix_image_update( matrix, &line_data_obj );
        }
        drv_show_screen( ctx, matrix );
        drv_show_delay( speed_ms );
    }
}

void c10x10rgb_demo_rainbow ( c10x10rgb_t *ctx, uint8_t brightness, uint16_t speed_ms ) 
{
    uint16_t pix_cnt;
    uint16_t color_cnt;
    uint32_t matrix[ NUM_MATRIX_BYTE ];
    
    for ( color_cnt = 0; color_cnt < 1275; color_cnt++ )
    {
        for ( pix_cnt = 0; pix_cnt < NUM_MATRIX_BYTE; pix_cnt++ )
        {
            matrix[ pix_cnt ] = drv_color_wheel( ( pix_cnt + color_cnt ) & 255, brightness );
        }

       drv_show_screen( ctx, matrix );
       drv_show_delay( speed_ms );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_show_screen ( c10x10rgb_t *ctx, uint32_t *screen_matrix )
{
    uint8_t cnt;
    
    for ( cnt = 0; cnt < NUM_MATRIX_BYTE; cnt++ )
    {
        c10x10rgb_write_data( ctx, screen_matrix[ cnt ] );
    }
}

static void drv_memset ( void * p1, char character, int n ) 
{
    char * pp;

    pp = p1;

    while( n-- )
    {
        *pp++ = character;
    }
}

static void drv_matrix_add_scroll_buf ( drv_scroll_buf_t *scroll_buf_obj,
     c10x10rgb_byte_t *data_array, uint8_t data_len )
{
    uint16_t cnt_char;
    uint8_t cnt_byte;
    uint16_t scroll_buf_len = 0;
    uint16_t buffer_element;
    
    // add space
    for( cnt_byte = 0; cnt_byte < 10; cnt_byte++ )
    {
        buffer_element = ( ++scroll_buf_len ) - 1;
        scroll_buf_obj->buffer[ buffer_element ].data_byte = ascii_matrix[ 0 ][ cnt_byte ];
        scroll_buf_obj->buffer[ buffer_element ].color = COLOR_DEFAULT;
        scroll_buf_obj->buffer[ buffer_element ].bg_color = BG_COLOR_DEFAULT;
        scroll_buf_obj->buffer[ buffer_element ].rotate = ROTATE_DEFAULT;
    }
    // add string
    for ( cnt_char = 0; cnt_char < data_len; cnt_char++ )
    {
        for ( cnt_byte = 0; cnt_byte < 10; cnt_byte++ )
        {
            buffer_element = ( ++scroll_buf_len ) - 1;
            scroll_buf_obj->buffer[ buffer_element ].data_byte = 
                ascii_matrix[ data_array[ cnt_char ]->data_byte - 32 ][ cnt_byte ];
            scroll_buf_obj->buffer[ buffer_element ].color = 
                data_array[ cnt_char ]->color;
            scroll_buf_obj->buffer[ buffer_element ].bg_color = 
                data_array[ cnt_char ]->bg_color;
            scroll_buf_obj->buffer[ buffer_element ].rotate = 
                data_array[ cnt_char ]->rotate;
        }
    }
    // add space
    for( cnt_byte = 0; cnt_byte < 10; cnt_byte++ )
    {
        buffer_element = ( ++scroll_buf_len ) - 1 ;
        scroll_buf_obj->buffer[ buffer_element ].data_byte = ascii_matrix[ 0 ][ cnt_byte ];
        scroll_buf_obj->buffer[ buffer_element ].color = COLOR_DEFAULT;
        scroll_buf_obj->buffer[ buffer_element ].bg_color = BG_COLOR_DEFAULT;
        scroll_buf_obj->buffer[ buffer_element ].rotate = ROTATE_DEFAULT;
    }
    scroll_buf_len--;

    buffer_element = scroll_buf_len++;
    scroll_buf_obj->buffer[ buffer_element ].data_byte = 0x00;
    scroll_buf_obj->buffer[ buffer_element ].color = COLOR_DEFAULT;
    scroll_buf_obj->buffer[ buffer_element ].bg_color = BG_COLOR_DEFAULT;
    scroll_buf_obj->buffer[ buffer_element ].rotate = ROTATE_DEFAULT;
    
    buffer_element = scroll_buf_len;
    scroll_buf_obj->buffer[ buffer_element ].data_byte = 0x00;
    scroll_buf_obj->buffer[ buffer_element ].color = COLOR_DEFAULT;
    scroll_buf_obj->buffer[ buffer_element ].bg_color = BG_COLOR_DEFAULT;
    scroll_buf_obj->buffer[ buffer_element ].rotate = ROTATE_DEFAULT;
    scroll_buf_obj->len = scroll_buf_len - 10;
}

static void drv_matrix_image_update ( uint32_t *matrix, drv_update_line_t *data_obj )
{
    uint8_t cnt_bit;

    for ( cnt_bit = 0; cnt_bit < 8; cnt_bit++ )
    {
         if ( ( data_obj->new_data >> SELECT_INVERT( (data_obj->rotate & 0x01),
             cnt_bit) ) & 0x01 != 0 )
         {
             matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ), 
                data_obj->line_pos, cnt_bit ) ] = data_obj->color;
         }
         else
         {
             matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ), 
                data_obj->line_pos, cnt_bit ) ] = data_obj->bg_color;
             matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ), 
                data_obj->line_pos, 8 ) ] = data_obj->bg_color;
             matrix[ SELECT_ROTATE( ( data_obj->rotate & 0x10 ), 
                data_obj->line_pos, 9 ) ] = data_obj->bg_color;
         }
    }
} 

static void drv_show_delay ( uint16_t wait_ms )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < wait_ms; cnt++ )
    {
        Delay_1ms();
    }
}

static uint32_t drv_color_wheel ( uint8_t wheel_pos, uint8_t brightness )
{
    wheel_pos = 255 - wheel_pos;

    if ( wheel_pos < 85 )
    {
        return c10x10rgb_make_color( 0,  255 - wheel_pos * 3, wheel_pos * 3, brightness );
    }
    if ( wheel_pos < 170 )
    {
        wheel_pos -= 85;

        return c10x10rgb_make_color( wheel_pos * 3, 0, 255 - wheel_pos * 3, brightness );
    }

    wheel_pos -= 170;
    return c10x10rgb_make_color( 255 - wheel_pos * 3, wheel_pos * 3, 0, brightness );
}

// ------------------------------------------------------------------------- END

