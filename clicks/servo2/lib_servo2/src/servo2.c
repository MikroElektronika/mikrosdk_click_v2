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
 * @file servo2.c
 * @brief Servo 2 Click Driver.
 */

#include "servo2.h"

void servo2_cfg_setup ( servo2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->sclk = HAL_PIN_NC;
    cfg->sout = HAL_PIN_NC;
    cfg->sin = HAL_PIN_NC;
    cfg->xlat = HAL_PIN_NC;
    cfg->gsclk = HAL_PIN_NC;

    // Additional gpio pins
    cfg->blank = HAL_PIN_NC;
    cfg->xerr = HAL_PIN_NC;

    cfg->dev_pwm_freq = SERVO2_DEF_FREQ;
}

err_t servo2_init ( servo2_t *ctx, servo2_cfg_t *cfg ) 
{
    digital_out_init( &ctx->sclk, cfg->sclk );
    digital_out_init( &ctx->sin, cfg->sin );
    digital_out_init( &ctx->blank, cfg->blank );
    digital_out_init( &ctx->xlat, cfg->xlat );
    digital_out_low ( &ctx->blank );
    digital_out_low ( &ctx->xlat );
    digital_out_low ( &ctx->sclk );
    digital_out_low ( &ctx->sin );

    digital_in_init( &ctx->sout, cfg->sout );
    digital_in_init( &ctx->xerr, cfg->xerr );
    Delay_100ms ( );

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->gsclk;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    Delay_100ms ( );
    pwm_set_duty( &ctx->pwm, SERVO2_DEF_DC );

    return SERVO2_OK;
}

err_t servo2_set_duty_cycle ( servo2_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t servo2_pwm_stop ( servo2_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t servo2_pwm_start ( servo2_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void servo2_write_data ( servo2_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    uint16_t pulse_cnt = 0;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;

    // Clocking in data to serial interface
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( data_in[ byte_cnt ] & ( 0x80 >> bit_cnt ) )
            {
                digital_out_high ( &ctx->sin );
            }
            else
            {
                digital_out_low ( &ctx->sin );
            }
            Delay_10us ( );
            digital_out_high ( &ctx->sclk );
            Delay_10us ( );
            digital_out_low ( &ctx->sclk );
        }
    }
    // Latching data to internal registers
    Delay_10us ( );
    digital_out_high ( &ctx->xlat );
    Delay_10us ( );
    digital_out_low ( &ctx->xlat );
    Delay_10us ( );
    
    // Adding extra clock pulse
    digital_out_high ( &ctx->sclk );
    Delay_10us ( );
    digital_out_low ( &ctx->sclk );
    Delay_10us ( );
    
    // Start PWM to clock out grayscale data
    pwm_start( &ctx->pwm );
    Delay_10ms ( );
    Delay_5ms ( );
    Delay_1ms ( );
    Delay_80us ( );

    // Stop PWM and blank data
    digital_out_high ( &ctx->blank );
    Delay_10us ( );
    digital_out_low ( &ctx->blank );
    Delay_10us ( );
    pwm_stop( &ctx->pwm );
}

void servo2_set_sclk_pin ( servo2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sclk, state );
}

void servo2_set_sin_pin ( servo2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sin, state );
}

void servo2_set_xlat_pin ( servo2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->xlat, state );
}

void servo2_set_blank_pin ( servo2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->blank, state );
}

uint8_t servo2_get_sout_pin ( servo2_t *ctx )
{
    return digital_in_read ( &ctx->sout );
}

uint8_t servo2_get_xerr_pin ( servo2_t *ctx )
{
    return digital_in_read ( &ctx->xerr );
}

err_t servo2_set_channel_pwm ( servo2_t *ctx, uint8_t ch_num, uint16_t pwm_out )
{
    uint8_t ch_cnt = 0;
    if ( ( ch_num > SERVO2_CHANNEL_ALL ) || ( pwm_out > SERVO2_PWM_MAX ) )
    {
        return SERVO2_ERROR;
    }
    if ( SERVO2_CHANNEL_ALL == ch_num )
    {
        for ( ch_cnt = SERVO2_CHANNEL_0; ch_cnt <= SERVO2_CHANNEL_15; ch_cnt++ )
        {
            ctx->pwm_out[ ch_cnt ] = pwm_out;
        }
    }
    else
    {
        ctx->pwm_out[ SERVO2_CHANNEL_15 - ch_num ] = pwm_out;
    }
    return SERVO2_OK;
}

err_t servo2_set_angle ( servo2_t *ctx, uint8_t ch_num, uint8_t angle )
{
    uint16_t pwm_out = 0;
    if ( ( ch_num > SERVO2_CHANNEL_ALL ) || ( angle > SERVO2_ANGLE_MAX ) )
    {
        return SERVO2_ERROR;
    }
    pwm_out = ( SERVO2_PWM_ZERO_DEGREE_PULSE - SERVO2_PWM_180_DEGREE_PULSE );
    pwm_out *= ( ( float ) angle / SERVO2_ANGLE_MAX );
    pwm_out = SERVO2_PWM_ZERO_DEGREE_PULSE - pwm_out;
    return servo2_set_channel_pwm ( ctx, ch_num, pwm_out );
}

void servo2_update_output ( servo2_t *ctx )
{
    uint8_t data_buf[ ( SERVO2_NUM_CHANNELS * 3 ) / 2 ] = { 0 };
    for ( uint8_t cnt = 0; cnt < ( SERVO2_NUM_CHANNELS / 2 ); cnt++ )
    {
        data_buf[ cnt * 3 ] = ( uint8_t ) ( ( ctx->pwm_out[ cnt * 2 ] & 0x0FF0 ) >> 4 );
        data_buf[ cnt * 3 + 1 ] = ( uint8_t ) ( ( ( ctx->pwm_out[ cnt * 2 ] & 0x000F ) << 4 ) | 
                                                ( ( ctx->pwm_out[ cnt * 2 + 1 ] & 0x0F00 ) >> 8 ) );
        data_buf[ cnt * 3 + 2 ] = ( uint8_t ) ( ctx->pwm_out[ cnt * 2 + 1 ] & 0x00FF );
    }
    servo2_write_data ( ctx, data_buf, ( SERVO2_NUM_CHANNELS * 3 ) / 2 );
}

// ------------------------------------------------------------------------- END
