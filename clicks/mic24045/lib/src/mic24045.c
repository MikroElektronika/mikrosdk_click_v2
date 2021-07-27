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

#include "mic24045.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float dev_bit_to_float( uint8_t bit_value );
static uint8_t dev_float_to_bit ( float float_value );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mic24045_cfg_setup ( mic24045_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MIC24045_I2C_ADDRESS;
}

MIC24045_RETVAL mic24045_init ( mic24045_t *ctx, mic24045_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MIC24045_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );

    return MIC24045_OK;
}

void mic24045_generic_write ( mic24045_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void mic24045_generic_read ( mic24045_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void mic24045_set_vout ( mic24045_t *ctx, float v_out )
{
    uint8_t w_buffer;
    
    w_buffer = dev_float_to_bit( v_out );
    
    mic24045_generic_write( ctx, MIC24045_REG_VOUT, &w_buffer, 1 );
}

void mic24045_set_vout_decimal ( mic24045_t *ctx, uint8_t dec )
{
    mic24045_generic_write( ctx, MIC24045_REG_VOUT, &dec, 1 );
}

uint8_t mic24045_get_status ( mic24045_t *ctx )
{
    uint8_t status_val;
    
    status_val = 0;
    
    mic24045_generic_read( ctx, MIC24045_REG_STATUS, &status_val, 1 );
     
    return status_val;
}

float mic24045_get_vout ( mic24045_t *ctx )
{
    uint8_t r_buffer;
    float result;
    
    r_buffer = 0;
    
    mic24045_generic_read( ctx, MIC24045_REG_VOUT, &r_buffer, 1 );
    
    result = dev_bit_to_float( r_buffer );
    
    return result;
}

void mic24045_enable( mic24045_t *ctx )
{
    digital_out_high( &ctx->en );
}

void mic24045_disable( mic24045_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t mic24045_get_power_good_state( mic24045_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float dev_bit_to_float ( uint8_t bit_value )
{
    float float_value;
    
    float_value = 0;
    
    if ( bit_value >= 0 && bit_value <= 0x80 )
    {
        float_value = 0.640 + bit_value * 0.005;
        
        return float_value;
    }
    else if ( bit_value >= 0x81 && bit_value <= 0xC3 )
    {
        float_value = 1.290 + ( bit_value - 0x81 ) * 0.010;
            
        return float_value;
    }
    else if ( bit_value >= 0xC4 && bit_value <= 0xF4 )
    {
        float_value = 1.980 + ( bit_value - 0xC4 ) * 0.030;
        
        return float_value;
    }
    else if ( bit_value >= 0xF5 && bit_value <= 0xFF )
    {
        float_value = 4.750 + ( bit_value - 0xF5 ) * 0.050;
        
        return float_value;
    }
       
    return float_value;
}

static uint8_t dev_float_to_bit ( float float_value )
{
    uint8_t bit_value;
    
    bit_value = 0;
    
    if ( float_value >= 5.250 )
    {
        bit_value = 0xFF;
        
        return bit_value;
    }
    else if ( float_value >= 4.750 )
    {
       bit_value = 0xF5;
            
       while ( float_value > 4.750 )
       {
           bit_value++;
           float_value -= 0.050;
       }
            
       return bit_value;
    }
    else if ( float_value >= 3.420 )
    {
        bit_value = 0xF4;
            
        return bit_value;
    }
    else if ( float_value >= 1.980 )
    {
        bit_value = 0xC4;
        
        while ( float_value > 1.980 )
        {
            bit_value++;
            float_value -= 0.030;
        }
        
        return bit_value;
    }
    else if ( float_value >= 1.290 )
    {
        bit_value = 0x81;
        
        while ( float_value > 1.290 )
        {
            bit_value++;
            float_value -= 0.010;
        }
        
        return bit_value;
    }
    else if ( float_value >= 0.640 )
    {
        bit_value = 0x00;
        
        while ( float_value > 0.640 )
        {
             bit_value++;
             float_value -= 0.005;
        }
            
        return bit_value;
    }
       
    else
    {
        bit_value = 0x00;
    }
    
    return bit_value;
}

// ------------------------------------------------------------------------- END

