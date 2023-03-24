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
 * @file accel24.c
 * @brief Accel 24 Click Driver.
 */

#include "accel24.h"

void accel24_cfg_setup ( accel24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL24_DEVICE_ADDRESS;
}

err_t accel24_init ( accel24_t *ctx, accel24_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t accel24_default_cfg ( accel24_t *ctx ) 
{
    err_t error_flag = ACCEL24_OK;
    if ( ACCEL24_ERROR == accel24_check_communication ( ctx ) )
    {
        return ACCEL24_ERROR;
    }
    error_flag |= accel24_soft_reset ( ctx );
    Delay_1sec ( );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_INT_CLR0, ACCEL24_INT_CLR0_ALL );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_INT_CLR1, ACCEL24_INT_CLR1_DRDYC );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_INT_MASK0, ACCEL24_INT_MASK0_NONE );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_INT_MASK1, ACCEL24_INT_MASK1_DRDYE );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_DETECTION, ACCEL24_DETECTION_SHTH_0p25G | 
                                                                       ACCEL24_DETECTION_SHC_8 | 
                                                                       ACCEL24_DETECTION_ORC_16 );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_CONTROL, ACCEL24_CONTROL_FSR_2G );
    error_flag |= accel24_set_full_scale_range ( ctx, ACCEL24_FSR_2G );
    return error_flag;
}

err_t accel24_generic_write ( accel24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( ( len > ACCEL24_REG_WHO_AM_I ) || ( reg > ACCEL24_REG_WHO_AM_I ) )
    {
        return ACCEL24_ERROR;
    }
    uint8_t data_buf[ 17 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t accel24_generic_read ( accel24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( len > ACCEL24_REG_WHO_AM_I ) || ( reg > ACCEL24_REG_WHO_AM_I ) )
    {
        return ACCEL24_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t accel24_write_register ( accel24_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel24_generic_write ( ctx, reg, &data_in, 1 );
}

err_t accel24_read_register ( accel24_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel24_generic_read ( ctx, reg, data_out, 1 );
}

err_t accel24_check_communication ( accel24_t *ctx )
{
    uint8_t who_am_i;
    if ( ACCEL24_OK == accel24_read_register ( ctx, ACCEL24_REG_WHO_AM_I, &who_am_i ) )
    {
        if ( ACCEL24_WHO_AM_I == ( who_am_i & ACCEL24_WHO_AM_I_MASK ) )
        {
            return ACCEL24_OK;
        }
    }
    return ACCEL24_ERROR;
}

uint8_t accel24_get_int_pin ( accel24_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t accel24_soft_reset ( accel24_t *ctx )
{
    return accel24_write_register ( ctx, ACCEL24_REG_INT_CLR1, ACCEL24_INT_CLR1_SW_RST );
}

err_t accel24_set_full_scale_range ( accel24_t *ctx, uint8_t fsr )
{
    if ( fsr > ACCEL24_FSR_8G )
    {
        return ACCEL24_ERROR;
    }
    err_t error_flag = ACCEL24_OK;
    uint8_t control;
    error_flag |= accel24_read_register ( ctx, ACCEL24_REG_CONTROL, &control );
    control &= ~ACCEL24_CONTROL_FSR_MASK;
    control |= ( fsr << 5 );
    error_flag |= accel24_write_register ( ctx, ACCEL24_REG_CONTROL, control );
    ctx->fsr_sens = ACCEL24_ACCEL_RESOLUTION / ( 2 << fsr );
    return error_flag;
}

err_t accel24_read_data ( accel24_t *ctx, accel24_data_t *data_out )
{
    uint8_t data_buf[ 7 ] = { 0 };
    if ( ACCEL24_ERROR == accel24_read_register ( ctx, ACCEL24_REG_INT_SRC1, data_buf ) )
    {
        return ACCEL24_ERROR;
    }
    if ( ACCEL24_INT_SRC1_DRDY != ( data_buf[ 0 ] & ACCEL24_INT_SRC1_DRDY ) )
    {
        return ACCEL24_ERROR;
    }
    if ( ACCEL24_ERROR == accel24_write_register ( ctx, ACCEL24_REG_INT_CLR1, ACCEL24_INT_CLR1_DRDYC ) )
    {
        return ACCEL24_ERROR;
    }
    if ( ACCEL24_ERROR == accel24_generic_read ( ctx, ACCEL24_REG_XOUT_MSB, data_buf, 7 ) )
    {
        return ACCEL24_ERROR;
    }
    int16_t raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    data_out->x = ( raw_data >> 4 ) / ctx->fsr_sens;
    raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    data_out->y = ( raw_data >> 4 ) / ctx->fsr_sens;
    raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
    data_out->z = ( raw_data >> 4 ) / ctx->fsr_sens;
    raw_data = ( ( int16_t ) data_buf[ 6 ] << 8 );
    data_out->temperature =  ( raw_data >> 8 ) * ACCEL24_TEMP_SENSITIVITY + ACCEL24_TEMP_NOMINAL;
    return ACCEL24_OK;
}

// ------------------------------------------------------------------------- END
