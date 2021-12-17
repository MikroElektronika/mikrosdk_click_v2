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
 * @file ir.c
 * @brief IR Click Driver.
 */

#include "ir.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief IR dev delay function.
 * @details This function is used for delays of 560 us for transmitting logic 0 
 * and limiting the duration of the pulses.
 */
void dev_space_delay_560us ( void );

/**
 * @brief IR dev delay function.
 * @details This function is used for delays of 1680 us for transmitting logic 1.
 */
void dev_space_delay_1680us ( void );

/**
 * @brief IR dev delay function.
 * @details This function is used for delays of 4500 us for starting of comunicatuion.
 */
void dev_start_delay_4500us ( void );

/**
 * @brief IR dev delay function.
 * @details This function is used for delays of 9000 us for starting of comunicatuion.
 */
void dev_start_delay_9000us ( void );

/**
 * @brief IR dev delay function.
 * @details This function is used for setting up a wait delay of 100 ms for the end of 
 * delay between sending more data.
 */
void dev_wait_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void ir_cfg_setup ( ir_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
    cfg->dev_pwm_freq = IR_DEF_FREQ;
    
    cfg->drv_sel = IR_DRV_SEL_GPIO;
}

void ir_drv_interface_selection ( ir_cfg_t *cfg, ir_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ir_init ( ir_t *ctx, ir_cfg_t *cfg ) 
{
    if ( IR_DRV_SEL_UART == ctx->drv_sel )
    {
        uart_config_t uart_cfg;

        // Default config
        uart_configure_default( &uart_cfg );

        // Ring buffer mapping
        ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
        ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

        // UART module config
        uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
        uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
        uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
        uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

        if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
        {
            return UART_ERROR;
        }
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );
    }
    else
    {
        pwm_config_t pwm_cfg;

        pwm_configure_default( &pwm_cfg );

        pwm_cfg.pin      = cfg->pwm;
        pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

        ctx->pwm_freq = cfg->dev_pwm_freq;

        if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
        {
            return PWM_ERROR;
        }
        pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
        
        pwm_set_duty( &ctx->pwm, 0.25 );
        
        digital_in_init( &ctx->an, cfg->an );
    }    
    return IR_OK;
}

err_t ir_set_duty_cycle ( ir_t *ctx, float duty_cycle ) {
    
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t ir_pwm_stop ( ir_t *ctx ) {
   
    return pwm_stop( &ctx->pwm );
}

err_t ir_pwm_start ( ir_t *ctx ) {
   
    return pwm_start( &ctx->pwm );
}

err_t ir_generic_write ( ir_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ir_generic_read ( ir_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t ir_get_an_state ( ir_t *ctx ) 
{
    if ( digital_in_read( &ctx->an ) == 1 )
    {
        return IR_STATE_HIGH;
    }
    else 
    {
        return IR_STATE_LOW;
    }
}

void ir_nec_send_command ( ir_t *ctx, uint8_t address, uint8_t command )
{
    uint8_t ir_byte[ 4 ];
    
    ir_byte[ 0 ] = address;
    ir_byte[ 1 ] = ~address;
    ir_byte[ 2 ] = command;
    ir_byte[ 3 ] = ~command;                       
    
    pwm_start( &ctx->pwm );                               
    dev_start_delay_9000us( );                           
    pwm_stop( &ctx->pwm );                          
    dev_start_delay_4500us( );        
    
    for( uint8_t bytenum = 0; bytenum < 4; bytenum++)
    {      
        for( uint8_t bitnum = 0; bitnum < 8; bitnum++)
        {    
            pwm_start( &ctx->pwm );                
            dev_space_delay_560us( );             
            pwm_stop( &ctx->pwm ); 
            
            if( ir_byte[ bytenum ] & ( 1 << bitnum ) )
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
    dev_space_delay_560us( );            
    pwm_stop( &ctx->pwm );                
    dev_space_delay_1680us( );  
    
    dev_wait_delay( );     
}


err_t ir_nec_read_command ( ir_t *ctx, uint8_t *address, uint8_t *command )
{
    uint8_t byte_data = 0;
    uint8_t cnt = 0;
    uint8_t rx_buf[ 4 ];
    
    while ( IR_STATE_HIGH == ir_get_an_state( ctx ) );
    
    while ( IR_STATE_LOW == ir_get_an_state( ctx ) );
    
    while ( IR_STATE_HIGH == ir_get_an_state( ctx ) );

    
    for ( uint8_t bytenum = 0; bytenum < 4; bytenum++)
    {
        byte_data = 0;
        for ( uint8_t bitnum = 0; bitnum < 8; bitnum++)
        {
            cnt = 0;
            while ( IR_STATE_LOW == ir_get_an_state( ctx ) );
            
            while ( IR_STATE_HIGH == ir_get_an_state( ctx ) )
            {
                cnt += 1;
                Delay_10us( );
            }

            if ( cnt > 90 )
            {
                byte_data |= ( 1 << bitnum );
            }
        }
        rx_buf[ bytenum ] = byte_data;
    }
    if ( ( rx_buf[ 0 ] == ~rx_buf[ 1 ] ) && ( rx_buf[ 2 ] == ~rx_buf[ 3 ] ) )
    {
        *address = rx_buf[ 0 ];
        *command = rx_buf[ 2 ];
        return IR_OK;
    }
    else
    {
        return IR_ERROR;
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
    Delay_50us( );
    Delay_50us( );
    Delay_80us( );
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
