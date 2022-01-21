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
 * @file pressure17.c
 * @brief Pressure 17 Click Driver.
 */

#include "pressure17.h"

void pressure17_cfg_setup ( pressure17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE17_SET_DEV_ADDR;
}

err_t pressure17_init ( pressure17_t *ctx, pressure17_cfg_t *cfg ) 
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

err_t pressure17_default_cfg ( pressure17_t *ctx ) 
{
    err_t error_flag = PRESSURE17_OK;
    
    if ( PRESSURE17_ERROR == pressure17_check_communication ( ctx ) )
    {
        return PRESSURE17_ERROR;
    }
    error_flag |= pressure17_write_register ( ctx, PRESSURE17_REG_POWER_DOWN, PRESSURE17_POWER_ACTIVE );
    error_flag |= pressure17_write_register ( ctx, PRESSURE17_REG_RESET, PRESSURE17_RSTB_ACTIVE );
    error_flag |= pressure17_write_register ( ctx, PRESSURE17_REG_MODE_CONTROL, PRESSURE17_MODE_AVE_NUM_64_TIMES | 
                                                                                PRESSURE17_MODE_DR_EN | 
                                                                                PRESSURE17_MODE_CONTINUOUS_MODE );
    
    return error_flag;
}

err_t pressure17_generic_write ( pressure17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t pressure17_generic_read ( pressure17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t pressure17_write_register ( pressure17_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pressure17_generic_write( ctx, reg, &data_in, 1 );
}

err_t pressure17_read_register ( pressure17_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pressure17_generic_read( ctx, reg, data_out, 1 );
}

err_t pressure17_check_communication ( pressure17_t *ctx )
{
    uint8_t manufacturer_id, part_id;
    err_t error_flag = pressure17_read_register( ctx, PRESSURE17_REG_MANUFACTURER_ID, &manufacturer_id );
    error_flag |= pressure17_read_register( ctx, PRESSURE17_REG_PART_ID, &part_id );
    if ( ( PRESSURE17_OK == error_flag ) && 
         ( PRESSURE17_MANUFACTURER_ID == manufacturer_id ) && 
         ( PRESSURE17_PART_ID == part_id ) )
    {
        return PRESSURE17_OK;
    }
    return PRESSURE17_ERROR;
}

err_t pressure17_read_data ( pressure17_t *ctx, float *pressure, float *temperature )
{
    uint8_t rx_buf[ 6 ] = { 0 };
    if ( PRESSURE17_OK == pressure17_generic_read ( ctx, PRESSURE17_REG_STATUS, rx_buf, 6 ) )
    {
        if ( rx_buf[ 0 ] & PRESSURE17_STATUS_RD_DRDY )
        {
            uint32_t pressure_count = ( ( uint32_t ) rx_buf[ 1 ] << 14 ) | 
                                      ( ( uint16_t ) rx_buf[ 2 ] << 6 ) | 
                                      ( rx_buf[ 3 ] & 0x3F );
            *pressure = ( float ) pressure_count / PRESSURE17_PRESS_COUNTS_PER_MBAR;
            int16_t temperature_count = ( ( uint16_t ) rx_buf[ 4 ] << 8 ) | rx_buf[ 5 ];
            *temperature = ( float ) temperature_count / PRESSURE17_TEMP_COUNTS_PER_C;
            return PRESSURE17_OK;
        }
    }
    return PRESSURE17_ERROR;
}

uint8_t pressure17_get_int_pin ( pressure17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
