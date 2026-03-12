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
 * @file thermo10.c
 * @brief Thermo 10 Click Driver.
 */

#include "thermo10.h"

void thermo10_cfg_setup ( thermo10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO10_DEVICE_ADDRESS_A2A1A0_000;
}

err_t thermo10_init ( thermo10_t *ctx, thermo10_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->alert, cfg->alert );
    Delay_100ms ( );

    thermo10_enable_device ( ctx );

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

err_t thermo10_default_cfg ( thermo10_t *ctx ) 
{
    err_t error_flag = THERMO10_OK;
    
    error_flag |= thermo10_set_config ( ctx, THERMO10_CONF_CONV_TIME_110_MS | 
                                             THERMO10_CONF_FAULT_QUEUE_2 | 
                                             THERMO10_CONF_POL_ACTIVE_LOW | 
                                             THERMO10_CONF_THERMOSTAT_MODE_COMP | 
                                             THERMO10_CONF_SHUTDOWN_MODE_SHUTDOWN );
    error_flag |= thermo10_set_high_limit ( ctx, THERMO10_TEMP_LIMIT_HIGH );
    error_flag |= thermo10_set_low_limit ( ctx, THERMO10_TEMP_LIMIT_LOW );
    error_flag |= thermo10_start_measurement ( ctx, THERMO10_MEASUREMENT_MODE_CONT_110_MS );

    return error_flag;
}

err_t thermo10_set_config ( thermo10_t *ctx, uint8_t config ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_CONF;
    data_buf[ 1 ] = config;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t thermo10_get_config ( thermo10_t *ctx, uint8_t *config ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_CONF;
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 1, config, 1 );
}

err_t thermo10_get_temp_raw ( thermo10_t *ctx, int16_t *temp_raw ) 
{
    err_t error_flag = THERMO10_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_TEMP;
    error_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp_raw ) )
    {
        *temp_raw = data_buf[ 1 ];
        *temp_raw <<= 8;
        *temp_raw |= data_buf[ 2 ];
        *temp_raw >>= 4;
    }
    return error_flag;
}

err_t thermo10_get_temp ( thermo10_t *ctx, float *temp ) 
{
    err_t error_flag = THERMO10_OK;
    int16_t temp_raw = 0;
    error_flag = thermo10_get_temp_raw( ctx, &temp_raw );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp ) )
    {
        *temp = temp_raw * THERMO10_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t thermo10_set_high_limit_raw ( thermo10_t *ctx, int16_t temp_high_raw ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_THIGH;
    data_buf[ 1 ] = ( uint8_t ) ( ( temp_high_raw >> 4 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( temp_high_raw << 4 ) & 0xF0 );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo10_set_low_limit_raw ( thermo10_t *ctx, int16_t temp_low_raw ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_TLOW;
    data_buf[ 1 ] = ( uint8_t ) ( ( temp_low_raw >> 4 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( temp_low_raw << 4 ) & 0xF0 );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo10_set_high_limit ( thermo10_t *ctx, float temp_high ) 
{
    int16_t temp_high_raw = temp_high / THERMO10_DATA_RESOLUTION;
    return thermo10_set_high_limit_raw( ctx, temp_high_raw );
}

err_t thermo10_set_low_limit ( thermo10_t *ctx, float temp_low ) 
{
    int16_t temp_low_raw = temp_low / THERMO10_DATA_RESOLUTION;
    return thermo10_set_low_limit_raw( ctx, temp_low_raw );
}

err_t thermo10_get_high_limit_raw ( thermo10_t *ctx, int16_t *temp_high_raw ) 
{
    err_t error_flag = THERMO10_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_THIGH;
    error_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp_high_raw ) )
    {
        *temp_high_raw = data_buf[ 1 ];
        *temp_high_raw <<= 8;
        *temp_high_raw |= data_buf[ 2 ];
        *temp_high_raw >>= 4;
    }
    return error_flag;
}

err_t thermo10_get_low_limit_raw ( thermo10_t *ctx, int16_t *temp_low_raw ) 
{
    err_t error_flag = THERMO10_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO10_REG_TLOW;
    error_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp_low_raw ) )
    {
        *temp_low_raw = data_buf[ 1 ];
        *temp_low_raw <<= 8;
        *temp_low_raw |= data_buf[ 2 ];
        *temp_low_raw >>= 4;
    }
    return error_flag;
}

err_t thermo10_get_high_limit ( thermo10_t *ctx, float *temp_high ) 
{
    err_t error_flag = THERMO10_OK;
    int16_t temp_high_raw = 0;
    error_flag = thermo10_get_high_limit_raw( ctx, &temp_high_raw );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp_high ) )
    {
        *temp_high = temp_high_raw * THERMO10_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t thermo10_get_low_limit ( thermo10_t *ctx, float *temp_low ) 
{
    err_t error_flag = THERMO10_OK;
    int16_t temp_low_raw = 0;
    error_flag = thermo10_get_low_limit_raw( ctx, &temp_low_raw );
    if ( ( THERMO10_OK == error_flag ) && ( NULL != temp_low ) )
    {
        *temp_low = temp_low_raw * THERMO10_DATA_RESOLUTION;
    }
    return error_flag;
}

void thermo10_enable_device ( thermo10_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void thermo10_disable_device ( thermo10_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

uint8_t thermo10_get_alert_pin ( thermo10_t *ctx )
{
    return !!digital_in_read ( &ctx->alert );
}

err_t thermo10_start_measurement ( thermo10_t *ctx, uint8_t mode )
{
    err_t error_flag = THERMO10_OK;
    uint8_t config = 0;
    if ( mode > THERMO10_MEASUREMENT_MODE_CONT_220_MS )
    {
        return THERMO10_ERROR;
    }
    error_flag |= thermo10_get_config ( ctx, &config );
    if ( THERMO10_OK == error_flag )
    {
        if ( THERMO10_MEASUREMENT_MODE_ONE_SHOT == mode )
        {
            config |= THERMO10_CONF_SHUTDOWN_MODE_SHUTDOWN;
            config |= THERMO10_CONF_ONE_SHOT;
            error_flag |= thermo10_set_config ( ctx, config );
        }
        else
        {
            config &= ( ~( THERMO10_CONF_SHUTDOWN_MODE_MASK | 
                           THERMO10_CONF_ONE_SHOT | 
                           THERMO10_CONF_CONV_TIME_MASK ) );
            config |= THERMO10_CONF_SHUTDOWN_MODE_CONTINUOUS;
            config |= ( ( mode - 1 ) << 5 );
            error_flag |= thermo10_set_config ( ctx, config );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
