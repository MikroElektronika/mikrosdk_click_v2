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

#include "compass3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void dev_com_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void compass3_cfg_setup ( compass3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COMPASS3_SLAVE_ADR;
}

COMPASS3_RETVAL compass3_init ( compass3_t *ctx, compass3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COMPASS3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COMPASS3_OK;
}

void compass3_default_cfg ( compass3_t *ctx )
{
    uint8_t tx_buf;
    tx_buf = COMPASS3_SET | COMPASS3_TM_M | COMPASS3_TM_T;
    compass3_generic_write( ctx, COMPASS3_INTERNAL_CTRL_0, &tx_buf, 1 );
    tx_buf = COMPASS3_INT_MEAS_DONE_EN | COMPASS3_CM_FREQ_2_2HZ;
    compass3_generic_write( ctx, COMPASS3_INTERNAL_CTRL_2, &tx_buf, 1 );
}

void compass3_generic_write ( compass3_t *ctx, uint8_t reg, uint8_t *data_buf, 
                              uint8_t len )
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

void compass3_generic_read ( compass3_t *ctx, uint8_t reg, uint8_t *data_buf, 
                             uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void compass3_full_measurement ( compass3_t *ctx, float *x_val, float *y_val, 
                                 float *z_val )
{
    uint8_t mag_val[ 6 ];
    uint16_t tmp_val;
    
    compass3_generic_read ( ctx, COMPASS3_XOUT_LSB, mag_val, 6 );
    dev_com_delay( );

    tmp_val = mag_val[ 1 ];
    tmp_val <<= 8;
    tmp_val |= mag_val[ 0 ];
    *x_val = ( tmp_val * COMPASS3_MAG_LSB_VALUE ) - COMPASS3_MAG_RANGE_VALUE;

    tmp_val = mag_val[ 3 ];
    tmp_val <<= 8;
    tmp_val |= mag_val[ 2 ];
    *y_val  = ( tmp_val * COMPASS3_MAG_LSB_VALUE ) - COMPASS3_MAG_RANGE_VALUE;

    tmp_val = mag_val[ 5 ];
    tmp_val <<= 8;
    tmp_val |= mag_val[ 4 ];
    *z_val  = ( tmp_val * COMPASS3_MAG_LSB_VALUE ) - COMPASS3_MAG_RANGE_VALUE;
}

float compass3_read_temp ( compass3_t *ctx )
{
    uint8_t rx_buf;
    float temp_val;

    compass3_generic_read ( ctx, COMPASS3_TEMP, &rx_buf, 1 );
    temp_val = (float)rx_buf;
    temp_val *= COMPASS3_TEMP_LSB_VALUE;
    temp_val -= COMPASS3_TEMP_RANGE_VALUE;

    return temp_val;
}

uint8_t compass3_check_int ( compass3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_com_delay ( void )
{
    Delay_10ms( );    
}

// ------------------------------------------------------------------------- END

