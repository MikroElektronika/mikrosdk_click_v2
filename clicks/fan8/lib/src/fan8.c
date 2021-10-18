/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file fan8.c
 * @brief FAN 8 Click Driver.
 */

#include "fan8.h"

void fan8_cfg_setup ( fan8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ot   = HAL_PIN_NC;
    cfg->fan_fail = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FAN8_DEV_ADDR_ADD0_GND_ADD1_GND;
}

err_t fan8_init ( fan8_t *ctx, fan8_cfg_t *cfg ) 
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

    digital_in_init( &ctx->ot, cfg->ot );
    digital_in_init( &ctx->fan_fail, cfg->fan_fail );
    digital_in_init( &ctx->fault, cfg->fault );

    return I2C_MASTER_SUCCESS;
}

err_t fan8_default_cfg ( fan8_t *ctx ) 
{
    if ( FAN8_ERROR == fan8_check_device_id ( ctx ) )
    {
        return FAN8_ERROR;
    }

    return fan8_write_register ( ctx, FAN8_REG_DC_ROC, 0 );
}

err_t fan8_write_register ( fan8_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t fan8_read_register ( fan8_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t fan8_check_overtemperature_indicator ( fan8_t *ctx )
{
    return digital_in_read ( &ctx->ot );
}

uint8_t fan8_check_fan_fail_indicator ( fan8_t *ctx )
{
    return digital_in_read ( &ctx->fan_fail );
}

uint8_t fan8_check_fault_indicator ( fan8_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

err_t fan8_check_device_id ( fan8_t *ctx )
{
    uint8_t dev_id = 0;
    if ( FAN8_OK == fan8_read_register ( ctx, FAN8_REG_DEVICE_ID, &dev_id ) )
    {
        if ( FAN8_DEVICE_ID == dev_id )
        {
            return FAN8_OK;
        }
    }
    return FAN8_ERROR;
}

err_t fan8_set_duty_cycle ( fan8_t *ctx, uint8_t fan_ch, uint8_t duty_cycle )
{
    uint8_t output_duty = 0;

    if ( duty_cycle > FAN8_MAX_DUTY_CYCLE )
    {
        duty_cycle = FAN8_MAX_DUTY_CYCLE;
    }

    if ( duty_cycle % 2 )
    {
        duty_cycle--;
    }

    switch ( fan_ch )
    {
        case FAN8_FAN_CHANNEL_1:
        {
            if ( FAN8_ERROR == fan8_write_register ( ctx, FAN8_REG_PWM1_TARGET_DC, duty_cycle  ) )
            {
                return FAN8_ERROR;
            }

            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_PWM1_INSTANTANEOUS_DC, &output_duty ) )
            {
                return FAN8_ERROR;
            }

            while ( output_duty != duty_cycle )
            {
                if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_PWM1_INSTANTANEOUS_DC, &output_duty ) )
                {
                    return FAN8_ERROR;
                }
                Delay_1ms( );
            }
            break;
        }
        case FAN8_FAN_CHANNEL_2:
        {
            if ( FAN8_ERROR == fan8_write_register ( ctx, FAN8_REG_PWM2_TARGET_DC, duty_cycle ) )
            {
                return FAN8_ERROR;
            }

            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_PWM2_INSTANTANEOUS_DC, &output_duty ) )
            {
                return FAN8_ERROR;
            }

            while ( output_duty != duty_cycle )
            {
                if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_PWM2_INSTANTANEOUS_DC, &output_duty ) )
                {
                    return FAN8_ERROR;
                }
                Delay_1ms( );
            }
            break;
        }
        default:
        {
            return FAN8_ERROR;
        }
    }
    return FAN8_OK;
}

err_t fan8_measure_rpm ( fan8_t *ctx, uint8_t fan_ch, uint8_t num_pulses, uint16_t *fan_rpm )
{
    uint8_t tach_reg = 0;

    switch ( fan_ch )
    {
        case FAN8_FAN_CHANNEL_1:
        {
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_TACH1_VALUE, &tach_reg ) )
            {
                return FAN8_ERROR;
            }
            break;
        }
        case FAN8_FAN_CHANNEL_2:
        {
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_TACH2_VALUE, &tach_reg ) )
            {
                return FAN8_ERROR;
            }
            break;
        }
        default:
        {
            return FAN8_ERROR;
        }
    }

    if ( tach_reg != FAN8_MAX_TACH_VALUE )
    {
        *fan_rpm = ( uint16_t ) ( ( ( float ) FAN8_CLOCK_COUNTER_FREQ * FAN8_SEC_PER_MIN ) / 
                                  ( ( uint16_t ) tach_reg * num_pulses ) );
    }
    else
    {
        *fan_rpm = 0;
    }

    return FAN8_OK;
}

err_t fan8_read_temperature ( fan8_t *ctx, uint8_t temp_ch, float *temperature )
{
    uint8_t temp_reg = 0;
    uint8_t temp_lsb = 0;

    switch ( temp_ch )
    {
        case FAN8_TEMP_CHANNEL_1:
        {
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_TEMP_CH1, &temp_reg ) )
            {
                return FAN8_ERROR;
            }
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_CH1_TEMP_LSB, &temp_lsb ) )
            {
                return FAN8_ERROR;
            }
            break;
        }
        case FAN8_TEMP_CHANNEL_2:
        {
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_TEMP_CH2, &temp_reg ) )
            {
                return FAN8_ERROR;
            }
            if ( FAN8_ERROR == fan8_read_register ( ctx, FAN8_REG_CH2_TEMP_LSB, &temp_lsb ) )
            {
                return FAN8_ERROR;
            }
            break;
        }
        default:
        {
            return FAN8_ERROR;
        }
    }

    *temperature = ( ( float ) temp_reg + ( temp_lsb >> 5 ) * FAN8_TEMPERATURE_RESOLUTION );

    return FAN8_OK;
}

err_t fan8_reset ( fan8_t *ctx )
{
    return fan8_write_register ( ctx, FAN8_REG_CONFIG_BYTE, FAN8_RESET );
}

// ------------------------------------------------------------------------- END
