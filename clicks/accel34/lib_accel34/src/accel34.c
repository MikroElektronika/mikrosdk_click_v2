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
 * @file accel34.c
 * @brief Accel 34 Click Driver.
 */

#include "accel34.h"

void accel34_cfg_setup ( accel34_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int0 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL34_DEVICE_ADDRESS_0;
}

err_t accel34_init ( accel34_t *ctx, accel34_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int0, cfg->int0 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return I2C_MASTER_SUCCESS;
}

err_t accel34_default_cfg ( accel34_t *ctx ) 
{
    err_t error_flag = ACCEL34_OK;
    if ( ACCEL34_ERROR == accel34_check_communication ( ctx ) )
    {
        return ACCEL34_ERROR;
    }
    error_flag |= accel34_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= accel34_write_reg ( ctx, ACCEL34_REG_DIG_EN, ACCEL34_DIG_EN_MODE_CHANNEL_EN_ALL );
    error_flag |= accel34_set_op_mode ( ctx, ACCEL34_OP_MODE_HP );
    error_flag |= accel34_set_accel_fsr ( ctx, ACCEL34_ACCEL_FSR_15G );
    Delay_100ms ( );
    return error_flag;
}

err_t accel34_write_regs ( accel34_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t accel34_read_regs ( accel34_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t accel34_write_reg ( accel34_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel34_write_regs ( ctx, reg, &data_in, 1 );
}

err_t accel34_read_reg ( accel34_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel34_read_regs ( ctx, reg, data_out, 1 );
}

uint8_t accel34_get_int0_pin ( accel34_t *ctx )
{
    return digital_in_read ( &ctx->int0 );
}

uint8_t accel34_get_int1_pin ( accel34_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

err_t accel34_check_communication ( accel34_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ACCEL34_OK == accel34_read_regs ( ctx, ACCEL34_REG_DEVID_AD, data_buf, 2 ) )
    {
        if ( ( ACCEL34_DEVID_AD == data_buf[ 0 ] ) && 
             ( ACCEL34_DEVID_MST == data_buf[ 1 ] ) )
        {
            return ACCEL34_OK;
        }
    }
    return ACCEL34_ERROR;
}

err_t accel34_reset_device ( accel34_t *ctx )
{
    return accel34_write_reg ( ctx, ACCEL34_REG_RESET, ACCEL34_RESET );
}

err_t accel34_set_op_mode ( accel34_t *ctx, uint8_t op_mode )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t reg_data = 0;
    if ( op_mode > ACCEL34_OP_MODE_HP_VLP )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_reg ( ctx, ACCEL34_REG_OP_MODE, &reg_data );
    }
    if ( ACCEL34_OK == error_flag )
    {
        reg_data &= ( ~ACCEL34_OP_MODE_MASK );
        reg_data |= ( op_mode & ACCEL34_OP_MODE_MASK );
        error_flag = accel34_write_reg ( ctx, ACCEL34_REG_OP_MODE, reg_data );
    }
    return error_flag;
}

err_t accel34_set_accel_fsr ( accel34_t *ctx, uint8_t fsr )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t reg_data = 0;
    if ( fsr > ACCEL34_ACCEL_FSR_60G )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_reg ( ctx, ACCEL34_REG_OP_MODE, &reg_data );
    }
    if ( ACCEL34_OK == error_flag )
    {
        reg_data &= ( ~ACCEL34_OP_MODE_RANGE_MASK );
        reg_data |= ( ( fsr << 6 ) & ACCEL34_OP_MODE_RANGE_MASK );
        ctx->accel_sens = ACCEL34_SCALE_FACTOR_LSB_PER_G / ( 1 << fsr );
        error_flag = accel34_write_reg ( ctx, ACCEL34_REG_OP_MODE, reg_data );
    }
    return error_flag;
}

err_t accel34_get_drdy ( accel34_t *ctx, uint8_t *drdy )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_reg ( ctx, ACCEL34_REG_STATUS3, &reg_data );
    }
    if ( ACCEL34_OK == error_flag )
    {
        *drdy = ( ACCEL34_STATUS3_DATA_READY & reg_data );
    }
    return error_flag;
}

err_t accel34_get_accel ( accel34_t *ctx, accel34_axes_t *accel )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL34_OK == error_flag )
    {
        if ( ACCEL34_STATUS3_DATA_READY != ( ACCEL34_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL34_DATA_NOT_READY;
        }
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_regs ( ctx, ACCEL34_REG_XDATA_H, data_buf, 6 );
    }
    if ( ACCEL34_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        accel->x = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 2 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 3 ];
        accel->y = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 4 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 5 ];
        accel->z = ( float ) raw_data / ctx->accel_sens;
    }
    return error_flag;
}

err_t accel34_get_temp ( accel34_t *ctx, float *temp )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL34_OK == error_flag )
    {
        if ( ACCEL34_STATUS3_DATA_READY != ( ACCEL34_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL34_DATA_NOT_READY;
        }
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_regs ( ctx, ACCEL34_REG_TDATA_H, data_buf, 2 );
    }
    if ( ACCEL34_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        raw_data >>= 4;
        *temp = ( float ) raw_data / ACCEL34_TEMP_SENS;
    }
    return error_flag;
}

err_t accel34_get_data ( accel34_t *ctx, accel34_data_t *data_out )
{
    err_t error_flag = ACCEL34_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 8 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == data_out )
    {
        error_flag = ACCEL34_ERROR;
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL34_OK == error_flag )
    {
        if ( ACCEL34_STATUS3_DATA_READY != ( ACCEL34_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL34_DATA_NOT_READY;
        }
    }
    if ( ACCEL34_OK == error_flag )
    {
        error_flag = accel34_read_regs ( ctx, ACCEL34_REG_XDATA_H, data_buf, 8 );
    }
    if ( ACCEL34_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        data_out->accel.x = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 2 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 3 ];
        data_out->accel.y = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 4 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 5 ];
        data_out->accel.z = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 6 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 7 ];
        raw_data >>= 4;
        data_out->temperature = ( float ) ( raw_data - ACCEL34_TEMP_OFFSET_LSB ) / ACCEL34_TEMP_SENS;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
