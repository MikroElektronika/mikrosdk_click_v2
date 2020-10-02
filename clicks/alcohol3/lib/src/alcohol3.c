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

#include "alcohol3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/* Convert ppm to mg/L
 *
 * Table:  mg/l | air ppm
 *         1.82 | 1000
 *         0.91 | 500
 *         0.18 | 100
 *         0.09 | 50
 */
static float ppm_2_mgl ( uint16_t ppm );

/* Etanol in CO data
 *
 * Table:  CO [ppm] | Equivalent C2H5OH
            0       |    0
           10       |    1
           50       |    6
          100       |    18
          500       |    274
 */
static float etanol_in_co ( uint16_t co );

static long map ( long x, long in_min, long in_max, long out_min, long out_max );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void alcohol3_cfg_setup ( alcohol3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ALCOHOL3_DEVICE_SLAVE_ADDRESS;
}

ALCOHOL3_RETVAL alcohol3_init ( alcohol3_t *ctx, alcohol3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ALCOHOL3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return ALCOHOL3_OK;
}

void alcohol3_generic_write ( alcohol3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void alcohol3_generic_read ( alcohol3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t alcohol3_get_adc_data ( alcohol3_t *ctx )
{
    uint8_t write_data;
    uint8_t read_data[ 2 ];
    uint16_t adc_value;
    
    write_data = 0x00;

    alcohol3_generic_read( ctx, write_data, read_data, 2 );
    
    adc_value = read_data[ 0 ];
    adc_value <<= 8;
    adc_value |= read_data[ 1 ];
    
    adc_value = adc_value & 0x0FFF;
    
    return adc_value;
}

uint16_t alcohol3_get_co_in_ppm ( alcohol3_t *ctx )
{
    uint16_t co_ppm;
    uint16_t adc_data;
    
    adc_data = alcohol3_get_adc_data( ctx );
    co_ppm   = map( adc_data, ALCOHOL3_PARAM_SUPPLY_IN_MIN, ALCOHOL3_PARAM_SUPPLY_IN_MAX, ALCOHOL3_PARAM_CO_OUT_MIN, ALCOHOL3_PARAM_CO_OUT_MAX );
    
    return co_ppm;
}

float alcohol3_get_co_in_mgl ( alcohol3_t *ctx )
{
    uint16_t co_ppm;
    float co_mgl;
    
    co_ppm = alcohol3_get_co_in_ppm( ctx );
    co_mgl = ppm_2_mgl( co_ppm );
    
    return co_mgl;
}

uint16_t alcohol3_ethanol_in_ppm ( alcohol3_t *ctx )
{
    uint16_t ethanol_ppm;
    uint16_t co_ppm;

    co_ppm      = alcohol3_get_co_in_ppm( ctx );
    ethanol_ppm = etanol_in_co( co_ppm );
    
    return ethanol_ppm;
}

float alcohol3_get_percentage_bac ( alcohol3_t *ctx )
{
    float alcohol_mgl;
    uint16_t ethanol_ppm;
    uint16_t read_data;

    read_data   = alcohol3_get_adc_data( ctx );
    ethanol_ppm = etanol_in_co( read_data );
    alcohol_mgl = ppm_2_mgl( ethanol_ppm );

    return alcohol_mgl;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float ppm_2_mgl ( uint16_t ppm )
{
    float mgl;
    
    mgl  = ppm;
    mgl *= ALCOHOL3_CONV_MGL_PARAM_A;
    mgl /= ALCOHOL3_CONV_AIR_PPM_PARAM_A;

    return mgl;
}

static float etanol_in_co ( uint16_t co )
{
    float etanol;

    if ( co == ALCOHOL3_CO_PPM_0 )
    {
        etanol = ALCOHOL3_EQU_TO_PPM_0;
    }
    else if ( co <= ALCOHOL3_CO_PPM_10 )
    {
        etanol = co / ALCOHOL3_CO_PPM_10;
    }
    else if ( co > ALCOHOL3_CO_PPM_10 && co <= ALCOHOL3_CO_PPM_50 )
    {
        etanol = ( float )( ALCOHOL3_EQU_TO_PPM_50 / ALCOHOL3_CO_PPM_50 ) * co;
    }
    else if ( co > ALCOHOL3_CO_PPM_50 && co <= ALCOHOL3_CO_PPM_100 )
    {
        etanol = ( ALCOHOL3_CONV_MGL_PARAM_C * co );
    }
    else if ( co > ALCOHOL3_CO_PPM_100 )
    {
        etanol = ( float )( ALCOHOL3_EQU_TO_PPM_500 / ALCOHOL3_CO_PPM_500 ) * co;
    }
    return etanol;
}

static long map ( long x, long in_min, long in_max, long out_min, long out_max )
{
    return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}

// ------------------------------------------------------------------------- END

