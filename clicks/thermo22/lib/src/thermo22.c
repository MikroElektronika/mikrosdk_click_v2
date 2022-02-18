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
 * @file thermo22.c
 * @brief Thermo 22 Click Driver.
 */

#include "thermo22.h"

void thermo22_cfg_setup ( thermo22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = THERMO22_DEV_ADDR_A2A1A0_111;
}

err_t thermo22_init ( thermo22_t *ctx, thermo22_cfg_t *cfg ) 
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

err_t thermo22_default_cfg ( thermo22_t *ctx ) 
{
    err_t error_flag = THERMO22_OK;
    error_flag |= thermo22_write_config ( ctx, THERMO22_CONFIG_ONESHOT_DIS | 
                                               THERMO22_CONFIG_FAULT_QUEUE_1 | 
                                               THERMO22_CONFIG_ALERT_ACTIVE_LOW | 
                                               THERMO22_CONFIG_ALERT_COMPARATOR | 
                                               THERMO22_CONFIG_SHUTDOWN_DIS );
    error_flag |= thermo22_set_temperature_low_limit ( ctx, THERMO22_TEMPERATURE_ALERT_LIMIT );
    error_flag |= thermo22_set_temperature_high_limit ( ctx, THERMO22_TEMPERATURE_ALERT_LIMIT );
    Delay_100ms ( );
    return error_flag;
}

err_t thermo22_write_config ( thermo22_t *ctx, uint8_t config )
{
    uint8_t data_buf[ 2 ] = { THERMO22_REG_CONFIGURATION, config };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t thermo22_read_config ( thermo22_t *ctx, uint8_t *config )
{
    uint8_t reg_addr = THERMO22_REG_CONFIGURATION;
    return i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, config, 1 );
}

err_t thermo22_read_temperature ( thermo22_t *ctx, float *temperature )
{
    uint8_t reg_addr = THERMO22_REG_TEMPERATURE;
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buf, 2 );
    int16_t raw_temp = ( int16_t ) ( ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) >> 4;
    *temperature = raw_temp * THERMO22_TEMPERATURE_RESOLUTION;
    return error_flag;
}

err_t thermo22_start_oneshot_conversion ( thermo22_t *ctx )
{
    uint8_t data_buf[ 2 ] = { THERMO22_REG_ONE_SHOT, 0 };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t thermo22_set_temperature_low_limit ( thermo22_t *ctx, float low_limit )
{
    if ( ( low_limit < THERMO22_TEMPERATURE_MIN ) || ( low_limit > THERMO22_TEMPERATURE_MAX ) )
    {
        return THERMO22_ERROR;
    }
    int16_t raw_temp = ( int16_t ) ( low_limit / THERMO22_TEMPERATURE_RESOLUTION ) << 4;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO22_REG_TEMPERATURE_LOW;
    data_buf[ 1 ] = ( uint8_t ) ( ( raw_temp >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( raw_temp & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t thermo22_set_temperature_high_limit ( thermo22_t *ctx, float high_limit )
{
    if ( ( high_limit < THERMO22_TEMPERATURE_MIN ) || ( high_limit > THERMO22_TEMPERATURE_MAX ) )
    {
        return THERMO22_ERROR;
    }
    int16_t raw_temp = ( int16_t ) ( high_limit / THERMO22_TEMPERATURE_RESOLUTION ) << 4;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = THERMO22_REG_TEMPERATURE_HIGH;
    data_buf[ 1 ] = ( uint8_t ) ( ( raw_temp >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( raw_temp & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

uint8_t thermo22_get_int_pin ( thermo22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
