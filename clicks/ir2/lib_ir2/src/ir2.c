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
 * @file ir2.c
 * @brief IR 2 Click Driver.
 */

#include "ir2.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief IR 2 dev space delay 560us function.
 * @details This function is used for delays of 560 us for transmitting logic 0 
 * and limiting the duration of the pulses.
 */
void dev_space_delay_560us ( void );

/**
 * @brief IR 2 dev space delay 1680us function.
 * @details This function is used for delays of 1680 us for transmitting logic 1.
 */
void dev_space_delay_1680us ( void );

/**
 * @brief IR 2 dev start delay 4500us function.
 * @details This function is used for delays of 4500 us for starting of communication.
 */
void dev_start_delay_4500us ( void );

/**
 * @brief IR 2 dev start delay 9000us function.
 * @details This function is used for delays of 9000 us for starting of communication.
 */
void dev_start_delay_9000us ( void );

/**
 * @brief IR 2 dev wait delay function.
 * @details This function is used for setting up a wait delay of 100 ms between each data send.
 */
void dev_wait_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void ir2_cfg_setup ( ir2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    cfg->dev_pwm_freq = IR2_DEF_FREQ;
    
    cfg->drv_sel = IR2_DRV_SEL_GPIO;
}

void ir2_drv_interface_selection ( ir2_cfg_t *cfg, ir2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ir2_init ( ir2_t *ctx, ir2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );
    if ( IR2_DRV_SEL_UART == ctx->drv_sel )
    {
        pwm_cfg.pin = cfg->tx_pin;
    }
    else
    {
        pwm_cfg.pin = cfg->pwm;
    }    
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    pwm_set_duty( &ctx->pwm, IR2_DEF_DUTY_CYCLE );
    
    if ( IR2_DRV_SEL_UART == ctx->drv_sel )
    {
        digital_in_init( &ctx->out_pin, cfg->rx_pin );
    }
    else
    {
        digital_in_init( &ctx->out_pin, cfg->int_pin );
    }
    
    return IR2_OK;
}

uint8_t ir2_get_out_pin ( ir2_t *ctx )
{
    return digital_in_read( &ctx->out_pin );
}

void ir2_nec_send_data ( ir2_t *ctx, uint8_t address, uint8_t data_in )
{
    uint8_t ir_byte[ 4 ];
    
    ir_byte[ 0 ] = address;
    ir_byte[ 1 ] = ~address;
    ir_byte[ 2 ] = data_in;
    ir_byte[ 3 ] = ~data_in;

    pwm_start( &ctx->pwm );
    pwm_set_duty( &ctx->pwm, IR2_DEF_DUTY_CYCLE );
    dev_start_delay_9000us( );
    pwm_stop( &ctx->pwm );
    dev_start_delay_4500us( );
    
    for ( uint8_t byte_num = 0; byte_num < 4; byte_num++ )
    {
        for ( uint8_t bit_num = 0; bit_num < 8; bit_num++ )
        {
            pwm_start( &ctx->pwm );
            pwm_set_duty( &ctx->pwm, IR2_DEF_DUTY_CYCLE );
            dev_space_delay_560us( );
            pwm_stop( &ctx->pwm );
            
            if ( ir_byte[ byte_num ] & ( 1 << bit_num ) )
            {
                dev_space_delay_1680us( );
            }
            else
            {
                dev_space_delay_560us( );
            }
        }
    }
    pwm_start( &ctx->pwm );
    pwm_set_duty( &ctx->pwm, IR2_DEF_DUTY_CYCLE );
    dev_space_delay_560us( );
    pwm_stop( &ctx->pwm );
    dev_space_delay_1680us( );
    dev_wait_delay( );
}

err_t ir2_nec_read_data ( ir2_t *ctx, uint8_t *address, uint8_t *data_out )
{
    uint8_t byte_data = 0;
    uint8_t cnt = 0;
    uint8_t rx_buf[ 4 ];
    
    // Wait until OUT pin falls
    while ( IR2_STATE_HIGH == ir2_get_out_pin ( ctx ) );
    
    // Check 9ms pulse (remote control sends logic high)
    while ( ( IR2_STATE_LOW == ir2_get_out_pin ( ctx ) ) && ( cnt < 200 ) )
    {
        Delay_50us ( );
        cnt++;
    }
    if ( ( cnt < 160 ) || ( cnt > 199 ) )
    {
        return IR2_ERROR;
    }
    cnt = 0;
    
    // Check 4.5ms space (remote control sends logic low)
    while ( ( IR2_STATE_HIGH == ir2_get_out_pin ( ctx ) ) && ( cnt < 100 ) )
    {
        Delay_50us ( );
        cnt++;
    }
    if ( ( cnt < 60 ) || ( cnt > 99 ) )
    {
        return IR2_ERROR;
    }
               
    // Read code message (32-bit)
    for ( uint8_t byte_num = 0; byte_num < 4; byte_num++ )
    {
        byte_data = 0;
        for ( uint8_t bit_num = 0; bit_num < 8; bit_num++ )
        {
            cnt = 0;
            while ( IR2_STATE_LOW == ir2_get_out_pin ( ctx ) );
            
            while ( IR2_STATE_HIGH == ir2_get_out_pin ( ctx ) )
            {
                dev_space_delay_560us ( );
                cnt++;            
            }

            if ( cnt > 2 )
            {
                byte_data |= ( 1 << bit_num );
            }
        }
        rx_buf[ byte_num ] = byte_data;
    }
    
    if ( ( rx_buf[ 0 ] == ( ( ~rx_buf[ 1 ] ) & 0xFF ) ) && 
         ( rx_buf[ 2 ] == ( ( ~rx_buf[ 3 ] ) & 0xFF )  ) )
    {
        *address = rx_buf[ 0 ];
        *data_out = rx_buf[ 2 ];
        return IR2_OK;
    }
    else
    {
        return IR2_ERROR;
    }
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_space_delay_560us ( void ) 
{
    Delay_500us( );
    Delay_50us( );
    Delay_10us( );
}

void dev_space_delay_1680us ( void ) 
{
    Delay_1ms( );
    Delay_500us( );
    Delay_80us( );
    Delay_50us( );
    Delay_50us( );
}

void dev_start_delay_4500us ( void )
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_500us( );
}

void dev_start_delay_9000us ( void )
{
    Delay_5ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

void dev_wait_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
