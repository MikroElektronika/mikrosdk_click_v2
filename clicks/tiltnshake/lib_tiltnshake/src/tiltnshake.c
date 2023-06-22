/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "tiltnshake.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tiltnshake_cfg_setup ( tiltnshake_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TILTNSHAKE_MMA8491Q_I2C;
}

err_t tiltnshake_init ( tiltnshake_t *ctx, tiltnshake_cfg_t *cfg )
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

    // Output pins 
    digital_out_init( &ctx->en, cfg->en );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TILTNSHAKE_OK;
}

void tiltnshake_generic_write ( tiltnshake_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

void tiltnshake_generic_read ( tiltnshake_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void tiltnshake_enable ( tiltnshake_t *ctx )
{
    digital_out_high( &ctx->en );
    Delay_10ms( );
}

void tiltnshake_disable ( tiltnshake_t *ctx )
{
    digital_out_low( &ctx->en );
    Delay_10ms( );
}

void tiltnshake_read_status_and_axis ( tiltnshake_t *ctx, uint8_t *status, 
                                       float *out_x, float *out_y, float *out_z )
{
    int16_t raw_data = 0;
    uint8_t temp[ 7 ] = { 0 };
    Delay_1ms( );
    tiltnshake_generic_read( ctx, TILTNSHAKE_STATUS_REG, temp, 7 );
    *status = temp[ 0 ];
    raw_data = ( ( ( int16_t ) temp[ 1 ] << 8 ) | temp[ 2 ] );
    *out_x = ( raw_data >> 2 ) / 1024.0;
    raw_data = ( ( ( int16_t ) temp[ 3 ] << 8 ) | temp[ 4 ] );
    *out_y = ( raw_data >> 2 ) / 1024.0;
    raw_data = ( ( ( int16_t ) temp[ 5 ] << 8 ) | temp[ 6 ] );
    *out_z = ( raw_data >> 2 ) / 1024.0;
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

