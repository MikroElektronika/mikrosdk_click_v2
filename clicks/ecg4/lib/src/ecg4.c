/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "ecg4.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ecg4_cfg_setup ( ecg4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

ECG4_RETVAL ecg4_init ( ecg4_t *ctx, ecg4_cfg_t *cfg )
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    return ECG4_OK;
}

void ecg4_module_reset ( ecg4_t *ctx )
{
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms( );
    Delay_100ms( );
}

void ecg4_enable_ldo_ctrl ( ecg4_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_write( &ctx->cs, 1 );
    }
    else
    {
        digital_out_write( &ctx->cs, 0 );
    }
}

void ecg4_generic_write ( ecg4_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t ecg4_generic_read ( ecg4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t ecg4_responseReady( ecg4_t *ctx )
{
    if ( ctx->response_ready )
    {
        ctx->response_ready = ECG4_RESPONSE_NOT_READY;

        return ECG4_RESPONSE_READY;
    }

    return ECG4_RESPONSE_NOT_READY;
}


void ecg4_uart_isr( ecg4_t *ctx, uint8_t rx_dat )
{
    static uint8_t rx_buff[ 256 ];
    static uint8_t rx_cnt = 0;
    static uint8_t rx_idx;
    static uint8_t payload_size;
    static uint8_t row_check = 0;
    static uint8_t op_code;
    static uint8_t row_size;
    static uint8_t row_size_check;
    static uint32_t checksum = 0;
    static uint8_t row_cnt = 0;

    
    if ( ( rx_cnt == 0 ) && ( rx_dat != ECG4_SYNC_BYTE ) )
    {
        rx_cnt = 0;
        
        return;
    }
    else if ( ( rx_cnt == 1 ) && ( rx_dat != ECG4_SYNC_BYTE ) )
    {
        rx_cnt = 0;
        
        return;
    }
    else if ( rx_cnt == 2 )
    {
        payload_size = rx_dat;
        rx_cnt++;
        row_check = 1;
        
        return;
    }
    else if ( rx_cnt > 2 )
    {
        if ( rx_cnt - 3 < payload_size )
        {
            if ( rx_dat == ECG4_EXCODE_BYTE )
            {
                row_check = 1;
                checksum += rx_dat;
                rx_cnt++;
                
                return;
            }
            
            if ( row_check == 1 )
            {
                op_code = rx_dat;
                row_check = 0;
                checksum += rx_dat;
                
                if ( ( op_code == ECG4_SIGNAL_QUALITY_CODE_BYTE ) || ( op_code == ECG4_HEART_RATE_CODE_BYTE ) )
                {
                    row_size = 1;
                    row_size_check = 0;
                }
                else if ( op_code == ECG4_RAW_DATA_CODE_BYTE )
                {
                    row_size_check = 1;
                }
                else
                {
                    rx_cnt = 0;
                    checksum = 0;
                    
                    return;
                }
                
                rx_idx = 0;
                rx_cnt++;
                
                return;
            }
            
            if ( row_size_check == 1 )
            {
                row_size = rx_dat;
                row_size_check = 0;
                checksum += rx_dat;
                rx_cnt++;
                
                return;
            }
            
            if ( rx_idx < row_size )
            {
                rx_buff[ rx_idx ] = rx_dat;
                rx_idx++;
                checksum += rx_dat;
                
                if ( rx_idx == row_size )
                {
                    ctx->driver_hdl( &op_code, &row_size, rx_buff, &row_cnt );
                    row_cnt++;
                    row_check = 1;
                }
                
                rx_cnt++;
                
                return;
            }
        }
        else
        {
            checksum &= 0xFF;
            checksum = ~checksum & 0xFF;
            
            if ( checksum == rx_dat )
            {
                ctx->response_ready = ECG4_RESPONSE_READY;
            }
            else
            {
                ctx->response_ready = ECG4_RESPONSE_NOT_READY;
            }
            
            checksum = 0;
            row_cnt = 0;
            rx_cnt = 0;
            rx_idx = 0;
            
            return;
        }
    }
    
    rx_cnt++;
}
// ------------------------------------------------------------------------- END

