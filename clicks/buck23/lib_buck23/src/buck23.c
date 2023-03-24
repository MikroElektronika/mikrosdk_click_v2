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
 * @file buck23.c
 * @brief Buck 23 Click Driver.
 */

#include "buck23.h"

void buck23_cfg_setup ( buck23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->sync = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCK23_DEVICE_ADDRESS_0;
}

err_t buck23_init ( buck23_t *ctx, buck23_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->en );
    digital_out_init( &ctx->sync, cfg->sync );
    digital_out_low ( &ctx->sync );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t buck23_default_cfg ( buck23_t *ctx ) 
{
    err_t error_flag = BUCK23_OK;
    buck23_disable_device ( ctx );
    Delay_100ms ( );
    if ( BUCK23_ERROR == buck23_check_communication ( ctx ) )
    {
        return BUCK23_ERROR;
    }
    buck23_write_register ( ctx, BUCK23_REG_VIDMAX, BUCK23_VIDMAX_UNCAPPED );
    buck23_write_register ( ctx, BUCK23_REG_CONFIG, BUCK23_CONFIG_VSTEP_10 | 
                                                    BUCK23_CONFIG_MODE_SYNC | 
                                                    BUCK23_CONFIG_SS_3_PCT_SPREAD | 
                                                    BUCK23_CONFIG_SYNC_IO_IN_RISE );
    ctx->vstep = BUCK23_VSTEP_10;
    buck23_enable_device ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t buck23_write_register ( buck23_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck23_read_register ( buck23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void buck23_enable_device ( buck23_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void buck23_disable_device ( buck23_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void buck23_restart_device ( buck23_t *ctx )
{
    buck23_disable_device ( ctx );
    Delay_100ms ( );
    buck23_enable_device ( ctx );
    Delay_100ms ( );
}

void buck23_set_sync_pin ( buck23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sync, state );
}

uint8_t buck23_get_pg_pin ( buck23_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t buck23_check_communication ( buck23_t *ctx )
{
    uint8_t device_id;
    if ( BUCK23_OK == buck23_read_register ( ctx, BUCK23_REG_ID, &device_id ) )
    {
        if ( BUCK23_DEVICE_ID == device_id )
        {
            return BUCK23_OK;
        }
    }
    return BUCK23_ERROR;
}

err_t buck23_set_vstep ( buck23_t *ctx, uint8_t vstep )
{
    if ( ctx->vstep == vstep )
    {
        return BUCK23_OK;
    }
    err_t error_flag = BUCK23_OK;
    uint8_t config;
    error_flag |= buck23_read_register ( ctx, BUCK23_REG_CONFIG, &config );
    config &= ~BUCK23_CONFIG_VSTEP_MASK;
    if ( BUCK23_VSTEP_10 == vstep )
    {
        config |= BUCK23_CONFIG_VSTEP_10;
    }
    else
    {
        config |= BUCK23_CONFIG_VSTEP_12_5;
    }
    error_flag |= buck23_write_register ( ctx, BUCK23_REG_CONFIG, config );
    ctx->vstep = vstep;
    return error_flag;
}

err_t buck23_set_vout ( buck23_t *ctx, uint16_t vout_mv )
{
    uint8_t vid = 0;
    if ( BUCK23_VSTEP_10 == ctx->vstep )
    {
        if ( vout_mv <= BUCK23_VOUT_MIN_VSTEP_10 )
        {
            vid = BUCK23_VID_MIN;
        }
        else if ( vout_mv >= BUCK23_VOUT_MAX_VSTEP_10 )
        {
            vid = BUCK23_VID_MAX;
        }
        else
        {
            vid = ( uint8_t ) ( ( float ) ( vout_mv - BUCK23_VOUT_MIN_VSTEP_10 ) / BUCK23_VOUT_RES_VSTEP_10 ) + 1;
        }
    }
    else
    {
        if ( vout_mv <= BUCK23_VOUT_MIN_VSTEP_12_5 )
        {
            vid = BUCK23_VID_MIN;
        }
        else if ( vout_mv >= BUCK23_VOUT_MAX_VSTEP_12_5 )
        {
            vid = BUCK23_VID_MAX;
        }
        else
        {
            vid = ( uint8_t ) ( ( float ) ( vout_mv - BUCK23_VOUT_MIN_VSTEP_12_5 ) / BUCK23_VOUT_RES_VSTEP_12_5 ) + 1;
        }
    }
    return buck23_write_register ( ctx, BUCK23_REG_VID, vid );
}

// ------------------------------------------------------------------------- END
