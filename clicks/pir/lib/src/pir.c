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

#include "pir.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pir_cfg_setup ( pir_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;
}

PIR_RETVAL pir_init ( pir_t *ctx, pir_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PIR_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return PIR_OK;

}

void pir_generic_write ( pir_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void pir_generic_read ( pir_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t pir_get_adc ( pir_t *ctx )
{
    return pir_reg_read( ctx );
}

uint16_t pir_reg_read ( pir_t *ctx )
{
    uint16_t value;
    uint8_t read_buf[ 2 ];

    i2c_master_read( &ctx->i2c, read_buf, 2 );   

    value = read_buf[ 0 ];
    value <<= 8;
    value |= read_buf[ 1 ];
    
    return value;
}

float pir_get_mili_volt ( pir_t *ctx, uint16_t ref_voltage )
{
    float mili_volt;
    uint16_t adc_value;
    uint8_t rd_buff[ 2 ];
    
    adc_value = pir_get_adc( ctx );
    mili_volt = ( float )adc_value / 4095;
    mili_volt *= ref_voltage;
    
    return mili_volt;
}

float pir_scale_results ( pir_t *ctx, uint16_t in_val, uint16_t out_min, uint16_t out_max )
{
    float out_val;
    
    out_val = ( float )( out_max - out_min );
    out_val *= in_val;
    out_val /= 4095;
    out_val += out_min;
    
    return out_val;
}

// ------------------------------------------------------------------------- END

