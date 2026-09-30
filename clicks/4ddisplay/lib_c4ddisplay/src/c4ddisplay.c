/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c4ddisplay.c
 * @brief 4D - display Click Driver.
 */

#include "c4ddisplay.h"

/**
 * @brief 4D - display Click complete frame writing function.
 * @details This function queues all bytes of a command before waiting for its reply.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] frame : Command frame including checksum.
 * @param[in] len : Number of bytes in the frame.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note Partial writes advance the buffer pointer; transmitted bytes are never repeated.
 */
static err_t c4ddisplay_write_frame ( c4ddisplay_t *ctx, uint8_t *frame, uint8_t len );

/**
 * @brief 4D - display Click reply frame reading function.
 * @details This function reads one ACK, NAK, or complete six-byte object report.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in,out] remaining_ms : Remaining one-millisecond polling budget.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note The reply is stored in ctx->reply. ACK-like bytes inside a report are payload.
 */
static err_t c4ddisplay_read_frame ( c4ddisplay_t *ctx, uint16_t *remaining_ms );

/**
 * @brief 4D - display Click command exchange function.
 * @details This function appends the XOR checksum, sends a command, and matches its response.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in,out] frame : Command bytes with space reserved for the final checksum.
 * @param[in] len : Total command length, including checksum.
 * @return Success or a negative #c4ddisplay_return_value_t error.
 * @note Touch events are queued while waiting. A failed exchange cannot reuse a late ACK.
 */
static err_t c4ddisplay_exchange ( c4ddisplay_t *ctx, uint8_t *frame, uint8_t len );

void c4ddisplay_cfg_setup ( c4ddisplay_cfg_t *cfg )
{
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = C4DDISPLAY_BAUD_RATE;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t c4ddisplay_init ( c4ddisplay_t *ctx, c4ddisplay_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    err_t error_flag = C4DDISPLAY_ERROR_ARGUMENT;
    uint8_t dummy_read;

    if ( ctx && cfg && !cfg->uart_blocking && cfg->baud_rate &&
         ( HAL_PIN_NC != cfg->rst ) &&
         ( UART_DATA_BITS_DEFAULT == cfg->data_bit ) &&
         ( UART_PARITY_DEFAULT == cfg->parity_bit ) &&
         ( UART_STOP_BITS_DEFAULT == cfg->stop_bit ) )
    {
        ctx->event_head = 0;
        ctx->event_count = 0;
        ctx->synchronized = 0;
        error_flag = C4DDISPLAY_ERROR;

        uart_configure_default( &uart_cfg );
        ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
        ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;
        uart_cfg.rx_pin = cfg->rx_pin;
        uart_cfg.tx_pin = cfg->tx_pin;
        uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
        uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

        if ( UART_ERROR != uart_open( &ctx->uart, &uart_cfg ) )
        {
            if ( ( UART_ERROR != uart_set_baud( &ctx->uart, cfg->baud_rate ) ) &&
                 ( UART_ERROR != uart_set_parity( &ctx->uart, cfg->parity_bit ) ) &&
                 ( UART_ERROR != uart_set_stop_bits( &ctx->uart, cfg->stop_bit ) ) &&
                 ( UART_ERROR != uart_set_data_bits( &ctx->uart, cfg->data_bit ) ) )
            {
                digital_out_init( &ctx->rst, cfg->rst );
                digital_out_high( &ctx->rst );
                uart_set_blocking( &ctx->uart, false );

                // Start the SDK receive interrupt before the display can return a reply.
                uart_read( &ctx->uart, &dummy_read, 1 );
                error_flag = C4DDISPLAY_OK;
            }
            else
            {
                uart_close( &ctx->uart );
            }
        }
    }
    return error_flag;
}

err_t c4ddisplay_default_cfg ( c4ddisplay_t *ctx )
{
    c4ddisplay_reset( ctx );
    return c4ddisplay_set_contrast( ctx, C4DDISPLAY_CONTRAST_MAX );
}

void c4ddisplay_reset ( c4ddisplay_t *ctx )
{
    ctx->synchronized = 0;
    ctx->event_head = 0;
    ctx->event_count = 0;

    // Cancel old UART traffic while the display is held in reset.
    digital_out_low( &ctx->rst );
    uart_clear( &ctx->uart );
    Delay_100ms();
    digital_out_high( &ctx->rst );

    // Allow time for display startup and loading graphics from microSD.
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();

    uart_clear( &ctx->uart );
    ctx->synchronized = 1;
}

err_t c4ddisplay_write_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t value )
{
    uint8_t frame[ C4DDISPLAY_FRAME_SIZE ];

    // Standard object frame: command, type, index, value MSB, value LSB, checksum.
    frame[ 0 ] = C4DDISPLAY_CMD_WRITE_OBJ;
    frame[ 1 ] = object;
    frame[ 2 ] = index;
    frame[ 3 ] = ( uint8_t ) ( value >> 8 );
    frame[ 4 ] = ( uint8_t ) value;
    return c4ddisplay_exchange( ctx, frame, sizeof( frame ) );
}

err_t c4ddisplay_read_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t *value )
{
    uint8_t frame[ 4 ];
    err_t error_flag = C4DDISPLAY_ERROR_ARGUMENT;

    if ( value )
    {
        frame[ 0 ] = C4DDISPLAY_CMD_READ_OBJ;
        frame[ 1 ] = object;
        frame[ 2 ] = index;
        error_flag = c4ddisplay_exchange( ctx, frame, sizeof( frame ) );
        if ( C4DDISPLAY_OK == error_flag )
        {
            // Only a matching, checksum-validated REPORT_OBJ reaches this point.
            *value = ( ( uint16_t ) ctx->reply[ 3 ] << 8 ) | ctx->reply[ 4 ];
        }
    }
    return error_flag;
}

err_t c4ddisplay_set_contrast ( c4ddisplay_t *ctx, uint8_t value )
{
    uint8_t frame[ 3 ];
    err_t error_flag = C4DDISPLAY_ERROR_ARGUMENT;

    if ( value <= C4DDISPLAY_CONTRAST_MAX )
    {
        frame[ 0 ] = C4DDISPLAY_CMD_WRITE_CONTRAST;
        frame[ 1 ] = value;
        error_flag = c4ddisplay_exchange( ctx, frame, sizeof( frame ) );
    }
    return error_flag;
}

err_t c4ddisplay_read_event ( c4ddisplay_t *ctx, c4ddisplay_event_t *event )
{
    err_t error_flag = C4DDISPLAY_ERROR_ARGUMENT;
    uint16_t remaining_ms = C4DDISPLAY_FRAME_TIMEOUT;

    if ( event )
    {
        error_flag = C4DDISPLAY_ERROR_STATE;
        if ( ctx->synchronized )
        {
            error_flag = C4DDISPLAY_NO_EVENT;
            if ( ctx->event_count )
            {
                // Deliver queued events before reading newer UART traffic.
                memcpy( ctx->reply, ctx->events[ ctx->event_head ], C4DDISPLAY_FRAME_SIZE );
                ctx->event_head++;
                if ( ctx->event_head == C4DDISPLAY_EVENT_COUNT )
                {
                    ctx->event_head = 0;
                }
                ctx->event_count--;
                error_flag = C4DDISPLAY_OK;
            }
            else if ( uart_bytes_available( &ctx->uart ) )
            {
                error_flag = c4ddisplay_read_frame( ctx, &remaining_ms );
                if ( ( C4DDISPLAY_OK == error_flag ) &&
                     ( C4DDISPLAY_CMD_REPORT_EVENT != ctx->reply[ 0 ] ) )
                {
                    error_flag = C4DDISPLAY_ERROR_FRAME;
                }
            }

            if ( C4DDISPLAY_OK == error_flag )
            {
                event->object = ctx->reply[ 1 ];
                event->index = ctx->reply[ 2 ];
                event->value = ( ( uint16_t ) ctx->reply[ 3 ] << 8 ) | ctx->reply[ 4 ];
            }
            else if ( error_flag < 0 )
            {
                ctx->synchronized = 0;
            }
        }
    }
    return error_flag;
}

err_t c4ddisplay_generic_write ( c4ddisplay_t *ctx, uint8_t *data_in, uint16_t len )
{
    ctx->synchronized = 0;
    return uart_write( &ctx->uart, data_in, len );
}

err_t c4ddisplay_generic_read ( c4ddisplay_t *ctx, uint8_t *data_out, uint16_t len )
{
    ctx->synchronized = 0;
    return uart_read( &ctx->uart, data_out, len );
}

static err_t c4ddisplay_write_frame ( c4ddisplay_t *ctx, uint8_t *frame, uint8_t len )
{
    err_t error_flag = C4DDISPLAY_OK;
    err_t write_size;
    uint8_t offset = 0;
    uint16_t wait_ms = 0;

    while ( ( offset < len ) && ( wait_ms < C4DDISPLAY_REPLY_TIMEOUT ) &&
            ( C4DDISPLAY_OK == error_flag ) )
    {
        write_size = uart_write( &ctx->uart, &frame[ offset ], len - offset );
        if ( ( write_size < 0 ) || ( write_size > len - offset ) )
        {
            error_flag = C4DDISPLAY_ERROR;
        }
        else if ( write_size > 0 )
        {
            offset += write_size;
        }
        else
        {
            Delay_1ms();
            wait_ms++;
        }
    }
    if ( ( C4DDISPLAY_OK == error_flag ) && ( offset < len ) )
    {
        error_flag = C4DDISPLAY_TIMEOUT;
    }
    return error_flag;
}

static err_t c4ddisplay_read_frame ( c4ddisplay_t *ctx, uint16_t *remaining_ms )
{
    err_t error_flag = C4DDISPLAY_OK;
    uint8_t length = 1;
    uint8_t count = 0;
    uint8_t checksum = 0;

    while ( ( count < length ) && *remaining_ms && ( C4DDISPLAY_OK == error_flag ) )
    {
        if ( uart_bytes_available( &ctx->uart ) )
        {
            if ( 1 != uart_read( &ctx->uart, &ctx->reply[ count ], 1 ) )
            {
                error_flag = C4DDISPLAY_ERROR;
            }
            else
            {
                checksum ^= ctx->reply[ count ];
                if ( 0 == count )
                {
                    // Interpret reply tokens only at a frame boundary.
                    if ( ( C4DDISPLAY_CMD_REPORT_OBJ == ctx->reply[ 0 ] ) ||
                         ( C4DDISPLAY_CMD_REPORT_EVENT == ctx->reply[ 0 ] ) )
                    {
                        length = C4DDISPLAY_FRAME_SIZE;
                    }
                    else if ( ( C4DDISPLAY_REPLY_ACK != ctx->reply[ 0 ] ) &&
                              ( C4DDISPLAY_REPLY_NAK != ctx->reply[ 0 ] ) )
                    {
                        error_flag = C4DDISPLAY_ERROR_FRAME;
                    }
                }
                count++;
            }
        }
        else
        {
            Delay_1ms();
            ( *remaining_ms )--;
        }
    }
    if ( C4DDISPLAY_OK == error_flag )
    {
        if ( count < length )
        {
            error_flag = C4DDISPLAY_TIMEOUT;
        }
        else if ( ( C4DDISPLAY_FRAME_SIZE == length ) && checksum )
        {
            // XOR of every byte, including the received checksum, must be zero.
            error_flag = C4DDISPLAY_ERROR_CHECKSUM;
        }
    }
    return error_flag;
}

static err_t c4ddisplay_exchange ( c4ddisplay_t *ctx, uint8_t *frame, uint8_t len )
{
    err_t error_flag = C4DDISPLAY_ERROR_STATE;
    uint16_t remaining_ms = C4DDISPLAY_REPLY_TIMEOUT;
    uint8_t index;
    uint8_t received = 0;

    if ( ctx->synchronized )
    {
        frame[ len - 1 ] = 0;
        for ( index = 0; index < len - 1; index++ )
        {
            frame[ len - 1 ] ^= frame[ index ];
        }
        error_flag = c4ddisplay_write_frame( ctx, frame, len );
        while ( ( C4DDISPLAY_OK == error_flag ) && remaining_ms && !received )
        {
            error_flag = c4ddisplay_read_frame( ctx, &remaining_ms );
            if ( C4DDISPLAY_OK == error_flag )
            {
                if ( C4DDISPLAY_CMD_REPORT_EVENT == ctx->reply[ 0 ] )
                {
                    if ( ctx->event_count < C4DDISPLAY_EVENT_COUNT )
                    {
                        index = ( ctx->event_head + ctx->event_count ) % C4DDISPLAY_EVENT_COUNT;
                        memcpy( ctx->events[ index ], ctx->reply, C4DDISPLAY_FRAME_SIZE );
                        ctx->event_count++;
                    }
                    else
                    {
                        error_flag = C4DDISPLAY_ERROR_OVERFLOW;
                    }

                    // Event traffic must not keep extending a missing command reply.
                    if ( remaining_ms )
                    {
                        Delay_1ms();
                        remaining_ms--;
                    }
                }
                else if ( C4DDISPLAY_REPLY_NAK == ctx->reply[ 0 ] )
                {
                    error_flag = C4DDISPLAY_ERROR_NAK;
                }
                else if ( C4DDISPLAY_CMD_READ_OBJ == frame[ 0 ] )
                {
                    if ( ( C4DDISPLAY_CMD_REPORT_OBJ == ctx->reply[ 0 ] ) &&
                         ( frame[ 1 ] == ctx->reply[ 1 ] ) &&
                         ( frame[ 2 ] == ctx->reply[ 2 ] ) )
                    {
                        received = 1;
                    }
                    else
                    {
                        error_flag = C4DDISPLAY_ERROR_FRAME;
                    }
                }
                else if ( C4DDISPLAY_REPLY_ACK == ctx->reply[ 0 ] )
                {
                    received = 1;
                }
                else
                {
                    error_flag = C4DDISPLAY_ERROR_FRAME;
                }
            }
        }
        if ( ( C4DDISPLAY_OK == error_flag ) && !received )
        {
            error_flag = C4DDISPLAY_TIMEOUT;
        }
        if ( ( error_flag < 0 ) && ( C4DDISPLAY_ERROR_NAK != error_flag ) )
        {
            // ACK has no sequence number; a late ACK cannot safely satisfy another request.
            ctx->synchronized = 0;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
