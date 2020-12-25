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

#include "mic2.h"

void mic2_cfg_setup ( mic2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address  = MIC2_DEVICE_SLAVE_ADDRESS;
}

MIC2_RETVAL mic2_init ( mic2_t *ctx, mic2_cfg_t *cfg )
{
     analog_in_config_t adc_cfg;
     i2c_master_config_t i2c_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;
 
    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return MIC2_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MIC2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return MIC2_OK;
}

void mic2_set_potentiometer ( mic2_t *ctx, uint8_t ptt_value )
{
    uint8_t write_reg[ 2 ];

    write_reg[ 0 ] = 0x00;
    write_reg[ 1 ] = ptt_value;

    i2c_master_write( &ctx->i2c, write_reg, 2 ); 
    
}

mic2_data_t mic2_generic_read ( mic2_t *ctx )
{
    mic2_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

// ------------------------------------------------------------------------- END

