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
 * @file color12.c
 * @brief Color 12 Click Driver.
 */

#include "color12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00

void color12_cfg_setup ( color12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR12_DEVICE_ADDRESS;
}

err_t color12_init ( color12_t *ctx, color12_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t color12_default_cfg ( color12_t *ctx ) 
{
    uint8_t device_id = DUMMY;
    err_t err_flag = color12_get_device_id ( ctx, &device_id );
    if ( COLOR12_MANUFACTURER_ID == device_id )
    {
        color12_config_t config;
        config.rgb_gain  = COLOR12_RGB_GAIN_X1;
        config.meas_mode = COLOR12_MEAS_MODE_100MS;
        config.flc_gain  = COLOR12_FLC_GAIN_X1;
        config.flc_mode  = COLOR12_FLC_MODE_1KHZ;
        config.int_sel   = COLOR12_INT_SEL_DISABLE;
        config.rgb_en    = COLOR12_RGB_EN_ENABLE;
        config.flc_en    = COLOR12_FLC_EN_DISABLE;
        err_flag |= color12_set_config( ctx, config );
    }
    else
    {
        err_flag = COLOR12_ERROR;
    }
    return err_flag;
}

err_t color12_generic_write ( color12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color12_generic_read ( color12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color12_sw_reset ( color12_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = color12_generic_read( ctx, COLOR12_REG_SYSTEM_CONTROL, &data_buf, 1 );
    data_buf |= COLOR12_SET_SW_RESET;
    err_flag |= color12_generic_write( ctx, COLOR12_REG_SYSTEM_CONTROL, &data_buf, 1 );
    return err_flag;
}

err_t color12_set_config ( color12_t *ctx, color12_config_t config ) 
{
    uint8_t data_buf = DUMMY;
    data_buf  = ( config.rgb_gain  & 0x03 ) << 4;
    data_buf |=   config.meas_mode & 0x03;
    err_t err_flag = color12_generic_write( ctx, COLOR12_REG_MODE_CONTROL1, &data_buf, 1 );
    data_buf  = ( config.flc_gain  & 0x07 ) << 3;
    data_buf |=   config.flc_mode  & 0x01;
    err_flag |= color12_generic_write( ctx, COLOR12_REG_MODE_CONTROL2, &data_buf, 1 );
    data_buf  = ( config.int_sel   & 0x03 ) << 2;
    data_buf |= ( config.rgb_en    & 0x01 ) << 1;
    data_buf |=   config.flc_en    & 0x01;
    err_flag |= color12_generic_write( ctx, COLOR12_REG_MODE_CONTROL3, &data_buf, 1 );
    return err_flag;
}

err_t color12_get_config ( color12_t *ctx, color12_config_t *config ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = color12_generic_read( ctx, COLOR12_REG_MODE_CONTROL1, &data_buf, 1 );
    config->rgb_gain  = ( data_buf >> 4 ) & 0x01;
    config->meas_mode =   data_buf        & 0x03;
    err_flag |= color12_generic_read( ctx, COLOR12_REG_MODE_CONTROL2, &data_buf, 1 );
    config->flc_gain = ( data_buf >> 3 ) & 0x07;
    config->flc_mode =   data_buf        & 0x01;
    err_flag |= color12_generic_read( ctx, COLOR12_REG_MODE_CONTROL3, &data_buf, 1 );
    config->int_sel = ( data_buf >> 2 ) & 0x03;
    config->rgb_en  = ( data_buf >> 1 ) & 0x01;
    config->flc_en  =   data_buf        & 0x01;
    return err_flag;
}

err_t color12_get_color_data ( color12_t *ctx, color12_color_sel_t color_sel, uint16_t *color_data ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = color12_generic_read( ctx, COLOR12_REG_RED_DATA_L + ( color_sel * 2 ), &data_buf, 1 );
    *color_data = data_buf;
    *color_data <<= 8;
    data_buf = DUMMY;
    err_flag |= color12_generic_read( ctx, COLOR12_REG_RED_DATA_H + ( color_sel * 2 ), &data_buf, 1 );
    *color_data |= data_buf;
    return err_flag;
}

err_t color12_get_device_id ( color12_t *ctx, uint8_t *device_id ) 
{
    return color12_generic_read( ctx, COLOR12_REG_MANUFACTURER_ID, device_id, 1 );
}

uint8_t color12_get_int_pin ( color12_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
