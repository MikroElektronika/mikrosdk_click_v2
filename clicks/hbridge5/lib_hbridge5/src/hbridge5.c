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

#include "hbridge5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hbridge5_cfg_setup ( hbridge5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl  = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an      = HAL_PIN_NC;
    cfg->rst      = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HBRIDGE5_DEVICE_SLAVE_ADDR_0_0;
}

HBRIDGE5_RETVAL hbridge5_init ( hbridge5_t *ctx, hbridge5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HBRIDGE5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return HBRIDGE5_OK;

}

void hbridge5_default_cfg ( hbridge5_t *ctx )
{
    Delay_100ms( );
    hbridge5_rst_state( ctx, 0 );
    Delay_100ms( );
    hbridge5_rst_state( ctx, 1 );
    Delay_100ms( );
    hbridge5_write_byte( ctx, HBRIDGE5_CMD_CONFIGURATION, HBRIDGE5_ENABLE_ALL_OUTPUT_PORT );
    Delay_100ms( );
}

void hbridge5_generic_write ( hbridge5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void hbridge5_generic_read ( hbridge5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void hbridge5_rst_state ( hbridge5_t *ctx, uint8_t state )
{
    if ( state != 0 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

uint8_t hbridge5_get_interrupt_state ( hbridge5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t hbridge5_read_byte ( hbridge5_t *ctx, uint8_t cmd )
{
    uint8_t rd_reg[ 1 ];
    
    i2c_master_write_then_read( &ctx->i2c, &cmd, 1, rd_reg, 1 );

    return rd_reg[ 0 ];
}

void hbridge5_write_byte ( hbridge5_t *ctx, uint8_t cmd, uint8_t data_in )
{
    uint8_t wr_reg[ 2 ];
    
    wr_reg[ 0 ] = cmd;
    wr_reg[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, wr_reg, 2 ); 
}

void hbridge5_set_port ( hbridge5_t *ctx, uint8_t port, uint8_t value )
{
    uint8_t port_data = 0xFF;

    if ( value == 1 )
    {
        port_data = port_data | port;
    }
    else
    {
       port_data = port_data & ( ~port );
    }
    
    hbridge5_write_byte( ctx, HBRIDGE5_CMD_OUTPUT_PORT, port_data );
}
    
void hbridge5_reverse ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 1 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_PHASE, 0 );
}

void hbridge5_forward ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 1 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_PHASE, 1 );
}

void hbridge5_brake_low ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 0 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_BRAKE, 1 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_B_MODE, 0 );
}

void hbridge5_brake_high ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 0 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_BRAKE, 1 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_B_MODE, 1 );
}

void hbridge5_sync_decay_0 ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 0 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_PHASE, 0 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_BRAKE, 0 );
}

void hbridge5_sync_decay_1 ( hbridge5_t *ctx )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_ENABLE, 0 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_PHASE, 1 );
    hbridge5_set_port( ctx, HBRIDGE5_PORT_BRAKE, 0 );
}

void hbridge5_sleep ( hbridge5_t *ctx, uint8_t state )
{
    hbridge5_set_port( ctx, HBRIDGE5_PORT_N_SLEEP, state );
    Delay_1ms( );
}

void hbridge5_configuration ( hbridge5_t *ctx, uint8_t cfg_data )
{
    uint8_t write_data;
    write_data = ~cfg_data;
    hbridge5_write_byte( ctx, HBRIDGE5_CMD_CONFIGURATION, write_data );
}

uint8_t hbridge5_n_fault_check ( hbridge5_t *ctx )
{
    uint8_t result;
    result = hbridge5_read_byte( ctx, HBRIDGE5_CMD_INPUT_PORT );
    result &= 0x20;
    
    if ( result )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// ------------------------------------------------------------------------- END

