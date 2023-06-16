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

#include "proxfusion.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proxfusion_cfg_setup ( proxfusion_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXFUSION_SLAVE_ADDRESS;
}

err_t proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return PROXFUSION_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXFUSION_OK;
}

err_t proxfusion_default_cfg ( proxfusion_t *ctx )
{
    err_t error_flag = PROXFUSION_OK;
    error_flag |= proxfusion_set_system_reg( ctx, PROXFUSION_SYSTEM_RESET | PROXFUSION_EVENT_MODE_1 |
                                                  PROXFUSION_CLOCK_16MHz | PROXFUSION_ATI_ENABLED |
                                                  PROXFUSION_ATI_BAND_1_16 | PROXFUSION_SYSTEM_ATI_RESET );
    Delay_100ms ( );
    error_flag |= proxfusion_set_event_reg( ctx, PROXFUSION_MASK_SYS_EVENT );
    Delay_100ms ( );
    return error_flag;
}

err_t proxfusion_generic_write ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

err_t proxfusion_generic_read ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t proxfusion_get_touch ( proxfusion_t *ctx )
{
    uint8_t rx_data = 0;

    proxfusion_generic_read( ctx, 0x12, &rx_data, 1 );

    if ( 0x11 == rx_data )
    {
        return 1;
    }
    if ( 0x22 == rx_data )
    {
        return 2;
    }
    if ( 0x33 == rx_data )
    {
        return 3;
    }

    return 0;
}

err_t proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg )
{
    return proxfusion_generic_write( ctx, 0xD0, &cfg, 1 );
}

err_t proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg )
{
    return proxfusion_generic_write( ctx, 0xD7, &cfg, 1 );
}

uint8_t proxfusion_get_interrupt ( proxfusion_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

