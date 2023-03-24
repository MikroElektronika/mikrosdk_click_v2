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
 * @file accel17.c
 * @brief Accel 17 Click Driver.
 */

#include "accel17.h"

void accel17_cfg_setup ( accel17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL17_SET_DEV_ADDR;
}

err_t accel17_init ( accel17_t *ctx, accel17_cfg_t *cfg ) 
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

    if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t accel17_default_cfg ( accel17_t *ctx ) 
{
    return accel17_generic_write( ctx, ACCEL17_REG_ACCEL_CONFIG,
                                       ACCEL17_TOEN_DISABLE |
                                       ACCEL17_BGTST_NORMAL |
                                       ACCEL17_ST_OFF |
                                       ACCEL17_PD_ON );
}

err_t accel17_generic_write ( accel17_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ] = { reg, tx_data };
    return i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

err_t accel17_generic_read ( accel17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t accel17_get_axes_data ( accel17_t *ctx, accel17_axes_t *axes )
{
    int16_t x, y;
    uint8_t read_buf[ 4 ] = { 0 };
    
    err_t ret_val = accel17_generic_read( ctx, ACCEL17_REG_ACCEL_X_MSB, read_buf, 4 );
    
    x = ( ( int16_t )read_buf[ 0 ] << 8 ) | ( int16_t )read_buf[ 1 ];
    
    axes->x = ( x - ACCEL17_OFFSET ) / ACCEL17_SENSITIVITY * ACCEL17_DEGREE_RES;
    
    y = ( ( int16_t )read_buf[ 2 ] << 8 ) | ( int16_t )read_buf[ 3 ];
    axes->y = ( y - ACCEL17_OFFSET ) / ACCEL17_SENSITIVITY * ACCEL17_DEGREE_RES;
    
    return ret_val;
}

// ------------------------------------------------------------------------- END
