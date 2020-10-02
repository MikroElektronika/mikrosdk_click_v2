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

#include "canfd5.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void canfd5_cfg_setup ( canfd5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

CANFD5_RETVAL canfd5_init ( canfd5_t *ctx, canfd5_cfg_t *cfg )
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

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return CANFD5_OK;
}

void canfd5_generic_write ( canfd5_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t canfd5_generic_read ( canfd5_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void canfd5_set_slp_pin_state ( canfd5_t *ctx, uint8_t slp_state )
{
    if ( slp_state == CANFD5_PIN_STATE_ENABLE )
    {
        digital_out_high( &ctx->pwm );
    }
    else
    {
        digital_out_low( &ctx->pwm );
    }
}

void canfd5_set_wak_pin_state ( canfd5_t *ctx, uint8_t wak_state )
{
    if ( wak_state == CANFD5_PIN_STATE_ENABLE )
    {
        digital_out_high( &ctx->cs );
    }
    else
    {
        digital_out_low( &ctx->cs );
    }
}

uint8_t canfd5_get_cts_pin_state ( canfd5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void canfd5_set_normal_operating_mode ( canfd5_t *ctx )
{
    canfd5_set_slp_pin_state( ctx, CANFD5_PIN_STATE_ENABLE );
    canfd5_set_wak_pin_state( ctx, CANFD5_PIN_STATE_ENABLE );
}

void canfd5_set_standby_operating_mode ( canfd5_t *ctx )
{
    canfd5_set_slp_pin_state( ctx, CANFD5_PIN_STATE_DISABLE );
    canfd5_set_wak_pin_state( ctx, CANFD5_PIN_STATE_ENABLE );
}

void canfd5_set_sleep_operating_mode ( canfd5_t *ctx )
{
    canfd5_set_slp_pin_state( ctx, CANFD5_PIN_STATE_DISABLE );
    canfd5_set_wak_pin_state( ctx, CANFD5_PIN_STATE_DISABLE );
}

void canfd5_set_operating_mode ( canfd5_t *ctx, uint8_t op_mode )
{
    switch ( op_mode )
    {
        case CANFD5_OPERATING_MODE_NORMAL:
        {
            canfd5_set_normal_operating_mode( ctx );
            break;
        }
        case CANFD5_OPERATING_MODE_STAND_BY:
        {
            canfd5_set_standby_operating_mode( ctx );
            break;
        }
        case CANFD5_OPERATING_MODE_SLEEP:
        {
            canfd5_set_sleep_operating_mode( ctx );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

