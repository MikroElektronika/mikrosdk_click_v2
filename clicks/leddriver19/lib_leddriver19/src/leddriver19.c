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
 * @file leddriver19.c
 * @brief LED Driver 19 Click Driver.
 */

#include "leddriver19.h"

void leddriver19_cfg_setup ( leddriver19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDDRIVER19_DEVICE_ADDRESS_0;
}

err_t leddriver19_init ( leddriver19_t *ctx, leddriver19_cfg_t *cfg ) 
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

err_t leddriver19_default_cfg ( leddriver19_t *ctx ) 
{
    err_t error_flag = LEDDRIVER19_OK;
    
    error_flag |= leddriver19_sw_reset( ctx );
    error_flag |= leddriver19_write_reg( ctx, LEDDRIVER19_REG_DEVICE_EN, LEDDRIVER19_ENABLE );
    error_flag |= leddriver19_write_reg( ctx, LEDDRIVER19_REG_FAULT_MASK, LEDDRIVER19_OVTP_MASK | 
                                                                          LEDDRIVER19_OPEN_MASK );
    error_flag |= leddriver19_enable_channels( ctx, LEDDRIVER19_CS_ENABLE_ALL );
    
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( ctx, LEDDRIVER19_PATSEL_0, n_cnt, 0  );
    }

    return error_flag;
}

err_t leddriver19_generic_write ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t leddriver19_generic_read ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t leddriver19_get_int_pin ( leddriver19_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t leddriver19_write_reg ( leddriver19_t *ctx, uint8_t reg, uint8_t data_in )
{
    return leddriver19_generic_write( ctx, reg, &data_in, 1 );
}

err_t leddriver19_read_reg ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return leddriver19_generic_read( ctx, reg, data_out, 1 );
}

err_t leddriver19_sw_reset ( leddriver19_t *ctx )
{
    return leddriver19_write_reg( ctx, LEDDRIVER19_REG_DEVICE_EN, LEDDRIVER19_SW_RESET );
}

err_t leddriver19_enable_channels ( leddriver19_t *ctx, uint16_t channels_en )
{
    uint8_t data_in[ 2 ] = { 0 };
    err_t error_flag = LEDDRIVER19_OK;
    
    channels_en &= LEDDRIVER19_CS_ENABLE_ALL;
    
    error_flag |= leddriver19_generic_read( ctx, LEDDRIVER19_REG_CH_EN_LOW, data_in, 2 );
    
    data_in[ 0 ] |= ( uint8_t ) channels_en;
    data_in[ 1 ] |= ( uint8_t ) ( channels_en >> 8 );
    
    error_flag |= leddriver19_generic_write( ctx, LEDDRIVER19_REG_CH_EN_LOW, data_in, 2 );
    
    return error_flag;
}

err_t leddriver19_disable_channels ( leddriver19_t *ctx, uint16_t channels_dis )
{
    uint8_t data_in[ 2 ] = { 0 };
    err_t error_flag = LEDDRIVER19_OK;
    
    channels_dis &= LEDDRIVER19_CS_ENABLE_ALL;
    
    error_flag |= leddriver19_generic_read( ctx, LEDDRIVER19_REG_CH_EN_LOW, data_in, 2 );
    
    data_in[ 0 ] &= ( uint8_t ) ~channels_dis;
    data_in[ 1 ] &= ( uint8_t ) ( ~channels_dis >> 8 );
    
    error_flag |= leddriver19_generic_write( ctx, LEDDRIVER19_REG_CH_EN_LOW, data_in, 2 );
    
    return error_flag;
}

err_t leddriver19_set_pattern_pwm ( leddriver19_t *ctx, uint8_t pattern_sel, uint8_t channel_sel, 
                                    float pwm_value )
{
    uint8_t data_in[ 2 ] = { 0 };
    uint8_t reg = LEDDRIVER19_REG_PWMREG_OFFSET + ( 2 * channel_sel ) + 
                  ( LEDDRIVER19_PATTERN_SEL_OFFSET * pattern_sel );
    uint16_t pwm_val = pwm_value * LEDDRIVER19_PWM_VAL_CONVERSION;
    
    data_in[ 0 ] = ( uint8_t ) pwm_val;
    data_in[ 1 ] = ( uint8_t ) ( pwm_val >> 8 );
    
    return leddriver19_generic_write( ctx, reg, data_in, 2 );
}

err_t leddriver19_get_ch_current ( leddriver19_t *ctx, uint8_t channel_sel, float *current_val )
{
    err_t error_flag = LEDDRIVER19_OK;
    uint8_t tmp_data = 0;
    uint8_t reg = LEDDRIVER19_REG_CUR_LED_CS0 + channel_sel;
    
    error_flag |= leddriver19_read_reg( ctx, reg, &tmp_data );
    
    *current_val = ( float ) tmp_data * LEDDRIVER19_CURRENT_STEP_TO_MA;
    
    return error_flag;
}

err_t leddriver19_set_ch_current ( leddriver19_t *ctx, uint8_t channel_sel, float current_val )
{
    uint8_t tmp_data = 0;
    uint8_t reg = LEDDRIVER19_REG_CUR_LED_CS0 + channel_sel;
    
    tmp_data = current_val * LEDDRIVER19_CURRENT_STEP_TO_HEX;

    return leddriver19_write_reg( ctx, reg, tmp_data );
}

err_t leddriver19_get_int_data ( leddriver19_t *ctx, uint8_t *int_data )
{
    return leddriver19_read_reg( ctx, LEDDRIVER19_REG_FAULT_INT, int_data );
}

err_t leddriver19_get_nc_led ( leddriver19_t *ctx, uint16_t *led_data )
{
    err_t error_flag = LEDDRIVER19_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= leddriver19_generic_read( ctx, LEDDRIVER19_REG_OPEN_LED_LOW, tmp_data, 2 );
    
    *led_data = ( ( uint16_t ) tmp_data[ 1 ] << 8 | tmp_data[ 0 ] );
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
