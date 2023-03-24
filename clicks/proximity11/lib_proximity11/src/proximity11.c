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

#include "proximity11.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity11_cfg_setup ( proximity11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY11_DEVICE_ADDRESS;

    cfg->als_data0_gain_cfg = 0;
    cfg->als_data1_gain_cfg = 0;
    cfg->als_measure_time_cfg = 0;
}

PROXIMITY11_RETVAL proximity11_init ( proximity11_t *ctx, proximity11_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    ctx->als.als_data0_gain = cfg->als_data0_gain_cfg;
    ctx->als.als_data1_gain = cfg->als_data1_gain_cfg;
    ctx->als.als_measure_time = cfg->als_measure_time_cfg;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY11_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY11_OK;
}

uint8_t proximity11_default_cfg ( proximity11_t *ctx )
{
    uint8_t aux_reg_addr;
    uint8_t aux_reg_val;

    aux_reg_addr = PROXIMITY11_SYS_CTRL;
    proximity11_get( ctx, aux_reg_addr, &aux_reg_val, 1 );

    if ( ( aux_reg_val & 0x3F ) != 0x0A ) 
    {
        return 1;
    }
    aux_reg_addr = PROXIMITY11_MANUFACT_ID;
    proximity11_get( ctx, aux_reg_addr, &aux_reg_val, 1 );

    if ( aux_reg_val != 0xE0 ) 
    {
        return 1;
    }

    aux_reg_addr = PROXIMITY11_MODE_CTRL;
    aux_reg_val = 0xC6;
    proximity11_set( ctx, aux_reg_addr, &aux_reg_val, 1 );

    aux_reg_addr = PROXIMITY11_ALS_PS_CTRL;
    aux_reg_val = 0x03;
    proximity11_set( ctx, aux_reg_addr, &aux_reg_val, 1 );

    aux_reg_addr = PROXIMITY11_PS_CTRL;
    aux_reg_val = 0x00;
    proximity11_set( ctx, aux_reg_addr, &aux_reg_val, 1 );

    proximity11_update( ctx );

    return 0;
}

void proximity11_generic_write ( proximity11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proximity11_generic_read ( proximity11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t proximity11_int_get ( proximity11_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t proximity11_get ( proximity11_t *ctx, uint8_t register_address, uint8_t * output_buffer, uint8_t n_bytes )
{
    if ( n_bytes > 22 )
    {
        return 1;
    } 

    proximity11_generic_read( ctx, register_address, output_buffer, n_bytes );

    return 0;
}

uint8_t proximity11_set ( proximity11_t *ctx, uint8_t register_address, uint8_t * input_buffer, uint8_t n_bytes )
{
    if ( n_bytes > 22 ) 
    {
        return 1;
    }

    proximity11_generic_write( ctx, register_address, input_buffer, n_bytes );

    return 0;
}

void proximity11_update ( proximity11_t *ctx )
{
    uint8_t aux_reg_addr;
    uint8_t aux_reg_val;
    
    uint8_t index;
    uint8_t als_gain_table[ 5 ] = { 1, 2, 64, 128 };
    uint16_t als_meas_time_table[ 17 ] = { 0, 0, 0, 0, 0, 100, 100, 100, 400, 400, 400, 400, 50, 0, 0, 0 };
    
    aux_reg_addr = PROXIMITY11_MODE_CTRL;
    proximity11_get( ctx, aux_reg_addr, &aux_reg_val, 1 );
    
    index = aux_reg_val & 0x0F;
    ctx->als.als_measure_time = als_meas_time_table[ index ];

    aux_reg_addr = PROXIMITY11_ALS_PS_CTRL;
    proximity11_get( ctx, aux_reg_addr, &aux_reg_val, 1 );

    index = ( aux_reg_val >> 4 ) & 0x03;
    ctx->als.als_data0_gain = als_gain_table[ index ];

    index = ( aux_reg_val >> 2 ) & 0x03;
    ctx->als.als_data1_gain = als_gain_table[ index ];
}

float proximity11_convert_lx ( proximity11_t *ctx, uint16_t *input_data )
{
    float lx;
    float d0;
    float d1;
    float d1_d0;

    if ( ctx->als.als_data0_gain == 0 )
    {
        return ( -1.0 );
    }

    if ( ctx->als.als_data1_gain == 0 )
    {
        return ( -1.0 );
    }

    if ( ctx->als.als_measure_time == 0 )
    {
        return ( -1.0 );
    } 
    else if ( ctx->als.als_measure_time == 50 )
    {
        if ( ( input_data[ 0 ] & 0x8000 ) == 0x8000 )
        {
            input_data[ 0 ] = 0x7FFF;
        }
        if ( ( input_data[ 1 ] & 0x8000 ) == 0x8000 )
        {
            input_data[ 1 ] = 0x7FFF;
        }
    }

    d0  = ( float )( input_data[ 0 ] );
    d0 *= ( float )( 100.0 / ctx->als.als_measure_time  );
    d0 /= ( float )( ctx->als.als_data0_gain);
    
    d1  = ( float )( input_data[ 1 ] );
    d1 *= ( float )( 100.0 / ctx->als.als_measure_time );
    d1 /= ( float )( ctx->als.als_data1_gain );
    

    if ( d0 == 0.0 )
    {
        lx = 0.0;
        return ( lx );
    }

    d1_d0 = d1 / d0;

    if ( d1_d0 < 0.595 )
    {
        lx = ( 1.682 * d0 - 1.877 * d1 );
    }
    else if ( d1_d0 < 1.015 )
    {
        lx = ( 0.644 * d0 - 0.132 * d1 );
    }
    else if ( d1_d0 < 1.352 )
    {
        lx = ( 0.756 * d0 - 0.243 * d1 );
    }
    else if ( d1_d0 < 3.053 )
    {
        lx = ( 0.766 * d0 - 0.25 * d1 );
    }
    else
    {
        lx = 0.0;
    }

    return ( lx );
}

void proximity11_get_raw_ps_als_values ( proximity11_t *ctx, uint8_t *data_buffer )
{
    uint8_t aux_reg_addr;

    aux_reg_addr = PROXIMITY11_PS_DATA_LSB;
    proximity11_get( ctx, aux_reg_addr, data_buffer, 6 );
}

void proximity11_get_ps_als_values ( proximity11_t *ctx, uint16_t *ps_value, float *als_value )
{
    uint8_t ps_als_values[ 6 ];
    uint16_t raw_ps;
    uint16_t raw_als[ 2 ];

    proximity11_get_raw_ps_als_values( ctx, ps_als_values );

    raw_ps     = ( ( uint16_t )ps_als_values[ 1 ] << 8 ) | ps_als_values[ 0 ];
    raw_als[ 0 ] = ( ( uint16_t )ps_als_values[ 3 ] << 8 ) | ps_als_values[ 2 ];
    raw_als[ 1 ] = ( ( uint16_t )ps_als_values[ 5 ] << 8 ) | ps_als_values[ 4 ];

    *ps_value  = raw_ps;
    *als_value = proximity11_convert_lx( ctx, raw_als );
}

uint8_t proximity11_set_ps_threshold_high ( proximity11_t *ctx, uint16_t threshold_value )
{
    uint8_t aux_buffer[ 2 ];
    
    if ( threshold_value > 4095 ) 
    {
        return 1;
    }

    aux_buffer[ 0 ] = ( uint8_t )( threshold_value );
    aux_buffer[ 1 ] = ( uint8_t )( threshold_value >> 8 );
    
    proximity11_set( ctx, PROXIMITY11_PS_TH_LSB, aux_buffer, 2 );
    
    return 0;
}

uint8_t proximity11_set_ps_threshold_low ( proximity11_t *ctx, uint16_t threshold_value )
{
    uint8_t aux_buffer[ 2 ];
    
    if ( threshold_value > 4095 ) 
    {
        return 1;
    }

    aux_buffer[ 0 ] = ( uint8_t )( threshold_value );
    aux_buffer[ 1 ] = ( uint8_t )( threshold_value >> 8 );

    proximity11_set( ctx, PROXIMITY11_PS_TL_LSB, aux_buffer, 2 );
    
    return 0;
}

void proximity11_set_als_threshold_high ( proximity11_t *ctx, uint16_t threshold_value )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = ( uint8_t )( threshold_value );
    aux_buffer[ 1 ] = ( uint8_t )( threshold_value >> 8 );

    proximity11_set( ctx, PROXIMITY11_ALS_DATA0_TH_LSB, aux_buffer, 2 );
}

void proximity11_set_als_threshold_low ( proximity11_t *ctx, uint16_t threshold_value )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = ( uint8_t )( threshold_value );
    aux_buffer[ 1 ] = ( uint8_t )( threshold_value >> 8 );

    proximity11_set( ctx, PROXIMITY11_ALS_DATA0_TL_LSB, aux_buffer, 2 );
}

uint8_t proximity11_set_ps_offset ( proximity11_t *ctx, uint16_t offset_value )
{
    uint8_t aux_buffer[ 2 ];

    if ( offset_value > 1023 ) 
    {
        return 1;
    }
    
    aux_buffer[ 0 ] = ( uint8_t )( offset_value );
    aux_buffer[ 1 ] = ( uint8_t )( offset_value >> 8 );

    proximity11_set( ctx, PROXIMITY11_PS_OFFSET_LSB, aux_buffer, 2 );
    
    return 0;
}

// ------------------------------------------------------------------------- END

