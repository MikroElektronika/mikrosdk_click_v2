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
 * @file fan5.c
 * @brief Fan 5 Click Driver.
 */

#include "fan5.h"

void fan5_cfg_setup ( fan5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FAN5_DEVICE_ADDRESS;
}

err_t fan5_init ( fan5_t *ctx, fan5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t fan5_default_cfg ( fan5_t *ctx ) 
{
    err_t error_flag = FAN5_OK;
    
    error_flag |= fan5_reg_write( ctx, FAN5_CONFIG_REG, FAN5_8_BIT_RESOLUTION | FAN5_VOUT_BASED_ON_DYTY_REG | 
                                                        FAN5_FAN2_PPR_2 | FAN5_FAN1_PPR_2 | FAN5_NORMAL_MODE );
    error_flag |= fan5_clear_flt_flag( ctx );
    error_flag |= fan5_set_fan_fault1( ctx, 0 );
    error_flag |= fan5_set_fan_fault2( ctx, 0 );
    error_flag |= fan5_set_duty_cycle( ctx, FAN5_30_PER_DUTY );
    
    return error_flag;
}

err_t fan5_generic_write ( fan5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t fan5_generic_read ( fan5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t fan5_reg_write ( fan5_t *ctx, uint8_t reg, uint8_t data_in )
{
    return fan5_generic_write( ctx, reg, &data_in, 1 );
}

err_t fan5_reg_read ( fan5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return fan5_generic_read( ctx, reg, data_out, 1 );
}

err_t fan5_get_mfr_id ( fan5_t *ctx, uint8_t *mfr_id )
{
    return fan5_reg_read( ctx, FAN5_MFR_ID_REG, mfr_id );
}

err_t fan5_get_rpm1 ( fan5_t *ctx, uint16_t *fan1_speed )
{
    err_t error_flag = FAN5_OK;
    uint8_t rpm1_data = 0;
   
    error_flag = fan5_reg_read( ctx, FAN5_RPM1_REG, &rpm1_data );
    
    *fan1_speed = 50 * rpm1_data; 
    
    return error_flag;
}

err_t fan5_get_rpm2 ( fan5_t *ctx, uint16_t *fan2_speed )
{
    err_t error_flag = FAN5_OK;
    uint8_t rpm2_data = 0;
    
    error_flag = fan5_reg_read( ctx, FAN5_RPM2_REG, &rpm2_data );
    
    *fan2_speed = 50 * rpm2_data; 
    
    return error_flag;
}

err_t fan5_set_fan_fault1 ( fan5_t *ctx, uint16_t fault1_value )
{
    err_t error_flag = FAN5_OK;
    
    if ( FAN5_MAX_RPM_VALUE < fault1_value )
    {
        error_flag = FAN5_ERROR;
    }
    else
    {
        uint8_t fault1_data = 0;
        fault1_data = fault1_value / 50;
        
        error_flag = fan5_reg_write( ctx, FAN5_FAN_FAULT1_REG, fault1_data );
    }

    return error_flag;
}

err_t fan5_set_fan_fault2 ( fan5_t *ctx, uint16_t fault2_value )
{
    err_t error_flag = FAN5_OK;
    
    if ( FAN5_MAX_RPM_VALUE < fault2_value )
    {
        error_flag = FAN5_ERROR;
    }
    else
    {
        uint8_t fault2_data = 0;
        fault2_data = fault2_value / 50;
        
        error_flag = fan5_reg_write( ctx, FAN5_FAN_FAULT2_REG, fault2_data );
    }

    return error_flag;
}

err_t fan5_set_duty_cycle ( fan5_t *ctx, uint8_t duty_cycle )
{
    err_t error_flag = FAN5_OK;
    
    if ( FAN5_100_PER_DUTY < duty_cycle )
    {
        error_flag = FAN5_ERROR;
    }
    else
    {
        error_flag = fan5_reg_write( ctx, FAN5_DUTY_CYCLE_REG, duty_cycle );
    }
    
    return error_flag;
}

err_t fan5_get_status_flags (  fan5_t *ctx, uint8_t *status_data )
{
    err_t error_flag = FAN5_OK;
    uint8_t read_data = 0;
    
    error_flag |= fan5_reg_read( ctx, FAN5_STATUS_REG, &read_data);
    *status_data = read_data;

    return error_flag;
}

err_t fan5_clear_flt_flag ( fan5_t *ctx )
{
    err_t error_flag = FAN5_OK;
    uint8_t read_data = 0;
    
    error_flag |= fan5_reg_read( ctx, FAN5_CONFIG_REG, &read_data);
    read_data |= FAN5_CLEAR_FLT;
    error_flag |= fan5_reg_write( ctx, FAN5_CONFIG_REG, read_data);
    read_data &= ~FAN5_CLEAR_FLT;
    error_flag |= fan5_reg_write( ctx, FAN5_CONFIG_REG, read_data);
    
    return error_flag;
}

err_t fan5_get_fault_state ( fan5_t *ctx )
{
    err_t error_flag;
    
    if ( digital_in_read( &ctx->flt ) )
    {
        error_flag = FAN5_OK;
    }
    else
    {
        error_flag = FAN5_FAULT;
    }
    
    return error_flag;
}

err_t fan5_turn_on_fans ( fan5_t *ctx )
{
    err_t error_flag = FAN5_OK;
    uint8_t read_data = 0;
    
    error_flag |= fan5_reg_read( ctx, FAN5_CONFIG_REG, &read_data);
    read_data &= ~FAN5_SHUTDOWN_MODE;
    error_flag |= fan5_reg_write( ctx, FAN5_CONFIG_REG, read_data);
    
    return error_flag;
}

err_t fan5_turn_off_fans ( fan5_t *ctx )
{
    err_t error_flag = FAN5_OK;
    uint8_t read_data = 0;
    
    error_flag |= fan5_reg_read( ctx, FAN5_CONFIG_REG, &read_data);
    read_data |= FAN5_SHUTDOWN_MODE;
    error_flag |= fan5_reg_write( ctx, FAN5_CONFIG_REG, read_data);
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
