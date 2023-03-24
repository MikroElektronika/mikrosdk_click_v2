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
 * @file proximity18.c
 * @brief Proximity 18 Click Driver.
 */

#include "proximity18.h"

void proximity18_cfg_setup ( proximity18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY18_DEVICE_ADDRESS;
}

err_t proximity18_init ( proximity18_t *ctx, proximity18_cfg_t *cfg ) 
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

err_t proximity18_default_cfg ( proximity18_t *ctx )
{
    err_t error_flag = PROXIMITY18_OK;
    if ( PROXIMITY18_ERROR == proximity18_check_communication ( ctx ) )
    {
        return PROXIMITY18_ERROR;
    }
    error_flag |= proximity18_write_register ( ctx, PROXIMITY18_REG_PS_CONF12, PROXIMITY18_PS_CONF2_MPX_INT_EN_EN | 
                                                                               PROXIMITY18_PS_CONF2_MPX_MODE_EN | 
                                                                               PROXIMITY18_PS_CONF2_PS_GAIN_TWO_STEP | 
                                                                               PROXIMITY18_PS_CONF2_PS_HD_12BITS | 
                                                                               PROXIMITY18_PS_CONF2_PS_INT_DIS | 
                                                                               PROXIMITY18_PS_CONF1_PS_DUTY_1_OF_40 | 
                                                                               PROXIMITY18_PS_CONF1_PS_PERS_4 | 
                                                                               PROXIMITY18_PS_CONF1_PS_IT_8T | 
                                                                               PROXIMITY18_PS_CONF1_PS_SD_POWER_ON );
    error_flag |= proximity18_write_register ( ctx, PROXIMITY18_REG_PS_CONF3_MS, PROXIMITY18_PS_MS_PS_SC_CUR_1X | 
                                                                                 PROXIMITY18_PS_MS_PS_SP_1X_CAP | 
                                                                                 PROXIMITY18_PS_MS_PS_SPO_00H | 
                                                                                 PROXIMITY18_PS_MS_LED_I_100mA | 
                                                                                 PROXIMITY18_PS_CONF3_LED_I_LOW_DIS | 
                                                                                 PROXIMITY18_PS_CONF3_IRED_SELECT_IRED1 | 
                                                                                 PROXIMITY18_PS_CONF3_PS_SMART_PERS_DIS | 
                                                                                 PROXIMITY18_PS_CONF3_PS_AF_EN | 
                                                                                 PROXIMITY18_PS_CONF3_PS_TRIG_NO_TRIG | 
                                                                                 PROXIMITY18_PS_CONF3_PS_MS_NORMAL | 
                                                                                 PROXIMITY18_PS_CONF3_PS_SC_EN_TURN_OFF );
    return error_flag;
}

err_t proximity18_write_register ( proximity18_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity18_read_register ( proximity18_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        return PROXIMITY18_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    return PROXIMITY18_OK;
}

err_t proximity18_check_communication ( proximity18_t *ctx )
{
    uint16_t device_id;
    if ( PROXIMITY18_OK == proximity18_read_register( ctx, PROXIMITY18_REG_ID, &device_id ) )
    {
        if ( PROXIMITY18_DEVICE_ID == ( device_id & PROXIMITY18_DEVICE_ID_MASK ) )
        {
            return PROXIMITY18_OK;
        }
    }
    return PROXIMITY18_ERROR;
}

uint8_t proximity18_get_int_pin ( proximity18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t proximity18_start_measurement ( proximity18_t *ctx )
{ 
    uint16_t conf3_ms;
    if ( PROXIMITY18_OK == proximity18_read_register ( ctx, PROXIMITY18_REG_PS_CONF3_MS, &conf3_ms ) )
    {
        conf3_ms |= PROXIMITY18_PS_CONF3_PS_TRIG_ONE_TIME;
        if ( PROXIMITY18_OK == proximity18_write_register ( ctx, PROXIMITY18_REG_PS_CONF3_MS, conf3_ms ) )
        {
            return PROXIMITY18_OK;
        }
    }
    return PROXIMITY18_ERROR;
}

err_t proximity18_wait_for_data_ready ( proximity18_t *ctx )
{
    uint16_t timeout_cnt = 0;
    while ( timeout_cnt++ < PROXIMITY18_DATA_READY_TIMEOUT_MS )
    {
        if ( !proximity18_get_int_pin ( ctx ) )
        {
            uint16_t int_flag;
            if ( PROXIMITY18_ERROR == proximity18_read_register ( ctx, PROXIMITY18_REG_INT_FLAG, &int_flag ) )
            {
                return PROXIMITY18_ERROR;
            }
            if ( int_flag & PROXIMITY18_INT_FLAG_MPX_DATA_READY )
            {
                return PROXIMITY18_OK;
            }
        }
        Delay_1ms ( );
    }
    return PROXIMITY18_ERROR;
}

err_t proximity18_read_proximity ( proximity18_t *ctx, uint16_t *ps1_data, uint16_t *ps2_data, uint16_t *ps3_data )
{
    if ( PROXIMITY18_ERROR == proximity18_read_register ( ctx, PROXIMITY18_REG_PS1_DATA, ps1_data ) )
    {
        return PROXIMITY18_ERROR;
    }
    if ( PROXIMITY18_ERROR == proximity18_read_register ( ctx, PROXIMITY18_REG_PS2_DATA, ps2_data ) )
    {
        return PROXIMITY18_ERROR;
    }
    if ( PROXIMITY18_ERROR == proximity18_read_register ( ctx, PROXIMITY18_REG_PS3_DATA, ps3_data ) )
    {
        return PROXIMITY18_ERROR;
    }
    return PROXIMITY18_OK;
}

// ------------------------------------------------------------------------- END
