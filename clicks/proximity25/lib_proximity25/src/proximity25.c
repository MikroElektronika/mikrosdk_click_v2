/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file proximity25.c
 * @brief Proximity 25 Click Driver.
 */

#include "proximity25.h"

void proximity25_cfg_setup ( proximity25_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY25_DEVICE_ADDRESS;
}

err_t proximity25_init ( proximity25_t *ctx, proximity25_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t proximity25_default_cfg ( proximity25_t *ctx ) 
{
    err_t error_flag = PROXIMITY25_OK;
    if ( PROXIMITY25_OK != proximity25_check_com ( ctx ) )
    {
        return PROXIMITY25_ERROR;
    }
    error_flag |= proximity25_write_reg ( ctx, PROXIMITY25_REG_PS_CONF1, PROXIMITY25_PS_CONF1_PS_CAL_EN | 
                                                                         PROXIMITY25_PS_CONF1_PS_ON_EN | 
                                                                         PROXIMITY25_PS_CONF1_RESERVED );
    error_flag |= proximity25_write_reg ( ctx, PROXIMITY25_REG_PS_CONF2, PROXIMITY25_PS_CONF2_PS_IT_8T | 
                                                                         PROXIMITY25_PS_CONF2_PS_MPS_8 | 
                                                                         PROXIMITY25_PS_CONF2_PS_HG_X2 | 
                                                                         PROXIMITY25_PS_CONF2_PS_SSINT_DIS | 
                                                                         PROXIMITY25_PS_CONF2_PS_PERIOD_80_MS | 
                                                                         PROXIMITY25_PS_CONF2_PS_PERS_4 | 
                                                                         PROXIMITY25_PS_CONF2_PS_INT_DIS | 
                                                                         PROXIMITY25_PS_CONF2_PS_SMART_PERS_DIS | 
                                                                         PROXIMITY25_PS_CONF2_PS_SD_POWER_ON |
                                                                         PROXIMITY25_PS_CONF2_RESERVED );
    error_flag |= proximity25_write_reg ( ctx, PROXIMITY25_REG_PS_CONF3, PROXIMITY25_PS_CONF3_PS_SC_DIS | 
                                                                         PROXIMITY25_PS_CONF3_PS_SC_LEVEL_1 | 
                                                                         PROXIMITY25_PS_CONF3_PS_CURRENT_70_MA | 
                                                                         PROXIMITY25_PS_CONF3_PS_MODE_AUTO | 
                                                                         PROXIMITY25_PS_CONF3_PS_TRIG_OFF |
                                                                         PROXIMITY25_PS_CONF3_PS_OFFSET_DIS | 
                                                                         PROXIMITY25_PS_CONF3_PS_SP_INT_DIS |
                                                                         PROXIMITY25_PS_CONF3_RESERVED );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity25_write_reg ( proximity25_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity25_read_reg ( proximity25_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        return PROXIMITY25_ERROR;
    }
    if ( NULL != data_out )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return PROXIMITY25_OK;
}

err_t proximity25_check_com ( proximity25_t *ctx )
{
    uint16_t device_id = 0;
    if ( PROXIMITY25_OK == proximity25_read_reg( ctx, PROXIMITY25_REG_ID, &device_id ) )
    {
        if ( PROXIMITY25_DEVICE_ID == device_id )
        {
            return PROXIMITY25_OK;
        }
    }
    return PROXIMITY25_ERROR;
}

err_t proximity25_read_proximity ( proximity25_t *ctx, uint16_t *ps_data )
{
    return proximity25_read_reg ( ctx, PROXIMITY25_REG_PS_DATA, ps_data );
}

uint8_t proximity25_get_int_pin ( proximity25_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
