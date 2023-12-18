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

#include "ambient8.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t wr_buf[ 2 ];
static uint8_t rd_buf[ 4 ];
static uint8_t reg_address;
static uint8_t gain_level;
static uint16_t integration_time;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient8_cfg_setup ( ambient8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMBIENT8_DEVICE_ADDRESS;
}

AMBIENT8_RETVAL ambient8_init ( ambient8_t *ctx, ambient8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    wr_buf[ 0 ] = AMBIENT8_ALS_CONTROL;
    wr_buf[ 1 ] = AMBIENT8_SW_RESET;
    ambient8_set_register( ctx, wr_buf, 2 );

    wr_buf[ 0 ] = AMBIENT8_ALS_MEASUREMENT_RATE;
    wr_buf[ 1 ] = AMBIENT8_ALS_INTEGRATION_TIME_400ms 
                | AMBIENT8_ALS_MEASUREMENT_RATE_100;
    ambient8_set_register( ctx, wr_buf, 2 );

    wr_buf[ 0 ] = AMBIENT8_ALS_CONTROL;
    wr_buf[ 1 ] = AMBIENT8_ALS_MODE_ACTIVE | AMBIENT8_ALS_GAIN_8X;
    ambient8_set_register( ctx, wr_buf, 2 );

    ambient8_set_constants( ctx );

    return AMBIENT8_OK;
}

void ambient8_set_register ( ambient8_t *ctx, uint8_t *write_buf, uint8_t n_bytes )
{   
    i2c_master_write( &ctx->i2c, write_buf, n_bytes ); 
}

void ambient8_get_register ( ambient8_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t n_bytes )
{
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buf, n_bytes );
}

void ambient8_set_constants ( ambient8_t* ctx )
{
    gain_level = 0;
    reg_address = AMBIENT8_ALS_CONTROL;
    ambient8_get_register( ctx, reg_address, rd_buf, 1 );
    rd_buf[ 0 ] >>= 2;
    rd_buf[ 0 ] &= 0x07;

    switch ( rd_buf[ 0 ] )
    {
        case 0:
        {
            gain_level = 1;
        break;
        }
        case 1:
        {
            gain_level = 2;
        break;
        }
        case 2:
        {
            gain_level = 4;
        break;
        }
        case 3:
        {
            gain_level = 8;
        break;
        }
        case 6:
        {
            gain_level = 48;
        break;
        }
        case 7:
        {
            gain_level = 96;
        break;
        }
        default:
        {
        break;
        }
    }

    integration_time = 0;
    reg_address = AMBIENT8_ALS_MEASUREMENT_RATE;
    ambient8_get_register( ctx, reg_address, rd_buf, 1 );
    rd_buf[ 0 ] >>= 3;
    rd_buf[ 0 ] &= 0x07;

    switch ( rd_buf[ 0 ] )
    {
        case 0:
        {
            integration_time = 100;
        break;
        }
        case 1:
        {
            integration_time = 50;
        break;
        }
        case 2:
        {
            integration_time = 200;
        break;
        }
        case 3:
        {
            integration_time = 400;
        break;
        }
        case 4:
        {
            integration_time = 150;
        break;
        }
        case 5:
        {
            integration_time = 250;
        break;
        }
        case 6:
        {
            integration_time = 300;
        break;
        }
        case 7:
        {
            integration_time = 350;
        break;
        }
        default:
        {
        break;
        }
    }
}

AMBIENT8_RETVAL ambient8_get_als_data ( ambient8_t *ctx, uint16_t* als_data_ch1,
                                        uint16_t* als_data_ch0 )
{
    rd_buf[ 0 ] = 0;
    reg_address = AMBIENT8_ALS_STATUS;
    ambient8_get_register( ctx, reg_address, rd_buf, 1 );

    if ( ( ( rd_buf[ 0 ] & 0x04 ) != 0 ) & ( ( rd_buf[ 0 ] & 0x80 ) == 0 ) )
    {
        reg_address = AMBIENT8_ALS_STATUS;
        ambient8_get_register( ctx, reg_address, rd_buf, 1 );

        ambient8_get_register( ctx, AMBIENT8_ALS_DATA_CH1_0, rd_buf, 4 );

        *als_data_ch1 = rd_buf[ 1 ];
        *als_data_ch1 <<= 8;
        *als_data_ch1 |= rd_buf[ 0 ];

        *als_data_ch0 = rd_buf[ 3 ];
        *als_data_ch0 <<= 8;
        *als_data_ch0 |= rd_buf[ 2 ];

        return AMBIENT8_OK;
    }
    else
    {
        *als_data_ch1 = 0;
        *als_data_ch0 = 0;

        return AMBIENT8_INIT_ERROR;
    }
}

AMBIENT8_RETVAL ambient8_get_lux_level ( ambient8_t *ctx, float* lux_level, 
                                         float window_factor, float IR_factor )
{
    uint16_t als_data_ch1;
    uint16_t als_data_ch0;
    float aux_var;

    rd_buf[ 0 ] = 0;
    reg_address = AMBIENT8_ALS_STATUS;
    ambient8_get_register( ctx, reg_address, rd_buf, 1 );

    if ( ( ( rd_buf[ 0 ] & 0x04 ) != 0 ) & ( ( rd_buf[ 0 ] & 0x80 ) == 0 ) )
    {
        reg_address = AMBIENT8_ALS_STATUS;
        ambient8_get_register( ctx, reg_address, rd_buf, 1 );

        ambient8_get_register( ctx, AMBIENT8_ALS_DATA_CH1_0, rd_buf, 4 );

        als_data_ch1 = rd_buf[ 1 ];
        als_data_ch1 <<= 8;
        als_data_ch1 |= rd_buf[ 0 ];

        als_data_ch0 = rd_buf[ 3 ];
        als_data_ch0 <<= 8;
        als_data_ch0 |= rd_buf[ 2 ];

        *lux_level = window_factor;
        *lux_level *= 0.6;
        *lux_level /= gain_level;
        *lux_level /= integration_time;
        *lux_level *= 100.0;
        aux_var = als_data_ch0;
        aux_var -= ( float )( IR_factor * ( float )( als_data_ch1 ) );
        *lux_level *= aux_var;

        return AMBIENT8_OK;
    }
    else
    {
        *lux_level = 0.0;
        return AMBIENT8_INIT_ERROR;
    }
}
// ------------------------------------------------------------------------- END

