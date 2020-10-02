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

PROXIMITY6_RETVAL proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY6_OK;
}

void proximity6_default_cfg ( proximity6_t *ctx )
{
    uint16_t temp_buff[ 1 ];
    
    temp_buff[ 0 ] = 0x000f;
    proximity6_generic_write( ctx, 0x0c, temp_buff, 1 );
    temp_buff[ 0 ] = 0x1010;
    proximity6_generic_write( ctx, 0x10, temp_buff, 1 );
    temp_buff[ 0 ] = 0x004c;
    proximity6_generic_write( ctx, 0x11, temp_buff, 1 );
    temp_buff[ 0 ] = 0x5f0c;
    proximity6_generic_write( ctx, 0x12, temp_buff, 1 );
    temp_buff[ 0 ] = 0xada5;
    proximity6_generic_write( ctx, 0x13, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0080;
    proximity6_generic_write( ctx, 0x14, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x15, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0600;
    proximity6_generic_write( ctx, 0x16, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x17, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2693;
    proximity6_generic_write( ctx, 0x18, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0004;
    proximity6_generic_write( ctx, 0x19, temp_buff, 1 );
    temp_buff[ 0 ] = 0x4280;
    proximity6_generic_write( ctx, 0x1a, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0060;
    proximity6_generic_write( ctx, 0x1b, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2094;
    proximity6_generic_write( ctx, 0x1c, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0020;
    proximity6_generic_write( ctx, 0x1d, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0001;
    proximity6_generic_write( ctx, 0x1e, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x1f, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0320;
    proximity6_generic_write( ctx, 0x20, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0A13;
    proximity6_generic_write( ctx, 0x21, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0320;
    proximity6_generic_write( ctx, 0x22, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0113;
    proximity6_generic_write( ctx, 0x23, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x24, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2412;
    proximity6_generic_write( ctx, 0x25, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2412;
    proximity6_generic_write( ctx, 0x26, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0022;
    proximity6_generic_write( ctx, 0x27, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x28, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0300;
    proximity6_generic_write( ctx, 0x29, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0600;
    proximity6_generic_write( ctx, 0x2a, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0400;
    proximity6_generic_write( ctx, 0x2b, temp_buff, 1 );
    temp_buff[ 0 ] = 0x6000;
    proximity6_generic_write( ctx, 0x2c, temp_buff, 1 );
    temp_buff[ 0 ] = 0x4000;
    proximity6_generic_write( ctx, 0x2d, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x2e, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x2f, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x30, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x31, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0F4F;
    proximity6_generic_write( ctx, 0x32, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0008;
    proximity6_generic_write( ctx, 0x33, temp_buff, 1 );
    temp_buff[ 0 ] = 0xE400;
    proximity6_generic_write( ctx, 0x34, temp_buff, 1 );
    temp_buff[ 0 ] = 0x8080;
    proximity6_generic_write( ctx, 0x38, temp_buff, 1 );
    temp_buff[ 0 ] = 0x8080;
    proximity6_generic_write( ctx, 0x39, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2000;
    proximity6_generic_write( ctx, 0x3a, temp_buff, 1 );
    temp_buff[ 0 ] = 0x1f00;
    proximity6_generic_write( ctx, 0x3b, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2000;
    proximity6_generic_write( ctx, 0x3c, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2000;
    proximity6_generic_write( ctx, 0x3d, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x3e, temp_buff, 1 );
    temp_buff[ 0 ] = 0x8069;
    proximity6_generic_write( ctx, 0x40, temp_buff, 1 );
    temp_buff[ 0 ] = 0x1f2f;
    proximity6_generic_write( ctx, 0x41, temp_buff, 1 );
    temp_buff[ 0 ] = 0x4000;
    proximity6_generic_write( ctx, 0x42, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x43, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0008;
    proximity6_generic_write( ctx, 0x44, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x46, temp_buff, 1 );
    temp_buff[ 0 ] = 0x00ef;
    proximity6_generic_write( ctx, 0x48, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x49, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x45, temp_buff, 1 );
}

void proximity6_generic_write ( proximity6_t *ctx, uint8_t reg, uint16_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    uint8_t cnt2;
    
    tx_buf[ 0 ] = reg;
    cnt2 = 0;

    for ( cnt = 1; cnt < ( len + 1 ); ( cnt+=2 ) )
    {
        tx_buf[ cnt ] = ( data_buf[ cnt2 ] >> 8 );
        tx_buf[ cnt + 1 ] = data_buf[ cnt2 ];
        cnt2++;
    }

    i2c_master_write( &ctx->i2c, tx_buf, ( len * 2 ) + 1 );    
}

uint8_t proximity6_generic_read ( proximity6_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t n_registers )
{
    uint8_t tx_buf[ 1 ];
    uint8_t buff_data[ 2 ];
    uint8_t cnt;
    uint8_t n_reg;
    uint8_t reg_addr;
    uint16_t ret_val;

    if ( reg > 0x6F )
    { 
        return 1;
    }
    if ( reg < 0x07 )
    {
        cnt = reg;
        n_reg = 0;
        while ( cnt < 0x07 )
        {
            cnt++;
            n_reg++;
        }
    }
    else if ( reg > 0x67 )
    {
        cnt = reg;
        n_reg = 0;
        while ( cnt < 0x70 )
        {
            cnt++;
            n_reg++;
        }
    }
    else
    {
        n_reg = 1;
    }

    if ( n_registers > n_reg )
    {
        n_registers = n_reg;
    }

    tx_buf [ 0 ] = reg;
    
    for ( cnt = 0; cnt < n_registers; cnt++ )
    {
        i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, buff_data, 2 );

        ret_val = buff_data[ 0 ];
        ret_val <<= 8;
        ret_val |= buff_data[ 1 ];
        data_out[ cnt ] = ret_val;
        tx_buf[ 0 ]++;
    }

    return 0;
}

uint8_t proximity6_set_mode ( proximity6_t *ctx, uint8_t select_mode )
{
    uint16_t temp;

    proximity6_generic_read( ctx, PROXIMITY6_OPERATION_CONTROL_REG, &temp, 1 );

    switch ( select_mode )
    {
        case PROXIMITY6_STANDBY_MODE :
        {
            temp &= 0xEFF0;
            temp |= 0x0000;
            ctx->mode_sel = 0;
            break;
        }
        case PROXIMITY6_PROXIMITY_MODE :
        {
            temp &= 0xEFF0;
            temp |= 0x0001;
            ctx->mode_sel = 1;
        break;
        }
        case PROXIMITY6_SAMPLE_MODE :
        {
            temp &= 0xEFF0;
            temp |= 0x0003;
            ctx->mode_sel = 2;
        break;
        }
        case PROXIMITY6_IDLE_MODE :
        {
            temp |= 0x000F;
            ctx->mode_sel = 3;
        break;
        }
        default :
        {
            return 1;
        }
    }

    proximity6_generic_write( ctx, PROXIMITY6_OPERATION_CONTROL_REG, &temp, 1 );

    return 0;
}

uint8_t proximity6_read_data ( proximity6_t *ctx, uint16_t *axis_out )
{
    uint16_t interr_check;
    uint16_t temp_buff[ 1 ];

    proximity6_generic_read( ctx, PROXIMITY6_INT_STATUS_REG, &interr_check, 1 );
    while ( !( interr_check & 0x003F ) )
    {
        proximity6_generic_read( ctx, PROXIMITY6_INT_STATUS_REG, &interr_check, 1 );
    }
    temp_buff[ 0 ] = 0x003F;
    proximity6_generic_write( ctx, PROXIMITY6_INT_STATUS_REG, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0F4F;
    proximity6_generic_write( ctx, PROXIMITY6_POWER_DOWN_CONT_REG, temp_buff, 1 );

    if ( ( ctx->mode_sel == 1 ) || ( ctx->mode_sel == 2 ) )
    {
        proximity6_generic_read( ctx, PROXIMITY6_DATA_REGISTER_X1_REG, axis_out, 4 );
        temp_buff[ 0 ] = 0x0040;
        proximity6_generic_write( ctx, PROXIMITY6_POWER_DOWN_CONT_REG, temp_buff, 1 );
        return 0;
    }
    else
    {
        temp_buff[ 0 ] = 0x0040;
        proximity6_generic_write( ctx, PROXIMITY6_POWER_DOWN_CONT_REG, temp_buff, 1 );
        return 1;
    }
}

void proximity6_get_position ( proximity6_t *ctx, uint8_t *position )
{
    uint16_t tmp[ 4 ] = { 0 };
    uint8_t i;
    uint16_t max;

    proximity6_read_data( ctx, tmp );

    max = tmp[ 0 ];
    for ( i = 1; i < 4; i++ )
    {
        if ( tmp[ i ] > max )
        {
            max = tmp[ i ];
        }
    }

    if ( ( tmp[ 0 ] != 0 )  &&  ( tmp[ 1 ] != 0 )  && 
         ( tmp[ 2 ] != 0 )  && ( tmp[ 3 ] != 0 ) )
    {
        for ( i = 0; i < 4; i++ )
        {
            if ( max == tmp[ i ] )
            {
                *position = i;
            }
        }
    }
    else
    {
        *position = 4;
    }
}

uint8_t proximity6_display_data ( proximity6_t *ctx, uint8_t *data_value, uint8_t set_resolution )
{
    uint16_t tmp[ 4 ] = { 0 };
    uint8_t count;
    uint16_t resolution;

    switch ( set_resolution )
    {
        case PROXIMITY6_RESOLUTION_300 :
        {
            resolution = 300;
            break;
        }
        case PROXIMITY6_RESOLUTION_400 :
        {
            resolution = 400;
            break;
        }
        case PROXIMITY6_RESOLUTION_500 :
        {
            resolution = 500;
            break;
        }
        case PROXIMITY6_RESOLUTION_600 :
        {
            resolution = 600;
            break;
        }
        case PROXIMITY6_RESOLUTION_700 :
        {
            resolution = 700;
            break;
        }
        default :
        {
            return 1;
        }
    }

    proximity6_read_data( ctx, tmp );

    for ( count = 0; count < 4; count++ )
    {
        data_value[ count ] = 0;
    }

    for ( count = 0; count < 4; count++ )
    {
        while ( tmp[ count ] >= resolution )
        {
            tmp[ count ] -= resolution;
            data_value[ count ] += 1;
        }
    }

    return 0;
}

void proximity6_load_settings ( proximity6_t *ctx )
{
    uint16_t temp_buff[ 1 ];

    temp_buff[ 0 ] = 0x0320;
    proximity6_generic_write( ctx, 0x20, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0A13;
    proximity6_generic_write( ctx, 0x21, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0320;
    proximity6_generic_write( ctx, 0x22, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0113;
    proximity6_generic_write( ctx, 0x23, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2412;
    proximity6_generic_write( ctx, 0x25, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2412;
    proximity6_generic_write( ctx, 0x26, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x27, temp_buff, 1 );
    temp_buff[ 0 ] = 0x2693;
    proximity6_generic_write( ctx, 0x18, temp_buff, 1 );
    temp_buff[ 0 ] = 0x1F2F;
    proximity6_generic_write( ctx, 0x41, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0000;
    proximity6_generic_write( ctx, 0x24, temp_buff, 1 );
    temp_buff[ 0 ] = 0x00C0;
    proximity6_generic_write( ctx, 0x48, temp_buff, 1 );
    temp_buff[ 0 ] = 0x8069;
    proximity6_generic_write( ctx, 0x40, temp_buff, 1 );
    temp_buff[ 0 ] = 0x0040;
    proximity6_generic_write( ctx, 0x32, temp_buff, 1 );
    temp_buff[ 0 ] = 0x003F;
    proximity6_generic_write( ctx, 0x49, temp_buff, 1 );
}

uint8_t proximity6_check_interrupt ( proximity6_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END

