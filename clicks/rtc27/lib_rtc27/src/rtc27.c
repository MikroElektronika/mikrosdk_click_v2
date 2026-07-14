/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file rtc27.c
 * @brief RTC 27 Click Driver.
 */

#include "rtc27.h"
#include "conversions.h"

void rtc27_cfg_setup ( rtc27_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC27_DEVICE_ADDRESS;
}

err_t rtc27_init ( rtc27_t *ctx, rtc27_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc27_default_cfg ( rtc27_t *ctx ) 
{
    err_t error_flag = RTC27_OK;
    
    if ( RTC27_ERROR == rtc27_check_communication ( ctx ) )
    {
        return RTC27_ERROR;
    }
    
    // Performs soft reset
    error_flag |= rtc27_write_reg ( ctx, RTC27_REG_SR_RESET, RTC27_SR_RESET_SOFT_RESET );
    Delay_100ms ( );
    
    // Enable seconds interrupt
    error_flag |= rtc27_write_reg ( ctx, RTC27_REG_CONTROL_1, RTC27_CONTROL_1_FIXED_BITS |
                                                              RTC27_CONTROL_1_SECOND_INT_EN );

    // Enable battery switch over function
    error_flag |= rtc27_write_reg ( ctx, RTC27_REG_CONTROL_3, RTC27_CONTROL_3_PWRMNG_EN );
    
    // Unmask seconds interrupt flag
    error_flag |= rtc27_write_reg ( ctx, RTC27_REG_INTB_MASK1, RTC27_INT_MASK1_MI |
                                                               RTC27_INT_MASK1_OSIE |
                                                               RTC27_INT_MASK1_AIE |
                                                               RTC27_INT_MASK1_BIE |
                                                               RTC27_INT_MASK1_WD_CD );
    
    // Set INTB function of INTB/CLKOUT pin
    error_flag |= rtc27_write_reg ( ctx, RTC27_REG_CLKOUT_CTL, RTC27_CLKOUT_CTL_CLKOE_INTB | 
                                                               RTC27_CLKOUT_CTL_COF_HIZ );
    Delay_100ms ( );

    return error_flag;
}

err_t rtc27_write_regs ( rtc27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc27_read_regs ( rtc27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc27_write_reg ( rtc27_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return rtc27_write_regs ( ctx, reg, &data_in, 1 );
}

err_t rtc27_read_reg ( rtc27_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return rtc27_read_regs ( ctx, reg, data_out, 1 );
}

uint8_t rtc27_get_int_pin ( rtc27_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc27_check_communication ( rtc27_t *ctx )
{
    uint8_t num_tries = 10;
    uint8_t sr_reset = 0;
    while ( num_tries-- )
    {
        if ( RTC27_OK == rtc27_read_reg ( ctx, RTC27_REG_SR_RESET, &sr_reset ) )
        {
            if ( RTC27_SR_RESET_READ == sr_reset )
            {
                return RTC27_OK;
            }
        }
        Delay_10ms ( );
    }
    return RTC27_ERROR;
}

err_t rtc27_stop_clock ( rtc27_t *ctx )
{
    uint8_t control_1 = 0;
    if ( RTC27_OK == rtc27_read_reg ( ctx, RTC27_REG_CONTROL_1, &control_1 ) )
    {
        control_1 |= RTC27_CONTROL_1_STOP_CLOCK;
        if ( RTC27_OK == rtc27_write_reg ( ctx, RTC27_REG_CONTROL_1, control_1 ) )
        {
            return RTC27_OK;
        }
    }
    return RTC27_ERROR;
}

err_t rtc27_start_clock ( rtc27_t *ctx )
{
    uint8_t control_1 = 0;
    if ( RTC27_OK == rtc27_read_reg ( ctx, RTC27_REG_CONTROL_1, &control_1 ) )
    {
        control_1 &= ( ~RTC27_CONTROL_1_STOP_CLOCK );
        if ( RTC27_OK == rtc27_write_reg ( ctx, RTC27_REG_CONTROL_1, control_1 ) )
        {
            return RTC27_OK;
        }
    }
    return RTC27_ERROR;
}

err_t rtc27_clear_prescaler ( rtc27_t *ctx )
{
    return rtc27_write_reg ( ctx, RTC27_REG_SR_RESET, RTC27_SR_RESET_CLEAR_PRESCALER );
}

err_t rtc27_clear_msf ( rtc27_t *ctx )
{
    uint8_t control_2 = 0;
    if ( RTC27_OK == rtc27_read_reg ( ctx, RTC27_REG_CONTROL_2, &control_2 ) )
    {
        control_2 &= ( ~RTC27_CONTROL_2_MSF );
        if ( RTC27_OK == rtc27_write_reg ( ctx, RTC27_REG_CONTROL_2, control_2 ) )
        {
            return RTC27_OK;
        }
    }
    return RTC27_ERROR;
}

err_t rtc27_set_time ( rtc27_t *ctx, rtc27_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    if ( RTC27_ERROR == rtc27_write_regs ( ctx, RTC27_REG_100TH_SECONDS, data_buf, 4 ) )
    {
        return RTC27_ERROR;
    }
    return RTC27_OK;
}

err_t rtc27_read_time ( rtc27_t *ctx, rtc27_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC27_ERROR == rtc27_read_regs ( ctx, RTC27_REG_100TH_SECONDS, data_buf, 4 ) )
    {
        return RTC27_ERROR;
    }
    if ( data_buf[ 1 ] & RTC27_SECONDS_OSF )
    {
        return RTC27_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] & RTC27_SECONDS_SEC_MASK );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC27_OK;
}

err_t rtc27_set_date ( rtc27_t *ctx, rtc27_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day );
    data_buf[ 1 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC27_ERROR == rtc27_write_regs ( ctx, RTC27_REG_DAYS, data_buf, 4 ) )
    {
        return RTC27_ERROR;
    }
    return RTC27_OK;
}

err_t rtc27_read_date ( rtc27_t *ctx, rtc27_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC27_ERROR == rtc27_read_regs ( ctx, RTC27_REG_DAYS, data_buf, 4 ) )
    {
        return RTC27_ERROR;
    }
    date->day = bcd_to_dec ( data_buf[ 0 ] );
    date->day_of_week = data_buf[ 1 ];
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC27_OK;
}

err_t rtc27_set_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date )
{
    err_t error_flag = RTC27_OK;
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    data_buf[ 4 ] = dec_to_bcd ( date->day );
    data_buf[ 5 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 6 ] = dec_to_bcd ( date->month );
    data_buf[ 7 ] = dec_to_bcd ( date->year );
    error_flag |= rtc27_stop_clock ( ctx );
    if ( RTC27_OK == error_flag )
    {
        error_flag |= rtc27_clear_prescaler ( ctx );
    }
    if ( RTC27_OK == error_flag )
    {
        error_flag |= rtc27_write_regs ( ctx, RTC27_REG_100TH_SECONDS, data_buf, 8 );
    }
    if ( RTC27_OK == error_flag )
    {
        error_flag |= rtc27_start_clock ( ctx );
    }
    return RTC27_OK;
}

err_t rtc27_read_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( RTC27_ERROR == rtc27_read_regs ( ctx, RTC27_REG_100TH_SECONDS, data_buf, 8 ) )
    {
        return RTC27_ERROR;
    }
    if ( data_buf[ 1 ] & RTC27_SECONDS_OSF )
    {
        return RTC27_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] & RTC27_SECONDS_SEC_MASK );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    date->day = bcd_to_dec ( data_buf[ 4 ] );
    date->day_of_week = data_buf[ 5 ];
    date->month = bcd_to_dec ( data_buf[ 6 ] );
    date->year = bcd_to_dec ( data_buf[ 7 ] );
    return RTC27_OK;
}

// ------------------------------------------------------------------------- END
