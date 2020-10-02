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

#include "templog4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SIGN_BIT      0x1000
#define TEMP_RESOL    0.0625

// ------------------------------------------------------------------ VARIABLES

static uint8_t temp_sel_prev = 0;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void templog4_cfg_setup ( templog4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x18;
}

TEMPLOG4_RETVAL templog4_init ( templog4_t *ctx, templog4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPLOG4_OK;
}

void templog4_generic_write ( templog4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void templog4_generic_read ( templog4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t templog4_write_reg ( templog4_t *ctx, uint8_t reg, uint16_t input_data )
{
    uint8_t w_buf[ 2 ];

    if ( ( reg < 0x01 ) || ( ( reg > 0x04 ) && ( reg != 0x22 ) ) )
    {
        return TEMPLOG4_ADDR_ERROR;
    }

    w_buf[ 0 ] = input_data >> 8;
    w_buf [ 1 ] = input_data;

    templog4_generic_write( ctx, reg, w_buf, 2 );

    return TEMPLOG4_OK;
}

uint8_t templog4_read_reg ( templog4_t *ctx, uint8_t reg, uint16_t *out_var )
{
    uint8_t r_buf[ 2 ];

    if ( ( reg > 0x07 ) && ( reg != 0x22 ) )
    {
        return TEMPLOG4_ADDR_ERROR;
    }

    templog4_generic_read( ctx, reg, r_buf, 2 );

    *out_var = r_buf[ 0 ];
    *out_var <<= 8;
    *out_var |= r_buf[ 1 ];

    return TEMPLOG4_OK;
}

void templog4_set_addr_ptr ( templog4_t *ctx, uint8_t addr )
{
    i2c_master_write( &ctx->i2c, &addr, 1 );   
}

void templog4_repeated_read ( templog4_t *ctx, uint16_t *out_var )
{
    uint8_t r_buf[ 2 ];

    i2c_master_read( &ctx->i2c, r_buf, 2 );   

    *out_var = r_buf[ 0 ];
    *out_var <<= 8;
    *out_var |= r_buf[ 1 ];
}

uint8_t templog4_get_temp ( templog4_t *ctx, uint8_t temp_sel, float *temp_out )
{
    uint16_t temp;
    int16_t temp_val;
    uint8_t limit_stat;

    if ( temp_sel_prev != temp_sel )
    {
        templog4_set_addr_ptr( ctx, temp_sel );
        temp_sel_prev = temp_sel;
    }

    templog4_repeated_read( ctx, &temp );

    limit_stat = ( temp & 0xE000 ) >> 8;

    if ( temp & SIGN_BIT )
    {
        temp_val = temp | 0xE000;
    }
    else
    {
        temp_val = temp & 0x1FFF;
    }
    
    *temp_out = temp_val * TEMP_RESOL; 

    return limit_stat;
}

void templog4_set_temp ( templog4_t *ctx, uint8_t temp_sel, float temp_in )
{
    int16_t temp_val;

    temp_val = ( temp_in / TEMP_RESOL );
    temp_val &= 0x1FFC;

    templog4_write_reg( ctx, temp_sel, temp_val );
}

void templog4_default_cfg ( templog4_t *ctx )
{
    templog4_write_reg( ctx, 0x01, TEMPLOG4_TLIMIT_HYST_0_DEG | TEMPLOG4_CONT_CONV_MODE | TEMPLOG4_EVENT_OUTPUT_EN 
                             | TEMPLOG4_EVENT_TCRIT_ONLY | TEMPLOG4_EVENT_POL_ACT_HIGH | TEMPLOG4_EVENT_COMPARATOR_MODE );
    
    templog4_set_temp( ctx, TEMPLOG4_TEMP_CRITICAL_REG, 28.5 );
    templog4_set_temp( ctx, TEMPLOG4_TEMP_UPPER_REG, 40.250 );
    templog4_set_temp( ctx, TEMPLOG4_TEMP_LOWER_REG, -5 ); 
}

// ------------------------------------------------------------------------- END

