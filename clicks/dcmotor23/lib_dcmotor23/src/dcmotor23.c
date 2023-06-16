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
 * @file dcmotor23.c
 * @brief DC Motor 23 Click Driver.
 */

#include "dcmotor23.h"

void dcmotor23_cfg_setup ( dcmotor23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en_a   = HAL_PIN_NC;
    cfg->slp   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en_b = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR23_DEVICE_ADDRESS_0;
}

err_t dcmotor23_init ( dcmotor23_t *ctx, dcmotor23_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en_a, cfg->en_a );
    digital_out_init( &ctx->en_b, cfg->en_b );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t dcmotor23_default_cfg ( dcmotor23_t *ctx ) 
{
    err_t err_flag = DCMOTOR23_OK;
    dcmotor23_normal_operation_mode ( ctx );
    dcmotor23_reset_device ( ctx );
    err_flag |= dcmotor23_write_register( ctx, DCMOTOR23_REG_CONFIG, DCMOTOR23_DEFAULT_CONFIG );
    err_flag |= dcmotor23_set_decay( ctx, DCMOTOR23_SEL_OUT_A );
    err_flag |= dcmotor23_set_decay( ctx, DCMOTOR23_SEL_OUT_B );
    err_flag |= dcmotor23_set_outa_torque( ctx, DCMOTOR23_TORQUE_100 );
    err_flag |= dcmotor23_set_outb_torque( ctx, DCMOTOR23_TORQUE_100 );
    return err_flag;
}

err_t dcmotor23_write_register ( dcmotor23_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor23_read_register ( dcmotor23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t dcmotor23_get_lo_pin ( dcmotor23_t *ctx, uint8_t *pin_state )
{
    uint8_t reg_data = 0;
    err_t err_flag = dcmotor23_read_register( ctx, DCMOTOR23_REG_OUTPUT, &reg_data );
    *pin_state = reg_data & DCMOTOR23_LO_PIN;
    return err_flag;
}

err_t dcmotor23_set_output_mode ( dcmotor23_t *ctx, uint8_t mode, uint8_t sel_motor )
{
    uint8_t reg_data = 0;
    err_t err_flag = dcmotor23_read_register ( ctx, DCMOTOR23_REG_OUTPUT, &reg_data );
    if ( mode > DCMOTOR23_MODE_CW )
    {
        err_flag = DCMOTOR23_ERROR;
    }

    if ( sel_motor == DCMOTOR23_SEL_OUT_A )
    {
        dcmotor23_set_en_a_pin( ctx, DCMOTOR23_PIN_HIGH_LEVEL );
        if ( DCMOTOR23_MODE_CW == mode )
        {
            reg_data |= DCMOTOR23_PHASE_A_PIN;
        }
        else if ( DCMOTOR23_MODE_CCW == mode )
        {
            reg_data &= ~DCMOTOR23_PHASE_A_PIN;
        }
        else
        {
            dcmotor23_set_en_a_pin( ctx, DCMOTOR23_PIN_LOW_LEVEL );    
        }    
    }

    if ( sel_motor == DCMOTOR23_SEL_OUT_B )
    {
        dcmotor23_set_en_b_pin( ctx, DCMOTOR23_PIN_HIGH_LEVEL );
        if ( DCMOTOR23_MODE_CW == mode )
        {
            reg_data |= DCMOTOR23_PHASE_B_PIN;
        }
        else if ( DCMOTOR23_MODE_CCW == mode )
        {
            reg_data &= ~DCMOTOR23_PHASE_B_PIN;
        }
        else
        {
            dcmotor23_set_en_b_pin( ctx, DCMOTOR23_PIN_LOW_LEVEL );    
        }    
    }
    err_flag |= dcmotor23_write_register( ctx, DCMOTOR23_REG_OUTPUT, reg_data );
    return err_flag;
}

err_t dcmotor23_set_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor )
{
    err_t err_flag = DCMOTOR23_OK;
    if ( sel_motor == DCMOTOR23_SEL_OUT_A )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_CW, DCMOTOR23_SEL_OUT_A );
    }
    else if ( sel_motor == DCMOTOR23_SEL_OUT_B )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_CW, DCMOTOR23_SEL_OUT_B ); 
    }
    else
    {
        err_flag = DCMOTOR23_ERROR;
    }
    return err_flag;
}

err_t dcmotor23_set_counter_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor )
{
    err_t err_flag = DCMOTOR23_OK;
    if ( sel_motor == DCMOTOR23_SEL_OUT_A )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_CCW, DCMOTOR23_SEL_OUT_A );
    }
    else if ( sel_motor == DCMOTOR23_SEL_OUT_B )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_CCW, DCMOTOR23_SEL_OUT_B );
    }
    else
    {
        err_flag = DCMOTOR23_ERROR;
    }
    return err_flag;
}

err_t dcmotor23_set_decay ( dcmotor23_t *ctx, uint8_t sel_motor )
{
    err_t err_flag = DCMOTOR23_OK;
    if ( sel_motor == DCMOTOR23_SEL_OUT_A )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_DECAY, DCMOTOR23_SEL_OUT_A );
    }
    else if ( sel_motor == DCMOTOR23_SEL_OUT_B )
    {
        err_flag = dcmotor23_set_output_mode( ctx, DCMOTOR23_MODE_DECAY, DCMOTOR23_SEL_OUT_B );    
    }
    else
    {
        err_flag = DCMOTOR23_ERROR;
    }
    return err_flag;
}

err_t dcmotor23_set_outa_torque ( dcmotor23_t *ctx, uint8_t torque )
{
    uint8_t reg_data;
    err_t err_flag = dcmotor23_read_register( ctx, DCMOTOR23_REG_OUTPUT, &reg_data );
    switch ( torque )
    {
        case DCMOTOR23_TORQUE_100:
        {
            reg_data &= ~DCMOTOR23_TRQ_A1_PIN;
            reg_data &= ~DCMOTOR23_TRQ_A2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_71:
        {
            reg_data |= DCMOTOR23_TRQ_A1_PIN;
            reg_data &= ~DCMOTOR23_TRQ_A2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_38: 
        {
            reg_data &= ~DCMOTOR23_TRQ_A1_PIN;
            reg_data |= DCMOTOR23_TRQ_A2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_0: 
        {
            reg_data |= DCMOTOR23_TRQ_A1_PIN;
            reg_data |= DCMOTOR23_TRQ_A2_PIN;
            break;
        }
        default: 
        {
            reg_data |= DCMOTOR23_TRQ_A1_PIN;
            reg_data |= DCMOTOR23_TRQ_A2_PIN;
            err_flag = DCMOTOR23_ERROR;
            break;
        }    
    }
    err_flag |= dcmotor23_write_register( ctx, DCMOTOR23_REG_OUTPUT, reg_data );
    return err_flag;
}

err_t dcmotor23_set_outb_torque ( dcmotor23_t *ctx, uint8_t torque )
{
    uint8_t reg_data;
    err_t err_flag = dcmotor23_read_register( ctx, DCMOTOR23_REG_OUTPUT, &reg_data );
    switch ( torque )
    {
        case DCMOTOR23_TORQUE_100:
        {
            reg_data &= ~DCMOTOR23_TRQ_B1_PIN;
            reg_data &= ~DCMOTOR23_TRQ_B2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_71:
        {
            reg_data |= DCMOTOR23_TRQ_B1_PIN;
            reg_data &= ~DCMOTOR23_TRQ_B2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_38: 
        {
            reg_data &= ~DCMOTOR23_TRQ_B1_PIN;
            reg_data |= DCMOTOR23_TRQ_B2_PIN;
            break;
        }
        case DCMOTOR23_TORQUE_0: 
        {
            reg_data |= DCMOTOR23_TRQ_B1_PIN;
            reg_data |= DCMOTOR23_TRQ_B2_PIN;
            break;
        }
        default: 
        {
            reg_data |= DCMOTOR23_TRQ_B1_PIN;
            reg_data |= DCMOTOR23_TRQ_B2_PIN;
            err_flag = DCMOTOR23_ERROR;
            break;
        }    
    }
    err_flag |= dcmotor23_write_register( ctx, DCMOTOR23_REG_OUTPUT, reg_data );
    return err_flag;
}

void dcmotor23_normal_operation_mode ( dcmotor23_t *ctx )
{
    digital_out_high( &ctx->slp );
}

void dcmotor23_sleep_mode ( dcmotor23_t *ctx )
{
    digital_out_low( &ctx->slp );
}

void dcmotor23_reset_device ( dcmotor23_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t dcmotor23_get_int_pin ( dcmotor23_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void dcmotor23_set_en_a_pin ( dcmotor23_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en_a, state );
}

void dcmotor23_set_en_b_pin ( dcmotor23_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en_b, state );
}

// ------------------------------------------------------------------------- END
