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
 * @file digipot11.c
 * @brief DIGI POT 11 Click Driver.
 */

#include "digipot11.h"

void digipot11_cfg_setup ( digipot11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed      = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address_u1 = DIGIPOT11_U1_DEVICE_ADDRESS_A1A0_00;
    cfg->i2c_address_u2 = DIGIPOT11_U2_DEVICE_ADDRESS_A1A0_00;
}

err_t digipot11_init ( digipot11_t *ctx, digipot11_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->u1_slave_address = cfg->i2c_address_u1;
    ctx->u2_slave_address = cfg->i2c_address_u2;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->u1_slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t digipot11_set_u1_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in ) 
{
    if ( ( DIGIPOT11_WIPER_SEL_A != wiper_sel ) && 
         ( DIGIPOT11_WIPER_SEL_B != wiper_sel ) && 
         ( DIGIPOT11_WIPER_SEL_BOTH != wiper_sel ) )
    {
        return DIGIPOT11_ERROR;
    }
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->u1_slave_address ) ) 
    {
        return DIGIPOT11_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = wiper_sel;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t digipot11_set_u2_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in ) 
{
    if ( ( DIGIPOT11_WIPER_SEL_A != wiper_sel ) && 
         ( DIGIPOT11_WIPER_SEL_B != wiper_sel ) && 
         ( DIGIPOT11_WIPER_SEL_BOTH != wiper_sel ) )
    {
        return DIGIPOT11_ERROR;
    }
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->u2_slave_address ) ) 
    {
        return DIGIPOT11_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = wiper_sel;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

// ------------------------------------------------------------------------- END
