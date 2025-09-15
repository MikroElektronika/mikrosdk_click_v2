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
 * @file smartbuck6.c
 * @brief Smart Buck 6 Click Driver.
 */

#include "smartbuck6.h"

void smartbuck6_cfg_setup ( smartbuck6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK6_DEVICE_ADDRESS_A2A1_00;
}

err_t smartbuck6_init ( smartbuck6_t *ctx, smartbuck6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->on, cfg->on );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck6_default_cfg ( smartbuck6_t *ctx ) 
{
    err_t error_flag = SMARTBUCK6_OK;

    Delay_100ms ( );
    smartbuck6_disable_device ( ctx );
    Delay_1sec ( );
    smartbuck6_enable_device ( ctx );
    Delay_100ms ( );
    if ( SMARTBUCK6_ERROR == smartbuck6_check_com ( ctx ) )
    {
        return SMARTBUCK6_ERROR;
    }
    Delay_100ms ( );
    error_flag |= smartbuck6_enable_buck ( ctx, SMARTBUCK6_BUCK_ALL );
    Delay_100ms ( );
    error_flag |= smartbuck6_clear_status( ctx );
    Delay_100ms ( );

    return error_flag;
}

err_t smartbuck6_write_reg ( smartbuck6_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t smartbuck6_read_reg ( smartbuck6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void smartbuck6_enable_device ( smartbuck6_t *ctx )
{
    digital_out_low ( &ctx->on );
}

void smartbuck6_disable_device ( smartbuck6_t *ctx )
{
    digital_out_high ( &ctx->on );
}

uint8_t smartbuck6_get_pg_pin ( smartbuck6_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t smartbuck6_check_com ( smartbuck6_t *ctx )
{
    uint8_t part_id = 0;
    if ( SMARTBUCK6_OK == smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_PART_ID, &part_id ) )
    {
        if ( SMARTBUCK6_PART_ID == part_id )
        {
            return SMARTBUCK6_OK;
        }
    }
    return SMARTBUCK6_ERROR;
}

err_t smartbuck6_read_status ( smartbuck6_t *ctx, smartbuck6_status_t *status )
{
    err_t error_flag = SMARTBUCK6_OK;
    error_flag |= smartbuck6_read_reg( ctx, SMARTBUCK6_REG_STATUS_0, &status->status_0 );
    error_flag |= smartbuck6_read_reg( ctx, SMARTBUCK6_REG_STATUS_1, &status->status_1 );
    error_flag |= smartbuck6_read_reg( ctx, SMARTBUCK6_REG_OC_STATUS_CLEAR, &status->oc_status );
    return error_flag;
}

err_t smartbuck6_clear_status ( smartbuck6_t *ctx )
{
    err_t error_flag = SMARTBUCK6_OK;
    error_flag |= smartbuck6_write_reg( ctx, SMARTBUCK6_REG_CLEAR_0, SMARTBUCK6_CLEAR_0_GLOBAL );
    error_flag |= smartbuck6_write_reg( ctx, SMARTBUCK6_REG_OC_STATUS_CLEAR, SMARTBUCK6_OC_STATUS_CLEAR_BUCK_A_OC | 
                                                                             SMARTBUCK6_OC_STATUS_CLEAR_BUCK_B_OC | 
                                                                             SMARTBUCK6_OC_STATUS_CLEAR_BUCK_C_OC );
    return error_flag;
}

err_t smartbuck6_enable_buck ( smartbuck6_t *ctx, uint8_t buck_sel )
{
    err_t error_flag = SMARTBUCK6_OK;
    uint8_t buckx_ctrl = 0;
    if ( ( !buck_sel ) || ( buck_sel > SMARTBUCK6_BUCK_ALL ) )
    {
        return SMARTBUCK6_ERROR;
    }
    error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_BUCKX_CTRL, &buckx_ctrl );
    if ( SMARTBUCK6_OK == error_flag )
    {
        buckx_ctrl |= ( ( buck_sel << 5 ) & SMARTBUCK6_BUCKX_CTRL_BUCK_X_EN_MASK );
        error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_BUCKX_CTRL, buckx_ctrl );
    }
    return error_flag;
}

err_t smartbuck6_disable_buck ( smartbuck6_t *ctx, uint8_t buck_sel )
{
    err_t error_flag = SMARTBUCK6_OK;
    uint8_t buckx_ctrl = 0;
    if ( ( !buck_sel ) || ( buck_sel > SMARTBUCK6_BUCK_ALL ) )
    {
        return SMARTBUCK6_ERROR;
    }
    error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_BUCKX_CTRL, &buckx_ctrl );
    if ( SMARTBUCK6_OK == error_flag )
    {
        buckx_ctrl &= ( ~( ( buck_sel << 5 ) & SMARTBUCK6_BUCKX_CTRL_BUCK_X_EN_MASK ) );
        error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_BUCKX_CTRL, buckx_ctrl );
    }
    return error_flag;
}

err_t smartbuck6_set_buck_vout ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t vout_mv )
{
    err_t error_flag = SMARTBUCK6_OK;
    uint8_t vout_range_sel = 0;
    uint8_t vout = ( vout_mv - SMARTBUCK6_VOUT_MV_MIN ) / SMARTBUCK6_VOUT_MV_STEP_10MV;
    if ( ( !buck_sel ) || 
         ( buck_sel > SMARTBUCK6_BUCK_ALL ) || 
         ( vout_mv < SMARTBUCK6_VOUT_MV_MIN ) || 
         ( vout_mv > SMARTBUCK6_VOUT_MV_MAX ) )
    {
        return SMARTBUCK6_ERROR;
    }
    if ( vout_mv > SMARTBUCK6_VOUT_MV_STEP_THRESHOLD )
    {
        vout = ( vout_mv - SMARTBUCK6_VOUT_MV_STEP_THRESHOLD ) / SMARTBUCK6_VOUT_MV_STEP_15MV;
    }

    error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_VOUT_RANGE_SEL, &vout_range_sel );
    if ( SMARTBUCK6_OK == error_flag )
    {
        if ( ( vout_mv > SMARTBUCK6_VOUT_MV_STEP_THRESHOLD ) && 
             ( ( buck_sel << 1 ) != ( vout_range_sel & ( buck_sel << 1 ) ) ) )
        {
            vout_range_sel |= ( buck_sel << 1 );
            error_flag |= smartbuck6_disable_buck ( ctx, buck_sel );
            Delay_100ms ( );
            error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_VOUT_RANGE_SEL, vout_range_sel );
            Delay_100ms ( );
            error_flag |= smartbuck6_enable_buck ( ctx, buck_sel );
        }
        else if ( ( vout_mv <= SMARTBUCK6_VOUT_MV_STEP_THRESHOLD ) && 
                  ( vout_range_sel & ( buck_sel << 1 ) ) )
        {
            vout_range_sel &= ( ~( buck_sel << 1 ) );
            error_flag |= smartbuck6_disable_buck ( ctx, buck_sel );
            Delay_100ms ( );
            error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_VOUT_RANGE_SEL, vout_range_sel );
            Delay_100ms ( );
            error_flag |= smartbuck6_enable_buck ( ctx, buck_sel );
        }
    }

    if ( ( SMARTBUCK6_OK == error_flag ) && ( buck_sel & SMARTBUCK6_BUCK_A ) )
    {
        error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_BUCK_A_VOUT, vout );
    }
    
    if ( ( SMARTBUCK6_OK == error_flag ) && ( buck_sel & SMARTBUCK6_BUCK_B ) )
    {
        error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_BUCK_B_VOUT, vout );
    }
    
    if ( ( SMARTBUCK6_OK == error_flag ) && ( buck_sel & SMARTBUCK6_BUCK_C ) )
    {
        error_flag |= smartbuck6_write_reg ( ctx, SMARTBUCK6_REG_BUCK_C_VOUT, vout );
    }
    return error_flag;
}

err_t smartbuck6_read_buck_current ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t *current_ma )
{
    err_t error_flag = SMARTBUCK6_OK;
    uint8_t reg_data = 0;
    if ( ( !buck_sel ) || ( buck_sel > SMARTBUCK6_BUCK_ALL ) )
    {
        return SMARTBUCK6_ERROR;
    }
    if ( buck_sel & SMARTBUCK6_BUCK_A )
    {
        error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_BUCK_A_CURR_PWR_METER, &reg_data );
    }
    else if ( buck_sel & SMARTBUCK6_BUCK_B )
    {
        error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_BUCK_B_CURR_PWR_METER, &reg_data );
    }
    else
    {
        error_flag |= smartbuck6_read_reg ( ctx, SMARTBUCK6_REG_BUCK_C_CURR_PWR_METER, &reg_data );
    }
    if ( SMARTBUCK6_OK == error_flag )
    {
        *current_ma = ( uint16_t ) reg_data * SMARTBUCK6_IOUT_RES_MV;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
