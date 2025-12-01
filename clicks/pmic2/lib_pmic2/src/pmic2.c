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
 * @file pmic2.c
 * @brief PMIC 2 Click Driver.
 */

#include "pmic2.h"

void pmic2_cfg_setup ( pmic2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dis = HAL_PIN_NC;
    cfg->bok = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PMIC2_DEVICE_ADDRESS;
}

err_t pmic2_init ( pmic2_t *ctx, pmic2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dis, cfg->dis );

    digital_in_init( &ctx->bok, cfg->bok );
    Delay_100ms ( );

    pmic2_disable_device ( ctx );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t pmic2_default_cfg ( pmic2_t *ctx ) 
{
    err_t error_flag = PMIC2_OK;
    pmic2_enable_device ( ctx );
    Delay_100ms ( );
    if ( PMIC2_ERROR == pmic2_check_communication ( ctx ) )
    {
        return PMIC2_ERROR;
    }
    error_flag |= pmic2_write_reg ( ctx, PMIC2_REG_LVD_OVP, PMIC2_LVD_OVP_LVD_3_5V | 
                                                            PMIC2_LVD_OVP_OVP_4_2V );
    error_flag |= pmic2_write_reg ( ctx, PMIC2_REG_LDO_IUSB, PMIC2_LDO_IUSB_LDO_BP_NORMAL | 
                                                             PMIC2_LDO_IUSB_LDO_CTRL_LDOEN | 
                                                             PMIC2_LDO_IUSB_VLDO_3_3V | 
                                                             PMIC2_LDO_IUSB_IUSB_MAX_200MA );
    error_flag |= pmic2_write_reg ( ctx, PMIC2_REG_FREQUENCY_RANGE, PMIC2_FREQUENCY_RANGE_MAX_1024_KHZ | 
                                                                    PMIC2_FREQUENCY_RANGE_MIN_32_KHZ );
    error_flag |= pmic2_write_reg ( ctx, PMIC2_REG_BOOSTING_FACTOR_RANGE, PMIC2_BOOSTING_FACTOR_RANGE_MAX_16X | 
                                                                          PMIC2_BOOSTING_FACTOR_RANGE_MIN_2X );
    error_flag |= pmic2_write_reg ( ctx, PMIC2_REG_MPPT_INTERVAL, PMIC2_MPPT_INTERVAL_1S );
    return error_flag;
}

err_t pmic2_write_reg ( pmic2_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t pmic2_read_reg ( pmic2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void pmic2_disable_device ( pmic2_t *ctx )
{
    digital_out_high ( &ctx->dis );
}

void pmic2_enable_device ( pmic2_t *ctx )
{
    digital_out_low ( &ctx->dis );
}

uint8_t pmic2_get_bok_pin ( pmic2_t *ctx )
{
    return digital_in_read ( &ctx->bok );
}

err_t pmic2_check_communication ( pmic2_t *ctx )
{
    uint8_t chip_id = 0;
    if ( PMIC2_OK == pmic2_read_reg ( ctx, PMIC2_REG_CHIP_ID, &chip_id ) )
    {
        if ( PMIC2_CHIP_ID == chip_id )
        {
            return PMIC2_OK;
        }
    }
    return PMIC2_ERROR;
}

err_t pmic2_get_charge_current ( pmic2_t *ctx, float *current )
{
    err_t error_flag = PMIC2_OK;
    uint8_t i_range = 0;
    uint8_t i_measured = 0;
    error_flag |= pmic2_read_reg ( ctx, PMIC2_REG_I_RANGE, &i_range );
    error_flag |= pmic2_read_reg ( ctx, PMIC2_REG_I_MEASURED, &i_measured );
    if ( ( PMIC2_OK == error_flag ) && ( NULL != current ) )
    {
        switch ( i_range & PMIC2_I_RANGE_3 )
        {
            case PMIC2_I_RANGE_0:
            {
                *current = i_measured * PMIC2_I_MEASURED_RANGE_0;
                break;
            }
            case PMIC2_I_RANGE_1:
            {
                *current = i_measured * PMIC2_I_MEASURED_RANGE_1;
                break;
            }
            case PMIC2_I_RANGE_2:
            {
                *current = i_measured * PMIC2_I_MEASURED_RANGE_2;
                break;
            }
            case PMIC2_I_RANGE_3:
            {
                *current = i_measured * PMIC2_I_MEASURED_RANGE_3;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
