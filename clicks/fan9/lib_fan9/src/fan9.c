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
 * @file fan9.c
 * @brief Fan 9 Click Driver.
 */

#include "fan9.h"

void fan9_cfg_setup ( fan9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rd  = HAL_PIN_NC;
    cfg->brk = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FAN9_DEVICE_ADDRESS;
}

err_t fan9_init ( fan9_t *ctx, fan9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->brk, cfg->brk );
    digital_out_init( &ctx->dir, cfg->dir );

    digital_in_init( &ctx->rd, cfg->rd );
    
    digital_in_init( &ctx->flt, cfg->flt );

    digital_out_low( &ctx->brk );

    return I2C_MASTER_SUCCESS;
}

err_t fan9_default_cfg ( fan9_t *ctx ) 
{
    err_t error_flag = FAN9_OK;
    
    fan9_set_direction( ctx, FAN9_DIRECTION_CW );
    fan9_set_brake( ctx, FAN9_PIN_STATE_HIGH );
    error_flag |= fan9_write_reg( ctx, FAN9_REG_EEPROM_ADDR_9, FAN9_STRTDMD_VALUE | FAN9_DMDPOST_VALUE );
    error_flag |= fan9_write_reg( ctx, FAN9_REG_EEPROM_ADDR_20, FAN9_SPEED_CTRL_CLOASED | FAN9_POLE_PAIR_2 | 
                                                                FAN9_NOCOAST | FAN9_ALIGNMODE_ONE_CYCLE | 
                                                                FAN9_QCKSTART_ENABLED | FAN9_OVPOPT_LOCK_DETECT | 
                                                                FAN9_FGSTRT_FG_DISABLED | FAN9_BEMFHYS_LEVEL_1 | 
                                                                FAN9_OCPOPT_RST_AFTER_TLOCK );

    fan9_set_brake( ctx, FAN9_PIN_STATE_LOW );
    return error_flag;
}

err_t fan9_generic_write ( fan9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t fan9_generic_read ( fan9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t fan9_get_rd_pin ( fan9_t *ctx )
{
    return digital_in_read( &ctx->rd );   
}

uint8_t fan9_get_flt_pin ( fan9_t *ctx )
{
    return digital_in_read( &ctx->flt );   
}

void fan9_set_direction ( fan9_t *ctx, uint8_t dir )
{
    if ( FAN9_DIRECTION_CCW == dir )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

void fan9_set_brake ( fan9_t *ctx, uint8_t brake_state )
{
    if ( FAN9_BRAKE_ON == brake_state )
    {
        digital_out_high( &ctx->brk );
    }
    else
    {
        digital_out_low( &ctx->brk );
    }
}

err_t fan9_write_reg ( fan9_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = FAN9_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    tmp_data[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    tmp_data[ 1 ] = ( uint8_t ) data_in;

    error_flag |= fan9_generic_write( ctx, reg + 64, tmp_data, 2 );

    return error_flag;
}

err_t fan9_read_reg ( fan9_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = FAN9_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    error_flag |= fan9_generic_read( ctx, reg + 64, tmp_data, 2 );
    *data_out = ( ( uint16_t ) tmp_data[ 0 ] << 8 ) | tmp_data[ 1 ];

    return error_flag;
}

err_t fan9_set_pwm ( fan9_t *ctx, uint8_t pwm_val )
{
    if ( 100 < pwm_val )
    {
        return FAN9_ERROR;
    }
    
    uint16_t tmp_data = ( uint16_t ) ( ( ( float ) pwm_val / FAN9_PWM_CALCULATION_MUL ) * FAN9_PWM_CALCULATION_CONS );

    return fan9_write_reg( ctx, FAN9_REG_PWM_VAL, tmp_data );
}

err_t fan9_get_pwm ( fan9_t *ctx, uint8_t *pwm_val )
{
    err_t error_flag = FAN9_OK;
    uint16_t tmp_data = 0;

    error_flag |= fan9_read_reg( ctx, FAN9_REG_PWM_VAL, &tmp_data );
    *pwm_val = ( uint8_t ) ( ( ( float ) tmp_data / FAN9_PWM_CALCULATION_CONS ) * FAN9_PWM_CALCULATION_MUL );

    return error_flag;
}

// ------------------------------------------------------------------------- END
