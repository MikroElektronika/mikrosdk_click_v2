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
 * @file c16x12r.c
 * @brief 16x12 R Click Driver.
 */

#include "c16x12r.h"
#include "c16x12r_resources.h"

/**
 * @brief 16x12 R invert bit pos function.
 * @details This function inverts bits position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - XY exchanged, X mirrored,
 *                       @li @c 0x01 - Vertical 180 - XY exchanged, Y mirrored,
 *                       @li @c 0x10 - Horizontal 0 - Normal,
 *                       @li @c 0x11 - Horizontal 180 - XY mirrored.
 * @param[in] data_in : Bits position input to invert (up to 11).
 * @return Output bits position.
 * @note None.
 */
static uint8_t c16x12r_invert_bit_pos ( uint8_t rotation, uint8_t data_in );

/**
 * @brief 16x12 R invert byte pos function.
 * @details This function inverts bytes position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - XY exchanged, X mirrored,
 *                       @li @c 0x01 - Vertical 180 - XY exchanged, Y mirrored,
 *                       @li @c 0x10 - Horizontal 0 - Normal,
 *                       @li @c 0x11 - Horizontal 180 - XY mirrored.
 * @param[in] data_in : Bytes position input to invert (up to 11).
 * @return Output bytes position.
 * @note None.
 */
static uint8_t c16x12r_invert_byte_pos ( uint8_t rotation, uint8_t data_in );

/**
 * @brief 16x12 R get led num function.
 * @details This function returns the LED number for X and Y position depending on the ASCII char rotation.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - XY exchanged, X mirrored,
 *                       @li @c 0x01 - Vertical 180 - XY exchanged, Y mirrored,
 *                       @li @c 0x10 - Horizontal 0 - Normal,
 *                       @li @c 0x11 - Horizontal 180 - XY mirrored.
 * @param[in] x_pos : X position for LED (up to 15).
 * @param[in] y_pos : Y position for LED (up to 15).
 * @return LED number.
 * @note None.
 */
static uint8_t c16x12r_get_led_num ( uint8_t rotation, uint8_t x_pos, uint8_t y_pos );

/**
 * @brief 16x12 R write char buf function.
 * @details This function writes the selected 12x12 char buffer to display.
 * @param[in] ctx : Click context object.
 * See #c16x12r_t object definition for detailed explanation.
 * @param[in] data_in : 12 words data buffer to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c16x12r_write_char_buf ( c16x12r_t *ctx, uint16_t *data_in );

void c16x12r_cfg_setup ( c16x12r_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sdb = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->intb = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C16X12R_DEVICE_ADDRESS_A2A1_00;
}

err_t c16x12r_init ( c16x12r_t *ctx, c16x12r_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sdb, cfg->sdb );

    digital_in_init( &ctx->intb, cfg->intb );

    return I2C_MASTER_SUCCESS;
}

err_t c16x12r_default_cfg ( c16x12r_t *ctx ) 
{
    err_t error_flag = C16X12R_OK;
    c16x12r_reset_device_i2c ( ctx );
    c16x12r_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= c16x12r_write_page_reg ( ctx, C16X12R_PAGE_REG_CONFIG, C16X12R_CONFIG_SSD_NORMAL );
    Delay_100ms ( );
    error_flag |= c16x12r_write_page_reg ( ctx, C16X12R_PAGE_REG_GLOBAL_CURRENT_CTRL, C16X12R_CURRENT_DEFAULT );
    error_flag |= c16x12r_set_pwm ( ctx, C16X12R_PWM_DUTY_DEFAULT );
    error_flag |= c16x12r_set_mode ( ctx, C16X12R_MODE_PWM );
    error_flag |= c16x12r_clear_screen ( ctx );
    Delay_100ms ( );
    ctx->text_rotation = C16X12R_ROTATION_H_0;
    return error_flag;
}

err_t c16x12r_write_reg ( c16x12r_t *ctx, uint8_t reg, uint8_t data_in )
{
    return c16x12r_write_regs( ctx, reg, &data_in, 1 );
}

err_t c16x12r_write_regs ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t c16x12r_read_reg ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return c16x12r_read_regs( ctx, reg, data_out, 1 );
}

err_t c16x12r_read_regs ( c16x12r_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void c16x12r_enable_device ( c16x12r_t *ctx )
{
    digital_out_high ( &ctx->sdb );
}

void c16x12r_disable_device ( c16x12r_t *ctx )
{
    digital_out_low ( &ctx->sdb );
}

void c16x12r_reset_device_i2c ( c16x12r_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void c16x12r_set_rst_pin ( c16x12r_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t c16x12r_get_intb_pin ( c16x12r_t *ctx )
{
    return digital_in_read ( &ctx->intb );
}

err_t c16x12r_lock_page ( c16x12r_t *ctx )
{
    return c16x12r_write_reg ( ctx, C16X12R_REG_PAGE_LOCK, C16X12R_PAGE_LOCK );
}

err_t c16x12r_unlock_page ( c16x12r_t *ctx )
{
    return c16x12r_write_reg ( ctx, C16X12R_REG_PAGE_LOCK, C16X12R_PAGE_UNLOCK );
}

err_t c16x12r_select_page ( c16x12r_t *ctx, uint8_t page )
{
    err_t error_flag = C16X12R_OK;
    if ( page > C16X12R_PAGE_SELECT_3 )
    {
        return C16X12R_ERROR;
    }
    error_flag |= c16x12r_unlock_page ( ctx );
    error_flag |= c16x12r_write_reg ( ctx, C16X12R_REG_PAGE_SELECT, page );
    return error_flag;
}

err_t c16x12r_write_page_reg ( c16x12r_t *ctx, uint16_t page_reg, uint8_t data_in )
{
    err_t error_flag = C16X12R_OK;
    error_flag |= c16x12r_select_page ( ctx, ( uint8_t ) ( page_reg >> 8 ) );
    error_flag |= c16x12r_write_reg ( ctx, ( uint8_t ) ( page_reg & 0xFF ), data_in );
    return error_flag;
}

err_t c16x12r_write_page_regs ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = C16X12R_OK;
    error_flag |= c16x12r_select_page ( ctx, ( uint8_t ) ( page_reg >> 8 ) );
    error_flag |= c16x12r_write_regs ( ctx, ( uint8_t ) ( page_reg & 0xFF ), data_in, len );
    return error_flag;
}

err_t c16x12r_read_page_reg ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_out )
{
    err_t error_flag = C16X12R_OK;
    error_flag |= c16x12r_select_page ( ctx, ( uint8_t ) ( page_reg >> 8 ) );
    error_flag |= c16x12r_read_reg ( ctx, ( uint8_t ) ( page_reg & 0xFF ), data_out );
    return error_flag;
}

err_t c16x12r_read_page_regs ( c16x12r_t *ctx, uint16_t page_reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = C16X12R_OK;
    error_flag |= c16x12r_select_page ( ctx, ( uint8_t ) ( page_reg >> 8 ) );
    error_flag |= c16x12r_read_regs ( ctx, ( uint8_t ) ( page_reg & 0xFF ), data_out, len );
    return error_flag;
}

err_t c16x12r_fill_screen ( c16x12r_t *ctx )
{
    memset ( ctx->leds, 0xFF, sizeof( ctx->leds ) );
    return c16x12r_write_page_regs ( ctx, C16X12R_PAGE_REG_LED_ON_OFF, ctx->leds, sizeof( ctx->leds ) );
}

err_t c16x12r_clear_screen ( c16x12r_t *ctx )
{
    memset ( ctx->leds, 0x00, sizeof( ctx->leds ) );
    return c16x12r_write_page_regs ( ctx, C16X12R_PAGE_REG_LED_ON_OFF, ctx->leds, sizeof( ctx->leds ) );
}

err_t c16x12r_set_pwm ( c16x12r_t *ctx, uint8_t duty )
{
    uint8_t leds_duty[ C16X12R_NUM_LEDS ] = { 0 };
    memset ( leds_duty, duty, C16X12R_NUM_LEDS );
    return c16x12r_write_page_regs ( ctx, C16X12R_PAGE_REG_PWM, leds_duty, C16X12R_NUM_LEDS );
}

err_t c16x12r_set_mode ( c16x12r_t *ctx, uint8_t mode )
{
    uint8_t leds_mode[ C16X12R_NUM_LEDS ] = { 0 };
    if ( mode > C16X12R_MODE_ABM3 )
    {
        return C16X12R_ERROR;
    }
    memset ( leds_mode, mode, C16X12R_NUM_LEDS );
    return c16x12r_write_page_regs ( ctx, C16X12R_PAGE_REG_MODE, leds_mode, C16X12R_NUM_LEDS );
}

void c16x12r_set_led_state ( c16x12r_t *ctx, uint8_t led_num, uint8_t state )
{
    if ( ( state > C16X12R_LED_STATE_ON ) || ( led_num >= C16X12R_NUM_LEDS ) )
    {
        return;
    }
    if ( C16X12R_LED_STATE_ON == state )
    {
        ctx->leds[ led_num / 8 ] |= ( 1 << ( led_num % 8 ) );
    }
    else
    {
        ctx->leds[ led_num / 8 ] &= ( ~( 1 << ( led_num % 8 ) ) );
    }
}

err_t c16x12r_write_leds ( c16x12r_t *ctx )
{
    return c16x12r_write_page_regs ( ctx, C16X12R_PAGE_REG_LED_ON_OFF, ctx->leds, sizeof( ctx->leds ) );
}

err_t c16x12r_draw_picture ( c16x12r_t *ctx, const uint16_t *image )
{
    for ( uint16_t column = 0; column < C16X12R_NUM_COLUMNS; column++ )
    {
        ctx->leds[ column * 2 + 1 ] = ( uint8_t ) ( image[ column ] >> 8 );
        ctx->leds[ column * 2 ] = ( uint8_t ) ( image[ column ] & 0xFF );
    }
    return c16x12r_write_leds ( ctx );
}

err_t c16x12r_write_char ( c16x12r_t *ctx, uint8_t data_in )
{
    uint16_t data_buf[ C16X12R_NUM_COLUMNS ] = { 0 };
    memcpy ( data_buf, c16x12r_font[ data_in - 32 ], sizeof ( data_buf ) );
    return c16x12r_write_char_buf ( ctx, data_buf );
}

err_t c16x12r_write_string ( c16x12r_t *ctx, uint8_t *data_in, uint16_t speed_ms )
{
    err_t error_flag = C16X12R_OK;
    uint16_t data_buf[ C16X12R_NUM_COLUMNS * 2 ] = { 0 };
    uint8_t char_cnt = 0;
    uint8_t line_cnt = 0;
    uint8_t delay_cnt = 0;
    uint8_t num_columns = 0;
    uint8_t column_cnt = 0;
    while ( char_cnt < ( strlen( data_in ) ) )
    {
        // Retrieve columns array for selected ASCII from font matrix ignoring multiple blank columns
        while ( ( column_cnt < C16X12R_NUM_COLUMNS ) && ( num_columns < C16X12R_NUM_COLUMNS ) )
        {
            if ( 0 != c16x12r_font[ data_in[ char_cnt ] - 32 ][ column_cnt ] || 
                 0 != c16x12r_font[ data_in[ char_cnt ] - 32 ][ column_cnt + 1 ] )
            {
                data_buf[ num_columns + C16X12R_NUM_COLUMNS ] = c16x12r_font[ data_in[ char_cnt ] - 32 ][ column_cnt ];
                num_columns++;
            }
            column_cnt++;
        }

        // Write buffer to display if all columns are retrieved
        if ( C16X12R_NUM_COLUMNS == num_columns )
        {
            for ( line_cnt = 0; line_cnt < C16X12R_NUM_COLUMNS; line_cnt++ )
            {
                // Writes char buffer scrolling it the left side
                error_flag |= c16x12r_write_char_buf ( ctx, data_buf );
                memmove ( &data_buf[ 0 ], &data_buf[ 1 ], sizeof ( data_buf ) - sizeof ( data_buf[ 0 ] ) );
                data_buf[ C16X12R_NUM_COLUMNS * 2 - 1 ] = 0;
                for ( delay_cnt = 0; delay_cnt < speed_ms; delay_cnt++ )
                {
                    Delay_1ms ( );
                }
            }
            num_columns = 0;
        }
        else
        {
            // Go to next char and add one blank column
            column_cnt = 0;
            data_buf[ num_columns + C16X12R_NUM_COLUMNS ] = 0;
            num_columns++;
            char_cnt++;
        }
    }

    // Scroll the rest of the ASCII char lines out of the screen
    for ( line_cnt = 0; line_cnt < ( C16X12R_NUM_COLUMNS * 2 ); line_cnt++ )
    {
        error_flag |= c16x12r_write_char_buf ( ctx, data_buf );
        memmove ( &data_buf[ 0 ], &data_buf[ 1 ], sizeof ( data_buf ) - sizeof ( data_buf[ 0 ] ) );
        data_buf[ C16X12R_NUM_COLUMNS * 2 - 1 ] = 0;
        for ( uint16_t cnt_delay = 0; cnt_delay < speed_ms; cnt_delay++ )
        {
            Delay_1ms ( );
        }
    }
    return error_flag;
}

static uint8_t c16x12r_invert_bit_pos ( uint8_t rotation, uint8_t data_in )
{
    if ( ( C16X12R_ROTATION_V_0 == rotation ) || ( C16X12R_ROTATION_H_0 == rotation ) )
    {
        return data_in;
    }
    // Invert bits position for H_180 and V_180 rotation
    return ( C16X12R_NUM_COLUMNS - data_in - 1 );
}

static uint8_t c16x12r_invert_byte_pos ( uint8_t rotation, uint8_t data_in )
{
    if ( ( C16X12R_ROTATION_V_0 == rotation ) || ( C16X12R_ROTATION_H_180 == rotation ) )
    {
        return data_in;
    }
    // Invert bytes position for H_0 and V_180 rotation
    return ( C16X12R_NUM_COLUMNS - data_in - 1 );
}

static uint8_t c16x12r_get_led_num ( uint8_t rotation, uint8_t x_pos, uint8_t y_pos )
{
    if ( ( C16X12R_ROTATION_H_0 == rotation ) || ( C16X12R_ROTATION_H_180 == rotation ) )
    {
        // Rotate X and Y for horizontal rotation
        return ( C16X12R_NUM_ROWS * x_pos + y_pos );
    }
    return ( C16X12R_NUM_ROWS * y_pos + x_pos );
}

static err_t c16x12r_write_char_buf ( c16x12r_t *ctx, uint16_t *data_in )
{
    uint8_t cnt_byte = 0;
    uint8_t cnt_bit = 0;
    uint16_t ascii_byte = 0;
    uint8_t led_offset = 2;
    memset ( ctx->leds, 0x00, sizeof( ctx->leds ) );
    for ( cnt_byte = 0; cnt_byte < C16X12R_NUM_COLUMNS; cnt_byte++ )
    {
        ascii_byte = data_in[ c16x12r_invert_byte_pos ( ctx->text_rotation, cnt_byte ) ];
        for ( cnt_bit = 0; cnt_bit < C16X12R_NUM_COLUMNS; cnt_bit++ )
        {
            if ( ascii_byte & ( 1 << c16x12r_invert_bit_pos( ctx->text_rotation, cnt_bit ) ) )
            {
                // Enable only those LEDs related to set bits in an input array
                c16x12r_set_led_state ( ctx, 
                                        c16x12r_get_led_num ( ctx->text_rotation, cnt_byte, cnt_bit ) + led_offset, 
                                        C16X12R_LED_STATE_ON );
            }
        }
    }
    return c16x12r_write_leds ( ctx );
}

// ------------------------------------------------------------------------- END
