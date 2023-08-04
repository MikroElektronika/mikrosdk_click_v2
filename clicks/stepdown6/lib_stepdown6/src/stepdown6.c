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
 * @file stepdown6.c
 * @brief Step Down 6 Click Driver.
 */

#include "stepdown6.h"

void stepdown6_cfg_setup ( stepdown6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN6_DEVICE_ADDRESS;
}

err_t stepdown6_init ( stepdown6_t *ctx, stepdown6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown6_default_cfg ( stepdown6_t *ctx ) 
{
    err_t error_flag = STEPDOWN6_OK;
    
    stepdown6_set_en_pin( ctx, STEPDOWN6_PIN_STATE_HIGH );
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK1_CTRL1, STEPDOWN6_SOFT_START_DLY_0_MS | 
                                                                       STEPDOWN6_SOFT_START_CFG0 );
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK1_CTRL2, STEPDOWN6_VOUT_LIMIT_I2C_EN | 
                                                                       STEPDOWN6_MODE_AUTO_PWM | 
                                                                       STEPDOWN6_CURRENT_LIM_4A | 
                                                                       STEPDOWN6_PH_DELAY_0 );
    
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK2_CTRL1, STEPDOWN6_SOFT_START_DLY_0_MS | 
                                                                       STEPDOWN6_SOFT_START_CFG0 );
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK2_CTRL2, STEPDOWN6_VOUT_LIMIT_I2C_EN | 
                                                                       STEPDOWN6_MODE_AUTO_PWM | 
                                                                       STEPDOWN6_CURRENT_LIM_4A | 
                                                                       STEPDOWN6_PH_DELAY_0 );
    
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK3_CTRL1, STEPDOWN6_SOFT_START_DLY_0_MS | 
                                                                       STEPDOWN6_SOFT_START_CFG0 );
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK3_CTRL2, STEPDOWN6_VOUT_LIMIT_I2C_EN | 
                                                                       STEPDOWN6_MODE_AUTO_PWM | 
                                                                       STEPDOWN6_CURRENT_LIM_4A | 
                                                                       STEPDOWN6_PH_DELAY_0 );
    
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK4_CTRL1, STEPDOWN6_SOFT_START_DLY_0_MS | 
                                                                       STEPDOWN6_SOFT_START_CFG0 );
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK4_CTRL2, STEPDOWN6_VOUT_LIMIT_I2C_EN | 
                                                                       STEPDOWN6_MODE_AUTO_PWM | 
                                                                       STEPDOWN6_CURRENT_LIM_4A | 
                                                                       STEPDOWN6_PH_DELAY_0 );
    
    error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_SYSTEM_CTRL1, STEPDOWN6_EN1_OUTPUT | 
                                                                        STEPDOWN6_EN2_OUTPUT | 
                                                                        STEPDOWN6_EN3_OUTPUT | 
                                                                        STEPDOWN6_EN4_OUTPUT | 
                                                                        STEPDOWN6_UVLO_TH_3V5 );
    
    error_flag |= stepdown6_set_out_voltage( ctx, STEPDOWN6_SELECT_VOUT1, STEPDOWN6_MIN_VOUT_VAL );
    error_flag |= stepdown6_set_out_voltage( ctx, STEPDOWN6_SELECT_VOUT2, STEPDOWN6_MIN_VOUT_VAL );
    error_flag |= stepdown6_set_out_voltage( ctx, STEPDOWN6_SELECT_VOUT3, STEPDOWN6_MIN_VOUT_VAL );
    error_flag |= stepdown6_set_out_voltage( ctx, STEPDOWN6_SELECT_VOUT4, STEPDOWN6_MIN_VOUT_VAL );
    
    return error_flag;
}

err_t stepdown6_generic_write ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepdown6_generic_read ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void stepdown6_set_en_pin ( stepdown6_t *ctx, uint8_t pin_state )
{
    if ( STEPDOWN6_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

err_t stepdown6_write_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t data_in )
{
    return stepdown6_generic_write( ctx, reg, &data_in, 1 );
}

err_t stepdown6_read_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return stepdown6_generic_read( ctx, reg, data_out, 1 );
}


err_t stepdown6_set_out_voltage ( stepdown6_t *ctx, uint8_t out_sel, uint16_t out_val )
{
    uint8_t out_data = 0;
    err_t error_flag = STEPDOWN6_OK;
    if ( ( STEPDOWN6_MIN_VOUT_VAL > out_val ) || ( STEPDOWN6_MAX_VOUT_VAL < out_val ) )
    {
        return STEPDOWN6_ERROR;
    }
    out_data = ( uint8_t )( ( out_val - STEPDOWN6_MIN_VOUT_VAL ) / STEPDOWN6_INCREMENT_VOUT_VAL );
    
    switch ( out_sel )
    {
        case STEPDOWN6_SELECT_VOUT1:
        {
            error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK1_CTRL3, out_data );
            break;
        }
        case STEPDOWN6_SELECT_VOUT2:
        {
            error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK2_CTRL3, out_data );
            break;
        }
        case STEPDOWN6_SELECT_VOUT3:
        {
            error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK3_CTRL3, out_data );
            break;
        }
        case STEPDOWN6_SELECT_VOUT4:
        {
            error_flag |= stepdown6_write_reg( ctx, STEPDOWN6_REG_BUCK4_CTRL3, out_data );
            break;
        }
        default:
        {
            error_flag = STEPDOWN6_ERROR;
            break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
