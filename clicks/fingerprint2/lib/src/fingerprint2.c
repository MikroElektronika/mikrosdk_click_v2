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

#include "fingerprint2.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fingerprint2_cfg_setup ( fingerprint2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ld1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;
    cfg->ld2 = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

FINGERPRINT2_RETVAL fingerprint2_init ( fingerprint2_t *ctx, fingerprint2_cfg_t *cfg )
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
    digital_out_init( &ctx->gp1, cfg->gp1 );
    digital_out_init( &ctx->gp2, cfg->gp2 );

    // Input pins

    digital_in_init( &ctx->ld1, cfg->ld1 );
    digital_in_init( &ctx->ld2, cfg->ld2 );

    return FINGERPRINT2_OK;
}

void fingerprint2_generic_write ( fingerprint2_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t fingerprint2_generic_read ( fingerprint2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t fingerprint2_get_ld1_status ( fingerprint2_t *ctx )
{
    return digital_in_read( &ctx->ld1 );
}

uint8_t fingerprint2_get_ld2_status ( fingerprint2_t *ctx )
{
    return digital_in_read( &ctx->ld2 );
}

void fingerprint2_set_rst_status ( fingerprint2_t *ctx, uint8_t status )
{
    
    digital_out_write( &ctx->rst, status );
}

void fingerprint2_set_gp1_status ( fingerprint2_t *ctx, uint8_t status )
{
    digital_out_write( &ctx->gp1, status );
}

void fingerprint2_set_gp2_status ( fingerprint2_t *ctx, uint8_t status )
{
    digital_out_write( &ctx->gp2, status );
}

void fingerprint2_reset ( fingerprint2_t *ctx )
{
    uint8_t dummy;
    digital_out_low( &ctx->rst );
    Delay_1ms(  );
    digital_out_high( &ctx->rst );
    Delay_1sec(  );
    fingerprint2_generic_read ( ctx, &dummy, 1 );
}

void fingerprint2_reg_one_fp ( fingerprint2_t *ctx, uint8_t fp_index )
{
    char snd_cmd[ 30 ] = "<C>RegisterOneFp=";
    char end_cmd[ 10 ] = "</C>";
    char num_cmd[ 3 ] = { 0 };
    uint8_t value;
    
    if ( fp_index > 24 )
    {
        return;
    }

    if ( ( fp_index / MOD_NUM ) > 0 )
    {
        value = fp_index / MOD_NUM;
        num_cmd[ 0 ] = value + VAL_CHAR;
        num_cmd[ 1 ] = ( fp_index % MOD_NUM ) + VAL_CHAR;
    }
    else
    {
        num_cmd[ 0 ] = fp_index + VAL_CHAR;
    }
    
    strcat( snd_cmd, num_cmd );
    strcat( snd_cmd, end_cmd );

    fingerprint2_generic_write( ctx, &snd_cmd[ 0 ], strlen( snd_cmd ) );
}

void fingerprint2_delete_one_fp ( fingerprint2_t *ctx, uint8_t fp_index )
{
    char snd_cmd[ 50 ] = "<C>ClearOneFp=";
    char end_cmd[ 10 ] = "</C>";
    char num_cmd[ 3 ] = { 0 };
    uint8_t value;

    if ( fp_index > 24 )
    {
        return;
    }

    if ( ( fp_index / MOD_NUM ) > 0 )
    {
        value = fp_index / MOD_NUM;
        num_cmd[ 0 ] = value + VAL_CHAR;
        num_cmd[ 1 ] = ( fp_index % MOD_NUM ) + VAL_CHAR;
    }
    else
    {
        num_cmd[ 0 ] = fp_index + VAL_CHAR;
    }

    strcat( snd_cmd, num_cmd );
    strcat( snd_cmd, end_cmd );

    fingerprint2_generic_write( ctx, &snd_cmd[ 0 ], strlen( snd_cmd ) );
}

// ------------------------------------------------------------------------- END

