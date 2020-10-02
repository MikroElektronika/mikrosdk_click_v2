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

#include "touchpad.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchpad_cfg_setup ( touchpad_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TOUCHPAD_DEVICE_SLAVE_ADDR;
}

TOUCHPAD_RETVAL touchpad_init ( touchpad_t *ctx, touchpad_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TOUCHPAD_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TOUCHPAD_OK;
}

void touchpad_default_cfg ( touchpad_t *ctx )
{
    // Click default configuration

    digital_out_high( &ctx->rst );
}

void touchpad_generic_write ( touchpad_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void touchpad_generic_read ( touchpad_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void touchpad_get_touch_coordinate ( touchpad_t *ctx, touchpad_cord_t *cord )
{
    uint8_t rx_data[ 3 ];

    touchpad_generic_read( ctx, TOUCHPAD_REG_TOUCH_X, rx_data, 3 );

    cord->x = rx_data[ 0 ];
    cord->x = ( cord->x << 3 ) | ( rx_data[ 2 ] >> 4 );
    cord->y = rx_data[ 1 ];
    cord->y = ( cord->y << 3 ) | ( rx_data[ 2 ] & 0x0F );
}

uint8_t touchpad_get_interrupt_state ( touchpad_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void touchpad_reset( touchpad_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t touchpad_get_event_state ( touchpad_t *ctx )
{
    uint8_t state;

    touchpad_generic_read( ctx, TOUCHPAD_REG_TOUCH_STATE, &state, 1 );

    if ( ( state & TOUCHPAD_TOUCH_IS_PRESENT ) != 0 )
    {
       return TOUCHPAD_EVENT_TOUCH;
    }
    else if ( ( state & TOUCHPAD_GESTURE_IS_PRESENT ) != 0 )
    {
       return TOUCHPAD_EVENT_GESTURE;
    }
    return TOUCHPAD_NO_EVENT;
}

uint8_t touchpad_get_gesture_type ( touchpad_t *ctx )
{
    uint8_t rx_data;

    touchpad_generic_read( ctx, TOUCHPAD_REG_GESTURE_STATE, &rx_data, 1 );

    return rx_data;
}

// ------------------------------------------------------------------------- END

