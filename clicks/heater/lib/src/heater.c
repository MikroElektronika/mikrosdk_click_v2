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

#include "heater.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heater_cfg_setup ( heater_cfg_t *cfg, heater_config_t  *cfg1)
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg1->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

    cfg1->dev_pwm_freq 	  = 5000;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HEATER_SLAVE_ADDRESS;
}

HEATER_RETVAL heater_init ( heater_t *ctx, heater_cfg_t *cfg, heater_config_t *cfg1  )
{
    i2c_master_config_t i2c_cfg;
    pwm_config_t  pwm_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    pwm_configure_default( &pwm_cfg );
    pwm_cfg.pin      = cfg1->pwm;
	pwm_cfg.freq_hz  = cfg1->dev_pwm_freq;

    ctx->pwm_freq = cfg1->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    { 
        return HEATER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    return HEATER_OK;
}

void heater_generic_write ( heater_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void heater_generic_read ( heater_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void heater_set_led1_status ( heater_t *ctx, uint8_t status )
{ 
    digital_out_write( &ctx->rst, status );   
}

void heater_set_led2_status ( heater_t *ctx, uint8_t status )
{
    digital_out_write( &ctx->cs, status );
}

uint16_t heater_read_data ( heater_t *ctx )
{
    uint16_t temp_data;
    uint8_t buf_data[ 2 ];

    i2c_master_write( &ctx->i2c, buf_data, 2 ); 
    
    temp_data = buf_data [ 0 ];
    temp_data <<= HEATER_SHIFT_DATA;
    temp_data |= buf_data[ 1 ];
    
    return temp_data;
}

float heater_read_mv ( heater_t *ctx )
{
    float temp_data;

    temp_data =  ( float ) heater_read_data( ctx );
    temp_data = ( temp_data * HEATER_ADC_VREF ) /  ( float ) HEATER_MV_RESOLUTION;

    return temp_data;
}

float heater_read_temp ( heater_t *ctx )
{
    float temp_data;

    temp_data = heater_read_mv( ctx );

    temp_data -= HEATER_TEMP_0;
    
    if ( temp_data >= 0 )
    {
        temp_data /= HEATER_TEMP_RESOLUTION;
    }
    else
    {
        temp_data *= HEATER_TEMP_RESOLUTION;
    }
    
    return temp_data;
}

void heater_set_duty_cycle ( heater_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void heater_pwm_stop ( heater_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void heater_pwm_start ( heater_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}


// ------------------------------------------------------------------------- END

