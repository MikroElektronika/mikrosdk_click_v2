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
 * @file hbridge16.c
 * @brief H-Bridge 16 Click Driver.
 */

#include "hbridge16.h"

void hbridge16_cfg_setup ( hbridge16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE16_DEVICE_ADDRESS_A1A0_00;
}

err_t hbridge16_init ( hbridge16_t *ctx, hbridge16_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->slp, cfg->slp );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t hbridge16_default_cfg ( hbridge16_t *ctx ) 
{
    err_t error_flag = HBRIDGE16_OK;
    
    hbridge16_reset_port_exp ( ctx );
    
    hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_ON );
    hbridge16_set_mode ( ctx, HBRIDGE16_PH_EN_MODE );
    error_flag |= hbridge16_write_reg( ctx, HBRIDGE16_REG_CONFIG, HBRIDGE16_FLT_PIN );
    error_flag |= hbridge16_set_out_state( ctx, HBRIDGE16_DRIVE_MOTOR_FORWARD );
    hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_OFF );

    return error_flag;
}

err_t hbridge16_generic_write ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t hbridge16_generic_read ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t hbridge16_write_reg ( hbridge16_t *ctx, uint8_t reg, uint8_t data_in )
{
    return hbridge16_generic_write( ctx, reg, &data_in, 1 );
}

err_t hbridge16_read_reg ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return hbridge16_generic_read( ctx, reg, data_out, 1 );
}

uint8_t hbridge16_get_int_pin ( hbridge16_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void hbridge16_set_slp_pin ( hbridge16_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE16_SLEEP_MODE_OFF == pin_state )
    {
        digital_out_high( &ctx->slp );
    }
    else
    {
        digital_out_low( &ctx->slp );
    }
}

void hbridge16_reset_port_exp ( hbridge16_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t hbridge16_set_pins ( hbridge16_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = hbridge16_read_reg( ctx, HBRIDGE16_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= hbridge16_write_reg( ctx, HBRIDGE16_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t hbridge16_set_mode ( hbridge16_t *ctx, uint8_t mode_sel )
{
    err_t error_flag = HBRIDGE16_OK;
    
    if ( HBRIDGE16_PWM_MODE == mode_sel )
    {
        error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_MD_PIN, HBRIDGE16_NONE_PIN );
    }
    else
    {
        error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_NONE_PIN, HBRIDGE16_MD_PIN );
    }
    
    return error_flag; 
}

err_t hbridge16_set_out_state ( hbridge16_t *ctx, uint8_t out_state )
{
    err_t error_flag = HBRIDGE16_OK;
    uint8_t mode_flg = 0;
    
    error_flag |= hbridge16_read_reg( ctx, HBRIDGE16_REG_OUTPUT_PORT, &mode_flg );
    
    switch ( out_state )
    {
        case ( HBRIDGE16_DRIVE_MOTOR_REVERSE ):
        {
            if ( HBRIDGE16_MD_PIN & mode_flg )
            {
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN, 
                                                        HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN );
            }
            else
            {
                hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_OFF );
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN, 
                                                        HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN );
            }
            break;
        }
        
        case ( HBRIDGE16_DRIVE_MOTOR_FORWARD ):
        {
            if ( HBRIDGE16_MD_PIN & mode_flg )
            {
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN, 
                                                        HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN );
            }
            else
            {
                hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_OFF );
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN |  
                                                        HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN, HBRIDGE16_NONE_PIN );
            }
            break;
        }
        
        case ( HBRIDGE16_DRIVE_MOTOR_BRAKE ):
        {
            if ( HBRIDGE16_MD_PIN & mode_flg )
            {
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN | 
                                                        HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN, HBRIDGE16_NONE_PIN );
            }
            else
            {
                hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_OFF );
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_NONE_PIN, HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN );
            }
            break;
        }
        
        case ( HBRIDGE16_DRIVE_MOTOR_FREEWHEEL ):
        {
            if ( HBRIDGE16_MD_PIN & mode_flg )
            {
                error_flag |= hbridge16_set_pins ( ctx, HBRIDGE16_NONE_PIN, HBRIDGE16_IN2_PIN | HBRIDGE16_IN4_PIN | 
                                                        HBRIDGE16_IN1_PIN | HBRIDGE16_IN3_PIN  );
            }
            else
            {
                hbridge16_set_slp_pin ( ctx, HBRIDGE16_SLEEP_MODE_ON );
            }
            break;
        }
        
        default:
        {
           error_flag = HBRIDGE16_ERROR;
           break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
