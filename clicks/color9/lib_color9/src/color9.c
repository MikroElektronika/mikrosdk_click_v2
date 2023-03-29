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

#include "color9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color9_cfg_setup ( color9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR9_SLAVE_ADDR;
}

COLOR9_RETVAL color9_init ( color9_t *ctx, color9_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR9_OK;

}

void color9_write ( color9_t *ctx, uint8_t reg_addr, uint8_t r_data )
{
    uint8_t tx_buf[ 256 ];

    tx_buf[ 0 ] = reg_addr;
    tx_buf[ 1 ] = r_data;
    
    i2c_master_write( &ctx->i2c, tx_buf, 2 );

}

uint8_t color9_read ( color9_t* ctx, uint8_t reg_addr )
{
    uint8_t rx_buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void color9_sw_reset ( color9_t* ctx )
{
    color9_write( ctx, COLOR9_MAIN_CTRL, COLOR9_MAIN_CTRL_SW_RESET );
}

uint32_t color9_get_Ir ( color9_t* ctx )
{
    return color9_read_32( ctx, COLOR9_LS_DATA_IR_0 );
}

uint32_t color9_get_green ( color9_t* ctx )
{
    return color9_read_32( ctx, COLOR9_LS_DATA_GREEN_0 );
}

uint32_t color9_get_blue ( color9_t* ctx )
{
    return color9_read_32( ctx, COLOR9_LS_DATA_BLUE_0 );
}

uint32_t color9_get_red ( color9_t* ctx )
{
    return color9_read_32( ctx, COLOR9_LS_DATA_RED_0 );
}

uint8_t color9_get_status_reg ( color9_t* ctx )
{
    return color9_read( ctx, COLOR9_MAIN_STATUS );
}

void color9_meas_rate ( color9_t* ctx, uint8_t resolution, uint8_t meas_rate )
{
    uint8_t tmp = ((uint8_t)(0x07 & resolution) << 4) | (uint8_t)(0x07 & meas_rate);
    color9_write( ctx, COLOR9_LS_MEAS_RATE, tmp );
}

void color9_reg_ctrl ( color9_t* ctx, uint8_t cfg )
{
    color9_write( ctx, COLOR9_MAIN_CTRL, cfg & ((1 << 4 | 1 << 2 | 1 << 1)) );
}

void color9_set_gain ( color9_t* ctx, uint8_t g_setting )
{
    color9_write( ctx, COLOR9_LS_GAIN, (g_setting & 0x07) );
}

void color9_int_config ( color9_t* ctx, uint8_t int_select, uint8_t int_mode, uint8_t cfg_setting )
{
    color9_write( ctx, COLOR9_INT_CFG, (int_select & 0x03) << 4 | int_mode << 3 | cfg_setting << 2);
}

void color9_sample_compare( color9_t *ctx, uint8_t num_of_compares )
{
    color9_write( ctx, COLOR9_LS_THRES_VAR, num_of_compares & 0x07);
}

uint32_t color9_read_32 ( color9_t* ctx, uint8_t reg_addr )
{
    uint8_t tmp[ 3 ];
    uint32_t raw_data;

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, tmp, 3 );

    raw_data = tmp[ 2 ];
    raw_data <<= 8;
    raw_data = tmp[ 1 ];
    raw_data <<= 8;
    raw_data = tmp[ 0 ];

    return raw_data;
}

void color9_write_32 ( color9_t* ctx, uint8_t reg_addr, uint32_t treas_val )
{
    uint8_t tx_buf[ 4 ];
    uint32_t raw_data;

    tx_buf[ 0 ] = reg_addr;
    tx_buf[ 0 ] = (uint8_t)( treas_val >> 16 );
    tx_buf[ 1 ] = (uint8_t)( treas_val >> 8 );
    tx_buf[ 2 ] = (uint8_t)treas_val;

    i2c_master_write( &ctx->i2c, tx_buf, 4 );   

}

void color9_similarity_count ( color9_t* ctx, uint8_t sim_set )
{
    color9_write( ctx, COLOR9_INT_PERSISTENCE, (sim_set & 0x0F) << 4);
}

void color9_upper_tresset ( color9_t* ctx, uint32_t set_val )
{
    color9_write_32( ctx, COLOR9_LS_THRES_UP_0, set_val & 0x0FFFFF );
}

void color9_lower_tresset ( color9_t* ctx, uint32_t set_val )
{
    color9_write_32( ctx, COLOR9_LS_THRES_LOW_0, set_val & 0x0FFFFF);
}

// ------------------------------------------------------------------------- END

