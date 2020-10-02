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

#include "joystick2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void joystick2_cfg_setup ( joystick2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = JOYSTICK2_DEVICE_SLAVE_ADDR_0_0;
}

JOYSTICK2_RETVAL joystick2_init ( joystick2_t *ctx, joystick2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return JOYSTICK2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return JOYSTICK2_OK;
}

void joystick2_default_cfg ( joystick2_t *ctx )
{
    // Click default configuration

    joystick2_set_cfg_register( ctx, JOYSTICK2_CFG_ENABLE_BUTTON | JOYSTICK2_CFG_ENABLE_DOWN_POS |
                                     JOYSTICK2_CFG_ENABLE_LEFT_POS | JOYSTICK2_CFG_ENABLE_RIGHT_POS |
                                     JOYSTICK2_CFG_ENABLE_UP_POS );
}

void joystick2_generic_write ( joystick2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void joystick2_generic_read ( joystick2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void joystick2_reset ( joystick2_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t joystick2_get_interrupt_state ( joystick2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void joystick2_set_cfg_register ( joystick2_t *ctx, uint8_t cfg_data )
{
    uint8_t tx_data;

    tx_data = ~cfg_data;
    joystick2_generic_write ( ctx, JOYSTICK2_CMD_CONFIGURATION, &tx_data, 1 );
}

uint8_t joystick2_get_position ( joystick2_t *ctx )
{
    uint8_t rx_data;

    joystick2_generic_read( ctx, JOYSTICK2_CMD_INPUT_PORT, &rx_data, 1 );

    rx_data = ~rx_data;
    rx_data &= 0x1F;

    return rx_data;
}

// ------------------------------------------------------------------------- END

