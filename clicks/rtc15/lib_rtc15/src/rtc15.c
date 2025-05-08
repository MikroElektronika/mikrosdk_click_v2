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
 * @file rtc15.c
 * @brief RTC 15 Click Driver.
 */

#include "rtc15.h"
#include "conversions.h"

void rtc15_cfg_setup ( rtc15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->cle = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC15_DEVICE_ADDRESS;
}

err_t rtc15_init ( rtc15_t *ctx, rtc15_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->cle, cfg->cle );
    digital_out_low ( &ctx->en );
    digital_out_low ( &ctx->cle );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc15_default_cfg ( rtc15_t *ctx ) 
{
    err_t error_flag = RTC15_OK;
    rtc15_enable_device ( ctx );
    rtc15_enable_clkout ( ctx );
    Delay_100ms ( );
    if ( RTC15_ERROR == rtc15_check_communication ( ctx ) )
    {
        return RTC15_ERROR;
    }

    error_flag |= rtc15_write_reg ( ctx, RTC15_REG_CONTROL1, RTC15_CONTROL1_TEST_NORMAL | 
                                                             RTC15_CONTROL1_SR_NORMAL | 
                                                             RTC15_CONTROL1_STOP_NO_STOP | 
                                                             RTC15_CONTROL1_CIE_DIS | 
                                                             RTC15_CONTROL1_12_24_24 );

    error_flag |= rtc15_write_reg ( ctx, RTC15_REG_CONTROL2, RTC15_CONTROL2_AIE_DIS | 
                                                             RTC15_CONTROL2_AF_DIS | 
                                                             RTC15_CONTROL2_MI_DIS | 
                                                             RTC15_CONTROL2_HMI_DIS | 
                                                             RTC15_CONTROL2_TF_DIS | 
                                                             RTC15_CONTROL2_FD_32_768KHZ );

    error_flag |= rtc15_write_reg ( ctx, RTC15_REG_TIMER_MODE, RTC15_TIMER_MODE_TD_1HZ | 
                                                               RTC15_TIMER_MODE_TE_EN | 
                                                               RTC15_TIMER_MODE_TIE_EN | 
                                                               RTC15_TIMER_MODE_TI_TP_PULSE );

    error_flag |= rtc15_write_reg ( ctx, RTC15_REG_TIMER_VALUE, RTC15_TIMER_VALUE_DEFAULT );

    return error_flag;
}

err_t rtc15_write_regs ( rtc15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ RTC15_REG_TIMER_MODE + 2 ] = { 0 };
    if ( ( ( reg + len ) > ( RTC15_REG_TIMER_MODE + 1 ) ) || ( NULL == data_in ) )
    {
        return RTC15_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc15_read_regs ( rtc15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( ( reg + len ) > ( RTC15_REG_TIMER_MODE + 1 ) ) || ( NULL == data_out ) )
    {
        return RTC15_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc15_write_reg ( rtc15_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc15_write_regs( ctx, reg, &data_in, 1 );
}

err_t rtc15_read_reg ( rtc15_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc15_read_regs( ctx, reg, data_out, 1 );
}

void rtc15_enable_device ( rtc15_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void rtc15_disable_device ( rtc15_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void rtc15_enable_clkout ( rtc15_t *ctx )
{
    digital_out_high ( &ctx->cle );
}

void rtc15_disable_clkout ( rtc15_t *ctx )
{
    digital_out_low ( &ctx->cle );
}

uint8_t rtc15_get_int_pin ( rtc15_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc15_check_communication ( rtc15_t *ctx )
{
    uint8_t dummy_ram = 0;
    if ( RTC15_OK == rtc15_write_reg ( ctx, RTC15_REG_RAM, RTC15_DUMMY_RAM ) )
    {
        if ( RTC15_OK == rtc15_read_reg ( ctx, RTC15_REG_RAM, &dummy_ram ) )
        {
            if ( RTC15_DUMMY_RAM == dummy_ram )
            {
                return RTC15_OK;
            }
        }
    }
    return RTC15_ERROR;
}

err_t rtc15_set_time ( rtc15_t *ctx, rtc15_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second );
    data_buf[ 1 ] = dec_to_bcd ( time->minute );
    data_buf[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC15_ERROR == rtc15_write_regs ( ctx, RTC15_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC15_ERROR;
    }
    return RTC15_OK;
}

err_t rtc15_read_time ( rtc15_t *ctx, rtc15_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( RTC15_ERROR == rtc15_read_regs ( ctx, RTC15_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC15_ERROR;
    }
    time->second = bcd_to_dec ( data_buf[ 0 ] );
    time->minute = bcd_to_dec ( data_buf[ 1 ] );
    time->hour = bcd_to_dec ( data_buf[ 2 ] );
    return RTC15_OK;
}

err_t rtc15_set_date ( rtc15_t *ctx, rtc15_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day );
    data_buf[ 1 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC15_ERROR == rtc15_write_regs ( ctx, RTC15_REG_DATE, data_buf, 4 ) )
    {
        return RTC15_ERROR;
    }
    return RTC15_OK;
}

err_t rtc15_read_date ( rtc15_t *ctx, rtc15_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC15_ERROR == rtc15_read_regs ( ctx, RTC15_REG_DATE, data_buf, 4 ) )
    {
        return RTC15_ERROR;
    }
    date->day = bcd_to_dec ( data_buf[ 0 ] );
    date->day_of_week = data_buf[ 1 ];
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC15_OK;
}

// ------------------------------------------------------------------------- END
