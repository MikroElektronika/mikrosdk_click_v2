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
 * @file leddriver15.c
 * @brief LED Driver 15 Click Driver.
 */

#include "leddriver15.h"

void leddriver15_cfg_setup ( leddriver15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDDRIVER15_DEVICE_ADDRESS;
}

err_t leddriver15_init ( leddriver15_t *ctx, leddriver15_cfg_t *cfg ) 
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
    
    digital_out_init ( &ctx->en, cfg->en );

    return LEDDRIVER15_OK;
}

err_t leddriver15_default_cfg ( leddriver15_t *ctx ) 
{
    err_t error_flag = LEDDRIVER15_OK;
    leddriver15_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= leddriver15_write_register ( ctx, LEDDRIVER15_REG_R0, LEDDRIVER15_R0_EN );
    error_flag |= leddriver15_write_register ( ctx, LEDDRIVER15_REG_R1, LEDDRIVER15_R1_DIMS_I2C | 
                                                                        LEDDRIVER15_R1_SYNC_ENABLE |
                                                                        LEDDRIVER15_R1_OVP_35p5V );
    return error_flag;
}

err_t leddriver15_write_register ( leddriver15_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write ( &ctx->i2c, data_buf, 2 );
}

err_t leddriver15_read_register ( leddriver15_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read ( &ctx->i2c, &reg, 1, data_out, 1 );
}

void leddriver15_enable_device ( leddriver15_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void leddriver15_disable_device ( leddriver15_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t leddriver15_set_i2c_dimming ( leddriver15_t *ctx, uint8_t dimming )
{
    if ( dimming > LEDDRIVER15_I2C_DIMMING_MAX )
    {
        return LEDDRIVER15_ERROR;
    }
    // Form register data, dimming bits are reversed and shifted left by 2
    uint8_t reg_data = LEDDRIVER15_R0_EN | ( ( ( dimming & 0x01 ) << 6 ) | 
                                             ( ( dimming & 0x02 ) << 4 ) | 
                                             ( ( dimming & 0x04 ) << 2 ) | 
                                             ( dimming & 0x08 ) |
                                             ( ( dimming & 0x10 ) >> 2 ) ); 
    return leddriver15_write_register ( ctx, LEDDRIVER15_REG_R0, reg_data );
}

// ------------------------------------------------------------------------- END
