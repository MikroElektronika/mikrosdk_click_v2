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
 * @file buck19.c
 * @brief Buck 19 Click Driver.
 */

#include "buck19.h"

void buck19_cfg_setup ( buck19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pon = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = BUCK19_DEVICE_ADDRESS_GND;
}

err_t buck19_init ( buck19_t *ctx, buck19_cfg_t *cfg ) 
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
    digital_in_init( &ctx->pon, cfg->pon );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t buck19_default_cfg ( buck19_t *ctx ) 
{
    err_t error_flag = BUCK19_OK;
    buck19_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= buck19_set_vout ( ctx, BUCK19_VOUT_DEFAULT );
    error_flag |= buck19_set_ilimit ( ctx, BUCK19_ILIMIT_DEFAULT );
    error_flag |= buck19_write_register ( ctx, BUCK19_REG_INT_STATUS, BUCK19_INT_DISABLE_ALL );
    error_flag |= buck19_write_register ( ctx, BUCK19_REG_INT_LATCH, BUCK19_INT_DISABLE_ALL );
    error_flag |= buck19_write_register ( ctx, BUCK19_REG_INT_MASK, BUCK19_INT_POWER_ON | 
                                                                    BUCK19_INT_SHORT_PROTECT | 
                                                                    BUCK19_INT_CC_FUNCTION );
    error_flag |= buck19_write_register ( ctx, BUCK19_REG_CONFIG_0, BUCK19_CONFIG_0_WATCHDOG_100MS | 
                                                                    BUCK19_CONFIG_0_CDC_OFF | 
                                                                    BUCK19_CONFIG_0_SW_FREQ_500KHZ |
                                                                    BUCK19_CONFIG_0_DITHERING_OFF |
                                                                    BUCK19_CONFIG_0_DISCHARGE_ON );
    error_flag |= buck19_write_register ( ctx, BUCK19_REG_CONFIG_1, BUCK19_CONFIG_1_WATCHDOG_EN_OFF | 
                                                                    BUCK19_CONFIG_1_DIG_EN_ON );
    return error_flag;
}

err_t buck19_write_register ( buck19_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > BUCK19_REG_CONFIG_1 )
    {
        return BUCK19_ERROR;
    }
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck19_read_register ( buck19_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > BUCK19_REG_CONFIG_1 )
    {
        return BUCK19_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void buck19_enable_device ( buck19_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void buck19_disable_device ( buck19_t *ctx )
{
    digital_out_high ( &ctx->en );
}

uint8_t buck19_get_pon_pin ( buck19_t *ctx )
{
    return digital_in_read ( &ctx->pon );
}

uint8_t buck19_get_int_pin ( buck19_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t buck19_set_vout ( buck19_t *ctx, float vout )
{
    if ( ( vout < ( BUCK19_VOUT_MIN - BUCK19_FLOAT_COMPARE_TOLERANCE ) ) || 
         ( vout > ( BUCK19_VOUT_MAX + BUCK19_FLOAT_COMPARE_TOLERANCE ) ) )
    {
        return BUCK19_ERROR;
    }
    uint8_t vout_reg_data = 0;
    float tmp_vout = vout;
    while ( tmp_vout > ( BUCK19_VOUT_MIN + BUCK19_FLOAT_COMPARE_TOLERANCE ) )
    {
        vout_reg_data++;
        if ( tmp_vout > ( BUCK19_VOUT_11V + BUCK19_FLOAT_COMPARE_TOLERANCE ) )
        {
            tmp_vout -= BUCK19_VOUT_11V_STEP;
            if ( tmp_vout < ( BUCK19_VOUT_11V - BUCK19_FLOAT_COMPARE_TOLERANCE ) )
            {
                tmp_vout = BUCK19_VOUT_11V;
            }
        }
        else if ( tmp_vout > ( BUCK19_VOUT_5p9V + BUCK19_FLOAT_COMPARE_TOLERANCE ) )
        {
            tmp_vout -= BUCK19_VOUT_5p9V_STEP;
            if ( tmp_vout < ( BUCK19_VOUT_5p9V - BUCK19_FLOAT_COMPARE_TOLERANCE ) )
            {
                tmp_vout = BUCK19_VOUT_5p9V;
            }
        }
        else
        {
            tmp_vout -= BUCK19_VOUT_STEP;
        }
    }
    return buck19_write_register( ctx, BUCK19_REG_VOUT, vout_reg_data );
}

err_t buck19_set_ilimit ( buck19_t *ctx, uint16_t ilimit )
{
    if ( ( ilimit < BUCK19_ILIMIT_MIN ) || ( ilimit > BUCK19_ILIMIT_MAX ) )
    {
        return BUCK19_ERROR;
    }
    uint8_t ilimit_reg_data = 0;
    float tmp_ilimit = ilimit;
    while ( tmp_ilimit > BUCK19_ILIMIT_MIN )
    {
        ilimit_reg_data++;
        tmp_ilimit -= BUCK19_ILIMIT_STEP;
    }
    return buck19_write_register( ctx, BUCK19_REG_ILIMIT, ilimit_reg_data );
}

// ------------------------------------------------------------------------- END
