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

#include "rng.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rng_cfg_setup ( rng_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RNG_DEVICE_SLAVE_ADDRESS_GND;
    cfg->dev_vref_cfg = 0;
}

RNG_RETVAL rng_init ( rng_t *ctx, rng_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->dev_vref = cfg->dev_vref_cfg;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RNG_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RNG_OK;
}

void rng_default_cfg ( rng_t *ctx )
{
    uint16_t conf_data = RNG_CONFIG_REG_COMP_QUEUE_DISABLE | RNG_CONFIG_REG_COMP_LAT_NON |
                         RNG_CONFIG_REG_COMP_POL_HIGH | RNG_CONFIG_REG_COMP_MODE_TRAD |
                         RNG_CONFIG_REG_DATA_RATE_128_SPS | RNG_CONFIG_REG_DEV_MODE_CONTIN |
                         RNG_CONFIG_REG_PGA_6144 |
                         RNG_CONFIG_REG_MUX_AINP_AINN_0_GND |
                         RNG_CONFIG_REG_OS_NO_EFFECT;
    rng_write_function( ctx, RNG_CONFIG_REG, conf_data );
    rng_set_vref( ctx, 6144 );
}

void rng_write_function ( rng_t *ctx, uint8_t reg, uint16_t reg_data )
{
    uint8_t tx_buf[ 256 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = reg_data >> 8;
    tx_buf[ 2 ] = reg_data;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );   
}

uint16_t rng_read_function ( rng_t *ctx, uint8_t reg )
{
    uint8_t data_buf[ 2 ];
    uint16_t r_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );

    r_data = data_buf[ 0 ];
    r_data <<= 8;
    r_data |= data_buf[ 1 ];

    return r_data;
}

void rng_reset_device ( rng_t *ctx )
{
    uint8_t reset;
    
    reset = 0x06;

    i2c_master_write( &ctx->i2c, &reset, 1 );   
}

void rng_set_config ( rng_t *ctx, uint16_t conf_data )
{
    rng_write_function( ctx, RNG_CONFIG_REG, conf_data );
}

void rng_set_vref ( rng_t *ctx, uint16_t vref_mv )
{
    ctx->dev_vref = vref_mv;
}

float rng_get_voltage ( rng_t *ctx )
{
    float voltage;
    int16_t sensor_value;

    sensor_value = rng_read_function( ctx, RNG_CONVERSION_REG );

    voltage = ( ( float ) sensor_value / 0x8000 ) * ctx->dev_vref;

    return voltage;
}

void rng_set_threshold ( rng_t *ctx, uint8_t thresh_reg, uint16_t thresh_data )
{
    rng_write_function( ctx, thresh_reg, thresh_data );
}

// ------------------------------------------------------------------------- END

