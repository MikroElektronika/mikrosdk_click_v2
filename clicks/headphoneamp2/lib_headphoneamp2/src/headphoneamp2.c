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
 * @file headphoneamp2.c
 * @brief Headphone AMP 2 Click Driver.
 */

#include "headphoneamp2.h"

void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->shd = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEADPHONEAMP2_DEVICE_ADDRESS;
}

err_t headphoneamp2_init ( headphoneamp2_t *ctx, headphoneamp2_cfg_t *cfg ) 
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
    
    digital_out_init( &ctx->shd, cfg->shd );
    
    return I2C_MASTER_SUCCESS;
}

err_t headphoneamp2_default_cfg ( headphoneamp2_t *ctx ) 
{
    // Enable the device
    headphoneamp2_enable( ctx );
    Delay_10ms( );
    // Shutdown the device, BassMax disable, max Gain disable and mute
    headphoneamp2_cmd_t cmd_ctrl;
    cmd_ctrl.wakes_up = HEADPHONEAMP2_CMD_DISABLE;
    cmd_ctrl.bass_max = HEADPHONEAMP2_CMD_DISABLE;
    cmd_ctrl.gain_max = HEADPHONEAMP2_CMD_DISABLE;
    cmd_ctrl.volume = HEADPHONEAMP2_VOL_MUTE;
    Delay_10ms( );
    return headphoneamp2_set_command( ctx, cmd_ctrl );
}

void headphoneamp2_enable ( headphoneamp2_t *ctx ) 
{
   digital_out_high( &ctx->shd );
}

void headphoneamp2_disable ( headphoneamp2_t *ctx ) 
{
   digital_out_low( &ctx->shd );
}

err_t headphoneamp2_write_data ( headphoneamp2_t *ctx, uint8_t data_in ) 
{
    return i2c_master_write( &ctx->i2c, &data_in, 1 );
}

err_t headphoneamp2_set_command ( headphoneamp2_t *ctx, headphoneamp2_cmd_t cmd_ctrl ) 
{
    uint8_t data_buf = 0;
    data_buf  = ( uint8_t ) ( cmd_ctrl.wakes_up << 7 );
    data_buf |= ( uint8_t ) ( cmd_ctrl.bass_max << 6 );
    data_buf |= ( uint8_t ) ( cmd_ctrl.gain_max << 5 );
    data_buf |= ( uint8_t ) ( cmd_ctrl.volume & HEADPHONEAMP2_VOL_LVL_MAX );
    return headphoneamp2_write_data( ctx, data_buf );
}

// ------------------------------------------------------------------------- END
