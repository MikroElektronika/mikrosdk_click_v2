/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file brushless22.c
 * @brief Brushless 22 Click Driver.
 */

#include "brushless22.h"

void brushless22_cfg_setup ( brushless22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->ss  = HAL_PIN_NC;
    cfg->fg  = HAL_PIN_NC;
    cfg->rt  = HAL_PIN_NC;

    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address  = BRUSHLESS22_ADDR_A2A1A0_111;
    cfg->dev_pwm_freq = BRUSHLESS22_DEF_FREQ;
}

err_t brushless22_init ( brushless22_t *ctx, brushless22_cfg_t *cfg ) 
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
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->ss, cfg->ss );
    digital_out_init( &ctx->rt, cfg->rt );

    // Input pins
    digital_in_init( &ctx->fg, cfg->fg );

    return PWM_SUCCESS;
}

err_t brushless22_default_cfg ( brushless22_t *ctx ) 
{
    err_t error_flag = BRUSHLESS22_OK;
    
    brushless22_set_soft_start ( ctx );
    brushless22_set_normal_regulation ( ctx );
    brushless22_set_direction ( ctx, BRUSHLESS22_DIR_FORWARD );
    
    error_flag |= brushless22_set_slew_rate_resistance ( ctx, BRUSHLESS22_SLEW_RATE_RES_DEFAULT );
    error_flag |= brushless22_set_rprog ( ctx, BRUSHLESS22_RPROG_3900 );
    
    error_flag |= brushless22_set_duty_cycle ( ctx, 0.0 );
    error_flag |= brushless22_pwm_start( ctx );
    
    Delay_100ms( );

    return error_flag;
}

err_t brushless22_set_slew_rate_resistance ( brushless22_t *ctx, uint16_t res_ohm )
{
    if ( ( res_ohm < BRUSHLESS22_SLEW_RATE_RES_MIN ) || ( res_ohm > BRUSHLESS22_SLEW_RATE_RES_MAX ) )
    {
        return BRUSHLESS22_ERROR;
    }
    
    res_ohm = ( uint16_t ) ( ( ( float ) res_ohm / BRUSHLESS22_DIGIPOT_MAX_VALUE ) * 
                             BRUSHLESS22_DIGIPOT_RESOLUTION + BRUSHLESS22_ROUND_TO_NEAREST_INT );
    
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( res_ohm >> 8 ) & 0x01 ), ( uint8_t ) ( res_ohm & 0xFF ) };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t brushless22_set_rprog ( brushless22_t *ctx, uint16_t res_ohm )
{
    if ( ( BRUSHLESS22_RPROG_3900 != res_ohm ) && ( BRUSHLESS22_RPROG_24000 != res_ohm ) )
    {
        return BRUSHLESS22_ERROR;
    }
    
    res_ohm = ( uint16_t ) ( ( ( float ) res_ohm / BRUSHLESS22_DIGIPOT_MAX_VALUE ) * 
                             BRUSHLESS22_DIGIPOT_RESOLUTION + BRUSHLESS22_ROUND_TO_NEAREST_INT );
    
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( res_ohm >> 8 ) & 0x01 ), ( uint8_t ) ( res_ohm & 0xFF ) };
    data_buf[ 0 ] |= BRUSHLESS22_RPROG_ADDRESS;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t brushless22_set_duty_cycle ( brushless22_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless22_pwm_stop ( brushless22_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless22_pwm_start ( brushless22_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless22_set_strong_start ( brushless22_t *ctx )
{
    digital_out_low ( &ctx->ss );
}

void brushless22_set_soft_start ( brushless22_t *ctx )
{
    digital_out_high ( &ctx->ss );
}

void brushless22_set_direction ( brushless22_t *ctx, uint8_t dir ) 
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless22_switch_direction ( brushless22_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void brushless22_set_normal_regulation ( brushless22_t *ctx )
{
    digital_out_low ( &ctx->rt );
}

void brushless22_set_low_load_regulation ( brushless22_t *ctx )
{
    digital_out_high ( &ctx->rt );
}

uint8_t brushless22_get_fg_pin ( brushless22_t *ctx )
{
    return digital_in_read ( &ctx->fg );
}

// ------------------------------------------------------------------------- END
