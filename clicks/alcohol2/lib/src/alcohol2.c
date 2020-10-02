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

#include "alcohol2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void alcohol2_read ( alcohol2_t *ctx, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void alcohol2_cfg_setup ( alcohol2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

ALCOHOL2_RETVAL alcohol2_init ( alcohol2_t *ctx, alcohol2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ALCOHOL2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    
    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    
    alcohol2_enable( ctx, 1 );
    Delay_100ms();

    return ALCOHOL2_OK;
}

void alcohol2_generic_write ( alcohol2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void alcohol2_generic_read ( alcohol2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void alcohol2_write_byte ( alcohol2_t *ctx, uint8_t reg, uint8_t w_data )
{
    alcohol2_enable( ctx, ALCOHOL2_DEVICE_EN );
    alcohol2_generic_write( ctx, reg, &w_data, 1 );
    alcohol2_enable( ctx, ALCOHOL2_DEVICE_DIS );
}

uint8_t alcohol2_read_byte ( alcohol2_t *ctx, uint8_t reg )
{
    uint8_t read_reg;
      
    alcohol2_enable(  ctx, ALCOHOL2_DEVICE_EN );
    alcohol2_generic_read( ctx, reg, &read_reg, 1 ); 
    alcohol2_enable(  ctx, ALCOHOL2_DEVICE_DIS );
    
    return read_reg;
}

void alcohol2_enable ( alcohol2_t *ctx, uint8_t state )
{
    Delay_10us();             
    digital_out_write( &ctx->rst, state );
}

uint16_t alcohol2_read_alcohol ( alcohol2_t *ctx )
{
    uint8_t read_data[ 2 ];
    uint16_t adc_data;
    
    i2c_master_set_slave_address( &ctx->i2c, ADC_DEVICE_ADDR );
    alcohol2_read( ctx, read_data, 2 );

    adc_data = read_data[ 0 ];
    adc_data <<= 8;
    adc_data |= read_data[ 1 ];
        
    return adc_data;
}

void alcohol2_wait_ready( alcohol2_t *ctx )
{
    uint8_t i2c_busy;

    i2c_busy = alcohol2_read_byte( ctx, ALCOHOL2_STATUS_REG );
    while ( ! ( i2c_busy & 0x01 ) )
    {
        i2c_busy = alcohol2_read_byte( ctx, ALCOHOL2_STATUS_REG );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void alcohol2_read ( alcohol2_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );   
}

// ------------------------------------------------------------------------- END

