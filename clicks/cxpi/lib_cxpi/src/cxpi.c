/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file cxpi.c
 * @brief CXPI Click Driver.
 */

#include "cxpi.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Initialization of 10 milliseconds delay.
 */
static void dev_init_delay ( void );

/**
 * @brief Change operation mode of 100 milliseconds delay.
 */
static void dev_change_mode_delay ( void );

/**
 * @brief Send command 100 milliseconds delay.
 */
static void dec_send_cmd_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void cxpi_cfg_setup ( cxpi_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t cxpi_init ( cxpi_t *ctx, cxpi_cfg_t *cfg ) {
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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return UART_SUCCESS;
}

err_t cxpi_generic_write ( cxpi_t *ctx, char *data_buf, uint16_t len ) {
    return uart_write( &ctx->uart, data_buf, len );
}

err_t cxpi_generic_read ( cxpi_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void cxpi_write_byte ( cxpi_t *ctx, uint8_t input ) {
    uart_write( &ctx->uart, &input, 1 );
}

uint8_t cxpi_read_byte ( cxpi_t *ctx ) {
    uint8_t data_buf;
    uart_read( &ctx->uart, &data_buf, 1 );
    return data_buf;
}

uint8_t cxpi_byte_ready ( cxpi_t *ctx ) {
    return uart_bytes_available( &ctx->uart);
}

void cxpi_send_command ( cxpi_t *ctx, char *command ) {
    char tmp_buf[ 100 ];
    uint8_t len;
    uint8_t cnt;

    memset( tmp_buf, 0, 100 );
    len = strlen( command );

    strncpy( tmp_buf, command, len );

    for( cnt = 0; cnt < len; cnt++ ) {
        cxpi_generic_write( ctx, &tmp_buf[ cnt ], 1 );
        dec_send_cmd_delay( );
    }
}

void cxpi_set_nslp_pin_state ( cxpi_t *ctx, uint8_t pin_state ) {
    if ( pin_state == CXPI_PIN_STATE_ENABLE ) {
        digital_out_high( &ctx->en );
    } else {
        digital_out_low( &ctx->en );
    }
}

void cxpi_set_pwm_pin_state ( cxpi_t *ctx, uint8_t pin_state ) {
    if ( pin_state == CXPI_PIN_STATE_ENABLE ) {
        digital_out_high( &ctx->pwm );
    } else {
        digital_out_low( &ctx->pwm );
    }
}

void cxpi_set_through_mode ( cxpi_t *ctx ) {
    digital_out_low( &ctx->en );
    dev_init_delay( );
    digital_out_high( &ctx->pwm );
    dev_init_delay( );
    digital_out_low( &ctx->pwm );
    dev_init_delay( );
    digital_out_high( &ctx->pwm );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_init_delay ( void ) {
    Delay_10ms( );
}

static void dev_change_mode_delay ( void ) {
    Delay_100ms( );
}

static void dec_send_cmd_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
