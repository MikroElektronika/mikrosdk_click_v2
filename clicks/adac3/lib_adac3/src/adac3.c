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
 * @file adac3.c
 * @brief ADAC 3 Click Driver.
 */

#include "adac3.h"

void adac3_cfg_setup ( adac3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADAC3_DEVICE_ADDRESS_A2A1A0_111;
}

err_t adac3_init ( adac3_t *ctx, adac3_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t adac3_default_cfg ( adac3_t *ctx ) 
{
    ctx->control = 0;
    ctx->dac = 0;
    return adac3_write_control ( ctx, ADAC3_CONTROL_AOUT_ENABLE | 
                                      ADAC3_CONTROL_AIN_MIXED | 
                                      ADAC3_CONTROL_AUTO_INCREMENT | 
                                      ADAC3_CONTROL_AD_CH0 );
}

err_t adac3_write_control ( adac3_t *ctx, uint8_t control )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = control;
    data_buf[ 1 ] = ctx->dac;
    ctx->control = control;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    // ignore first AD conversion upon writing control byte
    error_flag |= adac3_read_adc( ctx, data_buf );
    return error_flag;
}

err_t adac3_write_dac ( adac3_t *ctx, uint8_t dac )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ctx->control;
    data_buf[ 1 ] = dac;
    ctx->dac = dac;
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    // ignore first AD conversion upon writing control byte
    error_flag |= adac3_read_adc( ctx, data_buf );
    return error_flag;
}

err_t adac3_read_adc ( adac3_t *ctx, uint8_t *adc )
{
    return i2c_master_read( &ctx->i2c, adc, 1 );
}

// ------------------------------------------------------------------------- END
