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
 * @file proximity23.c
 * @brief Proximity 23 Click Driver.
 */

#include "proximity23.h"

void proximity23_cfg_setup ( proximity23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY23_DEVICE_ADDRESS;
}

err_t proximity23_init ( proximity23_t *ctx, proximity23_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_10ms ( );
    proximity23_enable_device ( ctx );
    Delay_100ms ( );

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

err_t proximity23_default_cfg ( proximity23_t *ctx ) 
{
    err_t error_flag = PROXIMITY23_OK;
    if ( PROXIMITY23_OK != proximity23_check_com ( ctx ) )
    {
        return PROXIMITY23_ERROR;
    }
    error_flag |= proximity23_write_reg ( ctx, PROXIMITY23_REG_PS_CONF1, PROXIMITY23_PS_CONF1_PS_CAL_EN | 
                                                                         PROXIMITY23_PS_CONF1_PS_ON_EN | 
                                                                         PROXIMITY23_PS_CONF1_RESERVED );
    error_flag |= proximity23_write_reg ( ctx, PROXIMITY23_REG_PS_CONF2, PROXIMITY23_PS_CONF2_PS_IT_8T | 
                                                                         PROXIMITY23_PS_CONF2_PS_MPS_8 | 
                                                                         PROXIMITY23_PS_CONF2_PS_ITB_25_US | 
                                                                         PROXIMITY23_PS_CONF2_PS_GAIN_EN | 
                                                                         PROXIMITY23_PS_CONF2_PS_PERIOD_80_MS | 
                                                                         PROXIMITY23_PS_CONF2_PS_PERS_4 | 
                                                                         PROXIMITY23_PS_CONF2_PS_INT_DIS | 
                                                                         PROXIMITY23_PS_CONF2_PS_SMART_PERS_DIS | 
                                                                         PROXIMITY23_PS_CONF2_PS_ST_START |
                                                                         PROXIMITY23_PS_CONF2_RESERVED );
    error_flag |= proximity23_write_reg ( ctx, PROXIMITY23_REG_PS_CONF3, PROXIMITY23_PS_CONF3_PS_SC_DIS | 
                                                                         PROXIMITY23_PS_CONF3_PS_HD_12_BITS | 
                                                                         PROXIMITY23_PS_CONF3_I_VCSEL_16_MA | 
                                                                         PROXIMITY23_PS_CONF3_PS_AF_AUTO |
                                                                         PROXIMITY23_PS_CONF3_PS_FOR_TRIG_OFF | 
                                                                         PROXIMITY23_PS_CONF3_PS_FORCENUM_ONE | 
                                                                         PROXIMITY23_PS_CONF3_PS_SP_INT_DIS |
                                                                         PROXIMITY23_PS_CONF3_RESERVED );
    error_flag |= proximity23_write_reg ( ctx, PROXIMITY23_REG_PS_CONF4, PROXIMITY23_PS_CONF4_PS_LPPER_320_MS | 
                                                                         PROXIMITY23_PS_CONF4_PS_LPEN_DIS | 
                                                                         PROXIMITY23_PS_CONF4_PS_AC_PERIOD_12_MS | 
                                                                         PROXIMITY23_PS_CONF4_PS_AC_NUM_8 |
                                                                         PROXIMITY23_PS_CONF4_PS_AC_DIS | 
                                                                         PROXIMITY23_PS_CONF4_PS_AC_TRIG_DIS | 
                                                                         PROXIMITY23_PS_CONF4_PS_AC_INT_DIS |
                                                                         PROXIMITY23_PS_CONF4_RESERVED );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity23_write_reg ( proximity23_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity23_read_reg ( proximity23_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        return PROXIMITY23_ERROR;
    }
    if ( NULL != data_out )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return PROXIMITY23_OK;
}

err_t proximity23_check_com ( proximity23_t *ctx )
{
    uint16_t device_id = 0;
    if ( PROXIMITY23_OK == proximity23_read_reg( ctx, PROXIMITY23_REG_ID, &device_id ) )
    {
        if ( PROXIMITY23_DEVICE_ID == device_id )
        {
            return PROXIMITY23_OK;
        }
    }
    return PROXIMITY23_ERROR;
}

err_t proximity23_read_proximity ( proximity23_t *ctx, uint16_t *ps_data )
{
    return proximity23_read_reg ( ctx, PROXIMITY23_REG_PS_DATA, ps_data );
}

void proximity23_enable_device ( proximity23_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void proximity23_disable_device ( proximity23_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

uint8_t proximity23_get_int_pin ( proximity23_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
