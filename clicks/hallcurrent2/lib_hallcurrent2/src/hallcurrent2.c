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

#include "hallcurrent2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallcurrent2_cfg_setup ( hallcurrent2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;
}

HALLCURRENT2_RETVAL hallcurrent2_init ( hallcurrent2_t *ctx, hallcurrent2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HALLCURRENT2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return HALLCURRENT2_OK;

}

uint16_t hallcurrent2_generic_read ( hallcurrent2_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 1 ];
    uint16_t data_buff;

    tx_buf [ 0 ] = 0x00;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );

    data_buff = rx_buf[ 0 ];
    data_buff = data_buff << 8;
    data_buff = data_buff | rx_buf[ 1 ];
    data_buff = data_buff & 0x0FFF;

    return data_buff;
}

void hallcurrent2_reset( hallcurrent2_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_10ms();
    digital_out_high( &ctx->rst );
    Delay_100ms();
    digital_out_low( &ctx->rst );
}

int16_t hallcurrent2_get_current( hallcurrent2_t *ctx )
{
    int16_t current;
    int16_t current_data;
    
    current = hallcurrent2_generic_read( ctx );
    
    current_data = current - 2047;
    current_data *= 100;
    current_data = ( current_data / 136.0 ) * 10;
    
    return current_data;
}

// ------------------------------------------------------------------------- END

