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
 * @file digipot13.c
 * @brief DIGI POT 13 Click Driver.
 */

#include "digipot13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                  0x00

void digipot13_cfg_setup ( digipot13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIGIPOT13_DEVICE_ADDRESS_GND;
}

err_t digipot13_init ( digipot13_t *ctx, digipot13_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t digipot13_default_cfg ( digipot13_t *ctx ) 
{
    return digipot13_set_wiper_pos( ctx, DIGIPOT13_WIPER_POS_MIDDLE );
}

err_t digipot13_write_data ( digipot13_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { DUMMY };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t digipot13_set_wiper_pos ( digipot13_t *ctx, uint8_t wiper_pos ) 
{
    return digipot13_write_data( ctx, DIGIPOT13_CMD_VREG, wiper_pos );
}

err_t digipot13_set_resistance ( digipot13_t *ctx, digipot13_cfg_res_t cfg_res, float res_kohm ) 
{
    err_t err_flag = DIGIPOT13_ERROR;
    if ( DIGIPOT13_RES_200_KOHM >= res_kohm )
    {
        float wiper_pos = ( float ) res_kohm;
        wiper_pos /= ( float ) DIGIPOT13_RES_200_KOHM;
        wiper_pos *= ( float ) DIGIPOT13_WIPER_POS_MAX;
        if ( DIGIPOT13_CFG_RES_WH == cfg_res )
        {
            wiper_pos = DIGIPOT13_WIPER_POS_MAX - wiper_pos;
        }
        err_flag = digipot13_set_wiper_pos( ctx, ( uint8_t ) wiper_pos );
    }
    return err_flag;
}

err_t digipot13_switch_v_to_nv ( digipot13_t *ctx ) 
{
    return digipot13_write_data( ctx, DIGIPOT13_CMD_VREGxNVREG, DUMMY );
}

err_t digipot13_switch_nv_to_v ( digipot13_t *ctx ) 
{
    return digipot13_write_data( ctx, DIGIPOT13_CMD_NVREGxVREG, DUMMY );
}

// ------------------------------------------------------------------------- END
