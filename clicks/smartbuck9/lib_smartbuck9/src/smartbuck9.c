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
 * @file smartbuck9.c
 * @brief Smart Buck 9 Click Driver.
 */

#include "smartbuck9.h"

/**
 * @brief Smart Buck 9 voltage to code function.
 * @details This function converts voltage value in millivolts to 8-bit register code.
 * @param[in] voltage_mv : Output voltage in millivolts.
 * @return 8-bit register code for voltage setting.
 * @note None.
 */
static uint8_t smartbuck9_voltage_to_code ( uint16_t voltage_mv );

void smartbuck9_cfg_setup ( smartbuck9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK9_DEVICE_ADDRESS;
}

err_t smartbuck9_init ( smartbuck9_t *ctx, smartbuck9_cfg_t *cfg ) 
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
    digital_in_init( &ctx->pg, cfg->pg );
    Delay_10ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck9_default_cfg ( smartbuck9_t *ctx ) 
{
    err_t error_flag = SMARTBUCK9_OK;

    smartbuck9_enable_device ( ctx );
    Delay_10ms ( );

    error_flag = smartbuck9_check_com( ctx );

    if ( SMARTBUCK9_OK == error_flag )
    {
        error_flag = smartbuck9_write_reg( ctx, SMARTBUCK9_REG_CONFIG,
                                           SMARTBUCK9_CONFIG_EN_BUCK_EN |
                                           SMARTBUCK9_CONFIG_AD_EN |
                                           SMARTBUCK9_CONFIG_FREQ_2MHZ |
                                           SMARTBUCK9_CONFIG_OCP_4A |
                                           SMARTBUCK9_CONFIG_PWM_PFM );
    }

    if ( SMARTBUCK9_OK == error_flag )
    {
        error_flag = smartbuck9_set_vout( ctx, SMARTBUCK9_VOUT_DEFAULT_MV );
    }

    return error_flag;
}

err_t smartbuck9_write_reg ( smartbuck9_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t smartbuck9_read_reg ( smartbuck9_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void smartbuck9_enable_device ( smartbuck9_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void smartbuck9_disable_device ( smartbuck9_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t smartbuck9_get_pg_pin ( smartbuck9_t *ctx )
{
    return !!digital_in_read ( &ctx->pg );
}

err_t smartbuck9_check_com ( smartbuck9_t *ctx )
{
    uint8_t devid = 0;
    if ( SMARTBUCK9_OK == smartbuck9_read_reg ( ctx, SMARTBUCK9_REG_DEVICE_ID, &devid ) )
    {
        if ( SMARTBUCK9_DEVICE_ID_VERSION_A == ( devid & SMARTBUCK9_DEVICE_ID_VERSION_MASK ) )
        {
            return SMARTBUCK9_OK;
        }
    }
    return SMARTBUCK9_ERROR;
}

err_t smartbuck9_set_vout ( smartbuck9_t *ctx, uint16_t voltage_mv )
{
    return smartbuck9_write_reg( ctx, SMARTBUCK9_REG_VOUT,
                                 smartbuck9_voltage_to_code( voltage_mv ) );
}

static uint8_t smartbuck9_voltage_to_code ( uint16_t voltage_mv )
{
    uint16_t voltage_limited = voltage_mv;
    uint8_t vout_code = SMARTBUCK9_VOUT_CODE_MIN;

    if ( voltage_limited < SMARTBUCK9_VOUT_MIN_MV )
    {
        voltage_limited = SMARTBUCK9_VOUT_MIN_MV;
    }

    if ( voltage_limited > SMARTBUCK9_VOUT_MAX_MV )
    {
        voltage_limited = SMARTBUCK9_VOUT_MAX_MV;
    }

    vout_code =  ( uint8_t )( ( voltage_limited - SMARTBUCK9_VOUT_MIN_MV ) / SMARTBUCK9_VOUT_STEP_MV );

    if ( vout_code > SMARTBUCK9_VOUT_CODE_MAX )
    {
        vout_code = SMARTBUCK9_VOUT_CODE_MAX;
    }

    return vout_code;
}

// ------------------------------------------------------------------------- END
