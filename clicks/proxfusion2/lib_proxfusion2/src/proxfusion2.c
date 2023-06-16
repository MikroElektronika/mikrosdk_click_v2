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

#include "proxfusion2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proxfusion2_cfg_setup ( proxfusion2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x44;
}

err_t proxfusion2_init ( proxfusion2_t *ctx, proxfusion2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    
    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return PROXFUSION2_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins
    digital_in_init( &ctx->rdy, cfg->rdy );

    return PROXFUSION2_OK;
}

err_t proxfusion2_default_cfg ( proxfusion2_t *ctx )
{
    if ( PROXFUSION2_ERROR == proxfusion2_check_communication( ctx ) )
    {
        return PROXFUSION2_ERROR;
    }
    
    proxfusion2_write_byte( ctx, 0x40, 0x01 );
    proxfusion2_write_byte( ctx, 0x41, 0x01 );
    proxfusion2_write_byte( ctx, 0x42, 0x02 );
    proxfusion2_write_byte( ctx, 0x43, 0x67 );
    proxfusion2_write_byte( ctx, 0x44, 0x67 );
    proxfusion2_write_byte( ctx, 0x45, 0x67 );
    proxfusion2_write_byte( ctx, 0x46, 0xE0 );
    proxfusion2_write_byte( ctx, 0x47, 0xE0 );
    proxfusion2_write_byte( ctx, 0x48, 0xD0 );
    proxfusion2_write_byte( ctx, 0x49, 0x06 );
    proxfusion2_write_byte( ctx, 0x4A, 0x06 );
    proxfusion2_write_byte( ctx, 0x4B, 0x06 );
    proxfusion2_write_byte( ctx, 0x4C, 0x01 );
    proxfusion2_write_byte( ctx, 0x4D, 0x01 );
    proxfusion2_write_byte( ctx, 0x4E, 0x06 );
    proxfusion2_write_byte( ctx, 0x4F, 0x06 );

    proxfusion2_write_byte( ctx, 0x50, 0x80 );
    proxfusion2_write_byte( ctx, 0x51, 0x01 );
    proxfusion2_write_byte( ctx, 0x52, 0xAA );
    proxfusion2_write_byte( ctx, 0x53, 0xB0 );
    proxfusion2_write_byte( ctx, 0x54, 0x8C );
    proxfusion2_write_byte( ctx, 0x55, 0x18 );
    proxfusion2_write_byte( ctx, 0x56, 0x18 );
    proxfusion2_write_byte( ctx, 0x57, 0x19 );
    
    proxfusion2_write_byte( ctx, 0x60, 0x32 );
    proxfusion2_write_byte( ctx, 0x61, 0x4E );
    proxfusion2_write_byte( ctx, 0x62, 0x32 );
    proxfusion2_write_byte( ctx, 0x63, 0x4E );
    proxfusion2_write_byte( ctx, 0x64, 0x28 );
    proxfusion2_write_byte( ctx, 0x65, 0x20 );
    proxfusion2_write_byte( ctx, 0x66, 0x16 );
    proxfusion2_write_byte( ctx, 0x67, 0x20 );
    proxfusion2_write_byte( ctx, 0x68, 0x28 );

    proxfusion2_write_byte( ctx, 0x70, 0x04 ); 
    
    proxfusion2_write_byte( ctx, 0x80, 0x11 );
    proxfusion2_write_byte( ctx, 0x81, 0x1E );
    proxfusion2_write_byte( ctx, 0x82, 0x32 );
    proxfusion2_write_byte( ctx, 0x83, 0x4E );
    
    proxfusion2_write_byte( ctx, 0x90, 0x03 );
    proxfusion2_write_byte( ctx, 0x91, 0x50 );
    proxfusion2_write_byte( ctx, 0x92, 0x00 );
    proxfusion2_write_byte( ctx, 0x93, 0x48 );
    proxfusion2_write_byte( ctx, 0x94, 0x00 );
    proxfusion2_write_byte( ctx, 0x95, 0x19 );
    proxfusion2_write_byte( ctx, 0x96, 0x19 );

    proxfusion2_write_byte( ctx, 0xA0, 0x55 ); 
    
    proxfusion2_write_byte( ctx, 0xC0, 0x00 ); 
    proxfusion2_write_byte( ctx, 0xC1, 0x06 );
    proxfusion2_write_byte( ctx, 0xC2, 0x00 );
    proxfusion2_write_byte( ctx, 0xC3, 0x00 );
    
    proxfusion2_write_byte( ctx, 0xD0, 0x29 ); 
    proxfusion2_write_byte( ctx, 0xD1, 0x7F ); 
    proxfusion2_write_byte( ctx, 0xD2, 0xC3 );  
    proxfusion2_write_byte( ctx, 0xD7, 0x28 ); 

    Delay_1sec();
    return PROXFUSION2_OK;
}

void proxfusion2_write_byte ( proxfusion2_t *ctx, uint8_t reg, uint8_t d_data)
{
    uint8_t write_reg[ 2 ] = { 0 };
    
    write_reg[ 0 ] = reg;
    write_reg[ 1 ] = d_data;  

    i2c_master_write( &ctx->i2c, write_reg, 2 ); 
    Delay_10ms( );
}

uint8_t proxfusion2_read_byte ( proxfusion2_t *ctx, uint8_t reg )
{
    uint8_t read_reg = 0;

    i2c_master_write( &ctx->i2c, &reg, 1 );
    Delay_10ms();
    i2c_master_read( &ctx->i2c, &read_reg, 1 );
    
    return read_reg;
}

uint16_t proxfusion2_read_data ( proxfusion2_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ] = { 0 };

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, read_reg, 2 );
    
    return ( ( uint16_t ) read_reg[ 1 ] << 8 ) | read_reg[ 0 ];
}

err_t proxfusion2_check_communication ( proxfusion2_t *ctx )
{
    uint8_t product_number = 0;
    uint8_t sw_number = 0;
    uint8_t hw_number = 0;
    
    product_number = proxfusion2_read_byte( ctx, 0x00 );
    sw_number = proxfusion2_read_byte( ctx, 0x01 );
    hw_number = proxfusion2_read_byte( ctx, 0x02 );
    
    if ( 0x46 != product_number )
    {
        return PROXFUSION2_ERROR;
    }
    if ( 0x09 != sw_number )
    {
        return PROXFUSION2_ERROR;
    }
    if ( 0x82 != hw_number )
    {
        return PROXFUSION2_ERROR;
    }
    return PROXFUSION2_OK;
}

uint8_t proxfusion2_detect_touch ( proxfusion2_t *ctx )
{
    if ( 0x02 & proxfusion2_read_byte( ctx, 0x13 ) )
    {
        return PROXFUSION2_TOUCH_DETECTED;
    }
    return PROXFUSION2_TOUCH_NOT_DETECTED;
}

uint8_t proxfusion2_detect_dark_light ( proxfusion2_t *ctx, uint8_t *als_range )
{
    uint8_t read_reg = proxfusion2_read_byte( ctx, 0x16 );
    
    *als_range = read_reg & 0x0F;
    
    if ( read_reg & 0x80 )
    {
        return PROXFUSION2_AMBIENT_LIGHT;
    }
    return PROXFUSION2_AMBIENT_DARK;
}

uint8_t proxfusion2_detect_hall ( proxfusion2_t *ctx )
{
    uint8_t read_reg = proxfusion2_read_byte( ctx, 0x19 );
    
    if ( read_reg & 0x03 )
    {
        if ( read_reg & 0x01 )
        {
            return PROXFUSION2_HALL_SOUTH;
        }
        return PROXFUSION2_HALL_NORTH;
    }
    return PROXFUSION2_HALL_UNKNOWN;
}

// ------------------------------------------------------------------------- END

