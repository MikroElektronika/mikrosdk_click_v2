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

#include "timer.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void timer_cfg_setup ( timer_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->evt = HAL_PIN_NC;
    cfg->alm = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TIMER_I2C_ADDR;
}

TIMER_RETVAL timer_init ( timer_t *ctx, timer_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TIMER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->evt, cfg->evt );
    digital_out_write( &ctx->evt, 1 );
    
    // Input pins

    digital_in_init( &ctx->alm, cfg->alm );

    return TIMER_OK;
}

void timer_generic_write ( timer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );     
}

void timer_generic_read ( timer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void timer_hw_reset ( timer_t *ctx )
{
    digital_out_low( &ctx->evt );
    Delay_100ms( );
    digital_out_high( &ctx->evt );
}

void timer_read_eeprom ( timer_t *ctx )
{
    uint8_t r_buffer[ 10 ];
    
    timer_generic_read( ctx, TIMER_REG_EEPROM, r_buffer, TIMER_EEPROM_SIZE );
}

void timer_write_byte_eeprom ( timer_t *ctx, uint8_t location, uint8_t write_data )
{
    location %= 10;
    timer_generic_write( ctx, TIMER_REG_EEPROM + location, &write_data, 1 );
}

uint8_t timer_read_byte_eeprom ( timer_t *ctx, uint8_t location )
{
    uint8_t result;
    
    location %= 10;
    
    timer_generic_read( ctx, TIMER_REG_EEPROM + location, &result, 1 );
    
    return result;
}

uint8_t timer_get_configuration ( timer_t *ctx )
{
    uint8_t tmp;

    timer_generic_read( ctx, TIMER_REG_CONFIG, &tmp, 1 );
    
    return tmp;
}

uint32_t timer_get_etc_data ( timer_t *ctx )
{
    uint8_t r_buffer[ 4 ];
    uint32_t result;
   
    timer_generic_read( ctx, TIMER_REG_ELAPSED, r_buffer, 4 );
    
    result = r_buffer[ 3 ];
    result <<= 8;
    result |= r_buffer[ 2 ];
    result <<= 8;
    result |= r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 0 ];
    
    return result;
}

void timer_set_etc_data ( timer_t *ctx, uint32_t etc_value )
{
    uint8_t w_buffer[ 4 ];
  
    w_buffer[ 0 ] = ( uint8_t ) etc_value;
    w_buffer[ 1 ] = ( uint8_t ) ( etc_value >> 8 );
    w_buffer[ 2 ] = ( uint8_t ) ( etc_value >> 16 );
    w_buffer[ 3 ] = ( uint8_t ) ( etc_value >> 24 );
    
    timer_generic_write( ctx, TIMER_REG_ELAPSED, w_buffer, 4 );
}

uint32_t timer_get_etc_seconds ( timer_t *ctx )
{
    uint32_t seconds;

    seconds = timer_get_etc_data( ctx );
    seconds >>= 2;

    return seconds;
}

void timer_get_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds )
{
    uint32_t seconds;

    seconds = timer_get_etc_seconds( ctx );
    
    *time_days = seconds / 86400;
    seconds %= 86400;
    *time_hours = seconds / 3600;
    seconds %= 3600;
    *time_minutes = seconds / 60;
    *time_seconds = seconds % 60;
}

void timer_set_etc_seconds ( timer_t *ctx, uint32_t etc_seconds )
{
    if ( etc_seconds < 0x40000000 )
    {
        etc_seconds <<= 2;
        timer_set_etc_data( ctx, etc_seconds );
    }
}

uint16_t timer_get_ec_data ( timer_t *ctx )
{
    uint8_t r_buffer[ 2 ];
    uint16_t result;

    timer_generic_read( ctx, TIMER_REG_EVT_CNTR, r_buffer, 2 );

    result = r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 0 ];

    return result;
}

void timer_set_ec_data ( timer_t *ctx, uint16_t ec_value )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ( uint8_t ) ec_value;
    w_buffer[ 1 ] = ( uint8_t ) ( ec_value >> 8 );

    timer_generic_write( ctx, TIMER_REG_EVT_CNTR, w_buffer, 2 );
}

uint16_t timer_get_ec_seconds ( timer_t *ctx )
{
    uint16_t seconds;

    seconds = timer_get_ec_data( ctx );
    seconds >>= 2;

    return seconds;
}

void timer_set_ec_seconds ( timer_t *ctx, uint16_t ec_seconds )
{
    if ( ec_seconds < 0x4000 )
    {
        ec_seconds <<= 2;
        timer_set_ec_data( ctx, ec_seconds );
    }
}

uint32_t timer_get_alarm_data ( timer_t *ctx )
{
    uint8_t r_buffer[ 4 ];
    uint32_t alarm;

    timer_generic_read( ctx, TIMER_REG_ALARM, r_buffer, 4 );
    alarm = r_buffer[ 3 ];
    alarm <<= 8;
    alarm |= r_buffer[ 2 ];
    alarm <<= 8;
    alarm |= r_buffer[ 1 ];
    alarm <<= 8;
    alarm |= r_buffer[ 0 ];

    return alarm;
}

void timer_set_alarm_data ( timer_t *ctx, uint32_t a_data )
{
    uint8_t w_buffer[ 4 ];
   
    w_buffer[ 0 ] = ( uint8_t ) a_data;
    w_buffer[ 1 ] = ( uint8_t ) ( a_data >> 8 );
    w_buffer[ 2 ] = ( uint8_t ) ( a_data >> 16 );
    w_buffer[ 3 ] = ( uint8_t ) ( a_data >> 24 );
    
    timer_generic_write( ctx, TIMER_REG_ALARM, w_buffer, 4 );
}

uint32_t timer_get_alarm_seconds ( timer_t *ctx  )
{
    uint8_t r_buffer[ 4 ];
    uint32_t alarm;

    timer_generic_read( ctx, TIMER_REG_ALARM, r_buffer, 4 );

    alarm = r_buffer[ 3 ];
    alarm <<= 8;
    alarm |= r_buffer[ 2 ];
    alarm <<= 8;
    alarm |= r_buffer[ 1 ];
    alarm <<= 8;
    alarm |= r_buffer[ 0 ];

    alarm >>= 2;

    return alarm;
}

void timer_get_alarm_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds )
{
    uint32_t seconds;

    seconds = timer_get_alarm_seconds( ctx );

    *time_days = seconds / 86400;
    seconds %= 86400;
    *time_hours = seconds / 3600;
    seconds %= 3600;
    *time_minutes = seconds / 60;
    *time_seconds = seconds % 60;
}

void timer_set_alarm_seconds ( timer_t *ctx, uint32_t alarm_seconds )
{
    uint8_t w_buffer[ 4 ];
    
    if ( alarm_seconds < 0x40000000 )
    {
        alarm_seconds <<= 2;
        
        w_buffer[ 0 ] = ( uint8_t ) alarm_seconds;
        w_buffer[ 1 ] = ( uint8_t ) ( alarm_seconds >> 8 );
        w_buffer[ 2 ] = ( uint8_t ) ( alarm_seconds >> 16 );
        w_buffer[ 3 ] = ( uint8_t ) ( alarm_seconds >> 24 );
        
        timer_generic_write( ctx, TIMER_REG_ALARM, w_buffer, 4 );
    }
}

uint8_t timer_check_write_disable ( timer_t *ctx )
{
    uint8_t status_wd;

    timer_generic_read( ctx, TIMER_REG_CONFIG, &status_wd, 1 );

    status_wd >>= 4;
    status_wd &= 0x01;

    return status_wd;
}

void timer_disable_write ( timer_t *ctx )
{
    uint8_t tmp = 0xAA;
    
    while ( timer_check_write_disable( ctx ) )
    {
        timer_generic_write( ctx, TIMER_REG_WRITE_DISABLE, &tmp, 1 );
        timer_generic_write( ctx, TIMER_REG_WRITE_DISABLE, &tmp, 1 );
        Delay_10us( );
    }
}

void timer_enable_write ( timer_t *ctx )
{
    uint8_t tmp = 0xF0;
    
    while ( !timer_check_write_disable( ctx ) )
    {
        timer_generic_write( ctx, TIMER_REG_WRITE_DISABLE, &tmp, 1 );
        timer_generic_write( ctx, TIMER_REG_WRITE_DISABLE, &tmp, 1 );
        Delay_10us( );
    }
}

void timer_alarm_output_select ( timer_t *ctx )
{
    uint8_t cnf_val;
    
    timer_generic_read( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
    cnf_val |= TIMER_AOS_BIT;
    timer_generic_write( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
}

void timer_reset_enable ( timer_t *ctx )
{
    uint8_t cnf_val;

    timer_generic_read( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
    cnf_val |= TIMER_RE_BIT;
    timer_generic_write( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
}

void timer_set_alarm_polarity ( timer_t *ctx )
{
    uint8_t cnf_val;

    timer_generic_read( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
    cnf_val |= TIMER_AP_BIT;
    timer_generic_write( ctx, TIMER_REG_CONFIG, &cnf_val, 1 );
}

uint8_t timer_get_alarm_flag ( timer_t *ctx )
{
    uint8_t af_val;

    timer_generic_read( ctx, TIMER_REG_CONFIG, &af_val, 1 );

    af_val >>= 6;
    af_val &= 0x01;

    return af_val;
}

void timer_soft_reset ( timer_t *ctx )
{
    uint8_t tmp = 0x55;

    timer_reset_enable( ctx );
    
    timer_generic_write( ctx, TIMER_REG_RESET, &tmp, 1 );
    timer_generic_write( ctx, TIMER_REG_RESET, &tmp, 1 );
}

uint8_t timer_check_interrupt ( timer_t *ctx )
{
    return digital_in_read( &ctx->alm );
}

// ------------------------------------------------------------------------- END

