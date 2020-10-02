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

#include "temphum.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void calibration ( temphum_t *ctx );

float linear_hum_interpolation ( temphum_t *ctx );

float linear_temp_interpolation ( temphum_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum_cfg_setup ( temphum_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
 
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPANDHUM_I2C_ADDRESS;
}

TEMPHIM_RETVAL temphum_init ( temphum_t *ctx, temphum_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHIM_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPHIM_OK;
}

void temphum_default_cfg ( temphum_t *ctx )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = TEMPANDHUM_AV_CONF_DEFAULT_VALUE;
    temphum_generic_write( ctx, TEMPANDHUM_AV_CONF, w_buffer, 1 );

    w_buffer[ 0 ] = TEMPANDHUM_CTRL_REG1_DEFAULT_VALUE;
    temphum_generic_write( ctx, TEMPANDHUM_CTRL_REG1, w_buffer, 1 );

    w_buffer[ 0 ] = TEMPANDHUM_CTRL_REG2_DEFAULT_VALUE;
    temphum_generic_write( ctx, TEMPANDHUM_CTRL_REG2, w_buffer, 1 );

    w_buffer[ 0 ] = TEMPANDHUM_CTRL_REG3_DEFAULT_VALUE;
    temphum_generic_write( ctx, TEMPANDHUM_CTRL_REG3, w_buffer, 1 );
}

void temphum_generic_write ( temphum_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum_generic_read ( temphum_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

// Gets humidity data function

uint16_t temphum_get_hum_data ( temphum_t *ctx )
{
    uint16_t humidity;
    uint8_t hum_l;
    uint8_t hum_h;

    temphum_generic_read( ctx, TEMPANDHUM_HUMIDITY_OUT_L, &hum_l, 1 );

    temphum_generic_read( ctx, TEMPANDHUM_HUMIDITY_OUT_H, &hum_h, 1 );

    humidity = hum_h;
    humidity <<= 8;
    humidity |= hum_l;

    return humidity;
}

// Gets temperature data function

uint16_t temphum_get_temp_data( temphum_t *ctx )
{
    uint16_t temperature;
    uint8_t temp_l;
    uint8_t temp_h;

    temphum_generic_read( ctx, TEMPANDHUM_TEMP_OUT_L, &temp_l, 1 );

    temphum_generic_read( ctx, TEMPANDHUM_TEMP_OUT_H, &temp_h, 1 );

    temperature = temp_h;
    temperature <<= 8;
    temperature |= temp_l;

    return temperature;
}

// Gets temperature and humidity function

void temphum_get_temp_hum ( temphum_t *ctx, float *temperature, float *humidity )
{
    uint16_t h_out;
    uint16_t t_out;

    calibration( ctx );

    h_out = temphum_get_hum_data( ctx );
    
    t_out = temphum_get_temp_data( ctx );
    
    if ( h_out & 0x8000 )
        ctx->float_h_out = ( float ) ( ( -1.0 ) * ( 0x8000 - ( 0x7fff & h_out ) ) );

    if ( t_out & 0x8000 )
        ctx->float_t_out = ( float ) ( ( -1.0 ) * ( 0x8000 - ( 0x7fff & t_out ) ) );

    *temperature = linear_temp_interpolation( ctx );
    Delay_10ms( );
    *humidity = linear_hum_interpolation( ctx );
    Delay_10ms( );
    
    if ( *temperature > 120.0 )
        *temperature = 120.0;
    if ( *temperature < - 40.0 )
        *temperature = - 40.0;
    if ( *humidity > 100.0 )
        *humidity = 100.0;
    if ( *humidity < 0.0 )
        *humidity = 0.0;
}

// Gets temperature in degrees Celsius function

float temphum_get_temperature( temphum_t *ctx )
{
    float temperature;
    uint16_t temp_data;
    float temp1;
    float temp2;
    
    temp_data = temphum_get_temp_data( ctx );
    
    temp1 = ( float ) ( temp_data >> 4 );
    temp2 = ( float ) ( temp_data & 0x000F );
        
    temperature = temp1 * 0.8046 + ( temp2 / 100.0 );

    return temperature;
}

// Gets humidity percentage function

float temphum_get_humidity( temphum_t *ctx )
{
    float humidity;
    uint16_t hum_data;
    float hum1;
    float hum2;

    hum_data = temphum_get_hum_data( ctx );

    hum1 = ( float ) ( hum_data >> 1 );
    hum2 = ( float ) ( hum_data & 0x000F );

    humidity = hum1 * 0.002515 + ( hum2 / 100.0 );

    return humidity;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

float linear_temp_interpolation ( temphum_t *ctx )
{
    float a;
    float b;
    float cal;
    
    a = ( float ) ( ( ctx->t1_deg_c_cal - ctx->t0_deg_c_cal ) / ( ctx->t1_out - ctx->t0_out ) );
    b = ( float ) ( ( ( ( -1.0 ) * a ) * ctx->t0_out ) + ctx->t0_deg_c_cal );
    cal = ( float ) ( ( a * ctx->float_t_out ) + b );
   
    return cal;
}

 float linear_hum_interpolation ( temphum_t *ctx )
{
    float a;
    float b;
    float cal;

    a = ( float ) ( ( ctx->h1_rh_cal - ctx->h0_rh_cal ) / ( ctx->h1_t0_out - ctx->h0_t0_out ) );
    b = ( float ) ( ( ( ( -1.0 ) * a ) * ctx->h0_t0_out ) + ctx->h0_rh_cal );
    cal = ( float ) ( ( a *  ctx->float_h_out  ) + b );
   
    return cal;
}

void calibration ( temphum_t *ctx )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 16 ];
    
    w_buffer[ 0 ] = 0xB0;
    
    temphum_generic_read( ctx, w_buffer[ 0 ], r_buffer, 16 );
    
    ctx->h0_rh_x2 = r_buffer[ 0 ];
    ctx->h1_rh_x2 = r_buffer[ 1 ];
    ctx->t0_deg_c_x8 = ( ( r_buffer[ 5 ] & 0x03 ) << 8 ) + r_buffer[ 2 ];
    ctx->t1_deg_c_x8 = ( ( r_buffer[ 5 ] & 0x0C ) << 6 ) + r_buffer[ 3 ];

    ctx->h0_t0_out = ( r_buffer[ 7 ] << 8 ) + r_buffer[ 6 ];
    ctx->h1_t0_out = ( r_buffer[ 11 ] << 8 ) + r_buffer[ 10 ];
    ctx->t0_out = ( r_buffer[ 13 ] << 8 ) + r_buffer[ 12 ];
    ctx->t1_out = ( r_buffer[ 15 ] << 8 ) + r_buffer[ 14 ];

    if ( ctx->h0_t0_out & 0x8000 )
    {
        ctx->h0_t0_out = - ( 0x8000 - ( 0x7fff & ctx->h0_t0_out ) );
    }
    if ( ctx->h1_t0_out & 0x8000 )
    {
        ctx->h1_t0_out = - ( 0x8000 - ( 0x7fff & ctx->h1_t0_out ) );
    }
    if ( ctx->t0_out & 0x8000 )
    {
        ctx->t0_out = - ( 0x8000 - ( 0x7fff & ctx->t0_out ) );
    }
    if ( ctx->t1_out & 0x8000 )
    {
        ctx->t1_out = - ( 0x8000 - ( 0x7fff & ctx->t1_out ) );
    }
    ctx->t0_deg_c_cal = ( float ) ctx->t0_deg_c_x8 / 8.0;
    ctx->t1_deg_c_cal = ( float ) ctx->t1_deg_c_x8 / 8.0;
    ctx->h0_rh_cal = ( float ) ctx->h0_rh_x2 / 2.0;
    ctx->h1_rh_cal = ( float ) ctx->h1_rh_x2 / 2.0;
}


// ------------------------------------------------------------------------- END

