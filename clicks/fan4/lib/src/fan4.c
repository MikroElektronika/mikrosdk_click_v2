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

#include "fan4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fan4_cfg_setup ( fan4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = FAN4_SLAVE_ADDRESS;
}

FAN4_RETVAL fan4_init ( fan4_t *ctx, fan4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return FAN4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return FAN4_OK;
}

void fan4_default_cfg ( fan4_t *ctx )
{
    // Click default configuration

    fan4_set_output( ctx, FAN4_MIN_VOLT_SCALE, FAN4_BOOST_START_TIMER_DIS );
}

void fan4_generic_write ( fan4_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );   
}

void fan4_generic_read ( fan4_t *ctx, uint8_t *data_out )
{
    i2c_master_read( &ctx->i2c, data_out, 1 );   
}

FAN4_RETVAL fan4_set_output ( fan4_t *ctx, uint16_t output_volt, uint8_t boost_start_timer )
{
    uint8_t cmd_byte;
    float temp;

    if ( output_volt > FAN4_MAX_VOLT_SCALE )
    {
        return FAN4_VOLT_RANGE_CHECK_MASK;
    }
    if ( boost_start_timer > 1 )
    {
        return FAN4_BS_TIMER_CHECK_MASK;
    }

    temp = output_volt / FAN4_DAC_LSB;
    cmd_byte = temp;
    cmd_byte |= ( boost_start_timer << 6 );

    fan4_generic_write ( ctx, cmd_byte );

    return FAN4_CHECK_OK;
}

uint8_t fan4_check_diagnostic ( fan4_t *ctx )
{
    uint8_t rx_data;

    fan4_generic_read( ctx, &rx_data );

    return rx_data;
}

// ------------------------------------------------------------------------- END

