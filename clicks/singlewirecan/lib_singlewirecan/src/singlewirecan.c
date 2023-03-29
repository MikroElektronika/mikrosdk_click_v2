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

#include "singlewirecan.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void singlewirecan_cfg_setup ( singlewirecan_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->md0 = HAL_PIN_NC;
    cfg->md1   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

SINGLEWIRECAN_RETVAL singlewirecan_init ( singlewirecan_t *ctx, singlewirecan_cfg_t *cfg )
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

    digital_out_init( &ctx->md0, cfg->md0 );
    digital_out_init( &ctx->md1, cfg->md1 );
    

    digital_out_write( &ctx->md0, SINGLEWIRECAN_PIN_STATE_LOW );
    digital_out_write( &ctx->md1, SINGLEWIRECAN_PIN_STATE_LOW );

    return SINGLEWIRECAN_OK;
}

void singlewirecan_generic_write ( singlewirecan_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t singlewirecan_generic_read ( singlewirecan_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void singlewirecan_set_md_0_pin_state ( singlewirecan_t *ctx, uint8_t rst_state )
{
    if ( rst_state == SINGLEWIRECAN_PIN_STATE_LOW )
    {
        digital_out_low( &ctx->md0 );
    }
    else
    {
         digital_out_high( &ctx->md0 );
    }
}

void singlewirecan_set_md_1_pin_state ( singlewirecan_t *ctx, uint8_t cs_state )
{
    if ( cs_state == SINGLEWIRECAN_PIN_STATE_LOW )
    {
         digital_out_low( &ctx->md1 );
    }
    else
    {
         digital_out_high( &ctx->md1 );
    }
}

void singlewirecan_set_operating_mode ( singlewirecan_t *ctx, uint8_t op_mode )
{
    switch ( op_mode )
    {
        case SINGLEWIRECAN_OPERATING_MODE_SLEEP:
        {
            singlewirecan_set_md_0_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            singlewirecan_set_md_1_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            break;
        }
        case SINGLEWIRECAN_OPERATING_MODE_HIGH_SPEED:
        {
            singlewirecan_set_md_0_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            singlewirecan_set_md_1_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_HIGH );
            break;
        }
        case SINGLEWIRECAN_OPERATING_MODE_HIGH_VOLTAGE_WAKE_UP:
        {
            singlewirecan_set_md_0_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_HIGH );
            singlewirecan_set_md_1_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            break;
        }
        case SINGLEWIRECAN_OPERATING_MODE_NORMAL:
        {
            singlewirecan_set_md_0_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_HIGH );
            singlewirecan_set_md_1_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_HIGH );
            break;
        }
        default:
        {
            singlewirecan_set_md_0_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            singlewirecan_set_md_1_pin_state( ctx, SINGLEWIRECAN_PIN_STATE_LOW );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

