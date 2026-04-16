/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file thermo31.c
 * @brief Thermo 31 Click Driver.
 */

#include "thermo31.h"

void thermo31_cfg_setup ( thermo31_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO31_DEVICE_ADDRESS;
}

err_t thermo31_init ( thermo31_t *ctx, thermo31_cfg_t *cfg ) 
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

err_t thermo31_default_cfg ( thermo31_t *ctx ) 
{
    err_t error_flag = THERMO31_OK;
    
    if ( THERMO31_ERROR == thermo31_check_communication ( ctx ) )
    {
        return THERMO31_ERROR;
    }
    error_flag |= thermo31_write_reg ( ctx, THERMO31_REG_CONFIGURATION, THERMO31_CONFIGURATION_FAULT_1 | 
                                                                        THERMO31_CONFIGURATION_POLARITY_HIGH | 
                                                                        THERMO31_CONFIGURATION_MODE_CONTINUOUS | 
                                                                        THERMO31_CONFIGURATION_CONV_RATE_0_25S | 
                                                                        THERMO31_CONFIGURATION_AVG_NO_AVG | 
                                                                        THERMO31_CONFIGURATION_RESERVED );

    return error_flag;
}

err_t thermo31_write_reg ( thermo31_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write ( &ctx->i2c, data_buf, 3 );
}

err_t thermo31_read_reg ( thermo31_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = THERMO31_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag |= i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( THERMO31_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t thermo31_check_communication ( thermo31_t *ctx )
{
    uint16_t device_id = 0;
    if ( THERMO31_OK == thermo31_read_reg ( ctx, THERMO31_REG_DEVICE_ID, &device_id ) )
    {
        if ( THERMO31_DEVICE_ID == ( device_id & THERMO31_DEVICE_ID_MASK ) )
        {
            return THERMO31_OK;
        }
    }
    return THERMO31_ERROR;
}

err_t thermo31_read_unique_id ( thermo31_t *ctx, uint16_t *unique_id )
{
    err_t error_flag = THERMO31_OK;
    uint16_t config = 0;
    uint16_t uid = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = thermo31_read_reg ( ctx, THERMO31_REG_CONFIGURATION, &config );
    if ( THERMO31_OK == error_flag )
    {
        error_flag = thermo31_write_reg ( ctx, THERMO31_REG_CONFIGURATION, THERMO31_CONFIGURATION_DEFAULT | 
                                                                           THERMO31_CONFIGURATION_MODE_SHUTDOWN );
    }
    for ( uint8_t cnt = 0; cnt < 3; cnt++ )
    {
        if ( THERMO31_OK == error_flag )
        {
            error_flag = thermo31_write_reg ( ctx, THERMO31_REG_UNIQUE_ID0 + cnt, uid );
        }
        if ( THERMO31_OK == error_flag )
        {
            error_flag = i2c_master_read ( &ctx->i2c, data_buf, 2 );
        }
        if ( THERMO31_OK == error_flag )
        {
            unique_id[ cnt ] = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        }
    }
    if ( THERMO31_OK == error_flag )
    {
        error_flag = thermo31_write_reg ( ctx, THERMO31_REG_CONFIGURATION, config );
    }
    return error_flag;
}

err_t thermo31_read_temperature ( thermo31_t *ctx, float *temperature )
{
    uint16_t raw_temp = 0;
    err_t error_flag = thermo31_read_reg ( ctx, THERMO31_REG_TEMP_RESULT, &raw_temp );
    if ( THERMO31_OK == error_flag )
    {
        *temperature = ( ( int16_t ) raw_temp ) * THERMO31_TEMP_RESOLUTION;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
