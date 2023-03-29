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

#include "proximity9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity9_cfg_setup ( proximity9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY9_DEV_ADDR;
}

PROXIMITY9_RETVAL proximity9_init ( proximity9_t *ctx, proximity9_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY9_OK;
}

void proximity9_default_cfg ( proximity9_t *ctx )
{
    proximity9_write_register( ctx, PROXIMITY9_ALS_CONF_REG, PROXIMITY9_ALS_IT_320_MS );
    proximity9_write_register( ctx, PROXIMITY9_PS_CONF_REG, PROXIMITY9_PS_OUTPUT_16BIT | 
                                                            PROXIMITY9_PS_INT_TRIGGER_BOTH | 
                                                            PROXIMITY9_PS_IR_ON_1_OFF_80 | 
                                                            PROXIMITY9_PS_IT_8T );
    proximity9_write_register( ctx, PROXIMITY9_PS_MS_REG, PROXIMITY9_PS_NORMAL_OP_MODE | 
                                                          PROXIMITY9_LED_I_160_MA );
    proximity9_write_register( ctx, PROXIMITY9_PS_THRSHD_L_REG, 30 );
    proximity9_write_register( ctx, PROXIMITY9_PS_THRSHD_H_REG, 2000 );
}

void proximity9_generic_write ( proximity9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proximity9_generic_read ( proximity9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

PROXIMITY9_RETVAL proximity9_read_register ( proximity9_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];   

    if ( reg_addr > PROXIMITY9_DEV_ID_REG )
    {
        return PROXIMITY9_INVALID_ADDR;
    }
    
    proximity9_generic_read( ctx, reg_addr, temp_data, 2 );

    *data_out = temp_data[ 1 ];
    *data_out <<= 8;
    *data_out |= temp_data[ 0 ];
    
    return PROXIMITY9_OK;
}

PROXIMITY9_RETVAL proximity9_write_register ( proximity9_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( reg_addr > PROXIMITY9_PS_THRSHD_H_REG )
    {
        return PROXIMITY9_INVALID_ADDR;
    }
    if ( reg_addr == PROXIMITY9_ALS_CONF_REG )
    {
        switch ( data_in >> 6 )
        {
            case 0 :
            {
                ctx->als_sens = 0.10;
            break;
            }
            case 1 :
            {
                ctx->als_sens = 0.05;
            break;
            }
            case 2 :
            {
                ctx->als_sens = 0.025;
            break;
            }
            case 3 :
            {
                ctx->als_sens = 0.0125;
            break;
            }
            default :
            {
                break;
            }
        }
    }
    
    temp_data[ 0 ] = data_in;
    temp_data[ 1 ] = data_in >> 8;
    
    proximity9_generic_write( ctx, reg_addr, temp_data, 2 );
    
    return PROXIMITY9_OK;
}

uint8_t proximity9_check_int_pin ( proximity9_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t proximity9_check_int_flag ( proximity9_t *ctx, uint8_t bit_mask )
{
    uint16_t int_flag;
    uint8_t ret_val;
    
    proximity9_read_register( ctx, PROXIMITY9_INT_FLAG_REG, &int_flag );
    
    ret_val = int_flag >> 8;
    ret_val &= bit_mask;
    
    return ret_val;
}

float proximity9_get_als_lux ( proximity9_t *ctx )
{
    uint16_t tmp_data;
    float ret_val;
    
    proximity9_read_register( ctx, PROXIMITY9_ALS_DATA_REG, &tmp_data );

    ret_val = tmp_data;
    ret_val *= ctx->als_sens;
    
    return ret_val;
}

// ------------------------------------------------------------------------- END

