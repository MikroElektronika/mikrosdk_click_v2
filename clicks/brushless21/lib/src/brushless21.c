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
 * @file brushless21.c
 * @brief Brushless 21 Click Driver.
 */

#include "brushless21.h"

void brushless21_cfg_setup ( brushless21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->fg  = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS21_DEF_FREQ;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = BRUSHLESS21_SET_DEV_ADDR;
    
    cfg->drv_sel     = BRUSHLESS21_DRV_SEL_GPIO;
}

err_t brushless21_init ( brushless21_t *ctx, brushless21_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    if ( BRUSHLESS21_DRV_SEL_I2C == ctx->drv_sel ) 
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
    }
    else
    {
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

        // Input pins
        digital_in_init( &ctx->fg, cfg->fg );
    }
    // Output pins
    digital_out_init( &ctx->en, cfg->en );

    return PWM_SUCCESS;
}

err_t brushless21_default_cfg ( brushless21_t *ctx ) 
{
    err_t error_flag = BRUSHLESS21_OK;
    
    brushless21_disable_device ( ctx );
    Delay_100ms ( );
    brushless21_enable_device ( ctx );
    
    error_flag |= brushless21_set_duty_cycle ( ctx, 0.0 );
    if ( BRUSHLESS21_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        error_flag |= brushless21_set_direction ( ctx, BRUSHLESS21_DIR_FORWARD );
    }
    else
    {
        error_flag |= brushless21_pwm_start( ctx );
    }

    return error_flag;
}

err_t brushless21_pwm_stop ( brushless21_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless21_pwm_start ( brushless21_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t brushless21_set_duty_cycle ( brushless21_t *ctx, float duty_cycle ) 
{
    if ( BRUSHLESS21_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t reg_data = 0;
        if ( BRUSHLESS21_ERROR == brushless21_read_register ( ctx, BRUSHLESS21_REG_SPEED_AND_FG, &reg_data ) )
        {
            return BRUSHLESS21_ERROR;
        }
        reg_data &= ~BRUSHLESS21_I2C_DUTY_RESOLUTION;
        reg_data |= ( uint16_t ) ( BRUSHLESS21_I2C_DUTY_RESOLUTION * duty_cycle ) | BRUSHLESS21_DUTY_CONTROLLED_BY_I2C_BIT;
        return brushless21_write_register ( ctx, BRUSHLESS21_REG_SPEED_AND_FG, reg_data );
    }
    else
    {
        return pwm_set_duty( &ctx->pwm, duty_cycle );
    }
}

err_t brushless21_write_register ( brushless21_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t brushless21_read_register ( brushless21_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BRUSHLESS21_OK == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return BRUSHLESS21_OK;
    }
    return BRUSHLESS21_ERROR;
}

void brushless21_enable_device ( brushless21_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void brushless21_disable_device ( brushless21_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t brushless21_get_fg_pin ( brushless21_t *ctx )
{
    return digital_in_read ( &ctx->fg );
}

err_t brushless21_get_temperature ( brushless21_t *ctx, int8_t *temperature )
{
    uint16_t raw_data = 0;
    if ( BRUSHLESS21_OK == brushless21_read_register( ctx, BRUSHLESS21_REG_READBACK_TEMPERATURE, &raw_data ) )
    {
        *temperature = ( int16_t ) raw_data - BRUSHLESS21_TEMPERATURE_OFFSET;
        return BRUSHLESS21_OK;
    }
    return BRUSHLESS21_ERROR;
}

err_t brushless21_get_motor_speed ( brushless21_t *ctx, float *motor_speed_hz )
{
    uint16_t raw_data = 0;
    if ( BRUSHLESS21_OK == brushless21_read_register( ctx, BRUSHLESS21_REG_READBACK_MOTOR_SPEED, &raw_data ) )
    {
        *motor_speed_hz = raw_data * BRUSHLESS21_MOTOR_SPEED_HZ;
        return BRUSHLESS21_OK;
    }
    return BRUSHLESS21_ERROR;
}

err_t brushless21_get_vbb_voltage ( brushless21_t *ctx, float *vbb_voltage )
{
    uint16_t raw_data = 0;
    if ( BRUSHLESS21_OK == brushless21_read_register( ctx, BRUSHLESS21_REG_READBACK_VBB, &raw_data ) )
    {
        *vbb_voltage = ( float ) raw_data * BRUSHLESS21_VBB_MAX / BRUSHLESS21_VBB_RESOLUTION;
        return BRUSHLESS21_OK;
    }
    return BRUSHLESS21_ERROR;
}

err_t brushless21_set_direction ( brushless21_t *ctx, uint8_t direction )
{
    if ( direction > BRUSHLESS21_DIR_FORWARD )
    {
        return BRUSHLESS21_ERROR;
    }
    
    uint16_t reg_data = 0;
    if ( BRUSHLESS21_ERROR == brushless21_read_register ( ctx, BRUSHLESS21_REG_RATED_SPEED_DIR, &reg_data ) )
    {
        return BRUSHLESS21_ERROR;
    }
    reg_data &= ~( ( uint16_t ) 1 << 14 );
    reg_data |= ( ( uint16_t ) direction << 14 );
    return brushless21_write_register ( ctx, BRUSHLESS21_REG_RATED_SPEED_DIR, reg_data );
}

err_t brushless21_switch_direction ( brushless21_t *ctx )
{
    uint16_t reg_data = 0;
    if ( BRUSHLESS21_ERROR == brushless21_read_register ( ctx, BRUSHLESS21_REG_RATED_SPEED_DIR, &reg_data ) )
    {
        return BRUSHLESS21_ERROR;
    }
    reg_data ^= ( ( uint16_t ) 1 << 14 );
    return brushless21_write_register ( ctx, BRUSHLESS21_REG_RATED_SPEED_DIR, reg_data );
}

// ------------------------------------------------------------------------- END
