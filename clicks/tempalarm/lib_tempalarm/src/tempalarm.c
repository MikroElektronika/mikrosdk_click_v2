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
 * @file tempalarm.c
 * @brief Temp Alarm Click Driver.
 */

#include "tempalarm.h"

void tempalarm_cfg_setup ( tempalarm_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->tcr   = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPALARM_DEVICE_ADDRESS;
}

err_t tempalarm_init ( tempalarm_t *ctx, tempalarm_cfg_t *cfg ) 
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

    digital_in_init( &ctx->tcr, cfg->tcr );
    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t tempalarm_default_cfg ( tempalarm_t *ctx ) 
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_CONFIGURATION, TEMPALARM_REMOTE_EN | 
                                                                         TEMPALARM_WTC_EN | 
                                                                         TEMPALARM_FAULT_QUE_EN );
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_CONV_PERIOD, TEMPALARM_CONVERSION_PERIOD_62MS5 );
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_ALERT_MASK, TEMPALARM_THIGH_LA_ALERT_DIS_MASK | 
                                                                      TEMPALARM_THIGH_RA_ALERT_ENABLE_MASK | 
                                                                      TEMPALARM_TLOW_RA_ALERT_DIS_MASK | 
                                                                      TEMPALARM_TCRIT_R_ALERT_DIS_MASK | 
                                                                      TEMPALARM_TCRIT_L_ALERT_DIS_MASK );
    
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_FILTER_ALERT_MODE, TEMPALARM_FILTER_LEVEL_0_MASK | 
                                                                             TEMPALARM_COMPARATOR_MODE );
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_CRIT_HYSTERESIS, 1 );
    
    error_flag |= tempalarm_set_crit_thigh( ctx, 30 );
    
    error_flag |= tempalarm_set_alarm_high_limit( ctx, 30 );

    return error_flag;
}

err_t tempalarm_generic_write ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t tempalarm_generic_read ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t tempalarm_get_alr_pin ( tempalarm_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

uint8_t tempalarm_get_tcr_pin ( tempalarm_t *ctx )
{
    return digital_in_read( &ctx->tcr );
}

err_t tempalarm_write_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag |= tempalarm_generic_write( ctx, reg, &data_in, 1 );

    return error_flag;
}

err_t tempalarm_read_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag |= tempalarm_generic_read( ctx, reg, data_out, 1 );

    return error_flag;
}

err_t tempalarm_read_temperature ( tempalarm_t *ctx, int8_t *temperature )
{
    err_t error_flag = TEMPALARM_OK;
    uint8_t data_buf;
    
    error_flag |= tempalarm_read_reg( ctx, TEMPALARM_REG_TEMP_LOCAL, &data_buf);

    *temperature = ( int8_t ) data_buf;

    return error_flag;
}

err_t tempalarm_read_remote_temp ( tempalarm_t *ctx, float *temperature )
{
    err_t error_flag = TEMPALARM_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    
    error_flag |= tempalarm_read_reg( ctx, TEMPALARM_REG_TEMP_REMOTE_MSB, &data_buf[ 0 ] );
    error_flag |= tempalarm_read_reg( ctx, TEMPALARM_REG_TEMP_REMOTE_LSB, &data_buf[ 1 ] );

    int8_t raw_temp = data_buf[ 0 ];
    *temperature = ( float ) raw_temp + ( ( float ) ( data_buf[ 1 ] >> 5 ) * TEMPALARM_TEMP_CLC ) ;
    return error_flag;
}

err_t tempalarm_set_crit_thigh ( tempalarm_t *ctx, int8_t max_temperature )
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_THIGH_CRIT_LOCAL, max_temperature );
    
    return error_flag;
}

err_t tempalarm_set_limit_thigh ( tempalarm_t *ctx, int8_t max_temperature )
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_THIGH_LIMIT_LOCAL, max_temperature );
    
    return error_flag;
}

err_t tempalarm_set_alarm_low_limit ( tempalarm_t *ctx, float min_temperature )
{
    err_t error_flag = TEMPALARM_OK;
    
    int8_t data_buf[ 2 ] = { 0 };
    
    data_buf[ 0 ] = ( int8_t ) min_temperature;
    data_buf[ 1 ] = ( int8_t ) ( ( min_temperature - data_buf[ 0 ] ) / TEMPALARM_TEMP_CLC ) << 5;
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_TLOW_LIMIT_REMOTE_MSB, data_buf[ 0 ] );
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_TLOW_LIMIT_REMOTE_LSB, data_buf[ 1 ] );
    
    return error_flag;
}

err_t tempalarm_set_alarm_high_limit ( tempalarm_t *ctx, float max_temperature )
{
    err_t error_flag = TEMPALARM_OK;
    
    int8_t data_buf[ 2 ] = { 0 };
    
    data_buf[ 0 ] = ( int8_t ) max_temperature;
    data_buf[ 1 ] = ( int8_t ) ( ( max_temperature - data_buf[ 0 ] ) / TEMPALARM_TEMP_CLC ) << 5;
    
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_THIGH_LIMIT_REMOTE_MSB, data_buf[ 0 ] );
    error_flag |= tempalarm_write_reg( ctx, TEMPALARM_REG_THIGH_LIMIT_REMOTE_LSB, data_buf[ 1 ] );
    
    return error_flag;
}

err_t tempalarm_get_alarms ( tempalarm_t *ctx, uint8_t *alarms )
{
    err_t error_flag = TEMPALARM_OK;
    
    error_flag = tempalarm_read_reg ( ctx, TEMPALARM_REG_ALERT_STATUS, alarms );
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
