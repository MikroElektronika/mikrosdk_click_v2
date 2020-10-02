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

#include "capextend.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void capextend_cfg_setup ( capextend_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPEXTEND_SLAVE_ADDRESS;
}

CAPEXTEND_RETVAL capextend_init ( capextend_t *ctx, capextend_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CAPEXTEND_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return CAPEXTEND_OK;
}

void capextend_generic_write ( capextend_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void capextend_generic_read ( capextend_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

int8_t capextend_read_msb_buttons ( capextend_t *ctx )
{
    uint8_t msb_byte;

    capextend_generic_read( ctx, CAPEXTEND_MSB_BUTTONS_ADDR, &msb_byte, 1 );

    return msb_byte;
}

int8_t capextend_read_lsb_buttons ( capextend_t *ctx )
{
    uint8_t lsb_byte;

    capextend_generic_read( ctx, CAPEXTEND_LSB_BUTTONS_ADDR, &lsb_byte, 1 );

    return lsb_byte;
}

void capextend_reset ( capextend_t *ctx )
{
    capextend_set_rst_low( ctx );
    Delay_100ms();
    capextend_set_rst_high( ctx );
    Delay_100ms();
}

void capextend_set_rst_high ( capextend_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void capextend_set_rst_low ( capextend_t *ctx )
{
    digital_out_low( &ctx->rst );
}

uint8_t capextend_get_int_input ( capextend_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

