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
 * \file ambient2.c
 *
 */

#include "ambient2.h"
#include <math.h>


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient2_cfg_setup( ambient2_cfg_t *cfg )
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_addr  = AMBIENT2_I2C_ADDRESS_GND;
}

ambient2_err_t ambient2_init( ambient2_t *ctx, ambient2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT2_ERR_INIT_DRV;
    }

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return AMBIENT2_ERR_UNSUPPORTED_PIN;
    }

    ctx->slave_addr = cfg->i2c_addr;
    ctx->sens_data.amb_light_lx    = 0;
    ctx->sens_data.amb_light_range = 0;
    ctx->sens_data.amb_light_per   = 0;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return AMBIENT2_OK;
}

void ambient2_default_cfg( ambient2_t *ctx )
{
    ambient2_generic_write( ctx, AMBIENT2_REG_CONFIGURATION, AMBIENT2_CFG_RANGE_AUTO_SCALE |
                                                             AMBIENT2_CFG_CONV_TIME_800MS |
                                                             AMBIENT2_CFG_CONV_MODE_CONT_CONV |
                                                             AMBIENT2_CFG_LATCH_COMP_WINDOW_STYLE |
                                                             AMBIENT2_CFG_POL_INT_ACTIVE_LOW |
                                                             AMBIENT2_CFG_FAULT_1_COUNT );
}

void ambient2_generic_write( ambient2_t *ctx, ambient2_reg_addr_t reg_addr, ambient2_data_t data_in )
{
    uint8_t data_buff[ 3 ];

    data_buff[ 0 ] = reg_addr;
    data_buff[ 1 ] = data_in >> 8;
    data_buff[ 2 ] = data_in;

    i2c_master_write( &ctx->i2c, data_buff, 3 ); 
}

ambient2_data_t ambient2_generic_read( ambient2_t *ctx, ambient2_reg_addr_t reg_addr )
{
    uint8_t data_buff[ 2 ];
    ambient2_data_t ret_val;

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buff, 2 );

    ret_val = data_buff[ 0 ];
    ret_val <<= 8;
    ret_val |= data_buff[ 1 ];

    return ret_val;
}

void ambient2_get_sens_results( ambient2_t *ctx )
{
    ambient2_data_t read_data;
    double res;
    double range;

    read_data = ambient2_generic_read( ctx, AMBIENT2_REG_RESULT );

    res = 0.01;
    res *= pow( 2, read_data >> 12 );
    res *= read_data & 0x0FFF;

    range = 40.95;
    range *= pow( 2, read_data >> 12 );

    ctx->sens_data.amb_light_lx    = res;
    ctx->sens_data.amb_light_range = range;
    ctx->sens_data.amb_light_per   = res / range * 100;
}

uint8_t ambient2_get_int( ambient2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------ END
