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

#include "proximity7.h"

// ------------------------------------------------------------------ VARIABLES

void proximity7_cfg_setup ( proximity7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY7_DEVICE_ADDRESS;

    cfg->dev_const.glass_attenuation = 0.49;
    cfg->dev_const.const_b = 1.862;
    cfg->dev_const.const_c = 0.746;
    cfg->dev_const.const_d = 1.291;
    cfg->dev_const.device_factor = 52.0;
}

PROXIMITY7_RETVAL proximity7_init ( proximity7_t *ctx, proximity7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    proximity7_set_constants( ctx, &cfg->dev_const );
   
    return PROXIMITY7_OK;
}

void proximity7_default_cfg ( proximity7_t *ctx )
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = 0x00;
    proximity7_generic_write( ctx, PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );

    Delay_100ms( );

    proximity7_set_als_integration_time( ctx, 400.0 );
    proximity7_set_proximity_integration_time( ctx, 2.73 );
    proximity7_set_wait_time( ctx, 2.73 );
    proximity7_set_proximity_pulse_count( ctx, 8 );

    write_buffer[ 0 ] = PROXIMITY7_LED_DRIVE_100mA |
                      PROXIMITY7_PROXIMITY_DIODE_CH1 |
                      PROXIMITY7_PROXIMITY_GAIN_1x |
                      PROXIMITY7_ALS_GAIN_8x;
    proximity7_generic_write( ctx, PROXIMITY7_GAIN_CONTROL | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );

    write_buffer[ 0 ] = PROXIMITY7_WAIT_ENA |
                      PROXIMITY7_PROXIMITY_ENA |
                      PROXIMITY7_ALS_ENA |
                      PROXIMITY7_POWER_ON;
   proximity7_generic_write( ctx, PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );
}

void proximity7_generic_write ( proximity7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proximity7_generic_read ( proximity7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t proximity7_set_als_integration_time( proximity7_t *ctx, float integration_time )
{
    uint8_t write_buffer[ 1 ];
    
    if ( integration_time >= 0.0 && integration_time <= 698.88 )
    {
        write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( integration_time / 2.73 ) ) );

        proximity7_generic_write( ctx, PROXIMITY7_ALS_ADC_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t proximity7_set_proximity_integration_time( proximity7_t *ctx, float integration_time )
{
    uint8_t write_buffer[ 1 ];

    if ( integration_time >= 0.0 && integration_time <= 698.88 )
    {
        write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( integration_time / 2.73 ) ) );

        proximity7_generic_write( ctx, PROXIMITY7_PROXIMITY_ADC_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t proximity7_set_wait_time( proximity7_t *ctx, float wait_time )
{
    uint8_t write_buffer[ 1 ];
    uint8_t wlong_bit[ 1 ];
    
    proximity7_generic_read( ctx, PROXIMITY7_CONFIGURATION | PROXIMITY7_REPEATED_BYTE, wlong_bit, 1 );
    wlong_bit[ 0 ] >>= 1;
    wlong_bit[ 0 ] &= 0x01;
    
    if ( wlong_bit[ 0 ] == 0 )
    {
        if ( ( wait_time >= 0.0 ) && ( wait_time <= 698.88 ) )
        {
            write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( wait_time / 2.73 ) ) );
            proximity7_generic_write( ctx, PROXIMITY7_WAIT_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if ( wlong_bit[ 0 ] == 1 )
    {
        if ( ( wait_time >= 32.76 ) && ( wait_time <= 8386.56 ) )
        {
            write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( wait_time / 32.76 ) ) );
            proximity7_generic_write( ctx, PROXIMITY7_WAIT_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void proximity7_set_low_alsCh0_threshold( proximity7_t *ctx, uint16_t low_als_ch0_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( low_als_ch0_threshold );
    write_buffer[ 1 ] = ( uint8_t )( low_als_ch0_threshold >> 8 );
    proximity7_generic_write( ctx, PROXIMITY7_LOW_ALS_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_high_alsCh0_threshold( proximity7_t *ctx, uint16_t high_als_ch0_threshold )
{
    uint8_t write_buffer[ 2 ];
    
    write_buffer[ 0 ] = ( uint8_t )( high_als_ch0_threshold );
    write_buffer[ 1 ] = ( uint8_t )( high_als_ch0_threshold >> 8 );
    proximity7_generic_write( ctx, PROXIMITY7_HIGH_ALS_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_low_proximity_threshold( proximity7_t *ctx, uint16_t low_proximity_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( low_proximity_threshold );
    write_buffer[ 1 ] = ( uint8_t )( low_proximity_threshold >> 8 );
    proximity7_generic_write( ctx, PROXIMITY7_LOW_PROXIMITY_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_high_proximity_threshold( proximity7_t *ctx, uint16_t high_proximity_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( high_proximity_threshold );
    write_buffer[ 1 ] = ( uint8_t )( high_proximity_threshold >> 8 );
    proximity7_generic_write( ctx, PROXIMITY7_HIGH_PROXIMITY_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_int_persistance( proximity7_t *ctx, uint16_t proximity_int_persistence, uint16_t als_int_persistence )
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = proximity_int_persistence | als_int_persistence;
    proximity7_generic_write( ctx, PROXIMITY7_INT_PIN_PERSISTANCE_FILTERS | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
}

void proximity7_set_proximity_pulse_count( proximity7_t *ctx, uint8_t proximity_pulse_count )
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = proximity_pulse_count;
    proximity7_generic_write( ctx, PROXIMITY7_PROXIMITY_PULSE_COUNT | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
}

uint16_t proximity7_get_als_data_ch0( proximity7_t *ctx )
{
    uint8_t register_buffer[ 2 ];
    uint16_t als_data_ch0;
    
    proximity7_generic_read( ctx, PROXIMITY7_CH0_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );
    
    als_data_ch0 = register_buffer[ 1 ];
    als_data_ch0 <<= 8;
    als_data_ch0 |= register_buffer[ 0 ];
    
    return als_data_ch0;
}

uint16_t proximity7_get_als_data_ch1( proximity7_t *ctx )
{
    uint8_t register_buffer[ 2 ];
    uint16_t als_data_ch1;

    proximity7_generic_read( ctx, PROXIMITY7_CH1_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );

    als_data_ch1 = register_buffer[ 1 ];
    als_data_ch1 <<= 8;
    als_data_ch1 |= register_buffer[ 0 ];

    return als_data_ch1;
}

uint16_t proximity7_get_proximity_data( proximity7_t *ctx )
{
    uint8_t register_buffer[ 2 ];
    uint16_t proximity_data;

    proximity7_generic_read( ctx, PROXIMITY7_PROXIMITY_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );

    proximity_data = register_buffer[ 1 ];
    proximity_data <<= 8;
    proximity_data |= register_buffer[ 0 ];

    return proximity_data;
}

uint8_t proximity7_set_proximity_offset( proximity7_t *ctx, uint8_t proximity_offset_sign, uint8_t proximity_offset_magnitude )
{
    uint8_t write_buffer[ 1 ];

    if ( proximity_offset_magnitude < 128 )
    {
        write_buffer[ 0 ] = proximity_offset_sign | proximity_offset_magnitude;

        proximity7_generic_write( ctx, PROXIMITY7_PROXIMITY_OFFSET | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

float proximity7_get_lux_level( proximity7_t *ctx )
{
    uint8_t register_buffer[ 4 ];
    uint16_t als_data_ch0;
    uint16_t als_data_ch1;

    float als_integration_time;
    float als_gain;
    float ir_adjusted_count1;
    float ir_adjusted_count2;
    float lux_per_count;
    float lux_level;

    proximity7_generic_read( ctx, PROXIMITY7_ALS_ADC_TIME | PROXIMITY7_REPEATED_BYTE, register_buffer, 1 );

    als_integration_time = ( 2.73 * ( 256 - register_buffer[ 0 ] ) );

    proximity7_generic_read( ctx, PROXIMITY7_GAIN_CONTROL | PROXIMITY7_REPEATED_BYTE, register_buffer, 1 );

    register_buffer[ 0 ] &= 0x03;

    if ( register_buffer[ 0 ] == 0 )
    {
        als_gain = 1.0;
    }
    else if ( register_buffer[ 0 ] == 1 )
    {
        als_gain = 8.0;
    }
    else if ( register_buffer[ 0 ] == 2 )
    {
        als_gain = 16.0;
    }
    else if ( register_buffer[ 0 ] == 3 )
    {
        als_gain = 120.0;
    }

    proximity7_generic_read( ctx, PROXIMITY7_CH0_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 4 );

    als_data_ch0 = register_buffer[ 1 ];
    als_data_ch0 <<= 8;
    als_data_ch0 |= register_buffer[ 0 ];
    
    als_data_ch1 = register_buffer[ 3 ];
    als_data_ch1 <<= 8;
    als_data_ch1 |= register_buffer[ 2 ];

    ir_adjusted_count1 = ( ( float )( als_data_ch0 ) - ( ctx->const_b * als_data_ch1 ) );
    ir_adjusted_count2 = ( ( ctx->const_c * als_data_ch0 ) - ( ctx->const_d * als_data_ch1 ) );
    lux_per_count      = (  ctx->glass_attenuation  * ctx->device_factor / ( als_integration_time * als_gain ) );
    
    if ( ir_adjusted_count1 > ir_adjusted_count2 )
    {
        lux_level = ( ir_adjusted_count1 * lux_per_count );
    }
    else
    {
        lux_level = ( ir_adjusted_count2 * lux_per_count );
    }

    return lux_level;
}

uint8_t proximity7_get_int( proximity7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void proximity7_set_constants( proximity7_t *ctx, proximity7_const_t *set_const_data )
{
    ctx->glass_attenuation = set_const_data->glass_attenuation;
    ctx->const_b = set_const_data->const_b;
    ctx->const_c = set_const_data->const_c;
    ctx->const_d = set_const_data->const_d;
    ctx->device_factor = set_const_data->device_factor;
}

// ------------------------------------------------------------------------- END

