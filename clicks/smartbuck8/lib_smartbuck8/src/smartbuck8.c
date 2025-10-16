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
 * @file smartbuck8.c
 * @brief Smart Buck 8 Click Driver.
 */

#include "smartbuck8.h"

void smartbuck8_cfg_setup ( smartbuck8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;
    cfg->pon = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK8_DEVICE_ADDRESS;
}

err_t smartbuck8_init ( smartbuck8_t *ctx, smartbuck8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->pon, cfg->pon );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck8_default_cfg ( smartbuck8_t *ctx ) 
{
    err_t error_flag = SMARTBUCK8_OK;
    
    Delay_100ms ( );
    smartbuck8_enable_power ( ctx );
    Delay_1sec ( );
    smartbuck8_disable_device ( ctx );
    Delay_1sec ( );
    smartbuck8_enable_device ( ctx );
    Delay_100ms ( );

    error_flag |= smartbuck8_set_control ( ctx, SMARTBUCK8_CONTROL_EN_FPWM_ON_CHANGE | 
                                                SMARTBUCK8_CONTROL_SOFT_EN | 
                                                SMARTBUCK8_CONTROL_EN_OUT_DISCHARGE | 
                                                SMARTBUCK8_CONTROL_EN_HICCUP | 
                                                SMARTBUCK8_CONTROL_V_RAMP_SPEED_5US );

    return error_flag;
}

err_t smartbuck8_write_reg ( smartbuck8_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( SMARTBUCK8_REG_VOUT != reg ) && 
         ( SMARTBUCK8_REG_CONTROL != reg ) )
    {
        return SMARTBUCK8_ERROR;
    }
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t smartbuck8_read_reg ( smartbuck8_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( SMARTBUCK8_REG_VOUT != reg ) && 
         ( SMARTBUCK8_REG_CONTROL != reg ) && 
         ( SMARTBUCK8_REG_STATUS != reg ) )
    {
        return SMARTBUCK8_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void smartbuck8_enable_power ( smartbuck8_t *ctx )
{
    digital_out_high ( &ctx->pon );
}

void smartbuck8_disable_power ( smartbuck8_t *ctx )
{
    digital_out_low ( &ctx->pon );
}

void smartbuck8_enable_device ( smartbuck8_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void smartbuck8_disable_device ( smartbuck8_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t smartbuck8_get_pg_pin ( smartbuck8_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t smartbuck8_read_status ( smartbuck8_t *ctx, uint8_t *status )
{
    return smartbuck8_read_reg( ctx, SMARTBUCK8_REG_STATUS, status );
}

err_t smartbuck8_set_control ( smartbuck8_t *ctx, uint8_t control )
{
    return smartbuck8_write_reg( ctx, SMARTBUCK8_REG_CONTROL, control );
}

err_t smartbuck8_set_vout ( smartbuck8_t *ctx, uint16_t vout_mv )
{
    uint8_t vout = ( vout_mv - SMARTBUCK8_VOUT_MV_MIN ) / SMARTBUCK8_VOUT_MV_STEP_5MV;
    if ( ( vout_mv < SMARTBUCK8_VOUT_MV_MIN ) || 
         ( vout_mv > SMARTBUCK8_VOUT_MV_MAX ) )
    {
        return SMARTBUCK8_ERROR;
    }
    return smartbuck8_write_reg ( ctx, SMARTBUCK8_REG_VOUT, vout );
}

// ------------------------------------------------------------------------- END
