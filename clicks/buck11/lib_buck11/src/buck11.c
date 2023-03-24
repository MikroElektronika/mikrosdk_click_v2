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

#include "buck11.h"

// ------------------------------------------------------------------ VARIABLES

static float vdd_val;
#define ADC_RESOLUTION  4096

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck11_cfg_setup ( buck11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BUCK11_MCP3221A5T_DEV_ADDR;
}

BUCK11_RETVAL buck11_init ( buck11_t *ctx, buck11_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BUCK11_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return BUCK11_OK;
}

void buck11_generic_write ( buck11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void buck11_generic_read ( buck11_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );
}

void buck11_set_vdd_value ( float vdd_volts )
{
    vdd_val = vdd_volts;
}

uint16_t buck11_read_adc ( buck11_t *ctx )
{
    uint8_t temp_data[ 2 ];
    uint16_t ret_val;
    
    buck11_generic_read( ctx, temp_data, 2 );
    
    ret_val = temp_data[ 0 ] & 0x0F;
    ret_val <<= 8;
    ret_val |= temp_data[ 1 ];
    
    return ret_val;
}

float buck11_get_vout ( buck11_t *ctx, uint8_t vout_resolution )
{
    uint16_t adc_val;
    float res;
    
    adc_val = buck11_read_adc( ctx );
    
    res = adc_val;
    res /= ADC_RESOLUTION;
    res *= vdd_val;
    
    if ( vout_resolution )
    {
        res *= 1000;
    }
    
    return res;
}

float buck11_get_averaged_vout ( buck11_t *ctx, uint8_t vout_resolution, uint8_t n_samples )
{
    uint16_t adc_val;
    uint32_t adc_sum;
    uint8_t cnt;
    float res;
    
    adc_sum = 0;
    for ( cnt = 0; cnt < n_samples; cnt++ )
    {
        adc_val = buck11_read_adc( ctx );
        adc_sum += adc_val;
        Delay_10us( );
    }
    
    res = adc_sum;
    res /= n_samples;
    res /= ADC_RESOLUTION;
    res *= vdd_val;
    
    if ( vout_resolution )
    {
        res *= 1000;
    }
    
    return res;
}

// ------------------------------------------------------------------------- END

