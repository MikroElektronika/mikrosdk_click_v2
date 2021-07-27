/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "stspin233.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void command_delay ( void );

static uint8_t drv_strlen ( char *s );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stspin233_cfg_setup ( stspin233_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

STSPIN233_RETVAL stspin233_init ( stspin233_t *ctx, stspin233_cfg_t *cfg )
{
    uart_config_t uart_cfg;

    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return STSPIN233_OK;
}

void stspin233_default_cfg ( stspin233_t *ctx )
{
    stspin233_wakeup( ctx );   
    command_delay( ); 
    stspin233_send_double_cmd( ctx, STSPIN233_CMD_MOTOR_POLE,  STSPIN233_M_POLE_8 );
    command_delay( );
    stspin233_send_double_cmd( ctx, STSPIN233_CMD_SET_PWM, STSPIN233_START_PWM_DUTY_DEF );
    command_delay( );
    stspin233_send_double_cmd( ctx, STSPIN233_CMD_SET_SPEED, STSPIN233_SPEED_DEF );
    command_delay( );
}

void stspin233_generic_write ( stspin233_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t stspin233_generic_read ( stspin233_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void stspin233_wakeup ( stspin233_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

void stspin233_send_single_cmd ( stspin233_t *ctx, uint8_t *tx_buf )
{
    uint8_t cnt;
    uint8_t cmd_len;

    cmd_len = drv_strlen( tx_buf );
    
    stspin233_generic_write( ctx, tx_buf, cmd_len );
    
    stspin233_generic_write( ctx, "\r\n", 2 );
}

void stspin233_send_double_cmd ( stspin233_t *ctx, uint8_t *cmd_buf, uint8_t *arg_buf )
{
    stspin233_send_single_cmd( ctx, cmd_buf );
    command_delay( );
    stspin233_send_single_cmd( ctx, arg_buf );
}

void stspin233_set_reset_state ( stspin233_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t stspin233_get_int_state ( stspin233_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void command_delay ( void )
{
    Delay_100ms( );
}

static uint8_t drv_strlen ( char *s )
{
    char *cp;

    cp = s;
    while ( *cp++ )
    {
        continue;
    }
    return ( cp - s - 1 );
}

// ------------------------------------------------------------------------- END

