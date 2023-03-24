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
 * @file rtc19.c
 * @brief RTC 19 Click Driver.
 */

#include "rtc19.h"
#include "conversions.h"

void rtc19_cfg_setup ( rtc19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->psw = HAL_PIN_NC;
    cfg->intb = HAL_PIN_NC;
    cfg->din = HAL_PIN_NC;
    cfg->inta = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC19_DEVICE_ADDRESS;
}

err_t rtc19_init ( rtc19_t *ctx, rtc19_cfg_t *cfg ) 
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

    digital_out_init( &ctx->din, cfg->din );
    digital_out_low ( &ctx->din );

    digital_in_init( &ctx->intb, cfg->intb );
    digital_in_init( &ctx->psw, cfg->psw );
    digital_in_init( &ctx->inta, cfg->inta );

    return I2C_MASTER_SUCCESS;
}

err_t rtc19_default_cfg ( rtc19_t *ctx ) 
{
    err_t error_flag = RTC19_OK;
    error_flag |= rtc19_reset_device ( ctx );
    error_flag |= rtc19_write_register ( ctx, RTC19_REG_INT_EN, RTC19_INT_EN_TIE );
    error_flag |= rtc19_write_register ( ctx, RTC19_REG_TIMER_INIT2, 
                                         ( uint8_t ) ( ( RTC19_TIMER_INIT_16CNT >> 8 ) & 0xFF ) );
    error_flag |= rtc19_write_register ( ctx, RTC19_REG_TIMER_INIT1, 
                                         ( uint8_t ) ( RTC19_TIMER_INIT_16CNT & 0xFF ) );
    error_flag |= rtc19_write_register ( ctx, RTC19_REG_TIMER_CONFIG, RTC19_TIMER_CONFIG_TE | 
                                                                      RTC19_TIMER_CONFIG_TRPT | 
                                                                      RTC19_TIMER_CONFIG_TFS_16HZ );
    error_flag |= rtc19_clear_interrupts ( ctx );
    return error_flag;
}

err_t rtc19_generic_write ( rtc19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc19_generic_read ( rtc19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc19_write_register ( rtc19_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc19_generic_write ( ctx, reg, &data_in, 1 );
}

err_t rtc19_read_register ( rtc19_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc19_generic_read ( ctx, reg, data_out, 1 );
}

void rtc19_set_din_pin ( rtc19_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->din, state );
}

uint8_t rtc19_get_psw_pin ( rtc19_t *ctx )
{
    return digital_in_read ( &ctx->psw );
}

uint8_t rtc19_get_inta_pin ( rtc19_t *ctx )
{
    return digital_in_read ( &ctx->inta );
}

uint8_t rtc19_get_intb_pin ( rtc19_t *ctx )
{
    return digital_in_read ( &ctx->intb );
}

err_t rtc19_set_time ( rtc19_t *ctx, rtc19_time_t *time )
{
    uint8_t data_buf[ 3 ];
    data_buf[ 0 ] = dec_to_bcd ( time->second );
    data_buf[ 1 ] = dec_to_bcd ( time->minute );
    data_buf[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC19_ERROR == rtc19_generic_write ( ctx, RTC19_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC19_ERROR;
    }
    return RTC19_OK;
}

err_t rtc19_read_time ( rtc19_t *ctx, rtc19_time_t *time )
{
    uint8_t data_buf[ 4 ];
    if ( RTC19_ERROR == rtc19_generic_read ( ctx, RTC19_REG_SECONDS_1_128, data_buf, 4 ) )
    {
        return RTC19_ERROR;
    }
    time->sub_second = ( ( uint32_t ) data_buf[ 0 ] * 1000 ) / 128;
    time->second = bcd_to_dec ( data_buf[ 1 ] );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC19_OK;
}

err_t rtc19_set_date ( rtc19_t *ctx, rtc19_date_t *date )
{
    uint8_t data_buf[ 4 ];
    data_buf[ 0 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 1 ] = dec_to_bcd ( date->day );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC19_ERROR == rtc19_generic_write ( ctx, RTC19_REG_DAY, data_buf, 4 ) )
    {
        return RTC19_ERROR;
    }
    return RTC19_OK;
}

err_t rtc19_read_date ( rtc19_t *ctx, rtc19_date_t *date )
{
    uint8_t data_buf[ 4 ];
    if ( RTC19_ERROR == rtc19_generic_read ( ctx, RTC19_REG_DAY, data_buf, 4 ) )
    {
        return RTC19_ERROR;
    }
    date->day_of_week = data_buf[ 0 ];
    date->day = bcd_to_dec ( data_buf[ 1 ] );
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC19_OK;
}

err_t rtc19_reset_device ( rtc19_t *ctx )
{
    err_t error_flag = rtc19_write_register ( ctx, RTC19_REG_RTC_RESET, RTC19_RTC_RESET_SET );
    Delay_100ms ( );
    error_flag |= rtc19_write_register ( ctx, RTC19_REG_RTC_RESET, RTC19_RTC_RESET_CLEAR );
    Delay_1sec ( );
    return error_flag;
}

err_t rtc19_clear_interrupts ( rtc19_t *ctx )
{
    uint8_t reg_data;
    return rtc19_read_register ( ctx, RTC19_REG_STATUS, &reg_data );
}

// ------------------------------------------------------------------------- END
