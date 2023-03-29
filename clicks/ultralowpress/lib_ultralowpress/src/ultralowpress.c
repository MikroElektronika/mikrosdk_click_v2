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
 * @file ultralowpress.c
 * @brief Ultra-Low Press Click Driver.
 */

#include "ultralowpress.h"

/**
 * @brief Temperature sensitivity/offset macros
 * @details Temperature sensitivity and offset macros for converting data to Celzius.
 */
#define ULTRALOWPRESS_B1                ( 397.2 )
#define ULTRALOWPRESS_B0                ( -16881 )

/**
 * @brief Pressure MIN/MAX macros
 * @details Pressure MIN/MAX macros for converting data to Pascal.
 */
#define ULTRALOWPRESS_P_MIN             ( -20.0 )
#define ULTRALOWPRESS_P_MAX             ( 500.0 )
#define ULTRALOWPRESS_OUT_MIN           ( -26215.0 )
#define ULTRALOWPRESS_OUT_MAX           ( 26214.0 )

/**
 * @brief Status masks
 * @details Mask for temperature and pressure data ready to read.
 */
#define ULTRALOWPRESS_STATUS_TEMP_MASK  0x0010
#define ULTRALOWPRESS_STATUS_PRESS_MASK 0x0008

void ultralowpress_cfg_setup ( ultralowpress_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ULTRALOWPRESS_SET_DEV_ADDR;
}

err_t ultralowpress_init ( ultralowpress_t *ctx, ultralowpress_cfg_t *cfg ) 
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

    if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t ultralowpress_generic_write ( ultralowpress_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t data_buf[ 3 ];
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( tx_data >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( tx_data & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t ultralowpress_generic_read ( ultralowpress_t *ctx, uint8_t reg, uint16_t *rx_data )
{
    uint8_t read_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, read_buf, 2 );
    if ( ULTRALOWPRESS_OK == error_flag )
    {
        *rx_data = ( ( uint16_t ) read_buf[ 1 ] << 8 ) | read_buf[ 0 ];
    }
    return error_flag;
}

void ultralowpress_clear_status ( ultralowpress_t *ctx )
{
    ultralowpress_generic_write( ctx, ULTRALOWPRESS_REG_STATUS, ULTRALOWPRESS_STATUS_CLEAR );
}

uint8_t ultralowpress_ready_to_read ( ultralowpress_t *ctx )
{
    uint16_t read_status = 0;
    ultralowpress_generic_read( ctx, ULTRALOWPRESS_REG_STATUS, &read_status );
    return ( read_status & ULTRALOWPRESS_STATUS_TEMP_MASK ) && ( read_status & ULTRALOWPRESS_STATUS_PRESS_MASK );
}

float ultralowpress_get_press ( ultralowpress_t *ctx )
{
    uint16_t pressure = 0;
    ultralowpress_generic_read( ctx, ULTRALOWPRESS_REG_PRESS, &pressure );
    return ULTRALOWPRESS_P_MIN + ( ( ( int16_t ) pressure - ULTRALOWPRESS_OUT_MIN ) / 
                                   ( ULTRALOWPRESS_OUT_MAX - ULTRALOWPRESS_OUT_MIN ) ) * 
                                   ( ULTRALOWPRESS_P_MAX - ULTRALOWPRESS_P_MIN );
}

float ultralowpress_get_temp ( ultralowpress_t *ctx )
{
    uint16_t temperature = 0;
    ultralowpress_generic_read( ctx, ULTRALOWPRESS_REG_TEMP, &temperature );
    return ( ( int16_t ) temperature - ULTRALOWPRESS_B0 ) / ULTRALOWPRESS_B1;
}

// ------------------------------------------------------------------------- END
