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
 * @file leddriver14.c
 * @brief LED Driver 14 Click Driver.
 */

#include "leddriver14.h"

void leddriver14_cfg_setup ( leddriver14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address_u2 = LEDDRIVER14_U2_ADDR_A2_VCC;
    cfg->i2c_address_u3 = LEDDRIVER14_U3_ADDR_A2_VCC;
    
    cfg->dev_pwm_freq = LEDDRIVER14_DEF_FREQ;
}

err_t leddriver14_init ( leddriver14_t *ctx, leddriver14_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address_u2 = cfg->i2c_address_u2;
    ctx->slave_address_u3 = cfg->i2c_address_u3;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_u2 ) ) 
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
    
    digital_out_init( &ctx->wp, cfg->wp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LEDDRIVER14_OK;
}

err_t leddriver14_default_cfg ( leddriver14_t *ctx ) 
{
    err_t error_flag = LEDDRIVER14_OK;
    
    leddriver14_rset_write_protect ( ctx, LEDDRIVER14_WRITE_PROTECT_DISABLE );
    
    error_flag |= leddriver14_set_rset ( ctx, LEDDRIVER14_RSET_1, LEDDRIVER14_RSET_RES_DEFAULT );
    error_flag |= leddriver14_set_rset ( ctx, LEDDRIVER14_RSET_2, LEDDRIVER14_RSET_RES_DEFAULT );
    error_flag |= leddriver14_set_rset ( ctx, LEDDRIVER14_RSET_3, LEDDRIVER14_RSET_RES_DEFAULT );
    error_flag |= leddriver14_set_rset ( ctx, LEDDRIVER14_RSET_4, LEDDRIVER14_RSET_RES_DEFAULT );
    
    error_flag |= leddriver14_set_duty_cycle ( ctx, 0.0 );
    error_flag |= leddriver14_pwm_start( ctx );
    
    return error_flag;
}

err_t leddriver14_set_rset ( leddriver14_t *ctx, uint8_t rset, uint16_t res_ohm )
{
    if ( ( rset > LEDDRIVER14_RSET_4 ) || ( res_ohm > LEDDRIVER14_RSET_RES_MAX ) )
    {
        return LEDDRIVER14_ERROR;
    }
    
    if ( rset < LEDDRIVER14_RSET_3 )
    {
        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_u2 ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    else
    {
        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_u3 ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    
    res_ohm = ( uint16_t ) ( ( ( float ) res_ohm / LEDDRIVER14_DIGIPOT_MAX_VALUE ) * 
                             LEDDRIVER14_DIGIPOT_RESOLUTION + LEDDRIVER14_ROUND_TO_NEAREST_INT );
    
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( res_ohm >> 8 ) & 0x01 ), ( uint8_t ) ( res_ohm & 0xFF ) };
    if ( rset % 2 )
    {
        data_buf[ 0 ] |= LEDDRIVER14_RSET1_AND_RSET3_ADDRESS;
    }
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

void leddriver14_rset_write_protect ( leddriver14_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

uint8_t leddriver14_get_int_pin ( leddriver14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t leddriver14_set_duty_cycle ( leddriver14_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t leddriver14_pwm_stop ( leddriver14_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t leddriver14_pwm_start ( leddriver14_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

// ------------------------------------------------------------------------- END
