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
 * @file buckboost6.c
 * @brief Buck-Boost 6 Click Driver.
 */

#include "buckboost6.h"

/**
 * @brief Buck-Boost 6 voltage to code function.
 * @details This function converts voltage value in millivolts to 7-bit register code.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @param[in] voltage_mv : Output voltage in millivolts.
 * @return 7-bit register code for voltage setting.
 * @note None.
 */
static uint8_t buckboost6_voltage_to_code ( uint16_t voltage_mv );

void buckboost6_cfg_setup ( buckboost6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->sel = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCKBOOST6_DEVICE_ADDRESS;
}

err_t buckboost6_init ( buckboost6_t *ctx, buckboost6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_in_init( &ctx->sel, cfg->sel );
    Delay_10ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t buckboost6_default_cfg ( buckboost6_t *ctx ) 
{
    err_t error_flag = BUCKBOOST6_OK;

    buckboost6_enable_device ( ctx );
    Delay_10ms ( );

    error_flag = buckboost6_check_com( ctx );

    if ( BUCKBOOST6_OK == error_flag )
    {
        error_flag = buckboost6_write_reg( ctx, BUCKBOOST6_REG_CONTROL,
                                           BUCKBOOST6_CONTROL_SDA_SLEW_HIGH |
                                           BUCKBOOST6_CONTROL_ULTRASONIC_DIS |
                                           BUCKBOOST6_CONTROL_FORCED_PWM_DIS |
                                           BUCKBOOST6_CONTROL_RAMP_PWM_DIS |
                                           BUCKBOOST6_CONTROL_DVS_SLEW_1V_MS );
    }

    if ( BUCKBOOST6_OK == error_flag )
    {
        error_flag = buckboost6_set_vout( ctx, BUCKBOOST6_VOUT_DEFAULT_MV );
    }

    return error_flag;
}

err_t buckboost6_write_reg ( buckboost6_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buckboost6_read_reg ( buckboost6_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void buckboost6_enable_device ( buckboost6_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void buckboost6_disable_device ( buckboost6_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t buckboost6_get_sel_pin ( buckboost6_t *ctx )
{
    return !!digital_in_read ( &ctx->sel );
}

err_t buckboost6_check_com ( buckboost6_t *ctx )
{
    uint8_t devid = 0;
    if ( BUCKBOOST6_OK == buckboost6_read_reg ( ctx, BUCKBOOST6_REG_DEVID, &devid ) )
    {
        if ( BUCKBOOST6_DEVID_MANUFACTURER_RICHTEK == ( devid & BUCKBOOST6_DEVID_MANUFACTURER_MASK ) )
        {
            return BUCKBOOST6_OK;
        }
    }
    return BUCKBOOST6_ERROR;
}

err_t buckboost6_set_vout ( buckboost6_t *ctx, uint16_t voltage_mv )
{
    err_t error_flag = BUCKBOOST6_OK;
    if ( buckboost6_get_sel_pin ( ctx ) )
    {
        error_flag = buckboost6_write_reg( ctx, BUCKBOOST6_REG_VOUT2,
                                           buckboost6_voltage_to_code( voltage_mv ) );
    }
    else
    {
        error_flag = buckboost6_write_reg( ctx, BUCKBOOST6_REG_VOUT1,
                                           buckboost6_voltage_to_code( voltage_mv ) );
    }
    return error_flag;
}

static uint8_t buckboost6_voltage_to_code ( uint16_t voltage_mv )
{
    uint16_t voltage_limited = voltage_mv;

    if ( voltage_limited < BUCKBOOST6_VOUT_MIN_MV )
    {
        voltage_limited = BUCKBOOST6_VOUT_MIN_MV;
    }

    if ( voltage_limited > BUCKBOOST6_VOUT_MAX_MV )
    {
        voltage_limited = BUCKBOOST6_VOUT_MAX_MV;
    }

    return ( uint8_t )( ( voltage_limited - BUCKBOOST6_VOUT_MIN_MV ) / BUCKBOOST6_VOUT_STEP_MV ) & BUCKBOOST6_VOUT_MASK;
}

// ------------------------------------------------------------------------- END
