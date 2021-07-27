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

#include "co2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void co2_cfg_setup ( co2_cfg_t *cfg )
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

CO2_RETVAL co2_init ( co2_t *ctx, co2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CO2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
 
    // Input pins

    digital_in_init( &ctx->an, cfg->an );


    return CO2_OK;

}

uint8_t co2_generic_write ( co2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    if ( ( reg < 0x01 ) || ( reg > 0x01 && reg < 0x10 ) || ( reg > 0x12 ))
    {
        return 1;
    }

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    co2_enable( ctx, CO2_DEVICE_EN );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
    co2_enable( ctx, CO2_DEVICE_DIS );

    return 0;
}

uint8_t co2_generic_read ( co2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    if ( ( reg > 0x01 && reg < 0x10 ) || ( reg > 0x12 ) )
    {
        return 1;
    }

    co2_enable( ctx, CO2_DEVICE_EN );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
    co2_enable( ctx, CO2_DEVICE_DIS );
    
    return 0;
}

void co2_wait_i2c_ready ( co2_t *ctx )
{
    uint8_t i2c_busy;

    co2_generic_read( ctx, CO2_STATUS_REG, &i2c_busy, 1 );

    while ( !( i2c_busy & 0x01 ) )
    {
        co2_generic_read( ctx, CO2_STATUS_REG, &i2c_busy, 1 );
    }
}

void co2_enable( co2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void co2_read_adc( co2_t *ctx, uint16_t *data_out )
{
    uint8_t buff_data[ 2 ];
    uint16_t tmp;
    uint8_t read_addr;

    read_addr = 0;
    
    i2c_master_set_slave_address( &ctx->i2c, ADC_DEVICE_ADDR );
    i2c_master_read( &ctx->i2c, buff_data, 2 );
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    tmp = buff_data[ 0 ];
    tmp <<= 8;
    tmp |= buff_data[ 1 ];
    
    *data_out = tmp;
}

void co2_get_co2_ppm( co2_t *ctx, float *co2_data )
{
    uint16_t adc_data;
    float temp;
    
    co2_read_adc( ctx, &adc_data );
    
    temp = ( float )adc_data / 4095;
    temp *= 1000;

    *co2_data = temp;
}
// ------------------------------------------------------------------------- END

