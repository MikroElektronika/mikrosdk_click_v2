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

#include "thermo17.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THERMO17_LB_RESOLUTION                              0.0625
#define THERMO17_LB_SHIFT                                   4
#define THERMO17_WRITE_SIZE                                 2
#define THERMO17_READ_SIZE                                  1

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo17_cfg_setup ( thermo17_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO17_SLAVE_ADDRESS;
}

THERMO17_RETVAL thermo17_init ( thermo17_t *ctx, thermo17_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO17_INIT_ERROR;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO17_OK;
}

void thermo17_generic_write ( thermo17_t *ctx, uint8_t reg_adr, uint8_t write_data )
{
    uint8_t tx_buf[ THERMO17_WRITE_SIZE ];
    
    tx_buf[ 0 ] = reg_adr;
    tx_buf[ 1 ] = write_data;

    i2c_master_write( &ctx->i2c, tx_buf, THERMO17_WRITE_SIZE );    
}

uint8_t thermo17_generic_read ( thermo17_t *ctx,  uint8_t reg_adr )
{
    uint8_t tx_buf[ 1 ];
    uint8_t temp_data;

    tx_buf [ 0 ] = reg_adr;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, &temp_data, THERMO17_READ_SIZE );
    
    return temp_data;
}

float thermo17_read_temp ( thermo17_t *ctx, uint8_t temp_macro )
{
    float ret_data;
    uint8_t tmp;

    switch ( temp_macro )
    {
        case THERMO17_TEMPERATURE_LOCAL:
        {
            tmp = thermo17_generic_read( ctx, THERMO17_REG_R_LOCAL_TEMP_HB );
            ret_data = tmp;
            tmp = thermo17_generic_read( ctx, THERMO17_REG_R_LOCAL_TEMP_LB );
            tmp >>= THERMO17_LB_SHIFT;
            ret_data += tmp * THERMO17_LB_RESOLUTION;
            return ret_data;
        }

        case THERMO17_TEMPERATURE_REMOTE:
        {
            tmp = thermo17_generic_read( ctx, THERMO17_REG_R_REMOTE_TEMP_HB );
            ret_data = tmp;
            tmp = thermo17_generic_read( ctx, THERMO17_REG_R_REMOTE_TEMP_LB );
            tmp >>= THERMO17_LB_SHIFT;
            ret_data += tmp * THERMO17_LB_RESOLUTION;
            return ret_data;
        }
        
        default:
        {
            return THERMO17_ERROR;
        }
    }
}

uint8_t thermo17_get_int_status ( thermo17_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t thermo17_get_an_status ( thermo17_t *ctx )
{
    return digital_in_read( &ctx->an );
}

// ------------------------------------------------------------------------- END

