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

#include "touchclamp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchclamp_cfg_setup ( touchclamp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TOUCHCLAMP_I2C_ADDRESS;
}

TOUCHCLAMP_RETVAL touchclamp_init ( touchclamp_t *ctx, touchclamp_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TOUCHCLAMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TOUCHCLAMP_OK;
}

void touchclamp_default_cfg ( touchclamp_t *ctx )
{
    // Click default configuration
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = TOUCHCLAMP_ECR_INIT_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_ECR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_MHDR_MAX_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_MHDR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDR_MIN_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_FDLR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_MHDF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_MHDF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_FDLF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_FDLT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_MHDPROXR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_MHDPROXR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDPROXR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDPROXR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLPROXR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLPROXR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_FDLPROXR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLPROXR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_MHDPROXF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_MHDPROXF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDPROXF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDPROXF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLPROXF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLPROXF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NCLPROXF_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLPROXF, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDPROXT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDPROXT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDPROXT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NCLPROXT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_NHDPROXT_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_FDLPROXT, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_DTR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_DTR, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_AFE1_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_AFE1, tx_buf, 1 );
    tx_buf [ 0 ] = TOUCHCLAMP_AFE2_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_AFE2, tx_buf, 1 );

    touchclamp_set_touch_threshold( ctx, 40 );
    touchclamp_set_release_threshold( ctx, 20 );
    
    tx_buf [ 0 ] = TOUCHCLAMP_ECR_DEF_VAL;
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_ECR, tx_buf, 1 );
}

void touchclamp_generic_write ( touchclamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void touchclamp_generic_read ( touchclamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void touchclamp_soft_reset ( touchclamp_t *ctx )
{
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = TOUCHCLAMP_BIT_MASK_SW_RESET;

    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_SRST, tx_buf, 1 );
}

void touchclamp_set_touch_threshold ( touchclamp_t *ctx, uint8_t th_data )
{
    uint8_t counter;
    uint8_t temp_data[ 1 ];
    uint8_t reg;
    uint8_t electrode;
    
    electrode = 0;

    temp_data[ 0 ] = th_data;

    for( counter = 0; counter < 13; counter++ )
    {
        reg = TOUCHCLAMP_REG_E0TTH + electrode;
        
        touchclamp_generic_write ( ctx, reg, temp_data, 1 );
        
        electrode += 2;
    }
}

uint8_t touchclamp_get_touch_threshold ( touchclamp_t *ctx, uint8_t electrode )
{
    uint8_t result;
    uint8_t reg_add;

    reg_add = electrode % 12;
    reg_add <<= 1;
    reg_add += TOUCHCLAMP_REG_E0TTH;
    
    touchclamp_generic_read ( ctx, reg_add, &result, 1 );

    return result;
}

void touchclamp_set_release_threshold ( touchclamp_t *ctx, uint8_t th_data )
{    
    uint8_t counter;
    uint8_t temp_data[ 1 ];
    uint8_t reg;
    uint8_t electrode;
    
    electrode = 0;

    temp_data[ 0 ] = th_data;

    for( counter = 0; counter < 13; counter++ )
    {
        reg = TOUCHCLAMP_REG_E0RTH + electrode;
        
        touchclamp_generic_write ( ctx, reg, temp_data, 1 );
        
        electrode += 2;
    }
}

uint8_t touchclamp_get_release_threshold ( touchclamp_t *ctx, uint8_t electrode )
{
    uint8_t result;
    uint8_t reg_add;

    reg_add = electrode % 12;
    reg_add <<= 1;
    reg_add += TOUCHCLAMP_REG_E0RTH;
    
    touchclamp_generic_read ( ctx, reg_add, &result, 1 );

    return result;
}

uint16_t touchclamp_get_touch_data ( touchclamp_t *ctx )
{
    uint16_t touch_data;
    uint8_t temp_data_low;
    uint8_t temp_data_high;
    
    touchclamp_generic_read ( ctx, TOUCHCLAMP_REG_TS1, &temp_data_low, 1 );
    touchclamp_generic_read ( ctx, TOUCHCLAMP_REG_TS2, &temp_data_high, 1 );

    touch_data = temp_data_high;
    touch_data <<= 8;
    touch_data |= temp_data_low;

    return touch_data;
}

void touchclamp_set_sample_period ( touchclamp_t *ctx, uint8_t sample_period )
{
    uint8_t scratch;
    uint8_t tx_buf[ 1 ];

    touchclamp_generic_read ( ctx, TOUCHCLAMP_REG_AFE2, &scratch, 1 );
    
    tx_buf[ 0 ] = scratch & TOUCHCLAMP_BIT_MASK_SCRATCH;
    tx_buf[ 0 ] |= sample_period & TOUCHCLAMP_BIT_MASK_SAMP_PER;
    
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_NHDPROXT, tx_buf, 1 );
}

void touchclamp_digital_toggle ( touchclamp_t *ctx, uint8_t electrode )
{
    uint8_t tx_buf[ 1 ];
    
    if ( ( electrode > 3 ) && ( electrode < 12 ) )
    {
        electrode -= 4;
        tx_buf[ 0 ] = electrode;
        tx_buf[ 0 ] <<= 1;
        
        touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_TOG, tx_buf, 1 );
    }
}

void touchclamp_stop ( touchclamp_t *ctx )
{
    uint8_t temp_bck;
    
    touchclamp_generic_read ( ctx, TOUCHCLAMP_REG_ECR, &temp_bck, 1 );
    
    temp_bck &= TOUCHCLAMP_BIT_MASK_STOP_BIT;
    
    touchclamp_generic_write ( ctx, TOUCHCLAMP_REG_ECR, &temp_bck, 1 );
}

uint8_t touchclamp_get_interrupt ( touchclamp_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

