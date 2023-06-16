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
 * @file smartbuck3.c
 * @brief Smart Buck 3 Click Driver.
 */

#include "smartbuck3.h"

void smartbuck3_cfg_setup ( smartbuck3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK3_DEVICE_ADDRESS;
}

err_t smartbuck3_init ( smartbuck3_t *ctx, smartbuck3_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck3_default_cfg ( smartbuck3_t *ctx ) 
{
    err_t error_flag = smartbuck3_set_voltage( ctx, SMARTBUCK3_VOUT_MIN );
    error_flag |= smartbuck3_set_operation_mode( ctx, SMARTBUCK3_OP_MODE_FORCED_PWM );
    error_flag |= smartbuck3_set_temperature_shutdown( ctx, SMARTBUCK3_TEMP_TS_ENABLE );
    return error_flag;
}

err_t smartbuck3_generic_write ( smartbuck3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t smartbuck3_generic_read ( smartbuck3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t smartbuck3_set_voltage ( smartbuck3_t *ctx, uint16_t vout_mv ) 
{
    err_t err_flag;
    if ( vout_mv < SMARTBUCK3_VOUT_MIN || ( vout_mv > SMARTBUCK3_VOUT_MAX ) )
    {
        err_flag = SMARTBUCK3_ERROR;
    }
    else
    {
        uint8_t data_buf;
        err_flag = smartbuck3_generic_read( ctx, SMARTBUCK3_REG_SET1, &data_buf, 1 );
        data_buf &= SMARTBUCK3_MOD_BIT_MASK;
        data_buf |= ( uint8_t ) ( ( vout_mv - 500 ) / 10 );
        err_flag |= smartbuck3_generic_write( ctx, SMARTBUCK3_REG_SET1, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartbuck3_get_voltage ( smartbuck3_t *ctx, uint16_t *vout_mv ) 
{
    err_t err_flag;
    uint8_t data_buf;
    err_flag = smartbuck3_generic_read( ctx, SMARTBUCK3_REG_SET1, &data_buf, 1 );
    data_buf &= SMARTBUCK3_OV_BIT_MASK;
    *vout_mv = ( uint16_t ) data_buf;
    *vout_mv *= 10;
    *vout_mv += 500;
    return err_flag;
}

err_t smartbuck3_set_operation_mode ( smartbuck3_t *ctx, uint8_t op_mode ) 
{
    uint8_t data_buf;
    err_t err_flag = smartbuck3_get_operation_mode( ctx, &data_buf );
    data_buf &= SMARTBUCK3_OV_BIT_MASK;
    if ( op_mode == SMARTBUCK3_OP_MODE_FORCED_PWM )
    {
        data_buf |= SMARTBUCK3_OP_MODE_FORCED_PWM;
    }
    err_flag |= smartbuck3_generic_write( ctx, SMARTBUCK3_REG_SET1, &data_buf, 1 );
    return err_flag;
}

err_t smartbuck3_get_operation_mode ( smartbuck3_t *ctx, uint8_t *op_mode ) 
{
    err_t err_flag = smartbuck3_generic_read( ctx, SMARTBUCK3_REG_SET1, op_mode, 1 );
    *op_mode &= SMARTBUCK3_OV_BIT_MASK;
    return err_flag;
}

err_t smartbuck3_set_temperature_shutdown ( smartbuck3_t *ctx, uint8_t temp_enable ) 
{
    uint8_t data_buf;
    err_t err_flag = smartbuck3_generic_read( ctx, SMARTBUCK3_REG_TEMP, &data_buf, 1 );
    data_buf &= SMARTBUCK3_TEMP_DIS_BIT_MASK;
    if ( temp_enable == SMARTBUCK3_TEMP_TS_DISABLE )
    {
        data_buf |= SMARTBUCK3_TEMP_TS_DISABLE;
    }
    err_flag |= smartbuck3_generic_write( ctx, SMARTBUCK3_REG_TEMP, &data_buf, 1 );
    return err_flag;
}

uint8_t smartbuck3_check_temperature_warning ( smartbuck3_t *ctx ) 
{
    uint8_t data_buf;
    if ( SMARTBUCK3_OK == smartbuck3_generic_read( ctx, SMARTBUCK3_REG_TEMP, &data_buf, 1 ) )
    {
         data_buf &= SMARTBUCK3_TEMP_TJEW;
         data_buf >>= 1;
    }
    else
    {
        data_buf = SMARTBUCK3_TEMP_ERROR;
    }
    return data_buf;
}

err_t smartbuck3_set_voltage_ramp_timing ( smartbuck3_t *ctx, uint8_t slope ) 
{
    uint8_t data_buf;
    err_t err_flag;
    if ( slope > SMARTBUCK3_VTG_RAMP_T_0_25mVns )
    {
        err_flag = SMARTBUCK3_ERROR;
    }
    else
    {
        err_flag = smartbuck3_generic_read( ctx, SMARTBUCK3_REG_RMPCTRL, &data_buf, 1 );
        data_buf &= SMARTBUCK3_VTG_RAMP_T_BIT_MASK;
        data_buf |= ( slope << 5 );
        err_flag |= smartbuck3_generic_write( ctx, SMARTBUCK3_REG_RMPCTRL, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartbuck3_get_device_id ( smartbuck3_t *ctx, uint8_t *device_id ) 
{
    return smartbuck3_generic_read ( ctx, SMARTBUCK3_REG_CHIP_ID_0, device_id, 1 );
}

// ------------------------------------------------------------------------- END
