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
 * @file hallswitch3.c
 * @brief Hall Switch 3 Click Driver.
 */

#include "hallswitch3.h"

/**
 * @brief Dummy and dot position data.
 * @details Definition of dummy and dot position data.
 */
#define DUMMY                    0x00

void hallswitch3_cfg_setup ( hallswitch3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->out = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLSWITCH3_DEVICE_ADDRESS;
}

err_t hallswitch3_init ( hallswitch3_t *ctx, hallswitch3_cfg_t *cfg ) 
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

    digital_in_init( &ctx->out, cfg->out );

    return I2C_MASTER_SUCCESS;
}

err_t hallswitch3_default_cfg ( hallswitch3_t *ctx ) 
{
    uint8_t device_id = DUMMY;
    err_t err_flag = hallswitch3_get_device_id( ctx, &device_id );
    if ( HALLSWITCH3_WHO_AM_I == device_id )
    {        
        err_flag |= hallswitch3_set_out_data_rate( ctx, HALLSWITCH3_USER_ODR_HSP );
        Delay_10ms( );

        err_flag |= hallswitch3_set_threshold( ctx, HALLSWITCH3_ASSERT_THOLD_DEFAULT, 
                                                    HALLSWITCH3_CLEAR_THOLD_DEFAULT );
        Delay_10ms( );

        err_flag |= hallswitch3_autonomous_mode( ctx );
        Delay_10ms( );
    }
    else
    {
        err_flag = HALLSWITCH3_ERROR;
    }
    return err_flag;
}

err_t hallswitch3_reg_write ( hallswitch3_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t hallswitch3_reg_read ( hallswitch3_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t hallswitch3_get_status ( hallswitch3_t *ctx, uint8_t *status ) 
{
    return hallswitch3_reg_read( ctx, HALLSWITCH3_REG_STATUS, status );
}

err_t hallswitch3_reset ( hallswitch3_t *ctx ) 
{
    return hallswitch3_reg_write( ctx, HALLSWITCH3_REG_CONTROL_REG1, HALLSWITCH3_CONTROL_SW_RESET );
}

err_t hallswitch3_set_one_shot ( hallswitch3_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = hallswitch3_reg_read( ctx, HALLSWITCH3_REG_CONTROL_REG1, &data_buf );
    data_buf |= HALLSWITCH3_CONTROL_ONE_SHOT;
    err_flag |= hallswitch3_reg_write( ctx, HALLSWITCH3_REG_CONTROL_REG1, data_buf );
    return err_flag;
}

err_t hallswitch3_autonomous_mode ( hallswitch3_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = hallswitch3_reg_read( ctx, HALLSWITCH3_REG_CONTROL_REG1, &data_buf );
    data_buf |= HALLSWITCH3_CONTROL_AUTO_START;
    err_flag |= hallswitch3_reg_write( ctx, HALLSWITCH3_REG_CONTROL_REG1, data_buf );
    return err_flag;
}

err_t hallswitch3_set_vpol ( hallswitch3_t *ctx, uint8_t v_pol ) 
{
    err_t err_flag = HALLSWITCH3_ERROR;
    if ( ( HALLSWITCH3_CONTROL_V_POL_ASSERT_L == v_pol ) || 
         ( HALLSWITCH3_CONTROL_V_POL_ASSERT_H == v_pol ) )
    {
        uint8_t data_buf = DUMMY;
        err_flag = hallswitch3_reg_read( ctx, HALLSWITCH3_REG_CONTROL_REG1, &data_buf );
        data_buf &= ~HALLSWITCH3_CONTROL_V_POL_ASSERT_L;
        data_buf |= v_pol;
        err_flag |= hallswitch3_reg_write( ctx, HALLSWITCH3_REG_CONTROL_REG1, data_buf );
    }
    return err_flag;
}

err_t hallswitch3_get_mag_data ( hallswitch3_t *ctx, int8_t *mag_data ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = hallswitch3_reg_read( ctx, HALLSWITCH3_REG_OUT_M_REG, &data_buf );
    *mag_data = ( int8_t ) data_buf;
    *mag_data >>= 2;
    return err_flag;
}

err_t hallswitch3_set_threshold ( hallswitch3_t *ctx, uint8_t assert_thold, uint8_t clear_thold ) 
{
    err_t err_flag = HALLSWITCH3_ERROR;
    if ( ( assert_thold | clear_thold ) <= HALLSWITCH3_THOLD_BITMASK )
    {
        assert_thold <<= 3;
        clear_thold <<= 3;
        err_flag = hallswitch3_reg_write( ctx, HALLSWITCH3_REG_USER_ASSERT_THRESH, assert_thold );
        err_flag |= hallswitch3_reg_write( ctx, HALLSWITCH3_REG_USER_CLEAR_THRESH, clear_thold );
    }
    return err_flag;
}

err_t hallswitch3_set_out_data_rate ( hallswitch3_t *ctx, uint8_t odr ) 
{
    err_t err_flag = HALLSWITCH3_ERROR;
    if ( odr < HALLSWITCH3_USER_ODR_CFG_ERR )
    {
        err_flag = hallswitch3_reg_write( ctx, HALLSWITCH3_REG_USER_ODR, odr );
    }
    return err_flag;
}

err_t hallswitch3_get_device_id ( hallswitch3_t *ctx, uint8_t *device_id ) 
{
    return hallswitch3_reg_read( ctx, HALLSWITCH3_REG_WHO_AM_I, device_id );
}

uint8_t hallswitch3_check_mag_field ( hallswitch3_t *ctx ) 
{
    return digital_in_read( &ctx->out );
}

// ------------------------------------------------------------------------- END
