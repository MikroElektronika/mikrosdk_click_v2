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

#include "canfd.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void canfd_cfg_setup ( canfd_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->stb = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->wke = HAL_PIN_NC;
    cfg->err = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

CANFD_RETVAL canfd_init ( canfd_t *ctx, canfd_cfg_t *cfg )
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

    digital_out_init( &ctx->stb, cfg->stb );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->wke, cfg->wke );
    digital_in_init( &ctx->err, cfg->err );

    return CANFD_OK;
}

void canfd_set_wke_pin ( canfd_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wke, state );
}

void canfd_set_stb_pin ( canfd_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->stb, state );
}

uint8_t canfd_get_err_pin ( canfd_t *ctx )
{
    return digital_in_read( &ctx->err );
}

void canfd_set_stand_by_stb_pin ( canfd_t *ctx, uint8_t stb_state )
{
    if ( stb_state == CANFD_PIN_STATE_ENABLE )
    {
        digital_out_high( &ctx->stb );
    }
    else if ( stb_state == CANFD_PIN_STATE_DISABLE )
    {
        digital_out_low( &ctx->stb );
    }
}

void canfd_set_mode_en_pin ( canfd_t *ctx, uint8_t en_state )
{
    if ( en_state == CANFD_PIN_STATE_ENABLE )
    {
        digital_out_high( &ctx->en );
    }
    else if ( en_state == CANFD_PIN_STATE_DISABLE )
    {
        digital_out_low( &ctx->en );
    }
}

void canfd_generic_write ( canfd_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t canfd_generic_read ( canfd_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void canfd_set_operating_mode ( canfd_t *ctx, uint8_t op_mode )
{
    switch ( op_mode )
    {
        case CANFD_OPERATING_MODE_NORMAL:
        {
            canfd_set_mode_en_pin( ctx, CANFD_PIN_STATE_ENABLE );      // CS  - 1
            canfd_set_stand_by_stb_pin( ctx, CANFD_PIN_STATE_ENABLE );  // RST - 1
            break;
        }
        case CANFD_OPERATING_MODE_RECEIVE:
        {
            canfd_set_mode_en_pin( ctx, CANFD_PIN_STATE_DISABLE );     // CS  - 0
            canfd_set_stand_by_stb_pin( ctx, CANFD_PIN_STATE_ENABLE );  // RST - 1
            break;
        }
        case CANFD_OPERATING_MODE_STAND_BY:
        {
            canfd_set_mode_en_pin( ctx, CANFD_PIN_STATE_DISABLE );     // CS  - 0
            canfd_set_stand_by_stb_pin( ctx, CANFD_PIN_STATE_DISABLE ); // RST - 0
            break;
        }
        case CANFD_OPERATING_MODE_SLEEP:
        {
            canfd_set_mode_en_pin( ctx, CANFD_PIN_STATE_ENABLE );      // CS  - 1
            canfd_set_stand_by_stb_pin( ctx, CANFD_PIN_STATE_DISABLE ); // RST - 0
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

