/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file currentlimit9.c
 * @brief Current Limit 9 Click Driver.
 */

#include "currentlimit9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                  0x00

void currentlimit9_cfg_setup ( currentlimit9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on  = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENTLIMIT9_DEVICE_ADDRESS;
}

err_t currentlimit9_init ( currentlimit9_t *ctx, currentlimit9_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->on, cfg->on );

    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t currentlimit9_default_cfg ( currentlimit9_t *ctx ) 
{
    currentlimit9_disable( ctx );
    Delay_10ms( );
    
    err_t err_flag = currentlimit9_set_limit( ctx, CURRENTLIMIT9_LIMIT_0_11_A );
    Delay_10ms( );

    currentlimit9_enable( ctx );
    Delay_10ms( );
    return err_flag;
}

void currentlimit9_enable ( currentlimit9_t *ctx ) 
{
    digital_out_high( &ctx->on );
}

void currentlimit9_disable ( currentlimit9_t *ctx ) 
{
    digital_out_low( &ctx->on );
}

err_t currentlimit9_write_data ( currentlimit9_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t currentlimit9_set_wiper_pos ( currentlimit9_t *ctx, uint8_t wiper_pos ) 
{
    return currentlimit9_write_data( ctx, CURRENTLIMIT9_CMD_VREG, wiper_pos );
}

err_t currentlimit9_set_resistance ( currentlimit9_t *ctx, float res_kohm ) 
{
    err_t err_flag = CURRENTLIMIT9_ERROR;
    if ( CURRENTLIMIT9_RES_200_KOHM >= res_kohm )
    {
        res_kohm /= CURRENTLIMIT9_RES_200_KOHM;
        res_kohm *= ( float ) CURRENTLIMIT9_WIPER_POS_MAX;
        err_flag = currentlimit9_set_wiper_pos( ctx, ( uint8_t ) res_kohm );
    }
    return err_flag;
}

err_t currentlimit9_set_limit ( currentlimit9_t *ctx, currentlimit9_limit_t current_limit )
{
    float current_limit_table[ 7 ] = { CURRENTLIMIT9_RESISTANCE };
    return currentlimit9_set_resistance( ctx, current_limit_table[ current_limit ] );
}

uint8_t currentlimit9_get_fault ( currentlimit9_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
