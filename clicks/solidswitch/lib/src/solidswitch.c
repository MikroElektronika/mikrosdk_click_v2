/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file solidswitch.c
 * @brief SolidSwitch Click Driver.
 */

#include "solidswitch.h"

void solidswitch_cfg_setup ( solidswitch_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SOLIDSWITCH_DEV_ADDR_A1_GND_A0_GND;
}

err_t solidswitch_init ( solidswitch_t *ctx, solidswitch_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t solidswitch_default_cfg ( solidswitch_t *ctx ) 
{
    solidswitch_reset ( ctx );
    solidswitch_write_single ( ctx, SOLIDSWITCH_DISABLE_ALL_OUTPUTS );
    
    return SOLIDSWITCH_OK;
}

err_t solidswitch_write_single ( solidswitch_t *ctx, uint8_t logic_state ) 
{
    uint8_t data_buf[ 1 ];
    
    data_buf[ 0 ] = logic_state;

    return i2c_master_write( &ctx->i2c, data_buf, 1 );
}

err_t solidswitch_write_two_bytes ( solidswitch_t *ctx, uint8_t logic_state, uint8_t int_mask ) 
{
    uint8_t data_buf[ 2 ];
    
    data_buf[ 0 ] = logic_state;
    data_buf[ 1 ] = int_mask;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t solidswitch_read_single ( solidswitch_t *ctx, uint8_t *logic_state ) 
{
    return i2c_master_read( &ctx->i2c, logic_state, 1 );
}

err_t solidswitch_read_two_bytes ( solidswitch_t *ctx, uint8_t *logic_state, uint8_t *transition_flags ) 
{
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    
    error_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    *logic_state = rx_buf[ 0 ]; 
    *transition_flags = rx_buf[ 1 ]; 
    
    return error_flag;
}

void solidswitch_reset ( solidswitch_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

uint8_t solidswitch_get_int_state ( solidswitch_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
