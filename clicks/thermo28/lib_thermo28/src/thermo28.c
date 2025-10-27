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
 * @file thermo28.c
 * @brief Thermo 28 Click Driver.
 */

#include "thermo28.h"

#define THERMO28_TEMP_CALC_CELSIUS       0.0078125  
#define THERMO28_TEMP_ALERT_LIMIT_MIN   20.0
#define THERMO28_TEMP_ALERT_LIMIT_MAX   35.0

/**
 * @brief Thermo 28 default configuration.
 * @details Default configuration of the AS6221 Digital Temperature Sensor
 * on the Thermo 28 Click board™
 */
static thermo28_config_t default_config = 
{
    .conv_rate          =  THERMO28_CONV_RATE4,
    .device_mode        =  THERMO28_STATE_ACTIVE,
    .alert_mode         =  THERMO28_ALERT_INTERRUPT,
    .alert_polarity     =  THERMO28_ALERT_ACTIVE_LOW,
    .consecutive_faults =  THERMO28_CONSEC_FAULTS2,
    .single_shot        = THERMO28_SINGLE_SHOT_START_CONVERSION,
};

void thermo28_cfg_setup ( thermo28_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO28_DEVICE_ADDRESS_VSS;
}

err_t thermo28_init ( thermo28_t *ctx, thermo28_cfg_t *cfg ) 
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

err_t thermo28_default_cfg ( thermo28_t *ctx ) 
{
    err_t err_flag = thermo28_set_config( ctx, default_config );

    err_flag |= thermo28_set_alert_limits( ctx, THERMO28_TEMP_ALERT_LIMIT_MIN, THERMO28_TEMP_ALERT_LIMIT_MAX );

    return err_flag;
}

err_t thermo28_generic_write ( thermo28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t thermo28_generic_read ( thermo28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t thermo28_get_temperature ( thermo28_t *ctx, float *temperature )
{
    uint8_t rx_buf[ 2 ];
    uint16_t tmp;

    err_t err_flag = thermo28_generic_read( ctx, THERMO28_REG_TVAL, rx_buf, 2 );
    if ( THERMO28_OK == err_flag )
    {
        tmp = rx_buf[ 0 ];
        tmp <<= 8;
        tmp |= rx_buf[ 1 ];  
            
        *temperature = ( float ) ( ( int16_t ) tmp );
        *temperature *= THERMO28_TEMP_CALC_CELSIUS;
    }
    return err_flag;
}

err_t thermo28_set_alert_limits ( thermo28_t *ctx, float alert_min, float alert_max )
{
    uint8_t tx_buf[ 2 ];
    uint16_t tmp;

    tmp = ( uint16_t ) ( alert_min / THERMO28_TEMP_CALC_CELSIUS );
    tx_buf[ 0 ] = ( uint8_t ) ( tmp );
    tx_buf[ 1 ] = ( uint8_t ) ( tmp >> 8 );
    err_t err_flag = thermo28_generic_write( ctx, THERMO28_REG_TLOW, tx_buf, 2 );

    tmp = ( uint16_t ) ( alert_max / THERMO28_TEMP_CALC_CELSIUS );
    tx_buf[ 0 ] = ( uint8_t ) ( tmp );
    tx_buf[ 1 ] = ( uint8_t ) ( tmp >> 8 );
    err_flag |= thermo28_generic_write( ctx, THERMO28_REG_THIGH, tx_buf, 2 );

    return err_flag;
}

err_t thermo28_set_config ( thermo28_t *ctx, thermo28_config_t config )
{
    uint8_t tx_buf[ 2 ];
    uint16_t cfg = config.conv_rate;
    cfg |= config.device_mode;
    cfg |= config.alert_mode;
    cfg |= config.alert_polarity;
    cfg |= config.consecutive_faults;
    cfg |= config.single_shot;
    
    tx_buf[ 0 ] = ( uint8_t ) ( cfg >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) cfg;
    
    return thermo28_generic_write( ctx, THERMO28_REG_CONFIG, tx_buf, 2 );
}

err_t thermo28_set_continuous_conversion ( thermo28_t *ctx )
{
    default_config.device_mode =  THERMO28_STATE_ACTIVE;

    return thermo28_set_config ( ctx, default_config );
}

err_t thermo28_set_sleep_mode ( thermo28_t *ctx )
{
    default_config.device_mode =  THERMO28_STATE_SLEEP;

    return thermo28_set_config ( ctx, default_config );
}

err_t thermo28_set_trigger_single_shot ( thermo28_t *ctx )
{
    default_config.single_shot = THERMO28_SINGLE_SHOT_START_CONVERSION;

    return thermo28_set_config ( ctx, default_config );
}

uint8_t thermo28_get_int_pin ( thermo28_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
