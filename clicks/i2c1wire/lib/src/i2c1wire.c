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

#include "i2c1wire.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2c1wire_cfg_setup ( i2c1wire_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CONEWIRE_I2C_ADDRESS_0;
}

I2C1WIRE_RETVAL i2c1wire_init ( i2c1wire_t *ctx, i2c1wire_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2C1WIRE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return I2C1WIRE_OK;
}

void i2c1wire_generic_write ( i2c1wire_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );     
}

void i2c1wire_generic_read ( i2c1wire_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void i2c1wire_soft_reset ( i2c1wire_t *ctx )
{
    i2c1wire_generic_read( ctx, I2CONEWIRE_COMMAND_RESET, 0, 1 );
}

uint8_t i2c1wire_set_config ( i2c1wire_t *ctx, uint8_t cfg )
{
    uint8_t r_val;
    
    i2c1wire_generic_write( ctx, I2CONEWIRE_COMMAND_WRITECONFIG, &cfg, 1 );

    i2c1wire_generic_read( ctx, I2CONEWIRE_POINTER_DATA, &r_val, 1 );

    cfg = ( ( ~cfg ) >> 4 );

    if ( cfg != r_val )
    {
        i2c1wire_soft_reset( ctx );
        
        return I2CONEWIRE_RESULT_ERROR;
    }
    else
    {
        return I2CONEWIRE_RESULT_OK;
    }
}

uint8_t i2c1wire_set_channel ( i2c1wire_t *ctx, uint8_t chan )
{
    uint8_t w_chan;
    uint8_t r_chan;
    uint8_t check;

    chan %= 8;
    
    i2c1wire_generic_write( ctx, I2CONEWIRE_CMD_CHSL, 0, 0 );

    switch ( chan )
    {
        case 0:
        {
            w_chan = I2CONEWIRE_CH_IO0;
            r_chan = I2CONEWIRE_RCH_IO0;
            break;
        }
        case 1:
        {
            w_chan = I2CONEWIRE_CH_IO1;
            r_chan = I2CONEWIRE_RCH_IO1;
            break;
        }
        case 2:
        {
            w_chan = I2CONEWIRE_CH_IO2;
            r_chan = I2CONEWIRE_RCH_IO2;
            break;
        }
        case 3: 
        {
            w_chan = I2CONEWIRE_CH_IO3;
            r_chan = I2CONEWIRE_RCH_IO3;
            break;
        }
        case 4:
        { 
            w_chan = I2CONEWIRE_CH_IO4;
            r_chan = I2CONEWIRE_RCH_IO4;
            break;
        }
        case 5: 
        {   
            w_chan = I2CONEWIRE_CH_IO5;
            r_chan = I2CONEWIRE_RCH_IO5;
            break;
        }
        case 6: 
        {
            w_chan = I2CONEWIRE_CH_IO6;
            r_chan = I2CONEWIRE_RCH_IO6;
            break;
        }
        case 7:
        {
            w_chan = I2CONEWIRE_CH_IO7;
            r_chan = I2CONEWIRE_RCH_IO7;
            break;
        }
    };

    i2c1wire_generic_write( ctx, I2CONEWIRE_CMD_CHSL, &w_chan, 1 );

    i2c1wire_generic_read( ctx, I2CONEWIRE_COMMAND_SRP, &check, 1 );
    
    if ( check != r_chan )
    {
        return I2CONEWIRE_RESULT_ERROR;
    }
    else
    {
        return I2CONEWIRE_RESULT_OK;
    }
}

void i2c1wire_set_read_pointer ( i2c1wire_t *ctx, uint8_t ptr )
{
    i2c1wire_generic_write( ctx, I2CONEWIRE_POINTER_DATA, &ptr, 1 );
}

void i2c1wire_one_wire_reset ( i2c1wire_t *ctx )
{
    uint8_t temp;

    i2c1wire_generic_read( ctx, I2CONEWIRE_COMMAND_RESETWIRE, &temp, 1 );
}

void i2c1wire_write_byte_one_wire ( i2c1wire_t *ctx, uint8_t input )
{
    uint8_t t_buf[ 2 ];
    uint8_t r_buf[ 2 ];

    t_buf[ 0 ] = I2CONEWIRE_COMMAND_WRITEBYTE;
    t_buf[ 1 ] = input;

    i2c_master_write_then_read( &ctx->i2c, t_buf, 2, r_buf, 2 );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t i2c1wire_read_byte_one_wire ( i2c1wire_t *ctx )
{
    uint8_t t_buf[ 2 ];
    uint8_t r_buf[ 1 ];

    t_buf[ 0 ] = I2CONEWIRE_COMMAND_READBYTE;

    i2c_master_write( &ctx->i2c, t_buf, 1 ); 
    Delay_100ms( );
    
    t_buf[ 0 ] = I2CONEWIRE_COMMAND_SRP;
    t_buf[ 1 ] = I2CONEWIRE_COMMAND_SRP;
    
    i2c_master_write( &ctx->i2c, t_buf, 2 );

    i2c_master_write_then_read( &ctx->i2c, t_buf, 1, r_buf, 1 );

    return r_buf[ 0 ];
}

// ------------------------------------------------------------------------- END

