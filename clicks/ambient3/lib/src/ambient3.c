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

#include "ambient3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t status_check ( ambient3_t *ctx, uint8_t status_val );
static void hw_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient3_cfg_setup ( ambient3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL; 
    cfg->i2c_address = AMBIENT3_DEVICE_SLAVE_ADDRESS;
}

void ambient3_default_cfg ( ambient3_t *ctx )
{
    ambient3_hardware_reset( ctx );
}

AMBIENT3_RETVAL ambient3_init ( ambient3_t *ctx, ambient3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );    
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AMBIENT3_OK;
}

void ambient3_write_byte ( ambient3_t *ctx, uint8_t virtual_reg, uint8_t data_buf )
{
    uint8_t tx_buf[ 2 ];
 
    while ( status_check( ctx, 0x02 ) ) {}

    tx_buf[ 0 ] = 0x01;
    tx_buf[ 1 ] = ( virtual_reg | 0x80 ); 

    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 

    while ( status_check( ctx, 0x02 ) ) {}

    tx_buf[ 0 ] = 0x01;
    tx_buf[ 1 ] = data_buf;

    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
}

uint8_t ambient3_read_byte ( ambient3_t *ctx, uint8_t virtual_reg )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_buf[ 1 ];

    while ( status_check( ctx, 0x02 ) ) {}

    write_reg[ 0 ] = 0x01;
    write_reg[ 1 ] = virtual_reg;
    
    i2c_master_write( &ctx->i2c, write_reg, 2 );   

    while ( !status_check( ctx, 0x01 ) ) {}
    
    write_reg[ 0 ] = 0x02;

    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_buf, 1 ); 

    return read_buf[ 0 ];
}

void ambient3_hardware_reset ( ambient3_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms();

    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );

    digital_out_high( &ctx->rst );
    Delay_1sec( );
    Delay_1sec( );
}

uint8_t ambient3_get_device_temperature ( ambient3_t *ctx )
{
    uint8_t temp;
    
    temp = ambient3_read_byte( ctx, AMBIENT3_REG_DEVICE_TEMP );
    return temp;
}

uint16_t ambient3_get_data_in_lux ( ambient3_t *ctx )
{
    uint16_t read_data;

    read_data = ambient3_read_byte( ctx, AMBIENT3_REG_CAL_LUX_MSB );
    read_data = read_data << 8;
    read_data = read_data | ambient3_read_byte( ctx, AMBIENT3_REG_CAL_LUX_LSB );

    return read_data;
}

uint16_t ambient3_get_cct_data ( ambient3_t *ctx )
{
    uint16_t read_data;

    read_data = ambient3_read_byte( ctx, AMBIENT3_REG_CAL_CCT_MSB );
    read_data = read_data << 8;
    read_data = read_data | ambient3_read_byte( ctx, AMBIENT3_REG_CAL_CCT_LSB );

    return read_data;
}

uint8_t ambient3_get_interrupt ( ambient3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t status_check ( ambient3_t *ctx, uint8_t status_val )
{
    uint8_t read_reg[ 1 ];
    uint8_t write_reg[ 1 ];
    write_reg[ 0 ] = 0x00;

    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 1 );
    
    if ( ( read_reg[ 0 ] & status_val ) != 0)
    {
       return 1;
    }
    else
    {
       return 0;
    }
}

// ------------------------------------------------------------------------- END

