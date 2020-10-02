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

#include "pressure8.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OUTPUT_MAX  0xE66666
#define OUTPUT_MIN  0x19999A

#define DATA_IN_mBar  68.9475729
#define DATA_IN_hPa   68.9475729
#define DATA_IN_kPa   6.89475729
#define DATA_IN_Torr  51.7150754
#define DATA_IN_mmHg  51.7150754

// ------------------------------------------------------------------ VARIABLES

uint8_t P_MAX  = 0;
uint8_t P_MIN  = 25;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure8_cfg_setup ( pressure8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->eoc = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x18;
}

PRESSURE8_RETVAL pressure8_init ( pressure8_t *ctx, pressure8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PRESSURE8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );

    // Input pins

    digital_in_init( &ctx->eoc, cfg->eoc );

    return PRESSURE8_OK;
}

void pressure8_generic_read ( pressure8_t *ctx, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 3 ];

    tx_buf [ 0 ] = 0xAA;
    tx_buf [ 1 ] = 0x00;
    tx_buf [ 2 ] = 0x00;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 3, data_buf, len );
}

float pressure8_get_pressure ( pressure8_t *ctx, uint8_t press_foramt )
{
    uint32_t press_data;
    uint32_t out_calculate;
    float pressure;
    uint8_t read_data[ 4 ];

    pressure8_generic_read( ctx, read_data, 4 );

    press_data = read_data[ 1 ];
    press_data <<= 16;
    press_data |= ( read_data[ 2 ] << 8 );
    press_data |= read_data[ 3 ];
    ctx->device_status = read_data[ 0 ]; 
    
    press_data = ( press_data - OUTPUT_MIN ) * ( P_MAX - P_MIN );
    out_calculate = OUTPUT_MAX - OUTPUT_MIN;
    
    pressure = ( ( double )press_data / ( double )out_calculate ) + P_MIN;
    
    if ( ( press_foramt == PRESSURE8_DATA_IN_mBar ) || 
         ( press_foramt == PRESSURE8_DATA_IN_hPa ) )
    {
        pressure *= DATA_IN_mBar;
    }
    else if ( ( press_foramt == PRESSURE8_DATA_IN_Torr ) || 
              ( press_foramt == PRESSURE8_DATA_IN_mmHg ) )
    {
        pressure *= DATA_IN_Torr;
    }
    else
    {
        pressure *= DATA_IN_kPa;
    }
    
    return pressure;
}

void pressure8_device_reset ( pressure8_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

uint8_t pressure8_get_interrupt_state ( pressure8_t *ctx )
{
    return digital_in_read( &ctx->eoc );
}

uint8_t pressure8_get_device_status ( pressure8_t *ctx )
{
    return ctx->device_status;
}

void pressure8_set_psi_range ( float psi_min, float psi_max )
{
   P_MAX = psi_max;
   P_MIN = psi_min;
}

// ------------------------------------------------------------------------- END

