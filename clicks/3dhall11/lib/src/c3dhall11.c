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
 * @file c3dhall11.c
 * @brief 3D Hall 11 Click Driver.
 */

#include "c3dhall11.h"

void c3dhall11_cfg_setup ( c3dhall11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL11_DEVICE_ADDRESS;
}

err_t c3dhall11_init ( c3dhall11_t *ctx, c3dhall11_cfg_t *cfg ) 
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

err_t c3dhall11_default_cfg ( c3dhall11_t *ctx ) 
{
    err_t error_flag = C3DHALL11_OK;
    if ( C3DHALL11_ERROR == c3dhall11_check_communication ( ctx ) )
    {
        return C3DHALL11_ERROR;
    }
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_DEVICE_CONFIG_1, C3DHALL11_CONV_AVG_32X | 
                                                                                 C3DHALL11_I2C_RD_STANDARD );
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_SENSOR_CONFIG_1, C3DHALL11_MAG_CH_EN_ENABLE_XYZ );
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_SENSOR_CONFIG_2, C3DHALL11_ANGLE_EN_XY_ANGLE | 
                                                                                 C3DHALL11_X_Y_RANGE_40mT | 
                                                                                 C3DHALL11_Z_RANGE_40mT );
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_T_CONFIG, C3DHALL11_T_CH_EN_ENABLE );
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_INT_CONFIG_1, C3DHALL11_MASK_INTB_DISABLE );
    error_flag |= c3dhall11_write_register ( ctx, C3DHALL11_REG_DEVICE_CONFIG_2, C3DHALL11_OPERATING_MODE_CONTINUOUS );
    return error_flag;
}

err_t c3dhall11_generic_write ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t c3dhall11_generic_read ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t c3dhall11_write_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t data_in )
{
    return c3dhall11_generic_write( ctx, reg, &data_in, 1 );
}

err_t c3dhall11_read_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return c3dhall11_generic_read( ctx, reg, data_out, 1 );
}

uint8_t c3dhall11_get_int_pin ( c3dhall11_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t c3dhall11_check_communication ( c3dhall11_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( C3DHALL11_OK == c3dhall11_generic_read( ctx, C3DHALL11_REG_DEVICE_ID, data_buf, 3 ) )
    {
        if ( ( C3DHALL11_DEVICE_ID == data_buf[ 0 ] ) && 
             ( C3DHALL11_MANUFACTURER_ID_LSB == data_buf[ 1 ] ) &&
             ( C3DHALL11_MANUFACTURER_ID_MSB == data_buf[ 2 ] ) )
        {
            return C3DHALL11_OK;
        }
    }
    return C3DHALL11_ERROR;
}

err_t c3dhall11_read_data ( c3dhall11_t *ctx, c3dhall11_data_t *data_out )
{
    uint8_t data_buf[ 12 ] = { 0 };
    err_t error_flag = c3dhall11_generic_read ( ctx, C3DHALL11_REG_T_MSB_RESULT, data_buf, 12 );
    if ( ( C3DHALL11_OK == error_flag ) && ( data_buf[ 8 ] & C3DHALL11_CONV_STATUS_DATA_READY ) )
    {
        uint8_t sensor_config[ 2 ] = { 0 };
        error_flag |= c3dhall11_generic_read ( ctx, C3DHALL11_REG_SENSOR_CONFIG_1, sensor_config, 2 );
        if ( sensor_config[ 0 ] & C3DHALL11_MAG_CH_EN_BIT_MASK )
        {
            data_out->magnitude = data_buf[ 11 ];
        }
        if ( sensor_config[ 1 ] & C3DHALL11_ANGLE_EN_BIT_MASK )
        {
            data_out->angle = ( ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 10 ] ) / C3DHALL11_ANGLE_RESOLUTION;
        }
        uint8_t temp_config = 0;
        error_flag |= c3dhall11_read_register ( ctx, C3DHALL11_REG_T_CONFIG, &temp_config );
        if ( temp_config & C3DHALL11_T_CH_EN_ENABLE )
        {
            data_out->temperature = C3DHALL11_TEMP_SENS_T0 + 
                                    ( ( int16_t ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) - C3DHALL11_TEMP_ADC_T0 ) 
                                    / C3DHALL11_TEMP_ADC_RESOLUTION;
        }
        data_out->x_axis = ( float ) ( ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ] );
        data_out->y_axis = ( float ) ( ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ] );
        data_out->z_axis = ( float ) ( ( ( int16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ] );
        if ( sensor_config[ 1 ] & C3DHALL11_X_Y_RANGE_80mT )
        {
            data_out->x_axis /= C3DHALL11_XYZ_SENSITIVITY_80mT;
            data_out->y_axis /= C3DHALL11_XYZ_SENSITIVITY_80mT; 
        }
        else
        {
            data_out->x_axis /= C3DHALL11_XYZ_SENSITIVITY_40mT;
            data_out->y_axis /= C3DHALL11_XYZ_SENSITIVITY_40mT; 
        }
        if ( sensor_config[ 1 ] & C3DHALL11_Z_RANGE_80mT )
        {
            data_out->z_axis /= C3DHALL11_XYZ_SENSITIVITY_80mT;
        }
        else
        {
            data_out->z_axis /= C3DHALL11_XYZ_SENSITIVITY_40mT;
        }
        return error_flag;
    }
    return C3DHALL11_ERROR;
}

// ------------------------------------------------------------------------- END
