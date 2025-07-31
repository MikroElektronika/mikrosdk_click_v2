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
 * @file c3dhall13.c
 * @brief 3D Hall 13 Click Driver.
 */

#include "c3dhall13.h"

void c3dhall13_cfg_setup ( c3dhall13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL13_DEVICE_ADDRESS_0;
}

err_t c3dhall13_init ( c3dhall13_t *ctx, c3dhall13_cfg_t *cfg ) 
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

err_t c3dhall13_default_cfg ( c3dhall13_t *ctx ) 
{
    err_t error_flag = C3DHALL13_OK;
    if ( C3DHALL13_ERROR == c3dhall13_check_communication ( ctx ) )
    {
        return C3DHALL13_ERROR;
    }
    error_flag |= c3dhall13_write_register ( ctx, C3DHALL13_REG_DEVICE_CONFIG_1, 
                                             C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_32X | 
                                             C3DHALL13_DEVICE_CONFIG_1_I2C_RD_STANDARD );
    error_flag |= c3dhall13_write_register ( ctx, C3DHALL13_REG_SENSOR_CONFIG_1, 
                                             C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_XYZ );
    error_flag |= c3dhall13_write_register ( ctx, C3DHALL13_REG_SENSOR_CONFIG_2, 
                                             C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_XY_ANGLE | 
                                             C3DHALL13_SENSOR_CONFIG_2_X_Y_RANGE_40MT | 
                                             C3DHALL13_SENSOR_CONFIG_2_Z_RANGE_40MT );
    error_flag |= c3dhall13_write_register ( ctx, C3DHALL13_REG_INT_CONFIG_1, 
                                             C3DHALL13_INT_CONFIG_1_MASK_INT_DISABLE );
    error_flag |= c3dhall13_write_register ( ctx, C3DHALL13_REG_DEVICE_CONFIG_2, 
                                             C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_CONTINUOUS );
    return error_flag;
}

err_t c3dhall13_generic_write ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t c3dhall13_generic_read ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t c3dhall13_write_register ( c3dhall13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return c3dhall13_generic_write( ctx, reg, &data_in, 1 );
}

err_t c3dhall13_read_register ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return c3dhall13_generic_read( ctx, reg, data_out, 1 );
}

uint8_t c3dhall13_get_int_pin ( c3dhall13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t c3dhall13_check_communication ( c3dhall13_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( C3DHALL13_OK == c3dhall13_generic_read( ctx, C3DHALL13_REG_DEVICE_ID, data_buf, 3 ) )
    {
        if ( ( C3DHALL13_DEVICE_ID == ( data_buf[ 0 ] & C3DHALL13_DEVICE_ID_MASK ) ) && 
             ( C3DHALL13_MANUFACTURER_ID_LSB == data_buf[ 1 ] ) &&
             ( C3DHALL13_MANUFACTURER_ID_MSB == data_buf[ 2 ] ) )
        {
            return C3DHALL13_OK;
        }
    }
    return C3DHALL13_ERROR;
}

err_t c3dhall13_read_data ( c3dhall13_t *ctx, c3dhall13_data_t *data_out )
{
    uint8_t data_buf[ 12 ] = { 0 };
    uint8_t sensor_config[ 2 ] = { 0 };
    uint8_t temp_config = 0;
    int16_t raw_data = 0;
    err_t error_flag = c3dhall13_generic_read ( ctx, C3DHALL13_REG_T_RESULT_MSB, data_buf, 12 );
    if ( ( C3DHALL13_OK == error_flag ) && ( data_buf[ 8 ] & C3DHALL13_CONV_STATUS_DATA_READY ) )
    {
        error_flag |= c3dhall13_generic_read ( ctx, C3DHALL13_REG_SENSOR_CONFIG_1, sensor_config, 2 );
        if ( sensor_config[ 0 ] & C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_MASK )
        {
            data_out->magnitude = data_buf[ 11 ];
        }
        if ( sensor_config[ 1 ] & C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_MASK )
        {
            data_out->angle = ( ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 10 ] ) / C3DHALL13_ANGLE_RESOLUTION;
        }
        raw_data = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] );
        raw_data -= C3DHALL13_TEMP_ADC_T0;
        data_out->temperature = C3DHALL13_TEMP_SENS_T0 + raw_data / C3DHALL13_TEMP_ADC_RESOLUTION;
        raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        data_out->x_axis = ( float ) raw_data;
        raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        data_out->y_axis = ( float ) raw_data;
        raw_data = ( ( int16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
        data_out->z_axis = ( float ) raw_data;
        if ( sensor_config[ 1 ] & C3DHALL13_SENSOR_CONFIG_2_X_Y_RANGE_80MT )
        {
            data_out->x_axis /= C3DHALL13_XYZ_SENSITIVITY_80MT;
            data_out->y_axis /= C3DHALL13_XYZ_SENSITIVITY_80MT; 
        }
        else
        {
            data_out->x_axis /= C3DHALL13_XYZ_SENSITIVITY_40MT;
            data_out->y_axis /= C3DHALL13_XYZ_SENSITIVITY_40MT; 
        }
        if ( sensor_config[ 1 ] & C3DHALL13_SENSOR_CONFIG_2_Z_RANGE_80MT )
        {
            data_out->z_axis /= C3DHALL13_XYZ_SENSITIVITY_80MT;
        }
        else
        {
            data_out->z_axis /= C3DHALL13_XYZ_SENSITIVITY_40MT;
        }
        return error_flag;
    }
    return C3DHALL13_ERROR;
}

// ------------------------------------------------------------------------- END
