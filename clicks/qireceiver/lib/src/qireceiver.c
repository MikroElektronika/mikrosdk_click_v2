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

#include "qireceiver.h"

// ------------------------------------------------------------------ VARIABLES

static qireceiver_t qireceiver;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void qireceiver_cfg_setup ( qireceiver_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->teop = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->stat = HAL_PIN_NC;
    cfg->end  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = QIRECEIVER_I2C_ADDR;
}

QIRECEIVER_RETVAL qireceiver_init ( qireceiver_t *ctx, qireceiver_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return QIRECEIVER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->teop, cfg->teop );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->end, cfg->end );
    digital_out_low( &ctx->en );

    // Input pins

    digital_in_init( &ctx->stat, cfg->stat );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return QIRECEIVER_OK;
}

void qireceiver_generic_write ( qireceiver_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void qireceiver_generic_read ( qireceiver_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void qireceiver_dev_enable ( qireceiver_t *ctx )
{
    digital_out_low( &ctx->en );
}

float qireceiver_read_voltage ( qireceiver_t *ctx )
{
    float result = 0.0;
    uint8_t raw_data0[ 1 ];
    uint8_t raw_data1[ 1 ];
    uint16_t temp_data;
    
    qireceiver_generic_read( ctx, QIRECEIVER_VRECT_REG0, raw_data0, 1 );
    temp_data = raw_data0[ 0 ];
    temp_data <<= 4;

    qireceiver_generic_read( ctx, QIRECEIVER_VRECT_REG1, raw_data1, 1 );
    raw_data1[ 0 ] >>= 4;
    raw_data1[ 0 ] &= 0x0F;
    temp_data |= raw_data1[ 0 ];
    temp_data *= 5;
    result = temp_data * 1.8;
    result /= 4096.0;

    return result;
}

float qireceiver_read_current ( qireceiver_t *ctx )
{
    float result = 0.0;
    uint8_t raw_data0[ 1 ];
    uint8_t raw_data1[ 1 ];
    uint16_t temp_data;

    qireceiver_generic_read( ctx, QIRECEIVER_IOUT_REG2, raw_data0, 1 );
    temp_data = raw_data0[ 0 ];
    temp_data <<= 4;

    qireceiver_generic_read( ctx, QIRECEIVER_IOUT_REG3, raw_data1, 1 );
    raw_data1[ 0 ] >>= 4;
    raw_data1[ 0 ] &= 0x0F;
    temp_data |= raw_data1[ 0 ];
    result = temp_data * 1.8;
    result /= 4096.0;

    return result;
}

float qireceiver_read_freq ( qireceiver_t *ctx )
{
    float result = 0.0;
    uint8_t raw_data0[ 1 ];
    uint8_t raw_data1[ 1 ];
    uint16_t temp_data;

    qireceiver_generic_read( ctx, QIRECEIVER_IOUT_REG2, raw_data0, 1 );
    temp_data = raw_data0[ 0 ];
    temp_data <<= 2;

    qireceiver_generic_read( ctx, QIRECEIVER_IOUT_REG3, raw_data1, 1 );
    raw_data1[ 0 ] >>= 6;
    raw_data1[ 0 ] &= 0x3F;
    temp_data |= raw_data1[ 0 ];

    if( temp_data == 0 )
    {
        return temp_data;
    }
    else
    {
    result = 65536.0 / temp_data;
    }
    
    return result;
}

// ------------------------------------------------------------------------- END

