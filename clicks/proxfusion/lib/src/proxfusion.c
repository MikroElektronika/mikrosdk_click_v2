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

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void function_delay( );

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

PROXFUSION_RETVAL proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXFUSION_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXFUSION_OK;
}

void proxfusion_default_cfg ( proxfusion_t *ctx )
{
    // Click default configuration

    proxfusion_set_system_reg( ctx,
        PROXFUSION_SYSTEM_RESET |PROXFUSION_EVENT_MODE_1 |
        PROXFUSION_CLOCK_16MHz | PROXFUSION_ATI_ENABLED |
        PROXFUSION_ATI_BAND_1_16 | PROXFUSION_SYSTEM_ATI_RESET );

    proxfusion_set_event_reg( ctx, PROXFUSION_MASK_SYS_EVENT );
}

void proxfusion_generic_write ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proxfusion_generic_read ( proxfusion_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float proxfusion_get_temperature ( proxfusion_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t temp_data;
    float temperature;

    proxfusion_generic_read( ctx, PROXFUSION_REG_OUT_TEMP, rx_buf, 2 );

    temp_data = rx_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= rx_buf[ 0 ];

    temperature = ( temp_data / 8.0 ) - 273.15;

    return temperature;
}

uint8_t proxfusion_get_touch ( proxfusion_t *ctx )
{
    uint8_t rx_data;

    proxfusion_generic_read( ctx, 0x12, &rx_data, 1 );

    if ( rx_data == 0x11 )
    {
        return 1;
    }
    if ( rx_data == 0x22 )
    {
        return 2;
    }
    if ( rx_data == 0x33 )
    {
        return 3;
    }

    return 0;
}

void proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg )
{
    proxfusion_generic_write( ctx, 0xD0, &cfg, 1 );
    function_delay( );
}

void proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg )
{
    proxfusion_generic_write( ctx, 0xD7, &cfg, 1 );
    function_delay( );
}

uint8_t proxfusion_get_interrupt ( proxfusion_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void function_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

