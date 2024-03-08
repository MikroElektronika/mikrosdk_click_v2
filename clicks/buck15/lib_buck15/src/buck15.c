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
 * @file buck15.c
 * @brief Buck 15 Click Driver.
 */

#include "buck15.h"

void buck15_cfg_setup ( buck15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCK15_DEVICE_ADDRESS_GND;
}

err_t buck15_init ( buck15_t *ctx, buck15_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t buck15_default_cfg ( buck15_t *ctx ) 
{   
    buck15_disable_device( ctx );
    Delay_10ms( );

    err_t err_flag = buck15_set_vout( ctx, BUCK15_VOUT_0V6 );
    Delay_10ms( );

    buck15_enable_device( ctx );
    Delay_10ms( );

    return err_flag;
}

void buck15_enable_device ( buck15_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void buck15_disable_device ( buck15_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

uint8_t buck15_get_power_good ( buck15_t *ctx ) 
{
    return digital_in_read( &ctx->pg );
}

err_t buck15_generic_write ( buck15_t *ctx, uint8_t instr, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { instr, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck15_generic_read ( buck15_t *ctx, uint8_t instr, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &instr, 1, data_out, 1 );
}

err_t buck15_set_vset ( buck15_t *ctx, uint8_t vset_wp )
{
    return buck15_generic_write( ctx, BUCK15_INSTR_RDAC_SEL_1, vset_wp );
}

err_t buck15_set_vos ( buck15_t *ctx, uint8_t vos_wp )
{
    return buck15_generic_write( ctx, BUCK15_INSTR_RDAC_SEL_2, vos_wp );
}

err_t buck15_set_vout ( buck15_t *ctx, buck15_vout_t vout )
{
    uint8_t vset_table[ 22 ] = { BUCK15_VSET_WIPER_POS };
    uint8_t vos_table[ 22 ] = { BUCK15_VOS_WIPER_POS };
    err_t err_flag = buck15_set_vset( ctx, vset_table[ vout ] );
    Delay_10ms( );
    err_flag |= buck15_set_vos( ctx, vos_table[ vout ] );
    Delay_10ms( );
    return err_flag;
}


// ------------------------------------------------------------------------- END
