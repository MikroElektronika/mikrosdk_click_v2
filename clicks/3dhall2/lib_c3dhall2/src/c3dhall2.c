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

#include "c3dhall2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3dhall2_cfg_setup ( c3dhall2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C3DHALL2_DEVICE_ADDRESS;
}

err_t c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg )
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

    return C3DHALL2_OK;
}

err_t c3dhall2_default_cfg( c3dhall2_t *ctx )
{
    return c3dhall2_configuration ( ctx, C3DHALL2_M1_I2C_SLAVE_ADDRESS_0 | 
                                         C3DHALL2_M1_INTERRUPT_DISABLE |
                                         C3DHALL2_M1_FAST_MODE_ENABLE | 
                                         C3DHALL2_M1_LOW_POWER_MODE_DISABLE,
                                         C3DHALL2_M2_TEMPERATURE_ENABLE | 
                                         C3DHALL2_M2_LOW_POWER_PERIOD_12MS |
                                         C3DHALL2_M2_PARITY_TEST_ENABLE );
}

err_t c3dhall2_write_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len )
{
    return i2c_master_write ( &ctx->i2c, data_buf, len );     
}

err_t c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len )
{
    uint8_t reg_addr = 0;
    return i2c_master_write_then_read ( &ctx->i2c, &reg_addr, 1, data_buf, len );
}

err_t c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data )
{
    uint8_t data_buf[ 7 ] = { 0 };
    int16_t x_axis = 0;
    int16_t y_axis = 0;
    int16_t z_axis = 0;
    int16_t temp = 0;

    err_t error_flag = c3dhall2_read_data ( ctx, data_buf, 7 );
    
    if ( data_buf[ 3 ] & 0x03 )
    {
        error_flag = C3DHALL2_ERROR;
    }
    else
    {
        x_axis = ( ( int16_t ) data_buf[ 0 ] << 4 ) | ( ( data_buf[ 4 ] >> 4 ) & 0x0F );
        x_axis <<= 4;
        x_axis >>= 4;
        axis_data[ 0 ] = ( float ) ( x_axis * 0.098 );

        y_axis = ( ( int16_t ) data_buf[ 1 ] << 4 ) | ( data_buf[ 4 ] & 0x0F );
        y_axis <<= 4;
        y_axis >>= 4;
        axis_data[ 1 ] = ( float ) ( y_axis * 0.098 );
        
        z_axis = ( ( int16_t ) data_buf[ 2 ] << 4 ) | ( data_buf[ 5 ] & 0x0F );
        z_axis <<= 4;
        z_axis >>= 4;
        axis_data[ 2 ] = ( float ) ( z_axis * 0.098 );
        
        temp = ( ( int16_t ) ( data_buf[ 3 ] & 0xF0 ) << 4 ) | data_buf[ 6 ];
        temp <<= 4;
        temp >>= 4;
        *temp_data = ( temp - 340 ) * 1.1 + 25.0;
    }
    
    return error_flag;
}

err_t c3dhall2_configuration ( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2 )
{
    err_t error_flag = C3DHALL2_OK;
    uint8_t data_buf[ 10 ] = { 0 };
    uint8_t parity_bit = 0;
    
    error_flag |= c3dhall2_read_data( ctx, data_buf, 10 );
    
    data_buf[ 0 ] = 0x00;
    data_buf[ 1 ] = ( data_buf[ 7 ] & 0x18 ) | ( settings1 & 0x67 );
    data_buf[ 2 ] = data_buf[ 8 ];
    data_buf[ 3 ] = ( data_buf[ 9 ] & 0x1F ) | ( settings2 & 0xE0 );
    
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
    {
        if ( data_buf[ 1 ] & ( 1 << bit_cnt ) )
        {
            parity_bit++;
        }
        if ( data_buf[ 2 ] & ( 1 << bit_cnt ) )
        {
            parity_bit++;
        }
        if ( data_buf[ 3 ] & ( 1 << bit_cnt ) )
        {
            parity_bit++;
        }
    }
    data_buf[ 1 ] |= ( ( parity_bit << 7 ) & 0x80 );

    error_flag |= c3dhall2_write_data( ctx, data_buf, 4 );
    
    return error_flag;
}
// ------------------------------------------------------------------------- END

