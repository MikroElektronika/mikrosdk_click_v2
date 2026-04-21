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
 * @file thermo32.c
 * @brief Thermo 32 Click Driver.
 */

#include "thermo32.h"

void thermo32_cfg_setup ( thermo32_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO32_DEVICE_ADDRESS_GND;
}

err_t thermo32_init ( thermo32_t *ctx, thermo32_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alert, cfg->alert );

    return I2C_MASTER_SUCCESS;
}

err_t thermo32_default_cfg ( thermo32_t *ctx ) 
{
    err_t error_flag = THERMO32_OK;
    
    error_flag |= thermo32_set_config ( ctx, THERMO32_CONFIGURATION_CONV_RATE_1_HZ | 
                                             THERMO32_CONFIGURATION_THERMOSTAT_INT | 
                                             THERMO32_CONFIGURATION_MODE_SHUTDOWN | 
                                             THERMO32_CONFIGURATION_POLARITY_LOW | 
                                             THERMO32_CONFIGURATION_HYS_1C );
    error_flag |= thermo32_set_high_limit ( ctx, THERMO32_TEMP_LIMIT_HIGH );
    error_flag |= thermo32_set_low_limit ( ctx, THERMO32_TEMP_LIMIT_LOW );
    error_flag |= thermo32_start_measurement ( ctx, THERMO32_MEASUREMENT_MODE_CONT_1_HZ );

    return error_flag;
}

err_t thermo32_set_config ( thermo32_t *ctx, uint16_t config ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_CONFIGURATION;
    data_buf[ 1 ] = ( uint8_t ) ( ( config >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( config & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo32_get_config ( thermo32_t *ctx, uint16_t *config ) 
{
    err_t error_flag = THERMO32_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_CONFIGURATION;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != config ) )
    {
        *config = data_buf[ 1 ];
        *config <<= 8;
        *config |= data_buf[ 2 ];
    }
    return error_flag;
}

err_t thermo32_get_temp_raw ( thermo32_t *ctx, int16_t *temp_raw ) 
{
    err_t error_flag = THERMO32_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_TEMPERATURE;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp_raw ) )
    {
        *temp_raw = data_buf[ 1 ];
        *temp_raw <<= 8;
        *temp_raw |= data_buf[ 2 ];
        *temp_raw >>= 4;
    }
    return error_flag;
}

err_t thermo32_get_temp ( thermo32_t *ctx, float *temp ) 
{
    err_t error_flag = THERMO32_OK;
    int16_t temp_raw = 0;
    error_flag = thermo32_get_temp_raw( ctx, &temp_raw );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp ) )
    {
        *temp = temp_raw * THERMO32_TEMP_RESOLUTION;
    }
    return error_flag;
}

err_t thermo32_set_high_limit_raw ( thermo32_t *ctx, int16_t temp_high_raw ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_THIGH;
    data_buf[ 1 ] = ( uint8_t ) ( ( temp_high_raw >> 4 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( temp_high_raw << 4 ) & 0xF0 );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo32_set_low_limit_raw ( thermo32_t *ctx, int16_t temp_low_raw ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_TLOW;
    data_buf[ 1 ] = ( uint8_t ) ( ( temp_low_raw >> 4 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( temp_low_raw << 4 ) & 0xF0 );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo32_set_high_limit ( thermo32_t *ctx, float temp_high ) 
{
    int16_t temp_high_raw = temp_high / THERMO32_TEMP_RESOLUTION;
    return thermo32_set_high_limit_raw( ctx, temp_high_raw );
}

err_t thermo32_set_low_limit ( thermo32_t *ctx, float temp_low ) 
{
    int16_t temp_low_raw = temp_low / THERMO32_TEMP_RESOLUTION;
    return thermo32_set_low_limit_raw( ctx, temp_low_raw );
}

err_t thermo32_get_high_limit_raw ( thermo32_t *ctx, int16_t *temp_high_raw ) 
{
    err_t error_flag = THERMO32_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_THIGH;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp_high_raw ) )
    {
        *temp_high_raw = data_buf[ 1 ];
        *temp_high_raw <<= 8;
        *temp_high_raw |= data_buf[ 2 ];
        *temp_high_raw >>= 4;
    }
    return error_flag;
}

err_t thermo32_get_low_limit_raw ( thermo32_t *ctx, int16_t *temp_low_raw ) 
{
    err_t error_flag = THERMO32_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO32_REG_TLOW;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp_low_raw ) )
    {
        *temp_low_raw = data_buf[ 1 ];
        *temp_low_raw <<= 8;
        *temp_low_raw |= data_buf[ 2 ];
        *temp_low_raw >>= 4;
    }
    return error_flag;
}

err_t thermo32_get_high_limit ( thermo32_t *ctx, float *temp_high ) 
{
    err_t error_flag = THERMO32_OK;
    int16_t temp_high_raw = 0;
    error_flag = thermo32_get_high_limit_raw( ctx, &temp_high_raw );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp_high ) )
    {
        *temp_high = temp_high_raw * THERMO32_TEMP_RESOLUTION;
    }
    return error_flag;
}

err_t thermo32_get_low_limit ( thermo32_t *ctx, float *temp_low ) 
{
    err_t error_flag = THERMO32_OK;
    int16_t temp_low_raw = 0;
    error_flag = thermo32_get_low_limit_raw( ctx, &temp_low_raw );
    if ( ( THERMO32_OK == error_flag ) && ( NULL != temp_low ) )
    {
        *temp_low = temp_low_raw * THERMO32_TEMP_RESOLUTION;
    }
    return error_flag;
}

uint8_t thermo32_get_alert_pin ( thermo32_t *ctx )
{
    return !!digital_in_read ( &ctx->alert );
}

err_t thermo32_clear_alert ( thermo32_t *ctx )
{
    return thermo32_get_config ( ctx, NULL );
}

err_t thermo32_start_measurement ( thermo32_t *ctx, uint8_t mode )
{
    err_t error_flag = THERMO32_OK;
    uint16_t config = 0;
    if ( mode > THERMO32_MEASUREMENT_MODE_CONT_16_HZ )
    {
        return THERMO32_ERROR;
    }
    error_flag |= thermo32_get_config ( ctx, &config );
    if ( THERMO32_OK == error_flag )
    {
        if ( THERMO32_MEASUREMENT_MODE_ONE_SHOT == mode )
        {
            config &= ( ~THERMO32_CONFIGURATION_MODE_MASK );
            config |= THERMO32_CONFIGURATION_MODE_ONE_SHOT;
            error_flag |= thermo32_set_config ( ctx, config );
        }
        else
        {
            config &= ( ~( THERMO32_CONFIGURATION_MODE_MASK | 
                           THERMO32_CONFIGURATION_CONV_RATE_MASK ) );
            config |= THERMO32_CONFIGURATION_MODE_CONTINUOUS;
            config |= ( ( ( uint16_t ) ( mode - 1 ) << 13 ) & THERMO32_CONFIGURATION_CONV_RATE_MASK );
            error_flag |= thermo32_set_config ( ctx, config );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
