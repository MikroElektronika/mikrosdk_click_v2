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
 * @file proximity20.c
 * @brief Proximity 20 Click Driver.
 */

#include "proximity20.h"

void proximity20_cfg_setup ( proximity20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY20_DEVICE_ADDRESS_U2;
}

err_t proximity20_init ( proximity20_t *ctx, proximity20_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    proximity20_disable_device ( ctx );

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
    
    proximity20_enable_device ( ctx );

    return I2C_MASTER_SUCCESS;
}

err_t proximity20_default_cfg ( proximity20_t *ctx ) 
{
    err_t error_flag = PROXIMITY20_OK;
    if ( PROXIMITY20_OK != proximity20_check_communication ( ctx ) )
    {
        return PROXIMITY20_ERROR;
    }
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U2 );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF1, PROXIMITY20_PS_CONF1_PS_HD_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_SP_INT_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_SMART_PERS_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_PERS_4 | 
                                                                              PROXIMITY20_PS_CONF1_PS_INT_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_CAL_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_ON_EN );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF2, PROXIMITY20_PS_CONF2_PS_SENS_NORMAL | 
                                                                              PROXIMITY20_PS_CONF2_PS_OFFSET_DIS | 
                                                                              PROXIMITY20_PS_CONF2_PS_CURRENT_15_MA | 
                                                                              PROXIMITY20_PS_CONF2_PS_PERIOD_200_MS | 
                                                                              PROXIMITY20_PS_CONF2_PS_IT_8T | 
                                                                              PROXIMITY20_PS_CONF2_PS_MPS_8 | 
                                                                              PROXIMITY20_PS_CONF2_PS_ITB_25_US | 
                                                                              PROXIMITY20_PS_CONF2_PS_GAIN_X2 );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF3, PROXIMITY20_PS_CONF3_PS_SPERIOD_DIS | 
                                                                              PROXIMITY20_PS_CONF3_PS_SC_DIS | 
                                                                              PROXIMITY20_PS_CONF3_PS_TRIG_OFF | 
                                                                              PROXIMITY20_PS_CONF3_PS_MODE_AUTO );
    
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U3 );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF1, PROXIMITY20_PS_CONF1_PS_HD_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_SP_INT_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_SMART_PERS_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_PERS_4 | 
                                                                              PROXIMITY20_PS_CONF1_PS_INT_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_CAL_DIS | 
                                                                              PROXIMITY20_PS_CONF1_PS_ON_EN );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF2, PROXIMITY20_PS_CONF2_PS_SENS_NORMAL | 
                                                                              PROXIMITY20_PS_CONF2_PS_OFFSET_DIS | 
                                                                              PROXIMITY20_PS_CONF2_PS_CURRENT_15_MA | 
                                                                              PROXIMITY20_PS_CONF2_PS_PERIOD_200_MS | 
                                                                              PROXIMITY20_PS_CONF2_PS_IT_8T | 
                                                                              PROXIMITY20_PS_CONF2_PS_MPS_8 | 
                                                                              PROXIMITY20_PS_CONF2_PS_ITB_25_US | 
                                                                              PROXIMITY20_PS_CONF2_PS_GAIN_X2 );
    error_flag |= proximity20_write_register ( ctx, PROXIMITY20_REG_PS_CONF3, PROXIMITY20_PS_CONF3_PS_SPERIOD_DIS | 
                                                                              PROXIMITY20_PS_CONF3_PS_SC_DIS | 
                                                                              PROXIMITY20_PS_CONF3_PS_TRIG_OFF | 
                                                                              PROXIMITY20_PS_CONF3_PS_MODE_AUTO );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity20_write_register ( proximity20_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity20_read_register ( proximity20_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        return PROXIMITY20_ERROR;
    }
    if ( NULL != data_out )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return PROXIMITY20_OK;
}

err_t proximity20_set_device_address ( proximity20_t *ctx, uint8_t dev_addr )
{
    if ( ( PROXIMITY20_DEVICE_ADDRESS_U2 != dev_addr ) && 
         ( PROXIMITY20_DEVICE_ADDRESS_U3 != dev_addr ) )
    {
        return PROXIMITY20_ERROR;
    }
    ctx->slave_address = dev_addr;
    return i2c_master_set_slave_address ( &ctx->i2c, ctx->slave_address );
}

err_t proximity20_check_communication ( proximity20_t *ctx )
{
    err_t error_flag = PROXIMITY20_OK;
    uint16_t device_id = 0;
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U2 );
    error_flag |= proximity20_read_register( ctx, PROXIMITY20_REG_ID, &device_id );
    if ( PROXIMITY20_DEVICE_ID_U2 != device_id )
    {
        return PROXIMITY20_ERROR;
    }
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U3 );
    error_flag |= proximity20_read_register( ctx, PROXIMITY20_REG_ID, &device_id );
    if ( PROXIMITY20_DEVICE_ID_U3 != device_id )
    {
        return PROXIMITY20_ERROR;
    }
    return error_flag;
}

err_t proximity20_read_proximity ( proximity20_t *ctx, uint16_t *ps_data_u2, uint16_t *ps_data_u3 )
{
    err_t error_flag = PROXIMITY20_OK;
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U2 );
    error_flag |= proximity20_read_register ( ctx, PROXIMITY20_REG_PS_DATA, ps_data_u2 );
    error_flag |= proximity20_set_device_address ( ctx, PROXIMITY20_DEVICE_ADDRESS_U3 );
    error_flag |= proximity20_read_register ( ctx, PROXIMITY20_REG_PS_DATA, ps_data_u3 );
    return error_flag;
}

void proximity20_enable_device ( proximity20_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void proximity20_disable_device ( proximity20_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

uint8_t proximity20_get_int_pin ( proximity20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
