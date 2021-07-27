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
 * @file ata6571.c
 * @brief ATA6571 Click Driver.
 */

#include "ata6571.h"

void ata6571_cfg_setup ( ata6571_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->nstb   = HAL_PIN_NC;
    cfg->nerr   = HAL_PIN_NC;
    cfg->en     = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ata6571_init ( ata6571_t *ctx, ata6571_cfg_t *cfg ) 
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->nstb, cfg->nstb );
    digital_out_init( &ctx->en, cfg->en );
    
    // Input pins
    digital_in_init( &ctx->nerr, cfg->nerr );

    return UART_SUCCESS;
}

err_t ata6571_generic_write ( ata6571_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ata6571_generic_read ( ata6571_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ata6571_set_nstb_pin ( ata6571_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->nstb, state );
}

void ata6571_set_en_pin ( ata6571_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->en, state );
}

uint8_t ata6571_get_nerr_pin ( ata6571_t *ctx ) 
{
    return digital_in_read( &ctx->nerr );
}

void ata6571_set_operating_mode ( ata6571_t *ctx, uint8_t op_mode )
{
    switch ( op_mode )
    {
        case ATA6571_OPERATING_MODE_SLEEP:
        {
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_LOW );
            ata6571_set_en_pin( ctx, ATA6571_PIN_STATE_HIGH );
            break;
        }
        case ATA6571_OPERATING_MODE_STANDBY:
        {
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_HIGH );
            Delay_1ms( );
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_LOW );
            ata6571_set_en_pin( ctx, ATA6571_PIN_STATE_LOW );
            break;
        }
        case ATA6571_OPERATING_MODE_SILENT:
        {
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_HIGH );
            ata6571_set_en_pin( ctx, ATA6571_PIN_STATE_LOW );
            break;
        }
        case ATA6571_OPERATING_MODE_NORMAL:
        {
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_HIGH );
            ata6571_set_en_pin( ctx, ATA6571_PIN_STATE_HIGH );
            break;
        }
        default:
        {
            ata6571_set_nstb_pin( ctx, ATA6571_PIN_STATE_HIGH );
            ata6571_set_en_pin( ctx, ATA6571_PIN_STATE_HIGH );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
