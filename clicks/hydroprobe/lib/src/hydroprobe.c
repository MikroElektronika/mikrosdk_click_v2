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

#include "hydroprobe.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hydroprobe_cfg_setup ( hydroprobe_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HYDROPROBE_SLAVE_ADR;
}

HYDROPROBE_RETVAL hydroprobe_init ( hydroprobe_t *ctx, hydroprobe_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HYDROPROBE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );    
    
    return HYDROPROBE_OK;
}

void hydroprobe_generic_write ( hydroprobe_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void hydroprobe_generic_read ( hydroprobe_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t hydroprobe_read_raw ( hydroprobe_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    i2c_master_read( &ctx->i2c, rx_buf, 2 ); 

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result &= 0x0FFF;

    return result;
}

uint16_t hydroprobe_avg_val ( hydroprobe_t *ctx )
{
    uint32_t avg = 0;
    uint8_t cnt;

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        avg += hydroprobe_read_raw( ctx );
        Delay_1ms( );
    }
    
    avg /= 100;

    return ( uint16_t ) avg;
}

uint16_t hydroprobe_max_val ( hydroprobe_t *ctx )
{
    uint16_t tmp = 0;
    uint16_t max = 0;
    uint8_t cnt;
    
    max = hydroprobe_read_raw( ctx );

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        tmp = hydroprobe_read_raw( ctx );
        if ( tmp > max )
        {
            max = tmp;
        }
        Delay_1ms( );
    }

    return max;
}

uint16_t hydroprobe_min_val ( hydroprobe_t *ctx )
{
    uint16_t tmp = 0;
    uint16_t min = 65500;
    uint8_t cnt;
    
    min = hydroprobe_read_raw( ctx );

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        tmp = hydroprobe_read_raw( ctx );
        if ( tmp < min )
        {
            min = tmp;
        }
        Delay_1ms( );
    }

    return min;
}

uint8_t hydroprobe_rel_env_hum ( hydroprobe_t *ctx, uint16_t dry_val, uint16_t wet_val )
{
    uint16_t raw_val;
    float result = 0.0;

    raw_val = hydroprobe_avg_val( ctx );

    if ( raw_val > dry_val )
    {
        raw_val = dry_val;
    }
    if ( raw_val < wet_val )
    {
        raw_val = wet_val;
    }

    result = 100.0 - ( ( ( ( float ) raw_val - ( float ) wet_val ) * 100.0 ) / ( ( float ) dry_val - ( float ) wet_val ) );

    return ( uint8_t ) result;
}

// ------------------------------------------------------------------------- END

