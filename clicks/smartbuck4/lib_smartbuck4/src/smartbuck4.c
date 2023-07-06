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
 * @file smartbuck4.c
 * @brief Smart Buck 4 Click Driver.
 */

#include "smartbuck4.h"

void smartbuck4_cfg_setup ( smartbuck4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->r40 = HAL_PIN_NC;
    cfg->r60 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK4_DEVICE_ADDRESS;
}

err_t smartbuck4_init ( smartbuck4_t *ctx, smartbuck4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->r40, cfg->r40 );
    digital_out_init( &ctx->r60, cfg->r60 );

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck4_default_cfg ( smartbuck4_t *ctx ) 
{
    err_t error_flag = SMARTBUCK4_OK;
    
    smartbuck4_dis_r40_reg( ctx );
    smartbuck4_dis_r60_reg( ctx );
    
    error_flag |= smartbuck4_disable_regulators( ctx );
    
    return error_flag;
}

void smartbuck4_set_r40_out ( smartbuck4_t *ctx, uint8_t out_level )
{
    if ( SMARTBUCK4_PIN_STATE_HIGH == out_level )
    {
        digital_out_high( &ctx->r40 );
    }
    else
    {
        digital_out_low( &ctx->r40 );
    }
}

void smartbuck4_en_r40_reg ( smartbuck4_t *ctx )
{
    smartbuck4_set_r40_out( ctx, SMARTBUCK4_PIN_STATE_HIGH );
}

void smartbuck4_dis_r40_reg ( smartbuck4_t *ctx )
{
    smartbuck4_set_r40_out( ctx, SMARTBUCK4_PIN_STATE_LOW );
}

void smartbuck4_set_r60_out ( smartbuck4_t *ctx, uint8_t out_level )
{
    if ( SMARTBUCK4_PIN_STATE_HIGH == out_level )
    {
        digital_out_high( &ctx->r60 );
    }
    else
    {
        digital_out_low( &ctx->r60 );
    }
}

void smartbuck4_en_r60_reg ( smartbuck4_t *ctx )
{
    smartbuck4_set_r60_out( ctx, SMARTBUCK4_PIN_STATE_LOW );
}

void smartbuck4_dis_r60_reg ( smartbuck4_t *ctx )
{
    smartbuck4_set_r60_out( ctx, SMARTBUCK4_PIN_STATE_HIGH );
}

err_t smartbuck4_send_command ( smartbuck4_t *ctx, uint8_t addr, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = addr;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t smartbuck4_disable_regulators ( smartbuck4_t *ctx )
{
    return smartbuck4_send_command ( ctx, SMARTBUCK4_REG_R600A_PROGRAM | 
                                          SMARTBUCK4_REG_R400A_PROGRAM | 
                                          SMARTBUCK4_REG_R600B_PROGRAM | 
                                          SMARTBUCK4_REG_R400B_PROGRAM, 
                                          SMARTBUCK4_DISABLE_REGULATOR );
}


// ------------------------------------------------------------------------- END
