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

#include "thermostat.h"


void thermostat_cfg_setup ( thermostat_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->te   = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMOSTAT_I2C_ADDRESS_0;
}

THERMOSTAT_RETVAL thermostat_init ( thermostat_t *ctx, thermostat_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMOSTAT_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
//     i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->te, cfg->te );

    return THERMOSTAT_OK;
}

void thermostat_generic_write ( thermostat_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermostat_generic_read ( thermostat_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void thermostat_write_data( thermostat_t *ctx, uint8_t reg_address, uint16_t write_data )
{
    uint8_t buffer_write[ 2 ];

    buffer_write[ 0 ] = ( uint8_t) ( ( write_data & THERMOSTAT_MSB_BITS ) >> 8 );
    buffer_write[ 1 ] = ( uint8_t) ( write_data & THERMOSTAT_LSB_BITS );

    thermostat_generic_write( ctx, reg_address, buffer_write, 2 );
}

uint16_t thermostat_read_data( thermostat_t *ctx, uint8_t reg_address )
{
    uint8_t buffer_read[ 2 ];
  
    uint16_t result;
    
    thermostat_generic_read( ctx, reg_address, buffer_read, 2 );
    
    result = buffer_read[ 0 ];
    result <<= 8;
    result |= buffer_read [ 1 ];

    return result;
}

float thermostat_get_temperature( thermostat_t *ctx )
{
    uint8_t buffer_read[ 2 ];
    float result;

    thermostat_generic_read( ctx, THERMOSTAT_REG_TEMP_OUT, buffer_read, 2 );

    result = ( float ) buffer_read[ 0 ];
    result += ( ( float ) ( buffer_read [ 1 ] >> 7 ) ) * 0.5;
    
    if ( buffer_read[ 0 ] >= THERMOSTAT_CHECK_SIGN )
    {
        result *= -1.0;
    }
    return result;
}

float thermostat_convert_fahrenheit( thermostat_t *ctx, float temp_celsius )
{
    float result;

    result = temp_celsius;
    result *= THERMOSTAT_CALCULATE_COEF_MULT;
    result += THERMOSTAT_CALCULATE_COEF_PLUS;

    return result;
}

void thermostat_set_configuration( thermostat_t *ctx, uint16_t config_value )
{
    thermostat_write_data( ctx, THERMOSTAT_REG_CONFIG, config_value );
}

void thermostat_set_temp_hyst( thermostat_t *ctx, int8_t temp_hyst )
{
    uint16_t temp_data;
    
    temp_data = THERMOSTAT_START_RESULT;
    
    temp_data = ( uint16_t ) temp_hyst;
    temp_data <<= 8;
    
    if ( ( temp_hyst > THERMOSTAT_LOWER_LIMITS_TEMP ) && ( temp_hyst < THERMOSTAT_UPPER_LIMITS_TEMP ) )
    {
        digital_out_write( &ctx->rst, temp_hyst );
    }        
}

void thermostat_set_temp_ref( thermostat_t *ctx, int8_t temp_ref )
{
    uint8_t temp_data;

    temp_data = THERMOSTAT_START_RESULT;

    temp_data = ( uint16_t ) temp_ref;
    temp_data <<= 8;

    if ( ( temp_ref > THERMOSTAT_LOWER_LIMITS_TEMP ) && ( temp_ref < THERMOSTAT_UPPER_LIMITS_TEMP ) )
    {    
         digital_out_write( &ctx->rst, temp_ref );
    }
}

void thermostat_soft_reset( thermostat_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void thermostat_switch_on( thermostat_t *ctx )
{
    digital_out_high( &ctx->te );
}

void thermostat_switch_off( thermostat_t *ctx )
{
    digital_out_low( &ctx->te );
}

void thermostat_enable( thermostat_t *ctx )
{
     digital_out_high( &ctx->rst );
}

void thermostat_disable( thermostat_t *ctx )
{
    digital_out_low( &ctx->rst );
}

// ------------------------------------------------------------------------- END

