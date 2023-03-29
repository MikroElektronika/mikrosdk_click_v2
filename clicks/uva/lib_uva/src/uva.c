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
 * @file uva.c
 * @brief UVA Click Driver.
 */

#include "uva.h"

void uva_cfg_setup ( uva_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = UVA_SET_DEV_ADDR;
}

err_t uva_init ( uva_t *ctx, uva_cfg_t *cfg ) 
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

err_t uva_default_cfg ( uva_t *ctx ) 
{
    if ( UVA_ERROR == uva_check_communication ( ctx ) )
    {
        return UVA_ERROR;
    }
    err_t error_flag = UVA_OK;
    error_flag |= uva_write_register ( ctx, UVA_REG_MODE, UVA_MODE_UVA_OPERATION | UVA_MODE_NORMAL );
    error_flag |= uva_write_register ( ctx, UVA_REG_RES_UV, UVA_RESOLUTION_100MS );
    error_flag |= uva_write_register ( ctx, UVA_REG_RANGE_UVA, UVA_RANGE_X128 );
    error_flag |= uva_write_register ( ctx, UVA_REG_MODE_CTRL, UVA_MODE_CTRL_SLEEP_2_TIMES );
    return error_flag;
}

err_t uva_generic_write ( uva_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t uva_generic_read ( uva_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    err_t error_flag = i2c_master_write( &ctx->i2c, &reg, 1 );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, rx_len );
    return error_flag;
}

err_t uva_write_register ( uva_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return uva_generic_write( ctx, reg, &data_in, 1 );
}

err_t uva_read_register ( uva_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return uva_generic_read ( ctx, reg, data_out, 1 );
}

err_t uva_check_communication ( uva_t *ctx )
{
    uint8_t chip_id = 0;
    if ( UVA_OK == uva_read_register ( ctx, UVA_REG_CHIP_ID, &chip_id ) )
    {
        if ( UVA_CHIP_ID == chip_id )
        {
            return UVA_OK;
        }
    }
    return UVA_ERROR;
}

err_t uva_read_data ( uva_t *ctx, uint16_t *uva_data )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( UVA_OK == uva_generic_read ( ctx, UVA_REG_UVA_LSB, data_buf, 2 ) )
    {
        *uva_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return UVA_OK;
    }
    return UVA_ERROR;
}

err_t uva_soft_reset ( uva_t *ctx )
{
    return uva_write_register ( ctx, UVA_REG_SOFT_RESET, UVA_SOFT_RESET );
}

// ------------------------------------------------------------------------- END
