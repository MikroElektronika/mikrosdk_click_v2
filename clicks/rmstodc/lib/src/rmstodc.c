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

#include "rmstodc.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rmstodc_cfg_setup ( rmstodc_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RMS2DC_DEVICE_ADDR;
}

RMSTODC_RETVAL rmstodc_init ( rmstodc_t *ctx, rmstodc_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RMSTODC_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    return RMSTODC_OK;
}

void rmstodc_generic_write ( rmstodc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rmstodc_generic_read ( rmstodc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t rms2dc_read_adc ( rmstodc_t *ctx )
{
    uint8_t data_out[ 2 ];
    uint16_t ret_val;
    
    rmstodc_generic_read( ctx, 0x00, data_out, 2 );
    
    ret_val = data_out[ 0 ] & 0x0F;
    ret_val <<= 8;
    ret_val |= data_out[ 1 ];
    
    return ret_val;
}

uint16_t rms2dc_vout_adc ( rmstodc_t *ctx, uint16_t vcc_sel )
{
    uint16_t adc_val;
    double res;
    
    adc_val = rms2dc_read_adc( ctx );
    
    res = ( double )adc_val / ADC_RESOLUTION;
    res *= vcc_sel;
    
    return ( uint16_t )res;
}

uint16_t rms2dc_avrg_vout_adc ( rmstodc_t *ctx, uint16_t vcc_select, uint8_t n_samples )
{
    uint16_t v_out;
    uint16_t v_max;
    uint16_t v_min;
    uint8_t cont = 0;
    uint8_t cnt;

    for ( cnt = 0; cnt < n_samples; cnt++ )
    {
        v_out = rms2dc_vout_adc( ctx, vcc_select );
        
        if ( cont == 0 )
        {
            v_max = v_out;
            v_min = v_out;
            cont = 1;
        }
        else
        {
            if ( v_max < v_out )
            {
                v_max = v_out;
            }
            if ( v_min > v_out )
            {
                v_min = v_out;
            }
        }
        Delay_1us( );
    }
    
    v_out = ( v_max + v_min ) / 2;
    
    return v_out;
}

void rms2dc_enable ( rmstodc_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

// ------------------------------------------------------------------------- END

