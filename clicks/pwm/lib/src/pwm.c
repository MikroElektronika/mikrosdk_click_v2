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

#include "pwm.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pwm_cfg_setup ( pwm_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PWM_I2C_ADDRESS;
}

PWM_RETVAL pwm_init ( pwm_t *ctx, pwm_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PWM_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return PWM_OK;
}

void pwm_generic_write ( pwm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void pwm_generic_read ( pwm_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void pwm_set_all_raw ( pwm_t *ctx, uint16_t raw_dc )
{
    uint8_t w_buffer[ 5 ];

    if ( raw_dc > PWM_MAX_RESOLUTION )
    {
        raw_dc = PWM_MAX_RESOLUTION;
    }

    w_buffer[ 0 ] = PWM_ALL_CH_ON_L;
    w_buffer[ 1 ] = 0x00;
    w_buffer[ 2 ] = 0x00;
    w_buffer[ 3 ] = raw_dc & 0x00FF;
    w_buffer[ 4 ] = ( raw_dc & 0x0F00 ) >> 8;

    i2c_master_write( &ctx->i2c, w_buffer, 5 );   
}

void pwm_set_all ( pwm_t *ctx, uint8_t duty_cyc )
{
    uint16_t raw_dc;

    raw_dc = PWM_MAX_RESOLUTION / 100 * duty_cyc;
    pwm_set_all_raw( ctx, raw_dc );
}

void pwm_dev_config ( pwm_t *ctx, uint8_t *config )
{
    uint8_t config_buff;

    config_buff = 0x20;
    config_buff |= ( config[ 3 ] & 0x01 ) << 3;
    config_buff |= ( config[ 2 ] & 0x01 ) << 2;
    config_buff |= ( config[ 1 ] & 0x01 ) << 1;
    config_buff |= ( config[ 4 ] & 0x01 ) << 4;
    config_buff |= ( config[ 0 ] & 0x01 );
    config_buff |= ( config[ 5 ] & 0x01 ) << 7;
 
     pwm_generic_write( ctx, PWM_MODE1_REG, &config_buff, 1 );
}


void pwm_output_config ( pwm_t *ctx, uint8_t *config1 )
{
    uint8_t output_buff[ 1 ];

    if( config1[ 0 ] > 3 )
    {
        config1[ 0 ] = config1[0] % 3;
    }
    output_buff[ 0 ] = 0;
    output_buff[ 0 ] |= ( config1[0] & 0x03 );
    output_buff[ 0 ] |= ( config1[1] & 0x01 ) << 2;
    output_buff[ 0 ] |= ( config1[2] & 0x01 ) << 3;
    output_buff[ 0 ] |= ( config1[4] & 0x01 ) << 4;

   pwm_generic_write( ctx, PWM_MODE2_REG, output_buff, 1 );
}


void pwm_channel_state ( pwm_t *ctx, uint8_t chann_id, uint8_t state )
{
    uint8_t w_buffer[ 5 ];
    uint8_t r_buffer[ 5 ];

    if ( chann_id > 15 )
    {
        chann_id = chann_id % 15;
    }

    w_buffer[ 0 ] = chann_id * 4 + PWM_CH0_ON_L;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 4 );
   
    w_buffer[ 5 ] = r_buffer[ 4 ];
    w_buffer[ 4 ] = r_buffer[ 3 ];
    w_buffer[ 3 ] = r_buffer[ 2 ];
    w_buffer[ 2 ] = r_buffer[ 1 ];
    w_buffer[ 1 ] = r_buffer[ 0 ];
    w_buffer[ 0 ] = chann_id * 4 + PWM_CH0_ON_L;

    if ( state )
    {
        w_buffer[ 2 ] |= 0x10;
        w_buffer[ 4 ] &= 0xEF;
    }
    else
    {
        w_buffer[ 2 ] &= 0xEF;
        w_buffer[ 4 ] |= 0x10;
    }

    i2c_master_write( &ctx->i2c, w_buffer, 1 );   
}

void pwm_set_channel_raw ( pwm_t *ctx, uint8_t chann_id, uint16_t raw_off_set, uint16_t raw_dc )
{
    uint8_t w_buffer[ 5 ];
    uint16_t w_buffer_off;

    if ( ( chann_id > 15 ) || ( raw_off_set > PWM_MAX_RESOLUTION ) || ( raw_dc > PWM_MAX_RESOLUTION ) )
    {
        chann_id =  chann_id % 15;
        raw_off_set = PWM_MAX_RESOLUTION;
        raw_dc = PWM_MAX_RESOLUTION;
    }

    w_buffer_off = ( raw_off_set + raw_dc ) % PWM_MAX_RESOLUTION;
    w_buffer[ 0 ] = chann_id * 4 + PWM_CH0_ON_L;
    w_buffer[ 1 ] = raw_off_set & 0x00FF;
    w_buffer[ 2 ] = ( raw_off_set & 0x0F00 ) >> 8;
    w_buffer[ 3 ] = w_buffer_off & 0x00FF;
    w_buffer[ 4 ] = ( w_buffer_off  & 0x0F00 ) >> 8;

    i2c_master_write( &ctx->i2c, w_buffer, 5 ); 
}


void pwm_all_chann_state ( pwm_t *ctx, uint8_t state )
{
    uint8_t w_buffer[ 5 ];
    uint8_t r_buffer[ 5 ];

    w_buffer[ 0 ] = PWM_ALL_CH_ON_L;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 4 );

    w_buffer[ 5 ] = r_buffer[ 4 ];
    w_buffer[ 4 ] = r_buffer[ 3 ];
    w_buffer[ 3 ] = r_buffer[ 2 ];
    w_buffer[ 2 ] = r_buffer[ 1 ];
    w_buffer[ 1 ] = r_buffer[ 0 ];
    w_buffer[ 0 ] = PWM_ALL_CH_ON_L;

    if ( state )
    {
        w_buffer[ 2 ] |= 0x10;
        w_buffer[ 4 ] &= 0xEF;
    } 
    else 
    {
        w_buffer[ 2 ] &= 0xEF;
        w_buffer[ 4 ] |= 0x10;
    }

    i2c_master_write( &ctx->i2c, w_buffer, 5 );
}

void pwm_set_pre_scale ( pwm_t *ctx, uint8_t pre_scale )
{
    pwm_generic_write( ctx, PWM_PRE_SCALE, &pre_scale, 1 );
}

void pwm_set_output ( pwm_t *ctx, uint8_t en_out )
{
    if ( en_out == PWM_DISABLE )
    {
        digital_out_high( &ctx->rst );   
    }
    if ( en_out == PWM_ENABLE )
    {
        digital_out_low( &ctx->rst );
    }
}

// ------------------------------------------------------------------------- END

