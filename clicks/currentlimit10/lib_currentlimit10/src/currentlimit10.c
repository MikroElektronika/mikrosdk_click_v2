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
 * @file currentlimit10.c
 * @brief Current Limit 10 Click Driver.
 */

#include "currentlimit10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                  0x00

void currentlimit10_cfg_setup ( currentlimit10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on  = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENTLIMIT10_DEVICE_ADDRESS;
}

err_t currentlimit10_init ( currentlimit10_t *ctx, currentlimit10_cfg_t *cfg ) 
{
    ctx->offset = 0.90;
    
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

err_t currentlimit10_default_cfg ( currentlimit10_t *ctx ) 
{
    currentlimit10_disable( ctx );
    Delay_10ms( );
    
    err_t err_flag = currentlimit10_set_limit( ctx, 1.0 );
    Delay_10ms( );

    currentlimit10_enable( ctx );
    Delay_10ms( );
    return err_flag;
}

void currentlimit10_enable ( currentlimit10_t *ctx ) 
{
    digital_out_high( &ctx->on );
}

void currentlimit10_disable ( currentlimit10_t *ctx ) 
{
    digital_out_low( &ctx->on );
}

err_t currentlimit10_write_data ( currentlimit10_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t currentlimit10_set_wiper_pos ( currentlimit10_t *ctx, uint8_t wiper_pos ) 
{
    return currentlimit10_write_data( ctx, CURRENTLIMIT10_CMD_VREG, wiper_pos );
}

err_t currentlimit10_set_resistance ( currentlimit10_t *ctx, float res_kohm ) 
{
    err_t err_flag = CURRENTLIMIT10_ERROR;
    if ( CURRENTLIMIT10_RES_200_KOHM >= res_kohm )
    {
        res_kohm /= CURRENTLIMIT10_RES_200_KOHM;
        res_kohm *= ( float ) CURRENTLIMIT10_WIPER_POS_MAX;
        err_flag = currentlimit10_set_wiper_pos( ctx, ( uint8_t ) res_kohm );
    }
    return err_flag;
}

err_t currentlimit10_set_limit ( currentlimit10_t *ctx, float current_limit )
{
    err_t err_flag = CURRENTLIMIT10_ERROR;
    if ( ( CURRENTLIMIT10_LIMIT_MAX > current_limit ) && 
         ( CURRENTLIMIT10_LIMIT_MIN < current_limit ) )
    {
        float res_kohm = CURRENTLIMIT10_COEFF_MULTI;
        res_kohm *= CURRENTLIMIT10_TYP_V_ILIM_MV;
        res_kohm *= ctx->offset;
        res_kohm /= current_limit;
        res_kohm -= CURRENTLIMIT10_RES_L_20_KOHM;
        err_flag = currentlimit10_set_resistance( ctx, res_kohm );
    }
    return err_flag;
}

uint8_t currentlimit10_get_fault ( currentlimit10_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
