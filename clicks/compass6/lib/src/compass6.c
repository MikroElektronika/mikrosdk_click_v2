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
 * @file compass6.c
 * @brief Compass 6 Click Driver.
 */

#include "compass6.h"

void compass6_cfg_setup ( compass6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COMPASS6_SET_DEV_ADDR;
}

err_t compass6_init ( compass6_t *ctx, compass6_cfg_t *cfg ) 
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
    
    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t compass6_default_cfg ( compass6_t *ctx ) 
{
    uint8_t temp_data = 0;
    //Software reset
    err_t ret_val = compass6_generic_write( ctx, COMPASS6_REG_CTRL3, 0x80 );
    do 
    {
        compass6_generic_read( ctx, COMPASS6_REG_CTRL3, &temp_data );
        Delay_10ms( );
    } while ( ( temp_data & 0x80 ) > 0 );
    //Enable reading
    ret_val |= compass6_generic_write( ctx, COMPASS6_REG_CTRL1, 0x8C );
    //15bit resolution
    ret_val |= compass6_generic_write( ctx, COMPASS6_REG_CTRL4, 0x90 );
    
    return ret_val;
}

err_t compass6_generic_write ( compass6_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t compass6_generic_read ( compass6_t *ctx, uint8_t reg, uint8_t *rx_data )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 1 );
}

uint8_t compass6_data_ready ( compass6_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

err_t compass6_get_axes_data ( compass6_t *ctx, compass6_axes_t *axes_data )
{
    uint8_t temp_data;
    //X
    err_t ret_val = compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_X_LSB, &temp_data );
    axes_data->x = temp_data;
    ret_val |= compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_X_MSB, &temp_data );
    axes_data->x |= ( int16_t )temp_data << 8;
    //Y
    ret_val |= compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_Y_LSB, &temp_data );
    axes_data->y = temp_data;
    ret_val |= compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_Y_MSB, &temp_data );
    axes_data->y |= ( int16_t )temp_data << 8;
    //Z
    ret_val |= compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_Z_LSB, &temp_data );
    axes_data->z = temp_data;
    ret_val |= compass6_generic_read( ctx, COMPASS6_REG_OUTPUT_Z_MSB, &temp_data );
    axes_data->z |= ( int16_t )temp_data << 8;
    
    return ret_val;
}

// ------------------------------------------------------------------------- END
