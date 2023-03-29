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
 * @file leddriver12.c
 * @brief LED Driver 12 Click Driver.
 */

#include "leddriver12.h"

void leddriver12_cfg_setup ( leddriver12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDDRIVER12_DEV_ADDR_A2A1A0_111;
}

err_t leddriver12_init ( leddriver12_t *ctx, leddriver12_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

err_t leddriver12_default_cfg ( leddriver12_t *ctx ) 
{
    err_t error_flag = LEDDRIVER12_OK;
    
    leddriver12_set_rst_pin ( ctx, 1 );
    Delay_100ms( );
    
    error_flag |= leddriver12_set_blink_period_pwm_0 ( ctx, LEDDRIVER12_BLINK_PERIOD_ONE_SECOND );
    error_flag |= leddriver12_set_duty_cycle_pwm_0 ( ctx, LEDDRIVER12_DUTY_CYCLE_HALF );
    error_flag |= leddriver12_set_blink_period_pwm_1 ( ctx, LEDDRIVER12_BLINK_PERIOD_HALF_SECOND );
    error_flag |= leddriver12_set_duty_cycle_pwm_1 ( ctx, LEDDRIVER12_DUTY_CYCLE_QUARTER );
    error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED0_TO_3, LEDDRIVER12_LED_OFF );
    error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED4_TO_7, LEDDRIVER12_LED_OFF );
    error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED8_TO_11, LEDDRIVER12_LED_PWM0 );
    error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED12_TO_15, LEDDRIVER12_LED_PWM1 );

    return error_flag;
}

err_t leddriver12_generic_write ( leddriver12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    if ( ( tx_len > LEDDRIVER12_REG_LS3 ) ||  
         ( reg < LEDDRIVER12_REG_PSC0 ) ||
         ( ( reg & ~LEDDRIVER12_AUTO_INCREMENT_BIT ) > LEDDRIVER12_REG_LS3 ) )
    {
        return LEDDRIVER12_ERROR;
    }
    uint8_t data_buf[ 10 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t leddriver12_generic_read ( leddriver12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t leddriver12_write_register ( leddriver12_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return leddriver12_generic_write( ctx, reg, &data_in, 1 );
}

err_t leddriver12_read_register ( leddriver12_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return leddriver12_generic_read( ctx, reg, data_out, 1 );
}

void leddriver12_set_rst_pin ( leddriver12_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

err_t leddriver12_set_led_config ( leddriver12_t *ctx, uint8_t led_number, uint8_t led_cfg )
{
    if ( ( led_cfg > LEDDRIVER12_LED_PWM1 ) ||
         ( ( led_number > LEDDRIVER12_LED15 ) && ( LEDDRIVER12_ALL_LEDS != led_number ) ) )
    {
        return LEDDRIVER12_ERROR;
    }
    if ( LEDDRIVER12_ALL_LEDS == led_number )
    {
        err_t error_flag = leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED0_TO_3, led_cfg );
        error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED4_TO_7, led_cfg );
        error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED8_TO_11, led_cfg );
        error_flag |= leddriver12_set_led_port_config ( ctx, LEDDRIVER12_LED12_TO_15, led_cfg );
        return error_flag;
    }
    uint8_t port_cfg = 0;
    uint8_t port_reg = LEDDRIVER12_REG_LS0 + ( led_number / 4 );
    err_t error_flag = leddriver12_read_register ( ctx, port_reg, &port_cfg );
    port_cfg &= ~( LEDDRIVER12_LED_PWM1 << ( ( led_number % 4 ) * 2 ) );
    port_cfg |= ( led_cfg << ( ( led_number % 4 ) * 2 ) );
    error_flag |= leddriver12_write_register ( ctx, port_reg, port_cfg );
    return error_flag;
}

err_t leddriver12_set_led_port_config ( leddriver12_t *ctx, uint8_t led_port_number, uint8_t led_cfg )
{
    if ( ( led_cfg > LEDDRIVER12_LED_PWM1 ) ||
         ( led_port_number > LEDDRIVER12_LED12_TO_15 ) )
    {
        return LEDDRIVER12_ERROR;
    }
    uint8_t port_cfg = led_cfg;
    port_cfg |= ( led_cfg << 2 );
    port_cfg |= ( led_cfg << 4 );
    port_cfg |= ( led_cfg << 6 );
    return leddriver12_write_register ( ctx, LEDDRIVER12_REG_LS0 + led_port_number, port_cfg );
}

err_t leddriver12_read_input_0 ( leddriver12_t *ctx, uint8_t *data_out )
{
    return leddriver12_read_register ( ctx, LEDDRIVER12_REG_INPUT0, data_out );
}

err_t leddriver12_read_input_1 ( leddriver12_t *ctx, uint8_t *data_out )
{
    return leddriver12_read_register ( ctx, LEDDRIVER12_REG_INPUT1, data_out );
}

err_t leddriver12_set_blink_period_pwm_0 ( leddriver12_t *ctx, float blink_period )
{
    if ( ( blink_period > LEDDRIVER12_BLINK_PERIOD_MAX ) || 
         ( blink_period < LEDDRIVER12_BLINK_PERIOD_MIN ) )
    {
        return LEDDRIVER12_ERROR;
    }
    uint8_t data_in = ( uint8_t ) ( ( blink_period * 152 ) - 1 );
    return leddriver12_write_register ( ctx, LEDDRIVER12_REG_PSC0, data_in );
}

err_t leddriver12_set_blink_period_pwm_1 ( leddriver12_t *ctx, float blink_period )
{
    if ( ( blink_period > LEDDRIVER12_BLINK_PERIOD_MAX ) || 
         ( blink_period < LEDDRIVER12_BLINK_PERIOD_MIN ) )
    {
        return LEDDRIVER12_ERROR;
    }
    uint8_t data_in = ( uint8_t ) ( ( blink_period * 152 ) - 1 );
    return leddriver12_write_register ( ctx, LEDDRIVER12_REG_PSC1, data_in );
}

err_t leddriver12_set_duty_cycle_pwm_0 ( leddriver12_t *ctx, uint8_t duty_cycle )
{
    return leddriver12_write_register ( ctx, LEDDRIVER12_REG_PWM0, duty_cycle );
}

err_t leddriver12_set_duty_cycle_pwm_1 ( leddriver12_t *ctx, uint8_t duty_cycle )
{
    return leddriver12_write_register ( ctx, LEDDRIVER12_REG_PWM1, duty_cycle );
}

// ------------------------------------------------------------------------- END
