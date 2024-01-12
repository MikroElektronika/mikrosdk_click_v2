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
 * @file hbridge15.c
 * @brief H-Bridge 15 Click Driver.
 */

#include "hbridge15.h"

void hbridge15_cfg_setup ( hbridge15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ena = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE15_DEVICE_ADDRESS_00;
}

err_t hbridge15_init ( hbridge15_t *ctx, hbridge15_cfg_t *cfg ) 
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
    digital_out_init( &ctx->ena, cfg->ena );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t hbridge15_default_cfg ( hbridge15_t *ctx ) 
{
    err_t error_flag = HBRIDGE15_OK;
    
    hbridge15_reset_port_exp( ctx );
    error_flag |= hbridge15_write_reg ( ctx, HBRIDGE15_REG_CONFIGURATION, HBRIDGE15_PIN_MASK_FLT );
    error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_NONE, HBRIDGE15_PIN_MASK_ALL );
    error_flag |= hbridge15_set_sleep ( ctx, HBRIDGE15_SLEEP_STATE_OFF );
    error_flag |= hbridge15_set_out_state ( ctx, HBRIDGE15_DRIVE_MOTOR_FREEWHEEL );
    
    return error_flag;
}

err_t hbridge15_generic_write ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t hbridge15_generic_read ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void hbridge15_set_rst_pin ( hbridge15_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE15_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void hbridge15_set_ena_pin ( hbridge15_t *ctx, uint8_t pin_state )
{
    if ( HBRIDGE15_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->ena );
    }
    else
    {
        digital_out_low( &ctx->ena );
    }
}

uint8_t hbridge15_get_int_state ( hbridge15_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void hbridge15_reset_port_exp ( hbridge15_t *ctx )
{
    hbridge15_set_rst_pin( ctx, HBRIDGE15_PIN_STATE_LOW );
    Delay_100ms( );
    hbridge15_set_rst_pin( ctx, HBRIDGE15_PIN_STATE_HIGH );
    Delay_100ms( );
}

err_t hbridge15_write_reg ( hbridge15_t *ctx, uint8_t reg, uint8_t data_in )
{
    return hbridge15_generic_write( ctx, reg, &data_in, 1 );
}

err_t hbridge15_read_reg ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return hbridge15_generic_read( ctx, reg, data_out, 1 );
}

err_t hbridge15_set_pins ( hbridge15_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t error_flag = hbridge15_read_reg( ctx, HBRIDGE15_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        error_flag |= hbridge15_write_reg( ctx, HBRIDGE15_REG_OUTPUT_PORT, data_in );
    }
    return error_flag;
}

err_t hbridge15_set_sleep ( hbridge15_t *ctx, uint8_t sleep_state )
{
    err_t error_flag = HBRIDGE15_OK;
    
    if ( HBRIDGE15_SLEEP_STATE_ON == sleep_state )
    {
        error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_NONE, HBRIDGE15_PIN_MASK_SLP );
    }
    else
    {
        error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_SLP, HBRIDGE15_PIN_MASK_NONE );
    }
    
    return error_flag;
}

err_t hbridge15_set_out_state ( hbridge15_t *ctx, uint8_t out_state )
{
    err_t error_flag = HBRIDGE15_OK;
    
    switch ( out_state )
    {
        case ( HBRIDGE15_DRIVE_MOTOR_REVERSE ):
        {
            error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_EN_B | HBRIDGE15_PIN_MASK_EN_A | 
                                                    HBRIDGE15_PIN_MASK_M0, HBRIDGE15_PIN_MASK_DIR );
            break;
        }
        
        case ( HBRIDGE15_DRIVE_MOTOR_FORWARD ):
        {
            error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_EN_B | HBRIDGE15_PIN_MASK_EN_A | 
                                                    HBRIDGE15_PIN_MASK_DIR, HBRIDGE15_PIN_MASK_M0 );
            break;
        }
        
        case ( HBRIDGE15_DRIVE_MOTOR_BRAKE ):
        {
            error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_EN_B | HBRIDGE15_PIN_MASK_EN_A, 
                                                    HBRIDGE15_PIN_MASK_M0 | HBRIDGE15_PIN_MASK_DIR );
            break;
        }
        
        case ( HBRIDGE15_DRIVE_MOTOR_FREEWHEEL ):
        {
            error_flag |= hbridge15_set_pins ( ctx, HBRIDGE15_PIN_MASK_EN_B | HBRIDGE15_PIN_MASK_EN_A | 
                                                    HBRIDGE15_PIN_MASK_DIR | HBRIDGE15_PIN_MASK_M0, 
                                                    HBRIDGE15_PIN_MASK_NONE );
            break;
        }
        
        default:
        {
           error_flag = HBRIDGE15_ERROR;
           break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
