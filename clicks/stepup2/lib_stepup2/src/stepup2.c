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
 * @file stepup2.c
 * @brief Step Up 2 Click Driver.
 */

#include "stepup2.h"

void stepup2_cfg_setup ( stepup2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPUP2_DEVICE_ADDRESS_0;
}

err_t stepup2_init ( stepup2_t *ctx, stepup2_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );
    digital_out_low( &ctx->en );
    
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

    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t stepup2_default_cfg ( stepup2_t *ctx ) 
{  
    stepup2_disable( ctx );
    Delay_100ms( );

    err_t err_flag = stepup2_set_resistance( ctx, STEPUP2_RES_3_01_KOHM );
    Delay_100ms( );

    stepup2_enable( ctx );
    Delay_100ms( );    

    return err_flag;
}

void stepup2_enable ( stepup2_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void stepup2_disable ( stepup2_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t stepup2_write_data ( stepup2_t *ctx, uint8_t ctrl_byte, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ctrl_byte;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepup2_read_data ( stepup2_t *ctx, uint8_t *data_out ) 
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t stepup2_set_wiper_pos ( stepup2_t *ctx, uint8_t wiper_pos ) 
{
    return stepup2_write_data( ctx, STEPUP2_CTRL_BYTE_VREG, wiper_pos );
}

err_t stepup2_set_resistance ( stepup2_t *ctx, float res_kohm ) 
{
    err_t err_flag = STEPUP2_ERROR;
    if ( STEPUP2_RES_200_KOHM >= res_kohm )
    {
        res_kohm /= STEPUP2_RES_200_KOHM;
        res_kohm *= ( float ) STEPUP2_WIPER_POS_MAX;
        err_flag = stepup2_set_wiper_pos( ctx, ( uint8_t ) res_kohm );
    }
    return err_flag;
}

err_t stepup2_set_vout ( stepup2_t *ctx, stepup2_vout_t vout ) 
{
    uint8_t vout_table[ 15 ] = { STEPUP2_RESISTANCE_LIST };
    stepup2_disable( ctx );
    Delay_10ms( );
    err_t err_flag = stepup2_set_resistance( ctx, vout_table[ vout ] );
    Delay_10ms( );
    stepup2_enable( ctx );
    return err_flag;
}

// ------------------------------------------------------------------------- END
