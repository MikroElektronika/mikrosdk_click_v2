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

#include "pac1934.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pac1934_cfg_setup ( pac1934_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->ale = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PAC1934_I2C_ADDR;
}

PAC1934_RETVAL pac1934_init ( pac1934_t *ctx, pac1934_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PAC1934_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->ale, cfg->ale );

    return PAC1934_OK;
}

void pac1934_generic_write ( pac1934_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void pac1934_generic_read ( pac1934_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void pac1934_write_byte ( pac1934_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    pac1934_generic_write( ctx, wr_addr, &wr_data, 1 );
}

uint8_t pac1934_read_byte ( pac1934_t *ctx, uint8_t rd_addr )
{
    uint8_t r_buffer[ 1 ];

    pac1934_generic_read( ctx, rd_addr, r_buffer, 1 );

    return r_buffer[ 0 ];
}

uint16_t pac1934_read_two_byte ( pac1934_t *ctx, uint8_t rd_addr )
{
    uint16_t result;
    uint8_t r_buffer[ 2 ];

    pac1934_generic_read( ctx, rd_addr, r_buffer, 2 );

    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];

    return result;
}

uint32_t pac1934_read_four_byte ( pac1934_t *ctx, uint8_t rd_addr )
{
    uint32_t result;
    uint8_t r_buffer[ 4 ];

    pac1934_generic_read( ctx, rd_addr, r_buffer, 4 );

    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 2 ];
    result <<= 8;
    result |= r_buffer[ 3 ];

    return result;
}

void pac1934_read_reg( pac1934_t *ctx, uint8_t reg_addr, uint8_t *output_data, uint8_t cnt )
{
    pac1934_generic_read( ctx, reg_addr, output_data, cnt );
}

void pac1934_send_command ( pac1934_t *ctx, uint8_t wr_cmd )
{
    uint8_t w_buffer[ 1 ];
    w_buffer[ 0 ] = wr_cmd;
    
    if ( wr_cmd == PAC1934_REFRESH_G_CMD )
    {
        i2c_master_set_slave_address( &ctx->i2c, 0 );
        i2c_master_write( &ctx->i2c, w_buffer, 1 );  
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else
    {
        i2c_master_write( &ctx->i2c, w_buffer, 1 );  
    }
}

float pac1934_measure_voltage ( pac1934_t *ctx, uint8_t channel )
{
    uint8_t w_buffer[ 1 ];
    float result;

    w_buffer[ 0 ] = channel + 0x06;

    result = ( float ) pac1934_read_two_byte( ctx, w_buffer[ 0 ] );

    result *= 32.0;
    result /= 0xFFFF;

    return result;
}

float pac1934_measure_current ( pac1934_t *ctx, uint8_t channel )
{
    uint8_t w_buffer[ 1 ];
    float result;

    w_buffer[ 0 ] = channel + 0x0A;

    result = ( float ) pac1934_read_two_byte( ctx, w_buffer[ 0 ] );

    result *= 25000.0;
    result /= 0xFFFF;

    return result;
}

float pac1934_measure_power ( pac1934_t *ctx, uint8_t channel )
{
    uint8_t wr_buff[ 1 ];
    uint8_t rd_buff[ 4 ];
    uint32_t return_int = 0;
    float result;

    wr_buff[ 0 ] = channel + 0x16;
    
    pac1934_generic_read( ctx, wr_buff[ 0 ], rd_buff, 4 );

    return_int = rd_buff[ 0 ];
    return_int <<= 8;
    return_int |= rd_buff[ 1 ];
    return_int <<= 8;
    return_int |= rd_buff[ 2 ];
    return_int <<= 4;
    rd_buff[ 3 ] >>= 4;
    return_int |= rd_buff[ 3 ];

    result = ( float ) return_int;
    result *= 0.0000029802;

    return result;
}

float pac1934_calc_power ( pac1934_t *ctx, float voltage, float amperage )
{
    float result;

    result = voltage * amperage;

    return result;
}

float pac1934_measure_energy ( pac1934_t *ctx, uint8_t chann, uint16_t samp_rate )
{
    uint8_t wr_data[ 1 ];
    uint8_t rd_buff[ 6 ];
    uint32_t acc_val = 0;
    float result;
    float result_msb;

    wr_data[ 0 ] = 0x02;

    pac1934_generic_read( ctx, wr_data[ 0 ], rd_buff, 3 );

    wr_data[ 0 ] = chann + 0x02;

    pac1934_generic_read( ctx, wr_data[ 0 ], rd_buff, 6 );

    acc_val = rd_buff[ 0 ];
    acc_val <<= 8;
    acc_val |= rd_buff[ 1 ];
    acc_val <<= 16;
    result_msb = ( float ) acc_val;
    result_msb *= 0.1953601953;
    
    acc_val = rd_buff[ 2 ];
    acc_val <<= 8;
    acc_val |= rd_buff[ 3 ];
    acc_val <<= 8;
    acc_val |= rd_buff[ 4 ];
    acc_val <<= 8;
    acc_val |= rd_buff[ 5 ];
    
    result = ( float ) acc_val;
    result *= 0.0000029802;
    result = result + result_msb;
    result = result / samp_rate;

    return result;
}

void pac1934_dev_enable ( pac1934_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void pac1934_dev_disable ( pac1934_t *ctx )
{
    digital_out_low( &ctx->rst );
}

void pac1934_dev_reset ( pac1934_t *ctx )
{
    digital_out_low( &ctx->rst );

    Delay_100ms( );

    digital_out_high( &ctx->rst );

    Delay_100ms( );
}

uint8_t pac1934_check_interrupt ( pac1934_t *ctx )
{
    return digital_in_read( &ctx->ale );
}

// ------------------------------------------------------------------------- END

