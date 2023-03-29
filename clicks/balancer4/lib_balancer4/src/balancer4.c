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
 * @file balancer4.c
 * @brief Balancer 4 Click Driver.
 */

#include "balancer4.h"

void balancer4_cfg_setup ( balancer4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BALANCER4_SET_DEV_ADDR;
}

err_t balancer4_init ( balancer4_t *ctx, balancer4_cfg_t *cfg ) 
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

err_t balancer4_default_cfg ( balancer4_t *ctx ) 
{
    err_t error_flag = BALANCER4_OK;
    error_flag |= balancer4_write_register ( ctx, BALANCER4_REG_TIMER, BALANCER4_TIMER_REGISTER_RESET | 
                                                                       BALANCER4_TIMER_I2C_WD_TIMER_RESET );
    Delay_100ms ( );
    error_flag |= balancer4_write_and_verify_register ( ctx, BALANCER4_REG_CONFIG0, 
                                                        BALANCER4_CONFIG0_VBAT_REG_8p4V | 
                                                        BALANCER4_CONFIG0_CHARGING_EN | 
                                                        BALANCER4_CONFIG0_VBAT_PRE_6p4V | 
                                                        BALANCER4_CONFIG0_CELL_OVP_HYS_80mV );
    
    error_flag |= balancer4_write_and_verify_register ( ctx, BALANCER4_REG_CONFIG1, 
                                                        BALANCER4_CONFIG1_NTC_TYPE_STANDARD | 
                                                        BALANCER4_CONFIG1_VCELL_BAL_3p7V | 
                                                        BALANCER4_CONFIG1_BAL_THD_H2L_50mV | 
                                                        BALANCER4_CONFIG1_BAL_THD_L2H_50mV | 
                                                        BALANCER4_CONFIG1_ICC_1000mA );
    
    error_flag |= balancer4_write_and_verify_register ( ctx, BALANCER4_REG_TIMER, 
                                                        BALANCER4_TIMER_FSW_1200KHZ | 
                                                        BALANCER4_TIMER_I2C_WD_TIMER_NORMAL | 
                                                        BALANCER4_TIMER_WD_TIMER_DIS | 
                                                        BALANCER4_TIMER_REGISTER_KEEP | 
                                                        BALANCER4_TIMER_CHG_TIMER_20H | 
                                                        BALANCER4_TIMER_EN_SUSP_BOOST_EN );
    
    return error_flag;
}

err_t balancer4_write_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t balancer4_write_and_verify_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 1 );
    if ( data_buf[ 0 ] == data_in )
    {
        return error_flag;
    }
    return BALANCER4_ERROR;
}

err_t balancer4_read_register ( balancer4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

// ------------------------------------------------------------------------- END
