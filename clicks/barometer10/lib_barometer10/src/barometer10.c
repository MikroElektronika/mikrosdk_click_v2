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
 * @file barometer10.c
 * @brief Barometer 10 Click Driver.
 */

#include "barometer10.h"

/**
 * @brief Barometer 10 pressure and temperature calculation values.
 * @details Definition of pressure and temperature calculation values.
 */
#define BAROMETER10_PRESS_CALC_RAW_DATA            0xFF
#define BAROMETER10_PRESS_CALC_RESOLUTION          4095.0f
#define BAROMETER10_TEMP_CALC_RESOLUTION           100.0f

void barometer10_cfg_setup ( barometer10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER10_DEVICE_ADDRESS_GND;
}

err_t barometer10_init ( barometer10_t *ctx, barometer10_cfg_t *cfg ) 
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

err_t barometer10_default_cfg ( barometer10_t *ctx ) 
{
    uint8_t device_id;
    err_t err_flag = barometer10_get_device_id( ctx, &device_id );
    if ( BAROMETER10_DEVICE_ID == device_id )
    {
        barometer10_sensor_cfg_t default_config;
        default_config.odr = BAROMETER10_ODR_ONE_SHOT;
        default_config.avg = BAROMETER10_AVG_4;
        default_config.fs_mode = BAROMETER10_FS_MODE_1260_hPa;
        default_config.lfpf_cfg = BAROMETER10_LFPF_CFG_ODR4;
        default_config.en_lpfp = BAROMETER10_EN_LPFP_DISABLE;
        default_config.bdu = BAROMETER10_BDU_NO_UPDATE_UNTIL_READ;
        default_config.oneshot = BAROMETER10_ONESHOT_NEW_SET_ACQUIRED;
        default_config.int_h_l = BAROMETER10_INT_H_L_ACTIVE_HIGH;
        default_config.if_add_inc = BAROMETER10_IF_ADD_INC_ENABLE;
        default_config.drdy_pls = BAROMETER10_DRDY_PLS_DISABLE;
        default_config.drdy = BAROMETER10_DRDY_DISABLE;
        default_config.int_en = BAROMETER10_INT_EN_DISABLE;
        Delay_10ms( );
        err_flag |= barometer10_set_config( ctx, default_config );
    }
    else
    {
        err_flag = BAROMETER10_ERROR;    
    }
    return err_flag;
}

err_t barometer10_generic_write ( barometer10_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t barometer10_generic_read ( barometer10_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t barometer10_sw_reset ( barometer10_t *ctx ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    data_buf |= BAROMETER10_SWRESET_BIT_MASK;
    err_flag |= barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    return err_flag;
}

err_t barometer10_get_device_id ( barometer10_t *ctx, uint8_t *device_id ) 
{
    return barometer10_generic_read( ctx, BAROMETER10_REG_WHO_AM_I, device_id, 1 );
}

err_t barometer10_get_config ( barometer10_t *ctx, barometer10_sensor_cfg_t *config )
{
    uint8_t data_buf = 0;
    err_t err_flag = barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG1, &data_buf, 1 );
    config->odr = ( data_buf >> 3 ) & 0x0F;
    config->avg =   data_buf        & 0x07;
    err_flag |= barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    config->fs_mode  = ( data_buf >> 6 ) & 0x01;
    config->lfpf_cfg = ( data_buf >> 4 ) & 0x01;
    config->en_lpfp  = ( data_buf >> 3 ) & 0x01;
    config->bdu      = ( data_buf >> 3 ) & 0x01;
    config->oneshot  =   data_buf        & 0x01;
    err_flag |= barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG3, &data_buf, 1 );
    config->int_h_l    = ( data_buf >> 3 ) & 0x01;
    config->if_add_inc =   data_buf        & 0x01;
    err_flag |= barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG4, &data_buf, 1 );
    config->drdy_pls = ( data_buf >> 6 ) & 0x01;
    config->drdy     = ( data_buf >> 5 ) & 0x01;
    config->int_en   = ( data_buf >> 4 ) & 0x01;
    return err_flag;
}

err_t barometer10_set_config ( barometer10_t *ctx, barometer10_sensor_cfg_t config )
{
    uint8_t data_buf = 0;
    data_buf  = ( config.odr & 0x0F ) << 3;
    data_buf |=   config.avg & 0x07;
    err_t err_flag = barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG1, &data_buf, 1 );
    data_buf  = ( config.fs_mode  & 0x01 ) << 6;
    data_buf |= ( config.lfpf_cfg & 0x01 ) << 5;
    data_buf |= ( config.en_lpfp  & 0x01 ) << 4;
    data_buf |= ( config.bdu      & 0x01 ) << 3;  
    data_buf |=   config.oneshot  & 0x01;
    err_flag |= barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    data_buf  = ( config.int_h_l     & 0x01 ) << 3;
    data_buf |=   config.if_add_inc  & 0x01;
    err_flag |= barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG3, &data_buf, 1 );
    data_buf  = ( config.drdy_pls & 0x01 ) << 6;
    data_buf |= ( config.drdy     & 0x01 ) << 5;
    data_buf |= ( config.int_en   & 0x01 ) << 4;
    err_flag |= barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG4, &data_buf, 1 );
    return err_flag;
}

err_t barometer10_trigger_one_shot ( barometer10_t *ctx )
{
    uint8_t data_buf = 0;
    err_t err_flag = barometer10_generic_read( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    data_buf &= ~BAROMETER10_ONESHOT_NEW_SET_ACQUIRED;
    data_buf |= BAROMETER10_ONESHOT_NEW_SET_ACQUIRED;
    err_flag |= barometer10_generic_write( ctx, BAROMETER10_REG_CTRL_REG2, &data_buf, 1 );
    return err_flag;
}

err_t barometer10_get_pressure_output ( barometer10_t *ctx, int32_t *pressure_raw ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t err_flag = barometer10_generic_read( ctx, BAROMETER10_REG_PRESS_OUT_XL, data_buf, 3 );
    *pressure_raw = data_buf[ 2 ];
    *pressure_raw <<= 8;
    *pressure_raw |= data_buf[ 1 ];
    *pressure_raw <<= 8;
    *pressure_raw |= data_buf[ 0 ];
    *pressure_raw <<= 8;
    *pressure_raw /= BAROMETER10_PRESS_CALC_RAW_DATA;
    return err_flag;
}

err_t barometer10_get_temperature_output ( barometer10_t *ctx, int16_t *temperature_raw ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = barometer10_generic_read( ctx, BAROMETER10_REG_TEMP_OUT_L, data_buf, 2 );
    *temperature_raw = data_buf[ 1 ];
    *temperature_raw <<= 8;
    *temperature_raw |= data_buf[ 0 ];
    return err_flag;
}

err_t barometer10_get_pressure ( barometer10_t *ctx, float *pressure ) 
{
    int32_t pressure_raw;
    barometer10_sensor_cfg_t config;
    barometer10_get_config( ctx, &config );
    Delay_1ms( );
    err_t err_flag = barometer10_trigger_one_shot( ctx );
    err_flag |= barometer10_get_pressure_output( ctx, &pressure_raw );
    *pressure = ( float ) pressure_raw;
    *pressure /= BAROMETER10_PRESS_CALC_RESOLUTION;
    *pressure *= config.fs_mode + 1;
    return err_flag;
}

err_t barometer10_get_temperature ( barometer10_t *ctx, float *temperature ) 
{
    int16_t temperature_raw;
    err_t err_flag = barometer10_trigger_one_shot( ctx );
    err_flag |= barometer10_get_temperature_output( ctx, &temperature_raw );
    *temperature = ( float ) temperature_raw;
    *temperature /= BAROMETER10_TEMP_CALC_RESOLUTION;
    return err_flag;
}

uint8_t barometer10_get_int_pin ( barometer10_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
