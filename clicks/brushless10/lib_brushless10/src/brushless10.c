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
 * @file brushless10.c
 * @brief Brushless 10 Click Driver.
 */

#include "brushless10.h"

void brushless10_cfg_setup ( brushless10_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fg_out = HAL_PIN_NC;
    cfg->brake = HAL_PIN_NC;
    cfg->ld_out = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS10_DEF_FREQ;
    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address  = BRUSHLESS10_DAC_DEVICE_ADDRESS_0;
}

err_t brushless10_init ( brushless10_t *ctx, brushless10_cfg_t *cfg )
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

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->brake, cfg->brake );

    // Input pins
    digital_in_init( &ctx->fg_out, cfg->fg_out );
    digital_in_init( &ctx->ld_out, cfg->ld_out );

    return BRUSHLESS10_OK;
}

err_t brushless10_default_cfg ( brushless10_t *ctx )
{
    err_t error_flag = BRUSHLESS10_OK;
    if ( BRUSHLESS10_ERROR == brushless10_dac_check_com ( ctx ) )
    {
        return BRUSHLESS10_ERROR;
    }
    brushless10_pull_brake ( ctx );
    error_flag |= brushless10_dac_sw_reset ( ctx );
    Delay_10ms ( );
    error_flag |= brushless10_dac_write ( ctx, BRUSHLESS10_DAC_REG_DEVICE_CONFIG, 
                                               BRUSHLESS10_DAC_CONFIG_ENABLE_ALL_CH );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHA_LA, BRUSHLESS10_LA0_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHB_MIN_SP, BRUSHLESS10_MIN_SP_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHC_SEL_LD, BRUSHLESS10_SEL_LD_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHD_FPWM, BRUSHLESS10_FPWM_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHE_SEL_LA, BRUSHLESS10_SEL_LA_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHF_SEL_FG, BRUSHLESS10_SEL_FG_STEP_0 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHG_SEL_SP, BRUSHLESS10_SEL_SP_STEP_1 );
    error_flag |= brushless10_dac_set_vout ( ctx, BRUSHLESS10_DAC_CHH_CW_CCW, BRUSHLESS10_CW_CCW_0 );
    error_flag |= brushless10_set_duty_cycle ( ctx, 0.0 );
    error_flag |= brushless10_pwm_start( ctx );
    brushless10_release_brake ( ctx );
    return error_flag;
}

err_t brushless10_dac_write ( brushless10_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t brushless10_dac_read ( brushless10_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t brushless10_set_duty_cycle ( brushless10_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless10_pwm_stop ( brushless10_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless10_pwm_start ( brushless10_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

uint8_t brushless10_get_fg_out_pin ( brushless10_t *ctx )
{
    return digital_in_read ( &ctx->fg_out );
}

uint8_t brushless10_get_ld_out_pin ( brushless10_t *ctx )
{
    return digital_in_read ( &ctx->ld_out );
}

void brushless10_pull_brake ( brushless10_t *ctx )
{
    digital_out_high ( &ctx->brake );
}

void brushless10_release_brake ( brushless10_t *ctx )
{
    digital_out_low ( &ctx->brake );
}

err_t brushless10_dac_check_com ( brushless10_t *ctx )
{
    uint16_t device_id = 0;
    if ( BRUSHLESS10_OK == brushless10_dac_read ( ctx, BRUSHLESS10_DAC_REG_STATUS_TRIGGER, &device_id ) )
    {
        if ( BRUSHLESS10_DAC_DEVICE_ID == ( device_id & BRUSHLESS10_DAC_DEVICE_ID_MASK ) )
        {
            return BRUSHLESS10_OK;
        }
    }
    return BRUSHLESS10_ERROR;
}

err_t brushless10_dac_sw_reset ( brushless10_t *ctx )
{
    return brushless10_dac_write ( ctx, BRUSHLESS10_DAC_REG_STATUS_TRIGGER, BRUSHLESS10_DAC_SW_RESET );
}

err_t brushless10_dac_set_data ( brushless10_t *ctx, uint8_t channel, uint8_t data_in )
{
    if ( channel > BRUSHLESS10_DAC_CHH_CW_CCW )
    {
        return BRUSHLESS10_ERROR;
    }
    uint16_t dac_data = ( uint16_t ) data_in << 4;
    return brushless10_dac_write ( ctx, BRUSHLESS10_DAC_REG_DACA_DATA_LA + channel, dac_data );
}

err_t brushless10_dac_set_vout ( brushless10_t *ctx, uint8_t channel, uint16_t vout_mv )
{
    if ( ( channel > BRUSHLESS10_DAC_CHH_CW_CCW ) || ( vout_mv > BRUSHLESS10_DAC_VREF ) )
    {
        return BRUSHLESS10_ERROR;
    }
    uint16_t dac_data = ( uint16_t ) ( ( float ) vout_mv / BRUSHLESS10_DAC_VREF * 
                                       BRUSHLESS10_DAC_RESOLUTION + BRUSHLESS10_DAC_ROUND_TO_INT ) << 4;
    return brushless10_dac_write ( ctx, BRUSHLESS10_DAC_REG_DACA_DATA_LA + channel, dac_data );
}

// ------------------------------------------------------------------------- END
