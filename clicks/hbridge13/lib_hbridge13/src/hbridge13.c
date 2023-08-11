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
 * @file hbridge13.c
 * @brief H-Bridge 13 Click Driver.
 */

#include "hbridge13.h"

void hbridge13_cfg_setup ( hbridge13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->dev_pwm_freq = HBRIDGE13_DEF_FREQ;
    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD;
    cfg->vref         = HBRIDGE13_VREF_3V3;
    cfg->i2c_address  = HBRIDGE13_DEVICE_ADDRESS_A1A0_00;
}

err_t hbridge13_init ( hbridge13_t *ctx, hbridge13_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;
    pwm_config_t pwm_cfg;

    i2c_master_configure_default( &i2c_cfg );
    pwm_configure_default( &pwm_cfg );
    
    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    
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
    
    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }
    
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t hbridge13_default_cfg ( hbridge13_t *ctx ) 
{
    err_t error_flag = HBRIDGE13_OK;
    
    digital_out_high( &ctx->rst );
    
    error_flag |= hbridge13_write_reg( ctx, HBRIDGE13_REG_CONFIG, HBRIDGE13_FLT_PIN );
    error_flag |= hbridge13_set_pins( ctx, HBRIDGE13_NONE_PIN, HBRIDGE13_ALL_PIN );
    
    error_flag |= hbridge13_set_duty_cycle ( ctx, 0 );
    error_flag |= hbridge13_pwm_start( ctx );

    return error_flag;
}

err_t hbridge13_generic_write ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t hbridge13_generic_read ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t hbridge13_write_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return hbridge13_generic_write( ctx, reg, &data_in, 1 );
}

err_t hbridge13_read_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t hbridge13_set_pins ( hbridge13_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in = 0; 
    uint8_t data_out = 0;
    
    err_t error_flag = hbridge13_read_reg( ctx, HBRIDGE13_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    
    if ( data_out != data_in )
    {
        error_flag |= hbridge13_write_reg( ctx, HBRIDGE13_REG_OUTPUT_PORT, data_in );
    }
    
    return error_flag;
}

err_t hbridge13_set_duty_cycle ( hbridge13_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t hbridge13_pwm_stop ( hbridge13_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t hbridge13_pwm_start ( hbridge13_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t hbridge13_set_brake ( hbridge13_t *ctx ) 
{
    err_t error_flag = HBRIDGE13_OK;
    uint8_t set_pins = 0;
    uint8_t clr_pins = 0;
    
    set_pins = HBRIDGE13_AIN1_IO_PIN | HBRIDGE13_AIN2_IO_PIN | 
               HBRIDGE13_BIN1_IO_PIN | HBRIDGE13_BIN2_IO_PIN;
    clr_pins = HBRIDGE13_PWM_SW1_PIN | HBRIDGE13_PWM_SW2_PIN;
    
    error_flag = hbridge13_set_pins( ctx, set_pins, clr_pins );
    
    return error_flag;
}

err_t hbridge13_set_coast ( hbridge13_t *ctx ) 
{
    err_t error_flag = HBRIDGE13_OK;
    uint8_t clr_pins = 0;
    
    clr_pins = HBRIDGE13_PWM_SW1_PIN | HBRIDGE13_PWM_SW2_PIN | HBRIDGE13_AIN1_IO_PIN | 
               HBRIDGE13_AIN2_IO_PIN | HBRIDGE13_BIN1_IO_PIN | HBRIDGE13_BIN2_IO_PIN;
    
    error_flag = hbridge13_set_pins( ctx, HBRIDGE13_NONE_PIN, clr_pins );
    
    return error_flag;
}

err_t hbridge13_set_direction ( hbridge13_t *ctx, uint8_t dir_set, uint8_t speed )
{
    err_t error_flag = HBRIDGE13_OK;
    uint8_t set_pins = 0;
    uint8_t clr_pins = 0;
    
    if ( 100 < speed )
    {
        return HBRIDGE13_ERROR;
    }
    
    error_flag |= hbridge13_set_duty_cycle ( ctx, ( ( float ) speed / 100 ) );
    
    if ( HBRIDGE13_DIR_FORWARD == dir_set )
    {
        set_pins = HBRIDGE13_PWM_SW1_PIN;
        clr_pins = HBRIDGE13_AIN1_IO_PIN | HBRIDGE13_AIN2_IO_PIN | HBRIDGE13_BIN1_IO_PIN | 
                   HBRIDGE13_BIN2_IO_PIN | HBRIDGE13_PWM_SW2_PIN;
    }
    else
    {
        set_pins = HBRIDGE13_PWM_SW2_PIN;
        clr_pins = HBRIDGE13_AIN1_IO_PIN | HBRIDGE13_AIN2_IO_PIN | HBRIDGE13_BIN1_IO_PIN | 
                   HBRIDGE13_BIN2_IO_PIN | HBRIDGE13_PWM_SW1_PIN;
    }
    
    error_flag |= hbridge13_set_pins( ctx, set_pins, clr_pins );
    
    return error_flag;
}

err_t hbridge13_read_raw_adc ( hbridge13_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t hbridge13_read_voltage ( hbridge13_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t hbridge13_set_vref ( hbridge13_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t hbridge13_get_an_voltage ( hbridge13_t *ctx, float *voltage, uint8_t an_sel )
{
    err_t error_flag = HBRIDGE13_OK;
    
    if ( HBRIDGE13_AN_A_PIN_SEL == an_sel )
    {
        error_flag |= hbridge13_set_pins( ctx, HBRIDGE13_AN_SW_PIN, HBRIDGE13_NONE_PIN );
        error_flag |= hbridge13_read_voltage( ctx, voltage );
    }
    else
    {
        error_flag |= hbridge13_set_pins( ctx, HBRIDGE13_NONE_PIN, HBRIDGE13_AN_SW_PIN );
        error_flag |= hbridge13_read_voltage( ctx, voltage );
    }
    
    return error_flag;
}

err_t hbridge13_get_flt_state ( hbridge13_t *ctx, uint8_t *pin_state )
{
    err_t error_flag = HBRIDGE13_OK;
    uint8_t tmp_data = 0;
    
    error_flag |= hbridge13_read_reg( ctx, HBRIDGE13_REG_INPUT_PORT, &tmp_data );
    
    *pin_state = ( tmp_data & HBRIDGE13_FLT_PIN ) >> 7;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
