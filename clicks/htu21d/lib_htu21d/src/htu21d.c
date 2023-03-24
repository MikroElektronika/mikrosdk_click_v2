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

#include "htu21d.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void htu21d_cfg_setup ( htu21d_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HTU21D_I2C_ADDRESS;
}

HTU21D_RETVAL htu21d_init ( htu21d_t *ctx, htu21d_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HTU21D_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    return HTU21D_OK;
}

void htu21d_generic_write ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void htu21d_generic_read ( htu21d_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void htu21d_send_cmd ( htu21d_t *ctx, uint8_t cmd_byte )
{
    i2c_master_write( &ctx->i2c, &cmd_byte, 1 );;    
}

float htu21d_get_temperature ( htu21d_t *ctx )
{
    uint8_t rx_buf[ 3 ];
    float result;
    uint32_t temp_val;

    htu21d_generic_read ( ctx, HTU21D_TRIG_TEMP_MEASURE_HOLD, rx_buf, 3 );
    
    temp_val = rx_buf[ 0 ];
    temp_val <<= 8;
    temp_val |= rx_buf[ 1 ];
    temp_val <<= 8;
    temp_val |= rx_buf[ 2 ];
    
    temp_val >>= 8;
    temp_val &= HTU21D_DATA_FILTER;

    result = ( float ) temp_val;
    result *= HTU21D_TEMP_CALC_COEF;
    result /= HTU21D_DATA_RESOLUTION;
    result += HTU21D_TEMP_STB_COEF;

    return result;
}
 
float htu21d_get_humidity ( htu21d_t *ctx )
{
    uint8_t rx_buf[ 3 ];
    uint32_t humidity;
    float result;

    htu21d_generic_read ( ctx, HTU21D_TRIG_HUMD_MEASURE_HOLD, rx_buf, 3 );
    
    humidity = rx_buf[ 0 ];
    humidity <<= 8;
    humidity |= rx_buf[ 1 ];
    humidity <<= 8;
    humidity |= rx_buf[ 2 ];

    humidity >>= 8;
    humidity &= HTU21D_DATA_FILTER;

    result = ( float ) humidity;
    result *= HTU21D_HUMI_CALC_COEF;
    result /= HTU21D_DATA_RESOLUTION ;
    result += HTU21D_HUMI_STB_COEF;

    return result;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

