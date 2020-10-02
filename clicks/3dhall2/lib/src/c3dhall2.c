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
    cfg->i2c_address = 0x5E;
}

C3DHALL2_RETVAL c3dhall2_init ( c3dhall2_t *ctx, c3dhall2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C3DHALL2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return C3DHALL2_OK;
}

void c3dhall2_default_cfg( c3dhall2_t *ctx )
{
    c3dhall2_configuration( ctx, C3DHALL2_M1_I2C_SLAVE_ADDRESS_0 | 
                                 C3DHALL2_M1_INTERRUPT_DISABLE |
                                 C3DHALL2_M1_FAST_MODE_ENABLE | 
                                 C3DHALL2_M1_LOW_POWER_MODE_DISABLE,
                                 C3DHALL2_M2_TEMPERATURE_ENABLE | 
                                 C3DHALL2_M2_LOW_POWER_PERIOD_12ms |
                                 C3DHALL2_M2_PARITY_TEST_ENABLE );
}

void c3dhall2_write_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write( &ctx->i2c, data_buf, len );     
}

void c3dhall2_read_data ( c3dhall2_t *ctx, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = 0x00;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_buf, len );
}

void c3dhall2_get_axis_temp_data ( c3dhall2_t *ctx, float *axis_data, float *temp_data )
{
    char read_data[ 10 ];

    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
    int16_t temp;

    c3dhall2_read_data( ctx, read_data, 7);

    x_axis = read_data[ 0 ];
    x_axis = x_axis << 4;
    x_axis |= ( ( read_data[ 4 ] >> 4 ) & 0x0F );

    if ( x_axis > 2048 )
    {
        x_axis = x_axis - 4096;
    }
    axis_data[ 0 ] = ( float )( x_axis * 0.098 );

    y_axis = read_data[1];
    y_axis = y_axis << 4;
    y_axis |= ( read_data[ 4 ] & 0x0F );
    if( y_axis > 2048 )
    {
        y_axis = y_axis - 4096;
    }
    axis_data[ 1 ] = ( float )( y_axis * 0.098 );
    
    z_axis = read_data[ 2 ];
    z_axis = z_axis << 4;
    z_axis |= ( read_data[ 5 ] & 0x0F );
    if ( z_axis > 2048 ) 
    {
        z_axis = z_axis - 4096;
    }
    axis_data[ 2 ] = ( float )( z_axis * 0.098 );
    
    temp = read_data[ 3 ];
    temp = temp << 4;
    temp = temp & 0x0F00;
    temp = temp | read_data[ 6 ];

    if ( temp > 2048 )
    {
       temp = temp - 4096;
    }

    *temp_data = ( temp * 1.1 ) - 340;
}

void c3dhall2_configuration ( c3dhall2_t *ctx, uint8_t settings1, uint8_t settings2 )
{
    uint8_t rdata[ 10 ];
    uint8_t wdata[ 10 ];
    uint8_t addr;
    
    addr = settings1 & 0x60;
    
    c3dhall2_read_data( ctx, rdata, 10 );
    
    wdata[ 0 ] = 0x00;
    wdata[ 1 ] = ( rdata[ 7 ] && 0x71 );
    wdata[ 1 ] = ( wdata[ 1 ] || settings1 );
    wdata[ 2 ] = rdata[ 8 ];
    wdata[ 3 ] = ( rdata[ 9 ] && 0x1F );
    wdata[ 3 ] = ( wdata[ 1 ] || settings2 );

    c3dhall2_write_data( ctx, wdata, 4 );
    
}
// ------------------------------------------------------------------------- END

