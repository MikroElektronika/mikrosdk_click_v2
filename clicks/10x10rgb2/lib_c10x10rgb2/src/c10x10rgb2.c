/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file c10x10rgb2.c
 * @brief 10x10 RGB 2 Click Driver.
 */

#include "c10x10rgb2.h"
#include "c10x10rgb2_resources.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief 10x10 RGB 2 invert bit pos function.
 * @details This function inverts bits position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - Normal,
 *                       @li @c 0x01 - Vertical 180 - XY mirrored,
 *                       @li @c 0x10 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 0x11 - Horizontal 180 - XY exchanged, Y mirrored.
 * @param[in] data_in : Bits position input to invert (up to 7).
 * @return Output bits position.
 * @note None.
 */
static uint8_t c10x10rgb2_invert_bit_pos ( uint8_t rotation, uint8_t data_in );

/**
 * @brief 10x10 RGB 2 invert byte pos function.
 * @details This function inverts bytes position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - Normal,
 *                       @li @c 0x01 - Vertical 180 - XY mirrored,
 *                       @li @c 0x10 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 0x11 - Horizontal 180 - XY exchanged, Y mirrored.
 * @param[in] data_in : Bytes position input to invert (up to 9).
 * @return Output bytes position.
 * @note None.
 */
static uint8_t c10x10rgb2_invert_byte_pos ( uint8_t rotation, uint8_t data_in );

/**
 * @brief 10x10 RGB 2 get led num function.
 * @details This function returns the LED number for X and Y position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - Normal,
 *                       @li @c 0x01 - Vertical 180 - XY mirrored,
 *                       @li @c 0x10 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 0x11 - Horizontal 180 - XY exchanged, Y mirrored.
 * @param[in] x_pos : X position for LED (up to 9).
 * @param[in] y_pos : Y position for LED (up to 9).
 * @return LED number.
 * @note None.
 */
static uint8_t c10x10rgb2_get_led_num ( uint8_t rotation, uint8_t x_pos, uint8_t y_pos );

/**
 * @brief 10x10 RGB 2 write char buf function.
 * @details This function writes the selected 8x10 char buffer to display.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] data_in : 10 bytes data buffer to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c10x10rgb2_write_char_buf ( c10x10rgb2_t *ctx, uint8_t *data_in );

void c10x10rgb2_cfg_setup ( c10x10rgb2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t c10x10rgb2_init ( c10x10rgb2_t *ctx, c10x10rgb2_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    return SPI_MASTER_SUCCESS;
}

err_t c10x10rgb2_default_cfg ( c10x10rgb2_t *ctx ) 
{
    c10x10rgb2_set_leds_brightness ( ctx, C10X10RGB2_LED_BRIGHTNESS_DEFAULT );
    c10x10rgb2_set_pen ( ctx, C10X10RGB2_COLOR_RED, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    return c10x10rgb2_fill_screen ( ctx, C10X10RGB2_COLOR_BLACK );
}

err_t c10x10rgb2_write_leds ( c10x10rgb2_t *ctx, c10x10rgb2_led_t *leds, uint16_t num_leds )
{
    if ( num_leds > C10X10RGB2_NUM_LEDS )
    {
        return C10X10RGB2_ERROR;
    }
    uint8_t data_buf[ C10X10RGB2_NUM_LEDS * 4 + 12 ] = { 0 };
    memset ( &data_buf[ 0 ], C10X10RGB2_FRAME_START, 4 );
    for ( uint16_t led_cnt = C10X10RGB2_LED_0; led_cnt < num_leds; led_cnt++ )
    {
        data_buf[ 4 + led_cnt * 4 ] = C10X10RGB2_LED_BRIGHTNESS_MASK | leds[ led_cnt ].brightness;
        data_buf[ 5 + led_cnt * 4 ] = leds[ led_cnt ].blue;
        data_buf[ 6 + led_cnt * 4 ] = leds[ led_cnt ].green;
        data_buf[ 7 + led_cnt * 4 ] = leds[ led_cnt ].red;
    }
    memset ( &data_buf[ 4 + num_leds * 4 ], C10X10RGB2_FRAME_END, 8 );
    return spi_master_write( &ctx->spi, data_buf, 12 + num_leds * 4 );
}

err_t c10x10rgb2_write_led_matrix ( c10x10rgb2_t *ctx )
{
    return c10x10rgb2_write_leds ( ctx, ctx->led_matrix, C10X10RGB2_NUM_LEDS );
}

void c10x10rgb2_set_led_brightness ( c10x10rgb2_t *ctx, uint16_t led_num, uint8_t brightness )
{
    ctx->led_matrix[ led_num % C10X10RGB2_NUM_LEDS ].brightness = brightness % ( C10X10RGB2_LED_BRIGHTNESS_MAX + 1 );
}

void c10x10rgb2_set_leds_brightness ( c10x10rgb2_t *ctx, uint8_t brightness )
{
    for ( uint16_t led_cnt = C10X10RGB2_LED_0; led_cnt < C10X10RGB2_NUM_LEDS; led_cnt++ )
    {
        c10x10rgb2_set_led_brightness ( ctx, led_cnt, brightness );
    }
}

void c10x10rgb2_set_led_color ( c10x10rgb2_t *ctx, uint16_t led_num, uint32_t rgb )
{
    ctx->led_matrix[ led_num % C10X10RGB2_NUM_LEDS ].red = ( uint8_t ) ( ( rgb >> 16 ) & 0xFF );
    ctx->led_matrix[ led_num % C10X10RGB2_NUM_LEDS ].green = ( uint8_t ) ( ( rgb >> 8 ) & 0xFF );
    ctx->led_matrix[ led_num % C10X10RGB2_NUM_LEDS ].blue = ( uint8_t ) ( rgb & 0xFF );
}

void c10x10rgb2_set_leds_color ( c10x10rgb2_t *ctx, uint32_t rgb )
{
    for ( uint16_t led_cnt = C10X10RGB2_LED_0; led_cnt < C10X10RGB2_NUM_LEDS; led_cnt++ )
    {
        c10x10rgb2_set_led_color ( ctx, led_cnt, rgb );
    }
}

uint32_t c10x10rgb2_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t rgb_pct )
{
    uint32_t rgb = 0;
    uint8_t rgb_max_pct = rgb_pct;
    // RGB percent maximal value is 100
    if ( rgb_max_pct > 100 )
    {
        rgb_max_pct = 100;
    }
    rgb = ( ( uint16_t ) green * rgb_max_pct ) / 100;
    rgb <<= 8;
    rgb |= ( ( uint16_t ) red * rgb_max_pct ) / 100;
    rgb <<= 8;
    rgb |= ( ( uint16_t ) blue * rgb_max_pct ) / 100;
    return rgb;
}

uint32_t c10x10rgb2_color_wheel ( uint8_t wheel_pos, uint8_t rgb_pct )
{
    uint32_t rgb = 0;
    uint8_t w_pos = wheel_pos;
    // RGB wheel color picker
    if ( w_pos < 85 )
    {
        rgb = c10x10rgb2_make_color( w_pos * 3, 255 - w_pos * 3, 0, rgb_pct );
    }
    else if ( w_pos < 170 )
    {
        w_pos -= 85;
        rgb = c10x10rgb2_make_color( 255 - w_pos * 3, 0, w_pos * 3, rgb_pct );
    }
    else
    {
        w_pos -= 170;
        rgb = c10x10rgb2_make_color( 0, w_pos * 3, 255 - w_pos * 3, rgb_pct );
    }
    return rgb;
}

err_t c10x10rgb2_fill_screen ( c10x10rgb2_t *ctx, uint32_t rgb )
{
    c10x10rgb2_set_leds_color ( ctx, rgb );
    return c10x10rgb2_write_led_matrix ( ctx );
}

void c10x10rgb2_set_pen ( c10x10rgb2_t *ctx, uint32_t txt_rgb, uint32_t bg_rgb, uint8_t rotation )
{
    ctx->pen.txt_rgb = txt_rgb;
    ctx->pen.bg_rgb = bg_rgb;
    ctx->pen.rotation = rotation;
}

err_t c10x10rgb2_write_char ( c10x10rgb2_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 10 ] = { 0 };
    // 2 lines offset for char writing
    memcpy ( &data_buf[ 2 ], &c10x10rgb_font_8x8[ data_in - 32 ][ 0 ], 8 );
    return c10x10rgb2_write_char_buf ( ctx, data_buf );
}

err_t c10x10rgb2_write_string ( c10x10rgb2_t *ctx, uint8_t *data_in, uint16_t speed_ms )
{
    err_t error_flag = C10X10RGB2_OK;
    uint8_t data_buf[ 18 ] = { 0 };
    uint8_t char_cnt = 0;
    uint8_t line_cnt = 0;
    uint8_t delay_cnt = 0;
    for ( char_cnt = 0; char_cnt < ( strlen( data_in ) ); char_cnt++ )
    {
        // Retrieve an 8 bytes array for selected ASCII from font matrix
        // 10 bytes offset in the beginning for blanko screen
        memcpy ( &data_buf[ 10 ], &c10x10rgb_font_8x8[ data_in[ char_cnt ] - 32 ][ 0 ], 8 );
        for ( line_cnt = 0; line_cnt < 8; line_cnt++ )
        {
            // Writes char buffer scrolling it the left side
            error_flag |= c10x10rgb2_write_char_buf ( ctx, data_buf );
            memmove ( &data_buf[ 0 ], &data_buf[ 1 ], sizeof ( data_buf ) - 1 );
            for ( delay_cnt = 0; delay_cnt < speed_ms; delay_cnt++ )
            {
                Delay_1ms ( );
            }
        }
    }
    for ( line_cnt = 0; line_cnt < 10; line_cnt++ )
    {
        // Scroll the rest of the ASCII char lines out of the screen 
        error_flag |= c10x10rgb2_write_char_buf ( ctx, data_buf );
        memmove ( &data_buf[ 0 ], &data_buf[ 1 ], sizeof ( data_buf ) - 1 );
        for ( uint16_t cnt_delay = 0; cnt_delay < speed_ms; cnt_delay++ )
        {
            Delay_1ms ( );
        }
    }
    return error_flag;
}

err_t c10x10rgb2_draw_picture ( c10x10rgb2_t *ctx, const uint32_t *demo_image )
{
    for ( uint16_t led_cnt = C10X10RGB2_LED_0; led_cnt < C10X10RGB2_NUM_LEDS; led_cnt++ )
    {
        c10x10rgb2_set_led_color ( ctx, led_cnt, demo_image[ led_cnt ] );
    }
    return c10x10rgb2_write_led_matrix ( ctx );
}

err_t c10x10rgb2_demo_rainbow ( c10x10rgb2_t *ctx, uint8_t rgb_pct, uint16_t upd_rate_ms, uint16_t upd_num )
{
    err_t error_flag = C10X10RGB2_OK;
    uint16_t led_cnt = 0;
    uint16_t upd_cnt = 0;
    uint16_t upd_rate_cnt = 0;
    
    for ( upd_cnt = 0; ( upd_cnt < upd_num ) && ( C10X10RGB2_OK == error_flag ); upd_cnt++ )
    {
        for ( led_cnt = 0; led_cnt < C10X10RGB2_NUM_LEDS; led_cnt++ )
        {
            c10x10rgb2_set_led_color ( ctx, led_cnt, 
                                       c10x10rgb2_color_wheel ( ( led_cnt + upd_cnt ) & 0xFF, rgb_pct ) );
        }
        error_flag |= c10x10rgb2_write_led_matrix ( ctx );
        for ( upd_rate_cnt = 0; upd_rate_cnt < upd_rate_ms; upd_rate_cnt++ )
        {
            Delay_1ms ( );
        }
    }
    return error_flag;
}

static uint8_t c10x10rgb2_invert_bit_pos ( uint8_t rotation, uint8_t data_in )
{
    if ( ( C10X10RGB2_ROTATION_V_0 == rotation ) || ( C10X10RGB2_ROTATION_H_0 == rotation ) )
    {
        return data_in;
    }
    // Invert bits position for H_0 and V_180 rotation
    return ( 7 - data_in );
}

static uint8_t c10x10rgb2_invert_byte_pos ( uint8_t rotation, uint8_t data_in )
{
    if ( ( C10X10RGB2_ROTATION_V_0 == rotation ) || ( C10X10RGB2_ROTATION_H_180 == rotation ) )
    {
        return data_in;
    }
    // Invert bytes position for H_0 and V_180 rotation
    return ( 9 - data_in );
}

static uint8_t c10x10rgb2_get_led_num ( uint8_t rotation, uint8_t x_pos, uint8_t y_pos )
{
    if ( ( C10X10RGB2_ROTATION_H_0 == rotation ) || ( C10X10RGB2_ROTATION_H_180 == rotation ) )
    {
        // Rotate X and Y for horizontal rotation
        return ( 10 * x_pos + y_pos );
    }
    return ( 10 * y_pos + x_pos );
}

static err_t c10x10rgb2_write_char_buf ( c10x10rgb2_t *ctx, uint8_t *data_in )
{
    uint8_t cnt_byte = 0;
    uint8_t cnt_bit = 0;
    uint8_t ascii_byte = 0;
    uint8_t led_offset = 0;
    if ( C10X10RGB2_ROTATION_V_180 == ctx->pen.rotation )
    {
        // LED offset of 2 X-lines in V_180 rotation
        led_offset = 20;
    }
    else if ( C10X10RGB2_ROTATION_H_180 == ctx->pen.rotation )
    {
        // LED offset of 2 Y-lines in H_180 rotation
        led_offset = 2;
    }
    // Set all LEDs to backgrount color
    c10x10rgb2_set_leds_color ( ctx, ctx->pen.bg_rgb );
    for ( cnt_byte = 0; cnt_byte < 10; cnt_byte++ )
    {
        ascii_byte = data_in[ c10x10rgb2_invert_byte_pos ( ctx->pen.rotation, cnt_byte ) ];
        for ( cnt_bit = 0; cnt_bit < 8; cnt_bit++ )
        {
            if ( ascii_byte & ( 1 << c10x10rgb2_invert_bit_pos( ctx->pen.rotation, cnt_bit ) ) )
            {
                // Set to text color only those LEDs related to set bits in a an input array
                c10x10rgb2_set_led_color ( ctx, c10x10rgb2_get_led_num ( ctx->pen.rotation, cnt_byte, cnt_bit ) + 
                                                led_offset, ctx->pen.txt_rgb );
            }
        }
    }
    return c10x10rgb2_write_led_matrix ( ctx );
}

// ------------------------------------------------------------------------- END
