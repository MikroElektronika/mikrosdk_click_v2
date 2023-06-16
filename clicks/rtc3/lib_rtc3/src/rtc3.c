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

#include "rtc3.h"
#include "conversions.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc3_cfg_setup ( rtc3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RTC3_I2C_ADDRESS;
}

err_t rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return RTC3_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC3_OK;
}

void rtc3_generic_write ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void rtc3_generic_read ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void rtc3_set_counting ( rtc3_t *ctx, uint8_t en_dis )
{
    uint8_t temp_w = 0;

    rtc3_generic_read( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );

    if ( 1 == en_dis )
    {
        temp_w &= ~0x80;

        rtc3_generic_write( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );
    }
    else if ( 0 == en_dis )
    {
        temp_w |= 0x80;

        rtc3_generic_write( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );
    }
}

void rtc3_set_time ( rtc3_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    data_buf[ 0 ] = dec_to_bcd ( ctx->time.time_seconds );
    data_buf[ 1 ] = dec_to_bcd ( ctx->time.time_minutes );
    data_buf[ 2 ] = dec_to_bcd ( ctx->time.time_hours );
    
    rtc3_generic_write ( ctx, RTC3_REG_TIME_SEC, data_buf, 3 );
}

void rtc3_get_time ( rtc3_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    rtc3_generic_read ( ctx, RTC3_REG_TIME_SEC, data_buf, 3 );
    
    ctx->time.time_seconds = bcd_to_dec ( data_buf[ 0 ] );
    ctx->time.time_minutes = bcd_to_dec ( data_buf[ 1 ] );
    ctx->time.time_hours = bcd_to_dec ( data_buf[ 2 ] );
}      

void rtc3_set_date ( rtc3_t *ctx )
{
    uint8_t data_buf[ 4 ] = { 0 };
    
    data_buf[ 0 ] = dec_to_bcd ( ctx->date.day_of_the_week );
    data_buf[ 1 ] = dec_to_bcd ( ctx->date.date_day );
    data_buf[ 2 ] = dec_to_bcd ( ctx->date.date_month );
    data_buf[ 3 ] = dec_to_bcd ( ctx->date.date_year );
    
    rtc3_generic_write ( ctx, RTC3_REG_TIME_DAY_OF_THE_WEEK, data_buf, 4 );
}

void rtc3_get_date ( rtc3_t *ctx )
{
    uint8_t data_buf[ 4 ] = { 0 };
    
    rtc3_generic_read ( ctx, RTC3_REG_TIME_DAY_OF_THE_WEEK, data_buf, 4 );
    
    ctx->date.day_of_the_week = bcd_to_dec ( data_buf[ 0 ] );
    ctx->date.date_day = bcd_to_dec ( data_buf[ 1 ] );
    ctx->date.date_month = bcd_to_dec ( data_buf[ 2 ] );
    ctx->date.date_year = bcd_to_dec ( data_buf[ 3 ] );
}

void rtc3_set_calibration ( rtc3_t *ctx, uint8_t cal_sign, uint8_t cal_number )
{
    uint8_t temp = 0;
    
    temp = RTC3_CONFIG1_INITIAL;
    
    temp |= cal_sign << 5;
    temp |= cal_number;
    
    rtc3_generic_write( ctx, RTC3_REG_CONFIG1, &temp, 1 );
}

void rtc3_set_trickle_charge ( rtc3_t *ctx, uint8_t tch2 )
{
    uint8_t temp = 0;

    rtc3_generic_read( ctx, RTC3_REG_TRICKLE_CHARGE2, &temp, 1 );

    if ( 0 == tch2 )
    {
        temp &= ~RTC3_TCH2_CLOSED;
    }
    else
    {
        temp |= RTC3_TCH2_CLOSED;
    }

    rtc3_generic_write( ctx, RTC3_REG_TRICKLE_CHARGE2, &temp, 1 );
}

void rtc3_set_trickle_charge_bypass ( rtc3_t *ctx, uint8_t tcfe )
{
    uint8_t temp = 0;

    rtc3_generic_read( ctx, RTC3_REG_CONFIG2, &temp, 1 );

    if ( 0 == tcfe )
    {
        temp &= ~RTC3_TCFE_CLOSED;
    }
    else
    {
        temp |= RTC3_TCFE_CLOSED;
    }

    rtc3_generic_write( ctx, RTC3_REG_CONFIG2, &temp, 1 );
}

void rtc3_set_special_function_key1 ( rtc3_t *ctx, uint8_t sfkey1 )
{
    rtc3_generic_write( ctx, RTC3_REG_SF_KEY1, &sfkey1, 1 );
}

void rtc3_set_special_function_key2 ( rtc3_t *ctx, uint8_t sfkey2 )
{
    rtc3_generic_write( ctx, RTC3_REG_SF_KEY2, &sfkey2, 1 );
}

void rtc3_set_frequency_calibration ( rtc3_t *ctx, uint8_t ftf )
{
    uint8_t w_temp = 0;

    if ( 0 == ftf )
    {
        w_temp = RTC3_FTF_NORMAL_512_HZ;
        rtc3_generic_write( ctx, RTC3_REG_SFR, &w_temp, 1 );
    }
    else
    {
        w_temp = RTC3_FTF_1_HZ;
        rtc3_generic_write( ctx, RTC3_REG_SFR, &w_temp, 1 );
    }
}

uint8_t rtc3_get_interrupt( rtc3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

