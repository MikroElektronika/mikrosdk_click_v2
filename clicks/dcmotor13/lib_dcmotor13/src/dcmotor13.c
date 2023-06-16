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
 * @file dcmotor13.c
 * @brief DC Motor 13 Click Driver.
 */

#include "dcmotor13.h"

void dcmotor13_cfg_setup ( dcmotor13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ai1 = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->bi1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR13_DEVICE_ADDRESS_A1A0_00;
}

err_t dcmotor13_init ( dcmotor13_t *ctx, dcmotor13_cfg_t *cfg ) 
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

    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->ai1, cfg->ai1 );
    digital_out_init( &ctx->bi1, cfg->bi1 );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t dcmotor13_default_cfg ( dcmotor13_t *ctx ) 
{
    err_t error_flag = DCMOTOR13_OK;
    
    dcmotor13_enable_device ( ctx );
    
    dcmotor13_reset_device ( ctx );
    
    // Configure AI2, BI2, TA1, TA2, TB1, and TB2 as OUTPUT, others as INPUT
    error_flag |= dcmotor13_write_register ( ctx, DCMOTOR13_REG_CONFIG, DCMOTOR13_DEFAULT_CONFIG );
    
    error_flag |= dcmotor13_set_outa_mode ( ctx, DCMOTOR13_MODE_SHORT_BRAKE );

    error_flag |= dcmotor13_set_outb_mode ( ctx, DCMOTOR13_MODE_SHORT_BRAKE );
    
    error_flag |= dcmotor13_set_outa_torque ( ctx, DCMOTOR13_TORQUE_100 );
    
    error_flag |= dcmotor13_set_outb_torque ( ctx, DCMOTOR13_TORQUE_100 );
    
    return error_flag;
}

err_t dcmotor13_write_register ( dcmotor13_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor13_read_register ( dcmotor13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void dcmotor13_enable_device ( dcmotor13_t *ctx )
{
    digital_out_high ( &ctx->slp );
}

void dcmotor13_disable_device ( dcmotor13_t *ctx )
{
    digital_out_low ( &ctx->slp );
}

void dcmotor13_reset_device ( dcmotor13_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t dcmotor13_get_int_pin ( dcmotor13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void dcmotor13_set_ai1_pin ( dcmotor13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ai1, state );
}

void dcmotor13_set_bi1_pin ( dcmotor13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->bi1, state );
}

err_t dcmotor13_get_lo_pin ( dcmotor13_t *ctx, uint8_t *pin_state )
{
    uint8_t reg_data;
    if ( DCMOTOR13_ERROR == dcmotor13_read_register ( ctx, DCMOTOR13_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR13_ERROR;
    }
    *pin_state = reg_data & DCMOTOR13_LO_PIN;
    return DCMOTOR13_OK;
}

err_t dcmotor13_set_outa_mode ( dcmotor13_t *ctx, uint8_t mode )
{
    if ( mode > DCMOTOR13_MODE_CW )
    {
        return DCMOTOR13_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR13_ERROR == dcmotor13_read_register ( ctx, DCMOTOR13_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR13_ERROR;
    }
    if ( DCMOTOR13_MODE_CW == mode )
    {
        dcmotor13_set_ai1_pin ( ctx, DCMOTOR13_PIN_HIGH_LEVEL );
    }
    else
    {
        dcmotor13_set_ai1_pin ( ctx, DCMOTOR13_PIN_LOW_LEVEL );
    }
    if ( DCMOTOR13_MODE_CCW == mode )
    {
        reg_data |= DCMOTOR13_AI2_PIN;
    }
    else
    {
        reg_data &= ~DCMOTOR13_AI2_PIN;
    }
    return dcmotor13_write_register ( ctx, DCMOTOR13_REG_OUTPUT, reg_data );
}

err_t dcmotor13_set_outb_mode ( dcmotor13_t *ctx, uint8_t mode )
{
    if ( mode > DCMOTOR13_MODE_CW )
    {
        return DCMOTOR13_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR13_ERROR == dcmotor13_read_register ( ctx, DCMOTOR13_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR13_ERROR;
    }
    if ( DCMOTOR13_MODE_CW == mode )
    {
        dcmotor13_set_bi1_pin ( ctx, DCMOTOR13_PIN_HIGH_LEVEL );
    }
    else
    {
        dcmotor13_set_bi1_pin ( ctx, DCMOTOR13_PIN_LOW_LEVEL );
    }
    if ( DCMOTOR13_MODE_CCW == mode )
    {
        reg_data |= DCMOTOR13_BI2_PIN;
    }
    else
    {
        reg_data &= ~DCMOTOR13_BI2_PIN;
    }
    return dcmotor13_write_register ( ctx, DCMOTOR13_REG_OUTPUT, reg_data );
}

err_t dcmotor13_set_outa_torque ( dcmotor13_t *ctx, uint8_t torque )
{
    if ( torque > DCMOTOR13_TORQUE_100 )
    {
        return DCMOTOR13_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR13_ERROR == dcmotor13_read_register ( ctx, DCMOTOR13_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR13_ERROR;
    }
    if ( DCMOTOR13_TORQUE_100 == torque )
    {
        reg_data &= ~DCMOTOR13_TA1_PIN;
        reg_data &= ~DCMOTOR13_TA2_PIN;
    }
    else if ( DCMOTOR13_TORQUE_71 == torque )
    {
        reg_data |= DCMOTOR13_TA1_PIN;
        reg_data &= ~DCMOTOR13_TA2_PIN;
    }
    else if ( DCMOTOR13_TORQUE_71 == torque )
    {
        reg_data &= ~DCMOTOR13_TA1_PIN;
        reg_data |= DCMOTOR13_TA2_PIN;
    }
    else
    {
        reg_data |= DCMOTOR13_TA1_PIN;
        reg_data |= DCMOTOR13_TA2_PIN;
    }
    return dcmotor13_write_register ( ctx, DCMOTOR13_REG_OUTPUT, reg_data );
}

err_t dcmotor13_set_outb_torque ( dcmotor13_t *ctx, uint8_t torque )
{
    if ( torque > DCMOTOR13_TORQUE_100 )
    {
        return DCMOTOR13_ERROR;
    }
    uint8_t reg_data;
    if ( DCMOTOR13_ERROR == dcmotor13_read_register ( ctx, DCMOTOR13_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR13_ERROR;
    }
    if ( DCMOTOR13_TORQUE_100 == torque )
    {
        reg_data &= ~DCMOTOR13_TB1_PIN;
        reg_data &= ~DCMOTOR13_TB2_PIN;
    }
    else if ( DCMOTOR13_TORQUE_71 == torque )
    {
        reg_data |= DCMOTOR13_TB1_PIN;
        reg_data &= ~DCMOTOR13_TB2_PIN;
    }
    else if ( DCMOTOR13_TORQUE_71 == torque )
    {
        reg_data &= ~DCMOTOR13_TB1_PIN;
        reg_data |= DCMOTOR13_TB2_PIN;
    }
    else
    {
        reg_data |= DCMOTOR13_TB1_PIN;
        reg_data |= DCMOTOR13_TB2_PIN;
    }
    return dcmotor13_write_register ( ctx, DCMOTOR13_REG_OUTPUT, reg_data );
}

// ------------------------------------------------------------------------- END
