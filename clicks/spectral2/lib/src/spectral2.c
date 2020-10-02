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

#include "spectral2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t get_status ( spectral2_t *ctx, uint8_t status );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void spectral2_cfg_setup ( spectral2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x49;
}

SPECTRAL2_RETVAL spectral2_init ( spectral2_t *ctx, spectral2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SPECTRAL2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_write( &ctx->rst, 1 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPECTRAL2_OK;
}

void spectral2_default_cfg ( spectral2_t *ctx, uint8_t cfg_data )
{
    // Click default configuration 

     uint8_t write_reg;
     uint8_t virtual_reg = 0x04;

     while ( get_status( ctx, 0x02 ) );

     write_reg = ( virtual_reg | 0x80 );
     spectral2_generic_write( ctx, 0x01, &write_reg, 1 );
    
     Delay_100ms( );
     while ( get_status( ctx, 0x02 ) );
     
     write_reg = cfg_data;
     spectral2_generic_write( ctx, 0x01, &write_reg, 1 );
     
     Delay_100ms( );
     Delay_100ms( );
}

void spectral2_generic_write ( spectral2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void spectral2_generic_read ( spectral2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t spectral2_read_byte ( spectral2_t *ctx, uint8_t virtual_reg )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 1 ];
    
    while ( get_status( ctx, 0x02 ) );
    
    spectral2_generic_write( ctx, 0x01, &virtual_reg, 1 );
    
    while ( get_status( ctx, 0x01 ) );

    write_reg[ 0 ] = 0x02;

    i2c_master_write( &ctx->i2c, write_reg, 1 ); 
    
    Delay_100ms( );

    i2c_master_read( &ctx->i2c, read_reg, 1 );

    Delay_100ms( );

    return read_reg[ 0 ];
}

void spectral2_reset ( spectral2_t *ctx )
{
   digital_out_write( &ctx->rst, 1 );
   Delay_100ms( );
   digital_out_write( &ctx->rst, 0 );
   Delay_100ms( );
   digital_out_write( &ctx->rst, 1 );
   Delay_1sec( );
   Delay_1sec( );
}

void spectral2_set_integration_time ( spectral2_t *ctx, uint8_t cur_time )
{
    uint8_t write_reg;
    uint8_t virtual_reg = 0x05;

    while ( get_status( ctx, 0x02 ) );

    write_reg = ( virtual_reg | 0x80 );
    spectral2_generic_write( ctx, 0x01, &write_reg, 1 );

    Delay_100ms( );
    while ( get_status( ctx, 0x02 ) );

    write_reg = cur_time;
    spectral2_generic_write( ctx, 0x01, &write_reg, 1 );

    Delay_100ms( );
    Delay_100ms( );
}

uint8_t spectral2_get_temperature ( spectral2_t *ctx )
{
    uint8_t write_reg;
    uint8_t read_reg[1];

    while ( get_status( ctx, 0x02 ) );

    write_reg = 0x06;
    spectral2_generic_write( ctx, 0x01, &write_reg, 1 );

    while ( get_status( ctx, 0x01 ) );

    write_reg = 0x02;
    spectral2_generic_read( ctx, write_reg, read_reg, 1 );

    return read_reg[ 0 ];
}

void spectral2_led_control ( spectral2_t *ctx, uint8_t led_data )
{
     uint8_t write_reg;
     uint8_t virtual_reg = 0x07;

     while ( get_status( ctx, 0x02 ) );

     write_reg = ( virtual_reg | 0x80 );
     spectral2_generic_write( ctx, 0x01, &write_reg, 1 );

     Delay_100ms( );
     while ( get_status( ctx, 0x02 ) );

     write_reg = led_data;
     spectral2_generic_write( ctx, 0x01, &write_reg, 1 );

     Delay_100ms( );
     Delay_100ms( );
}

int16_t spectral2_get_data ( spectral2_t *ctx, uint8_t data_reg )
{
    uint16_t value;
    
    value = spectral2_read_byte( ctx, data_reg);
    value = value << 8;
    value = value | spectral2_read_byte( ctx, data_reg + 1 );

    Delay_100ms( );
    Delay_100ms( );
    
    return value;
}

float spectral2_get_calibrated_data ( spectral2_t *ctx, uint8_t data_reg )
{
    uint32_t value;
    float float_data;
    
    value = spectral2_read_byte( ctx, data_reg );
    value = value << 8;
    value = value | spectral2_read_byte( ctx, data_reg + 1 );
    value = value << 8;
    value = value | spectral2_read_byte( ctx, data_reg + 2 );
    value = value << 8;
    value = value | spectral2_read_byte( ctx, data_reg + 3 );

    memcpy( &float_data, &value, 4 );
    
    return float_data;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t get_status ( spectral2_t *ctx, uint8_t status )
{
     uint8_t read_reg[ 1 ];
 

     spectral2_generic_read( ctx, 0x00, read_reg, 1 );

     if ( ( read_reg[ 0 ] & status ) != 0 )
     {
        return 1;
     }
     else
     {
        return 0;
     }
}

static void memcpy ( void *dest, void *src, uint8_t n )
{
    char *dp = dest;
    char *sp = src;
    
    while ( n-- )
    {
        *dp++ = *sp++;
    }
}

// ------------------------------------------------------------------------- END

