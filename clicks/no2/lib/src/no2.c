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

#include "no2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void no2_cfg_setup ( no2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

NO2_RETVAL no2_init ( no2_t *ctx, no2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return NO2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return NO2_OK;
}

void no2_default_cfg ( no2_t *ctx )
{
    no2_write_byte( ctx, NO2_MODECN_REG, NO2_DEEP_SLEEP_MODE );
    no2_write_byte( ctx, NO2_LOCK_REG, NO2_WRITE_MODE );
    no2_write_byte( ctx, NO2_TIACN_REG, NO2_EXT_TIA_RES | 
                                        NO2_100_OHM_LOAD_RES );
    no2_write_byte( ctx, NO2_REFCN_REG, NO2_VREF_INT | 
                                        NO2_50_PERCENTS_INT_ZERO | 
                                        NO2_BIAS_POL_NEGATIVE | 
                                        NO2_0_PERCENTS_BIAS );
}

void no2_generic_write ( no2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void no2_generic_read ( no2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void no2_write_byte ( no2_t *ctx, uint8_t reg, uint8_t dev_data )
{   
    no2_enable( ctx, NO2_DEVICE_EN );
    no2_generic_write( ctx, reg, &dev_data, 1 );
    no2_enable( ctx, NO2_DEVICE_DIS );
}

uint8_t no2_read_byte ( no2_t *ctx, uint8_t reg )
{
    uint8_t read_reg;
    
    no2_enable( ctx, NO2_DEVICE_EN );
    no2_generic_read( ctx, reg, &read_reg, 1 );
    no2_enable( ctx, NO2_DEVICE_DIS );
    
    return read_reg;
}

void no2_enable ( no2_t *ctx, uint8_t state )
{
    Delay_10us( );
    digital_out_write( &ctx->rst, state );
}

uint16_t no2_read_adc ( no2_t *ctx )
{
    uint8_t read_data[ 2 ];
    uint16_t adc_data;
    
    i2c_master_set_slave_address( &ctx->i2c, ADC_DEVICE_ADDR );
    i2c_master_read( &ctx->i2c, read_data, 2 );   
    
    adc_data = read_data[ 0 ];
    adc_data <<= 8;
    adc_data |= read_data[ 1 ];
        
    return adc_data;
}

float no2_get_no_2_ppm ( no2_t *ctx )
{
    uint16_t adc_data;
    float temp;
    
    adc_data = no2_read_adc( ctx );
    
    temp = adc_data / 4095.0;
    temp *= 1000;

    return temp;
}

void no2_wait_ready ( no2_t *ctx )
{
    uint8_t i2c_busy;

    i2c_busy = no2_read_byte( ctx, NO2_STATUS_REG );
    
    while ( ! ( i2c_busy & 0x01 ) )
    {
        i2c_busy = no2_read_byte( ctx, NO2_STATUS_REG );
    }
}

// ------------------------------------------------------------------------- END

