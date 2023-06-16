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

#include "proximity6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity6_cfg_setup ( proximity6_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x64;
}

err_t proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return PROXIMITY6_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY6_OK;
}

err_t proximity6_default_cfg ( proximity6_t *ctx )
{
    err_t error_flag = PROXIMITY6_OK;
    uint16_t reg_data = 0;
    
    reg_data = 0x000F;
    error_flag |= proximity6_generic_write( ctx, 0x0C, &reg_data, 1 );
    reg_data = 0x1010;
    error_flag |= proximity6_generic_write( ctx, 0x10, &reg_data, 1 );
    reg_data = 0x004C;
    error_flag |= proximity6_generic_write( ctx, 0x11, &reg_data, 1 );
    reg_data = 0x1C08;
    error_flag |= proximity6_generic_write( ctx, 0x12, &reg_data, 1 );
    reg_data = 0xADA5;
    error_flag |= proximity6_generic_write( ctx, 0x13, &reg_data, 1 );
    reg_data = 0x0080;
    error_flag |= proximity6_generic_write( ctx, 0x14, &reg_data, 1 );
    reg_data = 0x0600;
    error_flag |= proximity6_generic_write( ctx, 0x16, &reg_data, 1 );
    reg_data = 0x36A0;
    error_flag |= proximity6_generic_write( ctx, 0x18, &reg_data, 1 );
    reg_data = 0x0004;
    error_flag |= proximity6_generic_write( ctx, 0x19, &reg_data, 1 );
    reg_data = 0x425E;
    error_flag |= proximity6_generic_write( ctx, 0x1A, &reg_data, 1 );
    reg_data = 0x0020;
    error_flag |= proximity6_generic_write( ctx, 0x1B, &reg_data, 1 );
    reg_data = 0x2094;
    error_flag |= proximity6_generic_write( ctx, 0x1C, &reg_data, 1 );
    reg_data = 0x0020;
    error_flag |= proximity6_generic_write( ctx, 0x1D, &reg_data, 1 );
    reg_data = 0x0001;
    error_flag |= proximity6_generic_write( ctx, 0x1E, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x1F, &reg_data, 1 );
    reg_data = 0x0320;
    error_flag |= proximity6_generic_write( ctx, 0x20, &reg_data, 1 );
    reg_data = 0x0A13;
    error_flag |= proximity6_generic_write( ctx, 0x21, &reg_data, 1 );
    reg_data = 0x0320;
    error_flag |= proximity6_generic_write( ctx, 0x22, &reg_data, 1 );
    reg_data = 0x0A13;
    error_flag |= proximity6_generic_write( ctx, 0x23, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x24, &reg_data, 1 );
    reg_data = 0x2412;
    error_flag |= proximity6_generic_write( ctx, 0x25, &reg_data, 1 );
    reg_data = 0x2412;
    error_flag |= proximity6_generic_write( ctx, 0x26, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x27, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x28, &reg_data, 1 );
    reg_data = 0x0300;
    error_flag |= proximity6_generic_write( ctx, 0x29, &reg_data, 1 );
    reg_data = 0x0600;
    error_flag |= proximity6_generic_write( ctx, 0x2A, &reg_data, 1 );
    reg_data = 0x0400;
    error_flag |= proximity6_generic_write( ctx, 0x2B, &reg_data, 1 );
    reg_data = 0x6000;
    error_flag |= proximity6_generic_write( ctx, 0x2C, &reg_data, 1 );
    reg_data = 0x4000;
    error_flag |= proximity6_generic_write( ctx, 0x2D, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x2E, &reg_data, 1 );
    reg_data = 0x8000;
    error_flag |= proximity6_generic_write( ctx, 0x2F, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x30, &reg_data, 1 );
    reg_data = 0x0040;
    error_flag |= proximity6_generic_write( ctx, 0x32, &reg_data, 1 );
    reg_data = 0x8080;
    error_flag |= proximity6_generic_write( ctx, 0x38, &reg_data, 1 );
    reg_data = 0x8080;
    error_flag |= proximity6_generic_write( ctx, 0x39, &reg_data, 1 );
    reg_data = 0x2000;
    error_flag |= proximity6_generic_write( ctx, 0x3A, &reg_data, 1 );
    reg_data = 0x2000;
    error_flag |= proximity6_generic_write( ctx, 0x3B, &reg_data, 1 );
    reg_data = 0x2000;
    error_flag |= proximity6_generic_write( ctx, 0x3C, &reg_data, 1 );
    reg_data = 0x2000;
    error_flag |= proximity6_generic_write( ctx, 0x3D, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x3E, &reg_data, 1 );
    reg_data = 0x8099;
    error_flag |= proximity6_generic_write( ctx, 0x40, &reg_data, 1 );
    reg_data = 0x1525;
    error_flag |= proximity6_generic_write( ctx, 0x41, &reg_data, 1 );
    reg_data = 0x4000;
    error_flag |= proximity6_generic_write( ctx, 0x42, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x43, &reg_data, 1 );
    reg_data = 0x000A;
    error_flag |= proximity6_generic_write( ctx, 0x44, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x45, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x46, &reg_data, 1 );
    reg_data = 0x0080;
    error_flag |= proximity6_generic_write( ctx, 0x48, &reg_data, 1 );
    reg_data = 0x0000;
    error_flag |= proximity6_generic_write( ctx, 0x49, &reg_data, 1 );
    
    error_flag |= proximity6_set_mode( ctx, PROXIMITY6_PROXIMITY_MODE );
    return error_flag;
}

err_t proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 511 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt * 2 + 1 ] = ( uint8_t ) ( ( data_buf[ cnt ] >> 8 ) & 0xFF );
        tx_buf[ cnt * 2 + 2 ] = ( uint8_t ) ( data_buf[ cnt ] & 0xFF );
    }
    return i2c_master_write( &ctx->i2c, tx_buf, ( len * 2 ) + 1 );    
}

err_t proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len )
{
    err_t error_flag = PROXIMITY6_OK;
    uint8_t reg_addr = reg;
    uint8_t rx_buf[ 2 ] = { 0 };
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, rx_buf, 2 );
        data_out[ cnt ] = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
        reg_addr++;
    }
    return error_flag;
}

err_t proximity6_set_mode ( proximity6_t *ctx, uint8_t select_mode )
{
    err_t error_flag = PROXIMITY6_OK;
    uint16_t reg_data = 0;

    error_flag |= proximity6_generic_read( ctx, PROXIMITY6_REG_OPERATION_CONTROL, &reg_data, 1 );

    switch ( select_mode )
    {
        case PROXIMITY6_STANDBY_MODE :
        {
            reg_data &= 0xEFF0;
            reg_data |= 0x0000;
            ctx->mode_sel = 0;
            break;
        }
        case PROXIMITY6_PROXIMITY_MODE :
        {
            reg_data &= 0xEFF0;
            reg_data |= 0x0001;
            ctx->mode_sel = 1;
            break;
        }
        case PROXIMITY6_SAMPLE_MODE :
        {
            reg_data &= 0xEFF0;
            reg_data |= 0x0003;
            ctx->mode_sel = 2;
            break;
        }
        case PROXIMITY6_IDLE_MODE :
        {
            reg_data |= 0x000F;
            ctx->mode_sel = 3;
            break;
        }
        default :
        {
            return PROXIMITY6_ERROR;
        }
    }

    error_flag |= proximity6_generic_write( ctx, PROXIMITY6_REG_OPERATION_CONTROL, &reg_data, 1 );
    return error_flag;
}

err_t proximity6_read_data ( proximity6_t *ctx, proximity6_data_t *axis_out )
{
    err_t error_flag = PROXIMITY6_OK;
    uint16_t axis_data[ 4 ] = { 0 };
    uint16_t reg_data = 0;
    if ( proximity6_check_interrupt ( ctx ) )
    {
        return PROXIMITY6_ERROR;
    }
    error_flag |= proximity6_generic_read( ctx, PROXIMITY6_REG_INT_STATUS, &reg_data, 1 );
    error_flag |= proximity6_generic_write( ctx, PROXIMITY6_REG_INT_STATUS, &reg_data, 1 );

    if ( ( 1 == ctx->mode_sel ) || ( 2 == ctx->mode_sel ) )
    {
        error_flag |= proximity6_generic_read( ctx, PROXIMITY6_REG_DATA_REGISTER_X1, axis_data, 4 );
        axis_out->val_x1 = axis_data[ 0 ];
        axis_out->val_x2 = axis_data[ 1 ];
        axis_out->val_y1 = axis_data[ 2 ];
        axis_out->val_y2 = axis_data[ 3 ];
    }
    return error_flag;
}

uint8_t proximity6_check_interrupt ( proximity6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

