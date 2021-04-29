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

#include "clockgen3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t dev_get_dac_value ( double freq );
static uint32_t drv_pow_2 ( uint8_t exp );
static uint8_t dev_get_oct ( double freq );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void clockgen3_cfg_setup ( clockgen3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CLOCKGEN3_SLAVE_ADDRESS_GND;

    cfg->dev_conf = 0x00;
}

CLOCKGEN3_RETVAL clockgen3_init ( clockgen3_t *ctx, clockgen3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    ctx->dev_config = cfg->dev_conf;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CLOCKGEN3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );

    return CLOCKGEN3_OK;
}

void clockgen3_config ( clockgen3_t *ctx, uint8_t cfg )
{
    ctx->dev_config = ( cfg & 0x03 );
}

void clockgen3_set_cs_pin ( clockgen3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cs, state );
}

void clockgen3_generic_write ( clockgen3_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, data_buf, len ); 
}

void clockgen3_generic_read ( clockgen3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void clockgen3_set_freq ( clockgen3_t *ctx, float freq )
{
    uint8_t tx_data[ 2 ];
    uint16_t set_value;
    
    set_value = dev_get_oct( freq ) << 12;
    set_value |= dev_get_dac_value( freq ) << 2;
    set_value |= ctx->dev_config & 0x03;
    
    tx_data[ 0 ] = set_value >> 8;
    tx_data[ 1 ] = set_value;
    
    clockgen3_set_cs_pin( ctx, 0 );
    clockgen3_generic_write( ctx, tx_data, 2 );
    clockgen3_set_cs_pin( ctx, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t dev_get_dac_value ( double freq )
{
    uint8_t oct;
    uint16_t dac_value;
    double calc_data;
    
    oct = dev_get_oct( freq );
    
    // Formula 2048 - ( (2078[Hz] * pow(2, 10 + oct)) / freg[Hz])
    calc_data = 2078.0;
    calc_data *= drv_pow_2( 10 + oct );
    calc_data /= ( freq * 1000 );
    dac_value = 2048 - calc_data;
    dac_value = dac_value & 0x03FF;
    
    return dac_value;
}

static uint32_t drv_pow_2 ( uint8_t exp )
{
    uint8_t cnt;
    uint32_t res = 2;
    
    if ( exp == 0 )
    {
        return 1;
    }
    else if ( exp == 1 )
    {
        return 2;
    }
    else
    {
        for ( cnt = 2; cnt <= exp; cnt++ )
        {
            res *= 2;
        }
    }
    return res;
}

static uint8_t dev_get_oct ( double freq )
{
    if ( ( freq >= 1.039 ) && ( freq < 2.078 ) )
    {
        return CLOCKGEN3_OCT_0;
    }
    else if ( ( freq >= 2.078 ) && ( freq < 4.152 ) )
    {
        return CLOCKGEN3_OCT_1;
    }
    else if ( ( freq >= 4.152 ) && ( freq < 8.304 ) )
    {
        return CLOCKGEN3_OCT_2;
    }
    else if ( ( freq >= 8.304 ) && ( freq < 16.61 ) )
    {
        return CLOCKGEN3_OCT_3;
    }
    else if ( ( freq >= 16.61 ) && ( freq < 33.22 ) )
    {
        return CLOCKGEN3_OCT_4;
    }
    else if ( ( freq >= 33.22 ) && ( freq < 66.43 ) )
    {
        return CLOCKGEN3_OCT_5;
    }
    else if ( ( freq >= 66.43 ) && ( freq < 132.9 ) )
    {
        return CLOCKGEN3_OCT_6;
    }
    else if ( ( freq >= 132.9 ) && ( freq < 265.7 ) )
    {
        return CLOCKGEN3_OCT_7;
    }
    else if ( ( freq >= 265.7 ) && ( freq < 531.4 ) )
    {
        return CLOCKGEN3_OCT_8;
    }
    else if ( ( freq >= 531.4 ) && ( freq < 1063.0 ) )
    {
        return CLOCKGEN3_OCT_9;
    }
    else if ( ( freq >= 1063.0 ) && ( freq < 2126.0 ) )
    {
        return CLOCKGEN3_OCT_10;
    }
    else if ( ( freq >= 2126.0 ) && ( freq < 4252.0 ) )
    {
        return CLOCKGEN3_OCT_11;
    }
    else if ( ( freq >= 4252.0 ) && ( freq < 8503.0 ) )
    {
        return CLOCKGEN3_OCT_12;
    }
    else if ( ( freq >= 8053.0 ) && ( freq < 17010.0 ) )
    {
        return CLOCKGEN3_OCT_13;
    }
    else if ( ( freq >= 17010.0 ) && ( freq < 34010.0 ) )
    {
        return CLOCKGEN3_OCT_14;
    }
    else if ( ( freq >= 34010.0 ) && ( freq < 68030.0 ) )
    {
        return CLOCKGEN3_OCT_15;
    }
    return CLOCKGEN3_OCT_0;
}

// ------------------------------------------------------------------------- END

