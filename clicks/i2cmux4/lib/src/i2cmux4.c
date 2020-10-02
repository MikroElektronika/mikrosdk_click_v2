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

#include "i2cmux4.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2cmux4_cfg_setup ( i2cmux4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CMUX4_I2C_SLAVE_ADDRESS_0;
}

I2CMUX4_RETVAL i2cmux4_init ( i2cmux4_t *ctx, i2cmux4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2CMUX4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2CMUX4_OK;
}

void i2cmux4_generic_write ( i2cmux4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void i2cmux4_generic_read ( i2cmux4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void i2cmux4_power_on
(  i2cmux4_t *ctx, uint8_t enable )
{
    if ( enable == I2CMUX4_ENABLE_POWER_ON )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void i2cmux4_hw_reset 
( i2cmux4_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

void i2cmux4_write_cmd 
( i2cmux4_t *ctx, uint8_t cmd_data )
{
    i2c_master_write( &ctx->i2c, &cmd_data, 1 );  
}

uint8_t i2cmux4_read_cmd 
( i2cmux4_t *ctx )
{
    uint8_t rx_buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, 0, 0, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void i2cmux4_set_channel
( i2cmux4_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr )
{
    switch ( sel_ch )
    {
        case 0:
        {
            i2cmux4_write_cmd( ctx, I2CMUX4_SEL_CH_ALL_DISABLE );
            break;
        }
        case 1:
        {
            i2cmux4_write_cmd( ctx, I2CMUX4_SEL_CH_0 );
            break;
        }
        case 2:
        {
            i2cmux4_write_cmd( ctx, I2CMUX4_SEL_CH_1 );
            break;
        }
        default:
        {
            i2cmux4_write_cmd( ctx, I2CMUX4_SEL_CH_ALL_DISABLE );
            break;
        }
    }
    
    ctx->rmt_slave_addr = ch_slave_addr;
}

uint8_t i2cmux4_get_ch_interrupt
( i2cmux4_t *ctx )
{
    uint8_t ch_int_num;
    
    ch_int_num = i2cmux4_read_cmd( ctx );
    
    ch_int_num &= I2CMUX4_INTERRUPT_BIT_MASK;
    ch_int_num >>= 4;

    return ch_int_num;
}

void i2cmux4_rmt_write_bytes 
( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes )
{
    uint16_t n_cnt;
    uint8_t tx_buf[ 255 ];

    tx_buf[ 0 ] = reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ )
    {
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->rmt_slave_addr );
    i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1 ); 

}

void i2cmux4_rmt_read_bytes
( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_set_slave_address( &ctx->i2c, ctx->rmt_slave_addr );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, p_rx_data, n_bytes );
}

uint8_t i2cmux4_check_int 
( i2cmux4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

