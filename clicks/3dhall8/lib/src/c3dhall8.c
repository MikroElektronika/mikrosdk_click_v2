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
 * @file c3dhall8.c
 * @brief 3D Hall 8 Click Driver.
 */

#include "c3dhall8.h"

#define MASK_LOWER      0xF0
#define MASK_UPPER      0x0F
#define MASK_TEMP_LSB   0xC0

#define MAGNET_RES      7.7

#define TEMP_LSB_25     1180
#define TEMP_VAL_25     25
#define TEMP_RES        0.24

void c3dhall8_cfg_setup ( c3dhall8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL8_SET_DEV_ADDR;
}

err_t c3dhall8_init ( c3dhall8_t *ctx, c3dhall8_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t c3dhall8_default_cfg ( c3dhall8_t *ctx ) 
{
    c3dhall8_generic_write( ctx, C3DHALL8_REG_CONFIG_1, 0x01 );
    
    c3dhall8_generic_write( ctx, C3DHALL8_REG_MOD1, 0x10 );
 
    return C3DHALL8_OK;
}

err_t c3dhall8_generic_write ( c3dhall8_t *ctx, uint8_t reg, uint8_t tx_buf )
{
    uint8_t data_buf[ 2 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_buf;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t c3dhall8_generic_read ( c3dhall8_t *ctx, uint8_t reg, uint8_t *rx_buf )
{
    memset( ctx->receiver_buff, 0, C3DHALL8_RX_BUFFER );
    
    err_t flag = i2c_master_read( &ctx->i2c, ctx->receiver_buff, 0x16 );
    *rx_buf = ctx->receiver_buff[ reg ];
    
    return flag;
}

void c3dhall8_read_sensor_data ( c3dhall8_t *ctx, c3dhall8_data_t *sensor_data )
{
    volatile int16_t x_axis;
    volatile int16_t y_axis;
    volatile int16_t z_axis;
    volatile int16_t temperature;
    
    memset( ctx->receiver_buff, 0, C3DHALL8_RX_BUFFER );
    i2c_master_read( &ctx->i2c, ctx->receiver_buff, 0x16 );
    
    x_axis = ctx->receiver_buff[ C3DHALL8_REG_MAGNETIC_X_MSB ];
    x_axis <<= 8;
    x_axis |= ( ctx->receiver_buff[ C3DHALL8_REG_MAGNETIC_XY_LSB ] & MASK_LOWER );
    x_axis >>= 4;
    sensor_data->x_axis = x_axis * MAGNET_RES;
    
    y_axis = ctx->receiver_buff[ C3DHALL8_REG_MAGNETIC_Y_MSB ];
    y_axis <<= 4;
    y_axis |= ( ctx->receiver_buff[ C3DHALL8_REG_MAGNETIC_XY_LSB ] & MASK_UPPER );
    y_axis <<= 4;
    y_axis >>= 4;
    sensor_data->y_axis = y_axis * MAGNET_RES;
    
    z_axis = ctx->receiver_buff[ C3DHALL8_REG_MAGENTIC_Z_MSB ];
    z_axis <<= 4;
    z_axis |= ( ctx->receiver_buff[ C3DHALL8_REG_TEMPERATURE_Z_LSB ] & MASK_UPPER );
    z_axis <<= 4;
    z_axis >>= 4;
    sensor_data->z_axis = z_axis * MAGNET_RES;
    
    temperature = ctx->receiver_buff[ C3DHALL8_REG_TEMPERATURE_MSB ];
    temperature <<= 8;
    temperature |= ( ctx->receiver_buff[ C3DHALL8_REG_TEMPERATURE_Z_LSB ] & MASK_TEMP_LSB );
    temperature >>= 4;
    sensor_data->temperature = ( temperature - TEMP_LSB_25 ) * TEMP_RES + TEMP_VAL_25;
}

float c3dhall8_get_xyz_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data )
{
    return 200 * ( sensor_data.x_axis + sensor_data.y_axis - ( sensor_data.y_axis * 2 ) ) / 
                 ( sensor_data.x_axis + sensor_data.y_axis + ( sensor_data.y_axis * 2 ) );
}

float c3dhall8_get_xy_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data )
{
    return 200 * ( sensor_data.x_axis + sensor_data.y_axis ) / 
                 ( sensor_data.x_axis + sensor_data.y_axis );
}

// ------------------------------------------------------------------------- END
