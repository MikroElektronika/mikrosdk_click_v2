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
 * @file hwmonitor3.c
 * @brief HW Monitor 3 Click Driver.
 */

#include "hwmonitor3.h"

void hwmonitor3_cfg_setup ( hwmonitor3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sync = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HWMONITOR3_DEVICE_ADDRESS_0;
}

err_t hwmonitor3_init ( hwmonitor3_t *ctx, hwmonitor3_cfg_t *cfg ) 
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
    digital_out_init( &ctx->sleep, cfg->sleep );

    digital_in_init( &ctx->sync, cfg->sync );
    digital_in_init( &ctx->irq, cfg->irq );

    return I2C_MASTER_SUCCESS;
}

err_t hwmonitor3_default_cfg ( hwmonitor3_t *ctx ) 
{
    err_t error_flag = HWMONITOR3_OK;
    hwmonitor3_set_sleep_pin ( ctx, 1 );
    hwmonitor3_set_en_pin ( ctx, 0 );
    Delay_100ms ( );
    hwmonitor3_set_en_pin ( ctx, 1 );
    Delay_100ms ( );
    if ( HWMONITOR3_ERROR == hwmonitor3_check_communication ( ctx ) )
    {
        return HWMONITOR3_ERROR;
    }
    error_flag |= hwmonitor3_select_bank1 ( ctx );
    error_flag |= hwmonitor3_enable_channel ( ctx, HWMONITOR3_CHANNEL_ALL );
    error_flag |= hwmonitor3_set_scaling ( ctx, HWMONITOR3_SCALING_4X, HWMONITOR3_CHANNEL_1 | 
                                                                       HWMONITOR3_CHANNEL_2 | 
                                                                       HWMONITOR3_CHANNEL_3 );
    error_flag |= hwmonitor3_set_scaling ( ctx, HWMONITOR3_SCALING_1X, HWMONITOR3_CHANNEL_4 | 
                                                                       HWMONITOR3_CHANNEL_5 | 
                                                                       HWMONITOR3_CHANNEL_6 );
    error_flag |= hwmonitor3_select_bank0 ( ctx );
    return error_flag;
}

err_t hwmonitor3_write_reg ( hwmonitor3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return hwmonitor3_write_regs( ctx, reg, &data_in, 1 );
}

err_t hwmonitor3_write_regs ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t hwmonitor3_read_reg ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return hwmonitor3_read_regs( ctx, reg, data_out, 1 );
}

err_t hwmonitor3_read_regs ( hwmonitor3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void hwmonitor3_set_en_pin ( hwmonitor3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void hwmonitor3_set_sleep_pin ( hwmonitor3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sleep, state );
}

uint8_t hwmonitor3_get_sync_pin ( hwmonitor3_t *ctx )
{
    return digital_in_read ( &ctx->sync );
}

uint8_t hwmonitor3_get_irq_pin ( hwmonitor3_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t hwmonitor3_select_bank0 ( hwmonitor3_t *ctx )
{
    return hwmonitor3_write_reg( ctx, HWMONITOR3_REG_BANK_SEL, 0 );
}

err_t hwmonitor3_select_bank1 ( hwmonitor3_t *ctx )
{
    return hwmonitor3_write_reg( ctx, HWMONITOR3_REG_BANK_SEL, 1 );
}

err_t hwmonitor3_check_communication ( hwmonitor3_t *ctx )
{
    uint8_t i2c_addr = 0;
    if ( HWMONITOR3_OK == hwmonitor3_read_reg ( ctx, HWMONITOR3_REG_I2CADDR, &i2c_addr ) )
    {
        if ( i2c_addr == ctx->slave_address )
        {
            return HWMONITOR3_OK;
        }
    }
    return HWMONITOR3_ERROR;
}

err_t hwmonitor3_enable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask )
{
    uint8_t reg_data = 0;
    err_t error_flag = hwmonitor3_read_reg( ctx, HWMONITOR3_REG_MON_CH_EN, &reg_data );
    if ( HWMONITOR3_OK == error_flag )
    {
        reg_data |= ch_mask;
        error_flag = hwmonitor3_write_reg( ctx, HWMONITOR3_REG_MON_CH_EN, reg_data );
    }
    return error_flag;
}

err_t hwmonitor3_disable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask )
{
    uint8_t reg_data = 0;
    err_t error_flag = hwmonitor3_read_reg( ctx, HWMONITOR3_REG_MON_CH_EN, &reg_data );
    if ( HWMONITOR3_OK == error_flag )
    {
        reg_data &= ( ~ch_mask );
        error_flag = hwmonitor3_write_reg( ctx, HWMONITOR3_REG_MON_CH_EN, reg_data );
    }
    return error_flag;
}

err_t hwmonitor3_set_scaling ( hwmonitor3_t *ctx, uint8_t scaling, uint8_t ch_mask )
{
    uint8_t reg_data = 0;
    err_t error_flag = hwmonitor3_read_reg( ctx, HWMONITOR3_REG_VRANGE_MULT, &reg_data );
    if ( HWMONITOR3_OK == error_flag )
    {
        if ( scaling )
        {
            reg_data |= ch_mask;
        }
        else
        {
            reg_data &= ( ~ch_mask );
        }
        ctx->scaling = reg_data;
        error_flag = hwmonitor3_write_reg( ctx, HWMONITOR3_REG_VRANGE_MULT, reg_data );
    }
    return error_flag;
}

err_t hwmonitor3_read_voltage ( hwmonitor3_t *ctx, hwmonitor3_ch_mon_t *ch_mon )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = hwmonitor3_read_regs ( ctx, HWMONITOR3_REG_MON_LVL_1, data_buf, 6 );
    if ( HWMONITOR3_OK == error_flag )
    {
        ch_mon->ch1_v = ( data_buf[ 0 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        ch_mon->ch2_v = ( data_buf[ 1 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        ch_mon->ch3_v = ( data_buf[ 2 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        ch_mon->ch4_v = ( data_buf[ 3 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        ch_mon->ch5_v = ( data_buf[ 4 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        ch_mon->ch6_v = ( data_buf[ 5 ] * HWMONITOR3_DATA_RES + HWMONITOR3_DATA_OFFSET );
        if ( ctx->scaling & HWMONITOR3_CHANNEL_1 )
        {
            ch_mon->ch1_v *= HWMONITOR3_DATA_SCALE_4X;
        }
        if ( ctx->scaling & HWMONITOR3_CHANNEL_2 )
        {
            ch_mon->ch2_v *= HWMONITOR3_DATA_SCALE_4X;
        }
        if ( ctx->scaling & HWMONITOR3_CHANNEL_3 )
        {
            ch_mon->ch3_v *= HWMONITOR3_DATA_SCALE_4X;
        }
        if ( ctx->scaling & HWMONITOR3_CHANNEL_4 )
        {
            ch_mon->ch4_v *= HWMONITOR3_DATA_SCALE_4X;
        }
        if ( ctx->scaling & HWMONITOR3_CHANNEL_5 )
        {
            ch_mon->ch5_v *= HWMONITOR3_DATA_SCALE_4X;
        }
        if ( ctx->scaling & HWMONITOR3_CHANNEL_6 )
        {
            ch_mon->ch6_v *= HWMONITOR3_DATA_SCALE_4X;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
